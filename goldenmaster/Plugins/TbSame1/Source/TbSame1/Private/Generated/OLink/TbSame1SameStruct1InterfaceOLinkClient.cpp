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

#include "Generated/OLink/TbSame1SameStruct1InterfaceOLinkClient.h"
#include "ApiGearSettings.h"
#include "ApiGearOLink.h"
#include "Async/Async.h"
#include "Generated/api/TbSame1.json.adapter.h"
#include "OLinkClientConnection.h"
#include "OLinkSink.h"
#include "Engine/Engine.h"
#include "ApiGear/Public/ApiGearConnectionsStore.h"
#include "Misc/DateTime.h"
#include "TbSame1Settings.h"
THIRD_PARTY_INCLUDES_START
#include "olink/clientnode.h"
#include "olink/iobjectsink.h"
THIRD_PARTY_INCLUDES_END
#include "HAL/CriticalSection.h"

/**
   \brief data structure to hold the last sent property values
*/
struct TbSame1SameStruct1InterfacePropertiesData
{
	FCriticalSection Prop1Mutex;
	FTbSame1Struct1 Prop1{FTbSame1Struct1()};
};
DEFINE_LOG_CATEGORY(LogTbSame1SameStruct1InterfaceOLinkClient);

UTbSame1SameStruct1InterfaceOLinkClient::UTbSame1SameStruct1InterfaceOLinkClient()
	: UAbstractTbSame1SameStruct1Interface()
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION < 27)
	, _SentData(MakeUnique<TbSame1SameStruct1InterfacePropertiesData>())
#else
	, _SentData(MakePimpl<TbSame1SameStruct1InterfacePropertiesData>())
#endif
{
	m_sink = std::make_shared<FOLinkSink>("tb.same1.SameStruct1Interface");
}

UTbSame1SameStruct1InterfaceOLinkClient::UTbSame1SameStruct1InterfaceOLinkClient(FVTableHelper& Helper)
	: Super(Helper)
{
}
UTbSame1SameStruct1InterfaceOLinkClient::~UTbSame1SameStruct1InterfaceOLinkClient() = default;

