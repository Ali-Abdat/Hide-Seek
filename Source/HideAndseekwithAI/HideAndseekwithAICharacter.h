// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HideAndseekwithAICharacter.generated.h"

class UInputComponent;
class ASmallPickableCubes;
UCLASS(config=Game)
class AHideAndseekwithAICharacter : public ACharacter
{
	GENERATED_BODY()
	#pragma region Comp
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;
	#pragma endregion
public:
	AHideAndseekwithAICharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;
	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Scene)
		class USceneComponent* LeftHandGrip;

protected:
	#pragma region Inputs
	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/*
	* to pick the small Cubes , if it's already has been picked a hold the button tho charge
	*/
	void PickUp_Throwing();
	/*
	* Release the Small cube from your hand to distract the AI Bot
	*/
	void Releasing();
	#pragma endregion 
	virtual void BeginPlay();


public:
	#pragma region FORCEINLINEs
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	/** Returns SceneComponent subobject **/
	FORCEINLINE class USceneComponent* GetLeftHandGrip() const { return LeftHandGrip; }
	#pragma endregion
	/*
	* GettingDistractableItem if needed in the Blueprint 
	*/
	UFUNCTION(BlueprintPure,BlueprintCallable,Category = Getters)
	ASmallPickableCubes* GetDistractableItem();

	/*
	* SettingDistractableItem if needed in the Blueprint
	*/
	UFUNCTION(BlueprintCallable, Category = Setter)
	void SettingDistractableItem(ASmallPickableCubes* DitractableItem);
	/** it's a bool that indicate if you got something in your hand or not */
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = Checker)
		bool InHand;
	/** it's a bool that indicate that you can start charging using the LMB */
	UPROPERTY(EditAnywhere, Category = Checker)
		bool StartHolding;
	/** it's the Key Used for the Charing */
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = Checker)
		FKey Key;

private:
	/** A Ref from the Small Pickable Cube */
	UPROPERTY()
		ASmallPickableCubes* DistractableItem_Ref;
	/** A float that Indicate the holding time of the LMB */
	UPROPERTY()
		float TimetoExec;
};

