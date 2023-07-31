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

	void SetIsEnabled(bool InEnabled);

	bool GetIsEnabled() const {return IsEnabled;}

protected:

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	
	UPROPERTY(EditAnywhere)
	bool IsEnabled = true;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

};
