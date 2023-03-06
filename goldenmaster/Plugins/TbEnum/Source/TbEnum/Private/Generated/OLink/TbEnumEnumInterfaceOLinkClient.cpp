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

#include "Generated/OLink/TbEnumEnumInterfaceOLinkClient.h"
#include "Async/Future.h"
#include "Async/Async.h"
#include "Generated/api/TbEnum.json.adapter.h"
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

UTbEnumEnumInterfaceOLinkClient::UTbEnumEnumInterfaceOLinkClient()
	: UAbstractTbEnumEnumInterface()
{
	m_sink = std::make_shared<FUnrealOLinkSink>("tb.enum.EnumInterface");
}

void UTbEnumEnumInterfaceOLinkClient::Initialize(FSubsystemCollectionBase& Collection)
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

void UTbEnumEnumInterfaceOLinkClient::Deinitialize()
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

ETbEnumEnum0 UTbEnumEnumInterfaceOLinkClient::GetProp0_Implementation() const
{
	return Prop0;
}

void UTbEnumEnumInterfaceOLinkClient::SetProp0_Implementation(ETbEnumEnum0 InProp0)
{
	if (!m_sink->IsReady())
	{
		return;
	}
	m_sink->GetNode()->setRemoteProperty(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "prop0"), InProp0);
}

ETbEnumEnum1 UTbEnumEnumInterfaceOLinkClient::GetProp1_Implementation() const
{
	return Prop1;
}

void UTbEnumEnumInterfaceOLinkClient::SetProp1_Implementation(ETbEnumEnum1 InProp1)
{
	if (!m_sink->IsReady())
	{
		return;
	}
	m_sink->GetNode()->setRemoteProperty(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "prop1"), InProp1);
}

ETbEnumEnum2 UTbEnumEnumInterfaceOLinkClient::GetProp2_Implementation() const
{
	return Prop2;
}

void UTbEnumEnumInterfaceOLinkClient::SetProp2_Implementation(ETbEnumEnum2 InProp2)
{
	if (!m_sink->IsReady())
	{
		return;
	}
	m_sink->GetNode()->setRemoteProperty(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "prop2"), InProp2);
}

ETbEnumEnum3 UTbEnumEnumInterfaceOLinkClient::GetProp3_Implementation() const
{
	return Prop3;
}

void UTbEnumEnumInterfaceOLinkClient::SetProp3_Implementation(ETbEnumEnum3 InProp3)
{
	if (!m_sink->IsReady())
	{
		return;
	}
	m_sink->GetNode()->setRemoteProperty(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "prop3"), InProp3);
}

ETbEnumEnum0 UTbEnumEnumInterfaceOLinkClient::Func0_Implementation(ETbEnumEnum0 Param0)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return ETbEnumEnum0::TEE_VALUE0;
	}
	TPromise<ETbEnumEnum0> Promise;
	Async(EAsyncExecution::Thread,
		[Param0, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetEnumInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{ Promise.SetValue(arg.value.get<ETbEnumEnum0>()); };
			m_sink->GetNode()->invokeRemote(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "func0"), {Param0}, GetEnumInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

ETbEnumEnum1 UTbEnumEnumInterfaceOLinkClient::Func1_Implementation(ETbEnumEnum1 Param1)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return ETbEnumEnum1::TEE_VALUE1;
	}
	TPromise<ETbEnumEnum1> Promise;
	Async(EAsyncExecution::Thread,
		[Param1, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetEnumInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{ Promise.SetValue(arg.value.get<ETbEnumEnum1>()); };
			m_sink->GetNode()->invokeRemote(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "func1"), {Param1}, GetEnumInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

ETbEnumEnum2 UTbEnumEnumInterfaceOLinkClient::Func2_Implementation(ETbEnumEnum2 Param2)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return ETbEnumEnum2::TEE_VALUE2;
	}
	TPromise<ETbEnumEnum2> Promise;
	Async(EAsyncExecution::Thread,
		[Param2, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetEnumInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{ Promise.SetValue(arg.value.get<ETbEnumEnum2>()); };
			m_sink->GetNode()->invokeRemote(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "func2"), {Param2}, GetEnumInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

ETbEnumEnum3 UTbEnumEnumInterfaceOLinkClient::Func3_Implementation(ETbEnumEnum3 Param3)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return ETbEnumEnum3::TEE_VALUE3;
	}
	TPromise<ETbEnumEnum3> Promise;
	Async(EAsyncExecution::Thread,
		[Param3, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetEnumInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{ Promise.SetValue(arg.value.get<ETbEnumEnum3>()); };
			m_sink->GetNode()->invokeRemote(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "func3"), {Param3}, GetEnumInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

void UTbEnumEnumInterfaceOLinkClient::applyState(const nlohmann::json& fields)
{
	const bool bProp0Changed = fields.contains("prop0") && (Prop0 != fields["prop0"].get<ETbEnumEnum0>());
	if (bProp0Changed)
	{
		Prop0 = fields["prop0"].get<ETbEnumEnum0>();
		Execute_BroadcastProp0Changed(this, Prop0);
	}
	const bool bProp1Changed = fields.contains("prop1") && (Prop1 != fields["prop1"].get<ETbEnumEnum1>());
	if (bProp1Changed)
	{
		Prop1 = fields["prop1"].get<ETbEnumEnum1>();
		Execute_BroadcastProp1Changed(this, Prop1);
	}
	const bool bProp2Changed = fields.contains("prop2") && (Prop2 != fields["prop2"].get<ETbEnumEnum2>());
	if (bProp2Changed)
	{
		Prop2 = fields["prop2"].get<ETbEnumEnum2>();
		Execute_BroadcastProp2Changed(this, Prop2);
	}
	const bool bProp3Changed = fields.contains("prop3") && (Prop3 != fields["prop3"].get<ETbEnumEnum3>());
	if (bProp3Changed)
	{
		Prop3 = fields["prop3"].get<ETbEnumEnum3>();
		Execute_BroadcastProp3Changed(this, Prop3);
	}
}

void UTbEnumEnumInterfaceOLinkClient::emitSignal(const std::string& signalName, const nlohmann::json& args)
{
	if (signalName == "sig0")
	{
		Execute_BroadcastSig0(this, args[0].get<ETbEnumEnum0>());
		return;
	}
	if (signalName == "sig1")
	{
		Execute_BroadcastSig1(this, args[0].get<ETbEnumEnum1>());
		return;
	}
	if (signalName == "sig2")
	{
		Execute_BroadcastSig2(this, args[0].get<ETbEnumEnum2>());
		return;
	}
	if (signalName == "sig3")
	{
		Execute_BroadcastSig3(this, args[0].get<ETbEnumEnum3>());
		return;
	}
}
