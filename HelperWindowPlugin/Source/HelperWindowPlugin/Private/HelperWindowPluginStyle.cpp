// Copyright Epic Games, Inc. All Rights Reserved.

#include "HelperWindowPluginStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FHelperWindowPluginStyle::StyleInstance = nullptr;

void FHelperWindowPluginStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FHelperWindowPluginStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FHelperWindowPluginStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("HelperWindowPluginStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FHelperWindowPluginStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("HelperWindowPluginStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("HelperWindowPlugin")->GetBaseDir() / TEXT("Resources"));

	Style->Set("HelperWindowPlugin.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FHelperWindowPluginStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FHelperWindowPluginStyle::Get()
{
	return *StyleInstance;
}
