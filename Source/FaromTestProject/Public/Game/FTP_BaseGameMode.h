// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ball/FTP_BallActor.h"
#include "GameFramework/GameModeBase.h"
#include "FTP_BaseGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartGameSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGoalSignature);

/**
 * 
 */
UCLASS()
class FAROMTESTPROJECT_API AFTP_BaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE TArray<APlayerController*> GetPlayersControllers() { return PlayersControllers; }

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnStartGameSignature OnStartGameSignature;

	UPROPERTY(BlueprintCallable)
	FOnGoalSignature OnGoalSignature;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = GameSettings)
	TSubclassOf<AFTP_BallActor> BallClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = GameSettings)
	FVector PointSpawnBall;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = GameSettings)
	int32 CountPlayers = 2;
	
private:
	void WaitPlayers();
	void StartGame();
	
	UFUNCTION()
	void SpawnBall();
	
	FTimerHandle WaitPlayersTimerHandle;
	AFTP_BallActor* BallRef = nullptr;
	TArray<APlayerController*> PlayersControllers;
};
