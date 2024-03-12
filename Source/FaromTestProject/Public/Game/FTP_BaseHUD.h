// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FTP_BaseHUD.generated.h"

/**
 * 
 */
UCLASS()
class FAROMTESTPROJECT_API AFTP_BaseHUD : public AHUD
{
	GENERATED_BODY()

public:
	void SetVisibilityWidget(UUserWidget* Widget, bool IsVisible);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UUserWidget* GetWaitPlayersWidget() { return WaitPlayersWidgetInstance; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UUserWidget* GetPlayerHUDWidget() { return PlayerHUDWidgetInstance; }
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	UUserWidget* CreateNewWidget(TSubclassOf<UUserWidget> WidgetTemplate);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> WaitPlayersWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> PlayerHUDWidget;

private:
	UPROPERTY()
	UUserWidget* WaitPlayersWidgetInstance;

	UPROPERTY()
	UUserWidget* PlayerHUDWidgetInstance;

	void CreateWaitPlayersWidget();

	void CreatePlayerHUDWidget();
};
