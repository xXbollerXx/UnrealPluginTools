// Fill out your copyright notice in the Description page of Project Settings.


#include "HelperWindowPluginMenu.h"

#include "EditorLevelUtils.h"
#include "HWPMeshActor.h"
#include "Selection.h"
#include "SlateOptMacros.h"

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
		.OnCheckStateChanged(this, &SHelperWindowPluginMenu::OnCheckboxChanged)
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

	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World)
	{
		UE_LOG(LogTemp, Warning, TEXT("Function : Got world"));

		World->SpawnActor(AHWPMeshActor::StaticClass());
	}
	return FReply::Handled();
}

void SHelperWindowPluginMenu::OnCheckboxChanged(ECheckBoxState CheckBoxState)
{
	for (FSelectionIterator It(GEditor->GetSelectedActorIterator()); It; ++It)
	{
		AHWPMeshActor* Actor = Cast<AHWPMeshActor>(*It);
		if (Actor)
		{
			Actor->SetIsEnabled(CheckBoxState == ECheckBoxState::Checked ? true : false);
		}
	}
}

void SHelperWindowPluginMenu::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime,
                                   const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);


	ActorNameTextBlock->SetVisibility(EVisibility::Visible);
	CheckBox->SetVisibility(EVisibility::Visible);
	
	AHWPMeshActor* FirstInstance = nullptr;
	for (FSelectionIterator It(GEditor->GetSelectedActorIterator()); It; ++It)
	{
		AHWPMeshActor* Actor = Cast<AHWPMeshActor>(*It);
		UE_LOG(LogTemp, Warning, TEXT("Function : Actor name : %s"), *Actor->GetActorLabel());

		if (!Actor)
		{
			ActorNameTextBlock->SetVisibility(EVisibility::Collapsed);
			CheckBox->SetVisibility(EVisibility::Collapsed);
			break;
		}

		if (FirstInstance)
		{
			ActorNameTextBlock->SetVisibility(EVisibility::Collapsed);
			
			if (FirstInstance->GetIsEnabled() != Actor->GetIsEnabled())
			{
				CheckBox->SetIsChecked( ECheckBoxState::Undetermined);
			}
		}
		else
		{
			FirstInstance = Actor;
			ActorNameTextBlock->SetText(FText::FromString(Actor->GetActorLabel()));
			CheckBox->SetIsChecked(Actor->GetIsEnabled() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
		}
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
