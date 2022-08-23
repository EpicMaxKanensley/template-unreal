// Copyright Epic Games, Inc. All Rights Reserved
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FReply;
class FText;
class SDockTab;

class FApiGearEditorModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void PluginButtonClicked();

	FReply OLinkConnectButtonClicked();
	FReply OLinkDisconnectButtonClicked();
	FText OLinkConnectionStatus() const;

	FReply SimulationConnectButtonClicked();
	FReply SimulationDisconnectButtonClicked();
	FText SimulationConnectionStatus() const;

private:
	void RegisterMenus();
	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

	TSharedPtr<class FUICommandList> PluginCommands;

	/** Handle to the test dll we will load */
	void* FApiGearEditorModule;
};
