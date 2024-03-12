// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FTP_PlayerController.h"

#include "Game/FTP_BaseGameMode.h"
#include "Game/FTP_BaseHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

void AFTP_PlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFTP_PlayerController, PlayerStart);
}

void AFTP_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(!GetWorld()) return;
	const auto GameMode = Cast<AFTP_BaseGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if(!GameMode) return;
	GameMode->OnStartGameSignature.AddDynamic(this, &AFTP_PlayerController::Client_StartGame);
	PlayerState = GetPlayerState<AFTP_PlayerState>();
}

void AFTP_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("Move", this, &AFTP_PlayerController::MoveRight);
}

void AFTP_PlayerController::Client_StartGame_Implementation()
{
	Client_HideWaitPlayerWidget();
	Server_SpawnPlayer();
}

void AFTP_PlayerController::Server_SpawnPlayer_Implementation()
{
	if(!GetWorld() || !PlayerStart || !PlayerClass) return;
	FActorSpawnParameters SpawnInfo;
	AFTP_PlayerPawn* PlayerPawn = GetWorld()->SpawnActor<AFTP_PlayerPawn>(PlayerClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), SpawnInfo);
	if(!PlayerPawn) return;
	OnPossess(PlayerPawn);
}

void AFTP_PlayerController::MoveRight(float Amount)
{
	if(!GetPawn() || !GetPawn()->FindComponentByClass<UMeshComponent>() || Amount == 0) return;
	
	if(!TraceMove(Amount, GetPawn()->FindComponentByClass<UMeshComponent>())) return;
	FVector NewLocation = GetPawn()->FindComponentByClass<UMeshComponent>()->GetRelativeLocation();
	NewLocation.Y -= Amount * SpeedModify;
	GetPawn()->FindComponentByClass<UMeshComponent>()->SetRelativeLocation(NewLocation);
	if(GetNetMode() == NM_Client)
	{
		Server_MoveRight(Amount);
	}
}

bool AFTP_PlayerController::TraceMove(float Amount, UPrimitiveComponent* ComponentLocation)
{
	if(!GetWorld() || !ComponentLocation) return false;

	FHitResult HitResult;
	FVector TraceEnd, TraceStart;
	TraceStart = ComponentLocation->GetComponentLocation();
	FVector Direction = ComponentLocation->GetRightVector();
	if(Amount > 0)
	{
		Direction = ComponentLocation->GetRightVector() * -1;
	}
	TraceEnd = TraceStart + Direction * TraceMaxDistance;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredComponent(ComponentLocation);
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
	if(HitResult.bBlockingHit)
	{
		return false;
	}
	return true;
}

void AFTP_PlayerController::Server_MoveRight_Implementation(float Amount)
{
	MoveRight(Amount);
}

void AFTP_PlayerController::Client_ShowWaitPlayerWidget_Implementation()
{
	const auto HUD = Cast<AFTP_BaseHUD>(GetHUD());
	if(!HUD) return;

	HUD->SetVisibilityWidget(HUD->GetWaitPlayersWidget(), true);
	SetInputMode(FInputModeGameOnly());
}

void AFTP_PlayerController::Client_HideWaitPlayerWidget_Implementation()
{
	const auto HUD = Cast<AFTP_BaseHUD>(GetHUD());
	if(!HUD) return;
	
	HUD->SetVisibilityWidget(HUD->GetWaitPlayersWidget(), false);
	SetInputMode(FInputModeGameOnly());
}

void AFTP_PlayerController::Client_ShowPlayerHUDWidget_Implementation()
{
	const auto HUD = Cast<AFTP_BaseHUD>(GetHUD());
	if(!HUD) return;

	HUD->SetVisibilityWidget(HUD->GetPlayerHUDWidget(), true);
	SetInputMode(FInputModeGameOnly());
}

void AFTP_PlayerController::Client_HidePlayerHUDWidget_Implementation()
{
	const auto HUD = Cast<AFTP_BaseHUD>(GetHUD());
	if(!HUD) return;
	
	HUD->SetVisibilityWidget(HUD->GetPlayerHUDWidget(), false);
	SetInputMode(FInputModeGameOnly());
}

void AFTP_PlayerController::AddGoal()
{
	if(!PlayerState) return;

	PlayerState->AddGoal();
	if(GetNetMode() == NM_Client)
	{
		Server_AddGoal();
	}
}

void AFTP_PlayerController::Server_AddGoal_Implementation()
{
	AddGoal();
}
