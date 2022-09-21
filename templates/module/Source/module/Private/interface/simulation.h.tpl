{{- /* Copyright Epic Games, Inc. All Rights Reserved */ -}}
/**{{ template "copyright" }}*/
{{- $ModuleName := Camel .Module.Name}}
{{- $IfaceName := Camel .Interface.Name }}
{{- $Class := "SimulationService" }}
{{- $Iface := printf "%s%s" $ModuleName $IfaceName }}
#pragma once

#include "apig/{{$ModuleName}}_apig.h"

namespace {{$ModuleName}}
{
namespace {{Camel .Interface.Name}}
{
namespace Private
{

class {{$Class}} : public I{{$Iface}}Interface
{
public:
	explicit {{$Class}}();
	virtual ~{{$Class}}();

	// signals
{{- range .Interface.Signals }}
	F{{$Iface}}{{Camel .Name}}Delegate {{Camel .Name}}Signal;
	F{{$Iface}}{{Camel .Name}}Delegate& Get{{Camel .Name}}SignalDelegate() override;
{{ end }}
{{- range .Interface.Properties }}
	F{{$Iface}}{{Camel .Name}}ChangedDelegate {{Camel .Name}}Changed;
	F{{$Iface}}{{Camel .Name}}ChangedDelegate& Get{{Camel .Name}}ChangedDelegate() override;
{{ end }}
	// properties
{{- range .Interface.Properties }}
	{{ueReturn "" .}} Get{{Camel .Name}}() const override;
	void Set{{Camel .Name}}({{ueParam "" .}}) override;
{{ end }}
	// operations
{{- range .Interface.Operations }}
	{{ueReturn "" .Return}} {{Camel .Name}}({{ueParams "" .Params}}) override;
{{ end }}
private:
	// properties - local copy
{{- range .Interface.Properties }}
{{- if .Description }}
	/** {{ .Description }} */
{{- end }}
	{{ueReturn "" .}} {{ueVar "" .}};
{{- end }}
};

} // namespace Private
} // namespace {{Camel .Interface.Name}}
} // namespace {{$ModuleName}}