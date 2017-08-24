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
#ifndef __MOCK_UPPER_LAYER_H_
#define __MOCK_UPPER_LAYER_H_

#include <opendnp3/APL/AsyncLayerInterfaces.h>
#include <boost/function.hpp>

#include "BufferTestObject.h"

namespace apl
{

class MockUpperLayer : public IUpperLayer, public BufferTestObject
{
public:

	typedef boost::function<void (const boost::uint8_t*, size_t)> OnReceiveHandler;

	struct State {

		State() {
			Reset();
		}

		size_t mSuccessCnt;
		size_t mFailureCnt;
		size_t mNumLayerUp;
		size_t mNumLayerDown;

		void Reset() {
			mSuccessCnt = mFailureCnt = mNumLayerUp = mNumLayerDown = 0;
		}
	};

	MockUpperLayer(Logger*);
	virtual ~MockUpperLayer() {}

	void SendDown(const std::string&);
	void SendDown(const boost::uint8_t* apData, size_t aNumBytes);

	bool CountersEqual(size_t success, size_t failure) {
		return mState.mSuccessCnt == success && mState.mFailureCnt == failure;
	}

	bool StateEquals(const State& s) {
		return (mState.mSuccessCnt == s.mSuccessCnt)
		       && (mState.mFailureCnt == s.mFailureCnt)
		       && (mState.mNumLayerUp == s.mNumLayerUp)
		       && (mState.mNumLayerDown == s.mNumLayerDown);
	}

	void Reset() {
		mState.Reset();
	}
	State GetState() {
		return mState;
	}

	void SetReceiveHandler(const OnReceiveHandler& arHandler) {
		mOnReceiveHandler = arHandler;
	}

private:

	virtual std::string RecvString() const {
		return "MockUpperLayer <-";
	}

	OnReceiveHandler mOnReceiveHandler;
	State mState;

	//these are the NVII delegates
	void _OnReceive(const boost::uint8_t*, size_t);
	void _OnSendSuccess();
	void _OnSendFailure();
	void _OnLowerLayerUp();
	void _OnLowerLayerDown();
};



}

#endif
