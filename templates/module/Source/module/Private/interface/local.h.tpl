{{- /* Copyright Epic Games, Inc. All Rights Reserved */ -}}
{{- $ModuleName := Camel .Module.Name}}
{{- $IfaceName := Camel .Interface.Name }}
{{- $Category := printf "ApiGear|%s|%s" $ModuleName $IfaceName }}
{{- $DisplayName := printf "%s%s" $ModuleName $IfaceName }}
{{- $Class := "LocalService" }}
{{- $Iface := printf "%s%s" $ModuleName $IfaceName }}
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
#pragma once

#include "apig/{{$ModuleName}}_apig.h"

namespace {{$ModuleName}}
{
namespace {{$IfaceName}}
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
	// properties - local copy - use setter functions to emit changed signals
{{- range .Interface.Properties }}
{{- if .Description }}
	/** {{.Description}} */
{{- end }}
	{{ueReturn "" .}} {{ueVar "" .}};
{{- end }}
};

} // namespace Private
} // namespace {{$IfaceName}}
} // namespace {{$ModuleName}}