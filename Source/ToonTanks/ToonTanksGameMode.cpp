// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "ToonTanks/Pawns/TurretPawn.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
    UE_LOG(LogTemp, Warning, TEXT("Game Started."));
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this,0));
    TargetTurrets = GetTurretCount();
    GameStart();
}

void AToonTanksGameMode::HandleGameOver(bool PlayerWon)
{
    UE_LOG(LogTemp, Display, TEXT("Game Finished PlayerWon=%s"), PlayerWon ? "True" : "False");
    GameOver(PlayerWon);
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    //UE_LOG(LogTemp, Display, TEXT("Actor [%s] died"), *DeadActor->GetName());
    if(DeadActor == PlayerTank)
    {
        PlayerTank->Die();
        HandleGameOver(false);
    }else if(ATurretPawn* TurretThatDied = Cast<ATurretPawn>(DeadActor))
    {
        TurretThatDied->Die();
        if(--TargetTurrets == 0)
        {
            HandleGameOver(true);
        }
    }
}

int32 AToonTanksGameMode::GetTurretCount() const
{
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATurretPawn::StaticClass(), TurretActors);
    return TurretActors.Num();
}
