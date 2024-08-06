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

#include "Generated/OLink/TbSimpleSimpleInterfaceOLinkClient.h"
#include "ApiGearSettings.h"
#include "ApiGearOLink.h"
#include "Async/Async.h"
#include "Generated/api/TbSimple.json.adapter.h"
#include "OLinkClientConnection.h"
#include "OLinkSink.h"
#include "Engine/Engine.h"
#include "ApiGear/Public/ApiGearConnectionsStore.h"
#include "Misc/DateTime.h"
#include "TbSimpleSettings.h"
THIRD_PARTY_INCLUDES_START
#include "olink/clientnode.h"
#include "olink/iobjectsink.h"
THIRD_PARTY_INCLUDES_END
#include <atomic>
#include "HAL/CriticalSection.h"

/**
   \brief data structure to hold the last sent property values
*/
struct TbSimpleSimpleInterfacePropertiesData
{
	std::atomic<bool> bPropBool{false};
	std::atomic<int32> PropInt{0};
	std::atomic<int32> PropInt32{0};
	std::atomic<int64> PropInt64{0LL};
	std::atomic<float> PropFloat{0.0f};
	std::atomic<float> PropFloat32{0.0f};
	std::atomic<double> PropFloat64{0.0};
	FCriticalSection PropStringMutex;
	FString PropString{FString()};
	FCriticalSection PropReadOnlyStringMutex;
	FString PropReadOnlyString{FString()};
};
DEFINE_LOG_CATEGORY(LogTbSimpleSimpleInterfaceOLinkClient);

UTbSimpleSimpleInterfaceOLinkClient::UTbSimpleSimpleInterfaceOLinkClient()
	: UAbstractTbSimpleSimpleInterface()
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION < 27)
	, _SentData(MakeUnique<TbSimpleSimpleInterfacePropertiesData>())
#else
	, _SentData(MakePimpl<TbSimpleSimpleInterfacePropertiesData>())
#endif
{
	m_sink = std::make_shared<FOLinkSink>("tb.simple.SimpleInterface");
}

UTbSimpleSimpleInterfaceOLinkClient::UTbSimpleSimpleInterfaceOLinkClient(FVTableHelper& Helper)
	: Super(Helper)
{
}
UTbSimpleSimpleInterfaceOLinkClient::~UTbSimpleSimpleInterfaceOLinkClient() = default;

void UTbSimpleSimpleInterfaceOLinkClient::Initialize(FSubsystemCollectionBase& Collection)
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
	UTbSimpleSettings* settings = GetMutableDefault<UTbSimpleSettings>();

	UApiGearConnectionsStore* AGCM = GEngine->GetEngineSubsystem<UApiGearConnectionsStore>();

	TScriptInterface<IApiGearConnection> OLinkConnection = AGCM->GetConnection(settings->OLinkConnectionIdentifier);

	if (!OLinkConnection.GetInterface())
	{
		UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Warning, TEXT("No valid olink connection for the %s client, please set in the ApiGear TbSimple plugin settings or during run time"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}
	UseConnection(OLinkConnection);
	OLinkConnection->Connect();
}

void UTbSimpleSimpleInterfaceOLinkClient::Deinitialize()
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

void UTbSimpleSimpleInterfaceOLinkClient::UseConnection(TScriptInterface<IApiGearConnection> InConnection)
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

bool UTbSimpleSimpleInterfaceOLinkClient::GetPropBool_Implementation() const
{
	return bPropBool;
}

void UTbSimpleSimpleInterfaceOLinkClient::SetPropBool_Implementation(bool bInPropBool)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetPropBool_Implementation() == bInPropBool)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	if (_SentData->bPropBool == bInPropBool)
	{
		return;
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "propBool");
	m_sink->GetNode()->setRemoteProperty(memberId, bInPropBool);
	_SentData->bPropBool = bInPropBool;
}

int32 UTbSimpleSimpleInterfaceOLinkClient::GetPropInt_Implementation() const
{
	return PropInt;
}

void UTbSimpleSimpleInterfaceOLinkClient::SetPropInt_Implementation(int32 InPropInt)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetPropInt_Implementation() == InPropInt)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	if (_SentData->PropInt == InPropInt)
	{
		return;
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "propInt");
	m_sink->GetNode()->setRemoteProperty(memberId, InPropInt);
	_SentData->PropInt = InPropInt;
}

int32 UTbSimpleSimpleInterfaceOLinkClient::GetPropInt32_Implementation() const
{
	return PropInt32;
}

void UTbSimpleSimpleInterfaceOLinkClient::SetPropInt32_Implementation(int32 InPropInt32)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetPropInt32_Implementation() == InPropInt32)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	if (_SentData->PropInt32 == InPropInt32)
	{
		return;
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "propInt32");
	m_sink->GetNode()->setRemoteProperty(memberId, InPropInt32);
	_SentData->PropInt32 = InPropInt32;
}

