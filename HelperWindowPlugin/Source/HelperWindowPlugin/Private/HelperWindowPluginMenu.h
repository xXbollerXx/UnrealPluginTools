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
public:
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:

	TSharedPtr<SCheckBox> CanBeDamagedCheckBox;

	TSharedPtr<STextBlock> ActorNameTextBlock;

	TSharedPtr<SNumericEntryBox<float>> NumericEntryBox;
	
	UPROPERTY()
	UStaticMesh* StaticMesh = nullptr;

	UPROPERTY()
	UMaterialInterface* MaterialInterface = nullptr;

	static const FSoftObjectPath BasicCube;
	
	static const FSoftObjectPath BasicMaterial;

	FString GetCurrentStaticMeshPath() const;

	void OnStaticMeshSelected(const FAssetData& AssetData);

	FReply SpawnMeshActor();
	
	void OnCheckboxChanged(ECheckBoxState CheckBoxState);

	FString GetCurrentMaterialInterfacePath() const;

	void OnMaterialInterfaceSelected(const FAssetData& AssetData);

	void OnValueCommitted(float Value);

	TOptional<float> GetValue() const;

	void OnSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh);

};
