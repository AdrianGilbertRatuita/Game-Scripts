// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FinalCheesePawn.generated.h"

UCLASS()
class TESTING_API AFinalCheesePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFinalCheesePawn();

	//==================================================================================================================
	//	KEY INPUTS
	//==================================================================================================================
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Input Keys", meta = (AllowPrivateAccess = "true"))
		FKey ForwardKey = EKeys::W;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Input Keys", meta = (AllowPrivateAccess = "true"))
		FKey BackwardKey = EKeys::S;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Input Keys", meta = (AllowPrivateAccess = "true"))
		FKey LeftKey = EKeys::A;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Input Keys", meta = (AllowPrivateAccess = "true"))
		FKey RightKey = EKeys::D;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Input Keys", meta = (AllowPrivateAccess = "true"))
		FKey KeyboardInteractKey = EKeys::E;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Input Keys", meta = (AllowPrivateAccess = "true"))
		FKey GamePadInteractKey = EKeys::Gamepad_FaceButton_Bottom;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Input Keys", meta = (AllowPrivateAccess = "true"))
		FKey WalkKey = EKeys::LeftShift;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Input Keys", meta = (AllowPrivateAccess = "true"))
		FKey KeyboardCameraRefocusKey = EKeys::Tab;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Input Keys", meta = (AllowPrivateAccess = "true"))
		FKey GamepadCameraRefocusKey = EKeys::Gamepad_RightStick_Down;

	//==================================================================================================================
	//	COMPONENTS
	//==================================================================================================================
	// Default Pawn Components
	UPROPERTY(VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* ArrowComponent;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent * CameraComponent;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent * CapsuleComponent;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent * SpringArmComponent;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent * InteractionMeshComponent;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent * RightHandEquipment;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent * SkeletalMeshComponent;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UPhysicsHandleComponent * PhysicsHandleComponent;

	// Cheese pawn components
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UClimbComponent * ClimbComponent;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UPickUpComponent * PickUpComponent;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCheesePawnMovement * CheesePawnMovement;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UInteractionComponent * InteractionComponent;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UFloorCheckerComponent * FloorCheckerComponent;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USpellCastingComponent * SpellCastingComponent;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCameraControllerComponent * CameraControllerComponent;

protected:

	// Initiate Pawn
	void CharacterInitialization();

	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
