// Fill out your copyright notice in the Description page of Project Settings.

#include "FinalCheesePawn.h"

//
#include "CheeseComponents/ClimbComponent.h"
#include "CheeseComponents/PickUpComponent.h"
#include "CheeseComponents/CheesePawnMovement.h"
#include "CheeseComponents/InteractionComponent.h"
#include "CheeseComponents/FloorCheckerComponent.h"
#include "CheeseComponents/SpellCastingComponent.h"
#include "CheeseComponents/CameraControllerComponent.h"

//
#include "Engine/Engine.h"
#include "Runtime/Core/Public/Containers/Set.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "Runtime/Engine/Classes/Components/ArrowComponent.h"
#include "Runtime/Engine/Classes/Engine/SkeletalMeshSocket.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h"

//
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AFinalCheesePawn::AFinalCheesePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create default components
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("Arrow");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	InteractionMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	RightHandEquipment = CreateDefaultSubobject<UStaticMeshComponent>("Right Hand Equipment Mesh");
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh");
	PhysicsHandleComponent = CreateDefaultSubobject<UPhysicsHandleComponent>("Physics Handle");

	// Create Cheese Components
	PickUpComponent = CreateDefaultSubobject<UPickUpComponent>("Pick Up");
	ClimbComponent = CreateDefaultSubobject<UClimbComponent>("Climb Control");
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("Interaction");
	SpellCastingComponent = CreateDefaultSubobject<USpellCastingComponent>("Spell Casting");
	FloorCheckerComponent = CreateDefaultSubobject<UFloorCheckerComponent>("Floor Checker");
	CheesePawnMovement = CreateDefaultSubobject<UCheesePawnMovement>("Cheese Pawn Movement");
	CameraControllerComponent = CreateDefaultSubobject<UCameraControllerComponent>("Camera Controller");

	// Setup Pawn
	RootComponent = Cast<USceneComponent>(CapsuleComponent);
	Cast<UPrimitiveComponent>(RootComponent)->SetCollisionProfileName("Pawn");

	// Attach Camera to Springarm
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	// Attach components to RootComponent
	ArrowComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	InteractionMeshComponent->SetupAttachment(RootComponent);
	RightHandEquipment->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFinalCheesePawn::BeginPlay()
{

	Super::BeginPlay();	
	CharacterInitialization();

}

void AFinalCheesePawn::CharacterInitialization()
{

	// Setup SpringArm
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bInheritPitch = true;
	SpringArmComponent->bInheritYaw = true;
	SpringArmComponent->bInheritRoll = false;

	// Setup CapsuleComponent
	CapsuleComponent->SetEnableGravity(true);
	CapsuleComponent->SetSimulatePhysics(true);
	CapsuleComponent->BodyInstance.bLockXRotation = true;
	CapsuleComponent->BodyInstance.bLockYRotation = true;
	CapsuleComponent->BodyInstance.SetDOFLock(EDOFMode::Default);

	// Setup InteractionMesh
	InteractionMeshComponent->SetCollisionProfileName("Trigger");

	// Make right hand equipment a trigger
	RightHandEquipment->SetCollisionProfileName("Trigger");

	// Orient right hand equipment
	RightHandEquipment->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true), ClimbComponent->RightHandSocket);

}

