// Fill out your copyright notice in the Description page of Project Settings.


#include "HelperWindowPluginMenu.h"

#include "HWPMeshActor.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SHelperWindowPluginMenu::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SButton)
					.Text(FText::FromString("Spawn Actor other"))
					.OnClicked(this, &SHelperWindowPluginMenu::SpawnMeshActor)
				]
				+ SVerticalBox::Slot()
				[
					TextBlock = SNew(STextBlock)
					.Text(FText::FromString("ffffffff"))
				]
				+ SVerticalBox::Slot()
				[
					CheckBox = SNew(SCheckBox)
				]
			]
	];

	
}

FReply SHelperWindowPluginMenu::SpawnMeshActor()
{
	UE_LOG(LogTemp, Warning, TEXT("Function : I DID IT"));
	return FReply::Handled();
}

void SHelperWindowPluginMenu::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime,
	const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("Function : Update"));

	for (auto Element : GEditor->GetSelectedActors())
	{
		AHWPMeshActor* g = Cast<AHWPMeshActor>(Element);
		if (!g) continue;

		CheckBox.Get().SetIsChecked(g->SetIsEnabled())
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
