// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "HelperWindowPluginStyle.h"

class FHelperWindowPluginCommands : public TCommands<FHelperWindowPluginCommands>
{
public:

	FHelperWindowPluginCommands()
		: TCommands<FHelperWindowPluginCommands>(TEXT("HelperWindowPlugin"), NSLOCTEXT("Contexts", "HelperWindowPlugin", "HelperWindowPlugin Plugin"), NAME_None, FHelperWindowPluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};