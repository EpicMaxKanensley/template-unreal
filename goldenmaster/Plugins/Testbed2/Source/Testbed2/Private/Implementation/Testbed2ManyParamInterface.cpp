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

#include "Implementation/Testbed2ManyParamInterface.h"

UTestbed2ManyParamInterface::~UTestbed2ManyParamInterface() = default;

void UTestbed2ManyParamInterface::BroadcastSig0_Implementation()
{
	Sig0Signal.Broadcast();
}

FTestbed2ManyParamInterfaceSig0Delegate& UTestbed2ManyParamInterface::GetSig0SignalDelegate()
{
	return Sig0Signal;
}

void UTestbed2ManyParamInterface::BroadcastSig1_Implementation(int32 Param1)
{
	Sig1Signal.Broadcast(Param1);
}

FTestbed2ManyParamInterfaceSig1Delegate& UTestbed2ManyParamInterface::GetSig1SignalDelegate()
{
	return Sig1Signal;
}

void UTestbed2ManyParamInterface::BroadcastSig2_Implementation(int32 Param1, int32 Param2)
{
	Sig2Signal.Broadcast(Param1, Param2);
}

FTestbed2ManyParamInterfaceSig2Delegate& UTestbed2ManyParamInterface::GetSig2SignalDelegate()
{
	return Sig2Signal;
}

void UTestbed2ManyParamInterface::BroadcastSig3_Implementation(int32 Param1, int32 Param2, int32 Param3)
{
	Sig3Signal.Broadcast(Param1, Param2, Param3);
}

FTestbed2ManyParamInterfaceSig3Delegate& UTestbed2ManyParamInterface::GetSig3SignalDelegate()
{
	return Sig3Signal;
}

void UTestbed2ManyParamInterface::BroadcastSig4_Implementation(int32 Param1, int32 Param2, int32 Param3, int32 Param4)
{
	Sig4Signal.Broadcast(Param1, Param2, Param3, Param4);
}

FTestbed2ManyParamInterfaceSig4Delegate& UTestbed2ManyParamInterface::GetSig4SignalDelegate()
{
	return Sig4Signal;
}

void UTestbed2ManyParamInterface::BroadcastProp1Changed_Implementation(int32 InProp1)
{
	Prop1Changed.Broadcast(InProp1);
}

int32 UTestbed2ManyParamInterface::GetProp1_Implementation() const
{
	return Prop1;
}

void UTestbed2ManyParamInterface::SetProp1_Implementation(int32 InProp1)
{
	if (Prop1 != InProp1)
	{
		Prop1 = InProp1;
		Execute_BroadcastProp1Changed(this, Prop1);
	}
}

FTestbed2ManyParamInterfaceProp1ChangedDelegate& UTestbed2ManyParamInterface::GetProp1ChangedDelegate()
{
	return Prop1Changed;
}

void UTestbed2ManyParamInterface::BroadcastProp2Changed_Implementation(int32 InProp2)
{
	Prop2Changed.Broadcast(InProp2);
}

int32 UTestbed2ManyParamInterface::GetProp2_Implementation() const
{
	return Prop2;
}

void UTestbed2ManyParamInterface::SetProp2_Implementation(int32 InProp2)
{
	if (Prop2 != InProp2)
	{
		Prop2 = InProp2;
		Execute_BroadcastProp2Changed(this, Prop2);
	}
}

FTestbed2ManyParamInterfaceProp2ChangedDelegate& UTestbed2ManyParamInterface::GetProp2ChangedDelegate()
{
	return Prop2Changed;
}

void UTestbed2ManyParamInterface::BroadcastProp3Changed_Implementation(int32 InProp3)
{
	Prop3Changed.Broadcast(InProp3);
}

int32 UTestbed2ManyParamInterface::GetProp3_Implementation() const
{
	return Prop3;
}

void UTestbed2ManyParamInterface::SetProp3_Implementation(int32 InProp3)
{
	if (Prop3 != InProp3)
	{
		Prop3 = InProp3;
		Execute_BroadcastProp3Changed(this, Prop3);
	}
}

FTestbed2ManyParamInterfaceProp3ChangedDelegate& UTestbed2ManyParamInterface::GetProp3ChangedDelegate()
{
	return Prop3Changed;
}

void UTestbed2ManyParamInterface::BroadcastProp4Changed_Implementation(int32 InProp4)
{
	Prop4Changed.Broadcast(InProp4);
}

int32 UTestbed2ManyParamInterface::GetProp4_Implementation() const
{
	return Prop4;
}

void UTestbed2ManyParamInterface::SetProp4_Implementation(int32 InProp4)
{
	if (Prop4 != InProp4)
	{
		Prop4 = InProp4;
		Execute_BroadcastProp4Changed(this, Prop4);
	}
}

FTestbed2ManyParamInterfaceProp4ChangedDelegate& UTestbed2ManyParamInterface::GetProp4ChangedDelegate()
{
	return Prop4Changed;
}

void UTestbed2ManyParamInterface::Func0_Implementation()
{
	// do business logic here
}

int32 UTestbed2ManyParamInterface::Func1_Implementation(int32 Param1)
{
	(void)Param1;
	// do business logic here
	return 0;
}

int32 UTestbed2ManyParamInterface::Func2_Implementation(int32 Param1, int32 Param2)
{
	(void)Param1;
	(void)Param2;
	// do business logic here
	return 0;
}

int32 UTestbed2ManyParamInterface::Func3_Implementation(int32 Param1, int32 Param2, int32 Param3)
{
	(void)Param1;
	(void)Param2;
	(void)Param3;
	// do business logic here
	return 0;
}

int32 UTestbed2ManyParamInterface::Func4_Implementation(int32 Param1, int32 Param2, int32 Param3, int32 Param4)
{
	(void)Param1;
	(void)Param2;
	(void)Param3;
	(void)Param4;
	// do business logic here
	return 0;
}

void UTestbed2ManyParamInterface::Func5_Implementation(int32 Param1, int32 Param2, int32 Param3, int32 Param4, int32 Param5)
{
	(void)Param1;
	(void)Param2;
	(void)Param3;
	(void)Param4;
	(void)Param5;
	// do business logic here
}
