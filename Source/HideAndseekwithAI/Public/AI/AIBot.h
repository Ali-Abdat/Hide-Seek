// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIBot.generated.h"

class UStaticMeshComponent;
class USphereComponent;
UCLASS()
class HIDEANDSEEKWITHAI_API AAIBot : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIBot();
	UPROPERTY(VisibleAnywhere, Category = Comp)
		UStaticMeshComponent* Cylinder;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere, Category = Comp)
		USphereComponent* SphereComp;
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = Comp)
		USceneComponent* Pickingup_;
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = Info)
		FVector SpawnLocation;
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = Info)
		FVector NoiseLocation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Info)
		bool SawTheEnemy;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
