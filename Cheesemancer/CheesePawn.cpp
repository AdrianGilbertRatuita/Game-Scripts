// Fill out your copyright notice in the Description page of Project Settings.

#include "CheesePawn.h"


//
#include "Engine/Engine.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"

//
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

//
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

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
	IsClimbing = false;
	IsFalling = false;
	IsLedgeClimbing = false;

	//
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = CameraDistance;

	//
	CapsuleComponent->SetSimulatePhysics(true);
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

}
// Called when the game starts or when spawned
void ACheesePawn::BeginPlay()
{

	Super::BeginPlay();

	//
	InteractMesh->OnComponentEndOverlap.AddDynamic(this, &ACheesePawn::PickupOverlapExit);
	InteractMesh->OnComponentBeginOverlap.AddDynamic(this, &ACheesePawn::PickupOverlapBegin);
	InteractMesh->OnComponentBeginOverlap.AddDynamic(this, &ACheesePawn::MushroomOverlapBegin);
	InteractMesh->OnComponentEndOverlap.AddDynamic(this, &ACheesePawn::MushroomOverlapExit);
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ACheesePawn::LedgeOverlap);

}
// Called every frame
void ACheesePawn::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	if (IsLedgeClimbing)
	{

		LedgeTransition();

	}
	else if (!IsLedgeClimbing)
	{

		CombinationPress();

	}

	FloorCheck();

	if (HeldItem != nullptr && IsPickingStuffUp)
	{

		PickUpTransition();

	}

	FVector FinalItemPosition = GetActorLocation() + ItemHeldPosition;
	if (HeldItem != nullptr && !IsPickingStuffUp)
	{

		FVector HeldLocation = HeldItem->GetActorLocation();
		FVector Test = FMath().Lerp(HeldLocation, FinalItemPosition, 0.1f);
		HeldItem->SetActorLocation(Test + GetControlRotation().Quaternion() * FVector(1, 1, 1) * GetWorld()->GetDeltaSeconds());
		HeldItem->SetActorRotation(GetActorRotation());

	}

}
// Called to bind functionality to input
void ACheesePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	//
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//
	InputComponent = PlayerInputComponent;

	//
	InputComponent->BindAxisKey(ForwardKey, this, &ACheesePawn::MoveForward);
	InputComponent->BindAxisKey(BackwardKey, this, &ACheesePawn::MoveBackward);
	InputComponent->BindAxisKey(LeftKey, this, &ACheesePawn::MoveLeft);
	InputComponent->BindAxisKey(RightKey, this, &ACheesePawn::MoveRight);

	//
	InputComponent->BindKey(Interactkey, EInputEvent::IE_Pressed, this, &ACheesePawn::Interact);

	//
	InputComponent->BindAxisKey(EKeys::MouseX, this, &ACheesePawn::MouseMoveX);
	InputComponent->BindAxisKey(EKeys::MouseY, this, &ACheesePawn::MouseMoveY);
	InputComponent->BindAxisKey(EKeys::MouseWheelAxis, this, &ACheesePawn::Zoom);

}
//
float ACheesePawn::GetLedgeDistance()
{

	FVector YUp = FVector().ZeroVector;

	//
	FHitResult* HitTest = new FHitResult();
	FVector Self = GetActorLocation();
	FVector Trace = (GetActorForwardVector() * 100) + Self;
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

	for (int i = 0; i < 5000; i++)
	{

		if (!GetWorld()->LineTraceSingleByChannel(*HitTest, Self + YUp, Trace, ECC_Visibility, *TraceParams))
		{

			YUp.Z = i;
			break;

		}

	}

	return YUp.Z;
}

