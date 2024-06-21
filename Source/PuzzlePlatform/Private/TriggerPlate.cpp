	// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerPlate.h"
#include "Components/BoxComponent.h"
#include "MovingPlatform.h"

// Sets default values
ATriggerPlate::ATriggerPlate()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlateMesh"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));

	if (!ensure(TriggerVolume != nullptr)) return;

	TriggerVolume->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, NAME_None);


	if (!ensure(PlateMesh != nullptr)) return;

	PlateMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, NAME_None);

}
// Called when the game starts or when spawned
void ATriggerPlate::BeginPlay()
{
	Super::BeginPlay();

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ATriggerPlate::OnOverlapBegin);

	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ATriggerPlate::OnOverlapEnd);

		for (AMovingPlatform* Platform : Platforms_to_trigger)
		{
			if (Platform)
			{
				UE_LOG(LogTemp, Warning, TEXT("Platform to trigger: %s"), *Platform->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Platform to trigger is null"));
			}
		}
	
 	

}

// Called every frame
void ATriggerPlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerPlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin with: %s"), *OtherActor->GetName());

	for (AMovingPlatform* platforms : Platforms_to_trigger)
	{	
		if (platforms) // Ensure Platform is not null
		{
			platforms->AddActiveTriggers();
			UE_LOG(LogTemp, Warning, TEXT("Activated Platform: %s"), *platforms->GetName());

		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Platform is null in OnOverlapBegin"));
		}

	}
	

	/*FString tempstring = OtherActor->GetName();
	UE_LOG(LogTemp, Warning, TEXT("character entering :%s"),*tempstring);*/
}

void ATriggerPlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{	
	for (AMovingPlatform* platforms : Platforms_to_trigger)
	{	
		
		if (platforms) // Ensure Platform is not null
		{
			platforms->RemoveActiveTriggers();
			UE_LOG(LogTemp, Warning, TEXT("Deactivated Platform: %s"), *platforms->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Platform is null in OnOverlapEnd"));
		}

	}

	/*FString tempstringII = OtherActor->GetName();
	UE_LOG(LogTemp, Warning, TEXT("character leaving :%s"),*tempstringII);\
	*/
}
