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
#include "PhysicalLayerWrapper.h"

#include <opendnp3/APL/Logger.h>

namespace apl
{


PhysicalLayerWrapper::PhysicalLayerWrapper(Logger* apLogger, IPhysicalLayerAsync* apProxy) :
	Loggable(apLogger),
	IHandlerAsync(apLogger),
	mCorruptionProbability(-1.0),
	mpProxy(apProxy),
	mpHandler(NULL)
{
	mpProxy->SetHandler(this);
}

void PhysicalLayerWrapper::SetHandler(IHandlerAsync* apHandler)
{
	assert(apHandler != NULL);
	assert(mpHandler == NULL);
	mpHandler = apHandler;
}

void PhysicalLayerWrapper::AsyncOpen()
{
	return mpProxy->AsyncOpen();
}

void PhysicalLayerWrapper::AsyncClose()
{
	return mpProxy->AsyncClose();
}

void PhysicalLayerWrapper::AsyncWrite(const boost::uint8_t* apData, size_t apSize)
{
	return mpProxy->AsyncWrite(apData, apSize);
}

void PhysicalLayerWrapper::AsyncRead(boost::uint8_t* apData, size_t apSize)
{
	return mpProxy->AsyncRead(apData, apSize);
}

void PhysicalLayerWrapper::_OnLowerLayerUp()
{
	if(mpHandler) mpHandler->OnLowerLayerUp();
}

void PhysicalLayerWrapper::_OnLowerLayerDown()
{
	if(mpHandler) mpHandler->OnLowerLayerDown();
}

void PhysicalLayerWrapper::_OnReceive(const boost::uint8_t* apData, size_t aSize)
{
	if(mCorruptionProbability > mRandom.Next()) {
		LOG_BLOCK(LEV_INFO, "Corrupting data");
		boost::uint8_t* pData = const_cast<boost::uint8_t*>(apData);
		for(size_t i = 0; i < aSize; ++i) pData[i] = 0;
	}

	if(mpHandler) mpHandler->OnReceive(apData, aSize);
}

void PhysicalLayerWrapper::_OnSendSuccess()
{
	if(mpHandler) mpHandler->OnSendSuccess();
}

void PhysicalLayerWrapper::_OnSendFailure()
{
	if(mpHandler) mpHandler->OnSendFailure();
}

void PhysicalLayerWrapper::_OnOpenFailure()
{
	if(mpHandler) mpHandler->OnOpenFailure();
}

void PhysicalLayerWrapper::SetCorruptionProbability(double aProbability)
{
	mCorruptionProbability = aProbability;
}

}
