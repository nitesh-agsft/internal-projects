
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

#include "ChangeBuffer.h"

#include <assert.h>

namespace opendnp3
{

size_t ChangeBuffer::FlushUpdates(IDataObserver* apObserver)
{
	assert(this->InProgress());
	size_t count = this->mChangeQueue.size();
	if(count > 0) {
		Transaction t(apObserver);
for(auto f: mChangeQueue) f(apObserver);
	}
	this->Clear();
	return count;
}

void ChangeBuffer::_Start()
{
	mMutex.lock();
}

void ChangeBuffer::_End()
{
	bool notify = mNotify;
	mNotify = false;
	mMutex.unlock();
	if(notify) this->NotifyObservers();
}

void ChangeBuffer::_Update(const Binary& arPoint, size_t aIndex)
{
	mChangeQueue.push_back(std::bind(&ChangeBuffer::Dispatch<Binary>, std::placeholders::_1, arPoint, aIndex));
	mNotify = true;
}

void ChangeBuffer::_Update(const Analog& arPoint, size_t aIndex)
{
	mChangeQueue.push_back(std::bind(&ChangeBuffer::Dispatch<Analog>, std::placeholders::_1, arPoint, aIndex));
	mNotify = true;
}

void ChangeBuffer::_Update(const Counter& arPoint, size_t aIndex)
{
	mChangeQueue.push_back(std::bind(&ChangeBuffer::Dispatch<Counter>, std::placeholders::_1, arPoint, aIndex));
	mNotify = true;
}

void ChangeBuffer::_Update(const ControlStatus& arPoint, size_t aIndex)
{
	mChangeQueue.push_back(std::bind(&ChangeBuffer::Dispatch<ControlStatus>, std::placeholders::_1, arPoint, aIndex));
	mNotify = true;
}

void ChangeBuffer::_Update(const SetpointStatus& arPoint, size_t aIndex)
{
	mChangeQueue.push_back(std::bind(&ChangeBuffer::Dispatch<SetpointStatus>, std::placeholders::_1, arPoint, aIndex));
	mNotify = true;
}

void ChangeBuffer::Clear()
{
	assert(this->InProgress());
	_Clear();
}

void ChangeBuffer::_Clear()
{
	mChangeQueue.clear();
}

}


