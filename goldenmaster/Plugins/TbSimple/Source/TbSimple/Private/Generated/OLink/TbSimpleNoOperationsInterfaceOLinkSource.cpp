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

#include "TbSimpleNoOperationsInterfaceOLinkSource.h"
#include "Async/Future.h"
#include "Async/Async.h"
#include "Generated/api/TbSimple.json.adapter.h"
#include "OLinkClientConnection.h"
#include "Async/Async.h"
#include "Engine/Engine.h"
#include "Misc/DateTime.h"
THIRD_PARTY_INCLUDES_START
#include "olink/iobjectsource.h"
THIRD_PARTY_INCLUDES_END

using namespace ApiGear::ObjectLink;

namespace
{
static const std::string TbSimpleNoOperationsInterfaceIdentifier{"tb.simple.NoOperationsInterface"};
}

DEFINE_LOG_CATEGORY(LogTbSimpleNoOperationsInterfaceOLinkSource);
TbSimpleNoOperationsInterfaceOLinkSource::TbSimpleNoOperationsInterfaceOLinkSource()
	: Host(nullptr)
{
}

void TbSimpleNoOperationsInterfaceOLinkSource::setBackendService(TScriptInterface<ITbSimpleNoOperationsInterfaceInterface> InService)
{
	// only set if interface is implemented
	if (InService.GetInterface() == nullptr)
	{
		UE_LOG(LogTbSimpleNoOperationsInterfaceOLinkSource, Error, TEXT("Cannot set backend service to %s - interface TbSimpleNoOperationsInterface is not fully implemented"), *InService.GetObject()->GetName());
		return;
	}

	BackendService = InService;
}
void TbSimpleNoOperationsInterfaceOLinkSource::OnSigVoid()
{
	static const auto& signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sigVoid");
	static const auto& objectId = ApiGear::ObjectLink::Name::getObjectId(signalId);
	const nlohmann::json& args = {};
	for (auto node : Host->GetOLinkRegistry()->getNodes(objectId))
	{
		auto lockedNode = node.lock();
		if (lockedNode)
		{
			lockedNode->notifySignal(signalId, args);
		}
	}
}

void TbSimpleNoOperationsInterfaceOLinkSource::OnSigBool(bool bParamBool)
{
	static const auto& signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sigBool");
	static const auto& objectId = ApiGear::ObjectLink::Name::getObjectId(signalId);
	const nlohmann::json& args = {bParamBool};
	for (auto node : Host->GetOLinkRegistry()->getNodes(objectId))
	{
		auto lockedNode = node.lock();
		if (lockedNode)
		{
			lockedNode->notifySignal(signalId, args);
		}
	}
}

void TbSimpleNoOperationsInterfaceOLinkSource::OnPropBoolChanged(bool bInPropBool)
{
	static const auto& propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propBool");
	static const auto& objectId = ApiGear::ObjectLink::Name::getObjectId(propertyId);
	for (auto node : Host->GetOLinkRegistry()->getNodes(objectId))
	{
		auto lockedNode = node.lock();
		if (lockedNode)
		{
			lockedNode->notifyPropertyChange(propertyId, bInPropBool);
		}
	}
}

void TbSimpleNoOperationsInterfaceOLinkSource::OnPropIntChanged(int32 InPropInt)
{
	static const auto& propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "propInt");
	static const auto& objectId = ApiGear::ObjectLink::Name::getObjectId(propertyId);
	for (auto node : Host->GetOLinkRegistry()->getNodes(objectId))
	{
		auto lockedNode = node.lock();
		if (lockedNode)
		{
			lockedNode->notifyPropertyChange(propertyId, InPropInt);
		}
	}
}

void TbSimpleNoOperationsInterfaceOLinkSource::setOLinkHost(TSoftObjectPtr<UOLinkHost> InHost)
{
	Host = InHost.Get();
}

//
// IObjectSource interface
//

std::string TbSimpleNoOperationsInterfaceOLinkSource::olinkObjectName()
{
	return TbSimpleNoOperationsInterfaceIdentifier;
}

nlohmann::json TbSimpleNoOperationsInterfaceOLinkSource::olinkInvoke(const std::string& methodId, const nlohmann::json& args)
{
	if (!BackendService)
	{
		UE_LOG(LogTbSimpleNoOperationsInterfaceOLinkSource, Error, TEXT("No backend service set - please specify a service in the adapter TbSimpleNoOperationsInterfaceOLinkAdapter which implements the TbSimpleNoOperationsInterface interface"));
		return nlohmann::json();
	}

	const std::string path = Name::getMemberName(methodId);
	return nlohmann::json();
}

void TbSimpleNoOperationsInterfaceOLinkSource::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value)
{
	if (!BackendService)
	{
		UE_LOG(LogTbSimpleNoOperationsInterfaceOLinkSource, Error, TEXT("No backend service set - please specify a service in the adapter TbSimpleNoOperationsInterfaceOLinkAdapter which implements the TbSimpleNoOperationsInterface interface"));
		return;
	}

	const std::string path = Name::getMemberName(propertyId);
	if (path == "propBool")
	{
		bool bPropBool = value.get<bool>();
		BackendService->Execute_SetPropBool(BackendService.GetObject(), bPropBool);
	}
	if (path == "propInt")
	{
		int32 PropInt = value.get<int32>();
		BackendService->Execute_SetPropInt(BackendService.GetObject(), PropInt);
	}
}

nlohmann::json TbSimpleNoOperationsInterfaceOLinkSource::olinkCollectProperties()
{
	if (!BackendService)
	{
		UE_LOG(LogTbSimpleNoOperationsInterfaceOLinkSource, Error, TEXT("No backend service set - please specify a service in the adapter TbSimpleNoOperationsInterfaceOLinkAdapter which implements the TbSimpleNoOperationsInterface interface"));
		return nlohmann::json();
	}

	return nlohmann::json::object({

		{"propBool", BackendService->Execute_GetPropBool(BackendService.GetObject())},
		{"propInt", BackendService->Execute_GetPropInt(BackendService.GetObject())}});
}
