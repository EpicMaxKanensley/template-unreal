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

#include "Testbed2NestedStruct3InterfaceOLinkSource.h"
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

using namespace ApiGear::ObjectLink;

namespace
{
static const std::string Testbed2NestedStruct3InterfaceIdentifier{"testbed2.NestedStruct3Interface"};
}
Testbed2NestedStruct3InterfaceOLinkSource::Testbed2NestedStruct3InterfaceOLinkSource()
	: Host(nullptr)
{
}

void Testbed2NestedStruct3InterfaceOLinkSource::setBackendService(TScriptInterface<ITestbed2NestedStruct3InterfaceInterface> InService)
{
	// only set if interface is implemented
	if (InService.GetInterface() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot set backend service to %s - interface Testbed2NestedStruct3Interface is not fully implemented"), *InService.GetObject()->GetName());
		return;
	}

	// set to new backend
	BackendService = InService;
}
void Testbed2NestedStruct3InterfaceOLinkSource::OnSig1(const FTestbed2NestedStruct1& Param1)
{
	static const auto& signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sig1");
	static const auto& objectId = ApiGear::ObjectLink::Name::getObjectId(signalId);
	const nlohmann::json& args = {Param1};
	for (auto node : Host->GetOLinkRegistry()->getNodes(objectId))
	{
		auto lockedNode = node.lock();
		if (lockedNode)
		{
			lockedNode->notifySignal(signalId, args);
		}
	}
}

void Testbed2NestedStruct3InterfaceOLinkSource::OnSig2(const FTestbed2NestedStruct1& Param1, const FTestbed2NestedStruct2& Param2)
{
	static const auto& signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sig2");
	static const auto& objectId = ApiGear::ObjectLink::Name::getObjectId(signalId);
	const nlohmann::json& args = {Param1, Param2};
	for (auto node : Host->GetOLinkRegistry()->getNodes(objectId))
	{
		auto lockedNode = node.lock();
		if (lockedNode)
		{
			lockedNode->notifySignal(signalId, args);
		}
	}
}

void Testbed2NestedStruct3InterfaceOLinkSource::OnSig3(const FTestbed2NestedStruct1& Param1, const FTestbed2NestedStruct2& Param2, const FTestbed2NestedStruct3& Param3)
{
	static const auto& signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sig3");
	static const auto& objectId = ApiGear::ObjectLink::Name::getObjectId(signalId);
	const nlohmann::json& args = {Param1, Param2, Param3};
	for (auto node : Host->GetOLinkRegistry()->getNodes(objectId))
	{
		auto lockedNode = node.lock();
		if (lockedNode)
		{
			lockedNode->notifySignal(signalId, args);
		}
	}
}

void Testbed2NestedStruct3InterfaceOLinkSource::OnProp1Changed(const FTestbed2NestedStruct1& InProp1)
{
	static const auto& propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop1");
	static const auto& objectId = ApiGear::ObjectLink::Name::getObjectId(propertyId);
	for (auto node : Host->GetOLinkRegistry()->getNodes(objectId))
	{
		auto lockedNode = node.lock();
		if (lockedNode)
		{
			lockedNode->notifyPropertyChange(propertyId, InProp1);
		}
	}
}

void Testbed2NestedStruct3InterfaceOLinkSource::OnProp2Changed(const FTestbed2NestedStruct2& InProp2)
{
	static const auto& propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop2");
	static const auto& objectId = ApiGear::ObjectLink::Name::getObjectId(propertyId);
	for (auto node : Host->GetOLinkRegistry()->getNodes(objectId))
	{
		auto lockedNode = node.lock();
		if (lockedNode)
		{
			lockedNode->notifyPropertyChange(propertyId, InProp2);
		}
	}
}

void Testbed2NestedStruct3InterfaceOLinkSource::OnProp3Changed(const FTestbed2NestedStruct3& InProp3)
{
	static const auto& propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop3");
	static const auto& objectId = ApiGear::ObjectLink::Name::getObjectId(propertyId);
	for (auto node : Host->GetOLinkRegistry()->getNodes(objectId))
	{
		auto lockedNode = node.lock();
		if (lockedNode)
		{
			lockedNode->notifyPropertyChange(propertyId, InProp3);
		}
	}
}

void Testbed2NestedStruct3InterfaceOLinkSource::setOLinkHost(TSoftObjectPtr<UUnrealOLinkHost> InHost)
{
	Host = InHost.Get();
}

//
// IObjectSource interface
//

std::string Testbed2NestedStruct3InterfaceOLinkSource::olinkObjectName()
{
	return Testbed2NestedStruct3InterfaceIdentifier;
}

nlohmann::json Testbed2NestedStruct3InterfaceOLinkSource::olinkInvoke(const std::string& methodId, const nlohmann::json& args)
{
	const std::string path = Name::getMemberName(methodId);
	if (path == "func1")
	{
		FTestbed2NestedStruct1 Param1 = args.at(0);
		FTestbed2NestedStruct1 result = BackendService->Execute_Func1(BackendService.GetObject(), Param1);
		return result;
	}
	if (path == "func2")
	{
		FTestbed2NestedStruct1 Param1 = args.at(0);
		FTestbed2NestedStruct2 Param2 = args.at(1);
		FTestbed2NestedStruct1 result = BackendService->Execute_Func2(BackendService.GetObject(), Param1, Param2);
		return result;
	}
	if (path == "func3")
	{
		FTestbed2NestedStruct1 Param1 = args.at(0);
		FTestbed2NestedStruct2 Param2 = args.at(1);
		FTestbed2NestedStruct3 Param3 = args.at(2);
		FTestbed2NestedStruct1 result = BackendService->Execute_Func3(BackendService.GetObject(), Param1, Param2, Param3);
		return result;
	}
	return nlohmann::json();
}

void Testbed2NestedStruct3InterfaceOLinkSource::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value)
{
	const std::string path = Name::getMemberName(propertyId);
	if (path == "prop1")
	{
		FTestbed2NestedStruct1 Prop1 = value.get<FTestbed2NestedStruct1>();
		BackendService->Execute_SetProp1(BackendService.GetObject(), Prop1);
	}
	if (path == "prop2")
	{
		FTestbed2NestedStruct2 Prop2 = value.get<FTestbed2NestedStruct2>();
		BackendService->Execute_SetProp2(BackendService.GetObject(), Prop2);
	}
	if (path == "prop3")
	{
		FTestbed2NestedStruct3 Prop3 = value.get<FTestbed2NestedStruct3>();
		BackendService->Execute_SetProp3(BackendService.GetObject(), Prop3);
	}
}

nlohmann::json Testbed2NestedStruct3InterfaceOLinkSource::olinkCollectProperties()
{
	return nlohmann::json::object({

		{"prop1", BackendService->Execute_GetProp1(BackendService.GetObject())},
		{"prop2", BackendService->Execute_GetProp2(BackendService.GetObject())},
		{"prop3", BackendService->Execute_GetProp3(BackendService.GetObject())}});
}
