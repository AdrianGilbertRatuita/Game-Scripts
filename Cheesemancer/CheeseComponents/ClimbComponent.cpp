// Fill out your copyright notice in the Description page of Project Settings.

#include "ClimbComponent.h"
#include "FinalCheesePawn.h"

//
#include "BaseInteractable.h"
#include "CheesePawnAnimationInstance.h"
#include "CheeseComponents/CheesePawnMovement.h"
#include "CheeseComponents/InteractionComponent.h"
#include "CheeseComponents/FloorCheckerComponent.h"
#include "CheeseComponents/CameraControllerComponent.h"

//
#include "Engine/Engine.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

// Sets default values for this component's properties
UClimbComponent::UClimbComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UClimbComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	PawnReference = Cast<AFinalCheesePawn>(GetOwner());

	CapsuleReference = PawnReference->CapsuleComponent;

	MovementReference = PawnReference->CheesePawnMovement;
	
	InteractionReference = PawnReference->InteractionComponent;

	FloorCheckerReference = PawnReference->FloorCheckerComponent;

	CameraControllerReference = PawnReference->CameraControllerComponent;

	SkeletalMeshReference = PawnReference->SkeletalMeshComponent;

	RightHandReference = PawnReference->RightHandEquipment;

	CheeseAnimInstance = Cast<UCheesePawnAnimationInstance>(SkeletalMeshReference->GetAnimInstance());

}


// Called every frame
void UClimbComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Debugging Line for Probe
	//FVector OwnerLocation = GetOwner()->GetActorLocation() + FVector(0, 0, ProbeVerticalOffset);
	//FVector CapsuleStart = GetOwner()->GetActorForwardVector() * CapsuleReference->GetScaledCapsuleRadius() + ProbeStartOffsetModifier;
	//FVector ProbeStart = OwnerLocation + CapsuleStart;
	//FVector ProbeEnd = ProbeStart + (GetOwner()->GetActorForwardVector() * ForwardProbeDistance);
	//DrawDebugLine(GetWorld(), ProbeStart, ProbeEnd, FColor::Red, false, -1.0f, (uint8)'\000', 2.0f);

}

// Check for climb objects 
void UClimbComponent::CheckForClimb()
{

	// Prevents interference with Interaction Component
	if (InteractionReference->OverlappedInteractables.Num() == 0 
		&& !bClimbing)
	{

		FHitResult * HitTest = ProbeCheck();

		if (HitTest->GetActor() != nullptr && HitTest->GetActor()->ActorHasTag(ClimbTag))
		{

			BeginClimb(HitTest);

		}

	}
	else if (bClimbing)
	{

		EndClimb();

	}

}

// Start the Climb
void UClimbComponent::BeginClimb(FHitResult* HitResult)
{

	CheeseAnimInstance->bClimbing = true;

	bClimbing = true;
	MovementReference->DisableGravity();
	MovementReference->FreezeMovement();

	//
	float NormalAngle = FMath::Atan2(HitResult->Normal.Y, HitResult->Normal.X) * 180 / PI;

	//
	FRotator NewRotation;
	NewRotation.Pitch = 0;
	NewRotation.Roll = 0;
	NewRotation.Yaw = NormalAngle - 180;

	//
	GetOwner()->SetActorRotation(NewRotation);

	if (RightHandReference->GetAttachSocketName() == RightHandSocket)
	{

		CheeseAnimInstance->UpdateSocket();

	}

	FVector CapsuleStart = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * CapsuleReference->GetScaledCapsuleRadius();
	float distanceDiff = FVector::Distance(CapsuleStart, HitResult->ImpactPoint);
	if (distanceDiff > 45)
	{
		float X = distanceDiff - 40;
		GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * X);

	}

	//CameraControllerReference->ResetCamera();

}

// End the Climb
void UClimbComponent::EndClimb()
{

	CheeseAnimInstance->bClimbing = false;

	bClimbing = false;
	MovementReference->EnableGravity();
	MovementReference->UnfreezeMovement();

	//
	RightHandReference->AttachToComponent(SkeletalMeshReference, FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true), RightHandSocket);


	RightHandReference->SetRelativeLocation(FVector(0, 0, -15.0f));

	RightHandReference->SetRelativeRotation(FRotator(0, 0, 90.0f));

}

// Climb Up
void UClimbComponent::ClimbUp(float AxisValue)
{

	if (bClimbing && AxisValue != 0 && !bClimbingFrozen)
	{
		
		FVector FinalLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorUpVector() * VerticalClimbSpeed * GetWorld()->GetDeltaSeconds();
		GetOwner()->SetActorLocation(FinalLocation);

		//
		FVector OwnerLocation = GetOwner()->GetActorLocation() + FVector(0, 0, ProbeVerticalOffset);
		FVector CapsuleStart = GetOwner()->GetActorForwardVector() * CapsuleReference->GetScaledCapsuleRadius() + ProbeStartOffsetModifier;
		FVector ProbeStart = OwnerLocation + CapsuleStart + FVector(0, 0, -1) * CapsuleReference->GetScaledCapsuleHalfHeight();
		FVector ProbeEnd = ProbeStart + (GetOwner()->GetActorForwardVector() * ForwardProbeDistance) + FVector(0, 0, -1) * CapsuleReference->GetScaledCapsuleHalfHeight();

		FHitResult* HitTest = ProbeCheck(ProbeStart, ProbeEnd);

		if (HitTest->GetActor() == nullptr || !HitTest->GetActor()->ActorHasTag(ClimbTag)) EndClimb();

	}

}

