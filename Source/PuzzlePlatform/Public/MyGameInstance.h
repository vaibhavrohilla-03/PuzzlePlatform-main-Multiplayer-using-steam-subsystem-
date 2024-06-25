// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "MenuSystemInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
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

	UFUNCTION()
		FString GetServerName();
			


	UFUNCTION(BlueprintCallable)
		void CreateQuitMenu();

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
		FName LobbyName;

private:
	

	TSubclassOf<UUserWidget> MenuBPClass;
	TSubclassOf<UUserWidget> QuitMenuBPClass;
	TSubclassOf<UUserWidget> ServerNameBPClass;


	class UQuitMenu* QuitWidget;
	class UMenu* MenuWidget;
	class USessionNameTextWidget* ServerNameWidget;

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);
	void OnFindSessionsComplete(bool Success);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
		

	IOnlineSessionPtr onlinesession;

	TSharedPtr<class FOnlineSessionSearch> sessionsearch;

	void createsession();

	void CreateServerNameWidget();

};
