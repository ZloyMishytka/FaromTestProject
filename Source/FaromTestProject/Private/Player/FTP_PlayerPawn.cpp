// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FTP_PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"

AFTP_PlayerPawn::AFTP_PlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("RootScene");
	SetRootComponent(SceneComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	CameraComponent->SetupAttachment(SceneComponent);
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	MeshComponent->SetupAttachment(SceneComponent);
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("Arrow");
	ArrowComponent->SetupAttachment(MeshComponent);

	MeshComponent->SetIsReplicated(true);
}

void AFTP_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}


