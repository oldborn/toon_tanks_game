// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BasePawn.h"
#include "TurretPawn.generated.h"

class APawnTank;
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurretPawn : public ABasePawn
{
	GENERATED_BODY()

private:
	FQuat RotationDirection;
	FTimerHandle FireRateTimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta = (AllowPrivateAccess = "true"))
	float Range = 800.0f;
	APawnTank* PlayerPawn;
	float DistanceBetweenPlayerPawn();
	void CheckFireCondition();
	
public:
	ATurretPawn();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Die() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
};