// Called to bind functionality to input
void AFinalCheesePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent = PlayerInputComponent;

	// Keyboard
	//==================================================================================================================

	// Keyboard: Movement
	InputComponent->BindAxisKey(LeftKey, this->CheesePawnMovement, &UCheesePawnMovement::MoveLeft);
	InputComponent->BindAxisKey(RightKey, this->CheesePawnMovement, &UCheesePawnMovement::MoveRight);
	InputComponent->BindAxisKey(ForwardKey, this->CheesePawnMovement, &UCheesePawnMovement::MoveForward);
	InputComponent->BindAxisKey(BackwardKey, this->CheesePawnMovement, &UCheesePawnMovement::MoveBackward);
	InputComponent->BindKey(WalkKey, EInputEvent::IE_Released, this->CheesePawnMovement, &UCheesePawnMovement::EndWalking);
	InputComponent->BindKey(WalkKey, EInputEvent::IE_Pressed, this->CheesePawnMovement, &UCheesePawnMovement::StartWalking);

	// Keyboard: Climbing
	InputComponent->BindAxisKey(LeftKey, this->ClimbComponent, &UClimbComponent::ClimbLeft);
	InputComponent->BindAxisKey(RightKey, this->ClimbComponent, &UClimbComponent::ClimbRight);
	InputComponent->BindAxisKey(ForwardKey, this->ClimbComponent, &UClimbComponent::ClimbUp);
	InputComponent->BindAxisKey(BackwardKey, this->ClimbComponent, &UClimbComponent::ClimbDown);
	InputComponent->BindKey(KeyboardInteractKey, EInputEvent::IE_Pressed, this->ClimbComponent, &UClimbComponent::CheckForClimb);

	// Keyboard: Interaction
	InputComponent->BindKey(KeyboardInteractKey, EInputEvent::IE_Pressed, this->InteractionComponent, &UInteractionComponent::InteractPress);
	InputComponent->BindKey(KeyboardInteractKey, EInputEvent::IE_Pressed, this->InteractionComponent, &UInteractionComponent::InteractRelease);
	InputComponent->BindKey(KeyboardInteractKey, EInputEvent::IE_Pressed, this->PickUpComponent, &UPickUpComponent::PickUpPress);
	InputComponent->BindKey(KeyboardInteractKey, EInputEvent::IE_Released, this->PickUpComponent, &UPickUpComponent::PickUpRelease);

	// Mouse
	//==================================================================================================================

	// Mouse: Camera
	InputComponent->BindAxisKey(EKeys::MouseX, this->CameraControllerComponent, &UCameraControllerComponent::PanCamera);
	InputComponent->BindAxisKey(EKeys::MouseY, this->CameraControllerComponent, &UCameraControllerComponent::TiltCamera);
	InputComponent->BindAxisKey(EKeys::RightMouseButton, this->CameraControllerComponent, &UCameraControllerComponent::FocusCamera);
	InputComponent->BindKey(EKeys::RightMouseButton, EInputEvent::IE_Pressed, this->CameraControllerComponent, &UCameraControllerComponent::FocusLock);
	InputComponent->BindKey(EKeys::RightMouseButton, EInputEvent::IE_Released, this->CameraControllerComponent, &UCameraControllerComponent::FocusUnlock);
	InputComponent->BindKey(KeyboardCameraRefocusKey, EInputEvent::IE_Pressed, this->CameraControllerComponent, &UCameraControllerComponent::ResetCamera);
	InputComponent->BindKey(EKeys::LeftMouseButton, EInputEvent::IE_Pressed, this->SpellCastingComponent, &USpellCastingComponent::SpellCast);

	//==================================================================================================================

	// Gamepad
	//==================================================================================================================

	// Gamepad: Movement
	InputComponent->BindAxisKey(EKeys::Gamepad_LeftX, this->CheesePawnMovement, &UCheesePawnMovement::LeftStickXMove);
	InputComponent->BindAxisKey(EKeys::Gamepad_LeftY, this->CheesePawnMovement, &UCheesePawnMovement::LeftStickYMove);
	InputComponent->BindAxisKey(EKeys::Gamepad_LeftX, this->CheesePawnMovement, &UCheesePawnMovement::LeftStickXMove);
	InputComponent->BindAxisKey(EKeys::Gamepad_LeftY, this->CheesePawnMovement, &UCheesePawnMovement::LeftStickYMove);

	// Gamepad: Climbing
	InputComponent->BindAxisKey(EKeys::Gamepad_LeftX, this->ClimbComponent, &UClimbComponent::LeftStickClimbX);
	InputComponent->BindAxisKey(EKeys::Gamepad_LeftY, this->ClimbComponent, &UClimbComponent::LeftStickClimbY);
	InputComponent->BindKey(GamePadInteractKey, EInputEvent::IE_Pressed, this->ClimbComponent, &UClimbComponent::CheckForClimb);

	// Gamepad: Camera
	InputComponent->BindAxisKey(EKeys::Gamepad_RightX, this->CameraControllerComponent, &UCameraControllerComponent::PanCamera);
	InputComponent->BindAxisKey(EKeys::Gamepad_RightY, this->CameraControllerComponent, &UCameraControllerComponent::TiltCamera);
	InputComponent->BindAxisKey(EKeys::Gamepad_LeftTriggerAxis, this->CameraControllerComponent, &UCameraControllerComponent::FocusCamera);
	InputComponent->BindKey(GamepadCameraRefocusKey, EInputEvent::IE_Pressed, this->CameraControllerComponent, &UCameraControllerComponent::ResetCamera);
	InputComponent->BindKey(EKeys::Gamepad_LeftTriggerAxis, EInputEvent::IE_Pressed, this->CameraControllerComponent, &UCameraControllerComponent::FocusLock);
	InputComponent->BindKey(EKeys::Gamepad_LeftTriggerAxis, EInputEvent::IE_Released, this->CameraControllerComponent, &UCameraControllerComponent::FocusUnlock);
	InputComponent->BindKey(EKeys::Gamepad_RightTrigger, EInputEvent::IE_Pressed, this->SpellCastingComponent, &USpellCastingComponent::SpellCast);

	// Gamepad: Interaction
	InputComponent->BindKey(GamePadInteractKey, EInputEvent::IE_Pressed, this->InteractionComponent, &UInteractionComponent::InteractPress);
	InputComponent->BindKey(GamePadInteractKey, EInputEvent::IE_Pressed, this->InteractionComponent, &UInteractionComponent::InteractRelease);
	InputComponent->BindKey(GamePadInteractKey, EInputEvent::IE_Pressed, this->PickUpComponent, &UPickUpComponent::PickUpPress);
	InputComponent->BindKey(GamePadInteractKey, EInputEvent::IE_Released, this->PickUpComponent, &UPickUpComponent::PickUpRelease);

	//==================================================================================================================

}

// Called every frame
void AFinalCheesePawn::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	//
	if (FloorCheckerComponent)
	{

		FloorCheckerComponent->FloorCheck();

		if (FloorCheckerComponent->GetbOnFloor())
		{

			CapsuleComponent->SetLinearDamping(5.0f);
			CapsuleComponent->SetAngularDamping(5.0f);

		}
		else if (!FloorCheckerComponent->GetbOnFloor())
		{

			CapsuleComponent->SetLinearDamping(1.0f);
			CapsuleComponent->SetAngularDamping(1.0f);

		}

	}

}

