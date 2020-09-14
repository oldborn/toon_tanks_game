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



// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
    Super::BeginPlay();
    Rotate();
	Move();
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    Move();
    Rotate();
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward",this, &APawnTank::CalculateMoveInput);
    PlayerInputComponent->BindAxis("Turn",this, &APawnTank::CalculateRotateInput);
}