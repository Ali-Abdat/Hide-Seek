// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubes/SmallPickableCubes.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HideAndseekwithAI/HideAndseekwithAICharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Camera/CameraComponent.h"


ASmallPickableCubes::ASmallPickableCubes()
{
	//StaticMesh
	GetStaticMeshComponent()->SetRelativeScale3D(FVector(0.2f));
	GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetStaticMeshComponent()->SetCollisionResponseToAllChannels(ECR_Block);
	GetStaticMeshComponent()->SetNotifyRigidBodyCollision(true);
	//GetStaticMeshComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	GetStaticMeshComponent()->OnComponentHit.AddDynamic(this, &ASmallPickableCubes::OnStaticMeshHitComponent);
	//Box
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxCollision->SetupAttachment(GetStaticMeshComponent());
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	//BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxCollision->SetBoxExtent(FVector(150.0f));
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ASmallPickableCubes::OnOverlapEnd);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ASmallPickableCubes::OnOverlapBegin);

	IsChangedLocation = false;
}
// Called when the game starts or when spawned
void ASmallPickableCubes::BeginPlay()
{
	Super::BeginPlay();
	CurrentLoc = GetActorLocation();
}

void ASmallPickableCubes::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHideAndseekwithAICharacter* PlayerPawn = Cast<AHideAndseekwithAICharacter>(OtherActor);
	if (PlayerPawn)
	{
		if (!(PlayerPawn->InHand))
		{
			PlayerPawn->SettingDistractableItem(this);
		}
	}

}

void ASmallPickableCubes::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AHideAndseekwithAICharacter* PlayerPawn = Cast<AHideAndseekwithAICharacter>(OtherActor);
	if (PlayerPawn)
	{
		if (!(PlayerPawn->InHand))
		{
			PlayerPawn->SettingDistractableItem(nullptr);
		}
	}
}


void ASmallPickableCubes::OnStaticMeshHitComponent(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AHideAndseekwithAICharacter* PlayerPawn = Cast<AHideAndseekwithAICharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//GetStaticMeshComponent()->SetNotifyRigidBodyCollision(false);
	IsChangedLocation = true;
	MakeNoise(1.0, PlayerPawn);
}

void ASmallPickableCubes::Attaching()
{
	GetStaticMeshComponent()->SetSimulatePhysics(false);
	AHideAndseekwithAICharacter* PlayerPawn = Cast<AHideAndseekwithAICharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetStaticMeshComponent()->SetCollisionResponseToAllChannels(ECR_Overlap);
	SetActorLocation(FVector(0.0f));
	AttachToComponent(PlayerPawn->GetLeftHandGrip(), FAttachmentTransformRules::KeepRelativeTransform);
}

void ASmallPickableCubes::Detaching(float Distance)
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Throwed(Distance);
}

void ASmallPickableCubes::Throwed(float Distance)
{
	AHideAndseekwithAICharacter* PlayerPawn = Cast<AHideAndseekwithAICharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	GetStaticMeshComponent()->SetSimulatePhysics(true);
	GetStaticMeshComponent()->SetCollisionResponseToAllChannels(ECR_Block);
	FVector Forward = PlayerPawn->GetFirstPersonCameraComponent()->GetForwardVector();
	GetStaticMeshComponent()->SetNotifyRigidBodyCollision(true);
	GetStaticMeshComponent()->AddImpulse(Forward*Distance,NAME_None,true);
}

