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

#include "Generated/OLink/TbSimpleSimpleArrayInterfaceOLinkClient.h"
#include "ApiGearSettings.h"
#include "apigearolink.h"
#include "Async/Async.h"
#include "Generated/api/TbSimple.json.adapter.h"
#include "unrealolink.h"
#include "unrealolinksink.h"
#include "Engine/Engine.h"
#include "ApiGear/Public/ApiGearConnectionsStore.h"
#include "Misc/DateTime.h"
#include "TbSimpleSettings.h"
THIRD_PARTY_INCLUDES_START
#include "olink/clientnode.h"
#include "olink/iobjectsink.h"
THIRD_PARTY_INCLUDES_END
#include "HAL/CriticalSection.h"

/**
   \brief data structure to hold the last sent property values
*/
struct TbSimpleSimpleArrayInterfacePropertiesData
{
	FCriticalSection PropBoolMutex;
	TArray<bool> PropBool{TArray<bool>()};
	FCriticalSection PropIntMutex;
	TArray<int32> PropInt{TArray<int32>()};
	FCriticalSection PropInt32Mutex;
	TArray<int32> PropInt32{TArray<int32>()};
	FCriticalSection PropInt64Mutex;
	TArray<int64> PropInt64{TArray<int64>()};
	FCriticalSection PropFloatMutex;
	TArray<float> PropFloat{TArray<float>()};
	FCriticalSection PropFloat32Mutex;
	TArray<float> PropFloat32{TArray<float>()};
	FCriticalSection PropFloat64Mutex;
	TArray<double> PropFloat64{TArray<double>()};
	FCriticalSection PropStringMutex;
	TArray<FString> PropString{TArray<FString>()};
};
DEFINE_LOG_CATEGORY(LogTbSimpleSimpleArrayInterfaceOLinkClient);

UTbSimpleSimpleArrayInterfaceOLinkClient::UTbSimpleSimpleArrayInterfaceOLinkClient()
	: UAbstractTbSimpleSimpleArrayInterface()
#if (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION < 27)
	, _SentData(MakeUnique<TbSimpleSimpleArrayInterfacePropertiesData>())
#else
	, _SentData(MakePimpl<TbSimpleSimpleArrayInterfacePropertiesData>())
#endif
{
	m_sink = std::make_shared<FUnrealOLinkSink>("tb.simple.SimpleArrayInterface");
}

UTbSimpleSimpleArrayInterfaceOLinkClient::UTbSimpleSimpleArrayInterfaceOLinkClient(FVTableHelper& Helper)
	: Super(Helper)
{
}
UTbSimpleSimpleArrayInterfaceOLinkClient::~UTbSimpleSimpleArrayInterfaceOLinkClient() = default;

void UTbSimpleSimpleArrayInterfaceOLinkClient::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	m_sink->setOnInitCallback([this]()
		{ _SubscriptionStatusChanged.Broadcast(true); });
	m_sink->setOnReleaseCallback([this]()
		{ _SubscriptionStatusChanged.Broadcast(false); });

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

	check(GEngine);
	UTbSimpleSettings* settings = GetMutableDefault<UTbSimpleSettings>();

	UApiGearConnectionsStore* AGCM = GEngine->GetEngineSubsystem<UApiGearConnectionsStore>();

	TScriptInterface<IApiGearConnection> OLinkConnection = AGCM->GetConnection(settings->OLinkConnectionIdentifier);

	if (!OLinkConnection.GetInterface())
	{
		UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Warning, TEXT("No valid olink connection for the %s client, please set in the ApiGear TbSimple plugin settings or during run time"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}
	UseConnection(OLinkConnection);
	OLinkConnection->Connect();
}

void UTbSimpleSimpleArrayInterfaceOLinkClient::Deinitialize()
{
	// tell the sink that we are gone and should not try to be invoked
	m_sink->resetOnPropertyChangedCallback();
	m_sink->resetOnSignalEmittedCallback();
	m_sink->resetOnInitCallback();
	m_sink->resetOnReleaseCallback();

	if (Connection.GetObject())
	{
		UUnrealOLink* UnrealOLinkConnection = Cast<UUnrealOLink>(Connection.GetObject());
		UnrealOLinkConnection->unlinkObjectSource(m_sink->olinkObjectName());
		UnrealOLinkConnection->node()->registry().removeSink(m_sink->olinkObjectName());
	}

	Super::Deinitialize();
}

