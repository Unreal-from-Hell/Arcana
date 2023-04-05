// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss1Character.h"

#include "Boss1AnimInstance.h"
#include "Gimmick1_Projectile.h"
#include "Components/AudioComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABoss1Character::ABoss1Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<USoundCue> SCGimmick1(TEXT("SoundCue'/Game/ThirdPerson/Blueprints/Monster/Boss1/Sound/Cue/Boss1_Gimmick1_Cue.Boss1_Gimmick1_Cue'"));;
	static ConstructorHelpers::FObjectFinder<USoundCue> SCAttack(TEXT("SoundCue'/Game/ThirdPerson/Blueprints/Monster/Boss1/Sound/Cue/Boss1_AttackVoice.Boss1_AttackVoice'"));;
	static ConstructorHelpers::FObjectFinder<USoundCue> SCSword(TEXT("SoundCue'/Game/ThirdPerson/Blueprints/Monster/Boss1/Sound/Cue/Boss1_Attack_Sword.Boss1_Attack_Sword'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PNotSafeZone(TEXT("ParticleSystem'/Game/ThirdPerson/Blueprints/Monster/Boss1/Particles/FX/P_Boss1_Shield.P_Boss1_Shield'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PSafeZone(TEXT("ParticleSystem'/Game/ThirdPerson/Blueprints/Monster/Boss1/Particles/FX/P_Boss1_Shield_2.P_Boss1_Shield_2'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PDrop(TEXT("ParticleSystem'/Game/ThirdPerson/Blueprints/Monster/Boss1/Particles/FX/P_DropBoss1.P_DropBoss1'"));
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NSCast(TEXT("NiagaraSystem'/Game/ThirdPerson/Blueprints/Monster/Boss1/Particles/NS/Gimmick1/NS_Boss1_Cast.NS_Boss1_Cast'"));
	
	if(SCGimmick1.Succeeded())
		SC_Gimmick1 = SCGimmick1.Object;
	
	if(SCAttack.Succeeded())
		SC_Attack = SCAttack.Object;

	if(SCSword.Succeeded())
		SC_Sword = SCSword.Object;

	if(PNotSafeZone.Succeeded())
		P_NotSafeZoneParticle = PNotSafeZone.Object;

	if(PSafeZone.Succeeded())
		P_SafeZoneParticle = PSafeZone.Object;

	if(PDrop.Succeeded())
		P_DropBoss1Particle = PDrop.Object;

	if(NSCast.Succeeded())
		NS_ProjectileCast = NSCast.Object;

	if(_SafeZoneBoxComponent)
	{
		_SafeZoneBoxComponent->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
		_SafeZoneBoxComponent->SetCollisionProfileName(TEXT("SafeZone"));
	}
		


	bUseControllerRotationYaw=false;
	GetCharacterMovement()->bUseControllerDesiredRotation=false;
	GetCharacterMovement()->bOrientRotationToMovement=true;
	GetCharacterMovement()->RotationRate=FRotator(0.0f,480.0f,0.0f);
}

// Called when the game starts or when spawned
void ABoss1Character::BeginPlay()
{
	Super::BeginPlay();

	_gimmick1Location = GetActorLocation();
	_isAttacking=false;
	_animInstance=Cast<UBoss1AnimInstance>(GetMesh()->GetAnimInstance());
	_animInstance->OnMontageEnded.AddDynamic(this, &ABoss1Character::OnAttackMontageEnded);
	_animInstance->OnMontageEnded.AddDynamic(this, &ABoss1Character::OnGimmick1MontageEnded);
}

// Called every frame
void ABoss1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 임시로 체력이 계속 줄도록 
	if(GetHp()>75.1f)
		SetHp(GetHp()-0.02f);
	
}

// Called to bind functionality to input
void ABoss1Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABoss1Character::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(IsPlayerControlled())
	{
		// TODO 플레이어가 컨트롤중일 때
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed=400.0f;
	}
}

void ABoss1Character::Attack()
{
	if(_isAttacking)
		return;
	
	_animInstance->PlayAttackMontage();
	_animInstance->JumpToSection();
	PlayAttackSound();
	_isAttacking=true;
}

void ABoss1Character::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if(Montage->GetName() != "Boss1_Attack")
		return;
	UE_LOG(LogTemp, Warning, TEXT("OnAttackMontageEnded Called"));
	UE_LOG(LogTemp, Warning, TEXT("Montage Name: %s"), *Montage->GetName());
	_isAttacking=false;
	OnAttackEnd.Broadcast();
}

void ABoss1Character::Gimmick1()
{
	_animInstance->PlayGimmick1Montage();
	PlayGimmick1Sound();
	SpawnGimmick1ShieldParticle();
}

