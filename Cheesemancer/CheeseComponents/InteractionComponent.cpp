// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionComponent.h"
#include "FinalCheesePawn.h"

//
#include "Engine.h"
#include "BaseInteractable.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	//
	PawnReference = Cast<AFinalCheesePawn>(GetOwner());

	//
	InteractionMeshReference = PawnReference->InteractionMeshComponent;

	//
	InteractionMeshReference->OnComponentBeginOverlap.AddDynamic(this, &UInteractionComponent::InteractOverlapEnter);
	InteractionMeshReference->OnComponentEndOverlap.AddDynamic(this, &UInteractionComponent::InteractOverlapExit);
	
}

//
bool UInteractionComponent::bArrayContainsItem(FInteractable PossibleInteractable)
{

	for (int i = 0; i < OverlappedInteractables.Num(); i++)
	{

		if (PossibleInteractable.ActorClass == OverlappedInteractables[i].ActorClass &&
			PossibleInteractable.ActorReference == OverlappedInteractables[i].ActorReference)
		{

			return true;

		}

	}

	return false;
}

//
int UInteractionComponent::ArrayGetIndex(FInteractable PossibleInteractable)
{

	for (int i = 0; i < OverlappedInteractables.Num(); i++)
	{

		if (PossibleInteractable.ActorClass == OverlappedInteractables[i].ActorClass &&
			PossibleInteractable.ActorReference == OverlappedInteractables[i].ActorReference)
		{

			return i;

		}

	}

	return -1;

}

//
void UInteractionComponent::InteractAxis(float AxisValue)
{

	InteractionPress = AxisValue;

	FInteractable ClosestInteractable = ReturnClosestInteractable();
	if (ClosestInteractable.ActorReference != nullptr)
	{

		ABaseInteractable * Interactable = Cast<ABaseInteractable>(ClosestInteractable.ActorReference);
		if (!Interactable->bHasExecuted && !Interactable->bExecuting && !Interactable->bReceiveSingleInput)
		{

			Interactable->InitiateHoldPress(GetOwner());

		}
		else if (Interactable->bIsRepeatable && !Interactable->bExecuting && !Interactable->bReceiveSingleInput)
		{

			Interactable->bHasExecuted = false;
			Interactable->InitiateHoldPress(GetOwner());

		}

	}
	
}

void UInteractionComponent::InteractPress()
{

	InteractionPress = 1;

	FInteractable ClosestInteractable = ReturnClosestInteractable();
	if (ClosestInteractable.ActorReference != nullptr)
	{


		ABaseInteractable * Interactable = Cast<ABaseInteractable>(ClosestInteractable.ActorReference);
		if (!Interactable->bHasExecuted && !Interactable->bExecuting && Interactable->bReceiveSingleInput)
		{

			Interactable->InitiateForPress(GetOwner());

		}
		else if (Interactable->bIsRepeatable && !Interactable->bExecuting && Interactable->bReceiveSingleInput)
		{

			Interactable->bHasExecuted = false;
			Interactable->InitiateForPress(GetOwner());

		}

	}

}

void UInteractionComponent::InteractRelease()
{

	InteractionPress = 0;

	FInteractable ClosestInteractable = ReturnClosestInteractable();
	if (ClosestInteractable.ActorReference != nullptr)
	{

		ABaseInteractable * Interactable = Cast<ABaseInteractable>(ClosestInteractable.ActorReference);
		if (!Interactable->bHasExecuted && !Interactable->bExecuting && Interactable->bReceiveSingleInput)
		{

			Interactable->InitiateForRelease(GetOwner());

		}
		else if (Interactable->bIsRepeatable && !Interactable->bExecuting && Interactable->bReceiveSingleInput)
		{

			Interactable->bHasExecuted = false;
			Interactable->InitiateForRelease(GetOwner());

		}

	}

}

//
FInteractable UInteractionComponent::ReturnClosestInteractable()
{

	FInteractable ClosestInteractable;

	if (OverlappedInteractables.Num() != 0)
	{

		ClosestInteractable = OverlappedInteractables[0];

		for (int i = 0; i < OverlappedInteractables.Num(); i++)
		{

			FVector ActorLocation = GetOwner()->GetActorLocation();
			FVector ObjectLocation = OverlappedInteractables[i].ActorReference->GetActorLocation();
			FVector CurrentClosestLocation = ClosestInteractable.ActorReference->GetActorLocation();

			if (FVector().Distance(ActorLocation, CurrentClosestLocation) > FVector().Distance(ActorLocation, ObjectLocation))
			{

				ClosestInteractable = OverlappedInteractables[i];

			}

		}

	}

	return ClosestInteractable;

}

//
void UInteractionComponent::InteractOverlapEnter(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (OtherActor->ActorHasTag(InteractionTag))
	{

		//
		FInteractable NewAddition;
		NewAddition.ActorReference = OtherActor;
		NewAddition.ActorClass = OtherActor->StaticClass();

		//
		bool Contained = bArrayContainsItem(NewAddition);

		if (!Contained)
		{

			OverlappedInteractables.Add(NewAddition);

		}

	}

}

//
void UInteractionComponent::InteractOverlapExit(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{

	if (OtherActor->ActorHasTag(InteractionTag))
	{

		//
		FInteractable NewSubtraction;
		NewSubtraction.ActorReference = OtherActor;
		NewSubtraction.ActorClass = OtherActor->StaticClass();

		//
		int ContainedIndex = ArrayGetIndex(NewSubtraction);
		bool Contained = bArrayContainsItem(NewSubtraction);

		if (Contained)
		{

			OverlappedInteractables.RemoveAt(ContainedIndex);

		}

	}

}

// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

