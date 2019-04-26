// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GANDMComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTING_API UGANDMComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGANDMComponent();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GANDM - Control", meta = (AllowPrivateAccess = "true"))
		class AEntityManager * EntityManagerReference;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GANDM - Control", meta = (AllowPrivateAccess = "true"))
		bool bRespawning;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GANDM - Control", meta = (AllowPrivateAccess = "true"))
		bool bCanBeAttacked;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GANDM - Control", meta = (AllowPrivateAccess = "true"))
		float MaxHitpoints = 30.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GANDM - Control", meta = (AllowPrivateAccess = "true"))
		float CurrentHitpoints = 30.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GANDM - Control", meta = (AllowPrivateAccess = "true"))
		float AttackCooldown;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GANDM - Control", meta = (AllowPrivateAccess = "true"))
		float Attack = 5.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GANDM - Control", meta = (AllowPrivateAccess = "true"))
		float Defense = 5.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GANDM - Control", meta = (AllowPrivateAccess = "true"))
		float DefenseMultiplier = 0.25f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GANDM - Control", meta = (AllowPrivateAccess = "true"))
		FVector RespawnPoint;

	UFUNCTION(BlueprintCallable, Category = "GANDM - Control", meta = (AllowPrivateAccess = "true"))
		void ApplyDamage(float Damage);

	UFUNCTION(BlueprintCallable, Category = "GANDM - Control", meta = (AllowPrivateAccess = "true"))
		void TakeDamage();

	UFUNCTION(BlueprintCallable, Category = "GANDM - Control", meta = (AllowPrivateAccess = "true"))
		void RecoverHealth(float Health);

	UFUNCTION(BlueprintCallable, Category = "GANDM - Control", meta = (AllowPrivateAccess = "true"))
		void Respawn();

	UFUNCTION(BlueprintCallable, Category = "GANDM - Control", meta = (AllowPrivateAccess = "true"))
		void ChangeRespawn(FVector NewLocation);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class UCheesePawnAnimationInstance * AnimationReference;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
