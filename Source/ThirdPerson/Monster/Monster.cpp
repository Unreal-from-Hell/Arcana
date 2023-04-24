// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"

#include "MonsterAIController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AMonster::AMonster()
{
	CapsuleComponent=CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent=CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	CapsuleComponent->InitCapsuleSize(70,120);
	CapsuleComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CapsuleComponent->SetCollisionProfileName("BlockAllDynamic");
	CapsuleComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);

	// TODO 부모 클래스에 PawnMovement 추가
	// PawnMovement=CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	// PawnMovement->MaxSpeed=600.f;
	// PawnMovement->Acceleration=2000.f;
	// PawnMovement->Deceleration=2000.f;
	
	AIControllerClass=AMonsterAIController::StaticClass();
	AutoPossessAI=EAutoPossessAI::PlacedInWorldOrSpawned;
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMonster::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AMonster::Attack()
{
}
