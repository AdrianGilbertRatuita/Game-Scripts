// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseInteractable.generated.h"

UCLASS()
class TESTING_API ABaseInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseInteractable();

	// Is Interaction executing?
	/** Boolean to check if still executing */
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		bool bExecuting;

	// Flag for starting interaction
	/** Boolean to start execution of interaction */
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		bool bExecute;

	// Has interaction finished?
	/** Boolean to check if finished executing */
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		bool bHasExecuted;

	// Is Interaction Repeatable?
	/** Boolean to denote is Interaction repeatable */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Interaction	", meta = (AllowPrivateAccess = "true"))
		bool bIsRepeatable;

	// Is Interaction Repeatable?
	/** Boolean to denote is Interaction repeatable */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Interaction	", meta = (AllowPrivateAccess = "true"))
		bool bReceiveSingleInput;

	// Function to call to initiate interaction event
	/** Function prototype for Interaction Event */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		void InitiateForPress(AActor * thisActorReference);

	// Function to call to initiate interaction event
	/** Function prototype for Interaction Event */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		void InitiateForRelease(AActor * thisActorReference);

	// Function to call to initiate interaction event
	/** Function prototype for Interaction Event */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		void InitiateHoldPress(AActor * thisActorReference);

	// Function to call to initiate event
	/** Function prototype for execution Event */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		void ExecuteEvent(AActor * thisActorReference);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
