// Fill out your copyright notice in the Description page of Project Settings.

#include "GANDMComponent.h"
#include "FinalCheesePawn.h"
#include "GANDM/AntiCheeseCharacter.h"

//
#include "EntityManager.h"

//
#include "CheesePawnAnimationInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

// Sets default values for this component's properties
UGANDMComponent::UGANDMComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

}

// Called when the game starts
void UGANDMComponent::BeginPlay()
{

	Super::BeginPlay();

	RespawnPoint = GetOwner()->GetActorLocation();

	AnimationReference = Cast<UCheesePawnAnimationInstance>(Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()))->GetAnimInstance());

}

void UGANDMComponent::ApplyDamage(float Damage)
{

	CurrentHitpoints -= Damage - Defense * DefenseMultiplier;
	AnimationReference->bIsTakingDamage = true;

	if (CurrentHitpoints < 0)
	{

		GetWorld()->DestroyActor(GetOwner());

	}
		
}

void UGANDMComponent::TakeDamage()
{



}

void UGANDMComponent::RecoverHealth(float Health)
{

	CurrentHitpoints += Health;

	if (CurrentHitpoints > MaxHitpoints)
	{

		CurrentHitpoints = MaxHitpoints;

	}

}

void UGANDMComponent::Respawn()
{

	EntityManagerReference->Respawn();

}

void UGANDMComponent::ChangeRespawn(FVector NewLocation)
{

	RespawnPoint = NewLocation;

}

// Called every frame
void UGANDMComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

