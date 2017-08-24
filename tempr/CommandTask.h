
//
// Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
// more contributor license agreements. See the NOTICE file distributed
// with this work for additional information regarding copyright ownership.
// Green Energy Corp licenses this file to you under the Apache License,
// Version 2.0 (the "License"); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// This file was forked on 01/01/2013 by Automatak, LLC and modifications
// have been made to this file. Automatak, LLC licenses these modifications to
// you under the terms of the License.
//

#ifndef __COMMAND_TASK_H_
#define __COMMAND_TASK_H_

#include "MasterTaskBase.h"

#include <APL/APDUConstants.h>
#include <APL/CommandStatus.h>
#include <APL/Visibility.h>

#include <functional>
#include <queue>

namespace opendnp3
{

// Base class with machinery for performing command operations
class DLL_LOCAL CommandTask : public MasterTaskBase
{
	typedef std::function<CommandStatus (const APDU&)> Validator;
	typedef std::function<Validator (APDU&, FunctionCodes)> Formatter;
	typedef std::function<void (CommandStatus)> Responder;

public:
	CommandTask(Logger*);

	void Configure(const Formatter& arFormatter, const Responder& arResponder);
	void AddCommandCode(FunctionCodes aCode);

	void ConfigureRequest(APDU& arAPDU);

	std::string Name() const;

protected:

	Formatter mFormatter;
	Validator mValidator;
	Responder mResponder;

	// override from base class
	void OnFailure();

private:

	std::deque<FunctionCodes> mCodes;

	void Respond(CommandStatus aStatus);

	TaskResult _OnPartialResponse(const APDU&);
	TaskResult _OnFinalResponse(const APDU&);
};

} //ens ns

#endif
