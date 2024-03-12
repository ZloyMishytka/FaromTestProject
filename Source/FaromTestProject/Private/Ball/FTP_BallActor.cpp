// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball/FTP_BallActor.h"

#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
DEFINE_LOG_CATEGORY_STATIC(LogBallActor, All, All);

void AFTP_BallActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFTP_BallActor, VelocityBall);
	DOREPLIFETIME(AFTP_BallActor, SpeedBall);
	DOREPLIFETIME(AFTP_BallActor, DeltaBall);
	DOREPLIFETIME(AFTP_BallActor, DelayStartMove);
}

AFTP_BallActor::AFTP_BallActor()
{
	bReplicates = true;
 	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(SceneComponent);
	MeshBall = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	MeshBall->SetupAttachment(SceneComponent);

	SceneComponent->SetIsReplicated(true);
	MeshBall->SetIsReplicated(true);
}

void AFTP_BallActor::BeginPlay()
{
	Super::BeginPlay();

	if(!GetWorld()) return;
	
	GetWorld()->GetTimerManager().SetTimer(StartMoveBallTimerManager, this, &AFTP_BallActor::StartMove, 0.01f, false, DelayStartMove);
}

void AFTP_BallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFTP_BallActor::Server_StartMove_Implementation()
{
	StartMove();
}

void AFTP_BallActor::StartMove()
{
	if(!GetWorld()) return;

	float VelocX = 1.0f;
	float VelocY = 1.0f;
	if(FMath::RandBool())
	{
		VelocX = -1;
	}
	if(FMath::RandBool())
	{
		VelocY = -1;
	}
	VelocityBall = FVector(VelocX, VelocY, 0.0f);
	OnRep_VelocityBall();
	GetWorld()->GetTimerManager().SetTimer(UpdateMoveBallTimerManager, this, &AFTP_BallActor::MoveBall, DeltaBall, true, 0.0f);
	if(GetNetMode() == NM_Client)
	{
		Server_MoveBall();
	}
}

void AFTP_BallActor::MoveBall()
{
	if(!GetWorld()) return;
	FVector TraceStart, TraceEnd, NewLocation;
	TraceStart = GetActorLocation();
	TraceEnd = TraceStart + VelocityBall * SpeedBall * DeltaBall;
	NewLocation = TraceEnd;
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
	if(HitResult.bBlockingHit)
	{
		VelocityBall = UKismetMathLibrary::MirrorVectorByNormal(VelocityBall, HitResult.ImpactNormal);
		APawn* PlayerPawn = Cast<APawn>(HitResult.GetActor());
		if(PlayerPawn)
		{
			SpeedBall = FMath::Clamp(SpeedBall + AmountSpeedPerHit, SpeedBall, MaxSpeedBall);
		}
		OnRep_VelocityBall();
		NewLocation = TraceStart + VelocityBall * SpeedBall * DeltaBall;
	}
	SetActorLocation(NewLocation);
	if(GetNetMode() == NM_Client)
	{
		Server_MoveBall();
	}
}

void AFTP_BallActor::OnRep_VelocityBall()
{
	UE_LOG(LogBallActor, Display, TEXT("Velocity Ball Change. New value: X (%f) : Y (%f) : Z (%f)"), VelocityBall.X, VelocityBall.Y, VelocityBall.Z);
}

void AFTP_BallActor::Server_MoveBall_Implementation()
{
	MoveBall();
}