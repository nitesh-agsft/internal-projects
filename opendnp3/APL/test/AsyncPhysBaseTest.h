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
#ifndef __ASYNC_PHYS_BASE_TEST_H_
#define __ASYNC_PHYS_BASE_TEST_H_

#include <opendnp3/APL/LowerLayerToPhysAdapter.h>

#include <opendnp3/APL/test/util/LogTester.h>
#include <opendnp3/APL/test/util/MockUpperLayer.h>
#include <opendnp3/APL/test/util/MockPhysicalLayerAsync.h>

namespace apl
{

class AsyncPhysBaseTest : public LogTester
{
public:
	AsyncPhysBaseTest(FilterLevel aLevel = LEV_INFO, bool aImmediate = false);

	MockPhysicalLayerAsync phys;
	LowerLayerToPhysAdapter adapter;
	MockUpperLayer upper;
};

}

#endif