// Handle Animation Transition
#pragma region TransitionEvents
//
void ACheesePawn::LedgeTransition()
{

	if (SkeletalMesh->GetAnimInstance() != nullptr)
	{

		//
		float XCurveValue = 0;
		float XFinalValue = 0;

		//
		float YCurveValue = 0;
		float YFinalValue = 0;


		//
		SkeletalMesh->GetAnimInstance()->GetCurveValue(TEXT("XCurve"), XCurveValue);
		XFinalValue = CharacterLedgeClimbSpeed * XCurveValue;
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, FString::Printf(TEXT("X: %f"), XCurveValue));


		//
		SkeletalMesh->GetAnimInstance()->GetCurveValue(TEXT("YCurve"), YCurveValue);
		YFinalValue = CharacterLedgeClimbSpeed * YCurveValue;

		SetActorLocation(GetActorLocation() + GetActorUpVector() * (XFinalValue + YFinalValue) * GetWorld()->GetDeltaSeconds());

		CapsuleComponent->SetEnableGravity(GravityModifier);

	}

}
//
void ACheesePawn::PickUpTransition()
{

	float CurveValue = 0;

	SkeletalMesh->GetAnimInstance()->GetCurveValue(TEXT("PickUpCurve"), CurveValue);

	FVector FinalItemPosition = GetActorLocation() + ItemHeldPosition;
	if (HeldItem != nullptr)
	{

		FVector HeldLocation = HeldItem->GetActorLocation();
		FVector Test = FMath().Lerp(HeldLocation, FinalItemPosition, 0.1f);
		HeldItem->SetActorLocation(Test + GetControlRotation().Quaternion() * CurveValue * FVector(1, 1, 1) * GetWorld()->GetDeltaSeconds());
		HeldItem->SetActorRotation(GetActorRotation());

	}

}

#pragma endregion

// Overlap Events
// Triggers for changes
#pragma region OverlapEvents

void ACheesePawn::PickupOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (OtherActor->ActorHasTag(PickUpTag))
	{

		if (!OverlappedPickups.Contains(OtherActor) && OtherActor != nullptr)
		{
			OverlappedPickups.Add(OtherActor);

		}

	}

}

void ACheesePawn::PickupOverlapExit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (OtherActor->ActorHasTag(PickUpTag))
	{

		if (OverlappedPickups.Contains(OtherActor) && OtherActor != nullptr)
		{

			OverlappedPickups.Remove(OtherActor);

		}

	}

}

void ACheesePawn::MushroomOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (OtherActor->ActorHasTag(MushroomTag))
	{

		if (!OverlappedMushrooms.Contains(OtherActor) && OtherActor != nullptr)
		{
			OverlappedMushrooms.Add(OtherActor);

		}

	}

}

void ACheesePawn::MushroomOverlapExit(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{

	if (OtherActor->ActorHasTag(MushroomTag))
	{

		if (OverlappedMushrooms.Contains(OtherActor) && OtherActor != nullptr)
		{

			OverlappedMushrooms.Remove(OtherActor);

		}

	}

}

void ACheesePawn::LedgeOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (OtherActor->ActorHasTag(LedgeTag) && (IsClimbing || !IsFalling))
	{

		IsClimbing = false;
		IsFalling = false;
		IsLedgeClimbing = true;
		GravityModifier = false;

	}

}

#pragma endregion

// Input Events
// Handle events for character input
// From movement to Interaction
#pragma region InputEvents

void ACheesePawn::CombinationPress()
{

	//
	FRotator FaceDirection = GetActorRotation();
	if (!IsClimbing && !IsPickingStuffUp)
	{

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

	}

}

