// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AntiCheesePawnAnimationInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTING_API UAntiCheesePawnAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anti-Cheese Control - Animation", meta = (AllowPrivateAccess = "true"))
		float Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anti-Cheese Control - Animation", meta = (AllowPrivateAccess = "true"))
		bool bIsDying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anti-Cheese Control - Animation", meta = (AllowPrivateAccess = "true"))
		bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anti-Cheese Control - Animation", meta = (AllowPrivateAccess = "true"))
		bool bIsTakingDamage;
	
};
