// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#pragma region constructor
AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

#pragma endregion 

#pragma region BeginPlay

void AMovingPlatform::BeginPlay()
{

	Super::BeginPlay();
	SetReplicates(true);
	SetReplicateMovement(true);

	GTargetLocation = GetTransform().TransformPosition(TargetLocation);

	GInitialLocation = GetTransform().TransformPosition(InitialLocation);
	

	SetActorLocation(GInitialLocation);


	Flag = true;	

	
}

#pragma endregion 

#pragma region Tick
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ActiveTriggers > 0)
	{
		if (HasAuthority())
		{
			TimeElapsed += DeltaTime;

			if (Flag)
			{
				if (TimeElapsed < duration)
				{
					SetActorLocation(FMath::Lerp(GInitialLocation, GTargetLocation, TimeElapsed / duration));
					FVector location = GetActorLocation();
					//UE_LOG(LogTemp, Display, TEXT("actor location now : %s"),*location.ToString());
					//UE_LOG(LogTemp, Display, TEXT("time spent  : %f"),TimeElapsed);
				}
				else
				{
					Flag = false;
					TimeElapsed = 0.0f;  // Reset the timer for the return trip
				}

			}

			else
			{
				if (TimeElapsed < duration)
				{
					SetActorLocation(FMath::Lerp(GTargetLocation, GInitialLocation, TimeElapsed / duration));
				}
				else
				{
					Flag = true;
					TimeElapsed = 0.0f;  // Reset the timer for the forward trip
				}
			}

			/*FVector Location = GetActorLocation();
			FVector Direction = GTargetLocation - Location;
			UE_LOG(LogTemp, Display, TEXT("initial			: %s"),*Direction.ToString());
			Direction = (GTargetLocation - Location).GetSafeNormal();
			UE_LOG(LogTemp, Display, TEXT("after :				%s"), *Direction.ToString());
			Location += speed * DeltaTime * Direction;

			SetActorLocation(Location);*/
		}
	}
}
#pragma endregion

void AMovingPlatform::AddActiveTriggers()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTriggers()
{
	if (ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
}