void ACheesePawn::Interact()
{

	//
	FHitResult* HitTest = new FHitResult();
	FVector Self = GetActorLocation();
	FVector Trace = (GetActorForwardVector() * 100) + Self;
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

	//DrawDebugLine(GetWorld(), Self, Trace, FColor(255, 0, 0), true);

	if (!IsClimbing)
	{

		if (GetWorld()->LineTraceSingleByChannel(*HitTest, GetActorLocation(), Trace, ECC_Visibility, *TraceParams))
		{

			if (HitTest->Actor->ActorHasTag(ClimbTag))
			{

				//
				IsClimbing = true;
				CapsuleComponent->SetEnableGravity(false);


			}
			if (HitTest->Actor->ActorHasTag(LedgeTag))
			{

				IsLedgeClimbing = true;

			}

		}

	}
	else if (IsClimbing)
	{

		IsClimbing = false;
		CapsuleComponent->SetEnableGravity(true);

	}


	if (HeldItem == nullptr && OverlappedPickups.Num() != 0)
	{

		AActor* ClosestItem = OverlappedPickups[0];
		for (int i = 1; i < OverlappedPickups.Num(); i++)
		{

			if (FVector().Distance(ClosestItem->GetActorLocation(), GetActorLocation())
		> FVector().Distance(OverlappedPickups[i]->GetActorLocation(), GetActorLocation()))
			{

				ClosestItem = OverlappedPickups[i];

			}

		}

		if (ClosestItem != nullptr)
		{

			HeldItem = ClosestItem;
			IsPickingStuffUp = true;
			UStaticMeshComponent* GravityDisable = Cast<UStaticMeshComponent>(HeldItem->GetRootComponent());
			GravityDisable->SetEnableGravity(false);

		}

	}
	else if (HeldItem != nullptr && OverlappedMushrooms.Num() == 0 && !IsClimbing)
	{

		UStaticMeshComponent* GravityDisable = Cast<UStaticMeshComponent>(HeldItem->GetRootComponent());
		GravityDisable->SetEnableGravity(true);
		HeldItem = nullptr;

	}

	if (OverlappedMushrooms.Num() != 0 && !IsPickingStuffUp)
	{

		AActor* Item = OverlappedMushrooms[0];

		for (int i = 1; i < OverlappedPickups.Num(); i++)
		{

			if (FVector().Distance(Item->GetActorLocation(), GetActorLocation())
		> FVector().Distance(OverlappedPickups[i]->GetActorLocation(), GetActorLocation()))
			{

				Item = OverlappedMushrooms[i];

			}

		}

		if (Item != nullptr && OverlappedMushrooms.Contains(Item))
		{

			IsPickingStuffUp = true;
			MushroomCount += 1;
			OverlappedMushrooms.Remove(Item);
			Item->Destroy();

		}

	}

}

void ACheesePawn::MoveForward(float AxisValue)
{

	//
	ForwardPress = AxisValue;

	//
	FVector CurrentCameraDirection = GetControlRotation().Quaternion() * FVector(AxisValue, 0, 0);
	CurrentCameraDirection.Z = 0;

	if (AxisValue > 0)
	{

		if (!IsClimbing && !IsPickingStuffUp)
		{

			//
			SetActorLocation(GetActorLocation() + CurrentCameraDirection * CharacterSpeed * GetWorld()->GetDeltaSeconds());

		}
		else if (IsClimbing)
		{

			float CurveValue = 0;
			float FinalValue = 0;

			SkeletalMesh->GetAnimInstance()->GetCurveValue(TEXT("ClimbCurve"), CurveValue);
			FinalValue = CharacterClimbSpeed * CurveValue;

			if (!WallClimbCheck())
			{

				IsClimbing = false;
				CapsuleComponent->SetEnableGravity(true);

			}

			//
			SetActorLocation(GetActorLocation() + GetActorUpVector() * FinalValue * GetWorld()->GetDeltaSeconds());

		}

	}

}

void ACheesePawn::MoveBackward(float AxisValue)
{

	//
	BackwardPress = AxisValue;

	FHitResult* HitTest = new FHitResult();
	FVector Self = GetActorLocation();
	FVector Down = GetActorUpVector() * -1;
	FVector Trace = (Down * 100) + Self;
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

	//
	FVector CurrentCameraDirection = GetControlRotation().Quaternion() * FVector(AxisValue * -1, 0, 0);
	CurrentCameraDirection.Z = 0;

	if (AxisValue > 0)
	{

		//
		if (!IsClimbing && !IsPickingStuffUp)
		{

			//
			SetActorLocation(GetActorLocation() + CurrentCameraDirection * CharacterSpeed * GetWorld()->GetDeltaSeconds());

		}
		else if (IsClimbing)
		{

			float CurveValue = 0;
			float FinalValue = 0;

			SkeletalMesh->GetAnimInstance()->GetCurveValue(TEXT("ClimbCurve"), CurveValue);
			FinalValue = CharacterClimbSpeed * CurveValue;

			if (GetWorld()->LineTraceSingleByChannel(*HitTest, GetActorLocation(), Trace, ECC_Visibility, *TraceParams))
			{

				IsClimbing = false;
				CapsuleComponent->SetEnableGravity(true);
				SetActorLocation(GetActorLocation() + (GetActorUpVector() * -1) * FinalValue * GetWorld()->GetDeltaSeconds());

			}

			SetActorLocation(GetActorLocation() + (GetActorUpVector() * -1) * FinalValue * GetWorld()->GetDeltaSeconds());

		}

	}

}

