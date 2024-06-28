// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SessionNameTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API USessionNameTextWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	virtual bool Initialize() override;

	uint32 buttonindex;

	class UMyGameInstance* gameinstance;

public:

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ServerName;

	UPROPERTY(meta = (BindWidget))
		class UButton* ServerButton;

	UFUNCTION()
		void selectServer();

	UFUNCTION()
		void setbuttonindex(uint32 index);
};
