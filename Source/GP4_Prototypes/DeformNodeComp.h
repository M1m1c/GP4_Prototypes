// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "DeformNodeComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GP4_PROTOTYPES_API UDeformNodeComp : public USphereComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDeformNodeComp();

	void UpdateNodePos(float DeltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FVector localStartPos;
	UPROPERTY(EditDefaultsOnly)
	float lerpSpeed = 10.f;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
