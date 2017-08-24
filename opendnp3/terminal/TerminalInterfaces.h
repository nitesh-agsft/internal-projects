//
// Licensed to Green Energy Corp (www.greenenergycorp.com) under one
// or more contributor license agreements. See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  Green Enery Corp licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//

#ifndef __TERMINAL_INTERFACES_H_
#define __TERMINAL_INTERFACES_H_

#include <string>
#include <vector>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include <opendnp3/APL/Exception.h>
#include <opendnp3/APL/Types.h>
#include <opendnp3/APL/ITimerSource.h>

namespace apl
{
enum RetcodeType {
	TYPE_BAD_ARGUMENTS,
	TYPE_SUCCESS,
	TYPE_QUALIFIED_SUCCESS,
	TYPE_FAILURE
};

class retcode
{
	RetcodeType value;
	int code;
public:
	retcode() {};
	retcode(RetcodeType aValue, int aCode) {
		value = aValue;
		code = aCode;
	}

	bool operator==(const retcode& other) const {
		return this->value == other.value && this->code == other.code;
	}

	bool operator!=(const retcode& other) const {
		return !(this->value == other.value);
	}

	bool operator>=(const retcode& other) const {
		return this->value >= other.value || this->code >= other.code;
	}

	bool operator<=(const retcode& other) const {
		return this->value <= other.value;
	}

	bool operator>(const retcode& other) const {
		return this->value > other.value;
	}
	bool operator<(const retcode& other) const {
		return this->value < other.value;
	}
	retcode& operator|=(const retcode& other) {
		if(this->value != TYPE_SUCCESS) return *this;
		if(other.value != TYPE_SUCCESS) {
			this->value = other.value;
			this->code = other.code;
		}
		return *this;
	}
};

#define BAD_ARGUMENTS apl::retcode(apl::TYPE_BAD_ARGUMENTS,0)
#define SUCCESS apl::retcode(apl::TYPE_SUCCESS,0)
#define QUALIFIED_SUCCESS(code) apl::retcode(apl::TYPE_QUALIFIED_SUCCESS,code)
#define FAILURE(code) apl::retcode(apl::TYPE_FAILURE,code)

typedef boost::function<retcode (std::vector<std::string>&)> CommandHandler;

struct CommandNode {
	CommandHandler mHandler;
	std::string mName;
	std::string mUsage;
	std::string mDesc;

	std::string ToString() const;
};

typedef boost::function<void (const std::string& arLine)> RedirectFunc;

class ITerminal
{
public:

	const static int TERMINAL_CODE = 1 << 23; //pick a suitably high number for this code

	virtual ~ITerminal() {}

	virtual void BindCommand(const CommandNode& arNode, const std::string& arFullCommand) = 0;
	virtual void QueueSend(const std::string& arData, bool aLog = true) = 0;
	virtual void SetRedirect(const RedirectFunc&) = 0;
	virtual void ClearRedirect() = 0;
	virtual void Post(const FunctionVoidZero& arHandler) = 0;

	const static char EOL[3];
	const static char CLEAR_SRC[2];
};

class ITerminalExtension
{
public:

	ITerminalExtension() : mpTerminal(NULL) {}
	virtual ~ITerminalExtension() {}

	void BindToTerminal(ITerminal* apTerminal) {
		assert(apTerminal != NULL);
		assert(mpTerminal == NULL);
		mpTerminal = apTerminal;
		this->_BindToTerminal(apTerminal);
	}

	void Post(const FunctionVoidZero& arHandler) {
		mpTerminal->Post(arHandler);
	}

	void SetRedirect(const RedirectFunc& arRedirect) {
		mpTerminal->SetRedirect(arRedirect);
	}

	void ClearRedirect() {
		mpTerminal->ClearRedirect();
	}

protected:

	void Send(const std::string& arData, bool aClearSrc = false) {
		assert(mpTerminal != NULL);
		mpTerminal->QueueSend(arData, aClearSrc);
	}

private:

	virtual void _BindToTerminal(ITerminal* apTerminal) = 0;

	ITerminal* mpTerminal;
};

};

#endif
