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

#include "Generated/OLink/TbSame1SameEnum1InterfaceOLinkClient.h"
#include "ApiGearSettings.h"
#include "Async/Async.h"
#include "Generated/api/TbSame1.json.adapter.h"
#include "unrealolink.h"
#include "unrealolinksink.h"
#include "Engine/Engine.h"
#include "ApiGear/Public/ApiGearConnectionManager.h"
#include "Misc/DateTime.h"
THIRD_PARTY_INCLUDES_START
#include "olink/clientnode.h"
#include "olink/iobjectsink.h"
THIRD_PARTY_INCLUDES_END

namespace
{
bool IsTbSame1SameEnum1InterfaceLogEnabled()
{
	UApiGearSettings* settings = GetMutableDefault<UApiGearSettings>();
	return settings->OLINK_EnableDebugLog;
}
} // namespace

/**
   \brief data structure to hold the last sent property values
*/
struct TbSame1SameEnum1InterfacePropertiesData
{
	ETbSame1Enum1 Prop1{ETbSame1Enum1::TSE_VALUE1};
};

UTbSame1SameEnum1InterfaceOLinkClient::UTbSame1SameEnum1InterfaceOLinkClient()
	: UAbstractTbSame1SameEnum1Interface()
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION < 27)
	, _SentData(MakeUnique<TbSame1SameEnum1InterfacePropertiesData>())
#else
	, _SentData(MakePimpl<TbSame1SameEnum1InterfacePropertiesData>())
#endif
{
	m_sink = std::make_shared<FUnrealOLinkSink>("tb.same1.SameEnum1Interface");
}

UTbSame1SameEnum1InterfaceOLinkClient::UTbSame1SameEnum1InterfaceOLinkClient(FVTableHelper& Helper)
	: Super(Helper)
{
}
UTbSame1SameEnum1InterfaceOLinkClient::~UTbSame1SameEnum1InterfaceOLinkClient() = default;

void UTbSame1SameEnum1InterfaceOLinkClient::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (GEngine != nullptr)
	{
		UApiGearConnectionManager* AGCM = GEngine->GetEngineSubsystem<UApiGearConnectionManager>();
		AGCM->GetOLinkConnection()->Connect();
		AGCM->GetOLinkConnection()->node()->registry().addSink(m_sink);
		AGCM->GetOLinkConnection()->linkObjectSource(m_sink->olinkObjectName());
	}

	FUnrealOLinkSink::FPropertyChangedFunc PropertyChangedFunc = [this](const nlohmann::json& props)
	{
		this->applyState(props);
	};
	m_sink->setOnPropertyChangedCallback(PropertyChangedFunc);

	FUnrealOLinkSink::FSignalEmittedFunc SignalEmittedFunc = [this](const std::string& signalName, const nlohmann::json& args)
	{
		this->emitSignal(signalName, args);
	};
	m_sink->setOnSignalEmittedCallback(SignalEmittedFunc);
}

void UTbSame1SameEnum1InterfaceOLinkClient::Deinitialize()
{
	// tell the sink that we are gone and should not try to be invoked
	m_sink->resetOnPropertyChangedCallback();
	m_sink->resetOnSignalEmittedCallback();

	if (GEngine != nullptr)
	{
		UApiGearConnectionManager* AGCM = GEngine->GetEngineSubsystem<UApiGearConnectionManager>();
		AGCM->GetOLinkConnection()->unlinkObjectSource(m_sink->olinkObjectName());
		AGCM->GetOLinkConnection()->node()->registry().removeSink(m_sink->olinkObjectName());
	}

	Super::Deinitialize();
}

ETbSame1Enum1 UTbSame1SameEnum1InterfaceOLinkClient::GetProp1_Implementation() const
{
	return Prop1;
}

void UTbSame1SameEnum1InterfaceOLinkClient::SetProp1_Implementation(ETbSame1Enum1 InProp1)
{
	if (!m_sink->IsReady())
	{
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetProp1_Implementation() == InProp1)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	if (_SentData->Prop1 == InProp1)
	{
		return;
	}
	m_sink->GetNode()->setRemoteProperty(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "prop1"), InProp1);
	_SentData->Prop1 = InProp1;
}

ETbSame1Enum1 UTbSame1SameEnum1InterfaceOLinkClient::Func1_Implementation(ETbSame1Enum1 Param1)
{
	if (!m_sink->IsReady())
	{
		if (IsTbSame1SameEnum1InterfaceLogEnabled())
		{
			UE_LOG(LogTemp, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		}

		return ETbSame1Enum1::TSE_VALUE1;
	}
	TPromise<ETbSame1Enum1> Promise;
	Async(EAsyncExecution::Thread,
		[Param1, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetSameEnum1InterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{ Promise.SetValue(arg.value.get<ETbSame1Enum1>()); };
			m_sink->GetNode()->invokeRemote(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "func1"), {Param1}, GetSameEnum1InterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

void UTbSame1SameEnum1InterfaceOLinkClient::applyState(const nlohmann::json& fields)
{
	const bool bProp1Changed = fields.contains("prop1") && (Prop1 != fields["prop1"].get<ETbSame1Enum1>());
	if (bProp1Changed)
	{
		Prop1 = fields["prop1"].get<ETbSame1Enum1>();
		Execute_BroadcastProp1Changed(this, Prop1);
	}
}

void UTbSame1SameEnum1InterfaceOLinkClient::emitSignal(const std::string& signalName, const nlohmann::json& args)
{
	if (signalName == "sig1")
	{
		ETbSame1Enum1 Param1 = args[0].get<ETbSame1Enum1>();
		Execute_BroadcastSig1(this, Param1);
		return;
	}
}
