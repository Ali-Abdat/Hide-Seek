// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cubes/BigCubes.h"
#include "SmallPickableCubes.generated.h"


class UBoxComponent;
class UProjectileMovementComponent;
class UAIPerceptionStimuliSourceComponent;
/**
 * 
 */
UCLASS()
class HIDEANDSEEKWITHAI_API ASmallPickableCubes : public ABigCubes
{
	GENERATED_BODY()
	ASmallPickableCubes();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, Category = Component)
		UBoxComponent* BoxCollision;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere, Category = SmallBrick)
		FVector CurrentLoc;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = SmallBrick)
		bool IsChangedLocation;
	/*
	* called when pawn enters the Box component
	*/
	UFUNCTION(Category = Component)
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	/*
	* called when Pawn leaves the Box component
	*/
	UFUNCTION(Category = Component)
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	/*
	* called when Pawn leaves the Box component
	*/
	UFUNCTION(Category = Component)
		void OnStaticMeshHitComponent(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	//AAttached it the Player
	UFUNCTION(Category = Component)
		void Attaching();
	/**
	 * Detach it from Player
	 * @param Distance is the Distance given from the Holding of the mouse
	 */
	UFUNCTION(Category = Component)
		void Detaching(float Distance);
	/**
	 * Called via Detach as to start the throwing progress using the projectile.
	 * @param Distance is the Distance given from the Holding of the mouse
	 */
	UFUNCTION(Category = Component)
		void Throwed(float Distance);
};
