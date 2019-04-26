// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EntityManager.generated.h"

UCLASS()
class TESTING_API AEntityManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEntityManager();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Entity - Control", meta = (AllowPrivateAccess = "true"))
		void Respawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
