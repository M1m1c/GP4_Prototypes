
#include "SlimePawn.h"

#include "CameraDriverComp.h"
#include "MovementComp.h"
#include "DeformNodeComp.h"

#include "Components/SphereComponent.h"
#include <Runtime/Engine/Classes/GameFramework/SpringArmComponent.h>
#include <Runtime/Engine/Classes/Camera/CameraComponent.h>


ASlimePawn::ASlimePawn()
{
 	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USphereComponent>(TEXT("Root"));
	RootComponent = root;

	cameraHolder = CreateDefaultSubobject<USceneComponent>(TEXT("CameraHolder"));
	cameraHolder->SetupAttachment(root);

	cameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraArm->SetupAttachment(cameraHolder);
	cameraArm->TargetArmLength = 400.0f;

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	cameraComp->SetupAttachment(cameraArm, USpringArmComponent::SocketName);

	cameraDriver = CreateDefaultSubobject<UCameraDriverComp>(TEXT("CameraDriver"));
	movementComp = CreateDefaultSubobject<UMovementComp>(TEXT("MovementComp"));
}

void ASlimePawn::BeginPlay()
{
	Super::BeginPlay();
	cameraDriver->Initalize(cameraHolder, cameraArm);
	movementComp->Initalize(cameraComp);

	auto arr= GetComponentsByClass(UDeformNodeComp::StaticClass());
	for (auto item : arr)
	{
		auto casted = Cast<UDeformNodeComp>(item);
		if (!casted) { continue; }
		deformNodes.Add(casted);
	}

	GetWorldTimerManager().SetTimer(FixedTickHandle, this, &ASlimePawn::FixedTick, fixedTickDeltaTime, true, 0.0f);
}

void ASlimePawn::FixedTick()
{
	OnFixedTick(fixedTickDeltaTime);

	movementComp->UpdateMovement(fixedTickDeltaTime);	
	cameraDriver->UpdateCamera(fixedTickDeltaTime);
	for (auto node : deformNodes)
	{
		node->UpdateNodePos(fixedTickDeltaTime);
	}
}

void ASlimePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*movementComp->UpdateMovement(DeltaTime);

	for (auto node : deformNodes)
	{
		node->UpdateNodePos(DeltaTime);
	}*/
	
}

void ASlimePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("CameraHorizontal", cameraDriver, &UCameraDriverComp::ReadCameraHorizontal);
	InputComponent->BindAxis("CameraVertical", cameraDriver, &UCameraDriverComp::ReadCameraVertical);
	InputComponent->BindAxis("CameraZoom", cameraDriver, &UCameraDriverComp::ReadCameraZoom);
	InputComponent->BindAction("FreeCameraLook", IE_Pressed, cameraDriver, &UCameraDriverComp::ToggleCameraFreeLook);

	InputComponent->BindAxis("MoveVertical", movementComp, &UMovementComp::ReadVertical);
	InputComponent->BindAxis("MoveHorizontal", movementComp, &UMovementComp::ReadHorizontal);
	InputComponent->BindAction("JumpInput", IE_Pressed, movementComp, &UMovementComp::InputPressJump);
	InputComponent->BindAction("JumpInput", IE_Released, movementComp, &UMovementComp::InputReleaseJump);
}
