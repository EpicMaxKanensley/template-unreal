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

#include "TbSame2SameEnum2InterfaceOLink.h"
#include "Async/Future.h"
#include "Async/Async.h"
#include "apig/TbSame2.json.adapter.h"
#include "unrealolink.h"
#include "Async/Async.h"
#include "Engine/Engine.h"
#include "ApiGear/Public/ApiGearConnectionManager.h"
#include "Misc/DateTime.h"

using namespace ApiGear::ObjectLink;

namespace TbSame2
{
namespace SameEnum2Interface
{
namespace Private
{
OLinkService::OLinkService()
	: ITbSame2SameEnum2InterfaceInterface()
	, m_node(nullptr)
	, m_isReady(false)
	, Prop1(ETbSame2Enum1::VALUE1)
	, Prop2(ETbSame2Enum2::VALUE1)
{
	if (GEngine != nullptr)
	{
		UApiGearConnectionManager* AGCM = GEngine->GetEngineSubsystem<UApiGearConnectionManager>();
		AGCM->GetOLinkConnection()->Connect();
		AGCM->GetOLinkConnection()->linkObjectSource(olinkObjectName());
	}
	m_node = ClientRegistry::get().addObjectSink(this);
}

OLinkService::~OLinkService()
{
	ClientRegistry::get().removeObjectSink(this);
	if (GEngine != nullptr)
	{
		UApiGearConnectionManager* AGCM = GEngine->GetEngineSubsystem<UApiGearConnectionManager>();
		AGCM->GetOLinkConnection()->unlinkObjectSource(olinkObjectName());
	}
	m_isReady = false;
	m_node = nullptr;
}

FTbSame2SameEnum2InterfaceSig1Delegate& OLinkService::GetSig1SignalDelegate()
{
	return Sig1Signal;
}

FTbSame2SameEnum2InterfaceSig2Delegate& OLinkService::GetSig2SignalDelegate()
{
	return Sig2Signal;
}

ETbSame2Enum1 OLinkService::GetProp1() const
{
	return Prop1;
}

void OLinkService::SetProp1(const ETbSame2Enum1& InProp1)
{
	if (!m_node)
	{
		return;
	}
	m_node->setRemoteProperty("tb.same2.SameEnum2Interface/prop1", InProp1);
}

FTbSame2SameEnum2InterfaceProp1ChangedDelegate& OLinkService::GetProp1ChangedDelegate()
{
	return Prop1Changed;
}
ETbSame2Enum2 OLinkService::GetProp2() const
{
	return Prop2;
}

void OLinkService::SetProp2(const ETbSame2Enum2& InProp2)
{
	if (!m_node)
	{
		return;
	}
	m_node->setRemoteProperty("tb.same2.SameEnum2Interface/prop2", InProp2);
}

FTbSame2SameEnum2InterfaceProp2ChangedDelegate& OLinkService::GetProp2ChangedDelegate()
{
	return Prop2Changed;
}

ETbSame2Enum1 OLinkService::Func1(const ETbSame2Enum1& Param1)
{
	if (!m_node)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(olinkObjectName().c_str()));
		return ETbSame2Enum1::VALUE1;
	}
	TPromise<ETbSame2Enum1> Promise;
	Async(EAsyncExecution::Thread,
		[Param1, &Promise, this]()
		{
			InvokeReplyFunc GetSameEnum2InterfaceStateFunc = [&Promise](InvokeReplyArg arg)
			{ Promise.SetValue(arg.value.get<ETbSame2Enum1>()); };
			m_node->invokeRemote("tb.same2.SameEnum2Interface/func1", {Param1}, GetSameEnum2InterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

ETbSame2Enum1 OLinkService::Func2(const ETbSame2Enum1& Param1, const ETbSame2Enum2& Param2)
{
	if (!m_node)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(olinkObjectName().c_str()));
		return ETbSame2Enum1::VALUE1;
	}
	TPromise<ETbSame2Enum1> Promise;
	Async(EAsyncExecution::Thread,
		[Param1, Param2, &Promise, this]()
		{
			InvokeReplyFunc GetSameEnum2InterfaceStateFunc = [&Promise](InvokeReplyArg arg)
			{ Promise.SetValue(arg.value.get<ETbSame2Enum1>()); };
			m_node->invokeRemote("tb.same2.SameEnum2Interface/func2", {Param1, Param2}, GetSameEnum2InterfaceStateFunc);
		});

	return Promise.GetFuture().Get();
}

void OLinkService::applyState(const nlohmann::json& fields)
{
	if (fields.contains("prop1"))
	{
		if (Prop1 != fields["prop1"].get<ETbSame2Enum1>())
		{
			Prop1 = fields["prop1"].get<ETbSame2Enum1>();
			Prop1Changed.Broadcast(Prop1);
		}
	}
	if (fields.contains("prop2"))
	{
		if (Prop2 != fields["prop2"].get<ETbSame2Enum2>())
		{
			Prop2 = fields["prop2"].get<ETbSame2Enum2>();
			Prop2Changed.Broadcast(Prop2);
		}
	}
}

std::string OLinkService::olinkObjectName()
{
	return "tb.same2.SameEnum2Interface";
}

void OLinkService::olinkOnSignal(std::string name, nlohmann::json args)
{
	std::string path = Name::pathFromName(name);
	if (path == "sig1")
	{
		Sig1Signal.Broadcast(args[0].get<ETbSame2Enum1>());
		return;
	}
	if (path == "sig2")
	{
		Sig2Signal.Broadcast(args[0].get<ETbSame2Enum1>(), args[1].get<ETbSame2Enum2>());
		return;
	}
}

void OLinkService::olinkOnPropertyChanged(std::string name, nlohmann::json value)
{
	std::string path = Name::pathFromName(name);
	applyState({{path, value}});
}

void OLinkService::olinkOnInit(std::string name, nlohmann::json props, IClientNode* node)
{
	m_isReady = true;
	m_node = node;
	applyState(props);
	// call isReady();
}

void OLinkService::olinkOnRelease()
{
	m_isReady = false;
	m_node = nullptr;
}

} // namespace Private
} // namespace SameEnum2Interface
} // namespace TbSame2