void UTbSimpleSimpleArrayInterfaceOLinkClient::UseConnection(TScriptInterface<IApiGearConnection> InConnection)
{
	checkf(InConnection.GetInterface() != nullptr, TEXT("Cannot use connection - interface IApiGearConnection is not fully implemented"));

	// only accept connections of type olink
	checkf(InConnection->GetConnectionProtocolIdentifier() == ApiGearOLinkProtocolIdentifier, TEXT("Cannot use connection - must be of type olink"));

	UUnrealOLink* UnrealOLinkConnection = nullptr;
	// remove old connection
	if (Connection.GetObject())
	{
		UnrealOLinkConnection = Cast<UUnrealOLink>(Connection.GetObject());
		UnrealOLinkConnection->unlinkObjectSource(m_sink->olinkObjectName());
		UnrealOLinkConnection->node()->registry().removeSink(m_sink->olinkObjectName());
		UnrealOLinkConnection = nullptr;
	}

	// set up new connection
	UnrealOLinkConnection = Cast<UUnrealOLink>(InConnection.GetObject());
	UnrealOLinkConnection->node()->registry().addSink(m_sink);
	UnrealOLinkConnection->linkObjectSource(m_sink->olinkObjectName());

	Connection = InConnection;
}

TArray<bool> UTbSimpleSimpleArrayInterfaceOLinkClient::GetPropBool_Implementation() const
{
	return PropBool;
}

void UTbSimpleSimpleArrayInterfaceOLinkClient::SetPropBool_Implementation(const TArray<bool>& InPropBool)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetPropBool_Implementation() == InPropBool)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	{
		FScopeLock Lock(&(_SentData->PropBoolMutex));
		if (_SentData->PropBool == InPropBool)
		{
			return;
		}
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "propBool");
	m_sink->GetNode()->setRemoteProperty(memberId, InPropBool);
	FScopeLock Lock(&(_SentData->PropBoolMutex));
	_SentData->PropBool = InPropBool;
}

TArray<int32> UTbSimpleSimpleArrayInterfaceOLinkClient::GetPropInt_Implementation() const
{
	return PropInt;
}

void UTbSimpleSimpleArrayInterfaceOLinkClient::SetPropInt_Implementation(const TArray<int32>& InPropInt)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetPropInt_Implementation() == InPropInt)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	{
		FScopeLock Lock(&(_SentData->PropIntMutex));
		if (_SentData->PropInt == InPropInt)
		{
			return;
		}
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "propInt");
	m_sink->GetNode()->setRemoteProperty(memberId, InPropInt);
	FScopeLock Lock(&(_SentData->PropIntMutex));
	_SentData->PropInt = InPropInt;
}

TArray<int32> UTbSimpleSimpleArrayInterfaceOLinkClient::GetPropInt32_Implementation() const
{
	return PropInt32;
}

void UTbSimpleSimpleArrayInterfaceOLinkClient::SetPropInt32_Implementation(const TArray<int32>& InPropInt32)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetPropInt32_Implementation() == InPropInt32)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	{
		FScopeLock Lock(&(_SentData->PropInt32Mutex));
		if (_SentData->PropInt32 == InPropInt32)
		{
			return;
		}
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "propInt32");
	m_sink->GetNode()->setRemoteProperty(memberId, InPropInt32);
	FScopeLock Lock(&(_SentData->PropInt32Mutex));
	_SentData->PropInt32 = InPropInt32;
}

TArray<int64> UTbSimpleSimpleArrayInterfaceOLinkClient::GetPropInt64_Implementation() const
{
	return PropInt64;
}

void UTbSimpleSimpleArrayInterfaceOLinkClient::SetPropInt64_Implementation(const TArray<int64>& InPropInt64)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetPropInt64_Implementation() == InPropInt64)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	{
		FScopeLock Lock(&(_SentData->PropInt64Mutex));
		if (_SentData->PropInt64 == InPropInt64)
		{
			return;
		}
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "propInt64");
	m_sink->GetNode()->setRemoteProperty(memberId, InPropInt64);
	FScopeLock Lock(&(_SentData->PropInt64Mutex));
	_SentData->PropInt64 = InPropInt64;
}

TArray<float> UTbSimpleSimpleArrayInterfaceOLinkClient::GetPropFloat_Implementation() const
{
	return PropFloat;
}

void UTbSimpleSimpleArrayInterfaceOLinkClient::SetPropFloat_Implementation(const TArray<float>& InPropFloat)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetPropFloat_Implementation() == InPropFloat)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	{
		FScopeLock Lock(&(_SentData->PropFloatMutex));
		if (_SentData->PropFloat == InPropFloat)
		{
			return;
		}
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "propFloat");
	m_sink->GetNode()->setRemoteProperty(memberId, InPropFloat);
	FScopeLock Lock(&(_SentData->PropFloatMutex));
	_SentData->PropFloat = InPropFloat;
}

