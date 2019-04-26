// Fill out your copyright notice in the Description page of Project Settings.

//
#include "CheesePawnMovement.h"
#include "FinalCheesePawn.h"

//
#include "Engine/Engine.h"

//
#include "CheesePawnAnimationInstance.h"

//
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UCheesePawnMovement::UCheesePawnMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

}


// Called when the game starts
void UCheesePawnMovement::BeginPlay()
{
	Super::BeginPlay();

	// Setup references

	PawnReference = Cast<AFinalCheesePawn>(GetOwner());

	CapsuleReference = PawnReference->CapsuleComponent;

	SkeletalMeshReference = PawnReference->SkeletalMeshComponent;

	CheeseAnimInstance = Cast<UCheesePawnAnimationInstance>(SkeletalMeshReference->GetAnimInstance());

}

//
void UCheesePawnMovement::LeftStickXMove(float AxisValue)
{

	//
	XStickMovement = AxisValue;
	CheeseAnimInstance->XStickMove = AxisValue;

	if (!bMovementFrozen && XStickMovement != 0)
	{

		FVector Direction = PawnReference->GetControlRotation().Quaternion() * FVector(0, AxisValue, 0);
		Direction.Z = 0;

		float SpeedCorrection = (bIsWalking ? CharacterWalkSpeed : CharacterSprintSpeed);

		FVector FinalPosition = GetOwner()->GetActorLocation() + Direction * (SpeedCorrection / (FMath::Abs(YStickMovement) > 0 ? 2 : 1)) * GetWorld()->GetDeltaSeconds();
		GetOwner()->SetActorLocation(FinalPosition);

		StickActorRotationFix();
		StickCheckForWalk();

	}

}

//
void UCheesePawnMovement::LeftStickYMove(float AxisValue)
{

	//
	YStickMovement = AxisValue;
	CheeseAnimInstance->YStickMove = AxisValue;

	if (!bMovementFrozen && YStickMovement != 0)
	{

		FVector Direction = PawnReference->GetControlRotation().Quaternion() * FVector(AxisValue, 0, 0);
		Direction.Z = 0;

		if (PawnReference->GetControlRotation().Pitch > 270 && AxisValue != 0)
		{

			Direction = PawnReference->GetActorForwardVector();

		}

		float SpeedCorrection = (bIsWalking ? CharacterWalkSpeed : CharacterSprintSpeed);

		FVector FinalPosition = GetOwner()->GetActorLocation() + Direction * (SpeedCorrection / (FMath::Abs(XStickMovement) > 0 ? 2 : 1)) * GetWorld()->GetDeltaSeconds();
		GetOwner()->SetActorLocation(FinalPosition);

		StickActorRotationFix();
		StickCheckForWalk();

	}

}

//
void UCheesePawnMovement::MoveForward(float AxisValue)
{

	//
	ForwardPress = AxisValue;
	CheeseAnimInstance->Forward = AxisValue;

	if (!bMovementFrozen)
	{

		// Movement
		FVector Direction = PawnReference->GetControlRotation().Quaternion() * FVector(AxisValue, 0, 0);
		Direction.Z = 0;

		if (PawnReference->GetControlRotation().Pitch > 270 && AxisValue > 0)
		{

			Direction = PawnReference->GetActorForwardVector();

		}

		float SpeedCorrection = (bIsWalking ? CharacterWalkSpeed : CharacterSprintSpeed);
		if (LeftPress > 0 || RightPress > 0) { SpeedCorrection /= 2; }

		FVector FinalPosition = GetOwner()->GetActorLocation() + Direction * SpeedCorrection * GetWorld()->GetDeltaSeconds();
		GetOwner()->SetActorLocation(FinalPosition);

		if (AxisValue > 0)
		{

			// Rotation
			FRotator RotationFix = PawnReference->GetControlRotation();
			RotationFix.Pitch = 0;
			RotationFix.Roll = 0;

			FRotator CurrentRotation = GetOwner()->GetActorRotation();
			GetOwner()->SetActorRotation(FMath::Lerp(CurrentRotation, RotationFix, 0.25f));

		}

	}

}

//
void UCheesePawnMovement::MoveBackward(float AxisValue)
{

	//
	BackwardPress = AxisValue;
	CheeseAnimInstance->Backward = AxisValue;

	if (!bMovementFrozen)
	{

		// Movement
		FVector Direction = PawnReference->GetControlRotation().Quaternion() * FVector(AxisValue * -1, 0, 0);
		Direction.Z = 0;

		if (PawnReference->GetControlRotation().Pitch > 270 && AxisValue > 0)
		{

			Direction = PawnReference->GetActorForwardVector();

		}

		float SpeedCorrection = (bIsWalking ? CharacterWalkSpeed : CharacterSprintSpeed);
		if (LeftPress > 0 || RightPress > 0) { SpeedCorrection /= 2; }

		FVector FinalPosition = GetOwner()->GetActorLocation() + Direction * SpeedCorrection * GetWorld()->GetDeltaSeconds();
		GetOwner()->SetActorLocation(FinalPosition);

		if (AxisValue > 0)
		{

			// Rotation
			FRotator RotationFix = PawnReference->GetControlRotation();
			RotationFix.Yaw -= 180.0f;
			RotationFix.Pitch = 0;
			RotationFix.Roll = 0;

			FRotator CurrentRotation = GetOwner()->GetActorRotation();
			GetOwner()->SetActorRotation(FMath::Lerp(CurrentRotation, RotationFix, 0.25f));

		}

	}

}

