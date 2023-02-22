{{- /* Copyright Epic Games, Inc. All Rights Reserved */ -}}
/**{{ template "copyright" }}*/
{{- $ModuleName := Camel .Module.Name}}
{{- $IfaceName := Camel .Interface.Name }}
{{- $Category := printf "ApiGear|%s|%s" $ModuleName $IfaceName }}
{{- $DisplayName := printf "%s%s" $ModuleName $IfaceName }}
{{- $Class := printf "U%sOLinkClient" $DisplayName}}
{{- $Iface := printf "%s%s" $ModuleName $IfaceName }}
{{- $ifaceId := printf "%s.%s" .Module.Name .Interface.Name}}

////////////////////////////////
// WARNING AUTOGENERATED
// DO NOT MODIFY
///////////////////////////////

#include "Generated/OLink/{{$Iface}}OLinkClient.h"
#include "Async/Future.h"
#include "Async/Async.h"
#include "Generated/api/{{$ModuleName}}.json.adapter.h"
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
{{ if .Interface.Description }}
/**
   \brief {{.Interface.Description}}
*/
{{- end }}
{{$Class}}::{{$Class}}()
	: I{{$ModuleName}}{{$IfaceName}}Interface()
{
	m_sink = std::make_shared<FUnrealOLinkSink>("{{$ifaceId}}");
}

void {{$Class}}::Initialize(FSubsystemCollectionBase& Collection)
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

void {{$Class}}::Deinitialize()
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
{{- if len .Interface.Signals }}{{ nl }}{{ end }}
{{- range $i, $e := .Interface.Signals }}
{{- if $i }}{{nl}}{{ end }}
void {{$Class}}::Broadcast{{Camel .Name}}_Implementation({{ueParams "" .Params}})
{
	{{Camel .Name}}Signal.Broadcast({{ueVars "" .Params }});
}

F{{$Iface}}{{Camel .Name}}Delegate& {{$Class}}::Get{{Camel .Name}}SignalDelegate()
{
	return {{Camel .Name}}Signal;
}
{{- end }}
{{- if len .Interface.Properties }}{{ nl }}{{ end }}
{{- range $i, $e := .Interface.Properties }}
{{- if $i }}{{nl}}{{ end }}
void {{$Class}}::Broadcast{{Camel .Name}}Changed_Implementation({{ueParam "In" .}})
{
	{{ueVar "" .}} = {{ueVar "In" .}};
	{{Camel .Name}}Changed.Broadcast({{ueVar "In" .}});
}

{{ueReturn "" .}} {{$Class}}::Get{{Camel .Name}}_Implementation() const
{
	return {{ueVar "" .}};
}

void {{$Class}}::Set{{Camel .Name}}_Implementation({{ueParam "In" .}})
{
	if (!m_sink->IsReady())
	{
		return;
	}
	m_sink->GetNode()->setRemoteProperty(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "{{.Name}}"), {{ueVar "In" .}});
}

F{{$Iface}}{{Camel .Name}}ChangedDelegate& {{$Class}}::Get{{Camel .Name}}ChangedDelegate()
{
	return {{Camel .Name}}Changed;
}
{{- end }}
{{- if len .Interface.Operations }}{{ nl }}{{ end }}
{{- range $i, $e := .Interface.Operations }}
{{- if $i }}{{nl}}{{ end }}
{{- if .Description }}
/**
   \brief {{.Description}}
*/
{{- end }}
{{- $returnVal := (ueReturn "" .Return)}}
{{$returnVal}} {{$Class}}::{{Camel .Name}}_Implementation({{ueParams "" .Params}})
{
	{{- if .Return.IsVoid }}
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return;
	}
	ApiGear::ObjectLink::InvokeReplyFunc Get{{$IfaceName}}StateFunc = [this](ApiGear::ObjectLink::InvokeReplyArg arg) {};
	m_sink->GetNode()->invokeRemote(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "{{.Name}}"), { {{- ueVars "" .Params -}} }, Get{{$IfaceName}}StateFunc);
	{{- else }}
	if (!m_sink->IsReady())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has no node"), UTF8_TO_TCHAR(m_sink->olinkObjectName().c_str()));
		return {{ ueDefault "" .Return }};
	}
	TPromise<{{$returnVal}}> Promise;
	Async(EAsyncExecution::Thread,
		[{{ueVars "" .Params }}{{if len .Params}}, {{ end }}&Promise, this]()
		{
			ApiGear::ObjectLink::InvokeReplyFunc Get{{$IfaceName}}StateFunc = [&Promise](ApiGear::ObjectLink::InvokeReplyArg arg)
			{ Promise.SetValue(arg.value.get<{{$returnVal}}>()); };
			m_sink->GetNode()->invokeRemote(ApiGear::ObjectLink::Name::createMemberId(m_sink->olinkObjectName(), "{{.Name}}"), { {{- ueVars "" .Params -}} }, Get{{$IfaceName}}StateFunc);
		});

	return Promise.GetFuture().Get();
	{{- end }}
}
{{- end }}

void {{$Class}}::applyState(const nlohmann::json& fields)
{
{{- range .Interface.Properties }}
	if (fields.contains("{{.Name}}"))
	{
		if ({{ueVar "" .}} != fields["{{.Name}}"].get<{{ueReturn "" .}}>())
		{
			{{ueVar "" .}} = fields["{{.Name}}"].get<{{ueReturn "" .}}>();
			Execute_Broadcast{{Camel .Name}}Changed(this, {{ueVar "" .}});
		}
	}
{{- end }}
}

void {{$Class}}::emitSignal(const std::string& signalName, const nlohmann::json& args)
{
{{- range .Interface.Signals }}
	if (signalName == "{{.Name}}")
	{
		Execute_Broadcast{{Camel .Name}}(this
		{{- range $idx, $elem := .Params -}}
			, args[{{$idx}}].get<{{ueReturn "" .}}>()
		{{- end }});
		return;
	}
{{- end }}
}
