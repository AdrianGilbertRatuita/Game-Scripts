// Fill out your copyright notice in the Description page of Project Settings.

#include "AntiCheeseMovementComponent.h"
#include "GANDM/AntiCheesePawn.h"
#include "CheesePawnAnimationInstance.h"

//
#include "CheesePawnAnimationInstance.h"

//
#include "Engine/Engine.h"
#include "Components/CapsuleComponent.h"

//
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"


// Sets default values for this component's properties
UAntiCheeseMovementComponent::UAntiCheeseMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAntiCheeseMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...


	AntiPawnReference = Cast<AAntiCheesePawn>(GetOwner());

	CapsuleReference = AntiPawnReference->CapsuleComponent;

	AntiCheeseAnimInstance = Cast<UCheesePawnAnimationInstance>(AntiPawnReference->SkeletalMeshComponent->GetAnimInstance());
	
}

// Called every frame
void UAntiCheeseMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	

	//ProcessState();

}

void UAntiCheeseMovementComponent::ProcessState()
{

	//switch (ACM_States)
	//{
	//	case EACM_Behaviour::ACM_Wander:
	//	{
	//		
	//		break;
	//	}
	//	case EACM_Behaviour::ACM_Approach:
	//	{
	//		ApproachPlayerLocation();
	//		break;
	//	}
	//	case EACM_Behaviour::ACM_Attack:
	//	{
	//		CallAttack();
	//		break;
	//	}
	//	case EACM_Behaviour::ACM_Retreat:
	//	{
	//		RetreatOppositeToPlayer();
	//		break;
	//	}
	//}

}

void UAntiCheeseMovementComponent::CallAttack()
{

}

void UAntiCheeseMovementComponent::ApproachPlayerLocation()
{


}

void UAntiCheeseMovementComponent::RetreatOppositeToPlayer()
{

}

void UAntiCheeseMovementComponent::MoveToLocation(FVector NewLocation)
{

}

bool UAntiCheeseMovementComponent::LocationWithinArea(FVector NewLocation)
{


	return false;
}

FVector UAntiCheeseMovementComponent::GetDirection()
{


	return FVector();

}

FVector UAntiCheeseMovementComponent::CreateRandomLocation()
{


	return FVector();

}