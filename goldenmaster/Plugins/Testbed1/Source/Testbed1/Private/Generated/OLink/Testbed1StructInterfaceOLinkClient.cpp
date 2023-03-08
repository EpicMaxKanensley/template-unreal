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

#include "Generated/OLink/Testbed1StructInterfaceOLinkClient.h"
#include "ApiGearSettings.h"
#include "Async/Future.h"
#include "Async/Async.h"
#include "Generated/api/Testbed1.json.adapter.h"
#include "unrealolink.h"
#include "unrealolinksink.h"
#include "Async/Async.h"
#include "Engine/Engine.h"
#include "ApiGear/Public/ApiGearConnectionManager.h"
#include "Misc/DateTime.h"
THIRD_PARTY_INCLUDES_START
#include "olink/clientnode.h"
#include "olink/iobjectsink.h"
THIRD_PARTY_INCLUDES_END

namespace
{
bool IsTestbed1StructInterfaceLogEnabled()
{
	UApiGearSettings* settings = GetMutableDefault<UApiGearSettings>();
	return settings->OLINK_EnableDebugLog;
}
} // namespace

UTestbed1StructInterfaceOLinkClient::UTestbed1StructInterfaceOLinkClient()
	: UAbstractTestbed1StructInterface()
{
	m_sink = std::make_shared<FUnrealOLinkSink>("testbed1.StructInterface");
}

void UTestbed1StructInterfaceOLinkClient::Initialize(FSubsystemCollectionBase& Collection)
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

void UTestbed1StructInterfaceOLinkClient::Deinitialize()
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

FTestbed1StructBool UTestbed1StructInterfaceOLinkClient::GetPropBool_Implementation() const
{
	return PropBool;
}

void UTestbed1StructInterfaceOLinkClient::SetPropBool_Implementation(const FTestbed1StructBool& InPropBool)
{
	if (!m_sink->IsReady())
	{
		return;
	}
	m_sink->GetNode()->setRemoteProperty(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "propBool"), InPropBool);
}

FTestbed1StructInt UTestbed1StructInterfaceOLinkClient::GetPropInt_Implementation() const
{
	return PropInt;
}

void UTestbed1StructInterfaceOLinkClient::SetPropInt_Implementation(const FTestbed1StructInt& InPropInt)
{
	if (!m_sink->IsReady())
	{
		return;
	}
	m_sink->GetNode()->setRemoteProperty(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "propInt"), InPropInt);
}

FTestbed1StructFloat UTestbed1StructInterfaceOLinkClient::GetPropFloat_Implementation() const
{
	return PropFloat;
}

void UTestbed1StructInterfaceOLinkClient::SetPropFloat_Implementation(const FTestbed1StructFloat& InPropFloat)
{
	if (!m_sink->IsReady())
	{
		return;
	}
	m_sink->GetNode()->setRemoteProperty(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "propFloat"), InPropFloat);
}

FTestbed1StructString UTestbed1StructInterfaceOLinkClient::GetPropString_Implementation() const
{
	return PropString;
}

void UTestbed1StructInterfaceOLinkClient::SetPropString_Implementation(const FTestbed1StructString& InPropString)
{
	if (!m_sink->IsReady())
	{
		return;
	}
	m_sink->GetNode()->setRemoteProperty(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "propString"), InPropString);
}

