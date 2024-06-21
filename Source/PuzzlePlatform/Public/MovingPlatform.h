// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"
/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//UPROPERTY(EditAnywhere, Category = "dynamics")
		//float speed = 112.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "dynamics", meta = (MakeEditWidget = true))
		FVector TargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "dynamics", meta = (MakeEditWidget = true))
		FVector InitialLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "dynamics")
		float duration = 5.0f;	

	void AddActiveTriggers();
			
	void RemoveActiveTriggers();


private:

	UPROPERTY(EditAnywhere)
		int ActiveTriggers = 1;

	FVector GTargetLocation;
	FVector GInitialLocation;

	float Distance;
	float TimeElapsed;
	

	bool Flag;
};
