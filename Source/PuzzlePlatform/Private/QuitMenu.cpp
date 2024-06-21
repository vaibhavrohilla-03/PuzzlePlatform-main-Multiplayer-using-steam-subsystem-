// Fill out your copyright notice in the Description page of Project Settings.


#include "QuitMenu.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"
bool UQuitMenu::Initialize()
{
	bool success = Super::Initialize();

	QuitButton->OnClicked.AddDynamic(this, &UQuitMenu::QuitGame);
	CancelButton->OnClicked.AddDynamic(this, &UQuitMenu::RemoveWidget);

	return true;
}


void UQuitMenu::SetMenuInterface(IMenuSystemInterface* MenuInterfaceParam)
{
	MenuInterface = MenuInterfaceParam;
}


void UQuitMenu::RemoveWidget()
{
	this->RemoveFromParent();

	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(playerController != nullptr)) return;

	playerController->SetInputMode(FInputModeGameOnly());
	playerController->bShowMouseCursor = false;
}

void UQuitMenu::QuitGame()
{
	APlayerController* SpecificPlayer = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), SpecificPlayer, EQuitPreference::Quit, true);
}

