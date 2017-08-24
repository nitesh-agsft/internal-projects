
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
#ifndef __TRACKING_TASK_GROUP_H_
#define __TRACKING_TASK_GROUP_H_

#include <APL/Types.h>
#include <APL/Uncopyable.h>
#include <APL/Visibility.h>

#include "AsyncTaskInterfaces.h"

#include <set>
#include <queue>
#include <string>

namespace opendnp3
{

class AsyncTaskGroup;
class AsyncTaskContinuous;
class AsyncTaskBase;

/**
 Tracks all tasks that are created and releases them on destruction
*/
class DLL_LOCAL TrackingTaskGroup
{

public:

	TrackingTaskGroup(AsyncTaskGroup* apGroup);
	~TrackingTaskGroup();

	void ResetTasks(int aMask);

	AsyncTaskBase* Add(millis_t aPeriod, millis_t aRetryDelay, int aPriority, const TaskHandler& arCallback, const std::string& arName = "");
	AsyncTaskContinuous* AddContinuous(int aPriority, const TaskHandler& arCallback, const std::string& arName = "");


private:

	AsyncTaskGroup* mpGroup;

	typedef std::vector<AsyncTaskBase*> TaskVec;
	TaskVec mTaskVec;
};

}

#endif
