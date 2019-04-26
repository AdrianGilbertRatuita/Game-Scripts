// Fill out your copyright notice in the Description page of Project Settings.

#include "FloorCheckerComponent.h"
#include "FinalCheesePawn.h"

//
#include "Engine/Engine.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "CheesePawnAnimationInstance.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"


UFloorCheckerComponent::UFloorCheckerComponent()
{

	// Does not need to tick every frame
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts
void UFloorCheckerComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get Owner Capsule Reference

	PawnReference = Cast<AFinalCheesePawn>(GetOwner());

	CapsuleReference = PawnReference->CapsuleComponent;

	SkeletalMeshReference = PawnReference->SkeletalMeshComponent;

	CheeseAnimInstance = Cast<UCheesePawnAnimationInstance>(SkeletalMeshReference->GetAnimInstance());

}

// Called every frame
void UFloorCheckerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Function to check for the floor regardless if it's really the floor or not
void UFloorCheckerComponent::FloorCheck()
{

	if (CapsuleReference)
	{

		FVector CapsuleBottom = GetOwner()->GetActorLocation() + CapsuleReference->GetScaledCapsuleHalfHeight() * FVector(0, 0, -1);
		CapsuleBottom += FVector(0, 0, 50);

		//
		FHitResult* FirstHitTest = new FHitResult();
		FVector PrimaryProbe = CapsuleBottom + FVector(0, 0, CheckDistance * -1);
		FCollisionQueryParams* FirstTraceParams = new FCollisionQueryParams();

		
		//FHitResult* SecondHitTest = new FHitResult();
		//FVector SecondaryProbe = CapsuleBottom + Cast<APawn>(GetOwner())->GetControlRotation().Quaternion()	 * FVector(1, 0, 0) * CheckDistance;
		//FCollisionQueryParams* SecondTraceParams = new FCollisionQueryParams();

#if !UE_BUILD_DEBUG

		DrawDebugLine(GetWorld(), CapsuleBottom, PrimaryProbe, FColor::Red, true, 1.0f, (uint8)'\000', 5.0f);
		//DrawDebugLine(GetWorld(), CapsuleBottom, SecondaryProbe, FColor::Red);

#endif // DEBUG

		//if (!GetWorld()->LineTraceSingleByChannel(*FirstHitTest, CapsuleBottom, PrimaryProbe, ECC_Visibility, *FirstTraceParams) ||
		//	!GetWorld()->LineTraceSingleByChannel(*SecondHitTest, CapsuleBottom, SecondaryProbe, ECC_Visibility, *SecondTraceParams))
		//{

		//	bOnFloor = false;
		//	CheeseAnimInstance->bFalling = true;

		//}
		//else if (GetWorld()->LineTraceSingleByChannel(*FirstHitTest, CapsuleBottom, PrimaryProbe, ECC_Visibility, *FirstTraceParams) ||
		//	GetWorld()->LineTraceSingleByChannel(*SecondHitTest, CapsuleBottom, SecondaryProbe, ECC_Visibility, *SecondTraceParams))
		//{

		//	bOnFloor = true;
		//	CheeseAnimInstance->bFalling = false;

		//}

		if (!GetWorld()->LineTraceSingleByChannel(*FirstHitTest, CapsuleBottom, PrimaryProbe, ECC_Visibility, *FirstTraceParams))
		{

			bOnFloor = false;
			CheeseAnimInstance->bFalling = true;

		}
		else if (GetWorld()->LineTraceSingleByChannel(*FirstHitTest, CapsuleBottom, PrimaryProbe, ECC_Visibility, *FirstTraceParams))
		{

			bOnFloor = true;
			CheeseAnimInstance->bFalling = false;

		}


	}

}

// Function to check for the floor if and only if it has a Floor Tag
void UFloorCheckerComponent::FloorCheck(FName FloorTag)
{

	if (CapsuleReference)
	{

		FHitResult* HitTest = new FHitResult();
		FVector CapsuleBottom = GetOwner()->GetActorLocation() + CapsuleReference->GetScaledCapsuleHalfHeight() * FVector(0, 0, -1);
		FVector ProbeDistance = CapsuleBottom + FVector(0, 0, CheckDistance * -1);
		FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

//#if !UE_BUILD_DEBUG
//
//		DrawDebugLine(GetWorld(), CapsuleBottom, CapsuleBottom + FVector(0, 0, CheckDistance * -1), FColor::Red);
//
//#endif // DEBUG


		if (!GetWorld()->LineTraceSingleByChannel(*HitTest, CapsuleBottom, ProbeDistance, ECC_Visibility, *TraceParams))
		{

			if (HitTest->GetActor()->ActorHasTag(FloorTag))
			{

				bOnFloor = false;
				CheeseAnimInstance->bFalling = true;

			}
		}
		else if (GetWorld()->LineTraceSingleByChannel(*HitTest, CapsuleBottom, ProbeDistance, ECC_Visibility, *TraceParams))
		{

			if (HitTest->GetActor()->ActorHasTag(FloorTag))
			{
				
				bOnFloor = true;
				CheeseAnimInstance->bFalling = false;

			}

		}

	}

}

// Get bOnFloor
bool UFloorCheckerComponent::GetbOnFloor()
{

	return bOnFloor;

}

// Function to Change Check Distance
void UFloorCheckerComponent::SetCheckDistance(float NewDistance)
{

	CheckDistance = NewDistance;

}
