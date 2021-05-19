// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubes/BigCubes.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
ABigCubes::ABigCubes()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeObject(TEXT("/Game/Geometry/Meshes/1M_Cube"));
	GetStaticMeshComponent()->SetStaticMesh(CubeObject.Object);
	GetStaticMeshComponent()->SetRelativeScale3D(FVector(3.0f));
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
}

// Called when the game starts or when spawned
void ABigCubes::BeginPlay()
{
	Super::BeginPlay();
}


