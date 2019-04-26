// Fill out your copyright notice in the Description page of Project Settings.

#include "AntiCheeseCharacter.h"
#include "FinalCheesePawn.h"

//
#include "GANDM/GANDMComponent/GANDMComponent.h"
#include "CheesePawnAnimationInstance.h"

//
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

//
#include "Engine/Engine.h"
#include "AntiCheeseAIController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/ArrowComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"

// Sets default values
AAntiCheeseCharacter::AAntiCheeseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//
	GANDMComponent = CreateDefaultSubobject<UGANDMComponent>("UGANDM");

	// Create Weapon Mesh
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("Weapon Mesh");

	// Get References to inherited Components
	SkeletalMeshReference = GetMesh();
	CapsuleReference = GetCapsuleComponent();
	WeaponMesh->SetupAttachment(RootComponent);

	//
	RootComponent = Cast<USceneComponent>(CapsuleReference);
	Cast<UPrimitiveComponent>(RootComponent)->SetCollisionProfileName("Pawn");

}

// Called when the game starts or when spawned
void AAntiCheeseCharacter::BeginPlay()
{

	Super::BeginPlay();

	ACM_States = EACM_Behaviour::ACM_Wander;

	// Setup CapsuleComponent
	CapsuleReference->SetEnableGravity(true);
	CapsuleReference->SetSimulatePhysics(false);
	CapsuleReference->BodyInstance.bLockXRotation = true;
	CapsuleReference->BodyInstance.bLockYRotation = true;
	CapsuleReference->BodyInstance.SetDOFLock(EDOFMode::Default);

	//
	WeaponMesh->SetCollisionProfileName("Trigger");

	// Orient right hand equipment
	WeaponMesh->AttachToComponent(SkeletalMeshReference, FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true), "Socket_HandR");

	AntiCheesePawnAnimationInstance = Cast<UCheesePawnAnimationInstance>(SkeletalMeshReference->GetAnimInstance());

}

void AAntiCheeseCharacter::ProcessStates()
{

	switch (ACM_States)
	{

		case EACM_Behaviour::ACM_Wander:
		{
		
			break;
		}
		case EACM_Behaviour::ACM_Approach:
		{

			break;
		}
		case EACM_Behaviour::ACM_Attack:
		{

			break;
		}
		case EACM_Behaviour::ACM_Retreat:
		{

			break;
		}

	}

}

void AAntiCheeseCharacter::ConditionalProcessing()
{

	// If enemy is a coward
	if (bCoward)
	{

		FVector PlayerDistance = PlayerReference->GetActorLocation();

		if (FVector::Distance(PlayerDistance, GetActorLocation()) < DistanceToRunaway)
		{

			ACM_States = EACM_Behaviour::ACM_Retreat;

		}

	}

}

// Called every frame
void AAntiCheeseCharacter::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	ProcessStates();

	ConditionalProcessing();

}

// Called to bind functionality to input
void AAntiCheeseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

