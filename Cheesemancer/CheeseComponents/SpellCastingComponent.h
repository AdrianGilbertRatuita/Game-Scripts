// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellCastingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTING_API USpellCastingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpellCastingComponent();

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Character Control - Spell Casting", meta = (AllowPrivateAccess = "true"))
		bool bCanCast;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Character Control - Spell Casting", meta = (AllowPrivateAccess = "true"))
		bool bCooldown;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Spell Casting", meta = (AllowPrivateAccess = "true"))
		bool bNoCooldown;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Spell Casting", meta = (AllowPrivateAccess = "true"))
		float TankRecoveryTime = 5.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Spell Casting", meta = (AllowPrivateAccess = "true"))
		float TankRecoveryRate = 2.5f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Spell Casting", meta = (AllowPrivateAccess = "true"))
		float CheeseSpellTank = 10.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Spell Casting", meta = (AllowPrivateAccess = "true"))
		float CheeseSpellTankMax = 50.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Spell Casting", meta = (AllowPrivateAccess = "true"))
		float AimDistance = 2000.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Spell Casting", meta = (AllowPrivateAccess = "true"))
		float CastingCooldonwnTimer = 2.5f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - Spell Casting", meta = (AllowPrivateAccess = "true"))
		FName SpellInteractableTag = "SpellExecutive";

	UFUNCTION(BlueprintCallable, Category = "Character Control - Spell Casting", meta = (AllowPrivateAccess = "true"))
		void SpellCast();

	UFUNCTION(BlueprintCallable, Category = "Character Control - Spell Casting", meta = (AllowPrivateAccess = "true"))
		void SpellCastingCooldown();

	UFUNCTION(BlueprintCallable, Category = "Character Control - Spell Casting", meta = (AllowPrivateAccess = "true"))
		void SpellTankRecovery();

	UFUNCTION(BlueprintCallable, Category = "Character Control - Spell Casting", meta = (AllowPrivateAccess = "true"))
		void SpellTankRecoveryWithSpecifiedValue(float RecoveryValue);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FTimerHandle RecoveryHandler;

	FTimerHandle CooldownHandler;

	class AFinalCheesePawn * PawnReference;

	class UCapsuleComponent * CapsuleReference;

	class USkeletalMeshComponent * SkeletalMeshReference;

	class UPhysicsHandleComponent * PhysicsHandleReference;

	class UCheesePawnAnimationInstance * CheeseAnimInstance;

	class UCameraControllerComponent * CameraControllerReference;

public:	
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
