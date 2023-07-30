// Fill out your copyright notice in the Description page of Project Settings.


#include "HelperWindowPluginMenu.h"

#include "HWPMeshActor.h"
#include "Selection.h"
#include "SlateOptMacros.h"
#include "Slate/Private/Widgets/Views/SListPanel.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SHelperWindowPluginMenu::Construct(const FArguments& InArgs)
{


	TSharedRef<SHorizontalBox> TextHorizontalBox = SNew(SHorizontalBox);
	TextHorizontalBox->AddSlot()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Actor Name"))
	];

	TextHorizontalBox->AddSlot()
	[
		SAssignNew(ActorNameTextBlock, STextBlock)
		.Text(FText::FromString("TESTNAME"))
	];


	
	TSharedRef<SHorizontalBox> CheckHorizontalBox = SNew(SHorizontalBox);
	CheckHorizontalBox->AddSlot()
	[
		SNew(STextBlock)
		.Text(FText::FromString("IsEnabled"))
	];

	CheckHorizontalBox->AddSlot()
	[
		SAssignNew(CheckBox, SCheckBox)
	];


	
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Fill)
		.AutoHeight()
		.Padding(5)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
					[
						SNew(SButton)
						.Text(FText::FromString("Spawn Actor other"))
						.OnClicked(this, &SHelperWindowPluginMenu::SpawnMeshActor)
					]
			]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(5)
			[
				TextHorizontalBox
			]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(5)
			[
				CheckHorizontalBox
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

	bool IsUndetermined = false;
	AHWPMeshActor* PreActor = nullptr;

	ActorNameTextBlock->SetVisibility(EVisibility::Visible);
	CheckBox->SetVisibility(EVisibility::Visible);
	for (FSelectionIterator It(GEditor->GetSelectedActorIterator()); It; ++It)
	{
		AHWPMeshActor* Actor = Cast<AHWPMeshActor>(*It);
		if (!Actor)
		{
			ActorNameTextBlock->SetVisibility(EVisibility::Collapsed);
			CheckBox->SetVisibility(EVisibility::Collapsed);
			continue;
		}
		
		if (PreActor && PreActor->IsEnabled != Actor->IsEnabled)
		{
			IsUndetermined = true;
			ActorNameTextBlock->SetVisibility(EVisibility::Collapsed);
			CheckBox->SetIsChecked( ECheckBoxState::Undetermined);
		}
		
		if (!IsUndetermined)
		{
			ActorNameTextBlock->SetText(FText::FromString(Actor->GetActorLabel()));
			CheckBox->SetIsChecked(Actor->IsEnabled ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
		}
		
	}

	
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
