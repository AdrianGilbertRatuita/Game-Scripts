	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CheesePawnAnimationInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTING_API UCheesePawnAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Control - Animation", meta = (AllowPrivateAccess = "true"))
		float Movement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Control - Animation", meta = (AllowPrivateAccess = "true"))
		float Forward;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Control - Animation", meta = (AllowPrivateAccess = "true"))
		float Backward;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Control - Animation", meta = (AllowPrivateAccess = "true"))
		float Left;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Control - Animation", meta = (AllowPrivateAccess = "true"))
		float Right;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Control - Animation", meta = (AllowPrivateAccess = "true"))
		float XStickMove;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Control - Animation", meta = (AllowPrivateAccess = "true"))
		float YStickMove;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Control - Animation", meta = (AllowPrivateAccess = "true"))
		float CarryingItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Control - Animation", meta = (AllowPrivateAccess = "true"))
		float Interact;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Control - Animation", meta = (AllowPrivateAccess = "true"))
		bool bAnimate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Control - Animation", meta = (AllowPrivateAccess = "true"))
		bool bWalking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Control - Animation", meta = (AllowPrivateAccess = "true"))
		bool bFalling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Control - Animation", meta = (AllowPrivateAccess = "true"))
		bool bPickingUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Control - Animation", meta = (AllowPrivateAccess = "true"))
		bool bClimbing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Control - Animation", meta = (AllowPrivateAccess = "true"))
		bool bAiming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Control - Animation", meta = (AllowPrivateAccess = "true"))
		bool bIsDying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Control - Animation", meta = (AllowPrivateAccess = "true"))
		bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Control - Animation", meta = (AllowPrivateAccess = "true"))
		bool bIsDodging;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Control - Animation", meta = (AllowPrivateAccess = "true"))
		bool bIsSliding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Control - Animation", meta = (AllowPrivateAccess = "true"))
		bool bSpellCasting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anti-Cheese Control - Animation", meta = (AllowPrivateAccess = "true"))
		bool bIsTakingDamage;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		void UpdateSocket();
};
