// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawnWithInput.generated.h"

UCLASS()
class CPLUSTHIREDBOOKNEW_API AMyPawnWithInput : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawnWithInput();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;
	
	bool gGrooing;
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void JumpStart();
	void JumpStop();
	//Input Variables 
	FVector CurrentVelocity;
	
};
