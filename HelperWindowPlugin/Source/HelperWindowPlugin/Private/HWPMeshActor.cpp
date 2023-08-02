// Fill out your copyright notice in the Description page of Project Settings.
#include "HWPMeshActor.h"

#include "UObject/ConstructorHelpers.h"


AHWPMeshActor::AHWPMeshActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());
	
}

void AHWPMeshActor::SetIsEnabled(bool InEnabled)
{
	IsEnabled = InEnabled;
	StaticMeshComponent->SetVisibility(IsEnabled);
}

#if WITH_EDITOR

void AHWPMeshActor::SetStaticMesh(UStaticMesh* NewStaticMesh, UMaterialInterface* Material)
{
	StaticMeshComponent->SetStaticMesh(NewStaticMesh);
	StaticMeshComponent->SetMaterial(0, Material);
}

void AHWPMeshActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(AHWPMeshActor, IsEnabled))
	{
		StaticMeshComponent->SetVisibility(IsEnabled);
	}
}
#endif

