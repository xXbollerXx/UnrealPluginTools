#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HWPMeshActor.generated.h"

UCLASS()
class AHWPMeshActor : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere)
	float DamageMultiplier = 0;
	
	AHWPMeshActor();
	
#if WITH_EDITOR
	void SetStaticMesh(UStaticMesh* NewStaticMesh, UMaterialInterface* Material);
#endif

private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

};
