// Fill out your copyright notice in the Description page of Project Settings.

#include "CheesePawn.h"

#include "Engine/Engine.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"

//
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Called every frame
void ACheesePawn::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	if (!IsMovementFreezed)
	{

		InputCombination();
		FloorCheck();
		ControllerWalksSprintCheck();

	}

}

#pragma region PLAYER INITIALIZATION

// Sets default values
ACheesePawn::ACheesePawn()
{

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	InteractMesh = CreateDefaultSubobject<UStaticMeshComponent>("InteractionMesh");
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapusleComponent");
	RootComponent = Cast<USceneComponent>(CapsuleComponent);

	//
	Controller = GetController();

	//
	SpringArm->SetupAttachment(RootComponent);

	//
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);


}

// Called when the game starts or when spawned
void ACheesePawn::BeginPlay()
{
	Super::BeginPlay();

	//
	CharacterInitialization();

	//
	InteractMesh->OnComponentBeginOverlap.AddDynamic(this, &ACheesePawn::PickupOverlapBegin);
	InteractMesh->OnComponentEndOverlap.AddDynamic(this, &ACheesePawn::PickupOverlapExit);
	InteractMesh->OnComponentBeginOverlap.AddDynamic(this, &ACheesePawn::MushroomOverlapBegin);
	InteractMesh->OnComponentEndOverlap.AddDynamic(this, &ACheesePawn::MushroomOverlapExit);

}

/**

Initialize Player Settings

*/
void ACheesePawn::CharacterInitialization()
{

	//
	SpringArm->TargetArmLength = CameraDistance;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;

	//
	CapsuleComponent->SetSimulatePhysics(true);
	CapsuleComponent->SetEnableGravity(true);

	//
	Camera->SetRelativeLocation(CameraRelativeOffset);

	//
	IsFalling = false;
	IsGrounded = false;
	IsClimbing = false;
	IsWalking = false;
	IsLedgeClimbing = false;
	IsPickingStuffUp = false;
	IsMovementFreezed = false;
	IsGravityEnabled = true;

}

// Called to bind functionality to input
void ACheesePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//
	InputComponent = PlayerInputComponent;

	// Keyboard Bindings
	InputComponent->BindAxisKey(ForwardKey, this, &ACheesePawn::MoveForward);
	InputComponent->BindAxisKey(BackwardKey, this, &ACheesePawn::MoveBackward);
	InputComponent->BindAxisKey(LeftKey, this, &ACheesePawn::MoveLeft);
	InputComponent->BindAxisKey(RightKey, this, &ACheesePawn::MoveRight);
	InputComponent->BindKey(WalkKey, EInputEvent::IE_Pressed, this, &ACheesePawn::WalkingPress);
	InputComponent->BindKey(WalkKey, EInputEvent::IE_Released, this, &ACheesePawn::WalkingRelease);
	InputComponent->BindKey(Keyboard_InteractKey, EInputEvent::IE_Pressed, this, &ACheesePawn::Interact);

	// Controller Bindings
	InputComponent->BindAxisKey(EKeys::Gamepad_LeftX, this, &ACheesePawn::LeftThumbstickX);
	InputComponent->BindAxisKey(EKeys::Gamepad_LeftY, this, &ACheesePawn::LeftThumbstickY);
	InputComponent->BindAxisKey(EKeys::Gamepad_RightX, this, &ACheesePawn::RightThunbstickX);
	InputComponent->BindAxisKey(EKeys::Gamepad_RightY, this, &ACheesePawn::RightThunbstickY);
	InputComponent->BindKey(Controller_InteractKey, EInputEvent::IE_Pressed, this, &ACheesePawn::Interact);

	// Mouse Bindings
	InputComponent->BindAxisKey(EKeys::MouseX, this, &ACheesePawn::MouseMoveX);
	InputComponent->BindAxisKey(EKeys::MouseY, this, &ACheesePawn::MouseMoveY);
	InputComponent->BindAxisKey(EKeys::MouseWheelAxis, this, &ACheesePawn::Zoom);


}
#pragma endregion

#pragma region ENVIRONMENT CHECKS

