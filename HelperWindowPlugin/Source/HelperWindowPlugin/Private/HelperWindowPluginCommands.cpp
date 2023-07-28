// Copyright Epic Games, Inc. All Rights Reserved.

#include "HelperWindowPluginCommands.h"

#define LOCTEXT_NAMESPACE "FHelperWindowPluginModule"

void FHelperWindowPluginCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "HelperWindowPlugin", "Bring up HelperWindowPlugin window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
