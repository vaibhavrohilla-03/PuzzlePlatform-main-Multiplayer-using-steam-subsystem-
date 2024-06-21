// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystemInterface.h"
#include "QuitMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UQuitMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	

	void SetMenuInterface(IMenuSystemInterface* MenuInterfaceParam);

private:

	IMenuSystemInterface* MenuInterface;

	UPROPERTY(meta = (BindWidget))
		class UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* CancelButton;

	

	virtual bool Initialize() override;

	UFUNCTION()
		void QuitGame();

	UFUNCTION()
		void RemoveWidget();

};