FTestbed1StructBool UTestbed1StructInterfaceOLinkClient::FuncBool_Implementation(const FTestbed1StructBool& ParamBool)
{
	if (!m_sink->IsReady())
	{
		if (IsTestbed1StructInterfaceLogEnabled())
		{
			UE_LOG(LogTemp, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		}

		return FTestbed1StructBool();
	}
	TPromise<FTestbed1StructBool> Promise;
	Async(EAsyncExecution::Thread,
		[ParamBool, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetStructInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{ Promise.SetValue(arg.value.get<FTestbed1StructBool>()); };
			m_sink->GetNode()->invokeRemote(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcBool"), {ParamBool}, GetStructInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

FTestbed1StructBool UTestbed1StructInterfaceOLinkClient::FuncInt_Implementation(const FTestbed1StructInt& ParamInt)
{
	if (!m_sink->IsReady())
	{
		if (IsTestbed1StructInterfaceLogEnabled())
		{
			UE_LOG(LogTemp, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		}

		return FTestbed1StructBool();
	}
	TPromise<FTestbed1StructBool> Promise;
	Async(EAsyncExecution::Thread,
		[ParamInt, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetStructInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{ Promise.SetValue(arg.value.get<FTestbed1StructBool>()); };
			m_sink->GetNode()->invokeRemote(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcInt"), {ParamInt}, GetStructInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

FTestbed1StructFloat UTestbed1StructInterfaceOLinkClient::FuncFloat_Implementation(const FTestbed1StructFloat& ParamFloat)
{
	if (!m_sink->IsReady())
	{
		if (IsTestbed1StructInterfaceLogEnabled())
		{
			UE_LOG(LogTemp, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		}

		return FTestbed1StructFloat();
	}
	TPromise<FTestbed1StructFloat> Promise;
	Async(EAsyncExecution::Thread,
		[ParamFloat, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetStructInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{ Promise.SetValue(arg.value.get<FTestbed1StructFloat>()); };
			m_sink->GetNode()->invokeRemote(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcFloat"), {ParamFloat}, GetStructInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

FTestbed1StructString UTestbed1StructInterfaceOLinkClient::FuncString_Implementation(const FTestbed1StructString& ParamString)
{
	if (!m_sink->IsReady())
	{
		if (IsTestbed1StructInterfaceLogEnabled())
		{
			UE_LOG(LogTemp, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		}

		return FTestbed1StructString();
	}
	TPromise<FTestbed1StructString> Promise;
	Async(EAsyncExecution::Thread,
		[ParamString, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetStructInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{ Promise.SetValue(arg.value.get<FTestbed1StructString>()); };
			m_sink->GetNode()->invokeRemote(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcString"), {ParamString}, GetStructInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

void UTestbed1StructInterfaceOLinkClient::applyState(const nlohmann::json& fields)
{
	const bool bPropBoolChanged = fields.contains("propBool") && (PropBool != fields["propBool"].get<FTestbed1StructBool>());
	if (bPropBoolChanged)
	{
		PropBool = fields["propBool"].get<FTestbed1StructBool>();
		Execute_BroadcastPropBoolChanged(this, PropBool);
	}

	const bool bPropIntChanged = fields.contains("propInt") && (PropInt != fields["propInt"].get<FTestbed1StructInt>());
	if (bPropIntChanged)
	{
		PropInt = fields["propInt"].get<FTestbed1StructInt>();
		Execute_BroadcastPropIntChanged(this, PropInt);
	}

	const bool bPropFloatChanged = fields.contains("propFloat") && (PropFloat != fields["propFloat"].get<FTestbed1StructFloat>());
	if (bPropFloatChanged)
	{
		PropFloat = fields["propFloat"].get<FTestbed1StructFloat>();
		Execute_BroadcastPropFloatChanged(this, PropFloat);
	}

	const bool bPropStringChanged = fields.contains("propString") && (PropString != fields["propString"].get<FTestbed1StructString>());
	if (bPropStringChanged)
	{
		PropString = fields["propString"].get<FTestbed1StructString>();
		Execute_BroadcastPropStringChanged(this, PropString);
	}
}

void UTestbed1StructInterfaceOLinkClient::emitSignal(const std::string& signalName, const nlohmann::json& args)
{
	if (signalName == "sigBool")
	{
		const FTestbed1StructBool& ParamBool = args[0].get<FTestbed1StructBool>();
		Execute_BroadcastSigBool(this, ParamBool);
		return;
	}

	if (signalName == "sigInt")
	{
		const FTestbed1StructInt& ParamInt = args[0].get<FTestbed1StructInt>();
		Execute_BroadcastSigInt(this, ParamInt);
		return;
	}

	if (signalName == "sigFloat")
	{
		const FTestbed1StructFloat& ParamFloat = args[0].get<FTestbed1StructFloat>();
		Execute_BroadcastSigFloat(this, ParamFloat);
		return;
	}

	if (signalName == "sigString")
	{
		const FTestbed1StructString& ParamString = args[0].get<FTestbed1StructString>();
		Execute_BroadcastSigString(this, ParamString);
		return;
	}
}
