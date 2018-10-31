// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CheesePawn.generated.h"

UCLASS()
class TESTING_API ACheesePawn : public APawn
{

	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACheesePawn();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control")
		FName MushroomTag;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control")
		FName PickUpTag;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control")
		FName ClimbTag;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control")
		FName LedgeTag;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control")
		float CharacterSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control")
		float CharacterClimbSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control")
		float CharacterLedgeClimbSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control")
		float CameraDistance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control")
		float ZoomSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control")
		FVector2D ZoomLimits;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control")
		FKey Interactkey;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control")
		FKey ForwardKey;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control")
		FKey BackwardKey;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control")
		FKey LeftKey;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control")
		FKey RightKey;

	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control")
		float MushroomCount;
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control", meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0", AllowPrivateAccess = "true"))
		float CameraMoveSpeed;
	//
	UPROPERTY(EditAnywhere, Category = "Character Control", meta = (AllowPrivateAccess = "true"))
		FVector ItemHeldPosition;
	//
	UPROPERTY(EditAnywhere, Category = "Character Control", meta = (AllowPrivateAccess = "true"))
		TArray<AActor*> OverlappedPickups;

	UPROPERTY(EditAnywhere, Category = "Character Control", meta = (AllowPrivateAccess = "true"))
		TArray<AActor*> OverlappedMushrooms;
	//
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control", meta = (AllowPrivateAccess = "true"))
		class AActor* HeldItem;

	// Capsule component for player collider
	UPROPERTY(EditAnywhere, Category = "Component", meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* CapsuleComponent;

	// Skeletal Mesh for Character Model
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* SkeletalMesh;

	// Spring Arm component for Camera Retract and Control
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;

	// Player Camera
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

	// Static Mesh for Interaction Mesh
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* InteractMesh;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//
	UPROPERTY(BlueprintReadWrite, Category = "BlueprintExposed", meta = (AllowPrivateAccess = "true"))
		bool IsPickingStuffUp;
	//
	UPROPERTY(BlueprintReadOnly, Category = "BlueprintExposed", meta = (AllowPrivateAccess = "true"))
		bool IsFalling;
	//
	UPROPERTY(BlueprintReadOnly, Category = "BlueprintExposed", meta = (AllowPrivateAccess = "true"))
		bool IsClimbing;
	//
	UPROPERTY(BlueprintReadWrite, Category = "BlueprintExposed", meta = (AllowPrivateAccess = "true"))
		bool GravityModifier;
	//
	UPROPERTY(BlueprintReadWrite, Category = "BlueprintExposed", meta = (AllowPrivateAccess = "true"))
		bool IsLedgeClimbing;
	//
	UPROPERTY(BlueprintReadOnly, Category = "BlueprintExposed", meta = (AllowPrivateAccess = "true"))
		float ForwardPress;
	//
	UPROPERTY(BlueprintReadOnly, Category = "BlueprintExposed", meta = (AllowPrivateAccess = "true"))
		float BackwardPress;
	//
	UPROPERTY(BlueprintReadOnly, Category = "BlueprintExposed", meta = (AllowPrivateAccess = "true"))
		float LeftPress;
	//
	UPROPERTY(BlueprintReadOnly, Category = "BlueprintExposed", meta = (AllowPrivateAccess = "true"))
		float RightPress;

	UFUNCTION(BlueprintCallable, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
		void PickupOverlapBegin(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
		void PickupOverlapExit(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
		void MushroomOverlapBegin(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
		void MushroomOverlapExit(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
		void LedgeOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

	void FloorCheck();
	bool WallClimbCheck();
	void LedgeTransition();
	void PickUpTransition();
	void CombinationPress();

	//
	float GetLedgeDistance();

	// Keyboard Map
	void Interact();
	void MoveForward(float AxisValue);
	void MoveBackward(float AxisValue);
	void MoveLeft(float AxisValue);
	void MoveRight(float AxisValue);
	void Zoom(float AxisValue);

	// Mouse Control
	void MouseMoveX(float AxisValue);
	void MouseMoveY(float AxisValue);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