/**
	Check if floor is within range
*/
void ACheesePawn::FloorCheck()
{

	FHitResult* HitTest = new FHitResult();
	FVector Self = GetActorLocation();
	FVector Trace = Self + ((GetActorUpVector() * -1) * CapsuleComponent->GetScaledCapsuleHalfHeight() * 2);
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

	if (!GetWorld()->LineTraceSingleByChannel(*HitTest, GetActorLocation(), Trace, ECC_Visibility, *TraceParams))
	{

		CapsuleComponent->SetLinearDamping(1.0f);
		CapsuleComponent->SetAngularDamping(1.0f);

	}
	else if (GetWorld()->LineTraceSingleByChannel(*HitTest, GetActorLocation(), Trace, ECC_Visibility, *TraceParams))
	{

		CapsuleComponent->SetLinearDamping(5.0f);
		CapsuleComponent->SetAngularDamping(5.0f);

	}

}

/**
	Check if floor is within range
*/
void ACheesePawn::ControllerWalksSprintCheck()
{

	if (LeftThumbstickMoveX != 0 || LeftThumbstickMoveY != 0)
	{

		if (FMath::Abs<float>(LeftThumbstickMoveX) + FMath::Abs<float>(LeftThumbstickMoveY) > MinimumValueToNotSprint)
		{

			IsWalking = false;

		}
		else
		{

			IsWalking = true;

		}

	}

}


#pragma endregion

#pragma region OVERLAP EVENTS HANDLERS

void ACheesePawn::PickupOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (OtherActor->ActorHasTag(PickUpTag))
	{

		if (!OverlappedPickupItems.Contains(OtherActor) && OtherActor != nullptr)
		{

			OverlappedPickupItems.Add(OtherActor);

		}

	}

}

void ACheesePawn::PickupOverlapExit(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{

	if (OtherActor->ActorHasTag(PickUpTag))
	{

		if (OverlappedPickupItems.Contains(OtherActor) && OtherActor != nullptr)
		{

			OverlappedPickupItems.Remove(OtherActor);

		}

	}

}

void ACheesePawn::MushroomOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (OtherActor->ActorHasTag(MushroomTag))
	{

		if (!OverlappedMushroomItems.Contains(OtherActor) && OtherActor != nullptr)
		{

			OverlappedMushroomItems.Add(OtherActor);

		}

	}

}

