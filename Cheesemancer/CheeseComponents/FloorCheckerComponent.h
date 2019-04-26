// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FloorCheckerComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTING_API UFloorCheckerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UFloorCheckerComponent();

	// Is Object on the Floor
	/** Is Object on the Floor */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Floor Checker Settings", meta = (AllowPrivateAccess = "true"))
		bool bOnFloor;

	// Check distance for Probe
	/** How far should the Probe be */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Floor Checker Settings", meta = (AllowPrivateAccess = "true"))
		float CheckDistance = 0;

	// Get bOnfloor
	/** Check if object is on floor */
	UFUNCTION(BlueprintCallable, Category = "Floor Checker", meta = (AllowPrivateAccess = "true"))
		bool GetbOnFloor();

	// Function to Change Check Distance
	/** Change Check Distance */
	UFUNCTION(BlueprintCallable, Category = "Floor Checker", meta = (AllowPrivateAccess = "true"))
		virtual void SetCheckDistance(float NewDistance);

	// Function to check for the floor
	/** Do a floor check */
	UFUNCTION(BlueprintCallable, Category = "Floor Checker", meta = (AllowPrivateAccess = "true"))
		virtual void FloorCheck();
		virtual void FloorCheck(FName FloorTag);

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	class AFinalCheesePawn * PawnReference;

	class UCapsuleComponent* CapsuleReference;

	class USkeletalMeshComponent * SkeletalMeshReference;

	class UCheesePawnAnimationInstance * CheeseAnimInstance;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
};
