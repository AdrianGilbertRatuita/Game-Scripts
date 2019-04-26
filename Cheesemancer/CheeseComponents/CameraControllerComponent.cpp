// Fill out your copyright notice in the Description page of Project Settings.

//
#include "CameraControllerComponent.h"
#include "FinalCheesePawn.h"

//
#include "CheeseComponents/ClimbComponent.h"
#include "CheeseComponents/CheesePawnMovement.h"
#include "CheeseComponents/CameraControllerComponent.h"
#include "CheesePawnAnimationInstance.h"

//
#include "Engine/Engine.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Controller.h"

// Sets default values for this component's properties
UCameraControllerComponent::UCameraControllerComponent()
{

	// Tick events is needed as Camera Correction requires lerping for smooth controller rotation
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UCameraControllerComponent::BeginPlay()
{

	Super::BeginPlay();

	// Get References
	PawnReference = Cast<AFinalCheesePawn>(GetOwner());
	InputComponent = PawnReference->InputComponent;
	ControllerReference = PawnReference->GetController();
	SkeletalMeshReference = PawnReference->SkeletalMeshComponent;

	//
	ClimbReference = PawnReference->ClimbComponent;
	MovementReference = PawnReference->CheesePawnMovement;
	SpringArmReference = PawnReference->SpringArmComponent;

	//
	SpringArmReference->TargetArmLength = CameraFollowDistance;
	SpringArmReference->SetRelativeLocation(CameraFollowLocation);

	//
	CheeseAnimInstance = Cast<UCheesePawnAnimationInstance>(SkeletalMeshReference->GetAnimInstance());

}

// Called every frame
void UCameraControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...

	ResettingCamera();

}

void UCameraControllerComponent::FocusLock()
{

	if (!ClimbReference->bClimbing)
	{

		//
		if (bAimMovementFreeze) MovementReference->FreezeMovement();

		//
		//LimitCameraYaw(PawnReference->GetControlRotation().Yaw, 90);
		//LimitCameraPitch(PawnReference->GetControlRotation().Pitch, 90);

	}


}

void UCameraControllerComponent::FocusUnlock()
{

	if (!ClimbReference->bClimbing)
	{

		//
		MovementReference->UnfreezeMovement();

		//
		ReleaseCameraYaw();
		ReleaseCameraPitch();

	}

}

void UCameraControllerComponent::FocusCamera(float AxisValue)
{

	if (InputComponent->GetAxisKeyValue(EKeys::Gamepad_LeftTriggerAxis) > 0 || InputComponent->GetAxisKeyValue(EKeys::RightMouseButton) > 0 && !ClimbReference->bClimbing)
	{

		// Set Booleans to true
		bTargetingMode = true;
		CheeseAnimInstance->bAiming = true;

		// Override Pawn's yaw with controller's yaw
		PawnReference->bUseControllerRotationYaw = true;

		// Set Current SpringArm Length
		float CurrentArmLength = SpringArmReference->TargetArmLength;

		// Get and Lerp to desired SpringArm Location
		FVector RelativeLocation = SpringArmReference->GetRelativeTransform().GetLocation();
		SpringArmReference->SetRelativeLocation(FMath::Lerp(RelativeLocation, CameraTargettingLocation, 0.25f));

		// Determine if Springarm Location is nearly in desired position
		if (!FMath::IsNearlyEqual(CurrentArmLength, CameraTargetingDistance, 0.1f))
		{

			SpringArmReference->TargetArmLength = FMath::Lerp(CurrentArmLength, CameraTargetingDistance, 0.25f);

		}

	}
	else
	{

		// Set Booleans to true
		bTargetingMode = false;
		CheeseAnimInstance->bAiming = false;

		// Override Pawn's yaw with controller's yaw
		PawnReference->bUseControllerRotationYaw = false;

		// Set Current SpringArm Length
		float CurrentArmLength = SpringArmReference->TargetArmLength;

		// Get and Lerp to desired SpringArm Location
		FVector RelativeLocation = SpringArmReference->GetRelativeTransform().GetLocation();
		SpringArmReference->SetRelativeLocation(FMath::Lerp(RelativeLocation, CameraFollowLocation, 0.25f));

		// Determine if Springarm Location is nearly in desired position
		if (!FMath::IsNearlyEqual(CurrentArmLength, CameraFollowDistance, 0.1f))
		{

			SpringArmReference->TargetArmLength = FMath::Lerp(CurrentArmLength, CameraFollowDistance, 0.25f);

		}

	}

}