void ACheesePawn::MushroomOverlapExit(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{

	if (OtherActor->ActorHasTag(MushroomTag))
	{

		if (OverlappedMushroomItems.Contains(OtherActor) && OtherActor != nullptr)
		{

			OverlappedMushroomItems.Remove(OtherActor);

		}

	}

}

void ACheesePawn::LedgeOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

#pragma region OVERLAP FUNCION HELPERS

void ACheesePawn::PickUpClosestItem()
{

	AActor* Item = OverlappedPickupItems[0];
	for (int i = 1; i < OverlappedPickupItems.Num(); i++)
	{

		if (FVector().Distance(Item->GetActorLocation(), GetActorLocation())
	> FVector().Distance(OverlappedPickupItems[i]->GetActorLocation(), GetActorLocation()))
		{

			Item = OverlappedPickupItems[i];

		}

	}

	if (Item != nullptr)
	{

		HeldItem = Item;
		IsPickingStuffUp = true;
		UStaticMeshComponent* GravityDisable = Cast<UStaticMeshComponent>(HeldItem->GetRootComponent());
		GravityDisable->SetEnableGravity(false);

	}

}

void ACheesePawn::PickUpClosestMushroom()
{

	AActor* Item = OverlappedMushroomItems[0];

	for (int i = 1; i < OverlappedMushroomItems.Num(); i++)
	{

		if (FVector().Distance(Item->GetActorLocation(), GetActorLocation())
	> FVector().Distance(OverlappedMushroomItems[i]->GetActorLocation(), GetActorLocation()))
		{

			Item = OverlappedMushroomItems[i];

		}

	}

	if (Item != nullptr && OverlappedMushroomItems.Contains(Item))
	{

		IsPickingStuffUp = true;
		MushroomCount += 1;
		OverlappedMushroomItems.Remove(Item);
		Item->Destroy();

	}

}

void ACheesePawn::RaycastCheck()
{
}

#pragma endregion

#pragma endregion

#pragma region INPUT EVENTS HANDLERS

/**
	Interact with objects
*/
void ACheesePawn::Interact()
{

	if (OverlappedPickupItems.Num() != 0)
	{

		PickUpClosestItem();

	}
	if (OverlappedMushroomItems.Num() != 0)
	{

		PickUpClosestMushroom();

	}

}

/**
	Move player forward
*/
void ACheesePawn::MoveForward(float AxisValue)
{

	//
	ForwardPress = AxisValue;
	//
	FVector FinalPosition = GetActorLocation() + GetPlayerForwardDirection(AxisValue, true) * (IsWalking ? CharacterWalkSpeed : CharacterSprintSpeed) * GetWorld()->GetDeltaSeconds();
	SetActorLocation(FinalPosition);

}

/**
	Move player backward
*/
void ACheesePawn::MoveBackward(float AxisValue)
{

	//
	BackwardPress = AxisValue;
	//
	FVector FinalPosition = GetActorLocation() + GetPlayerBackwardDirection(AxisValue, true) * (IsWalking ? CharacterWalkSpeed : CharacterSprintSpeed) * GetWorld()->GetDeltaSeconds();
	SetActorLocation(FinalPosition);

}

/**
	Move player left
*/
void ACheesePawn::MoveLeft(float AxisValue)
{

	//
	LeftPress = AxisValue;
	//
	FVector FinalPosition = GetActorLocation() + GetPlayerLeftDirection(AxisValue, true) * (IsWalking ? CharacterWalkSpeed : CharacterSprintSpeed) * GetWorld()->GetDeltaSeconds();
	SetActorLocation(FinalPosition);

}

/**
	Move player right
*/
void ACheesePawn::MoveRight(float AxisValue)
{

	//
	RightPress = AxisValue;
	//
	FVector FinalPosition = GetActorLocation() + GetPlayerRightDirection(AxisValue, true) * (IsWalking ? CharacterWalkSpeed : CharacterSprintSpeed) * GetWorld()->GetDeltaSeconds();
	SetActorLocation(FinalPosition);

}

/**
	Walking is true if Walk key is pressed
*/
void ACheesePawn::WalkingPress()
{

	IsWalking = true;

}

/**
	Walking is false if Walk key was released
*/
void ACheesePawn::WalkingRelease()
{

	IsWalking = false;

}

/**
	Move player at the right axis using the Controller
*/
void ACheesePawn::LeftThumbstickX(float AxisValue)
{

	//
	LeftThumbstickMoveX = AxisValue;
	if (AxisValue != 0)
	{

		FVector FinalPosition = GetActorLocation() + GetPlayerForwardAxis(AxisValue, true) * (IsWalking ? CharacterWalkSpeed : CharacterSprintSpeed) * GetWorld()->GetDeltaSeconds();
		SetActorLocation(FinalPosition);

	}

}

/**
	Move player at the forward axis using the Controller 
*/
void ACheesePawn::LeftThumbstickY(float AxisValue)
{

	//
	LeftThumbstickMoveY = AxisValue;
	if (AxisValue != 0)
	{

		FVector FinalPosition = GetActorLocation() + GetPlayerRightAxis(AxisValue, true) * (IsWalking ? CharacterWalkSpeed : CharacterSprintSpeed) * GetWorld()->GetDeltaSeconds();
		SetActorLocation(FinalPosition);

	}

}

/**
	Adjust Camera Yaw relative to player using the Controller
*/
void ACheesePawn::RightThunbstickX(float AxisValue)
{

	//
	RightThumbStickMoveX = AxisValue;
	AddControllerYawInput(AxisValue * (CameraInvertYaw ? -1 : 1) * CameraYawMoveSpeed * GetWorld()->GetDeltaSeconds());

}

/**
	Adjust Camera Pitch relative to player using the Controller
*/
void ACheesePawn::RightThunbstickY(float AxisValue)
{

	//
	RightThumbStickMoveY = AxisValue;
	AddControllerPitchInput(AxisValue * (CameraInvertPitch ? 1 : -1) * CameraPitchMoveSpeed * GetWorld()->GetDeltaSeconds());

}

/**
	Adjust Camera Yaw relative to player using the Mouse
*/
void ACheesePawn::MouseMoveX(float AxisValue)
{

	AddControllerYawInput(AxisValue * (CameraInvertYaw ? -1 : 1) * CameraYawMoveSpeed * GetWorld()->GetDeltaSeconds());

}

/**
	Adjust Camera Pitch relative to player using the Mouse
*/
void ACheesePawn::MouseMoveY(float AxisValue)
{

	AddControllerPitchInput(AxisValue * (CameraInvertPitch ? -1 : 1) * CameraPitchMoveSpeed * GetWorld()->GetDeltaSeconds());

}

/**
	Shorten or extend Camera boom
*/
void ACheesePawn::Zoom(float AxisValue)
{

	SpringArm->TargetArmLength -= AxisValue * CameraZoomSpeed * GetWorld()->GetDeltaSeconds();
	FMath().Clamp<float>(SpringArm->TargetArmLength, CameraZoomLimits.X, CameraZoomLimits.Y);

}


/**
	Determine combination presses and rotate player to match direction
*/
void ACheesePawn::InputCombination()
{

	//
	FRotator FaceDirection = GetActorRotation();
	// Forward
	if (ForwardPress > 0)
	{

		FaceDirection = FMath().Lerp(GetActorRotation(), GetControlRotation(), 0.1f);
		FaceDirection.Pitch = 0.0f;
		FaceDirection.Roll = 0.0f;

		//
		SetActorRotation(FaceDirection);

	}
	// Backward
	if (BackwardPress > 0)
	{

		//
		FRotator Goal = GetControlRotation();
		Goal.Yaw -= 180;
		Goal.Pitch = 0.0f;
		Goal.Roll = 0.0f;

		//
		FaceDirection = FMath().Lerp(GetActorRotation(), Goal, 0.1f);

		//
		SetActorRotation(FaceDirection);

	}
	// Left
	if (LeftPress > 0)
	{

		//
		FRotator Goal = GetControlRotation();
		Goal.Yaw -= 90;
		Goal.Pitch = 0.0f;
		Goal.Roll = 0.0f;

		//
		FaceDirection = FMath().Lerp(GetActorRotation(), Goal, 0.1f);

		//
		SetActorRotation(FaceDirection);

	}
	// Left
	if (RightPress > 0)
	{

		//
		FRotator Goal = GetControlRotation();
		Goal.Yaw += 90;
		Goal.Pitch = 0.0f;
		Goal.Roll = 0.0f;

		//
		FaceDirection = FMath().Lerp(GetActorRotation(), Goal, 0.1f);

		//
		SetActorRotation(FaceDirection);

	}
	// Forward, Left
	if (ForwardPress > 0 && LeftPress > 0)
	{

		//
		FRotator Goal = GetControlRotation();
		Goal.Yaw -= 45;
		Goal.Pitch = 0.0f;
		Goal.Roll = 0.0f;

		//
		FaceDirection = FMath().Lerp(GetActorRotation(), Goal, 0.1f);

		//
		SetActorRotation(FaceDirection);

	}
	// Forward, Right
	if (ForwardPress > 0 && RightPress > 0)
	{

		//
		FRotator Goal = GetControlRotation();
		Goal.Yaw += 45;
		Goal.Pitch = 0.0f;
		Goal.Roll = 0.0f;

		//
		FaceDirection = FMath().Lerp(GetActorRotation(), Goal, 0.1f);

		//
		SetActorRotation(FaceDirection);

	}
	// Backward, Left
	if (BackwardPress > 0 && LeftPress > 0)
	{

		//
		FRotator Goal = GetControlRotation();
		Goal.Yaw -= 135;
		Goal.Pitch = 0.0f;
		Goal.Roll = 0.0f;

		//
		FaceDirection = FMath().Lerp(GetActorRotation(), Goal, 0.1f);

		//
		SetActorRotation(FaceDirection);

	}
	// Backward, Right
	if (BackwardPress > 0 && RightPress > 0)
	{

		//
		FRotator Goal = GetControlRotation();
		Goal.Yaw += 135;
		Goal.Pitch = 0.0f;
		Goal.Roll = 0.0f;

		//
		FaceDirection = FMath().Lerp(GetActorRotation(), Goal, 0.1f);

		//
		SetActorRotation(FaceDirection);

	}
	// Left Thumbstick Axes
	if (LeftThumbstickMoveX != 0 || LeftThumbstickMoveY != 0)
	{

		//
		FRotator Goal = GetControlRotation();
		Goal.Yaw += atan2(LeftThumbstickMoveX, LeftThumbstickMoveY) * 180 / PI;
		Goal.Pitch = 0.0f;
		Goal.Roll = 0.0f;

		FaceDirection = FMath().Lerp(GetActorRotation(), Goal, 0.1f);

		//
		SetActorRotation(FaceDirection);

	}

}

#pragma endregion

#pragma region PLAYER DATA GETTERS

/**
	Get camera controller rotation
*/
FRotator ACheesePawn::GetCameraRotation()
{

	return GetControlRotation();

}

/**
	Get player rotation
*/
FRotator ACheesePawn::GetPlayerRotation()
{

	return GetActorRotation();

}

/**
	Returns player forward axis based on camera direction
*/
FVector ACheesePawn::GetPlayerForwardAxis(float AxisValue, bool IgnoreZ = false)
{

	//
	FVector Forward = GetControlRotation().Quaternion() * FVector(0, AxisValue, 0);
	if (IgnoreZ) Forward.Z = 0;

	//
	return Forward;

}

/**
	Returns player right axis based on camera direction
*/
FVector ACheesePawn::GetPlayerRightAxis(float AxisValue, bool IgnoreZ = false)
{

	//
	FVector Right = GetControlRotation().Quaternion() * FVector(AxisValue, 0, 0);
	if (IgnoreZ) Right.Z = 0;

	//
	return Right;

}

/**
	Returns player forward direction based on camera direction
*/
FVector ACheesePawn::GetPlayerForwardDirection(float AxisValue, bool IgnoreZ = false)
{

	//
	FVector Forward = GetControlRotation().Quaternion() * FVector(AxisValue, 0, 0);
	if (IgnoreZ) Forward.Z = 0;

	//
	return Forward;

}

/**
	Returns player backward direction based on camera direction
*/
FVector ACheesePawn::GetPlayerBackwardDirection(float AxisValue, bool IgnoreZ = false)
{

	//
	FVector Backward = GetControlRotation().Quaternion() * FVector(AxisValue * -1, 0, 0);
	if (IgnoreZ) Backward.Z = 0;

	//
	return Backward;

}

/**
	Returns player left direction based on camera direction
*/
FVector ACheesePawn::GetPlayerLeftDirection(float AxisValue, bool IgnoreZ = false)
{
	//
	FVector Left = GetControlRotation().Quaternion() * FVector(0, AxisValue * -1, 0);
	if (IgnoreZ) Left.Z = 0;

	//
	return Left;
}

/**
	Returns player right direction based on camera direction
*/
FVector ACheesePawn::GetPlayerRightDirection(float AxisValue, bool IgnoreZ = false)
{
	//
	FVector Right = GetControlRotation().Quaternion() * FVector(0, AxisValue, 0);
	if (IgnoreZ) Right.Z = 0;

	//
	return Right;
}

#pragma endregion

#pragma region PLAYER MANIPULATION FUNCTIONS

/**

	Freeze player Movement

*/
void ACheesePawn::FreezeMovement()
{

	IsMovementFreezed = true;

}

/**

	Freeze player Movement within a specified time frame

*/
void ACheesePawn::FreezeMovement(float FreezeLength)
{

	IsMovementFreezed = true;

}

/**

	UnFreeze player Movement

*/
void ACheesePawn::UnfreezeMovement()
{
	
	IsMovementFreezed = false;

}

#pragma endregion
