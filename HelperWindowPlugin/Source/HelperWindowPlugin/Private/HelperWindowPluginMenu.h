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

protected:

	
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
private:

	TSharedPtr<SCheckBox> CanBeDamagedCheckBox;

	TSharedPtr<STextBlock> ActorNameTextBlock;

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

	float NumericEntryBoxValue;

	TSharedPtr<SNumericEntryBox<float>> NumericEntryBox;
};
