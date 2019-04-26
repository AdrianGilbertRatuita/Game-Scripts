// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AntiCheesePawn.generated.h"

UCLASS()
class TESTING_API AAntiCheesePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAntiCheesePawn();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anti-Cheese AI - Control", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree * BehaviorTree;	

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class AFinalCheesePawn * CheesePawnReference;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* ArrowComponent;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UGANDMComponent * GANDMComponent;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USphereComponent * AreaMesh;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent * WeaponMesh;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent * CapsuleComponent;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent * SkeletalMeshComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UAntiCheeseMovementComponent * AntiCheeseMovementComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCharacterMovementComponent * CharacterMovementComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UPawnMovementComponent * PawnMovemenComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CharacterInitialization();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
