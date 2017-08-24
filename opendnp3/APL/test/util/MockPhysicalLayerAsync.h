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
#ifndef __MOCK_PHYSICAL_LAYER_ASYNC_H_
#define __MOCK_PHYSICAL_LAYER_ASYNC_H_

#include <opendnp3/APL/PhysicalLayerAsyncBase.h>
#include <opendnp3/APL/IHandlerAsync.h>

#include "BufferTestObject.h"

namespace apl
{

class ITimerSource;

// Provides a backend for testing physical layers
class MockPhysicalLayerAsync : public PhysicalLayerAsyncBase, public BufferTestObject
{
public:
	MockPhysicalLayerAsync(Logger*, ITimerSource* apTimerSource = NULL);

	void SignalOpenSuccess();
	void SignalOpenFailure();
	void SignalSendSuccess();
	void SignalSendFailure();
	void SignalReadFailure();

	void TriggerRead(const std::string& arData);
	void TriggerClose();

	size_t NumWrites() {
		return mNumWrites;
	}
	size_t NumOpen() {
		return mNumOpen;
	}
	size_t NumOpenSuccess() {
		return mNumOpenSuccess;
	}
	size_t NumOpenFailure() {
		return mNumOpenFailure;
	}
	size_t NumClose() {
		return mNumClose;
	}

	void SetAutoOpen(bool aSuccess);

private:

	void DoOpen();
	void DoClose();
	void DoOpenSuccess() {
		++mNumOpenSuccess;
	}
	void DoOpenFailure() {
		++mNumOpenFailure;
	}

	void DoAsyncRead(boost::uint8_t* apBuff, size_t aNumBytes) {
		mpWriteBuff = apBuff;
		mNumToRead = aNumBytes;
	}

	void DoAsyncWrite(const boost::uint8_t* apData, size_t aNumBytes) {
		mNumToWrite = aNumBytes;
		++mNumWrites;
		WriteToBuffer(apData, aNumBytes);
	}

	boost::uint8_t* mpWriteBuff;

	size_t mNumToRead;
	size_t mNumToWrite;
	size_t mNumWrites;
	size_t mNumOpen;
	size_t mNumOpenSuccess;
	size_t mNumOpenFailure;
	size_t mNumClose;

	bool mIsAutoOpenSuccess;

	ITimerSource* mpTimerSource;
};

}

#endif
