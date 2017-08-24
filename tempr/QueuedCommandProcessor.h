
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
// you under the GNU Affero General Public License Version 3.0
// (the "Additional License"). You may not use these modifications except in
// compliance with the additional license. You may obtain a copy of the Additional
// License at
//
// http://www.gnu.org/licenses/agpl.html
//
// Contact Automatak, LLC for a commercial license to these modifications
//
#ifndef __QUEUED_COMMAND_PROCESSOR_H_
#define __QUEUED_COMMAND_PROCESSOR_H_

#include <APL/ICommandProcessor.h>
#include <APL/SubjectBase.h>
#include <APL/Visibility.h>

#include <queue>
#include <mutex>

namespace opendnp3
{

class DLL_LOCAL QueuedCommandProcessor : public ICommandProcessor, public SubjectBase
{
public:

	QueuedCommandProcessor();

	// Implement the ICommandProcessor interface

	void SelectAndOperate(const ControlRelayOutputBlock& arCommand, size_t aIndex, std::function<void (CommandResponse)> aCallback);
	void DirectOperate(const ControlRelayOutputBlock& arCommand, size_t aIndex, std::function<void (CommandResponse)> aCallback);

	void SelectAndOperate(const AnalogOutputInt16& arCommand, size_t aIndex, std::function<void (CommandResponse)> aCallback);
	void DirectOperate(const AnalogOutputInt16& arCommand, size_t aIndex, std::function<void (CommandResponse)> aCallback);

	void SelectAndOperate(const AnalogOutputInt32& arCommand, size_t aIndex, std::function<void (CommandResponse)> aCallback);
	void DirectOperate(const AnalogOutputInt32& arCommand, size_t aIndex, std::function<void (CommandResponse)> aCallback);

	void SelectAndOperate(const AnalogOutputFloat32& arCommand, size_t aIndex, std::function<void (CommandResponse)> aCallback);
	void DirectOperate(const AnalogOutputFloat32& arCommand, size_t aIndex, std::function<void (CommandResponse)> aCallback);

	void SelectAndOperate(const AnalogOutputDouble64& arCommand, size_t aIndex, std::function<void (CommandResponse)> aCallback);
	void DirectOperate(const AnalogOutputDouble64& arCommand, size_t aIndex, std::function<void (CommandResponse)> aCallback);

	// Function used to marshall calls another ICommandProcessor

	bool Dispatch(ICommandProcessor* apProcessor);

private:
	std::mutex mMutex;
	std::queue<std::function<void (ICommandProcessor*)>> mRequestQueue;

	template <class T>
	void SelectAndOperateT(const T& arCommand, size_t aIndex, std::function<void (CommandResponse)> aCallback) {
		{
			std::lock_guard<std::mutex> lock(mMutex);
			mRequestQueue.push([arCommand, aIndex, aCallback](ICommandProcessor * pProcessor) {
				pProcessor->SelectAndOperate(arCommand, aIndex, aCallback);
			});
		}
		this->NotifyObservers();
	}

	template <class T>
	void DirectOperateT(const T& arCommand, size_t aIndex, std::function<void (CommandResponse)> aCallback) {
		{
			std::lock_guard<std::mutex> lock(mMutex);
			mRequestQueue.push([arCommand, aIndex, aCallback](ICommandProcessor * pProcessor) {
				pProcessor->DirectOperate(arCommand, aIndex, aCallback);
			});
		}
		this->NotifyObservers();
	}
};

}

#endif

