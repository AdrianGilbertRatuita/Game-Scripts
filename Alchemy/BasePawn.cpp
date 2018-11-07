// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"

#include "Engine.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create components
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	// Make sure main collider is Root
	RootComponent = Cast<USceneComponent>(Capsule);

	// Setup Camera Boom
	// Attach Camera Boom to RootComponent
	// Adjust arm length to preset Camera Distance
	// Make sure to use Pawn Controlller Rotation
	// Inherit Yaw from Pawn Controller Rotation
	// Inherit Pitch from Pawn Controller Rotation
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = CameraDistance;
	SpringArm->SetRelativeLocation(FVector(0, 0, CameraHeightOffset));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritPitch = true;

	// Attach Camera to Camera Boom
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	//
	StaticMesh->SetupAttachment(RootComponent);
	SkeletalMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

	// Make sure to Simulate Physics
	Capsule->SetSimulatePhysics(true);

	// Make sure Gravity is enabled
	Capsule->SetEnableGravity(true);

	// Automatically set Collision Preset to Pawn
	Capsule->SetCollisionProfileName("Pawn");

	//
	SpringArm->SetRelativeLocation(FVector(0, 0, CameraHeightOffset));

}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	HandleInput();

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("%s"), *GetControlRotation().Euler().ToString()));

}

void ABasePawn::HandleInput()
{

	// Move Character depending on player input
	if (InputComponent->GetAxisKeyValue(EKeys::W) > 0)
	{

		SetActorLocation((GetActorLocation() + GetControlRotation().Quaternion() * FVector(1, 0, 0) * CharacterMoveSpeed * GetWorld()->GetDeltaSeconds()));

	}
	if (InputComponent->GetAxisKeyValue(EKeys::S) > 0)
	{

		SetActorLocation((GetActorLocation() + GetControlRotation().Quaternion() * FVector(-1, 0, 0) * CharacterMoveSpeed * GetWorld()->GetDeltaSeconds()));
		


	}
	if (InputComponent->GetAxisKeyValue(EKeys::A) > 0)
	{

		SetActorLocation((GetActorLocation() + GetControlRotation().Quaternion() * FVector(0, -1, 0) * CharacterMoveSpeed * GetWorld()->GetDeltaSeconds()));

	}
	if (InputComponent->GetAxisKeyValue(EKeys::D) > 0)
	{

		SetActorLocation((GetActorLocation() + GetControlRotation().Quaternion() * FVector(0, 1, 0) * CharacterMoveSpeed * GetWorld()->GetDeltaSeconds()));

	}

	// Rotate camera relative to player
	AddControllerYawInput(InputComponent->GetAxisKeyValue(EKeys::MouseX));
	AddControllerPitchInput(InputComponent->GetAxisKeyValue(EKeys::MouseY));

}

// Called to bind functionality to input
// This part maybe refactored into Implementation of BasePawn
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// For Binding to Functions
	// InputComponent->BindAxisKey(EKeys::Key, this, &ActorName::FunctionName);
	// InputComponent->BindKey(EKeys::Key, IE_PRESSED, this, &ActorName::FunctionName);

	// Create Bindings
	InputComponent = PlayerInputComponent;
	InputComponent->BindAxisKey(EKeys::W);
	InputComponent->BindAxisKey(EKeys::S);
	InputComponent->BindAxisKey(EKeys::A);
	InputComponent->BindAxisKey(EKeys::D);
	InputComponent->BindAxisKey(EKeys::MouseX);
	InputComponent->BindAxisKey(EKeys::MouseY);

}

void ABasePawn::AddControllerYawInput(float Val)
{

	Super::AddControllerYawInput(IsCameraYawInverted ? Val * -1: Val);

}

void ABasePawn::AddControllerPitchInput(float Val)
{

	Super::AddControllerPitchInput(IsCameraPitchInverted ? Val * -1: Val);

}



