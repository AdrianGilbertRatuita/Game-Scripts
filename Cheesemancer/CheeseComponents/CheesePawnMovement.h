// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CheesePawnMovement.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTING_API UCheesePawnMovement : public UActorComponent
{

	GENERATED_BODY()

public:	

	//
	UCheesePawnMovement();

	// Is the player currently walking?
	/** Boolean for checking if the player is walking */
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		bool bIsWalking;

	// Is player movement frozen?
	/** Boolean for checking if movement is frozen */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		bool bMovementFrozen;

	// Is player animation frozen?
	/** Boolean for checking if animation is frozen */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		bool bAnimationFrozen;

	// How fast is the player sprinting?
	/** Speed modifier for player sprint */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		float CharacterSprintSpeed;

	// How fast is the player walking?
	/** Speed modifier for player walk */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		float CharacterWalkSpeed;

	// Did the player move Left stick X axis of stick?
	/** Float to check for Left Stick X axis changes */
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		float XStickMovement = 0;

	// Did the player move Left stick Y axis of stick?
	/** Float to check for Left Stick Y axis changes */
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		float YStickMovement = 0;

	// Did the player press the forward key?
	/** Float to check for forward key presses */
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		float ForwardPress = 0;

	// Did the player press the backward key?
	/** Float to check for backward key presses */
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		float BackwardPress = 0;

	// Did the player press the left key?
	/** Float to check for left key presses */
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		float LeftPress = 0;

	// Did the player press the right key?
	/** Float to check for right key presses */
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		float RightPress = 0;

	// Did the player press the right key?
	/** Float to check for right key presses */
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		float MinimumToStickWalk = 0.65f;

	// Call to disable all movement from input
	/** Function to call to freeze all movement */
	UFUNCTION(BlueprintCallable, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		virtual void FreezeMovement();

	// Call to enable all movement from input
	/** Function to call to unfreeze all movement */
	UFUNCTION(BlueprintCallable, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		virtual void UnfreezeMovement();

	// Call to disable all animation
	/** Function to call to freeze all animation */
	UFUNCTION(BlueprintCallable, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		virtual void FreezeAnimation();

	// Call to enable all animation
	/** Function to call to unfreeze all animation */
	UFUNCTION(BlueprintCallable, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		virtual void UnfreezeAnimation();

	// Call to turn on player gravity
	/** Function to call to enable gravity */
	UFUNCTION(BlueprintCallable, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		virtual void EnableGravity();

	// Call to turn off player gravity
	/** Function to call to disable gravity */
	UFUNCTION(BlueprintCallable, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		virtual void DisableGravity();

	//
	virtual void StartWalking();

	//
	virtual void EndWalking();

	//
	virtual void LeftStickXMove(float AxisValue);

	//
	virtual void LeftStickYMove(float AxisValue);

	//
	virtual void MoveForward(float AxisValue);

	//
	virtual void MoveBackward(float AxisValue);

	//
	virtual void MoveLeft(float AxisValue);

	//
	virtual void MoveRight(float AxisValue);

	//
	virtual void StickCheckForWalk();

	//
	virtual void StickActorRotationFix();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class AFinalCheesePawn * PawnReference;

	class UCapsuleComponent * CapsuleReference;

	class USkeletalMeshComponent * SkeletalMeshReference;

	class UCheesePawnAnimationInstance * CheeseAnimInstance;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	
};
