{{- /* Copyright Epic Games, Inc. All Rights Reserved */ -}}
/**{{ template "copyright" }}*/
{{- $ModuleName := Camel .Module.Name}}
{{- $IfaceName := Camel .Interface.Name }}
{{- $DisplayName := printf "%s%s" $ModuleName $IfaceName }}
{{- $Class := printf "U%sSimulationClient" $DisplayName}}
{{- $Iface := printf "%s%s" $ModuleName $IfaceName }}
{{- $ifaceId := printf "%s/%s" .Module.Name .Interface.Name}}

////////////////////////////////
// WARNING AUTOGENERATED
// DO NOT MODIFY
///////////////////////////////

#include "{{$Iface}}SimulationClient.h"
#include "Generated/api/{{$ModuleName}}.json.adapter.h"
#include "ApiGear/Public/ApiGearConnectionManager.h"
#include "unrealsimulation.h"
#include "Async/Async.h"
#include "Engine/Engine.h"

using namespace ApiGear::JSONRPC;

{{- if .Interface.Description }}
/**
   \brief {{ .Interface.Description }}
*/
{{- end }}
{{$Class}}::{{$Class}}()
	: I{{$ModuleName}}{{Camel .Interface.Name}}Interface()
{
}

void {{$Class}}::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UApiGearConnectionManager* AGCM = nullptr;
	if (GEngine != nullptr)
	{
		AGCM = GEngine->GetEngineSubsystem<UApiGearConnectionManager>();
	}
	NotifyRequestFunc {{$IfaceName}}StateChangedFunc = [this](NotifyRequestArg arg)
	{
		const json fields = arg.params;
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
	};
	if (AGCM != nullptr)
	{
		AGCM->GetSimulationConnection()->Connect();
		AGCM->GetSimulationConnection()->onNotifyState("{{$ifaceId}}", {{$IfaceName}}StateChangedFunc);
	}

	CallResponseFunc Get{{$IfaceName}}StateFunc = [this](CallResponseArg arg)
	{
		if (arg.result.size() != 1)
		{
			return;
		}
		const json fields = arg.result;
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
	};
	if (AGCM != nullptr)
	{
		AGCM->GetSimulationConnection()->doFetchState("{{$ifaceId}}", Get{{$IfaceName}}StateFunc);
	}

	// register notification callback functions, signal/event -> fcn
{{- range .Interface.Signals }}
	NotifyRequestFunc {{.Name}}Func = [this](NotifyRequestArg arg)
	{
	{{- if len .Params }}
		const json fields = arg.params;
		if (
	{{- range $idx, $elem := .Params }}
		{{- if $idx}} && {{ end -}}
		fields.contains("{{.Name}}")
	{{- end }})
		{
			Execute_Broadcast{{Camel .Name}}(this,
		{{- range $idx, $elem := .Params }}
			    {{- if $idx }},{{ end }} fields["{{.Name}}"].get<{{ueReturn "" .}}>()
		{{- end -}}
			);
		}
	{{- else }}
		Execute_Broadcast{{Camel .Name}}(this);
	{{- end }}
	};
	if (AGCM != nullptr)
	{
		AGCM->GetSimulationConnection()->onNotify("{{$ifaceId}}#{{.Name}}", {{.Name}}Func);
	}
{{ else }}
{{ end -}}
}

void {{$Class}}::Deinitialize()
{
	Super::Deinitialize();

	if (GEngine != nullptr)
	{
		UApiGearConnectionManager* AGCM = GEngine->GetEngineSubsystem<UApiGearConnectionManager>();
		AGCM->GetSimulationConnection()->RemoveOnNotifyState("{{$ifaceId}}");
		// unregister notification callback functions
{{- range .Interface.Signals }}
		AGCM->GetSimulationConnection()->RemoveOnNotify("{{$ifaceId}}#{{.Name}}");
{{- end }}
	}
}
{{ range .Interface.Signals }}
void {{$Class}}::Broadcast{{Camel .Name}}_Implementation({{ueParams "" .Params}})
{
	{{Camel .Name}}Signal.Broadcast({{ueVars "" .Params }});
}

F{{$Iface}}{{Camel .Name}}Delegate& {{$Class}}::Get{{Camel .Name}}SignalDelegate()
{
	return {{Camel .Name}}Signal;
}
{{ end }}
{{- range .Interface.Properties }}
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
	Params params;
	params["{{.Name}}"] = {{ueVar "In" .}};
	if (GEngine != nullptr)
	{
		UApiGearConnectionManager* AGCM = GEngine->GetEngineSubsystem<UApiGearConnectionManager>();
		AGCM->GetSimulationConnection()->doCall("{{$ifaceId}}", "_set", params);
	}
}

F{{$Iface}}{{Camel .Name}}ChangedDelegate& {{$Class}}::Get{{Camel .Name}}ChangedDelegate()
{
	return {{Camel .Name}}Changed;
}
{{ end }}

{{- range .Interface.Operations }}
{{- if .Description }}
/**
 * \brief {{.Description}}
 */
{{- end }}
{{- $returnVal := (ueReturn "" .Return)}}
{{$returnVal}} {{$Class}}::{{Camel .Name}}_Implementation({{ueParams "" .Params}})
{
	Params params;
	{{- range .Params }}
	params["{{.Name}}"] = {{ueVar "" .}};
	{{- end }}

	{{- if .Return.IsVoid }}
	if (GEngine != nullptr)
	{
		UApiGearConnectionManager* AGCM = GEngine->GetEngineSubsystem<UApiGearConnectionManager>();
		AGCM->GetSimulationConnection()->doCall("{{$ifaceId}}", "{{.Name}}", params);
	}
	{{- else }}
	TPromise<{{$returnVal}}> Promise;
	Async(EAsyncExecution::Thread,
		[params, &Promise]()
		{
			CallResponseFunc Get{{$IfaceName}}StateFunc = [&Promise](CallResponseArg arg)
			{ Promise.SetValue(arg.result.get<{{$returnVal}}>()); };
			if (GEngine != nullptr)
			{
				UApiGearConnectionManager* AGCM = GEngine->GetEngineSubsystem<UApiGearConnectionManager>();
				AGCM->GetSimulationConnection()->doCall("{{$ifaceId}}", "{{.Name}}", params, Get{{$IfaceName}}StateFunc);
			}
		});

	return Promise.GetFuture().Get();
	{{- end }}
}
{{ end }}