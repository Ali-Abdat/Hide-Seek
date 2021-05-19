// Fill out your copyright notice in the Description page of Project Settings.


#include "Spot/WinningSpot.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AWinningSpot::AWinningSpot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//Creating The Component and Setting the StaticMesh using ConstructorHelper
	GreenPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GreenPlane"));
	static ConstructorHelpers::FObjectFinder <UStaticMesh> Plane(TEXT("/Game/Geometry/Meshes/1mx1mFloor"));
	GreenPlane->SetStaticMesh(Plane.Object);
	//Create The Box Component to do the actor overlap function that when the Player Overlap with he Wins The Game and setting Box Extent to fit the Plane
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	CollisionBox->SetupAttachment(GreenPlane);
	CollisionBox->SetBoxExtent(FVector(50.0f));
	this->OnActorBeginOverlap.AddDynamic(this, &AWinningSpot::OnActorOverlap);
}

// Called when the game starts or when spawned
void AWinningSpot::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWinningSpot::OnActorOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor == UGameplayStatics::GetPlayerPawn(this,0))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Winner")));
	}

}


