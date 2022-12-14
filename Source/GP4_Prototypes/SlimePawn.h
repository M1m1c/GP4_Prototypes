// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SlimePawn.generated.h"

UCLASS()
class GP4_PROTOTYPES_API ASlimePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASlimePawn();


	UFUNCTION(BlueprintImplementableEvent)
		void OnFixedTick(const float deltaTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void FixedTick();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* cameraHolder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* cameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* cameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCameraDriverComp* cameraDriver;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMovementComp* movementComp;

	TArray<class UDeformNodeComp*> deformNodes;

	FTimerHandle FixedTickHandle;
	const float fixedTickDeltaTime=0.016f;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
