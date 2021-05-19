// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIBot.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Cubes/SmallPickableCubes.h"

// Sets default values
AAIBot::AAIBot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Cylinder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cylinder"));
	Cylinder->SetupAttachment(GetCapsuleComponent());
	Cylinder->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComp->SetSphereRadius(150.0f);
	SphereComp->SetupAttachment(GetCapsuleComponent());

	Pickingup_ = CreateDefaultSubobject<USceneComponent>(TEXT("PickUp"));
	Pickingup_->SetupAttachment(GetCapsuleComponent());

}

// Called when the game starts or when spawned
void AAIBot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

