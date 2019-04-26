// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AntiCheeseMovementComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTING_API UAntiCheeseMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAntiCheeseMovementComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AntiCheese Control - Movement", meta = (AllowPrivateAccess = "true"))
		FName CheesePawnTag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AntiCheese Control - Movement", meta = (AllowPrivateAccess = "true"))
		float TimeToStayAtLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AntiCheese Control - Movement", meta = (AllowPrivateAccess = "true"))
		float MovementSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AntiCheese Control - Movement", meta = (AllowPrivateAccess = "true"))
		float AttackDistance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AntiCheese Control - Movement", meta = (AllowPrivateAccess = "true"))
		float DetectionDistance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AntiCheese Control - Movement", meta = (AllowPrivateAccess = "true"))
		FVector2D MovementRange;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "AntiCheese Control - Movement", meta = (AllowPrivateAccess = "true"))
		class AAntiCheesePawn * AntiPawnReference;

protected:

	//
	FTimerHandle StayAtLocation;

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void ProcessState();

	//
	virtual void CallAttack();

	virtual void ApproachPlayerLocation();

	virtual void RetreatOppositeToPlayer();

	virtual void MoveToLocation(FVector NewLocation);

	virtual bool LocationWithinArea(FVector NewLocation);

	virtual FVector GetDirection();

	virtual FVector CreateRandomLocation();

	class UCapsuleComponent * CapsuleReference;

	class UCheesePawnAnimationInstance * AntiCheeseAnimInstance;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
