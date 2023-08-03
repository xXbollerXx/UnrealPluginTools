// Fill out your copyright notice in the Description page of Project Settings.


#include "HelperWindowPluginMenu.h"

#include "EditorLevelUtils.h"
#include "HWPMeshActor.h"
#include "LevelEditorViewport.h"
#include "PropertyCustomizationHelpers.h"
#include "Selection.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

const FSoftObjectPath SHelperWindowPluginMenu::BasicCube("/Engine/BasicShapes/Cube", "Cube", {});
const FSoftObjectPath SHelperWindowPluginMenu::BasicMaterial("/Engine/BasicShapes/BasicShapeMaterial", "BasicShapeMaterial", {});


void SHelperWindowPluginMenu::Construct(const FArguments& InArgs)
{
	StaticMesh = LoadObject<UStaticMesh>(nullptr, *BasicCube.ToString());
	MaterialInterface = LoadObject<UMaterialInterface>(nullptr, *BasicMaterial.ToString());


	TSharedRef<SHorizontalBox> TextHorizontalBox = SNew(SHorizontalBox);
	TextHorizontalBox->AddSlot()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Actor Name"))
	];

	TextHorizontalBox->AddSlot()
	[
		SAssignNew(ActorNameTextBlock, STextBlock)
		.Text(FText::FromString(""))
	];


	TSharedRef<SHorizontalBox> CheckHorizontalBox = SNew(SHorizontalBox);
	CheckHorizontalBox->AddSlot()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Actor Can Be Damaged"))
	];

	CheckHorizontalBox->AddSlot()
	[
		SAssignNew(CanBeDamagedCheckBox, SCheckBox)
		.OnCheckStateChanged(this, &SHelperWindowPluginMenu::OnCheckboxChanged)
	];

	TSharedRef<SVerticalBox> DetailsPanel = SNew(SVerticalBox)
	+ SVerticalBox::Slot()
	.HAlign(HAlign_Center)
	.AutoHeight()
	//.Padding(15)
		[
			SNew(STextBlock)
			.Text(FText::FromString("Details"))
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
		];


	TSharedRef<SVerticalBox> SpawnActorDetails = SNew(SVerticalBox)
	+ SVerticalBox::Slot()
	.HAlign(HAlign_Center)
	.AutoHeight()
	.Padding(15)
	[
		SNew(STextBlock)
		.Text(FText::FromString("Spawn New Actor Details"))
	]
	+ SVerticalBox::Slot()
	.AutoHeight()
	.Padding(5)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			[
				SNew(STextBlock)
				.Text(FText::FromString("Mesh"))
			]
			+SHorizontalBox::Slot()
			[
				SNew(SObjectPropertyEntryBox)
				.DisplayBrowse(true)
				.DisplayThumbnail(true)
				.DisplayUseSelected(true)
				.AllowedClass(UStaticMesh::StaticClass())
				.AllowClear(true)
				.ObjectPath(this, &SHelperWindowPluginMenu::GetCurrentStaticMeshPath)
				.OnObjectChanged(this, &SHelperWindowPluginMenu::OnStaticMeshSelected)
				
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(5)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			[
				SNew(STextBlock)
				.Text(FText::FromString("Material"))
			]
			+SHorizontalBox::Slot()
			[
				SNew(SObjectPropertyEntryBox)
				.DisplayBrowse(true)
				.DisplayThumbnail(true)
				.DisplayUseSelected(true)
				.AllowedClass(UMaterialInterface::StaticClass())
				.AllowClear(true)
				.ObjectPath(this, &SHelperWindowPluginMenu::GetCurrentMaterialInterfacePath)
				.OnObjectChanged(this, &SHelperWindowPluginMenu::OnMaterialInterfaceSelected)
			]

	]
	+ SVerticalBox::Slot()
	.HAlign(HAlign_Center)
	.AutoHeight()
	.Padding(5)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
				[
					SNew(SButton)
					.Text(FText::FromString("Spawn Actor"))
					.OnClicked(this, &SHelperWindowPluginMenu::SpawnMeshActor)
				]
		];



	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Fill)
		.AutoHeight()
		.Padding(15)
			[
				DetailsPanel
			]
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Fill)
		.AutoHeight()
		.Padding(15)
			[
				SpawnActorDetails
			]
	];
}

FReply SHelperWindowPluginMenu::SpawnMeshActor()
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (World)
	{
		AHWPMeshActor* MeshActor = World->SpawnActor<AHWPMeshActor>(AHWPMeshActor::StaticClass());
		
		MeshActor->SetStaticMesh(StaticMesh, MaterialInterface);
		
		GEditor->MoveActorInFrontOfCamera(*MeshActor, 
					  GCurrentLevelEditingViewportClient->GetViewLocation(), 
					  GCurrentLevelEditingViewportClient->GetViewRotation().Vector());
	}
				  
	return FReply::Handled();
}

FString SHelperWindowPluginMenu::GetCurrentStaticMeshPath() const
{
	return StaticMesh ? StaticMesh->GetPathName() : FString("");
}

void SHelperWindowPluginMenu::OnStaticMeshSelected(const FAssetData& AssetData)
{
	StaticMesh = CastChecked<UStaticMesh>(AssetData.GetAsset());
}

void SHelperWindowPluginMenu::OnCheckboxChanged(ECheckBoxState CheckBoxState)
{
	for (FSelectionIterator It(GEditor->GetSelectedActorIterator()); It; ++It)
	{
		AHWPMeshActor* Actor = Cast<AHWPMeshActor>(*It);
		if (Actor)
		{
			Actor->SetCanBeDamaged(CheckBoxState == ECheckBoxState::Checked ? true : false);
		}
	}
}

FString SHelperWindowPluginMenu::GetCurrentMaterialInterfacePath() const
{
	return MaterialInterface ? MaterialInterface->GetPathName() : FString("");

}

void SHelperWindowPluginMenu::OnMaterialInterfaceSelected(const FAssetData& AssetData)
{
	MaterialInterface = CastChecked<UMaterialInterface>(AssetData.GetAsset());

}

void SHelperWindowPluginMenu::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime,
                                   const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);


	ActorNameTextBlock->SetVisibility(EVisibility::Visible);
	CanBeDamagedCheckBox->SetVisibility(EVisibility::Visible);
	
	AHWPMeshActor* FirstInstance = nullptr;
	for (FSelectionIterator It(GEditor->GetSelectedActorIterator()); It; ++It)
	{
		AHWPMeshActor* Actor = Cast<AHWPMeshActor>(*It);

		if (!Actor)
		{
			ActorNameTextBlock->SetVisibility(EVisibility::Collapsed);
			CanBeDamagedCheckBox->SetVisibility(EVisibility::Collapsed);
			break;
		}

		if (FirstInstance)
		{
			ActorNameTextBlock->SetVisibility(EVisibility::Collapsed);
			
			if (FirstInstance->CanBeDamaged() != Actor->CanBeDamaged())
			{
				CanBeDamagedCheckBox->SetIsChecked( ECheckBoxState::Undetermined);
			}
		}
		else
		{
			FirstInstance = Actor;
			ActorNameTextBlock->SetText(FText::FromString(Actor->GetActorLabel()));
			CanBeDamagedCheckBox->SetIsChecked(Actor->CanBeDamaged() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
		}
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
