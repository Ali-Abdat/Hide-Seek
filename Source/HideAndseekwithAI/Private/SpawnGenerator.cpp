// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnGenerator.h"
#include "Engine/StaticMeshActor.h"
#include "UObject/Class.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AI/AIBot.h"

// Sets default values
ASpawnGenerator::ASpawnGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	NumberOfSmallCubes = 24;
	NumberOfBigCubes = 24;
}

// Called when the game starts or when spawned
void ASpawnGenerator::BeginPlay()
{
	Super::BeginPlay();
	if (Enemy)
	{
		SpawningAIBOT();
	}
}

void ASpawnGenerator::SpawningCubes()
{
	//If the (Floor ref and Small Cube Class and BigCube Class) are not Valid it Will leave the function to avoid Engine Crash
	if (!RectangleFloorRef && !SmallCube_Class && !BigCube_Class)
		return;
	RemoveAllTheCubes();
	FBox Bounds = GettingBoundBoxofFloor();
	BigCubesRef.Empty();
	FVector SpawnPoint;
	for (int i = 0; i < NumberOfBigCubes; i++)
	{
		//300 is because of the Bound of the Cube Size
		bool Found = GetFreeLocation(SpawnPoint, FVector(300), Bounds);
		if (Found)
		{
			SpawnPoint.Z += 200.0f;
			AStaticMeshActor* SpawnedCube = GetWorld()->SpawnActor<AStaticMeshActor>(BigCube_Class);
			SpawnedCube->SetActorRelativeLocation(SpawnPoint);
			BigCubesRef.Add(SpawnedCube);
		}
	}
	SmallCubesRef.Empty();
	for (int i = 0; i < NumberOfSmallCubes; i++)
	{
		//20 is because of the Bound of the Cube Size
		bool Found = GetFreeLocation(SpawnPoint, FVector(20), Bounds);
		if (Found)
		{
			SpawnPoint.Z += 60.0f;
			AStaticMeshActor* SpawnedCube = GetWorld()->SpawnActor<AStaticMeshActor>(SmallCube_Class);
			SpawnedCube->SetActorRelativeLocation(SpawnPoint);
			SmallCubesRef.Add(SpawnedCube);
		}
	}
	
}

void ASpawnGenerator::SpawningAIBOT()
{
	FBox Bounds = GettingBoundBoxofFloor();
	FVector SpawnPoint;
	for (int i = 0; i < NumberOfBots; i++)
	{
		//300 is because of the Bound of the Cube Size
		bool Found = GetFreeLocation(SpawnPoint, FVector(150), Bounds);
		if (Found)
		{
			SpawnPoint.Z += 200.0f;
			AAIBot* AiBot = GetWorld()->SpawnActor<AAIBot>(Enemy);
			AiBot->SetActorRelativeLocation(SpawnPoint);
		}
	}
}

void ASpawnGenerator::RemoveAllTheCubes()
{
	for (AStaticMeshActor* SmallCube : SmallCubesRef)
	{
		if (SmallCube)
		{
			SmallCube->Destroy();
		}	
	}
	for (AStaticMeshActor* BigCube : BigCubesRef)
	{
		if (BigCube)
		{
			BigCube->Destroy();
		}
	}
}

bool ASpawnGenerator::GetFreeLocation(FVector& SpawnLocation, FVector BoxExtent, FBox Bounds)
{
	const int NumberofAttempts = 100;
	for (size_t i = 0; i < NumberofAttempts; i++)
	{
		FVector CandidatePoint = FMath::RandPointInBox(Bounds);
		if (CanSpawn(CandidatePoint, BoxExtent))
		{
			SpawnLocation = CandidatePoint;
			return true;
		}
	}
	return false;
}

bool ASpawnGenerator::CanSpawn(FVector SpawnLocation, FVector BoxExtent)
{
	TArray<FHitResult> HitResults;
	FVector Start = SpawnLocation + FVector(0.0f, 0.0f, 300.0f);
	FVector End = SpawnLocation + FVector(0.0f, 0.0f, -300.0f);
	bool GotHit = GetWorld()->SweepMultiByChannel(HitResults,
		Start,
		End,
		FQuat::Identity,
		ECollisionChannel::ECC_WorldStatic,
		FCollisionShape::MakeBox(BoxExtent));
	if (HitResults.Num()!= 1)
	{
		return false;
	}
	if (HitResults[0].Actor == RectangleFloorRef)
	{
		return true;
	}
	return false;
}

FBox ASpawnGenerator::GettingBoundBoxofFloor()
{
	FVector PivotLocation = RectangleFloorRef->GetActorLocation();
	float HalfHorizontal = RectangleFloorRef->GetActorScale().X * 50;
	float HalfVertical = RectangleFloorRef->GetActorScale().Y * 50;
	float SpawnZ = RectangleFloorRef->GetActorLocation().Z;
	FVector Min(PivotLocation.X - HalfHorizontal, PivotLocation.Y - HalfVertical, SpawnZ);
	FVector Max(PivotLocation.X + HalfHorizontal, PivotLocation.Y + HalfVertical, SpawnZ);
	FBox Bounds(Min, Max);
	return Bounds;
}

