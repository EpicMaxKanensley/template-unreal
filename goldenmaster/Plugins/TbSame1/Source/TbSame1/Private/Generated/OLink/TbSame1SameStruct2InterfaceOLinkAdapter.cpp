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

////////////////////////////////
// WARNING AUTOGENERATED
// DO NOT MODIFY
///////////////////////////////

#include "Generated/OLink/TbSame1SameStruct2InterfaceOLinkAdapter.h"
#include "Async/Future.h"
#include "Async/Async.h"
#include "Generated/api/TbSame1.json.adapter.h"
#include "unrealolink.h"
#include "Async/Async.h"
#include "Engine/Engine.h"
#include "Misc/DateTime.h"
THIRD_PARTY_INCLUDES_START
#include "olink/iobjectsource.h"
THIRD_PARTY_INCLUDES_END
#include "TbSame1SameStruct2InterfaceOLinkSource.h"

using namespace ApiGear::ObjectLink;
UTbSame1SameStruct2InterfaceOLinkAdapter::UTbSame1SameStruct2InterfaceOLinkAdapter()
	: Source(std::make_shared<TbSame1SameStruct2InterfaceOLinkSource>())
{
}

void UTbSame1SameStruct2InterfaceOLinkAdapter::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UTbSame1SameStruct2InterfaceOLinkAdapter::Deinitialize()
{
	Super::Deinitialize();
}

void UTbSame1SameStruct2InterfaceOLinkAdapter::setBackendService(TScriptInterface<ITbSame1SameStruct2InterfaceInterface> InService)
{
	// unsubscribe from old backend
	if (BackendService != nullptr)
	{
		UTbSame1SameStruct2InterfaceSignals* BackendSignals = BackendService->Execute__GetSignals(BackendService.GetObject());
		checkf(BackendSignals, TEXT("Cannot unsubscribe from delegates from backend service TbSame1SameStruct2Interface"));
		BackendSignals->OnProp1Changed.RemoveDynamic(this, &UTbSame1SameStruct2InterfaceOLinkAdapter::OnProp1Changed);
		BackendSignals->OnProp2Changed.RemoveDynamic(this, &UTbSame1SameStruct2InterfaceOLinkAdapter::OnProp2Changed);
		BackendSignals->OnSig1Signal.RemoveDynamic(this, &UTbSame1SameStruct2InterfaceOLinkAdapter::OnSig1);
		BackendSignals->OnSig2Signal.RemoveDynamic(this, &UTbSame1SameStruct2InterfaceOLinkAdapter::OnSig2);
	}

	// only set if interface is implemented
	checkf(InService.GetInterface() != nullptr, TEXT("Cannot set backend service - interface TbSame1SameStruct2Interface is not fully implemented"));

	// subscribe to new backend
	BackendService = InService;
	UTbSame1SameStruct2InterfaceSignals* BackendSignals = BackendService->Execute__GetSignals(BackendService.GetObject());
	checkf(BackendSignals, TEXT("Cannot unsubscribe from delegates from backend service TbSame1SameStruct2Interface"));
	// connect property changed signals or simple events
	BackendSignals->OnProp1Changed.AddDynamic(this, &UTbSame1SameStruct2InterfaceOLinkAdapter::OnProp1Changed);
	BackendSignals->OnProp2Changed.AddDynamic(this, &UTbSame1SameStruct2InterfaceOLinkAdapter::OnProp2Changed);
	BackendSignals->OnSig1Signal.AddDynamic(this, &UTbSame1SameStruct2InterfaceOLinkAdapter::OnSig1);
	BackendSignals->OnSig2Signal.AddDynamic(this, &UTbSame1SameStruct2InterfaceOLinkAdapter::OnSig2);

	// update olink source with new backend
	Source->setBackendService(InService);
}

void UTbSame1SameStruct2InterfaceOLinkAdapter::OnSig1(const FTbSame1Struct1& Param1)
{
	Source->OnSig1(Param1);
}

void UTbSame1SameStruct2InterfaceOLinkAdapter::OnSig2(const FTbSame1Struct1& Param1, const FTbSame1Struct2& Param2)
{
	Source->OnSig2(Param1, Param2);
}

void UTbSame1SameStruct2InterfaceOLinkAdapter::OnProp1Changed(const FTbSame1Struct2& InProp1)
{
	Source->OnProp1Changed(InProp1);
}

void UTbSame1SameStruct2InterfaceOLinkAdapter::OnProp2Changed(const FTbSame1Struct2& InProp2)
{
	Source->OnProp2Changed(InProp2);
}

void UTbSame1SameStruct2InterfaceOLinkAdapter::setOLinkHost(TSoftObjectPtr<UUnrealOLinkHost> InHost)
{
	check(InHost);
	Source->setOLinkHost(InHost.Get());

	if (Registry)
	{
		Registry->removeSource(Source->olinkObjectName());
	}
	Registry = InHost->GetOLinkRegistry();
	// register source to host registry
	Registry->addSource(Source);
}