// Pans Camera
void UCameraControllerComponent::PanCamera(float AxisValue)
{
	
	if (!bCameraLock)
	{

		// If Yaw Is Limited
		if (bLimitCameraYaw) YawLimitControl(AxisValue);
		// If Yaw is not Limited
		else PawnReference->AddControllerYawInput(AxisValue * (bCameraInvertYaw ? -1 : 1) * CameraYawSpeed * GetWorld()->GetDeltaSeconds());

	}

}

// Titlts Camera
void UCameraControllerComponent::TiltCamera(float AxisValue)
{

	if (!bCameraLock)
	{

		// If Pitch is Limited
		if (bLimitCameraPitch) PitchLimitControl(AxisValue);
		// If Pitch is not Limited
		else PawnReference->AddControllerPitchInput(AxisValue * (bCameraInvertPitch ? -1 : 1) * CameraYawSpeed * GetWorld()->GetDeltaSeconds());

	}

}

// Function for Limiting Yaw
void UCameraControllerComponent::YawLimitControl(float AxisValue)
{

	//
	bool NegativeAdjustment = false;

	//
	float Limit = YawLimitCenter;
	float Lower = Limit - YawAngleRange;
	float Upper = Limit + YawAngleRange;

	//
	float AngleAdjustment = ControllerReference->GetControlRotation().Yaw;

	// Determinant for Non-Negative Lower Limit
	if (Lower < 0) NegativeAdjustment = true;
	AngleAdjustment -= AngleAdjustment > 360 ? 360 : 0;

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("CurrentYaw: %f"), AngleAdjustment));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("LIMIT: %f, LOWER: %f, UPPER: %f"), Limit, Lower + (NegativeAdjustment ? 360 : 0), Upper));

	//
	if (AngleAdjustment >= Lower + (NegativeAdjustment ? 360 : 0) ||
		AngleAdjustment <= Upper)
	{

		PawnReference->AddControllerYawInput(AxisValue * (bCameraInvertYaw ? -1 : 1) * CameraYawSpeed * GetWorld()->GetDeltaSeconds());

	}
	else
	{

		CameraYawCorrection(Upper, Lower, NegativeAdjustment);

	}

}

// Function for Limiting Pitch
void UCameraControllerComponent::PitchLimitControl(float AxisValue)
{

	//
	bool NegativeAdjustment = false;

	//
	float Limit = PitchLimitCenter;
	float Lower = Limit - PitchAngleRange;
	float Upper = Limit + PitchAngleRange;

	//
	float AngleAdjustment = ControllerReference->GetControlRotation().Pitch;

	// Determinant for Non-Negative Lower Limit
	if (Lower < 0)
	{

		NegativeAdjustment = true;

	}

	//
	if (AngleAdjustment >= Lower + (NegativeAdjustment ? 360 : 0) ||
		AngleAdjustment <= Upper)
	{

		PawnReference->AddControllerPitchInput(AxisValue * (bCameraInvertPitch ? -1 : 1) * CameraPitchSpeed * GetWorld()->GetDeltaSeconds());

	}
	else
	{

		CameraPitchCorrection(Upper, Lower, NegativeAdjustment);

	}

}

