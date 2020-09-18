// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanks/GameModes/ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
UHealthComponent::UHealthComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

}

// Called when the game starts or when spawned
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = DefaultHealth;
	GameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCause)
{
	if(Damage == 0) return;

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);
	if(Health <= 0)
	{
		if (GameMode)
		{
			GameMode->ActorDied(GetOwner());
		}else
		{
			UE_LOG(LogTemp, Error, TEXT("Health Component of [%s] has no GameMode Reference."), *GetOwner()->GetName());
		}
	}
}


