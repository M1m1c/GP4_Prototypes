// Fill out your copyright notice in the Description page of Project Settings.


#include "SlimePawn.h"

#include "CameraDriverComp.h"

#include <Runtime/Engine/Classes/GameFramework/SpringArmComponent.h>
#include <Runtime/Engine/Classes/Camera/CameraComponent.h>


// Sets default values
ASlimePawn::ASlimePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;

	cameraHolder = CreateDefaultSubobject<USceneComponent>(TEXT("CameraHolder"));
	cameraHolder->SetupAttachment(root);

	cameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraArm->SetupAttachment(cameraHolder);
	cameraArm->TargetArmLength = 300.0f; // The camera follows at this distance behind the character

	// Create a follow camera
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	cameraComp->SetupAttachment(cameraArm, USpringArmComponent::SocketName);

	cameraDriver = CreateDefaultSubobject<UCameraDriverComp>(TEXT("CameraDriver"));

}

// Called when the game starts or when spawned
void ASlimePawn::BeginPlay()
{
	Super::BeginPlay();
	cameraDriver->Initalize(cameraHolder, cameraArm);
}

// Called every frame
void ASlimePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASlimePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("CameraHorizontal", cameraDriver, &UCameraDriverComp::ReadCameraHorizontal);
	InputComponent->BindAxis("CameraVertical", cameraDriver, &UCameraDriverComp::ReadCameraVertical);
	//InputComponent->BindAxis("CameraZoom", cameraDriver, &UCameraDriverComp::ReadCameraZoom);
	InputComponent->BindAction("FreeCameraLook", IE_Pressed, cameraDriver, &UCameraDriverComp::ToggleCameraFreeLook);
}
