// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Components/HealthComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	
}

void ABasePawn::LookAt(FVector LookAtThat)
{
	FRotator TurretRotation =
		FVector(FVector(LookAtThat.X, LookAtThat.Y, TurretMesh->GetComponentLocation().Z) - TurretMesh->GetComponentLocation()).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);
	
}

void ABasePawn::Fire()
{
	UE_LOG(LogTemp, Display, TEXT("The Pawn [%s] used ABasePawn::Fire !"), *GetOwner()->GetName());
	if(ProjectileClass)
	{
		FVector SpawnVector = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnVector, SpawnRotation);
		TempProjectile->SetOwner(this);
	}
}

void ABasePawn::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("Actor [%s] died"), *GetOwner()->GetName());
	const FVector ActorLocation = GetActorLocation();
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, ActorLocation);
	UGameplayStatics::PlaySoundAtLocation(this,DieSound,ActorLocation);
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DieShake);
}


