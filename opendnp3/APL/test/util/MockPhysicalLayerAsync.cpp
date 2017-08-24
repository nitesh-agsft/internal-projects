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
#include "MockPhysicalLayerAsync.h"

#include "BufferHelpers.h"
#include <opendnp3/APL/ITimerSource.h>

#include <memory.h>
#include <boost/bind.hpp>

using namespace boost::system;

namespace apl
{

MockPhysicalLayerAsync::MockPhysicalLayerAsync(Logger* apLogger, ITimerSource* apTimerSource) :
	PhysicalLayerAsyncBase(apLogger),
	mpWriteBuff(NULL),
	mNumToRead(0),
	mNumToWrite(0),
	mNumWrites(0),
	mNumOpen(0),
	mNumOpenSuccess(0),
	mNumOpenFailure(0),
	mNumClose(0),

	mIsAutoOpenSuccess(true),
	mpTimerSource(apTimerSource)
{

}

void MockPhysicalLayerAsync::SetAutoOpen(bool aIsSuccess)
{
	mIsAutoOpenSuccess = aIsSuccess;
}

void MockPhysicalLayerAsync::DoOpen()
{
	++mNumOpen;
	if(mpTimerSource) {
		if(this->mIsAutoOpenSuccess) mpTimerSource->Post(boost::bind(&MockPhysicalLayerAsync::SignalOpenSuccess, this));
		else mpTimerSource->Post(boost::bind(&MockPhysicalLayerAsync::SignalOpenFailure, this));
	}
}

void MockPhysicalLayerAsync::DoClose()
{
	++mNumClose;
	if(mpTimerSource) {
		mpTimerSource->Post(boost::bind(&MockPhysicalLayerAsync::DoThisLayerDown, this));
	}
}

void MockPhysicalLayerAsync::SignalOpenSuccess()
{
	error_code ec(errc::success, get_generic_category());
	this->OnOpenCallback(ec);
}

void MockPhysicalLayerAsync::SignalOpenFailure()
{
	error_code ec(errc::permission_denied, get_generic_category());
	this->OnOpenCallback(ec);
}

void MockPhysicalLayerAsync::SignalSendSuccess()
{
	size_t num = mNumToWrite; mNumToWrite = 0;
	error_code ec(errc::success, get_generic_category());
	this->OnWriteCallback(ec, num);
}

void MockPhysicalLayerAsync::SignalSendFailure()
{
	mNumToWrite = 0;
	error_code ec(errc::permission_denied, get_generic_category());
	this->OnWriteCallback(ec, 0);
}

void MockPhysicalLayerAsync::SignalReadFailure()
{
	mNumToRead = 0;
	error_code ec(errc::permission_denied, get_generic_category());
	this->OnReadCallback(ec, mpWriteBuff, 0);
}

void MockPhysicalLayerAsync::TriggerRead(const std::string& arData)
{
	HexSequence hs(arData);
	assert(hs.Size() <= this->mNumToRead);
	memcpy(mpWriteBuff, hs.Buffer(), hs.Size());
	mNumToRead = 0;
	error_code ec(errc::success, get_generic_category());
	this->OnReadCallback(ec, mpWriteBuff, hs.Size());
}

void MockPhysicalLayerAsync::TriggerClose()
{
	error_code ec(errc::connection_aborted, get_generic_category());
	this->OnReadCallback(ec, mpWriteBuff, 0);
}


}
