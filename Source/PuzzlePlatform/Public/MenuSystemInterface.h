// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuSystemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuSystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PUZZLEPLATFORM_API IMenuSystemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void Host() = 0;
	virtual void Join() = 0;
	virtual void CreateQuitMenu() = 0;
	virtual void FindSessions() = 0;


};
