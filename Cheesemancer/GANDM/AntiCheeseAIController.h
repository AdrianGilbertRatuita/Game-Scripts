// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AntiCheeseAIController.generated.h"


UCLASS()
class TESTING_API AAntiCheeseAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "AntiCheese Control - Movement", meta = (AllowPrivateAccess = "true"))
		class AAntiCheesePawn * AntiPawnReference;

protected:

};
