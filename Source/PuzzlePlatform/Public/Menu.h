	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystemInterface.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetMenuInterface(IMenuSystemInterface* MenuInterfaceParam);

	void RemoveMenu();

protected:

	virtual bool Initialize() override;

private:

	UPROPERTY(meta = (BindWidget))
		class UButton* Host;

	UPROPERTY(meta = (BindWidget))
		class UButton* Join;

	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* Menuswitcher;

	UPROPERTY(meta = (BindWidget))
		class UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* JoinGame;

	UPROPERTY(meta = (BindWidget))
		class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
		class UWidget* JoinGameMenu;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* IPTextField;

	UFUNCTION()
		void HostServer();

	 IMenuSystemInterface* MenuInterface;

	UFUNCTION()
		void SwitchWidget();

	UFUNCTION()
		void JoinServer();

};