void UTbSame1SameStruct1InterfaceOLinkClient::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	m_sink->setOnInitCallback([this]()
		{ _SubscriptionStatusChanged.Broadcast(true); });
	m_sink->setOnReleaseCallback([this]()
		{ _SubscriptionStatusChanged.Broadcast(false); });

	FOLinkSink::FPropertyChangedFunc PropertyChangedFunc = [this](const nlohmann::json& props)
	{
		this->applyState(props);
	};
	m_sink->setOnPropertyChangedCallback(PropertyChangedFunc);

	FOLinkSink::FSignalEmittedFunc SignalEmittedFunc = [this](const std::string& signalName, const nlohmann::json& args)
	{
		this->emitSignal(signalName, args);
	};
	m_sink->setOnSignalEmittedCallback(SignalEmittedFunc);

	check(GEngine);
	UTbSame1Settings* settings = GetMutableDefault<UTbSame1Settings>();

	UApiGearConnectionsStore* AGCM = GEngine->GetEngineSubsystem<UApiGearConnectionsStore>();

	TScriptInterface<IApiGearConnection> OLinkConnection = AGCM->GetConnection(settings->OLinkConnectionIdentifier);

	if (!OLinkConnection.GetInterface())
	{
		UE_LOG(LogTbSame1SameStruct1InterfaceOLinkClient, Warning, TEXT("No valid olink connection for the %s client, please set in the ApiGear TbSame1 plugin settings or during run time"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}
	UseConnection(OLinkConnection);
	OLinkConnection->Connect();
}

void UTbSame1SameStruct1InterfaceOLinkClient::Deinitialize()
{
	// tell the sink that we are gone and should not try to be invoked
	m_sink->resetOnPropertyChangedCallback();
	m_sink->resetOnSignalEmittedCallback();
	m_sink->resetOnInitCallback();
	m_sink->resetOnReleaseCallback();

	if (Connection.GetObject())
	{
		UOLinkClientConnection* UnrealOLinkConnection = Cast<UOLinkClientConnection>(Connection.GetObject());
		UnrealOLinkConnection->unlinkObjectSource(m_sink->olinkObjectName());
		UnrealOLinkConnection->node()->registry().removeSink(m_sink->olinkObjectName());
	}

	Super::Deinitialize();
}

void UTbSame1SameStruct1InterfaceOLinkClient::UseConnection(TScriptInterface<IApiGearConnection> InConnection)
{
	checkf(InConnection.GetInterface() != nullptr, TEXT("Cannot use connection - interface IApiGearConnection is not fully implemented"));

	// only accept connections of type olink
	checkf(InConnection->GetConnectionProtocolIdentifier() == ApiGearOLinkProtocolIdentifier, TEXT("Cannot use connection - must be of type olink"));

	UOLinkClientConnection* UnrealOLinkConnection = nullptr;
	// remove old connection
	if (Connection.GetObject())
	{
		UnrealOLinkConnection = Cast<UOLinkClientConnection>(Connection.GetObject());
		UnrealOLinkConnection->unlinkObjectSource(m_sink->olinkObjectName());
		UnrealOLinkConnection->node()->registry().removeSink(m_sink->olinkObjectName());
		UnrealOLinkConnection = nullptr;
	}

	// set up new connection
	UnrealOLinkConnection = Cast<UOLinkClientConnection>(InConnection.GetObject());
	UnrealOLinkConnection->node()->registry().addSink(m_sink);
	UnrealOLinkConnection->linkObjectSource(m_sink->olinkObjectName());

	Connection = InConnection;
}

FTbSame1Struct1 UTbSame1SameStruct1InterfaceOLinkClient::GetProp1_Implementation() const
{
	return Prop1;
}

void UTbSame1SameStruct1InterfaceOLinkClient::SetProp1_Implementation(const FTbSame1Struct1& InProp1)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSame1SameStruct1InterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetProp1_Implementation() == InProp1)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	{
		FScopeLock Lock(&(_SentData->Prop1Mutex));
		if (_SentData->Prop1 == InProp1)
		{
			return;
		}
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "prop1");
	m_sink->GetNode()->setRemoteProperty(memberId, InProp1);
	FScopeLock Lock(&(_SentData->Prop1Mutex));
	_SentData->Prop1 = InProp1;
}

FTbSame1Struct1 UTbSame1SameStruct1InterfaceOLinkClient::Func1_Implementation(const FTbSame1Struct1& Param1)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSame1SameStruct1InterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return FTbSame1Struct1();
	}
	TPromise<FTbSame1Struct1> Promise;
	Async(EAsyncExecution::Thread,
		[Param1, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetSameStruct1InterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{
				if (!arg.value.empty())
				{
					Promise.SetValue(arg.value.get<FTbSame1Struct1>());
				}
				else
				{
					UE_LOG(LogTbSame1SameStruct1InterfaceOLinkClient, Error, TEXT("Func1: OLink service returned empty value - should have returned type of FTbSame1Struct1"));
					Promise.SetValue(FTbSame1Struct1());
				}
			};
			static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "func1");
			m_sink->GetNode()->invokeRemote(memberId, {Param1}, GetSameStruct1InterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

bool UTbSame1SameStruct1InterfaceOLinkClient::_IsSubscribed() const
{
	return m_sink->IsReady();
}

void UTbSame1SameStruct1InterfaceOLinkClient::applyState(const nlohmann::json& fields)
{
	const bool bProp1Changed = fields.contains("prop1") && (Prop1 != fields["prop1"].get<FTbSame1Struct1>());
	if (bProp1Changed)
	{
		Prop1 = fields["prop1"].get<FTbSame1Struct1>();
		Execute__GetSignals(this)->OnProp1Changed.Broadcast(Prop1);
	}
}

void UTbSame1SameStruct1InterfaceOLinkClient::emitSignal(const std::string& signalName, const nlohmann::json& args)
{
	if (signalName == "sig1")
	{
		const FTbSame1Struct1& Param1 = args[0].get<FTbSame1Struct1>();
		Execute__GetSignals(this)->OnSig1Signal.Broadcast(Param1);
		return;
	}
}
