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
	
public:

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ServerName;
};
