// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/FTP_BaseHUD.h"
#include "Blueprint/UserWidget.h"

void AFTP_BaseHUD::BeginPlay()
{
	Super::BeginPlay();

	CreateWaitPlayersWidget();
	SetVisibilityWidget(WaitPlayersWidgetInstance, false);
	CreatePlayerHUDWidget();
}

UUserWidget* AFTP_BaseHUD::CreateNewWidget(TSubclassOf<UUserWidget> WidgetTemplate)//, UDI_BaseUserWidget* WidgetInstance)
{
	UUserWidget* WidgetInstance = nullptr;
	
	if(WidgetTemplate)
	{
		if(!WidgetInstance)
		{
			WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WidgetTemplate);
		}
		if(!WidgetInstance->IsInViewport())
		{
			WidgetInstance->AddToViewport();
		}
	}
	return WidgetInstance;
}

void AFTP_BaseHUD::SetVisibilityWidget(UUserWidget* Widget, bool IsVisible)
{
	if(!Widget) return;
	
	if(IsVisible)
	{
		Widget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Widget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AFTP_BaseHUD::CreateWaitPlayersWidget()
{
	if(IsValid(WaitPlayersWidgetInstance)) return;
	
	WaitPlayersWidgetInstance = CreateNewWidget(WaitPlayersWidget);
}

void AFTP_BaseHUD::CreatePlayerHUDWidget()
{
	if(IsValid(PlayerHUDWidgetInstance)) return;
	
	PlayerHUDWidgetInstance = CreateNewWidget(PlayerHUDWidget);
}