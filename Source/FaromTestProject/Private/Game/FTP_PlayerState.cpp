// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/FTP_PlayerState.h"

#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerState, All, All);

void AFTP_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFTP_PlayerState, CountGoals);
}

void AFTP_PlayerState::AddGoal()
{
	CountGoals++;
	OnRep_CountGoals();
}

void AFTP_PlayerState::OnRep_CountGoals()
{
	UE_LOG(LogPlayerState, Display, TEXT("PlayerState: %s. Score: %i"), *GetName(), CountGoals);
}
