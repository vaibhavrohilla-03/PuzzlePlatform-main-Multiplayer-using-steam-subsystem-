// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"

#include "Components/Button.h"

#include "Components/WidgetSwitcher.h"

#include "Components/ScaleBox.h"

#include "Components/EditableTextBox.h"

bool UMenu::Initialize()
{
	bool success = Super::Initialize();

	if (!success) return false;

	if (!ensure(Host != nullptr)) return false;
	Host->OnClicked.AddDynamic(this, &UMenu::HostServer);

	if (!ensure(Join != nullptr)) return false;
	Join->OnClicked.AddDynamic(this, &UMenu::SwitchWidget);

	if (!ensure(BackButton != nullptr)) return false;
	BackButton->OnClicked.AddDynamic(this, &UMenu::SwitchWidget);

	if (!ensure(JoinGame != nullptr)) return false;
	JoinGame->OnClicked.AddDynamic(this, &UMenu::JoinServer);

	return true;
}

void UMenu::SetMenuInterface(IMenuSystemInterface* MenuInterfaceParam)
{
	UMenu::MenuInterface = MenuInterfaceParam;
}


void UMenu::HostServer()
{
	MenuInterface->Host();
}

void UMenu::RemoveMenu()
{	
	this->RemoveFromParent();
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();

	if (!ensure( playerController!= nullptr)) return;

	playerController->SetInputMode(FInputModeGameOnly());
	playerController->bShowMouseCursor = false;
}

void UMenu::SwitchWidget() 
{
	UWidget* tempWidget = Menuswitcher->GetActiveWidget();
	
	if (!ensure(MainMenu != nullptr)) return;
	if (!ensure(JoinGameMenu != nullptr)) return;

	if (tempWidget->GetName() == MainMenu->GetName())
	{
		Menuswitcher->SetActiveWidget(JoinGameMenu);
		MenuInterface->FindSessions();
		return;
	}
	else
	{
		Menuswitcher->SetActiveWidget(MainMenu);
		return;
	}
	
	
	
}
void UMenu::JoinServer()
{	
	
	MenuInterface->Join();
}

/*uint32 UMenu::GetSelectedIndex()
{
	if (SelectedIndex.IsSet())
	{
		return SelectedIndex.GetValue();
	}
}*/


/*void UMenu::SetIndex(uint32 SelectedIndexP)
{
	SelectedIndex = SelectedIndexP;
}
*/