int64 UTbSimpleSimpleInterfaceOLinkClient::GetPropInt64_Implementation() const
{
	return PropInt64;
}

void UTbSimpleSimpleInterfaceOLinkClient::SetPropInt64_Implementation(int64 InPropInt64)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetPropInt64_Implementation() == InPropInt64)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	if (_SentData->PropInt64 == InPropInt64)
	{
		return;
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "propInt64");
	m_sink->GetNode()->setRemoteProperty(memberId, InPropInt64);
	_SentData->PropInt64 = InPropInt64;
}

float UTbSimpleSimpleInterfaceOLinkClient::GetPropFloat_Implementation() const
{
	return PropFloat;
}

void UTbSimpleSimpleInterfaceOLinkClient::SetPropFloat_Implementation(float InPropFloat)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetPropFloat_Implementation() == InPropFloat)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	if (_SentData->PropFloat == InPropFloat)
	{
		return;
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "propFloat");
	m_sink->GetNode()->setRemoteProperty(memberId, InPropFloat);
	_SentData->PropFloat = InPropFloat;
}

float UTbSimpleSimpleInterfaceOLinkClient::GetPropFloat32_Implementation() const
{
	return PropFloat32;
}

void UTbSimpleSimpleInterfaceOLinkClient::SetPropFloat32_Implementation(float InPropFloat32)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetPropFloat32_Implementation() == InPropFloat32)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	if (_SentData->PropFloat32 == InPropFloat32)
	{
		return;
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "propFloat32");
	m_sink->GetNode()->setRemoteProperty(memberId, InPropFloat32);
	_SentData->PropFloat32 = InPropFloat32;
}

double UTbSimpleSimpleInterfaceOLinkClient::GetPropFloat64_Implementation() const
{
	return PropFloat64;
}

void UTbSimpleSimpleInterfaceOLinkClient::SetPropFloat64_Implementation(double InPropFloat64)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetPropFloat64_Implementation() == InPropFloat64)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	if (_SentData->PropFloat64 == InPropFloat64)
	{
		return;
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "propFloat64");
	m_sink->GetNode()->setRemoteProperty(memberId, InPropFloat64);
	_SentData->PropFloat64 = InPropFloat64;
}

FString UTbSimpleSimpleInterfaceOLinkClient::GetPropString_Implementation() const
{
	return PropString;
}

void UTbSimpleSimpleInterfaceOLinkClient::SetPropString_Implementation(const FString& InPropString)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetPropString_Implementation() == InPropString)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	{
		FScopeLock Lock(&(_SentData->PropStringMutex));
		if (_SentData->PropString == InPropString)
		{
			return;
		}
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "propString");
	m_sink->GetNode()->setRemoteProperty(memberId, InPropString);
	FScopeLock Lock(&(_SentData->PropStringMutex));
	_SentData->PropString = InPropString;
}

FString UTbSimpleSimpleInterfaceOLinkClient::GetPropReadOnlyString_Implementation() const
{
	return PropReadOnlyString;
}

void UTbSimpleSimpleInterfaceOLinkClient::FuncVoid_Implementation()
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return;
	}
	ApiGear::ObjectLink::InvokeReplyFunc GetSimpleInterfaceStateFunc = [this](ApiGear::ObjectLink::InvokeReplyArg arg) {};
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcVoid");
	m_sink->GetNode()->invokeRemote(memberId, {}, GetSimpleInterfaceStateFunc);
}

