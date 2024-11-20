/**
Copyright 2021 ApiGear UG
Copyright 2021 Epic Games, Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#pragma once

#include "Generated/OLink/Testbed1StructArrayInterfaceOLinkClient.h"
#include "Testbed1TestsCommon.h"
#include "Testbed1StructArrayInterfaceOLinkFixture.h"

#if WITH_DEV_AUTOMATION_TESTS

BEGIN_DEFINE_SPEC(UTestbed1StructArrayInterfaceOLinkSpec, "Testbed1.StructArrayInterface.OLink", Testbed1TestFilterMask);

TUniquePtr<FTestbed1StructArrayInterfaceOLinkFixture> ImplFixture;

// signal callbacks for testing
void PropBoolPropertyCb(const TArray<FTestbed1StructBool>& PropBool);
void PropIntPropertyCb(const TArray<FTestbed1StructInt>& PropInt);
void PropFloatPropertyCb(const TArray<FTestbed1StructFloat>& PropFloat);
void PropStringPropertyCb(const TArray<FTestbed1StructString>& PropString);
void SigBoolSignalCb(const TArray<FTestbed1StructBool>& ParamBool);
void SigIntSignalCb(const TArray<FTestbed1StructInt>& ParamInt);
void SigFloatSignalCb(const TArray<FTestbed1StructFloat>& ParamFloat);
void SigStringSignalCb(const TArray<FTestbed1StructString>& ParamString);
void _SubscriptionStatusChangedCb(bool bSubscribed);
FDoneDelegate testDoneDelegate;

friend class UTestbed1StructArrayInterfaceOLinkHelper;
END_DEFINE_SPEC(UTestbed1StructArrayInterfaceOLinkSpec);

#endif // WITH_DEV_AUTOMATION_TESTS
