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

	UPROPERTY()
		class UTextBlock* ServerName; 
	UPROPERTY(meta = (BindWidget))
		class UPanelWidget* IPScrollBox;

	//TOptional<uint32> SelectedIndex;

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

	

	UFUNCTION()
		void HostServer();

	 IMenuSystemInterface* MenuInterface;

	UFUNCTION()
		void SwitchWidget();

	UFUNCTION()
		void JoinServer();

	/*UFUNCTION()
	uint32 GetSelectedIndex();*/

	/*UFUNCTION()
		void SetIndex(uint32 SelectedIndexP);*/


};
