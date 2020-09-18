// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretPawn.h"

#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

float ATurretPawn::DistanceBetweenPlayerPawn()
{
    if(!PlayerPawn)
    {
        return 10000.0f;
    }

    float Distance = FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
    return Distance;
}

void ATurretPawn::CheckFireCondition()
{
    //UE_LOG(LogTemp, Warning, TEXT("Called: ATurretPawn::CheckFireCondition"));
    
    // If player is not null or dead
    // then
    //     if player in range
    //        fire!
    if(PlayerPawn && PlayerPawn->GetIsPlayerAlive() && DistanceBetweenPlayerPawn() < Range)
    {
        UE_LOG(LogTemp, Warning, TEXT("Fire!!"));
        Fire();
    }
}

ATurretPawn::ATurretPawn()
{
    
}

void ATurretPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if(PlayerPawn && PlayerPawn->GetIsPlayerAlive()) LookAt(PlayerPawn->GetActorLocation());
}

void ATurretPawn::BeginPlay()
{
    Super::BeginPlay();
    GetWorld()->GetTimerManager()
        .SetTimer(FireRateTimerHandle, this, &ATurretPawn::CheckFireCondition, FireRate, true);
    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
}

void ATurretPawn::Die()
{
    Super::Die();
    UE_LOG(LogTemp, Warning, TEXT("Turret [%s] died"), *GetOwner()->GetName());
    Destroy();
}
