{{- /* Copyright Epic Games, Inc. All Rights Reserved */ -}}
/**{{ template "copyright" }}*/
{{- $ModuleName := Camel .Module.Name}}
{{- $DisplayName := printf "%s%s" $ModuleName (Camel .Interface.Name) }}
{{- $IfaceName := Camel .Interface.Name }}
{{- $Class := printf "U%s" $DisplayName}}
{{- $Iface := printf "%s%s" $ModuleName $IfaceName }}

#include "{{$Iface}}.h"

{{$Class}}::~{{$Class}}() = default;

{{- range .Interface.Signals }}

void {{$Class}}::Broadcast{{Camel .Name}}_Implementation({{ueParams "" .Params}})
{
	{{Camel .Name}}Signal.Broadcast({{ueVars "" .Params }});
}

F{{$Iface}}{{Camel .Name}}Delegate& {{$Class}}::Get{{Camel .Name}}SignalDelegate()
{
	return {{Camel .Name}}Signal;
}
{{- end }}
{{- range .Interface.Properties }}

void {{$Class}}::Broadcast{{Camel .Name}}Changed_Implementation({{ueParam "In" .}})
{
	{{Camel .Name}}Changed.Broadcast({{ueVar "In" .}});
}

{{ueReturn "" .}} {{$Class}}::Get{{Camel .Name}}_Implementation() const
{
	return {{ueVar "" .}};
}

void {{$Class}}::Set{{Camel .Name}}_Implementation({{ueParam "In" .}})
{
	if ({{ueVar "" .}} != {{ueVar "In" .}})
	{
		{{ueVar "" .}} = {{ueVar "In" .}};
		Execute_Broadcast{{Camel .Name}}Changed(this, {{ueVar "" .}});
	}
}

F{{$Iface}}{{Camel .Name}}ChangedDelegate& {{$Class}}::Get{{Camel .Name}}ChangedDelegate()
{
	return {{Camel .Name}}Changed;
}
{{- else }}
{{- end }}
{{- range .Interface.Operations }}{{ nl }}
{{- if .Description }}
/**
   \brief {{.Description}}
*/
{{- end }}
{{ueReturn "" .Return}} {{$Class}}::{{Camel .Name}}_Implementation({{ueParams "" .Params}})
{
	{{- range .Params }}
	(void){{ueVar "" .}};
	{{- end }}
	// do business logic here
	{{- if not .Return.IsVoid }}
	return {{ueDefault "" .Return}};
	{{- end }}
}
{{- else }}
{{- end }}