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
#include "MockTimerSource.h"


#include <boost/foreach.hpp>
#include <boost/thread.hpp>

using namespace boost::posix_time;

namespace apl
{

MockTimerSource::MockTimerSource() : mPostIsSynchronous(false)
{

}

MockTimerSource::~MockTimerSource()
{
	BOOST_FOREACH(MockTimer * i, mAllTimers) {
		delete i;
	}
}

bool MockTimerSource::DispatchOne()
{
	if(mPostQueue.size() > 0) {
		FunctionVoidZero callback = mPostQueue.front();
		mPostQueue.pop_front();
		callback();
		return true;
	} else {
		TimerMap::iterator front = mTimerMap.begin();

		if(front != mTimerMap.end()) {

			MockTimer* pTimer = front->second;
			mIdle.push_back(pTimer);
			mTimerMap.erase(front);

			// do the callback last so that if it does something to
			// the timer itself we're safe
			pTimer->mCallback();

			return true;
		}
	}

	return false;
}

size_t MockTimerSource::Dispatch(size_t aMaximum)
{
	size_t num = 0;
	while(num < aMaximum && this->DispatchOne()) ++num;
	return num;
}

void MockTimerSource::Post(const FunctionVoidZero& arHandler)
{
	if(mPostIsSynchronous) arHandler();
	else mPostQueue.push_back(arHandler);
}

void MockTimerSource::PostSync(const FunctionVoidZero& arHandler)
{
	this->Dispatch();
	arHandler();
}

ITimer* MockTimerSource::Start(millis_t aDelay, const FunctionVoidZero& arCallback)
{
	ptime t =  microsec_clock::universal_time() + milliseconds(aDelay);
	return Start(t, arCallback);
}

ITimer* MockTimerSource::Start(const boost::posix_time::ptime& arTime, const FunctionVoidZero& arCallback)
{
	MockTimer* pTimer;
	if(mIdle.size() > 0) {
		pTimer = mIdle.front();
		mIdle.pop_front();
		pTimer->mCallback = arCallback;
	} else {

		pTimer = new MockTimer(this, arTime, arCallback);
		mAllTimers.push_back(pTimer);
	}

	mTimerMap.insert(std::pair<ptime, MockTimer*>(arTime, pTimer));
	return pTimer;
}

void MockTimerSource::Cancel(ITimer* apTimer)
{
	for(TimerMap::iterator i = mTimerMap.begin(); i != mTimerMap.end(); ++i) {
		if(i->second == apTimer) {
			mIdle.push_back(i->second);
			mTimerMap.erase(i);
			return;
		}
	}
}

MockTimer::MockTimer(MockTimerSource* apSource, const boost::posix_time::ptime& arTime, const FunctionVoidZero& arCallback) :
	mTime(arTime),
	mpSource(apSource),
	mCallback(arCallback)
{

}

void MockTimer::Cancel()
{
	mpSource->Cancel(this);
}

boost::posix_time::ptime MockTimer::ExpiresAt()
{
	return mTime;
}

}