void ABoss1Character::Gimmick1DropProjectile()
{
	// 0.02초마다 투사체 추락
	GetWorldTimerManager().SetTimer(_countdownHandle, this, &ABoss1Character::Drop,0.02f, true);
}

void ABoss1Character::OnGimmick1MontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if(Montage->GetName() != "Boss1_Gimmick1")
		return;
	UE_LOG(LogTemp, Warning, TEXT("OnGimmick1MontageEnded Called"));
	UE_LOG(LogTemp, Warning, TEXT("Montage Name: %s"), *Montage->GetName());
	// TODO 기본공격후 호출이됨 수정필요
	OnGimmick1End.Broadcast();
	
	Gimmick1DropProjectile();

	SetbClearGimmick1(true);
}

void ABoss1Character::Drop()
{
	// 일정 시간 지난 후 Timer 초기화 
	--_countdown;
	if(_countdown <= 0)
	{
		GetWorldTimerManager().ClearTimer(_countdownHandle);
		
		for(auto Particle : ParticleSystemComponents)
			Particle->DestroyComponent();
	}
	
	FVector DropLocation = GetActorLocation() + FVector(FMath::RandRange(-5000, 5000), FMath::RandRange(-5000, 5000), 3000.0f);
	
	UWorld* World = GetWorld();
	if(World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner=this;
		SpawnParams.Instigator=GetInstigator();
		AGimmick1_Projectile* Projectile = World->SpawnActor<AGimmick1_Projectile>(ProjectileClass, DropLocation, FRotator::ZeroRotator, SpawnParams);
		Projectile->PlayProjectileCastSound();
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_ProjectileCast, Projectile->GetActorLocation(), FRotator(-90, 0 ,0));
	}
	
}

void ABoss1Character::PlayGimmick1Sound()
{
	if(SC_Gimmick1 != nullptr)
		UGameplayStatics::PlaySoundAtLocation(this, SC_Gimmick1, GetActorLocation());
}

void ABoss1Character::PlayAttackSound()
{
	if(SC_Attack != nullptr)
		UGameplayStatics::PlaySoundAtLocation(this, SC_Attack, GetActorLocation());
}

void ABoss1Character::PlaySwordSound()
{
	if(SC_Sword != nullptr)
		UGameplayStatics::PlaySoundAtLocation(this, SC_Sword, GetActorLocation());
}

void ABoss1Character::SpawnGimmick1ShieldParticle()
{
	uint8 RandomIdx = FMath::RandRange(0,3);
	uint8 idx = 0;
	// 임시로 Particle 생성
	for(auto TargetPoint : TargetPoints)
	{
		FVector SpawnFrontLocation = TargetPoint->GetActorLocation() + FVector(0,0,300); 
		FVector SpawnLeftLocation =  SpawnFrontLocation + FVector(300, -300, 0);
		FVector SpawnRightLocation = SpawnFrontLocation + FVector(300, 300, 0);
		FVector SpawnBehindLocation = SpawnFrontLocation + FVector(600, 0, 0);
		
		if(idx == RandomIdx)
		{
			// TODO 투명 콜리전 박스 생성해서 Safe Zone 생성
			_SafeZoneBoxComponent->SetWorldLocation(TargetPoint->GetActorLocation());
			
			ParticleSystemComponents.Add(UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),P_SafeZoneParticle, SpawnFrontLocation, FRotator::ZeroRotator, true));
			ParticleSystemComponents.Add(UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),P_SafeZoneParticle, SpawnLeftLocation, FRotator(0,90,0), true));
			ParticleSystemComponents.Add(UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),P_SafeZoneParticle, SpawnRightLocation, FRotator(0,90,0), true));
			ParticleSystemComponents.Add(UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),P_SafeZoneParticle, SpawnBehindLocation, FRotator::ZeroRotator, true));
			idx++;
			continue;
		}
		
		ParticleSystemComponents.Add(UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),P_NotSafeZoneParticle, SpawnFrontLocation, FRotator::ZeroRotator, true));
		ParticleSystemComponents.Add(UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),P_NotSafeZoneParticle, SpawnLeftLocation, FRotator(0,90,0), true));
		ParticleSystemComponents.Add(UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),P_NotSafeZoneParticle, SpawnRightLocation, FRotator(0,90,0), true));
		ParticleSystemComponents.Add(UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),P_NotSafeZoneParticle, SpawnBehindLocation, FRotator::ZeroRotator, true));
		idx++;
	}
}

void ABoss1Character::SpawnBoss1DropParticle()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),P_DropBoss1Particle, GetActorLocation(), FRotator::ZeroRotator, true);
}


