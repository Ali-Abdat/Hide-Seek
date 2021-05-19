// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnGenerator.generated.h"

class AStaticMeshActor;
class AAIBot;
UCLASS()
class HIDEANDSEEKWITHAI_API ASpawnGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnGenerator();
	UPROPERTY(EditAnywhere, Category = Spawners)
		int NumberOfSmallCubes;
	UPROPERTY(EditAnywhere, Category = Spawners)
		int NumberOfBigCubes;
	UPROPERTY(EditAnywhere, Category = Spawners)
		int NumberOfBots;
	UPROPERTY(EditAnywhere, Category = Spawners)
		TSubclassOf<AStaticMeshActor> SmallCube_Class;
	UPROPERTY(EditAnywhere, Category = Spawners)
		TSubclassOf<AStaticMeshActor> BigCube_Class;
	UPROPERTY(EditAnywhere, Category = Spawners)
		TSubclassOf<AAIBot> Enemy;
	//Having a reference for the floor which will spawn on it the cubes to make sure it will spawn in the Rectangle
	UPROPERTY(EditAnywhere, Category = REF)
		AActor* RectangleFloorRef;
	UPROPERTY(VisibleDefaultsOnly,Category = Spawners)
		TArray<AStaticMeshActor*> SmallCubesRef;
	UPROPERTY(VisibleDefaultsOnly,Category = Spawners)
		TArray<AStaticMeshActor*> BigCubesRef;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//It's CallInEditor to make It changeable Locations Every Time the Cubes Spawn but the RecantagleFloorRef need to be Vaild.
	UFUNCTION(CallInEditor, Category = Spawners)
		void SpawningCubes();
	//It's Spawing AiBOTs
	UFUNCTION(Category = Spawners)
		void SpawningAIBOT();
private:
	/**
	* Called inside Spawning cubes to automatically destroying the cubes that are already existed.
	*/
	UFUNCTION(Category = Spawners)
		void RemoveAllTheCubes();
	/**
	* Called inside for loop in each one in Spawncubes, It will Loop 100 times to find the best location to by using CanSpawn and when it find it returns true with the SpawnLocation.
	* @param SpawnLocation - Passing it by value to get back the best location to spawn the Cube.
	* @param BoxExtent - It's the Cube Extend double size to avoid cubes being near Each Other Given from the SmallCube and BigCube To check the Surrounding.
	* @param Bounds - Getting the Min and Max Of the Floor Location.
	* @return The bool in which if it canSpawn or not.
	*/
	UFUNCTION(Category = Spawners)
		bool GetFreeLocation(FVector& SpawnLocation, FVector BoxExtent, FBox Bounds);
	/**
	* Called inside for loop in each one in Spawncubes, It will Loop 100 times to find the best location to spawn and when it find it returns true with the Location.
	* @param SpawnLocation - Used from the GetFreeLocation function to Cast the SweepingLineTrace
	* @param BoxExtent - For the MakingTheBox Shape
	* @return The bool in which if it can Hit another Cube or the side walls or not
	*/
	UFUNCTION(Category = Spawners)
		bool CanSpawn(FVector SpawnLocation, FVector BoxExtent);

	UFUNCTION(Category = Spawners)
		FBox GettingBoundBoxofFloor();
};
