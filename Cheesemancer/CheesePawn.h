// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CheesePawn.generated.h"

UCLASS()
class TESTING_API ACheesePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACheesePawn();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//==================================================================================================================
	//	SOCKET TAGS
	//==================================================================================================================
	//
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Socket Names", meta = (AllowPrivateAccess = "true"))
		FName ItemHatSocketName;
	//
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Socket Names", meta = (AllowPrivateAccess = "true"))
		FName RightHandStaffSocketName;
	////
	//UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Socket Names", meta = (AllowPrivateAccess = "true"))
	//	FName LeftHandPickupSocket;
	//
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Socket Names", meta = (AllowPrivateAccess = "true"))
		FName BackStaffSocketName;

	//==================================================================================================================
	//	INTERACTION TAGS
	//==================================================================================================================
	//
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Game Tags", meta = (AllowPrivateAccess = "true"))
		FName PickUpTag;
	//
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Game Tags", meta = (AllowPrivateAccess = "true"))
		FName ClimbTag;
	//
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Game Tags", meta = (AllowPrivateAccess = "true"))
		FName LedgeTag;
	//
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Game Tags", meta = (AllowPrivateAccess = "true"))
		FName MushroomTag;

	//==================================================================================================================
	//	KEY INPUTS
	//==================================================================================================================
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Input Keys", meta = (AllowPrivateAccess = "true"))
		FKey ForwardKey = EKeys::W;
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Input Keys", meta = (AllowPrivateAccess = "true"))
		FKey BackwardKey = EKeys::S;
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Input Keys", meta = (AllowPrivateAccess = "true"))
		FKey LeftKey = EKeys::A;
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Input Keys", meta = (AllowPrivateAccess = "true"))
		FKey RightKey = EKeys::D;
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Input Keys", meta = (AllowPrivateAccess = "true"))
		FKey WalkKey = EKeys::LeftShift;
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Input Keys", meta = (AllowPrivateAccess = "true"))
		FKey Keyboard_InteractKey = EKeys::E;
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Input Keys", meta = (AllowPrivateAccess = "true"))
		FKey Controller_InteractKey = EKeys::Gamepad_FaceButton_Bottom;

	//==================================================================================================================
	//	CHARACTER SETTINGS
	//==================================================================================================================
	//
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		float CharacterWalkSpeed;
	//
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		float CharacterSprintSpeed;
	//
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		float CharacterClimbSpeed;
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		float LedgeJumpHeight;
	//
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Movement", meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1", AllowPrivateAccess = "true"))
		float MinimumValueToNotSprint;
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Movement", meta = (AllowPrivateAccess = "true"))
		FVector FinalLedgePosition;

	//==================================================================================================================
	//	CAMERA SETTINGS
	//==================================================================================================================
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Camera", meta = (AllowPrivateAccess = "true"))
		float CameraDistance;
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Camera", meta = (AllowPrivateAccess = "true"))
		float CameraZoomSpeed;
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Camera", meta = (ClampMin = "0", ClampMax = "500", UIMin = "0", UIMax = "500", AllowPrivateAccess = "true"))
		float CameraYawMoveSpeed;
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Camera", meta = (ClampMin = "0", ClampMax = "500", UIMin = "0", UIMax = "500", AllowPrivateAccess = "true"))
		float CameraPitchMoveSpeed;
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Camera", meta = (AllowPrivateAccess = "true"))
		bool CameraInvertYaw;
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Camera", meta = (AllowPrivateAccess = "true"))
		bool CameraInvertPitch;
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Camera", meta = (AllowPrivateAccess = "true"))
		FVector2D CameraZoomLimits;
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Camera", meta = (AllowPrivateAccess = "true"))
		FVector CameraRelativeOffset;

	//==================================================================================================================
	//	TOTAL MUSHROOM COUNT
	//==================================================================================================================
	//
	UPROPERTY(BlueprintReadWrite, Category = "Character Inventory", meta = (AllowPrivateAccess = "true"))
		float MushroomCount;

	//==================================================================================================================
	//	CURRENT HELD ITEMS
	//==================================================================================================================
	//
	UPROPERTY(BlueprintReadWrite, Category = "Character Inventory", meta = (AllowPrivateAccess = "true"))
		AActor* HatHeldItem;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Inventory", meta = (AllowPrivateAccess = "true"))
		AActor* StaffHeldItem;
	////
	//UPROPERTY(BlueprintReadWrite, Category = "Character Inventory", meta = (AllowPrivateAccess = "true"))
	//	AActor* HandHeldItem;

	//==================================================================================================================
	//	OVERLAP LISTS
	//==================================================================================================================
	//
	TArray<AActor*> OverlappedPickupItems;
	//
	TArray<AActor*> OverlappedMushroomItems;

	//==================================================================================================================
	//	CHARACTER STATES
	//==================================================================================================================
	// Is character picking something up
	UPROPERTY(BlueprintReadWrite, Category = "Character Control - State", meta = (AllowPrivateAccess = "true"))
		bool IsPickingStuffUp;
	// Is character falling
	UPROPERTY(BlueprintReadWrite, Category = "Character Control - State", meta = (AllowPrivateAccess = "true"))
		bool IsFalling;
	// Is character on the ground
	UPROPERTY(BlueprintReadWrite, Category = "Character Control - State", meta = (AllowPrivateAccess = "true"))
		bool IsGrounded;
	// Is character on the ground
	UPROPERTY(BlueprintReadWrite, Category = "Character Control - State", meta = (AllowPrivateAccess = "true"))
		bool IsWalking;
	// Is character currently climbing
	UPROPERTY(BlueprintReadWrite, Category = "Character Control - State", meta = (AllowPrivateAccess = "true"))
		bool IsClimbing;
	// Is character climbing ledges
	UPROPERTY(BlueprintReadWrite, Category = "Character Control - State", meta = (AllowPrivateAccess = "true"))
		bool IsLedgeClimbing;

	//==================================================================================================================
	//	ANIMATION BLUEPRINT - CHARACTER CONTROL
	//==================================================================================================================
	// Is character movement freezed
	UPROPERTY(BlueprintReadOnly, Category = "Pawn Animation Hook", meta = (AllowPrivateAccess = "true"))
		bool IsMovementFreezed;
	// Is character gravity enabled
	UPROPERTY(BlueprintReadOnly, Category = "Pawn Animation Hook", meta = (AllowPrivateAccess = "true"))
		bool IsGravityEnabled;

	//==================================================================================================================
	//	ANIMATION BLUEPRINT - INPUT DATA
	//==================================================================================================================
	// Value to check if Key is pressed
	UPROPERTY(BlueprintReadOnly, Category = "Pawn Animation Hook", meta = (AllowPrivateAccess = "true"))
		float ForwardPress;
	// Value to check if Key is pressed
	UPROPERTY(BlueprintReadOnly, Category = "Pawn Animation Hook", meta = (AllowPrivateAccess = "true"))
		float BackwardPress;
	// Value to check if Key is pressed
	UPROPERTY(BlueprintReadOnly, Category = "Pawn Animation Hook", meta = (AllowPrivateAccess = "true"))
		float LeftPress;
	// Value to check if Key is pressed
	UPROPERTY(BlueprintReadOnly, Category = "Pawn Animation Hook", meta = (AllowPrivateAccess = "true"))
		float RightPress;
	// Value to check if Key is pressed
	UPROPERTY(BlueprintReadOnly, Category = "Pawn Animation Hook", meta = (AllowPrivateAccess = "true"))
		float InteractPress;
	// Value to check if left thumbstick is moved
	UPROPERTY(BlueprintReadOnly, Category = "Pawn Animation Hook", meta = (AllowPrivateAccess = "true"))
		float LeftThumbstickMoveX;
	// Value to check if left thumbstick is moved
	UPROPERTY(BlueprintReadOnly, Category = "Pawn Animation Hook", meta = (AllowPrivateAccess = "true"))
		float LeftThumbstickMoveY;
	// Value to check if left thumbstick is moved
	UPROPERTY(BlueprintReadOnly, Category = "Pawn Animation Hook", meta = (AllowPrivateAccess = "true"))
		float RightThumbStickMoveX;
	// Value to check if left thumbstick is moved
	UPROPERTY(BlueprintReadOnly, Category = "Pawn Animation Hook", meta = (AllowPrivateAccess = "true"))
		float RightThumbStickMoveY;

	//==================================================================================================================
	//	CHARACTER COMPONENTS
	//==================================================================================================================
	// Capsule component for player collider
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* CapsuleComponent;

	// Skeletal Mesh for Character Model
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* SkeletalMesh;

	// Spring Arm component for Camera Retract and Control
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;

	// Player Camera
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

	// Static Mesh for Interaction Mesh
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* InteractMesh;

	//==================================================================================================================
	//	PLAYER DATA GETTER FUNCTIONS
	//==================================================================================================================
	// Get Current Camrea Rotation
	UFUNCTION(BlueprintCallable, Category = "Character Control - Get Data", meta = (AllowPrivateAccess = "true"))
		FRotator GetCameraRotation();
	// Get Current Player Rotation
	UFUNCTION(BlueprintCallable, Category = "Character Control - Get Data", meta = (AllowPrivateAccess = "true"))
		FRotator GetPlayerRotation();
	// Get Player current forward axis based on Camera
	UFUNCTION(BlueprintCallable, Category = "Character Control - Get Data", meta = (AllowPrivateAccess = "true"))
		FVector GetPlayerForwardAxis(float AxisValue, bool IgnoreZ);
	// Get Player current right axis based on Camera
	UFUNCTION(BlueprintCallable, Category = "Character Control - Get Data", meta = (AllowPrivateAccess = "true"))
		FVector GetPlayerRightAxis(float AxisValue, bool IgnoreZ);
	// Get Player current forward direction based on Camera
	UFUNCTION(BlueprintCallable, Category = "Character Control - Get Data", meta = (AllowPrivateAccess = "true"))
		FVector GetPlayerForwardDirection(float AxisValue, bool IgnoreZ);
	// Get Player current backward direction based on Camera
	UFUNCTION(BlueprintCallable, Category = "Character Control - Get Data", meta = (AllowPrivateAccess = "true"))
		FVector GetPlayerBackwardDirection(float AxisValue, bool IgnoreZ);
	// Get Player current left direction based on Camera
	UFUNCTION(BlueprintCallable, Category = "Character Control - Get Data", meta = (AllowPrivateAccess = "true"))
		FVector GetPlayerLeftDirection(float AxisValue, bool IgnoreZ);
	// Get Player current right direction based on Camera
	UFUNCTION(BlueprintCallable, Category = "Character Control - Get Data", meta = (AllowPrivateAccess = "true"))
		FVector GetPlayerRightDirection(float AxisValue, bool IgnoreZ);

	//==================================================================================================================
	//	PLAYER MANIPULATION FUNCTIONS
	//==================================================================================================================
	// Freeze character movement
	UFUNCTION(BlueprintCallable, Category = "Character Control - Manipulate Character", meta = (AllowPrivateAccess = "true"))
		void FreezeMovement();
	// Free character movement within set time
		void FreezeMovement(float FreezeLength);
	//	Unfreeze character movement
	UFUNCTION(BlueprintCallable, Category = "Character Control - Manipulate Character", meta = (AllowPrivateAccess = "true"))
		void UnfreezeMovement();
	//
	UFUNCTION(BlueprintCallable, Category = "Character Control - Manipulate Character", meta = (AllowPrivateAccess = "true"))
		void DisableGravity();
	//
	UFUNCTION(BlueprintCallable, Category = "Character Control - Manipulate Character", meta = (AllowPrivateAccess = "true"))
		void EnableGravity();

	//==================================================================================================================
	//	PLAYER OVERLAP EVENTS
	//==================================================================================================================
	//
	UFUNCTION(BlueprintCallable, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		void PickupOverlapBegin(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);
	//
	UFUNCTION(BlueprintCallable, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		void PickupOverlapExit(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);
	//
	UFUNCTION(BlueprintCallable, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		void MushroomOverlapBegin(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);
	//
	UFUNCTION(BlueprintCallable, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		void MushroomOverlapExit(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);
	//
	UFUNCTION(BlueprintCallable, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		void LedgeOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

	//==================================================================================================================
	//	PLAYER INPUT EVENT HANDLERS
	//==================================================================================================================
	// Key Press Events
	void Interact();
	void InteractRelease();
	void WalkingPress();
	void WalkingRelease();
	void MoveForward(float AxisValue);
	void MoveBackward(float AxisValue);
	void MoveLeft(float AxisValue);
	void MoveRight(float AxisValue);
	// Mouse Control
	void Zoom(float AxisValue);
	void MouseMoveX(float AxisValue);
	void MouseMoveY(float AxisValue);
	// ControllerMapping
	void LeftThumbstickX(float AxisValue);
	void LeftThumbstickY(float AxisValue);
	void RightThunbstickX(float AxisValue);
	void RightThunbstickY(float AxisValue);

	//==================================================================================================================
	//	TICK BASED EXECUTED FUNCTIONS
	//==================================================================================================================
	void InputCombination();
	void FloorCheck();
	void ControllerWalksSprintCheck();
	void PickUpClosestItem();
	void PickUpClosestMushroom();
	void UpdateSocketPositions();
	void LedgeTransition();
	void LedgePositionCheck();

	//==================================================================================================================
	//	CODE BASED CALLABLE FUNCTIONS
	//==================================================================================================================
	void EnableActorGravity(AActor* Actor);
	void DisableActorGravity(AActor* Actor);

	//==================================================================================================================
	void CharacterInitialization();

	UFUNCTION(BlueprintCallable, Category = "Character Control - Getter", meta = (AllowPrivateAccess = "true"))
		UInputComponent* GetInputComponent();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
