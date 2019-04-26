// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraControllerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTING_API UCameraControllerComponent : public UActorComponent
{

	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UCameraControllerComponent();

	//==================================================================================================================
	// Camera Variable Settings
	//==================================================================================================================

	// Boolean for Targeting mode
	/** Boolean to check if targeting or not */
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		bool bTargetingMode = false;

	// Boolean for aim camera freeze
	/** Boolean to freeze the camera when aiming */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		bool bAimMovementFreeze = true;

	// Boolean for Inverting Yaw
	/** Should the Yaw of the Camera be inverted */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		bool bCameraInvertYaw = false;

	// Boolean for Inverting Pitch
	/** Should the Pitch of the Camera be inverted */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		bool bCameraInvertPitch = false;

	// Regular Camera distance
	/** Camera distance when following player */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		float CameraFollowDistance;

	// Targeting Camera distance
	/** Camera distance when player is targetting */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		float CameraTargetingDistance;

	// Speed for Camera Panning
	/** How fast should the camera pan */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		float CameraYawSpeed;

	// Speed for Camera Tilting
	/** How fast should the camera tilt */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		float CameraPitchSpeed;

	// Speed for Camera Correction
	/** How fast should the camera correct itself when limited */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cameral Controller", meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1", AllowPrivateAccess = "true"))
		float CameraCorrectionSpeed = 0.1f;

	// Upper Modifier for preventing camera from locking when it reaches the Upper Limit
	/** Modifier subtracted to the Upper Limit to prevent locking */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		float CameraUpperCorrectionModifier = 0.5f;

	// Lower Modifier for preventing camera from locking when it reaches the Lower Limit
	/** Modifier added to the Lower Limit to prevent locking */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		float CameraLowerCorrectionModifier = 0.5f;

	// Camera Relative location when following the player
	/** Relative location of the camera when following the player */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		FVector CameraFollowLocation;

	// Camera Relative location when in targeting mode
	/** Relative location of the camera when in targeting mode */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		FVector CameraTargettingLocation;

	//==================================================================================================================
	// Camera Control Functions
	//==================================================================================================================

	// Lock Camera Yaw and Pitch
	/** Locks camera yaw and pitch for Focus */
	UFUNCTION(BlueprintCallable, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		virtual void FocusLock();

	// Unlock Camera Yaw and Pitch
	/** Unlocks camera yaw and pitch from Focus */
	UFUNCTION(BlueprintCallable, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		virtual void FocusUnlock();

	// Tilt Camera
	/** Tilts camera based on AxisValue */
	UFUNCTION(BlueprintCallable, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		virtual void FocusCamera(float AxisValue);

	// Pan Camera
	/** Pans camera based on AxisValue */
	UFUNCTION(BlueprintCallable, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		virtual void PanCamera(float AxisValue);

	// Tilt Camera
	/** Tilts camera based on AxisValue */
	UFUNCTION(BlueprintCallable, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		virtual void TiltCamera(float AxisValue);

	// Reset Camera to Object Back
	/** Resets the camera to the back of the object */
	UFUNCTION(BlueprintCallable, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		virtual void ResetCamera();

	// Reset Camera to Yaw Center Limit
	/** Resets the camera to the specified yaw center limit */
	UFUNCTION(BlueprintCallable, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		virtual void ResetCameraToYawCenterLimit();

	// Reset Camera to Pitch Center Limit
	/** Resets the camera to the specified yaw center limit */
	UFUNCTION(BlueprintCallable, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		virtual void ResetCameraToPitchCenterLimit();

	// Reset Camera to Yaw and Pitch Center Limit
	/** Resets the camera to the specified pitch center limit */
	UFUNCTION(BlueprintCallable, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		virtual void ResetCameraToYawAndPitchCenterLimit();

	// Lock Camera
	/** Lock Camera and prevent movement */
	UFUNCTION(BlueprintCallable, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		virtual void LockCamera();

	// Unlock Camera
	/** Unlock Camera and enable movement */
	UFUNCTION(BlueprintCallable, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		virtual void UnlockCamera();

	// Limit Camera Yaw
	/** Limit Camera yaw within a specified angle range relative to a center limit */
	UFUNCTION(BlueprintCallable, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		virtual void LimitCameraYaw(float LimitCenter, float AngleRange);

	// Limit Camera Pitch
	/** Limit Camera pitch within a specified angle range relative to a center limit */
	UFUNCTION(BlueprintCallable, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		virtual void LimitCameraPitch(float LimitCenter, float AngleRange);

	// Release Camera Yaw
	/** Releases the limit on Camera Yaw */
	UFUNCTION(BlueprintCallable, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		virtual void ReleaseCameraYaw();

	// Release Camera Pitch
	/** Releases the limit on Camera Pitch */
	UFUNCTION(BlueprintCallable, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		virtual void ReleaseCameraPitch();

	// Release Camera Yaw and Pitch
	/** Releases the limit on Camera Yaw and Pitch */
	UFUNCTION(BlueprintCallable, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		virtual void ReleaseCameraYawAndPitch();

	// Correct Yaw to nearest Limit
	/** Corrects the Yaw of the Camera if it goes beyond Upper and Lower Limits */
	UFUNCTION(BlueprintCallable, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		virtual void CameraYawCorrection(float Upper, float Lower, bool NegativeAdjustment);

	// Correct Pitch to nearest Limit
	/** Corrects the Pitch of the Camera if it goes beyond Upper and Lower Limits */
	UFUNCTION(BlueprintCallable, Category = "Cameral Controller", meta = (AllowPrivateAccess = "true"))
		virtual void CameraPitchCorrection(float Upper, float Lower, bool NegativeAdjustment);

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	// Center of Yaw Limit
	float YawLimitCenter;

	// Center of Pitch Limit
	// Set to 89 Degrees for Default Angle
	// Adjusted to prevent any locks
	float PitchLimitCenter = 89.0f;

	// Minimum and Maximum Angle from Yaw Center Limit
	float YawAngleRange;

	// Minimum and Maximum Angle from Pitch Center Limit
	float PitchAngleRange;

	// Boolean for locking camera
	bool bCameraLock = false;

	// Boolean for Limiting Camera Yaw
	bool bLimitCameraYaw = false;

	// Boolean for Limiting Camera Pitch
	bool bLimitCameraPitch = false;

	// Boolean for Camera Reset Process
	bool bResettingCamera = false;

	// Boolean for Camera Reset Process for Yaw
	bool bResettingYawCamera = false;

	// Boolean for Camera Reset Process for Pitch
	bool bResettingPitchCamera = false;

	// Reference for Pawn Owner
	class AFinalCheesePawn * PawnReference;

	// Reference for Controller
	class AController * ControllerReference;

	// Reference for the Input Component
	class UInputComponent * InputComponent;

	// Reference for the Climb Component
	class UClimbComponent * ClimbReference;

	// Reference for the Movement Component
	class UCheesePawnMovement * MovementReference;

	// Reference for Springarm
	class USpringArmComponent * SpringArmReference;

	// Reference for Skeletal Mesh
	class USkeletalMeshComponent * SkeletalMeshReference;

	// Reference for Animation Instance
	class UCheesePawnAnimationInstance * CheeseAnimInstance;

	// Function for Limiting Yaw
	void YawLimitControl(float AxisValue);

	// Function for Limiting Pitch
	void PitchLimitControl(float AxisValue);

	void ResettingCamera();

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
	
};
