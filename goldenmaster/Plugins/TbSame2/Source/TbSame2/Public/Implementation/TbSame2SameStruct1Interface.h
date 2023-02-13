
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

#include "CoreMinimal.h"
#include "Generated/api/TbSame2SameStruct1InterfaceInterface.h"
#include "TbSame2SameStruct1Interface.generated.h"

UCLASS(BlueprintType, Blueprintable)
class TBSAME2_API UTbSame2SameStruct1Interface : public UObject, public ITbSame2SameStruct1InterfaceInterface
{
	GENERATED_BODY()
public:
	virtual ~UTbSame2SameStruct1Interface();

	// signals
	UPROPERTY(BlueprintAssignable, Category = "ApiGear|TbSame2|SameStruct1Interface", DisplayName = "Sig1 Signal")
	FTbSame2SameStruct1InterfaceSig1Delegate Sig1Signal;
	FTbSame2SameStruct1InterfaceSig1Delegate& GetSig1SignalDelegate() override;

	UPROPERTY(BlueprintAssignable, Category = "ApiGear|TbSame2|SameStruct1Interface", DisplayName = "Prop1 Changed")
	FTbSame2SameStruct1InterfaceProp1ChangedDelegate Prop1Changed;
	FTbSame2SameStruct1InterfaceProp1ChangedDelegate& GetProp1ChangedDelegate() override;

	// properties
	FTbSame2Struct1 GetProp1_Implementation() const override;
	void SetProp1_Implementation(const FTbSame2Struct1& Prop1) override;

	// operations
	void Func1Async_Implementation(UObject* WorldContextObject, FLatentActionInfo LatentInfo, FTbSame2Struct1& Result, const FTbSame2Struct1& Param1) override{};
	FTbSame2Struct1 Func1_Implementation(const FTbSame2Struct1& Param1) override;

protected:
	// signals
	void BroadcastSig1_Implementation(const FTbSame2Struct1& Param1) override;

	void BroadcastProp1Changed_Implementation(const FTbSame2Struct1& Prop1) override;

private:
	// properties - local copy - use setter functions to emit changed signals
	FTbSame2Struct1 Prop1{FTbSame2Struct1()};
};
