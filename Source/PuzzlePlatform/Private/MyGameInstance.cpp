// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "Menu.h"
#include "SessionNameTextWidget.h"
#include "QuitMenu.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"


const static FName SESSION_NAME = TEXT("MySession");

UMyGameInstance::UMyGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstanceConstructor"));

	ConstructorHelpers::FClassFinder<UUserWidget> ClassOf_MenuBP(TEXT("/Game/Bluprints/Widgets_withMaterial/WBP_Menu"));
	ConstructorHelpers::FClassFinder<UUserWidget> ClassOf_QuitMenuBP(TEXT("/Game/Bluprints/Widgets_withMaterial/WBP_QuitMenu"));
	ConstructorHelpers::FClassFinder<UUserWidget> ClassOf_SessionNameBP(TEXT("/Game/Bluprints/Widgets_withMaterial/WBP_ServerNameText"));

	if(!ensure(ClassOf_MenuBP.Class != nullptr)) return;
	if(!ensure(ClassOf_QuitMenuBP.Class != nullptr)) return;
	if(!ensure(ClassOf_SessionNameBP.Class != nullptr)) return;

	MenuBPClass = ClassOf_MenuBP.Class;

	QuitMenuBPClass = ClassOf_QuitMenuBP.Class;
	
	ServerNameBPClass = ClassOf_SessionNameBP.Class;
	UWorld* world = GetWorld();
}

void UMyGameInstance::Init()
{	
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Init Called"));
	

	IOnlineSubsystem* Myonlinesubsystem = IOnlineSubsystem::Get();

	onlinesession = Myonlinesubsystem->GetSessionInterface();

	onlinesession->OnCreateSessionCompleteDelegates.AddUObject(this, &UMyGameInstance::OnCreateSessionComplete);
	onlinesession->OnDestroySessionCompleteDelegates.AddUObject(this, &UMyGameInstance::OnDestroySessionComplete);
	onlinesession->OnFindSessionsCompleteDelegates.AddUObject(this, &UMyGameInstance::OnFindSessionsComplete);
	onlinesession->OnJoinSessionCompleteDelegates.AddUObject(this, &UMyGameInstance::OnJoinSessionComplete);
	
	
}


void UMyGameInstance::LoadMenu()
{
	if (!ensure(MenuBPClass  != nullptr)) return;

	MenuWidget = CreateWidget<UMenu>(this, *MenuBPClass, *MenuBPClass->GetName());

	MenuWidget->AddToViewport();

	MenuWidget->SetMenuInterface(this);

}


void UMyGameInstance::CreateQuitMenu()
{
	


	QuitWidget = CreateWidget<UQuitMenu>(this, *QuitMenuBPClass, *QuitMenuBPClass->GetName());

	QuitWidget->AddToViewport();

	QuitWidget->SetMenuInterface(this);

	APlayerController* playerController = GetWorld()->GetFirstPlayerController();

	if (!ensure(playerController != nullptr)) return;

	playerController->SetInputMode(FInputModeUIOnly());
	playerController->bShowMouseCursor = true;
}
void UMyGameInstance::CreateServerNameWidget()
{
	ServerNameWidget = CreateWidget<USessionNameTextWidget>(this, *ServerNameBPClass, *ServerNameBPClass->GetName());
}

void UMyGameInstance::OnCreateSessionComplete(FName SessionName, bool Success) 
{
	GEngine->AddOnScreenDebugMessage(0, 7.0f, FColor::Red, TEXT("Hosting"));

	UWorld* world = GetWorld();

	if (!ensure(world != NULL)) return;

	if (!ensure(LobbyName != "")) return;

	FString MapURL = FString::Printf(TEXT("/Game/Maps/%s?listen"), *LobbyName.ToString());

	UE_LOG(LogTemp, Warning, TEXT("Map URL --> %s"), *MapURL);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *LobbyName.ToString());

	if (!(world->ServerTravel(MapURL)))
	{
		// do nothing 
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Session is Created, Removed menu and new map loadedd"));

		if (MenuWidget != nullptr)
		{
			MenuWidget->RemoveMenu();
		}

	}
}
void UMyGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success)
	{
		FOnlineSessionSettings sessionsettings = FOnlineSessionSettings();

		onlinesession->CreateSession(0, SESSION_NAME, sessionsettings);
	}
}