void UCameraControllerComponent::ResettingCamera()
{

	//if (bResettingCamera)
	//{

	//	if (!bResettingYawCamera && !bResettingPitchCamera)
	//	{

	//		//
	//		FRotator CurrentCameraRotation = PawnReference->GetControlRotation();
	//		CurrentCameraRotation.Yaw = GetOwner()->GetActorRotation().Yaw;
	//		CurrentCameraRotation.Pitch = 0;

	//		//
	//		ControllerReference->SetControlRotation(FMath::Lerp(PawnReference->GetControlRotation(), CurrentCameraRotation, CameraCorrectionSpeed));

	//		//
	//		float ActorYaw = GetOwner()->GetActorRotation().Yaw;
	//		float AngleYaw = PawnReference->GetControlRotation().Yaw;
	//		float AnglePitch = PawnReference->GetControlRotation().Pitch;

	//		if (ActorYaw < 0) { ActorYaw += 360; }
	//		if (AngleYaw > 360) { AngleYaw -= 360; }

	//		if (FMath::IsNearlyEqual(ActorYaw, AngleYaw, 0.125f))
	//		{

	//			bResettingCamera = false;

	//		}

	//	}
	//	else if (bResettingYawCamera &&
	//		FMath::IsNearlyEqual(YawLimitCenter, PawnReference->GetControlRotation().Yaw))
	//	{

	//		//
	//		FRotator CurrentCameraRotation = PawnReference->GetControlRotation();
	//		CurrentCameraRotation.Yaw = GetOwner()->GetActorRotation().Yaw;

	//		//
	//		ControllerReference->SetControlRotation(FMath::Lerp(PawnReference->GetControlRotation(), CurrentCameraRotation, CameraCorrectionSpeed));

	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("SECOND")));

	//	}
	//	else if (bResettingPitchCamera &&
	//		FMath::IsNearlyEqual(PitchLimitCenter, PawnReference->GetControlRotation().Pitch))
	//	{

	//		//
	//		FRotator CurrentCameraRotation = PawnReference->GetControlRotation();
	//		CurrentCameraRotation.Pitch = GetOwner()->GetActorRotation().Pitch;

	//		//
	//		ControllerReference->SetControlRotation(FMath::Lerp(PawnReference->GetControlRotation(), CurrentCameraRotation, CameraCorrectionSpeed));

	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("THIRD")));

	//	}
	//	else if (bResettingYawCamera && bResettingPitchCamera)
	//	{

	//		//
	//		FRotator CurrentCameraRotation = PawnReference->GetControlRotation();
	//		CurrentCameraRotation.Yaw = GetOwner()->GetActorRotation().Yaw;
	//		CurrentCameraRotation.Pitch = GetOwner()->GetActorRotation().Pitch;

	//		//
	//		ControllerReference->SetControlRotation(FMath::Lerp(PawnReference->GetControlRotation(), CurrentCameraRotation, CameraCorrectionSpeed));

	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("FOURTH")));

	//	}
	//	else bResettingCamera = false;

	//}

	if (bResettingCamera)
	{

		if (!bResettingYawCamera && !bResettingPitchCamera)
		{

			//
			FRotator CurrentCameraRotation = PawnReference->GetControlRotation();
			CurrentCameraRotation.Yaw = GetOwner()->GetActorRotation().Yaw;
			CurrentCameraRotation.Pitch = 0;

			//
			ControllerReference->SetControlRotation(FMath::Lerp(PawnReference->GetControlRotation(), CurrentCameraRotation, 0.25f));

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Owner Rotation: %s"), *GetOwner()->GetActorRotation().ToString()));

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Camera Rotation: %s"), *PawnReference->GetControlRotation().ToString()));

			//
			float ActorYaw = GetOwner()->GetActorRotation().Yaw;
			float AngleYaw = PawnReference->GetControlRotation().Yaw;

			if (ActorYaw < 0) { ActorYaw += 360; }
			if (ActorYaw > 360) { ActorYaw -= 360; }
			if (AngleYaw > 360) { AngleYaw -= 360; }
			if (AngleYaw < 0) { AngleYaw += 360; }

			if (FMath::IsNearlyEqual(ActorYaw, AngleYaw, 0.125f))
			{

				ControllerReference->SetControlRotation(PawnReference->GetControlRotation());
				bResettingCamera = false;

			}

		}

	}

}

// Reset Camera Position to Face from Object Back
void UCameraControllerComponent::ResetCamera()
{

	bResettingCamera = true;

}

// Reset Camera Position to Specified Yaw Limit
void UCameraControllerComponent::ResetCameraToYawCenterLimit()
{

	bResettingCamera = true;
	bResettingYawCamera = true;

}

// Reset Camera Position to Specified Pitch Limit
void UCameraControllerComponent::ResetCameraToPitchCenterLimit()
{

	bResettingCamera = true;
	bResettingPitchCamera = true;

}