// Climb Down
void UClimbComponent::ClimbDown(float AxisValue)
{

	if (bClimbing && AxisValue != 0 && !bClimbingFrozen)
	{

		FVector FinalLocation = GetOwner()->GetActorLocation() + (GetOwner()->GetActorUpVector() * -1) * VerticalClimbSpeed * GetWorld()->GetDeltaSeconds();
		GetOwner()->SetActorLocation(FinalLocation);

		FVector CapsuleBottom = GetOwner()->GetActorLocation() + CapsuleReference->GetScaledCapsuleHalfHeight() * FVector(0, 0, -1);
		FVector CapsuleEndProbe= CapsuleBottom + FVector(0, 0, VerticalCheckDistance * -1);

		FHitResult* HitTest = ProbeCheck(CapsuleBottom, CapsuleEndProbe);

		if (HitTest->GetActor() != nullptr)	EndClimb();
	}

}

// Climb Left
void UClimbComponent::ClimbLeft(float AxisValue)
{

	if (bClimbing && AxisValue != 0 && !bClimbingFrozen)
	{

		FVector FinalLocation = GetOwner()->GetActorLocation() + (GetOwner()->GetActorRightVector() * -1) * HorizontalClimbSpeed * GetWorld()->GetDeltaSeconds();
		GetOwner()->SetActorLocation(FinalLocation);

		FHitResult* HitTest = ProbeCheck();

		if (HitTest->GetActor() == nullptr || !HitTest->GetActor()->ActorHasTag(ClimbTag)) EndClimb();

	}

}

// Climb Right
void UClimbComponent::ClimbRight(float AxisValue)
{

	if (bClimbing && AxisValue != 0 && !bClimbingFrozen)
	{

		FVector FinalLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorRightVector() * HorizontalClimbSpeed * GetWorld()->GetDeltaSeconds();
		GetOwner()->SetActorLocation(FinalLocation);

		FHitResult* HitTest = ProbeCheck();

		if (HitTest->GetActor() == nullptr || !HitTest->GetActor()->ActorHasTag(ClimbTag)) EndClimb();

	}

}

// Climb based on left stick X axis
void UClimbComponent::LeftStickClimbX(float AxisValue)
{

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%f"), AxisValue));

	if (bClimbing && AxisValue != 0 && !bClimbingFrozen)
	{


		FVector FinalLocation = GetOwner()->GetActorLocation() + (GetOwner()->GetActorRightVector() * AxisValue) * HorizontalClimbSpeed * GetWorld()->GetDeltaSeconds();
		GetOwner()->SetActorLocation(FinalLocation);

		FHitResult* HitTest = ProbeCheck();

		if (HitTest->GetActor() == nullptr || !HitTest->GetActor()->ActorHasTag(ClimbTag)) EndClimb();

	}

}

// Climb based on left stick Y stick axis
void UClimbComponent::LeftStickClimbY(float AxisValue)
{

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%f"), AxisValue));

	if (bClimbing && AxisValue != 0 && !bClimbingFrozen)
	{

		//
		FVector FinalLocation = GetOwner()->GetActorLocation() + (GetOwner()->GetActorUpVector() * AxisValue) * VerticalClimbSpeed * GetWorld()->GetDeltaSeconds();
		GetOwner()->SetActorLocation(FinalLocation);

		//
		FVector OwnerLocation = GetOwner()->GetActorLocation() + FVector(0, 0, ProbeVerticalOffset);
		FVector CapsuleStart = GetOwner()->GetActorForwardVector() * CapsuleReference->GetScaledCapsuleRadius() + ProbeStartOffsetModifier;
		FVector ProbeStart = OwnerLocation + CapsuleStart + FVector(0, 0, -1) * CapsuleReference->GetScaledCapsuleHalfHeight();
		FVector ProbeEnd = ProbeStart + (GetOwner()->GetActorForwardVector() * ForwardProbeDistance) + FVector(0, 0, -1) * CapsuleReference->GetScaledCapsuleHalfHeight();
		FVector CapsuleBottom = GetOwner()->GetActorLocation() + CapsuleReference->GetScaledCapsuleHalfHeight() * FVector(0, 0, -1);
		FVector CapsuleEndProbe = CapsuleBottom + FVector(0, 0, VerticalCheckDistance * -1);

		FHitResult* TopCheck = ProbeCheck(ProbeStart, ProbeEnd);
		FHitResult* BottomCheck = ProbeCheck(CapsuleBottom, CapsuleEndProbe);

		if (TopCheck->GetActor() == nullptr) EndClimb();
		else if (BottomCheck->GetActor() != nullptr && AxisValue < 0) EndClimb();

	}

}

FHitResult * UClimbComponent::ProbeCheck()
{

	FVector OwnerLocation = GetOwner()->GetActorLocation() + FVector(0, 0, ProbeVerticalOffset);
	FVector CapsuleStart = GetOwner()->GetActorForwardVector() * CapsuleReference->GetScaledCapsuleRadius() + ProbeStartOffsetModifier;
	FVector ProbeStart = OwnerLocation + CapsuleStart;
	FVector ProbeEnd = ProbeStart + (GetOwner()->GetActorForwardVector() * ForwardProbeDistance);

	FHitResult* HitTest = new FHitResult();
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();


	GetWorld()->LineTraceSingleByChannel(*HitTest, ProbeStart, ProbeEnd, ECC_Visibility, *TraceParams);

	return HitTest;
}

FHitResult * UClimbComponent::ProbeCheck(FVector Start, FVector End)
{

	FHitResult* HitTest = new FHitResult();
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

	GetWorld()->LineTraceSingleByChannel(*HitTest, Start, End, ECC_Visibility, *TraceParams);

	return HitTest;

}

// Freeze climbing action
void UClimbComponent::FreezeClimbing()
{

	bClimbingFrozen = true;

}

// Freeze climbing action
void UClimbComponent::UnfreezeClimbing()
{

	bClimbingFrozen = false;

}

