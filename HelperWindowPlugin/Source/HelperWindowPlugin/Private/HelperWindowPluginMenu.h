// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class HELPERWINDOWPLUGIN_API SHelperWindowPluginMenu : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SHelperWindowPluginMenu)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);


	FReply SpawnMeshActor();

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	TSharedRef<SCheckBox> CheckBox;

	TSharedRef<STextBlock> TextBlock;
};
