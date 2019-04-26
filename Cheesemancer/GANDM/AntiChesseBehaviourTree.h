// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AntiChesseBehaviourTree.generated.h"

/**
 * 
 */
UCLASS()
class TESTING_API UAntiChesseBehaviourTree : public UBehaviorTree
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		class AAntiCheeseCharacter * CharacterReference;

};
