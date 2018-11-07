// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class ALCHEMYBACKUPSTUFF_API ABasePawn : public APawn
{

	GENERATED_BODY()

public:

	// Sets default values for this pawn's properties
	ABasePawn();
	
	// Capsule Collider
	UPROPERTY(EditAnywhere, Category = "Components")
		class UCapsuleComponent* Capsule;
	// Static Mesh for something?
	UPROPERTY(EditAnywhere, Category = "Components")
		class UStaticMeshComponent* StaticMesh;
	// Skeletal Mesh for Character Models
	UPROPERTY(EditAnywhere, Category = "Components")
		class USkeletalMeshComponent* SkeletalMesh;
	// Camera for Player
	UPROPERTY(EditAnywhere, Category = "Components")
		class UCameraComponent* Camera;
	// Camera Boom to keep the camera at a certain distance
	UPROPERTY(EditAnywhere, Category = "Components")
		class USpringArmComponent* SpringArm;
	// Character move speed
	UPROPERTY(EditAnywhere, Category = "Character")
		float CharacterMoveSpeed;
	// Invert yaw axis of camera?
	UPROPERTY(EditAnywhere, Category = "Character")
		bool IsCameraYawInverted = false;
	// Invert pitch axis of camera?
	UPROPERTY(EditAnywhere, Category = "Character")
		bool IsCameraPitchInverted = false;
	// Distance of Camera to Camera Boom center
	UPROPERTY(EditAnywhere, Category = "Character")
		float CameraDistance = 400.0f;
	UPROPERTY(EditAnywhere, Category = "Character")
		float CameraHeightOffset = 100.0f;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HandleInput();

	// Remove this override for Implementation
	virtual void AddControllerPitchInput(float Val) override;

	// Remove this override for Implementation
	virtual void AddControllerYawInput(float Val) override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
