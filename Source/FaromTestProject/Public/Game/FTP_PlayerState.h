// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FTP_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FAROMTESTPROJECT_API AFTP_PlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE int32 GetCountGoals() { return CountGoals; }

	void AddGoal();

private:
	UFUNCTION()
	void OnRep_CountGoals();
	
	UPROPERTY(ReplicatedUsing = OnRep_CountGoals)
	int32 CountGoals = 0;
};
