#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HWPMeshActor.generated.h"

UCLASS()
class AHWPMeshActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AHWPMeshActor();

	void SetIsEnabled(const bool Enabled);

protected:

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	bool IsEnabled = true;
};
