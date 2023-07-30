// Fill out your copyright notice in the Description page of Project Settings.
#include "HWPMeshActor.h"

AHWPMeshActor::AHWPMeshActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	// hard ref static mesh here?
}

#if WITH_EDITOR

void AHWPMeshActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(AHWPMeshActor, IsEnabled))
	{
		StaticMeshComponent->SetVisibility(IsEnabled);
	}
}
#endif

