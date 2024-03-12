// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball/FTP_BallActor.h"

// Sets default values
AFTP_BallActor::AFTP_BallActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFTP_BallActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFTP_BallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

