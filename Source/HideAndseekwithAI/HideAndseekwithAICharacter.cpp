// Copyright Epic Games, Inc. All Rights Reserved.

#include "HideAndseekwithAICharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Cubes/SmallPickableCubes.h"
#include "GameFramework/Actor.h"
DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AHideAndseekwithAICharacter

AHideAndseekwithAICharacter::AHideAndseekwithAICharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	//Create Scene Component
	LeftHandGrip = CreateDefaultSubobject<USceneComponent>(TEXT("grip"));
	LeftHandGrip->SetupAttachment(Mesh1P,"hand_l");

	StartHolding = false;
	InHand = false;
}

void AHideAndseekwithAICharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	Mesh1P->SetHiddenInGame(false, true);
}


//////////////////////////////////////////////////////////////////////////
// Input

void AHideAndseekwithAICharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AHideAndseekwithAICharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHideAndseekwithAICharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AHideAndseekwithAICharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AHideAndseekwithAICharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Pickingup/ThrowItem", IE_Pressed, this, &AHideAndseekwithAICharacter::PickUp_Throwing);
	PlayerInputComponent->BindAction("Pickingup/ThrowItem", IE_Released, this, &AHideAndseekwithAICharacter::Releasing);

}

void AHideAndseekwithAICharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AHideAndseekwithAICharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AHideAndseekwithAICharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AHideAndseekwithAICharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AHideAndseekwithAICharacter::PickUp_Throwing()
{
	if (InHand)
	{
		//Activating the if in the Tick
		StartHolding = true;
	}
	else
	{
		if (GetDistractableItem())
		{
			InHand = true;
			//Attaching Cube to the FPS
			GetDistractableItem()->Attaching();
		}
	}
}

void AHideAndseekwithAICharacter::Releasing()
{
	if (GetDistractableItem() && StartHolding)
	{
		StartHolding = false;
		float Multipl = FMath::Min(TimetoExec, 2.0f);
		float Distance = Multipl * 1000.f;
		GetDistractableItem()->Detaching(Distance);
		SettingDistractableItem(nullptr);
		InHand = false;
	}
}
	
void AHideAndseekwithAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (StartHolding)
	{
		TimetoExec = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetInputKeyTimeDown(Key);
	}
}

ASmallPickableCubes* AHideAndseekwithAICharacter::GetDistractableItem()
{
	return DistractableItem_Ref;
}

void AHideAndseekwithAICharacter::SettingDistractableItem(ASmallPickableCubes* DitractableItem)
{
	DistractableItem_Ref = DitractableItem;
}

