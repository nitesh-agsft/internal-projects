#include "ControlTerminalExtension.h"

#include <opendnp3/APL/FlexibleDataObserver.h>
#include <opendnp3/APL/CommandInterfaces.h>
#include <opendnp3/APL/CommandTypes.h>
#include <opendnp3/APL/CommandResponseQueue.h>
#include <opendnp3/APL/Util.h>
#include <opendnp3/APL/Parsing.h>

#include <boost/bind.hpp>
#include <sstream>

using namespace std;
using namespace boost;

namespace apl
{
typedef boost::function<std::string(boost::uint8_t)> QualityFunctor;

void ControlTerminalExtension::_BindToTerminal(ITerminal* apTerminal)
{
	CommandNode cmd;

	cmd.mName = "issue bo";
	cmd.mUsage  = "issue bo <index> lon|loff\r\n";
	cmd.mUsage += "       issue bo <index> pon|pclose|ptrip [<on time>] [<off time>] [<count>]";
	cmd.mDesc = "Issues a binary output command. ";
	cmd.mHandler = boost::bind(&ControlTerminalExtension::HandleIssueBO, this, _1);
	apTerminal->BindCommand(cmd, "issue bo");

	cmd.mName = "issue st";
	cmd.mUsage = "issue st <index> <integer|double>";
	cmd.mDesc = "Issues a setpoint request. If the value contains a \'.\', it is treated as a double.";
	cmd.mHandler = boost::bind(&ControlTerminalExtension::HandleIssueST, this, _1);
	apTerminal->BindCommand(cmd, "issue st");
}

void ControlTerminalExtension::WaitForResponse()
{
	this->Send("Waiting for response... ");
	CommandResponse rsp;
	bool success = mRspQueue.WaitForResponse(rsp, mSequence, 5000);
	ostringstream oss;
	if(success) {
		oss << "Result: " << ToString(rsp.mResult) << ITerminal::EOL;
		this->Send(oss.str());
	} else {
		oss << "Timeout" << ITerminal::EOL;
		this->Send(oss.str());
	}
}


retcode ControlTerminalExtension::HandleIssueST(std::vector<std::string>& arArgs)
{
	if(arArgs.size() < 2) return BAD_ARGUMENTS;

	Setpoint st;

	int index;

	if(!Parsing::GetPositive(arArgs[0], index)) return BAD_ARGUMENTS;
	if(arArgs[1].find('.') == std::string::npos) {
		int iValue;
		if(!Parsing::Get(arArgs[1], iValue)) return BAD_ARGUMENTS;
		st.SetValue(static_cast<boost::int32_t>(iValue));
	} else {
		double dValue;
		if(!Parsing::Get(arArgs[1], dValue)) return BAD_ARGUMENTS;
		st.SetValue(dValue);
	}

	mpCmdAcceptor->AcceptCommand(st, static_cast<size_t>(index), ++mSequence, &mRspQueue);
	WaitForResponse();
	return SUCCESS;
}

ControlCode ControlTerminalExtension::ParseControlCode( const std::string& arString )
{
	std::string lower(arString);
	toLowerCase(lower);
	if ( lower.compare("pon") == 0 )			return CC_PULSE;
	else if ( lower.compare("lon") == 0 )		return CC_LATCH_ON;
	else if ( lower.compare("loff") == 0 )		return CC_LATCH_OFF;
	else if ( lower.compare("pclose") == 0 )	return CC_PULSE_CLOSE;
	else if ( lower.compare("ptrip") == 0 )		return CC_PULSE_TRIP;
	else return CC_UNDEFINED;
}

retcode ControlTerminalExtension::HandleIssueBO(std::vector<std::string>& arArgs)
{
	if(arArgs.size() < 2) return BAD_ARGUMENTS;

	BinaryOutput b; b.mOnTimeMS = 100; b.mOffTimeMS = 100; b.mCount = 1;
	boost::uint32_t index;
	if(!Parsing::Get(arArgs[0], index)) return BAD_ARGUMENTS;

	b.mRawCode = static_cast<boost::uint8_t>(ParseControlCode(arArgs[1]));
	switch(b.mRawCode) {
	case(CC_PULSE):
	case(CC_PULSE_CLOSE):
	case(CC_PULSE_TRIP):
		switch(arArgs.size()) {
		case(5):
			if(!Parsing::Get(arArgs[4], b.mCount)) return BAD_ARGUMENTS;
		case(4):
			if(!Parsing::Get(arArgs[3], b.mOffTimeMS)) return BAD_ARGUMENTS;
		case(3):
			if(!Parsing::Get(arArgs[2], b.mOnTimeMS)) return BAD_ARGUMENTS;
		case(2):
			break;
		default:
			return BAD_ARGUMENTS;
		}
		break;
	case(CC_LATCH_ON):
	case(CC_LATCH_OFF):
		if(arArgs.size() > 2) return BAD_ARGUMENTS;
		break;
	default:
		return BAD_ARGUMENTS;
	}

	mpCmdAcceptor->AcceptCommand(b, index, ++mSequence, &mRspQueue);
	WaitForResponse();
	return SUCCESS;
}

}