TArray<float> UTbSimpleSimpleArrayInterfaceOLinkClient::GetPropFloat32_Implementation() const
{
	return PropFloat32;
}

void UTbSimpleSimpleArrayInterfaceOLinkClient::SetPropFloat32_Implementation(const TArray<float>& InPropFloat32)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetPropFloat32_Implementation() == InPropFloat32)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	{
		FScopeLock Lock(&(_SentData->PropFloat32Mutex));
		if (_SentData->PropFloat32 == InPropFloat32)
		{
			return;
		}
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "propFloat32");
	m_sink->GetNode()->setRemoteProperty(memberId, InPropFloat32);
	FScopeLock Lock(&(_SentData->PropFloat32Mutex));
	_SentData->PropFloat32 = InPropFloat32;
}

TArray<double> UTbSimpleSimpleArrayInterfaceOLinkClient::GetPropFloat64_Implementation() const
{
	return PropFloat64;
}

void UTbSimpleSimpleArrayInterfaceOLinkClient::SetPropFloat64_Implementation(const TArray<double>& InPropFloat64)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}

	// only send change requests if the value changed -> reduce network load
	if (GetPropFloat64_Implementation() == InPropFloat64)
	{
		return;
	}

	// only send change requests if the value wasn't already sent -> reduce network load
	{
		FScopeLock Lock(&(_SentData->PropFloat64Mutex));
		if (_SentData->PropFloat64 == InPropFloat64)
		{
			return;
		}
	}
	static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "propFloat64");
	m_sink->GetNode()->setRemoteProperty(memberId, InPropFloat64);
	FScopeLock Lock(&(_SentData->PropFloat64Mutex));
	_SentData->PropFloat64 = InPropFloat64;
}

TArray<FString> UTbSimpleSimpleArrayInterfaceOLinkClient::GetPropString_Implementation() const
{
	return PropString;
}

void UTbSimpleSimpleArrayInterfaceOLinkClient::SetPropString_Implementation(const TArray<FString>& InPropString)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
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

