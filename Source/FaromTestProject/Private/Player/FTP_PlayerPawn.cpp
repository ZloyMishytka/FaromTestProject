// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FTP_PlayerPawn.h"

// Sets default values
AFTP_PlayerPawn::AFTP_PlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFTP_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFTP_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFTP_PlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