void UMyGameInstance::OnFindSessionsComplete(bool success)
{
	FString SuccessMessage = success ? TEXT("true") : TEXT("false");
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Session search completed: %s"), *SuccessMessage));

	if (success && sessionsearch.IsValid())
	{
		int i = 0;
		for (FOnlineSessionSearchResult& results : sessionsearch->SearchResults)
		{
			FString tempString = results.GetSessionIdStr();
			FText tempText = FText::FromString(tempString);
			CreateServerNameWidget();
			ServerNameWidget->ServerName->SetText(tempText);
			MenuWidget->IPScrollBox->AddChild(ServerNameWidget); 
			ServerNameWidget->setbuttonindex(i);
			++i;
			FString DebugMessage = FString::Printf(TEXT("Session added on index %d"), i);
			GEngine->AddOnScreenDebugMessage(-1, 7.0f, FColor::Red, DebugMessage);

		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(0, 7.0f, FColor::Red, TEXT(" No session was found "));
	}
}

void UMyGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	FString Address;
	onlinesession->GetResolvedConnectString(SessionName, Address);

	APlayerController* playercontroller = GetFirstLocalPlayerController();
	if (!ensure(playercontroller != NULL)) return;
	playercontroller->ClientTravel(Address, ETravelType::TRAVEL_Absolute);

	if (MenuWidget != nullptr)
	{
		MenuWidget->RemoveMenu();
	}
}
void UMyGameInstance::createsession()
{
	FOnlineSessionSettings sessionsettings = FOnlineSessionSettings();

	sessionsettings.bIsLANMatch = false;
	sessionsettings.NumPublicConnections = 20;
	sessionsettings.bShouldAdvertise = true;
	sessionsettings.bUsesPresence = true;
	sessionsettings.bUseLobbiesIfAvailable = true;
	sessionsettings.Set(SEARCH_KEYWORDS, FString("MyUniqueKeyword"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);


	onlinesession->CreateSession(0, SESSION_NAME, sessionsettings);
	
}

void UMyGameInstance::Host()
{	
	if (onlinesession.IsValid())
	{
		FNamedOnlineSession* ExistingSession = onlinesession->GetNamedSession(SESSION_NAME);

		if (ExistingSession != nullptr)
		{
			onlinesession->DestroySession(SESSION_NAME);
		}
		else
		{

			createsession();
			
		}

	}

	
}

void UMyGameInstance::Join()
{
	GEngine->AddOnScreenDebugMessage(0, 7.0f, FColor::Red, FString::Printf(TEXT("Joining")));
	if (selectedindex == 0)
	{
		onlinesession->JoinSession(0, SESSION_NAME, sessionsearch->SearchResults[0]);
	}
	else
	{
		onlinesession->JoinSession(0, SESSION_NAME, sessionsearch->SearchResults[selectedindex]);
	}
	

}

void UMyGameInstance::FindSessions()
{
	sessionsearch = MakeShareable<FOnlineSessionSearch>(new FOnlineSessionSearch());
	if (sessionsearch.IsValid())
	{
		sessionsearch->bIsLanQuery = false;
		sessionsearch->MaxSearchResults = 100;
		sessionsearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		sessionsearch->QuerySettings.Set(SEARCH_KEYWORDS, FString("MyUniqueKeyword"), EOnlineComparisonOp::In);
		onlinesession->FindSessions(0, sessionsearch.ToSharedRef());
		GEngine->AddOnScreenDebugMessage(0, 7.0f, FColor::Red, TEXT("session search starting"));
	}

	
}