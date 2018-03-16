// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawnWithInput.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"



// Sets default values
AMyPawnWithInput::AMyPawnWithInput()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Create a camera and a visible object
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMyPawnWithInput::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawnWithInput::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
	float CurrentScale = OurVisibleComponent->GetComponentScale().X;

	if (gGrooing) {
		CurrentScale += DeltaTime;
	}
	else {
		CurrentScale -= DeltaTime;
	}

	if (!CurrentVelocity.IsZero()) {
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime );
		SetActorLocation(NewLocation);
	}

}

// Called to bind functionality to input
void AMyPawnWithInput::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyPawnWithInput::JumpStart);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyPawnWithInput::JumpStop);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPawnWithInput::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPawnWithInput::MoveRight);

}

void AMyPawnWithInput::MoveForward(float Axis) {
	CurrentVelocity.X = FMath::Clamp(Axis, -1.0f, 1.0f) * 100.0f ;
}
void AMyPawnWithInput::MoveRight(float Axis) {
	CurrentVelocity.Y = FMath::Clamp(Axis, -1.0f, 1.0f) * 100.0f;
}

void AMyPawnWithInput::JumpStart() {
	gGrooing = true;
}

void AMyPawnWithInput::JumpStop() {
	gGrooing = false;
}