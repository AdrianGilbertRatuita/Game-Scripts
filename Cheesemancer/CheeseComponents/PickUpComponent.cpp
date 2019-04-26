// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpComponent.h"
#include "FinalCheesePawn.h"

//
#include "BaseInteractable.h"
#include "CheesePawnAnimationInstance.h"
#include "CheeseComponents/CheesePawnMovement.h"

//
#include "Engine.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "Runtime/Engine/Classes/Engine/SkeletalMeshSocket.h"

// Sets default values for this component's properties
UPickUpComponent::UPickUpComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UPickUpComponent::BeginPlay()
{

	Super::BeginPlay();

	// ...

	PawnReference = Cast<AFinalCheesePawn>(GetOwner());

	InteractionMeshReference = PawnReference->InteractionMeshComponent;

	SkeletalMeshReference = PawnReference->SkeletalMeshComponent;

	CheeseAnimInstance = Cast<UCheesePawnAnimationInstance>(SkeletalMeshReference->GetAnimInstance());

	//
	InteractionMeshReference->OnComponentBeginOverlap.AddDynamic(this, &UPickUpComponent::PickUpOverlapEnter);
	InteractionMeshReference->OnComponentEndOverlap.AddDynamic(this, &UPickUpComponent::PickUpOverlapExit);

}

// Called every frame
void UPickUpComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	UpdateItemSocketPosition();

}


AActor * UPickUpComponent::GetClosestItem()
{

	AActor * ClosestItem = nullptr;

	if (OverlappedPickups.Num() != 0)
	{

		ClosestItem = OverlappedPickups[0];

		for (int i = 0; i < OverlappedPickups.Num(); i++)
		{

			FVector ActorLocation = GetOwner()->GetActorLocation();
			FVector ObjectLocation = OverlappedPickups[i]->GetActorLocation();
			FVector CurrentClosestLocation = ClosestItem->GetActorLocation();

			if (FVector().Distance(ActorLocation, CurrentClosestLocation) > FVector().Distance(ActorLocation, ObjectLocation))
			{

				ClosestItem = OverlappedPickups[i];

			}

		}

	}

	return ClosestItem;

}

void UPickUpComponent::PickUpPress()
{

	PickUpKeyPress = 1;

	FVector Direction = GetOwner()->GetActorLocation() + PawnReference->GetControlRotation().Quaternion() * FVector(1, 0, 0) * 500;
	FVector Extra = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 500;

	if (!CheeseAnimInstance->bPickingUp && CurrentHeldItem == nullptr)
	{

		AActor * ClosestItem = GetClosestItem();

		if (ClosestItem)
		{

			ABaseInteractable * Item = Cast<ABaseInteractable>(ClosestItem);
			if (Item)
			{

				Item->ExecuteEvent(GetOwner());

			}

			if (ClosestItem->ActorHasTag(PickupTag))
			{

				OverlappedPickups.Remove(ClosestItem);
				
				//
				CurrentHeldItem = ClosestItem;
				CheeseAnimInstance->bPickingUp = true;

				Cast<UPrimitiveComponent>(CurrentHeldItem->GetRootComponent())->SetEnableGravity(false);
				Cast<UPrimitiveComponent>(CurrentHeldItem->GetRootComponent())->SetSimulatePhysics(false);
				Cast<UPrimitiveComponent>(CurrentHeldItem->GetRootComponent())->SetCollisionProfileName("NoCollision");

				CheeseAnimInstance->CarryingItem = 1;

			}
			else if (ClosestItem->ActorHasTag(PickupAndDestroyTag) && ClosestItem->ActorHasTag(MushroomTag))
			{

				MushroomCounter++;
				OverlappedPickups.Remove(ClosestItem);
				GetWorld()->DestroyActor(ClosestItem);
				CheeseAnimInstance->bPickingUp = true;

			}
			else if (ClosestItem->ActorHasTag(PickupAndDestroyTag))
			{

				OverlappedPickups.Remove(ClosestItem);
				GetWorld()->DestroyActor(ClosestItem);
				CheeseAnimInstance->bPickingUp = true;

			}

		}

	}
	else if (CurrentHeldItem != nullptr)
	{

		//
		AActor * Item = CurrentHeldItem;
		CurrentHeldItem = nullptr;
		FVector Direction = GetOwner()->GetActorForwardVector();
		FVector FinalLocation = GetOwner()->GetActorLocation() + Direction * 500 * GetWorld()->GetDeltaSeconds();

		//
		Item->SetActorLocation(FinalLocation);

		//
		UPrimitiveComponent * NewPrimitive = Cast<UPrimitiveComponent>(Item->GetRootComponent());
		NewPrimitive->SetEnableGravity(true);
		NewPrimitive->SetSimulatePhysics(true);
		NewPrimitive->SetCollisionProfileName("PhysicsActor");
		NewPrimitive->AddImpulse((Direction + GetOwner()->GetActorUpVector() / 2) * 5000, NAME_None, true);

		CheeseAnimInstance->CarryingItem = 0;

	}

}

void UPickUpComponent::PickUpRelease()
{
		
	PickUpKeyPress = 0;

}

void UPickUpComponent::PickUpOverlapEnter(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (OtherActor->ActorHasTag(PickupTag) || OtherActor->ActorHasTag(PickupAndDestroyTag))
	{

		if (!OverlappedPickups.Contains(OtherActor) && OtherActor != nullptr)
		{

			OverlappedPickups.Add(OtherActor);

		}

	}

}

void UPickUpComponent::PickUpOverlapExit(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{

	if (OtherActor->ActorHasTag(PickupTag) || OtherActor->ActorHasTag(PickupAndDestroyTag))
	{

		if (OverlappedPickups.Contains(OtherActor) && OtherActor != nullptr)
		{

			OverlappedPickups.Remove(OtherActor);

		}

	}

}

//
void UPickUpComponent::UpdateItemSocketPosition()
{

	if (CurrentHeldItem != nullptr && SkeletalMeshReference && SkeletalMeshReference->GetSocketByName(ItemSocketName) != NULL)
	{

		FVector SocketLocation = SkeletalMeshReference->GetSocketLocation(ItemSocketName);
		CurrentHeldItem->SetActorLocation(SocketLocation);

	}

}



