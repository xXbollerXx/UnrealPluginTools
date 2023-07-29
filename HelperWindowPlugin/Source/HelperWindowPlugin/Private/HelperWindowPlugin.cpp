// Copyright Epic Games, Inc. All Rights Reserved.

#include "HelperWindowPlugin.h"
#include "HelperWindowPluginStyle.h"
#include "HelperWindowPluginCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "ToolMenus.h"

static const FName HelperWindowPluginTabName("HelperWindowPlugin");

#define LOCTEXT_NAMESPACE "FHelperWindowPluginModule"

void FHelperWindowPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FHelperWindowPluginStyle::Initialize();
	FHelperWindowPluginStyle::ReloadTextures();

	FHelperWindowPluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FHelperWindowPluginCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FHelperWindowPluginModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FHelperWindowPluginModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(HelperWindowPluginTabName, FOnSpawnTab::CreateRaw(this, &FHelperWindowPluginModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FHelperWindowPluginTabTitle", "HelperWindowPlugin"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FHelperWindowPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FHelperWindowPluginStyle::Shutdown();

	FHelperWindowPluginCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(HelperWindowPluginTabName);
}

TSharedRef<SDockTab> FHelperWindowPluginModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FHelperWindowPluginModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("HelperWindowPlugin.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(STextBlock)
					.Text(WidgetText)
				]
				+ SVerticalBox::Slot()
				[
					SNew(SButton)
					.Text(FText::FromString("Spawn Actor"))
					//.ClickMethod(EButtonClickMethod::MouseUp)
					.OnClicked_Raw(this, &FHelperWindowPluginModule::SpawnMeshActor)
				]
			]
		];
}

FReply FHelperWindowPluginModule::SpawnMeshActor()
{
	UE_LOG(LogTemp, Warning, TEXT("Function : I DID IT"));
	return FReply::Handled();
}

void FHelperWindowPluginModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(HelperWindowPluginTabName);
}

void FHelperWindowPluginModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FHelperWindowPluginCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FHelperWindowPluginCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHelperWindowPluginModule, HelperWindowPlugin)