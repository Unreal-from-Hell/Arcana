// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick1_Projectile.h"

#include "NiagaraFunctionLibrary.h"

// Sets default values
AGimmick1_Projectile::AGimmick1_Projectile()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NSProjectileHit(TEXT("NiagaraSystem'/Game/ThirdPerson/Blueprints/Monster/Boss1/Particles/NS/Gimmick1/NS_Boss1_Hit.NS_Boss1_Hit'"));

	if(NSProjectileHit.Succeeded())
		NS_ProjectileHit = NSProjectileHit.Object;
	
	// 콜리전 초기화
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("Projectile"));
	RootComponent=CollisionComponent;

	// Projectile Movement 초기화
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 0.0f;
	ProjectileMovementComponent->MaxSpeed = 0.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
}


// Called when the game starts or when spawned
void AGimmick1_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGimmick1_Projectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// TODO 에러 해결 및 Overlapped 해결
	//CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AGimmick1_Projectile::OnProjectileOverlap);
}

void AGimmick1_Projectile::OnProjectileOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO Overlapped 해결
	UE_LOG(LogTemp, Warning, TEXT("Projectile Overlapped"));
	//UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_ProjectileHit, GetActorLocation(), FRotator::ZeroRotator);
}

// Called every frame
void AGimmick1_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

