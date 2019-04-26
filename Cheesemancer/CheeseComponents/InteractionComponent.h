// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

USTRUCT(BlueprintType)
struct FInteractable
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		AActor * ActorReference;
	UPROPERTY(BlueprintReadOnly, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		UClass * ActorClass;

	FInteractable()
	{

		ActorReference = nullptr;
		ActorClass = nullptr;

	}

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTING_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

	// Function to call for interaction
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		float InteractionPress = 0;

	// Function to call for interaction
	UFUNCTION(BlueprintCallable, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		virtual void InteractPress();

	// Function to call for interaction
	UFUNCTION(BlueprintCallable, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		virtual void InteractRelease();

	// Function to call for interaction
	UFUNCTION(BlueprintCallable, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		virtual void InteractAxis(float AxisValue);

	// Call to get closest interactable from the Player
	UFUNCTION(BlueprintCallable, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		FInteractable ReturnClosestInteractable();

	// Collection of all currently overlapped interactables
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		TArray<FInteractable> OverlappedInteractables;

	// Interaction Tag to check for
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		FName InteractionTag = "Interact";

	// Bound function for Entering Overlapped Objects
	UFUNCTION(BlueprintCallable, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		void InteractOverlapEnter(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

	// Bound function for Exitting Overlapped Objects
	UFUNCTION(BlueprintCallable, Category = "Character Control - Interaction", meta = (AllowPrivateAccess = "true"))
		void InteractOverlapExit(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Reference to Pawn Owner
	class AFinalCheesePawn * PawnReference;

	// Reference to Static Mesh used an Interaction Component
	class UStaticMeshComponent * InteractionMeshReference;

	// Gets the index of the desired interactable
	int ArrayGetIndex(FInteractable PossibleInteractable);

	// Checks if the interactable is in the list or not
	bool bArrayContainsItem(FInteractable PossibleInteractable);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