void ACheesePawn::MoveLeft(float AxisValue)
{

	//
	LeftPress = AxisValue;

	//
	FVector CurrentCameraDirection = GetControlRotation().Quaternion() * FVector(0, AxisValue * -1, 0);
	CurrentCameraDirection.Z = 0;

	if (AxisValue > 0)
	{

		//
		if (!IsClimbing && !IsPickingStuffUp)
		{

			//
			SetActorLocation(GetActorLocation() + CurrentCameraDirection * CharacterSpeed * GetWorld()->GetDeltaSeconds());

		}
		else if (IsClimbing)
		{

			//
			if (!WallClimbCheck())
			{

				IsClimbing = false;
				CapsuleComponent->SetEnableGravity(true);

			}

			float CurveValue = 0;
			float FinalValue = 0;

			SkeletalMesh->GetAnimInstance()->GetCurveValue(TEXT("ClimbCurve"), CurveValue);
			FinalValue = CharacterClimbSpeed * CurveValue;

			//
			SetActorLocation(GetActorLocation() + (GetActorRightVector() * AxisValue * -1) * FinalValue * GetWorld()->GetDeltaSeconds());

		}

	}

}

void ACheesePawn::MoveRight(float AxisValue)
{

	//
	RightPress = AxisValue;

	//
	FVector CurrentCameraDirection = GetControlRotation().Quaternion() * FVector(0, AxisValue, 0);
	CurrentCameraDirection.Z = 0;

	if (AxisValue > 0)
	{

		if (!IsClimbing && !IsPickingStuffUp)
		{

			//
			SetActorLocation(GetActorLocation() + CurrentCameraDirection * CharacterSpeed * GetWorld()->GetDeltaSeconds());

		}
		else if (IsClimbing)
		{

			//
			if (!WallClimbCheck())
			{

				IsClimbing = false;
				CapsuleComponent->SetEnableGravity(true);

			}

			float CurveValue = 0;
			float FinalValue = 0;
			SkeletalMesh->GetAnimInstance()->GetCurveValue(TEXT("ClimbCurve"), CurveValue);
			FinalValue = CharacterClimbSpeed * CurveValue;

			//
			SetActorLocation(GetActorLocation() + (GetActorRightVector() * AxisValue) * FinalValue * GetWorld()->GetDeltaSeconds());

		}

	}

}

void ACheesePawn::Zoom(float AxisValue)
{


	FMath().Clamp<float>(SpringArm->TargetArmLength, ZoomLimits.X, ZoomLimits.Y);
	SpringArm->TargetArmLength -= AxisValue * ZoomSpeed * GetWorld()->GetDeltaSeconds();

}

void ACheesePawn::MouseMoveX(float AxisValue)
{

	AddControllerYawInput(AxisValue * FMath().Clamp<float>(CameraMoveSpeed * GetWorld()->GetDeltaSeconds(), 0, 2));

}

void ACheesePawn::MouseMoveY(float AxisValue)
{

	AddControllerPitchInput(AxisValue * FMath().Clamp<float>(CameraMoveSpeed * GetWorld()->GetDeltaSeconds(), 0, 2));

}

#pragma endregion

// Environment Checks
// Checks for Climb Areas, Ledge Areas, and floor check
#pragma region Environment Checks

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
		IsFalling = true;

	}
	else if (GetWorld()->LineTraceSingleByChannel(*HitTest, GetActorLocation(), Trace, ECC_Visibility, *TraceParams))
	{

		CapsuleComponent->SetLinearDamping(5.0f);
		CapsuleComponent->SetAngularDamping(5.0f);
		IsFalling = false;

	}

}

bool ACheesePawn::WallClimbCheck()
{

	//
	FHitResult* HitTest = new FHitResult();
	FVector Self = GetActorLocation();
	FVector Trace = (GetActorForwardVector() * 100) + Self;
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

	if (!GetWorld()->LineTraceSingleByChannel(*HitTest, GetActorLocation(), Trace, ECC_Visibility, *TraceParams))
	{

		return false;

	}

	return true;
}

#pragma endregion

//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, FString::Printf(TEXT("X: %f"), AxisValue));