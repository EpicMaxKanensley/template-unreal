
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
#include "Subsystems/GameInstanceSubsystem.h"
#include "TbSame1SameEnum2InterfaceInterface.h"
#include "TbSame1SameEnum2InterfaceLoggingDecorator.generated.h"

// General Log
DECLARE_LOG_CATEGORY_EXTERN(LogTbSame1SameEnum2InterfaceLoggingDecorator, Log, All);

UCLASS(BlueprintType, Blueprintable)
class TBSAME1_API UTbSame1SameEnum2InterfaceLoggingDecorator : public UGameInstanceSubsystem, public ITbSame1SameEnum2InterfaceInterface
{
	GENERATED_BODY()

public:
	explicit UTbSame1SameEnum2InterfaceLoggingDecorator();
	virtual ~UTbSame1SameEnum2InterfaceLoggingDecorator();

	UFUNCTION(BlueprintCallable, Category = "ApiGear|TbSame1|SameEnum2Interface")
	void setBackendService(TScriptInterface<ITbSame1SameEnum2InterfaceInterface> InService);

	// subsystem
	void Initialize(FSubsystemCollectionBase& Collection) override;
	void Deinitialize() override;

	// signals
	UPROPERTY(BlueprintAssignable, Category = "ApiGear|TbSame1|SameEnum2Interface", DisplayName = "Sig1 Signal")
	FTbSame1SameEnum2InterfaceSig1Delegate Sig1Signal;
	FTbSame1SameEnum2InterfaceSig1Delegate& GetSig1SignalDelegate() override;

	UPROPERTY(BlueprintAssignable, Category = "ApiGear|TbSame1|SameEnum2Interface", DisplayName = "Sig2 Signal")
	FTbSame1SameEnum2InterfaceSig2Delegate Sig2Signal;
	FTbSame1SameEnum2InterfaceSig2Delegate& GetSig2SignalDelegate() override;

	UPROPERTY(BlueprintAssignable, Category = "ApiGear|TbSame1|SameEnum2Interface", DisplayName = "Prop1 Changed")
	FTbSame1SameEnum2InterfaceProp1ChangedDelegate Prop1Changed;
	FTbSame1SameEnum2InterfaceProp1ChangedDelegate& GetProp1ChangedDelegate() override;

	UPROPERTY(BlueprintAssignable, Category = "ApiGear|TbSame1|SameEnum2Interface", DisplayName = "Prop2 Changed")
	FTbSame1SameEnum2InterfaceProp2ChangedDelegate Prop2Changed;
	FTbSame1SameEnum2InterfaceProp2ChangedDelegate& GetProp2ChangedDelegate() override;

	// properties
	ETbSame1Enum1 GetProp1_Implementation() const override;

	void SetProp1_Implementation(ETbSame1Enum1 InProp1) override;

	ETbSame1Enum2 GetProp2_Implementation() const override;

	void SetProp2_Implementation(ETbSame1Enum2 InProp2) override;

	// operations
	void Func1Async_Implementation(UObject* WorldContextObject, FLatentActionInfo LatentInfo, ETbSame1Enum1& Result, ETbSame1Enum1 Param1) override;
	ETbSame1Enum1 Func1_Implementation(ETbSame1Enum1 Param1) override;

	void Func2Async_Implementation(UObject* WorldContextObject, FLatentActionInfo LatentInfo, ETbSame1Enum1& Result, ETbSame1Enum1 Param1, ETbSame1Enum2 Param2) override;
	ETbSame1Enum1 Func2_Implementation(ETbSame1Enum1 Param1, ETbSame1Enum2 Param2) override;

protected:
	// signals
	void BroadcastSig1_Implementation(ETbSame1Enum1 Param1) override;

	void BroadcastSig2_Implementation(ETbSame1Enum1 Param1, ETbSame1Enum2 Param2) override;

	void BroadcastProp1Changed_Implementation(ETbSame1Enum1 Prop1) override;

	void BroadcastProp2Changed_Implementation(ETbSame1Enum2 Prop2) override;

private:
	/** The connection to the service backend. */
	UPROPERTY(VisibleAnywhere, Category = "ApiGear|TbSame1|SameEnum2Interface")
	TScriptInterface<ITbSame1SameEnum2InterfaceInterface> BackendService;

	// signals
	UFUNCTION(Category = "ApiGear|TbSame1|SameEnum2Interface", BlueprintInternalUseOnly)
	void OnSig1(ETbSame1Enum1 Param1);

	UFUNCTION(Category = "ApiGear|TbSame1|SameEnum2Interface", BlueprintInternalUseOnly)
	void OnSig2(ETbSame1Enum1 Param1, ETbSame1Enum2 Param2);

	UFUNCTION(Category = "ApiGear|TbSame1|SameEnum2Interface", BlueprintInternalUseOnly)
	void OnProp1Changed(ETbSame1Enum1 Prop1);

	UFUNCTION(Category = "ApiGear|TbSame1|SameEnum2Interface", BlueprintInternalUseOnly)
	void OnProp2Changed(ETbSame1Enum2 Prop2);

	// properties - local copy
	UPROPERTY(EditAnywhere, BlueprintGetter = GetProp1_Private, BlueprintSetter = SetProp1_Private, Category = "ApiGear|TbSame1|SameEnum2Interface")
	ETbSame1Enum1 Prop1{ETbSame1Enum1::TSE_VALUE1};

	UFUNCTION(BlueprintGetter, Category = "ApiGear|TbSame1|SameEnum2Interface", BlueprintInternalUseOnly)
	ETbSame1Enum1 GetProp1_Private() const;

	UFUNCTION(BlueprintSetter, Category = "ApiGear|TbSame1|SameEnum2Interface", BlueprintInternalUseOnly)
	void SetProp1_Private(ETbSame1Enum1 InProp1);

	UPROPERTY(EditAnywhere, BlueprintGetter = GetProp2_Private, BlueprintSetter = SetProp2_Private, Category = "ApiGear|TbSame1|SameEnum2Interface")
	ETbSame1Enum2 Prop2{ETbSame1Enum2::TSE_VALUE1};

	UFUNCTION(BlueprintGetter, Category = "ApiGear|TbSame1|SameEnum2Interface", BlueprintInternalUseOnly)
	ETbSame1Enum2 GetProp2_Private() const;

	UFUNCTION(BlueprintSetter, Category = "ApiGear|TbSame1|SameEnum2Interface", BlueprintInternalUseOnly)
	void SetProp2_Private(ETbSame1Enum2 InProp2);
};
