// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"

APawnTank::APawnTank()
{
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArmComponent->SetupAttachment(RootComponent);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
    CameraComponent->SetupAttachment(SpringArmComponent);
}

void APawnTank::CalculateMoveInput(float Value)
{
    MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds,0,0);
}

void APawnTank::CalculateRotateInput(float Value)
{
    float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
    FRotator Rotation = FRotator(0,RotateAmount,0);
    RotationDirection = FQuat(Rotation);
}

void APawnTank::Move()
{
       AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
    AddActorLocalRotation(RotationDirection, true);
}

void APawnTank::LookAtCursor()
{
    if(PlayerController)
    {
        FHitResult HitResult;
        if(PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
        {
            LookAt(HitResult.ImpactPoint);
        }
    }
}


// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
    Super::BeginPlay();
    PlayerController = Cast<APlayerController>(GetController());
}

void APawnTank::Die()
{
    Super::Die();
    bIsPlayerAlive = false;
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

bool APawnTank::GetIsPlayerAlive() const
{
    return bIsPlayerAlive;
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    Move();
    Rotate();
    LookAtCursor();
}

void APawnTank::Fire()
{
    Super::Fire();
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward",this, &APawnTank::CalculateMoveInput);
    PlayerInputComponent->BindAxis("Turn",this, &APawnTank::CalculateRotateInput);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}