//
void UCheesePawnMovement::MoveLeft(float AxisValue)
{

	//
	LeftPress = AxisValue;
	CheeseAnimInstance->Left = AxisValue;

	if (!bMovementFrozen)
	{

		// Movement
		FVector Direction = PawnReference->GetControlRotation().Quaternion() * FVector(0, AxisValue * -1, 0);
		Direction.Z = 0;

		float SpeedCorrection = (bIsWalking ? CharacterWalkSpeed : CharacterSprintSpeed);
		if (ForwardPress > 0 || BackwardPress > 0) { SpeedCorrection /= 2; }

		FVector FinalPosition = GetOwner()->GetActorLocation() + Direction * SpeedCorrection * GetWorld()->GetDeltaSeconds();
		GetOwner()->SetActorLocation(FinalPosition);

		if (AxisValue > 0)
		{

			// Rotation
			FRotator RotationFix = PawnReference->GetControlRotation();
			RotationFix.Yaw -= 90.0f;
			RotationFix.Pitch = 0;
			RotationFix.Roll = 0;

			FRotator CurrentRotation = GetOwner()->GetActorRotation();
			GetOwner()->SetActorRotation(FMath::Lerp(CurrentRotation, RotationFix, 0.25f));

		}

	}

}

//
void UCheesePawnMovement::MoveRight(float AxisValue)
{

	//
	RightPress = AxisValue;
	CheeseAnimInstance->Right = AxisValue;

	if (!bMovementFrozen)
	{

		// Movement
		FVector Direction = PawnReference->GetControlRotation().Quaternion() * FVector(0, AxisValue, 0);
		Direction.Z = 0;

		float SpeedCorrection = (bIsWalking ? CharacterWalkSpeed : CharacterSprintSpeed);
		if (ForwardPress > 0 || BackwardPress > 0) { SpeedCorrection /= 2; }

		FVector FinalPosition = GetOwner()->GetActorLocation() + Direction * SpeedCorrection * GetWorld()->GetDeltaSeconds();
		GetOwner()->SetActorLocation(FinalPosition);

		if (AxisValue > 0)
		{

			// Rotation
			FRotator RotationFix = PawnReference->GetControlRotation();
			RotationFix.Yaw += 90.0f;
			RotationFix.Pitch = 0;
			RotationFix.Roll = 0;

			FRotator CurrentRotation = GetOwner()->GetActorRotation();
			GetOwner()->SetActorRotation(FMath::Lerp(CurrentRotation, RotationFix, 0.25f));

		}

	}

}

void UCheesePawnMovement::StickCheckForWalk()
{

	if (FMath::Abs(XStickMovement) + FMath::Abs(YStickMovement) < MinimumToStickWalk)
	{

		bIsWalking = true;
		CheeseAnimInstance->bWalking = true;

	}
	else
	{

		bIsWalking = false;
		CheeseAnimInstance->bWalking = false;

	}

}

void UCheesePawnMovement::StickActorRotationFix()
{

	if (YStickMovement != 0 || XStickMovement != 0)
	{

		float Rotation = (atan2(XStickMovement, YStickMovement) * 180 / PI);

		// Rotation
		FRotator RotationFix = PawnReference->GetControlRotation();
		RotationFix.Yaw += Rotation;
		RotationFix.Pitch = 0;
		RotationFix.Roll = 0;

		FRotator CurrentRotation = GetOwner()->GetActorRotation();
		GetOwner()->SetActorRotation(FMath::Lerp(CurrentRotation, RotationFix, 0.1f));

	}

}

// Enable gravity
void UCheesePawnMovement::EnableGravity()
{

	Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->SetEnableGravity(true);

}

// Disable gravity
void UCheesePawnMovement::DisableGravity()
{

	Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->SetEnableGravity(false);

}

// Freeze player movement or ignore input into this component
void UCheesePawnMovement::FreezeMovement()
{

	bMovementFrozen = true;

}

// Unfreeze player movement or allow input into this component
void UCheesePawnMovement::UnfreezeMovement()
{

	bMovementFrozen = false;

}

// Freeze Animation
void UCheesePawnMovement::FreezeAnimation()
{

	bAnimationFrozen = true;

}

// Unfreeze Animation
void UCheesePawnMovement::UnfreezeAnimation()
{

	bAnimationFrozen = false;

}

// Start walking
void UCheesePawnMovement::StartWalking()
{

	bIsWalking = true;
	CheeseAnimInstance->bWalking = true;


}

// End walking
void UCheesePawnMovement::EndWalking()
{

	bIsWalking = false;
	CheeseAnimInstance->bWalking = false;

}

// Called every frame
void UCheesePawnMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

}

