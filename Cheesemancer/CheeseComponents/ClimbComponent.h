// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClimbComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTING_API UClimbComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClimbComponent();

	// Check for Climb Objects
	virtual void CheckForClimb();

	// Climb Up
	virtual void ClimbUp(float AxisValue);

	// Climb Down
	virtual void ClimbDown(float AxisValue);

	// Climb Left
	virtual void ClimbLeft(float AxisValue);

	// Climb Right
	virtual void ClimbRight(float AxisValue);

	// Climb based on left stick axis
	virtual void LeftStickClimbX(float AxisValue);

	// Climb based on right stick axis
	virtual void LeftStickClimbY(float AxisValue);

	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Climbing", meta = (AllowPrivateAccess = "true"))
		FName BackSocket;

	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Climbing", meta = (AllowPrivateAccess = "true"))
		FName RightHandSocket;

	// Is the player climbing?
	/** Boolean to check if the player is climbing */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Climbing", meta = (AllowPrivateAccess = "true"))
		bool bClimbing;

	// Is climbing Frozen
	/** Boolean to check if the player can climb */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Climbing", meta = (AllowPrivateAccess = "true"))
		bool bClimbingFrozen;

	// How fast can the player vertically climb?
	/** Speed modifier for vertical climbing */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Climbing", meta = (AllowPrivateAccess = "true"))
		float VerticalClimbSpeed;

	// How fast can the player horizontally climb?
	/** Speed modifier for horizontal climbing */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Climbing", meta = (AllowPrivateAccess = "true"))
		float HorizontalClimbSpeed;

	// How fast can the player climb based on Left Stick movement?
	/** Speed modifier for climbing with the Left Stick */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Climbing", meta = (AllowPrivateAccess = "true"))
		float StickBasedClimbSpeed;

	// How far should the forward probe check for?
	/** Check distance for forward probe */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Climbing", meta = (AllowPrivateAccess = "true"))
		float ForwardProbeDistance;
	
	// How far should the vertical probe check for?
	/** Check distance for vertical probe */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Climbing", meta = (AllowPrivateAccess = "true"))
		float VerticalCheckDistance;

	// How much should we offset the the forward start of the probe?
	/** Modifier for forward probe start */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Climbing", meta = (AllowPrivateAccess = "true"))
		float ProbeStartOffsetModifier;

	// How much should we offset the the vertical start of the probe?
	/** Modifier for vertical probe start */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Climbing", meta = (AllowPrivateAccess = "true"))
		float ProbeVerticalOffset;

	// What is the tag associated wih climb objects?
	/** Tag for Climb Objects */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Climbing", meta = (AllowPrivateAccess = "true"))
		FName ClimbTag;

	// Freeze climbing action
	/** Function to call to freeze plaer climbing */
	UFUNCTION(BlueprintCallable, Category = "Character Control - Climbing", meta = (AllowPrivateAccess = "true"))
		void FreezeClimbing();

	// Unfreeze climbing action
	/** Function to call to unfreeze plaer climbing */
	UFUNCTION(BlueprintCallable, Category = "Character Control - Climbing", meta = (AllowPrivateAccess = "true"))
		void UnfreezeClimbing();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Start Climbing
	virtual void BeginClimb(FHitResult * HitTest);

	// End Climbing
	virtual void EndClimb();

	// Function for checking forward with default parameters
	virtual FHitResult * ProbeCheck();

	// Function for checking forward with changeable parameters
	virtual FHitResult * ProbeCheck(FVector Start, FVector End);

	class AFinalCheesePawn * PawnReference;

	class UCapsuleComponent * CapsuleReference;

	class UCheesePawnMovement * MovementReference;

	class UStaticMeshComponent * RightHandReference;

	class UInteractionComponent * InteractionReference;

	class UFloorCheckerComponent * FloorCheckerReference;

	class USkeletalMeshComponent * SkeletalMeshReference;

	class UCheesePawnAnimationInstance * CheeseAnimInstance;

	class UCameraControllerComponent * CameraControllerReference;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
