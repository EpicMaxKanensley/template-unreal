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

#include "Generated/OLink/Testbed2ManyParamInterfaceOLinkAdapter.h"
#include "Async/Future.h"
#include "Async/Async.h"
#include "Generated/api/Testbed2.json.adapter.h"
#include "unrealolink.h"
#include "Async/Async.h"
#include "Engine/Engine.h"
#include "Misc/DateTime.h"
THIRD_PARTY_INCLUDES_START
#include "olink/iobjectsource.h"
THIRD_PARTY_INCLUDES_END
#include "Testbed2ManyParamInterfaceOLinkSource.h"

using namespace ApiGear::ObjectLink;
UTestbed2ManyParamInterfaceOLinkAdapter::UTestbed2ManyParamInterfaceOLinkAdapter()
	: Source(std::make_shared<Testbed2ManyParamInterfaceOLinkSource>())
{
}

void UTestbed2ManyParamInterfaceOLinkAdapter::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UTestbed2ManyParamInterfaceOLinkAdapter::Deinitialize()
{
	Super::Deinitialize();
}

void UTestbed2ManyParamInterfaceOLinkAdapter::setBackendService(TScriptInterface<ITestbed2ManyParamInterfaceInterface> InService)
{
	// unsubscribe from old backend
	if (BackendService != nullptr)
	{
		BackendService->GetProp1ChangedDelegate().RemoveDynamic(this, &UTestbed2ManyParamInterfaceOLinkAdapter::OnProp1Changed);
		BackendService->GetProp2ChangedDelegate().RemoveDynamic(this, &UTestbed2ManyParamInterfaceOLinkAdapter::OnProp2Changed);
		BackendService->GetProp3ChangedDelegate().RemoveDynamic(this, &UTestbed2ManyParamInterfaceOLinkAdapter::OnProp3Changed);
		BackendService->GetProp4ChangedDelegate().RemoveDynamic(this, &UTestbed2ManyParamInterfaceOLinkAdapter::OnProp4Changed);
		BackendService->GetSig1SignalDelegate().RemoveDynamic(this, &UTestbed2ManyParamInterfaceOLinkAdapter::OnSig1);
		BackendService->GetSig2SignalDelegate().RemoveDynamic(this, &UTestbed2ManyParamInterfaceOLinkAdapter::OnSig2);
		BackendService->GetSig3SignalDelegate().RemoveDynamic(this, &UTestbed2ManyParamInterfaceOLinkAdapter::OnSig3);
		BackendService->GetSig4SignalDelegate().RemoveDynamic(this, &UTestbed2ManyParamInterfaceOLinkAdapter::OnSig4);
	}

	// only set if interface is implemented
	checkf(InService.GetInterface() != nullptr, TEXT("Cannot set backend service - interface HmiFrontDisplay is not fully implemented"));

	// subscribe to new backend
	BackendService = InService;
	// connect property changed signals or simple events
	BackendService->GetProp1ChangedDelegate().AddDynamic(this, &UTestbed2ManyParamInterfaceOLinkAdapter::OnProp1Changed);
	BackendService->GetProp2ChangedDelegate().AddDynamic(this, &UTestbed2ManyParamInterfaceOLinkAdapter::OnProp2Changed);
	BackendService->GetProp3ChangedDelegate().AddDynamic(this, &UTestbed2ManyParamInterfaceOLinkAdapter::OnProp3Changed);
	BackendService->GetProp4ChangedDelegate().AddDynamic(this, &UTestbed2ManyParamInterfaceOLinkAdapter::OnProp4Changed);
	BackendService->GetSig1SignalDelegate().AddDynamic(this, &UTestbed2ManyParamInterfaceOLinkAdapter::OnSig1);
	BackendService->GetSig2SignalDelegate().AddDynamic(this, &UTestbed2ManyParamInterfaceOLinkAdapter::OnSig2);
	BackendService->GetSig3SignalDelegate().AddDynamic(this, &UTestbed2ManyParamInterfaceOLinkAdapter::OnSig3);
	BackendService->GetSig4SignalDelegate().AddDynamic(this, &UTestbed2ManyParamInterfaceOLinkAdapter::OnSig4);

	// update olink source with new backend
	Source->setBackendService(InService);
}

void UTestbed2ManyParamInterfaceOLinkAdapter::OnSig1(int32 Param1)
{
	Source->OnSig1(Param1);
}

void UTestbed2ManyParamInterfaceOLinkAdapter::OnSig2(int32 Param1, int32 Param2)
{
	Source->OnSig2(Param1, Param2);
}

void UTestbed2ManyParamInterfaceOLinkAdapter::OnSig3(int32 Param1, int32 Param2, int32 Param3)
{
	Source->OnSig3(Param1, Param2, Param3);
}

void UTestbed2ManyParamInterfaceOLinkAdapter::OnSig4(int32 Param1, int32 Param2, int32 Param3, int32 Param4)
{
	Source->OnSig4(Param1, Param2, Param3, Param4);
}

void UTestbed2ManyParamInterfaceOLinkAdapter::OnProp1Changed(int32 InProp1)
{
	Source->OnProp1Changed(InProp1);
}

void UTestbed2ManyParamInterfaceOLinkAdapter::OnProp2Changed(int32 InProp2)
{
	Source->OnProp2Changed(InProp2);
}

void UTestbed2ManyParamInterfaceOLinkAdapter::OnProp3Changed(int32 InProp3)
{
	Source->OnProp3Changed(InProp3);
}

void UTestbed2ManyParamInterfaceOLinkAdapter::OnProp4Changed(int32 InProp4)
{
	Source->OnProp4Changed(InProp4);
}

void UTestbed2ManyParamInterfaceOLinkAdapter::setOLinkHost(TSoftObjectPtr<UUnrealOLinkHost> InHost)
{
	check(InHost);
	Source->setOLinkHost(InHost.Get());

	// register source to host
	InHost->GetOLinkRegistry()->addSource(Source);
}
