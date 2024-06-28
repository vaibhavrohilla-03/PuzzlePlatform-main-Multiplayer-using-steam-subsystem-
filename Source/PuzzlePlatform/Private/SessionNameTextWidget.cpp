// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionNameTextWidget.h"
#include "Components/Button.h"
#include "Menu.h"
#include "MyGameInstance.h"



bool USessionNameTextWidget::Initialize()
{
	bool success = Super::Initialize();

	if (!success) return false;

	ServerButton->OnClicked.AddDynamic(this, &USessionNameTextWidget::selectServer);

	return true;
}


void USessionNameTextWidget::selectServer()
{
	
	gameinstance = Cast<UMyGameInstance>(GetGameInstance());
	gameinstance->selectedindex = buttonindex;

	GEngine->AddOnScreenDebugMessage(0, 7.0f, FColor::Red, FString::Printf(TEXT("serverselected")));
}

void USessionNameTextWidget::setbuttonindex(uint32 index)
{
	index = buttonindex;
}