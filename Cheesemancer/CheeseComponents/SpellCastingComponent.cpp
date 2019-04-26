// Fill out your copyright notice in the Description page of Project Settings.

#include "SpellCastingComponent.h"
#include "FinalCheesePawn.h"

//
#include "Engine/Engine.h"

//
#include "BaseInteractable.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

//
#include "GameFramework/SpringArmComponent.h"

//
#include "CheesePawnAnimationInstance.h"
#include "CheeseComponents/CameraControllerComponent.h"

//
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h"


// Sets default values for this component's properties
USpellCastingComponent::USpellCastingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void USpellCastingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	PawnReference = Cast<AFinalCheesePawn>(GetOwner());

	CapsuleReference = PawnReference->CapsuleComponent;

	SkeletalMeshReference = PawnReference->SkeletalMeshComponent;

	PhysicsHandleReference = PawnReference->PhysicsHandleComponent;

	CameraControllerReference = PawnReference->CameraControllerComponent;

	CheeseAnimInstance = Cast<UCheesePawnAnimationInstance>(SkeletalMeshReference->GetAnimInstance());
	
}


// Called every frame
void USpellCastingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure any spell casting won't put Spell Tank below 0
	if (CheeseSpellTank < 0) CheeseSpellTank = 0;

	// Make sure spell casting is disallowed if Spell Tank is Empty
	if (CheeseSpellTank == 0) bCanCast = false;
	else if (CheeseSpellTank > 0) bCanCast = true;

	// Recover Spell Tank when spell tank is not maxed
	if (CheeseSpellTank != CheeseSpellTankMax)
	{

		if (!PawnReference->GetWorldTimerManager().IsTimerActive(RecoveryHandler))
		{

			PawnReference->GetWorldTimerManager().SetTimer(RecoveryHandler, this, &USpellCastingComponent::SpellTankRecovery, TankRecoveryTime, false);

		}
	}

	if (bCooldown)
	{

		if (!PawnReference->GetWorldTimerManager().IsTimerActive(CooldownHandler))
		{

			PawnReference->GetWorldTimerManager().SetTimer(CooldownHandler, this, &USpellCastingComponent::SpellCastingCooldown, CastingCooldonwnTimer, false);

		}

	}

}


void USpellCastingComponent::SpellCastingCooldown()
{

	bCooldown = false;

}

void USpellCastingComponent::SpellCast()
{

	if (CameraControllerReference->bTargetingMode && bCanCast && !bCooldown)
	{

		//
		bCooldown = true;

		//
		CheeseAnimInstance->bSpellCasting = true;

		FVector ActorLocation = GetOwner()->GetActorLocation();
		FVector CameraStart = PawnReference->SpringArmComponent->GetSocketLocation(USpringArmComponent::SocketName);
		FVector Direction = PawnReference->GetControlRotation().Quaternion() * FVector(1, 0, 0);

		FHitResult * HitCheck = new FHitResult();
		FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

		if (GetWorld()->LineTraceSingleByChannel(*HitCheck, CameraStart, ActorLocation + Direction * AimDistance, ECC_Visibility, *TraceParams))
		{

			if (HitCheck->GetComponent()->GetOwner()->ActorHasTag(SpellInteractableTag))
			{

				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("TEST")));
				////GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%s"), *HitCheck->GetComponent()->GetFName().ToString()));
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%s"), *HitCheck->GetComponent()->GetOwner()->GetFName().ToString()));

				ABaseInteractable * SpellTarget = Cast<ABaseInteractable>(HitCheck->GetComponent()->GetOwner());
				SpellTarget->ExecuteEvent(GetOwner());

			}

			//if (HitCheck->GetComponent()->GetOwner()->ActorHasTag(SpellInteractableTag))
			//{

			//	ABaseInteractable * SpellTarget = Cast<ABaseInteractable>(HitCheck->GetComponent()->GetOwner());
			//	SpellTarget->ExecuteEvent(GetOwner());

			//}

		}

		DrawDebugLine(GetWorld(), CameraStart, ActorLocation + Direction * AimDistance, FColor::Red, false, 5, (uint8)'\000', 5.0f);

	}

}

void USpellCastingComponent::SpellTankRecovery()
{

	CheeseSpellTank += TankRecoveryRate;

	if (CheeseSpellTank > CheeseSpellTankMax) CheeseSpellTank = CheeseSpellTankMax;

}

void USpellCastingComponent::SpellTankRecoveryWithSpecifiedValue(float RecoveryValue)
{

	CheeseSpellTank += RecoveryValue;

	if (CheeseSpellTank > CheeseSpellTankMax) CheeseSpellTank = CheeseSpellTankMax;

}
