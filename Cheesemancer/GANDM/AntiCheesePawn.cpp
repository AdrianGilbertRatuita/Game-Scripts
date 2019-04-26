// Fill out your copyright notice in the Description page of Project Settings.

#include "AntiCheesePawn.h"
#include "FinalCheesePawn.h"

//
#include "GANDM/GANDMComponent/GANDMComponent.h"
#include "GANDM/GANDMComponent/AntiCheeseMovementComponent.h"

//
#include "Components/SphereComponent.h"
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
#include "Runtime/Engine/Classes/GameFramework/PawnMovementComponent.h"

// Sets default values
AAntiCheesePawn::AAntiCheesePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//
	CharacterMovementComponent = CreateDefaultSubobject<UCharacterMovementComponent>("Character Move");
	PawnMovemenComponent = CreateDefaultSubobject<UPawnMovementComponent>("Pawn Move");

	//
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("Arrow");
	AreaMesh = CreateDefaultSubobject<USphereComponent>("Area");
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("Weapon");
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh");

	//
	GANDMComponent = CreateDefaultSubobject<UGANDMComponent>("GANDM");
	AntiCheeseMovementComponent = CreateDefaultSubobject<UAntiCheeseMovementComponent>("Anti-Cheese Movement");

	//
	RootComponent = Cast<USceneComponent>(CapsuleComponent);
	Cast<UPrimitiveComponent>(RootComponent)->SetCollisionProfileName("Pawn");

	//
	AreaMesh->SetupAttachment(RootComponent);
	ArrowComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	WeaponMesh->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AAntiCheesePawn::BeginPlay()
{

	Super::BeginPlay();
	
	CharacterInitialization();

}

void AAntiCheesePawn::CharacterInitialization()
{

	// Setup CapsuleComponent
	CapsuleComponent->SetEnableGravity(true);
	CapsuleComponent->SetSimulatePhysics(true);
	CapsuleComponent->BodyInstance.bLockXRotation = true;
	CapsuleComponent->BodyInstance.bLockYRotation = true;
	CapsuleComponent->BodyInstance.SetDOFLock(EDOFMode::Default);

	//
	if (AreaMesh)
	{

		AreaMesh->SetCollisionProfileName("NoCollision");
		AreaMesh->SetSphereRadius(AntiCheeseMovementComponent->DetectionDistance);
		AreaMesh->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true), NAME_None);

	}

	//
	WeaponMesh->SetCollisionProfileName("Trigger");

	// Orient right hand equipment
	WeaponMesh->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true), "Socket_HandR");

}

// Called every frame
void AAntiCheesePawn::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAntiCheesePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

