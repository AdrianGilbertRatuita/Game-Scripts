// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AntiCheeseCharacter.generated.h"

UENUM(BlueprintType)
enum class EACM_Behaviour : uint8
{
	ACM_Wander UMETA(DisplayName = "Wander"),
	ACM_Approach UMETA(DisplayName = "Approach"),
	ACM_Attack	UMETA(DisplayName = "Attack"),
	ACM_Retreat	UMETA(DisplayName = "Retreat")
};

UCLASS()
class TESTING_API AAntiCheeseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAntiCheeseCharacter();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anti-Cheese AI - Control", meta = (AllowPrivateAccess = "true"))
		class AFinalCheesePawn * PlayerReference;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anti-Cheese AI - Control", meta = (AllowPrivateAccess = "true"))
		float DistanceToRunaway;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anti-Cheese AI - Control", meta = (AllowPrivateAccess = "true"))
		bool bCoward;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anti-Cheese AI - Control", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree * BehaviorTree;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Anti-Cheese AI - Control", meta = (AllowPrivateAccess = "true"))
		class UGANDMComponent * GANDMComponent;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Anti-Cheese AI - Control", meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent * CapsuleReference;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Anti-Cheese AI - Control", meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent * SkeletalMeshReference;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Anti-Cheese AI - Control", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent * WeaponMesh;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Anti-Cheese AI - Control", meta = (AllowPrivateAccess = "true"))
		class UCheesePawnAnimationInstance * AntiCheesePawnAnimationInstance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Enum, meta = (AllowPrivateAccess = "true"))
		EACM_Behaviour ACM_States;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ProcessStates();

	virtual void ConditionalProcessing();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
