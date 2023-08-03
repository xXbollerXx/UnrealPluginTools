// Fill out your copyright notice in the Description page of Project Settings.


#include "HelperWindowPluginMenu.h"

#include "HWPMeshActor.h"
#include "LevelEditor.h"
#include "LevelEditorViewport.h"
#include "PropertyCustomizationHelpers.h"
#include "Selection.h"
#include "SlateOptMacros.h"
#include "LevelEditor/Private/SLevelEditor.h"
#include "Widgets/Input/SNumericEntryBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

const FSoftObjectPath SHelperWindowPluginMenu::BasicCube("/Engine/BasicShapes/Cube", "Cube", {});
const FSoftObjectPath SHelperWindowPluginMenu::BasicMaterial("/Engine/BasicShapes/BasicShapeMaterial", "BasicShapeMaterial", {});


void SHelperWindowPluginMenu::Construct(const FArguments& InArgs)
{
	StaticMesh = LoadObject<UStaticMesh>(nullptr, *BasicCube.ToString());
	MaterialInterface = LoadObject<UMaterialInterface>(nullptr, *BasicMaterial.ToString());

	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked< FLevelEditorModule >("LevelEditor");
	LevelEditorModule.OnActorSelectionChanged().AddSP(this, &SHelperWindowPluginMenu::OnSelectionChanged);


	

	TSharedRef<SHorizontalBox> TextHorizontalBox = SNew(SHorizontalBox)
	+SHorizontalBox::Slot()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Actor Name"))
	]
	+SHorizontalBox::Slot()
	[
		SAssignNew(ActorNameTextBlock, STextBlock)
		.Text(FText::FromString(""))
		.Visibility(EVisibility::Collapsed)
	];


	
	TSharedRef<SHorizontalBox> CheckHorizontalBox = SNew(SHorizontalBox)
	+SHorizontalBox::Slot()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Actor Can Be Damaged"))
	]
	+SHorizontalBox::Slot()
	[
		SAssignNew(CanBeDamagedCheckBox, SCheckBox)
		.OnCheckStateChanged(this, &SHelperWindowPluginMenu::OnCheckboxChanged)
		.Visibility(EVisibility::Collapsed)
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
		]
	+ SVerticalBox::Slot()
	.AutoHeight()
	.Padding(5)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
				[
					SNew(STextBlock)
					.Text(FText::FromString("Damage Multiplier"))
				]
			+SHorizontalBox::Slot()
				[
					SAssignNew(NumericEntryBox, SNumericEntryBox<float>)
					.Value(this, &SHelperWindowPluginMenu::GetValue)
					.OnValueChanged(this, &SHelperWindowPluginMenu::OnValueCommitted)
					.UndeterminedString(FText::FromString("Undetermined"))
					.Visibility(EVisibility::Collapsed)
				]
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

void SHelperWindowPluginMenu::OnValueCommitted(float Value)
{
	for (FSelectionIterator It(GEditor->GetSelectedActorIterator()); It; ++It)
	{
		AHWPMeshActor* Actor = Cast<AHWPMeshActor>(*It);
		if (Actor)
		{
			Actor->DamageMultiplier = Value;
		}
	}
}

TOptional<float> SHelperWindowPluginMenu::GetValue() const
{
	AHWPMeshActor* First = nullptr;
	TOptional<float> Temp = TOptional<float>();
	
	for (FSelectionIterator It(GEditor->GetSelectedActorIterator()); It; ++It)
	{
		AHWPMeshActor* Actor = Cast<AHWPMeshActor>(*It);

		if (Actor)
		{
			if (!First)
			{
				First = Actor;
			}

			if (Actor->DamageMultiplier != First->DamageMultiplier)
			{
				return TOptional<float>();
			}

			if (Actor == First)
			{
				Temp = TOptional<float>(Actor->DamageMultiplier);
			}
		}
	}
	
	return  Temp;
}

void SHelperWindowPluginMenu::OnSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh)
{
	ActorNameTextBlock->SetVisibility(EVisibility::Visible);
	CanBeDamagedCheckBox->SetVisibility(EVisibility::Visible);
	NumericEntryBox->SetVisibility(EVisibility::Visible);
	
	AHWPMeshActor* FirstInstance = nullptr;
	for (UObject* Object : NewSelection)
	{
		AHWPMeshActor* Actor = Cast<AHWPMeshActor>(Object);

		if (!Actor)
		{
			ActorNameTextBlock->SetVisibility(EVisibility::Collapsed);
			CanBeDamagedCheckBox->SetVisibility(EVisibility::Collapsed);
			NumericEntryBox->SetVisibility(EVisibility::Collapsed);
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
