// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/FTP_BaseGameMode.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Player/FTP_PlayerController.h"

void AFTP_BaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	OnGoalSignature.AddDynamic(this, &AFTP_BaseGameMode::SpawnBall);
	
	if(!GetWorld()) return;

	GetWorld()->GetTimerManager().SetTimer(WaitPlayersTimerHandle, this, &AFTP_BaseGameMode::WaitPlayers, 0.01f, true, 0.0f);
}

void AFTP_BaseGameMode::WaitPlayers()
{
	TArray<AActor*> Controllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerController::StaticClass(), Controllers);

	if(Controllers.Num() < CountPlayers)
	{
		for (auto PlayerControl : Controllers)
		{
			AFTP_PlayerController* PlayerController = Cast<AFTP_PlayerController>(PlayerControl);
			if(PlayerController)
			{
				PlayerController->Client_ShowWaitPlayerWidget();
			}
		}
	}
	else
	{
		if(Controllers.Num() > CountPlayers)
		{
			return;
		}
		TArray<AActor*> PlayersStarts;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayersStarts);
		if(PlayersStarts.Num() < CountPlayers)
		{
			GetWorld()->GetTimerManager().ClearTimer(WaitPlayersTimerHandle);
			return;
		}
		int32 IndexPlayerStart = 0;
		for (auto PlayerControl : Controllers)
		{
			AFTP_PlayerController* PlayerController = Cast<AFTP_PlayerController>(PlayerControl);
			if(PlayerController)
			{
				PlayersControllers.Add(PlayerController);
				PlayerController->PlayerStart = PlayersStarts[IndexPlayerStart];
				IndexPlayerStart++;
			}
		}
		StartGame();
	}
	
}

void AFTP_BaseGameMode::StartGame()
{
	GetWorld()->GetTimerManager().ClearTimer(WaitPlayersTimerHandle);
	OnStartGameSignature.Broadcast();
	SpawnBall();
}

void AFTP_BaseGameMode::SpawnBall()
{
	if(!GetWorld() || PointSpawnBall.IsZero() || !BallClass) return;
	if(BallRef)
	{
		BallRef->Destroy();
	}
	FActorSpawnParameters SpawnInfo;
	BallRef = GetWorld()->SpawnActor<AFTP_BallActor>(BallClass, PointSpawnBall, FRotator::ZeroRotator, SpawnInfo);
}