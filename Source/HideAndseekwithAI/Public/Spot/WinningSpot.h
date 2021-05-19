// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WinningSpot.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class HIDEANDSEEKWITHAI_API AWinningSpot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWinningSpot();
	UPROPERTY(VisibleAnywhere,Category = "StaticMesh")
	UStaticMeshComponent* GreenPlane;
	UPROPERTY(VisibleAnywhere, Category = "CollisionBox")
	UBoxComponent* CollisionBox;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/*
	* When you Overlap with the Green Spot A message will appear with Winner
	*/
	UFUNCTION()
	 void OnActorOverlap(AActor* OverlappedActor , AActor* OtherActor);
};
