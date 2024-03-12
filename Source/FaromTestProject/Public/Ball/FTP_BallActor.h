// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FTP_BallActor.generated.h"

UCLASS()
class FAROMTESTPROJECT_API AFTP_BallActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AFTP_BallActor();

	UFUNCTION()
	void StartMove();
	
	UFUNCTION(Server, Reliable)
	void Server_StartMove();
	
protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	USceneComponent* SceneComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	UStaticMeshComponent* MeshBall;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite, Category = BallParameters)
	float SpeedBall = 500.0f;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite, Category = BallParameters)
	float MaxSpeedBall = 800.0f;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite, Category = BallParameters)
	float AmountSpeedPerHit = 20.0f;
	
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite, Category = BallParameters)
	float DeltaBall = 0.01f;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite, Category = BallParameters)
	float DelayStartMove = 2.0f;
	
public:	
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void MoveBall();

	UFUNCTION(Server, Reliable)
	void Server_MoveBall();

	UFUNCTION()
	void OnRep_VelocityBall();
	
	UPROPERTY(ReplicatedUsing = OnRep_VelocityBall)
	FVector VelocityBall;
	
	FTimerHandle StartMoveBallTimerManager;
	FTimerHandle UpdateMoveBallTimerManager;
};
