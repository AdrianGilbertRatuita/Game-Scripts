// Fill out your copyright notice in the Description page of Project Settings.

#include "AntiCheeseAIController.h"
#include "AntiCheeseCharacter.h"

#include "Engine/Engine.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardData.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionComponent.h"

void AAntiCheeseAIController::BeginPlay()
{

	Super::BeginPlay();

	AAntiCheeseCharacter * CharacterReferenceReference = Cast<AAntiCheeseCharacter>(GetPawn());

	if (CharacterReferenceReference)
	{

		RunBehaviorTree(CharacterReferenceReference->BehaviorTree);

	}

}

