// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystemInterface.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UMyGameInstance : public UGameInstance, public IMenuSystemInterface	
{
	GENERATED_BODY()

public:
	UMyGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;
	
	UFUNCTION(Exec)
		void Host();

	UFUNCTION(Exec)
		void Join(const FString& Address);

	UFUNCTION(BlueprintCallable)
		void CreateQuitMenu();

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
		FName LobbyName;

private:
	

	TSubclassOf<UUserWidget> MenuBPClass;
	TSubclassOf<UUserWidget> QuitMenuBPClass;

	class UQuitMenu* QuitWidget;
	class UMenu* MenuWidget;
	

	UFUNCTION(BlueprintCallable)
	void LoadMenu();


};
