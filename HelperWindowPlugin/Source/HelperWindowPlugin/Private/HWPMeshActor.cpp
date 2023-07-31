// Fill out your copyright notice in the Description page of Project Settings.
#include "HWPMeshActor.h"

#include "UObject/ConstructorHelpers.h"

AHWPMeshActor::AHWPMeshActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObject(TEXT("/Engine/Content/BasicShapes/Cube"));
	//if (StaticMeshObject.Succeeded())
	//{
		StaticMeshComponent->SetStaticMesh(StaticMeshObject.Object);
	//o}
	StaticMeshComponent->SetupAttachment(GetRootComponent());
	
}

void AHWPMeshActor::SetIsEnabled(bool InEnabled)
{
	IsEnabled = InEnabled;
	StaticMeshComponent->SetVisibility(IsEnabled);
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

