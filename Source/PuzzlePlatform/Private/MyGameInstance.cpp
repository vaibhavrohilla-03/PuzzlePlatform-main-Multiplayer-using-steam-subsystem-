// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Menu.h"
#include "QuitMenu.h"
UMyGameInstance::UMyGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstanceConstructor"));

	ConstructorHelpers::FClassFinder<UUserWidget> ClassOf_MenuBP(TEXT("/Game/Bluprints/Widgets_withMaterial/WBP_Menu"));
	ConstructorHelpers::FClassFinder<UUserWidget> ClassOf_QuitMenuBP(TEXT("/Game/Bluprints/Widgets_withMaterial/WBP_QuitMenu"));

	if(!ensure(ClassOf_MenuBP.Class != nullptr)) return;
	if(!ensure(ClassOf_QuitMenuBP.Class != nullptr)) return;

	MenuBPClass = ClassOf_MenuBP.Class;

	QuitMenuBPClass = ClassOf_QuitMenuBP.Class;
	
	UWorld* world = GetWorld();
}

void UMyGameInstance::Init()
{	
	Super::Init();
}


void UMyGameInstance::LoadMenu()
{
	if (!ensure(MenuBPClass  != nullptr)) return;

	MenuWidget = CreateWidget<UMenu>(this, *MenuBPClass, *MenuBPClass->GetName());

	MenuWidget->AddToViewport();

	MenuWidget->SetMenuInterface(this);

}


void UMyGameInstance::CreateQuitMenu()
{
	


	QuitWidget = CreateWidget<UQuitMenu>(this, *QuitMenuBPClass, *QuitMenuBPClass->GetName());

	QuitWidget->AddToViewport();

	QuitWidget->SetMenuInterface(this);

	APlayerController* playerController = GetWorld()->GetFirstPlayerController();

	if (!ensure(playerController != nullptr)) return;

	playerController->SetInputMode(FInputModeUIOnly());
	playerController->bShowMouseCursor = true;
}


void UMyGameInstance::Host()
{	
	GEngine->AddOnScreenDebugMessage(0, 7.0f, FColor::Red, TEXT("Hosting"));

	UWorld* world = GetWorld();
	
	if (!ensure(world != NULL)) return;

	if (!ensure(LobbyName != "")) return;

	FString MapURL = FString::Printf(TEXT("/Game/Maps/%s?listen"), *LobbyName.ToString());

	UE_LOG(LogTemp, Warning, TEXT("Map URL --> %s"), *MapURL);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *LobbyName.ToString());
	
	if (!(world->ServerTravel(MapURL)))
	{
	
		GEngine->AddOnScreenDebugMessage(-1, 7.0f, FColor::Red, TEXT("NotWorking"));
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 7.0f, FColor::Red, TEXT("Working"));

		if (MenuWidget != nullptr)
		{
			MenuWidget->RemoveMenu();
		}
		
	}

	
}

void UMyGameInstance::Join(const FString& Address)
{
	GEngine->AddOnScreenDebugMessage(0, 7.0f, FColor::Red, FString::Printf(TEXT("Joining : %s"),*Address));

	APlayerController* playercontroller = GetFirstLocalPlayerController();

	if (!ensure(playercontroller != NULL)) return;

	playercontroller->ClientTravel(Address, ETravelType::TRAVEL_Absolute);

	if (MenuWidget != nullptr)
	{
		MenuWidget->RemoveMenu();
	}

}