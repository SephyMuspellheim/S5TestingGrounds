// Fill out your copyright notice in the Description page of Project Settings.

#include "Mannequin.h"
#include "S5TestingGrounds.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "../Weapons/Weapon.h"

// Sets default values
AMannequin::AMannequin()
{
	//Set so that character can call Tick() each frame (comment to improve performance)
	//PrimaryActorTick.bCanEverTick = true;

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (WeaponBlueprint == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("A weapon blueprint has not been specified! Please specify a Weapon Blueprint"))
			return;
	}

	EquippedWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponBlueprint);
	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	if(IsPlayerControlled())
	{
		EquippedWeapon->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
	else 
	{
		EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}

	EquippedWeapon->FPAnimInstance = Mesh1P->GetAnimInstance();
	EquippedWeapon->TPAnimInstance = GetMesh()->GetAnimInstance();

	if (InputComponent != nullptr)
	{
		// Bind fire event
		InputComponent->BindAction("PullTrigger", IE_Pressed, this, &AMannequin::PullTrigger);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AMannequin::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMannequin::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMannequin::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMannequin::LookUpAtRate);

}

void AMannequin::UnPossessed()
{
	Super::UnPossessed();

	if (EquippedWeapon != nullptr)
	{
		EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
	else
	{
		return;
	}
}

void AMannequin::PullTrigger()
{
	EquippedWeapon->OnFire();
}

void AMannequin::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMannequin::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMannequin::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMannequin::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


