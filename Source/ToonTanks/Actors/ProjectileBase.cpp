// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	//ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = ProjectileMesh;
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovementComponent->InitialSpeed = Speed;
	ProjectileMovementComponent->MaxSpeed = Speed * Speed;

	ParticleTrailSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Trail System Component"));
	ParticleTrailSystemComponent->SetupAttachment(RootComponent);
	
	InitialLifeSpan = 3.0f;
	
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit!"));
	UGameplayStatics::PlaySoundAtLocation(this,HitSound,GetActorLocation());
	
	AActor* MyOwner = GetOwner();
	if(!MyOwner) return;
	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), MyOwner, DamageType);
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitShake);
	}

	Destroy();
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	UGameplayStatics::PlaySoundAtLocation(this,LaunchSound,GetActorLocation());
}