bool UTbSimpleSimpleInterfaceOLinkClient::FuncBool_Implementation(bool bParamBool)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return false;
	}
	TPromise<bool> Promise;
	Async(EAsyncExecution::Thread,
		[bParamBool, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetSimpleInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{
				if (!arg.value.empty())
				{
					Promise.SetValue(arg.value.get<bool>());
				}
				else
				{
					UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Error, TEXT("FuncBool: OLink service returned empty value - should have returned type of bool"));
					Promise.SetValue(bool());
				}
			};
			static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcBool");
			m_sink->GetNode()->invokeRemote(memberId, {bParamBool}, GetSimpleInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

int32 UTbSimpleSimpleInterfaceOLinkClient::FuncInt_Implementation(int32 ParamInt)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return 0;
	}
	TPromise<int32> Promise;
	Async(EAsyncExecution::Thread,
		[ParamInt, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetSimpleInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{
				if (!arg.value.empty())
				{
					Promise.SetValue(arg.value.get<int32>());
				}
				else
				{
					UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Error, TEXT("FuncInt: OLink service returned empty value - should have returned type of int32"));
					Promise.SetValue(int32());
				}
			};
			static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcInt");
			m_sink->GetNode()->invokeRemote(memberId, {ParamInt}, GetSimpleInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

int32 UTbSimpleSimpleInterfaceOLinkClient::FuncInt32_Implementation(int32 ParamInt32)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return 0;
	}
	TPromise<int32> Promise;
	Async(EAsyncExecution::Thread,
		[ParamInt32, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetSimpleInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{
				if (!arg.value.empty())
				{
					Promise.SetValue(arg.value.get<int32>());
				}
				else
				{
					UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Error, TEXT("FuncInt32: OLink service returned empty value - should have returned type of int32"));
					Promise.SetValue(int32());
				}
			};
			static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcInt32");
			m_sink->GetNode()->invokeRemote(memberId, {ParamInt32}, GetSimpleInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

int64 UTbSimpleSimpleInterfaceOLinkClient::FuncInt64_Implementation(int64 ParamInt64)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return 0LL;
	}
	TPromise<int64> Promise;
	Async(EAsyncExecution::Thread,
		[ParamInt64, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetSimpleInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{
				if (!arg.value.empty())
				{
					Promise.SetValue(arg.value.get<int64>());
				}
				else
				{
					UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Error, TEXT("FuncInt64: OLink service returned empty value - should have returned type of int64"));
					Promise.SetValue(int64());
				}
			};
			static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcInt64");
			m_sink->GetNode()->invokeRemote(memberId, {ParamInt64}, GetSimpleInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

float UTbSimpleSimpleInterfaceOLinkClient::FuncFloat_Implementation(float ParamFloat)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return 0.0f;
	}
	TPromise<float> Promise;
	Async(EAsyncExecution::Thread,
		[ParamFloat, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetSimpleInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{
				if (!arg.value.empty())
				{
					Promise.SetValue(arg.value.get<float>());
				}
				else
				{
					UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Error, TEXT("FuncFloat: OLink service returned empty value - should have returned type of float"));
					Promise.SetValue(float());
				}
			};
			static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcFloat");
			m_sink->GetNode()->invokeRemote(memberId, {ParamFloat}, GetSimpleInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

float UTbSimpleSimpleInterfaceOLinkClient::FuncFloat32_Implementation(float ParamFloat32)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return 0.0f;
	}
	TPromise<float> Promise;
	Async(EAsyncExecution::Thread,
		[ParamFloat32, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetSimpleInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{
				if (!arg.value.empty())
				{
					Promise.SetValue(arg.value.get<float>());
				}
				else
				{
					UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Error, TEXT("FuncFloat32: OLink service returned empty value - should have returned type of float"));
					Promise.SetValue(float());
				}
			};
			static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcFloat32");
			m_sink->GetNode()->invokeRemote(memberId, {ParamFloat32}, GetSimpleInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

double UTbSimpleSimpleInterfaceOLinkClient::FuncFloat64_Implementation(double ParamFloat)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return 0.0;
	}
	TPromise<double> Promise;
	Async(EAsyncExecution::Thread,
		[ParamFloat, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetSimpleInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{
				if (!arg.value.empty())
				{
					Promise.SetValue(arg.value.get<double>());
				}
				else
				{
					UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Error, TEXT("FuncFloat64: OLink service returned empty value - should have returned type of double"));
					Promise.SetValue(double());
				}
			};
			static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcFloat64");
			m_sink->GetNode()->invokeRemote(memberId, {ParamFloat}, GetSimpleInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

FString UTbSimpleSimpleInterfaceOLinkClient::FuncString_Implementation(const FString& ParamString)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return FString();
	}
	TPromise<FString> Promise;
	Async(EAsyncExecution::Thread,
		[ParamString, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetSimpleInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{
				if (!arg.value.empty())
				{
					Promise.SetValue(arg.value.get<FString>());
				}
				else
				{
					UE_LOG(LogTbSimpleSimpleInterfaceOLinkClient, Error, TEXT("FuncString: OLink service returned empty value - should have returned type of FString"));
					Promise.SetValue(FString());
				}
			};
			static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcString");
			m_sink->GetNode()->invokeRemote(memberId, {ParamString}, GetSimpleInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

bool UTbSimpleSimpleInterfaceOLinkClient::_IsSubscribed() const
{
	return m_sink->IsReady();
}

void UTbSimpleSimpleInterfaceOLinkClient::applyState(const nlohmann::json& fields)
{
	const bool bPropBoolChanged = fields.contains("propBool") && (bPropBool != fields["propBool"].get<bool>());
	if (bPropBoolChanged)
	{
		bPropBool = fields["propBool"].get<bool>();
		Execute__GetSignals(this)->OnPropBoolChanged.Broadcast(bPropBool);
	}

	const bool bPropIntChanged = fields.contains("propInt") && (PropInt != fields["propInt"].get<int32>());
	if (bPropIntChanged)
	{
		PropInt = fields["propInt"].get<int32>();
		Execute__GetSignals(this)->OnPropIntChanged.Broadcast(PropInt);
	}

	const bool bPropInt32Changed = fields.contains("propInt32") && (PropInt32 != fields["propInt32"].get<int32>());
	if (bPropInt32Changed)
	{
		PropInt32 = fields["propInt32"].get<int32>();
		Execute__GetSignals(this)->OnPropInt32Changed.Broadcast(PropInt32);
	}

	const bool bPropInt64Changed = fields.contains("propInt64") && (PropInt64 != fields["propInt64"].get<int64>());
	if (bPropInt64Changed)
	{
		PropInt64 = fields["propInt64"].get<int64>();
		Execute__GetSignals(this)->OnPropInt64Changed.Broadcast(PropInt64);
	}

	const bool bPropFloatChanged = fields.contains("propFloat") && (PropFloat != fields["propFloat"].get<float>());
	if (bPropFloatChanged)
	{
		PropFloat = fields["propFloat"].get<float>();
		Execute__GetSignals(this)->OnPropFloatChanged.Broadcast(PropFloat);
	}

	const bool bPropFloat32Changed = fields.contains("propFloat32") && (PropFloat32 != fields["propFloat32"].get<float>());
	if (bPropFloat32Changed)
	{
		PropFloat32 = fields["propFloat32"].get<float>();
		Execute__GetSignals(this)->OnPropFloat32Changed.Broadcast(PropFloat32);
	}

	const bool bPropFloat64Changed = fields.contains("propFloat64") && (PropFloat64 != fields["propFloat64"].get<double>());
	if (bPropFloat64Changed)
	{
		PropFloat64 = fields["propFloat64"].get<double>();
		Execute__GetSignals(this)->OnPropFloat64Changed.Broadcast(PropFloat64);
	}

	const bool bPropStringChanged = fields.contains("propString") && (PropString != fields["propString"].get<FString>());
	if (bPropStringChanged)
	{
		PropString = fields["propString"].get<FString>();
		Execute__GetSignals(this)->OnPropStringChanged.Broadcast(PropString);
	}

	const bool bPropReadOnlyStringChanged = fields.contains("propReadOnlyString") && (PropReadOnlyString != fields["propReadOnlyString"].get<FString>());
	if (bPropReadOnlyStringChanged)
	{
		PropReadOnlyString = fields["propReadOnlyString"].get<FString>();
		Execute__GetSignals(this)->OnPropReadOnlyStringChanged.Broadcast(PropReadOnlyString);
	}
}

void UTbSimpleSimpleInterfaceOLinkClient::emitSignal(const std::string& signalName, const nlohmann::json& args)
{
	if (signalName == "sigVoid")
	{
		Execute__GetSignals(this)->OnSigVoidSignal.Broadcast();
		return;
	}

	if (signalName == "sigBool")
	{
		bool bParamBool = args[0].get<bool>();
		Execute__GetSignals(this)->OnSigBoolSignal.Broadcast(bParamBool);
		return;
	}

	if (signalName == "sigInt")
	{
		int32 ParamInt = args[0].get<int32>();
		Execute__GetSignals(this)->OnSigIntSignal.Broadcast(ParamInt);
		return;
	}

	if (signalName == "sigInt32")
	{
		int32 ParamInt32 = args[0].get<int32>();
		Execute__GetSignals(this)->OnSigInt32Signal.Broadcast(ParamInt32);
		return;
	}

	if (signalName == "sigInt64")
	{
		int64 ParamInt64 = args[0].get<int64>();
		Execute__GetSignals(this)->OnSigInt64Signal.Broadcast(ParamInt64);
		return;
	}

	if (signalName == "sigFloat")
	{
		float ParamFloat = args[0].get<float>();
		Execute__GetSignals(this)->OnSigFloatSignal.Broadcast(ParamFloat);
		return;
	}

	if (signalName == "sigFloat32")
	{
		float ParamFloa32 = args[0].get<float>();
		Execute__GetSignals(this)->OnSigFloat32Signal.Broadcast(ParamFloa32);
		return;
	}

	if (signalName == "sigFloat64")
	{
		double ParamFloat64 = args[0].get<double>();
		Execute__GetSignals(this)->OnSigFloat64Signal.Broadcast(ParamFloat64);
		return;
	}

	if (signalName == "sigString")
	{
		const FString& ParamString = args[0].get<FString>();
		Execute__GetSignals(this)->OnSigStringSignal.Broadcast(ParamString);
		return;
	}
}
