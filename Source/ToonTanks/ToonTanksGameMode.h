// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Pawns/PawnTank.h"

#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	APawnTank* PlayerTank = nullptr;
	int32 TargetTurrets = 0;
	
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);
	int32 GetTurretCount() const;
	
public:
	void ActorDied(AActor* DeadActor);
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Game Loop")
	int32 StartDelay = 3;
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);
};