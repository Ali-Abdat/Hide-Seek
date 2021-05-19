// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "BigCubes.generated.h"

UCLASS()
class HIDEANDSEEKWITHAI_API ABigCubes : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABigCubes();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