// Reset Camera Position to Specified Yaw and Pitch Limit
void UCameraControllerComponent::ResetCameraToYawAndPitchCenterLimit()
{

	bResettingCamera = true;
	bResettingYawCamera = true;
	bResettingPitchCamera = true;

}

// Lock Camera Movement
void UCameraControllerComponent::LockCamera()
{

	bCameraLock = true;

}

// Unlock Camera Movement
void UCameraControllerComponent::UnlockCamera()
{

	bCameraLock = false;

}

// Limit Camera Yaw based on a Center Limit and Minimum to Maximum range
void UCameraControllerComponent::LimitCameraYaw(float LimitCenter, float AngleRange)
{

	bLimitCameraYaw = true;
	YawLimitCenter = LimitCenter;
	YawAngleRange = AngleRange;

}

// Limit Camera Pitch based on a Center Limit and Minimum to Maximum range
void UCameraControllerComponent::LimitCameraPitch(float LimitCenter, float AngleRange)
{

	bLimitCameraPitch = true;
	PitchLimitCenter = LimitCenter;
	PitchAngleRange = AngleRange;

}

// Release Camera Yaw Limit
void UCameraControllerComponent::ReleaseCameraYaw()
{

	bLimitCameraYaw = false;

}

// Release Camera Pitch Limit
void UCameraControllerComponent::ReleaseCameraPitch()
{

	bLimitCameraPitch = false;

}

// Release Camera Yaw and Pitch
void UCameraControllerComponent::ReleaseCameraYawAndPitch()
{

	bLimitCameraYaw = false;
	bLimitCameraPitch = false;

}

// Correct Yaw to nearest Limit
void UCameraControllerComponent::CameraYawCorrection(float Upper, float Lower, bool NegativeAdjustment)
{

	float UDistance = FMath::Abs(Upper - PawnReference->GetControlRotation().Yaw);
	float LDistance = FMath::Abs((Lower + (NegativeAdjustment ? 360 : 0)) - PawnReference->GetControlRotation().Yaw);

	if (UDistance > 360) UDistance -= 360;

	if (UDistance < LDistance)
	{

		FRotator RotationFix = PawnReference->GetControlRotation();
		RotationFix.Yaw = Upper - CameraUpperCorrectionModifier;

		ControllerReference->SetControlRotation(FMath::Lerp(PawnReference->GetControlRotation(), RotationFix, CameraCorrectionSpeed));

	}
	else if (LDistance < UDistance)
	{

		FRotator RotationFix = PawnReference->GetControlRotation();
		RotationFix.Yaw = Lower + (NegativeAdjustment ? 360 : 0) + CameraLowerCorrectionModifier;

		ControllerReference->SetControlRotation(RotationFix);
		ControllerReference->SetControlRotation(FMath::Lerp(PawnReference->GetControlRotation(), RotationFix, CameraCorrectionSpeed));

	}

}

// Correct Pitch to nearest Limit
void UCameraControllerComponent::CameraPitchCorrection(float Upper, float Lower, bool NegativeAdjustment)
{

	float UDistance = FMath::Abs(Upper - PawnReference->GetControlRotation().Pitch);
	float LDistance = FMath::Abs((Lower + (NegativeAdjustment ? 360 : 0)) - PawnReference->GetControlRotation().Pitch);

	if (UDistance < LDistance)
	{

		FRotator RotationFix = PawnReference->GetControlRotation();
		RotationFix.Pitch = Upper - CameraUpperCorrectionModifier;

		ControllerReference->SetControlRotation(FMath::Lerp(PawnReference->GetControlRotation(), RotationFix, 1.0f));

	}
	else if (LDistance < UDistance)
	{

		FRotator RotationFix = PawnReference->GetControlRotation();
		RotationFix.Pitch = Lower + (NegativeAdjustment ? 360 : 0) + CameraLowerCorrectionModifier;

		ControllerReference->SetControlRotation(RotationFix);
		ControllerReference->SetControlRotation(FMath::Lerp(PawnReference->GetControlRotation(), RotationFix, 1.0f));

	}

}