TArray<bool> UTbSimpleSimpleArrayInterfaceOLinkClient::FuncBool_Implementation(const TArray<bool>& ParamBool)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return TArray<bool>();
	}
	TPromise<TArray<bool>> Promise;
	Async(EAsyncExecution::Thread,
		[ParamBool, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetSimpleArrayInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{
				if (!arg.value.empty())
				{
					Promise.SetValue(arg.value.get<TArray<bool>>());
				}
				else
				{
					UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Error, TEXT("FuncBool: OLink service returned empty value - should have returned type of TArray<bool>"));
					Promise.SetValue(TArray<bool>());
				}
			};
			static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcBool");
			m_sink->GetNode()->invokeRemote(memberId, {ParamBool}, GetSimpleArrayInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

TArray<int32> UTbSimpleSimpleArrayInterfaceOLinkClient::FuncInt_Implementation(const TArray<int32>& ParamInt)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return TArray<int32>();
	}
	TPromise<TArray<int32>> Promise;
	Async(EAsyncExecution::Thread,
		[ParamInt, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetSimpleArrayInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{
				if (!arg.value.empty())
				{
					Promise.SetValue(arg.value.get<TArray<int32>>());
				}
				else
				{
					UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Error, TEXT("FuncInt: OLink service returned empty value - should have returned type of TArray<int32>"));
					Promise.SetValue(TArray<int32>());
				}
			};
			static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcInt");
			m_sink->GetNode()->invokeRemote(memberId, {ParamInt}, GetSimpleArrayInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

TArray<int32> UTbSimpleSimpleArrayInterfaceOLinkClient::FuncInt32_Implementation(const TArray<int32>& ParamInt32)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return TArray<int32>();
	}
	TPromise<TArray<int32>> Promise;
	Async(EAsyncExecution::Thread,
		[ParamInt32, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetSimpleArrayInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{
				if (!arg.value.empty())
				{
					Promise.SetValue(arg.value.get<TArray<int32>>());
				}
				else
				{
					UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Error, TEXT("FuncInt32: OLink service returned empty value - should have returned type of TArray<int32>"));
					Promise.SetValue(TArray<int32>());
				}
			};
			static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcInt32");
			m_sink->GetNode()->invokeRemote(memberId, {ParamInt32}, GetSimpleArrayInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

TArray<int64> UTbSimpleSimpleArrayInterfaceOLinkClient::FuncInt64_Implementation(const TArray<int64>& ParamInt64)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return TArray<int64>();
	}
	TPromise<TArray<int64>> Promise;
	Async(EAsyncExecution::Thread,
		[ParamInt64, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetSimpleArrayInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{
				if (!arg.value.empty())
				{
					Promise.SetValue(arg.value.get<TArray<int64>>());
				}
				else
				{
					UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Error, TEXT("FuncInt64: OLink service returned empty value - should have returned type of TArray<int64>"));
					Promise.SetValue(TArray<int64>());
				}
			};
			static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcInt64");
			m_sink->GetNode()->invokeRemote(memberId, {ParamInt64}, GetSimpleArrayInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

TArray<float> UTbSimpleSimpleArrayInterfaceOLinkClient::FuncFloat_Implementation(const TArray<float>& ParamFloat)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return TArray<float>();
	}
	TPromise<TArray<float>> Promise;
	Async(EAsyncExecution::Thread,
		[ParamFloat, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetSimpleArrayInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{
				if (!arg.value.empty())
				{
					Promise.SetValue(arg.value.get<TArray<float>>());
				}
				else
				{
					UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Error, TEXT("FuncFloat: OLink service returned empty value - should have returned type of TArray<float>"));
					Promise.SetValue(TArray<float>());
				}
			};
			static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcFloat");
			m_sink->GetNode()->invokeRemote(memberId, {ParamFloat}, GetSimpleArrayInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

TArray<float> UTbSimpleSimpleArrayInterfaceOLinkClient::FuncFloat32_Implementation(const TArray<float>& ParamFloat32)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return TArray<float>();
	}
	TPromise<TArray<float>> Promise;
	Async(EAsyncExecution::Thread,
		[ParamFloat32, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetSimpleArrayInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{
				if (!arg.value.empty())
				{
					Promise.SetValue(arg.value.get<TArray<float>>());
				}
				else
				{
					UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Error, TEXT("FuncFloat32: OLink service returned empty value - should have returned type of TArray<float>"));
					Promise.SetValue(TArray<float>());
				}
			};
			static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcFloat32");
			m_sink->GetNode()->invokeRemote(memberId, {ParamFloat32}, GetSimpleArrayInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

TArray<double> UTbSimpleSimpleArrayInterfaceOLinkClient::FuncFloat64_Implementation(const TArray<double>& ParamFloat)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return TArray<double>();
	}
	TPromise<TArray<double>> Promise;
	Async(EAsyncExecution::Thread,
		[ParamFloat, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetSimpleArrayInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{
				if (!arg.value.empty())
				{
					Promise.SetValue(arg.value.get<TArray<double>>());
				}
				else
				{
					UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Error, TEXT("FuncFloat64: OLink service returned empty value - should have returned type of TArray<double>"));
					Promise.SetValue(TArray<double>());
				}
			};
			static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcFloat64");
			m_sink->GetNode()->invokeRemote(memberId, {ParamFloat}, GetSimpleArrayInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

TArray<FString> UTbSimpleSimpleArrayInterfaceOLinkClient::FuncString_Implementation(const TArray<FString>& ParamString)
{
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));

		return TArray<FString>();
	}
	TPromise<TArray<FString>> Promise;
	Async(EAsyncExecution::Thread,
		[ParamString, &Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc GetSimpleArrayInterfaceStateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{
				if (!arg.value.empty())
				{
					Promise.SetValue(arg.value.get<TArray<FString>>());
				}
				else
				{
					UE_LOG(LogTbSimpleSimpleArrayInterfaceOLinkClient, Error, TEXT("FuncString: OLink service returned empty value - should have returned type of TArray<FString>"));
					Promise.SetValue(TArray<FString>());
				}
			};
			static const auto memberId = ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "funcString");
			m_sink->GetNode()->invokeRemote(memberId, {ParamString}, GetSimpleArrayInterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

bool UTbSimpleSimpleArrayInterfaceOLinkClient::_IsSubscribed() const
{
	return m_sink->IsReady();
}

void UTbSimpleSimpleArrayInterfaceOLinkClient::applyState(const nlohmann::json& fields)
{
	const bool bPropBoolChanged = fields.contains("propBool") && (PropBool != fields["propBool"].get<TArray<bool>>());
	if (bPropBoolChanged)
	{
		PropBool = fields["propBool"].get<TArray<bool>>();
		Execute__GetSignals(this)->OnPropBoolChanged.Broadcast(PropBool);
	}

	const bool bPropIntChanged = fields.contains("propInt") && (PropInt != fields["propInt"].get<TArray<int32>>());
	if (bPropIntChanged)
	{
		PropInt = fields["propInt"].get<TArray<int32>>();
		Execute__GetSignals(this)->OnPropIntChanged.Broadcast(PropInt);
	}

	const bool bPropInt32Changed = fields.contains("propInt32") && (PropInt32 != fields["propInt32"].get<TArray<int32>>());
	if (bPropInt32Changed)
	{
		PropInt32 = fields["propInt32"].get<TArray<int32>>();
		Execute__GetSignals(this)->OnPropInt32Changed.Broadcast(PropInt32);
	}

	const bool bPropInt64Changed = fields.contains("propInt64") && (PropInt64 != fields["propInt64"].get<TArray<int64>>());
	if (bPropInt64Changed)
	{
		PropInt64 = fields["propInt64"].get<TArray<int64>>();
		Execute__GetSignals(this)->OnPropInt64Changed.Broadcast(PropInt64);
	}

	const bool bPropFloatChanged = fields.contains("propFloat") && (PropFloat != fields["propFloat"].get<TArray<float>>());
	if (bPropFloatChanged)
	{
		PropFloat = fields["propFloat"].get<TArray<float>>();
		Execute__GetSignals(this)->OnPropFloatChanged.Broadcast(PropFloat);
	}

	const bool bPropFloat32Changed = fields.contains("propFloat32") && (PropFloat32 != fields["propFloat32"].get<TArray<float>>());
	if (bPropFloat32Changed)
	{
		PropFloat32 = fields["propFloat32"].get<TArray<float>>();
		Execute__GetSignals(this)->OnPropFloat32Changed.Broadcast(PropFloat32);
	}

	const bool bPropFloat64Changed = fields.contains("propFloat64") && (PropFloat64 != fields["propFloat64"].get<TArray<double>>());
	if (bPropFloat64Changed)
	{
		PropFloat64 = fields["propFloat64"].get<TArray<double>>();
		Execute__GetSignals(this)->OnPropFloat64Changed.Broadcast(PropFloat64);
	}

	const bool bPropStringChanged = fields.contains("propString") && (PropString != fields["propString"].get<TArray<FString>>());
	if (bPropStringChanged)
	{
		PropString = fields["propString"].get<TArray<FString>>();
		Execute__GetSignals(this)->OnPropStringChanged.Broadcast(PropString);
	}
}

void UTbSimpleSimpleArrayInterfaceOLinkClient::emitSignal(const std::string& signalName, const nlohmann::json& args)
{
	if (signalName == "sigBool")
	{
		const TArray<bool>& ParamBool = args[0].get<TArray<bool>>();
		Execute__GetSignals(this)->OnSigBoolSignal.Broadcast(ParamBool);
		return;
	}

	if (signalName == "sigInt")
	{
		const TArray<int32>& ParamInt = args[0].get<TArray<int32>>();
		Execute__GetSignals(this)->OnSigIntSignal.Broadcast(ParamInt);
		return;
	}

	if (signalName == "sigInt32")
	{
		const TArray<int32>& ParamInt32 = args[0].get<TArray<int32>>();
		Execute__GetSignals(this)->OnSigInt32Signal.Broadcast(ParamInt32);
		return;
	}

	if (signalName == "sigInt64")
	{
		const TArray<int64>& ParamInt64 = args[0].get<TArray<int64>>();
		Execute__GetSignals(this)->OnSigInt64Signal.Broadcast(ParamInt64);
		return;
	}

	if (signalName == "sigFloat")
	{
		const TArray<float>& ParamFloat = args[0].get<TArray<float>>();
		Execute__GetSignals(this)->OnSigFloatSignal.Broadcast(ParamFloat);
		return;
	}

	if (signalName == "sigFloat32")
	{
		const TArray<float>& ParamFloa32 = args[0].get<TArray<float>>();
		Execute__GetSignals(this)->OnSigFloat32Signal.Broadcast(ParamFloa32);
		return;
	}

	if (signalName == "sigFloat64")
	{
		const TArray<double>& ParamFloat64 = args[0].get<TArray<double>>();
		Execute__GetSignals(this)->OnSigFloat64Signal.Broadcast(ParamFloat64);
		return;
	}

	if (signalName == "sigString")
	{
		const TArray<FString>& ParamString = args[0].get<TArray<FString>>();
		Execute__GetSignals(this)->OnSigStringSignal.Broadcast(ParamString);
		return;
	}
}
