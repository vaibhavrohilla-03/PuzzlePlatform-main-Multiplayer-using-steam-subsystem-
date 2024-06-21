// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerPlate.generated.h"

UCLASS()
class PUZZLEPLATFORM_API ATriggerPlate : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATriggerPlate();

	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, category = "Triggers");
	class UBoxComponent* TriggerVolume;

	UPROPERTY(VisibleAnywhere, Category = "Meshes");
	UStaticMeshComponent* PlateMesh;

	UPROPERTY(EditAnywhere, Category = "platforms to trigger")
		TArray<class AMovingPlatform*> Platforms_to_trigger;

		
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
