// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickUpComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTING_API UPickUpComponent : public UActorComponent
{

	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickUpComponent();

	// Float to check if key is being pressed
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - PickUp", meta = (AllowPrivateAccess = "true"))
		float MushroomCounter = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - PickUp", meta = (AllowPrivateAccess = "true"))
		FName MushroomTag;

	// Float to check if key is being pressed
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Character Control - PickUp", meta = (AllowPrivateAccess = "true"))
		float PickUpKeyPress = 0;

	// Boolean for checking if the player is holding an Item
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Character Control - PickUp", meta = (AllowPrivateAccess = "true"))
		bool bHoldingItem;

	// Name of the tag for Pickups
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - PickUp", meta = (AllowPrivateAccess = "true"))
		FName PickupTag;

	// Name of the tag for Pickups
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - PickUp", meta = (AllowPrivateAccess = "true"))
		FName PickupAndDestroyTag;

	// Name of the Item Socket for the item to go in
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - PickUp", meta = (AllowPrivateAccess = "true"))
		FName ItemSocketName;

	// Reference to current held item
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Character Control - PickUp", meta = (AllowPrivateAccess = "true"))
		AActor * CurrentHeldItem;

	// Collection of all currently overlapped items
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Control - PickUp", meta = (AllowPrivateAccess = "true"))
		TArray<AActor*> OverlappedPickups;

	// Return the closest item that the player can pick up
	UFUNCTION(BlueprintCallable, Category = "Character Control - PickUp", meta = (AllowPrivateAccess = "true"))
		AActor * GetClosestItem();

	// Function to call for pickup press
	UFUNCTION(BlueprintCallable, Category = "Character Control - PickUp", meta = (AllowPrivateAccess = "true"))
		virtual void PickUpPress();

	// Function to call for pickup release
	UFUNCTION(BlueprintCallable, Category = "Character Control - PickUp", meta = (AllowPrivateAccess = "true"))
		virtual void PickUpRelease();

	// Bound function for Entering Overlapped Objects
	UFUNCTION(BlueprintCallable, Category = "Character Control - PickUp", meta = (AllowPrivateAccess = "true"))
		void PickUpOverlapEnter(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

	// Bound function for Exitting Overlapped Objects
	UFUNCTION(BlueprintCallable, Category = "Character Control - PickUp", meta = (AllowPrivateAccess = "true"))
		void PickUpOverlapExit(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Update item location to socket location
	void UpdateItemSocketPosition();

	// Reference to Pawn Owner
	class AFinalCheesePawn * PawnReference;

	// Reference to Skeletal Mesh for item sockets
	class USkeletalMeshComponent * SkeletalMeshReference;

	// Reference to Static Mesh used an Interaction Component
	class UStaticMeshComponent * InteractionMeshReference;

	// Reference to animation instance in Skeletal Mesh
	class UCheesePawnAnimationInstance * CheeseAnimInstance;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
