// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTP_PlayerPawn.h"
#include "Game/FTP_PlayerState.h"
#include "GameFramework/PlayerController.h"
#include "FTP_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FAROMTESTPROJECT_API AFTP_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void AddGoal();
	
	UFUNCTION(Server, Reliable)
	void Server_AddGoal();
	
	UFUNCTION(Client, Unreliable)
	void Client_ShowWaitPlayerWidget();

	UFUNCTION(Client, Unreliable)
	void Client_HideWaitPlayerWidget();

	UFUNCTION(Client, Unreliable)
	void Client_ShowPlayerHUDWidget();

	UFUNCTION(Client, Unreliable)
	void Client_HidePlayerHUDWidget();
	
	UPROPERTY(Replicated)
	AActor* PlayerStart = nullptr;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MovePlatform)
	float SpeedModify = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MovePlatform)
	float TraceMaxDistance = 300.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MovePlatform)
	TSubclassOf<AFTP_PlayerPawn> PlayerClass;
private:
	UFUNCTION(Client, Reliable)
	void Client_StartGame();

	UFUNCTION(Server, Reliable)
	void Server_SpawnPlayer();
	
	UFUNCTION()
	void MoveRight(float Amount);
	
	UFUNCTION(Server, Reliable)
	void Server_MoveRight(float Amount);
	
	bool TraceMove(float Amount, UPrimitiveComponent* ComponentLocation);

	AFTP_PlayerState* PlayerState = nullptr;
};
