#include "MakePlayerController.h"
#include "GameFramework/Pawn.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "MyCharacter.h"
#include "Kismet/KismetMathLibrary.h"

AMakePlayerController::AMakePlayerController()
{
	//bShowMouseCursor = true;
	//DefaultMouseCursor = EMouseCursor::Default;
	
	// static ConstructorHelpers::FObjectFinder<UNiagaraSystem> fxCursor_object(TEXT("NiagaraSystem'/Game/Cursor/FX_Cursor.FX_Cursor'"));
	// if (fxCursor_object.Object != nullptr)
	// {
	// 	FXCursor = fxCursor_object.Object;
	// }
}



// MyPawn으로 캐릭터 정보 갖고오기 
void AMakePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	MyPawn = Cast<AMyCharacter>(GetPawn());
}

// 컨트롤러 Tick 
void AMakePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if(bInputPressed&& MyPawn->GetAttacking() == false)// &e)
	{
		UE_LOG(LogTemp,Warning,TEXT("1"));
		if(MyPawn== nullptr)
			return;

		FollowTime += DeltaTime;

		// Look for the touch location
		FVector HitLocation = FVector::ZeroVector;
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		
		HitLocation = Hit.Location;
		// Direct the Pawn towards that location
		if(MyPawn)
		{
			FVector WorldDirection = (HitLocation - MyPawn->GetActorLocation()).GetSafeNormal();
			MyPawn->AddMovementInput(WorldDirection, 1.f, false);
		}
	}
	else
	{
		FollowTime = 0.f;
	}

	//if(check == true)
	

}

// 액션, 바인드 입력 처리 
void AMakePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	//InputComponent->BindAction("SetDestination", IE_Pressed, this, &AMakePlayerController::OnSetDestinationPressed);
	//InputComponent->BindAction("SetDestination", IE_Released, this, &AMakePlayerController::OnSetDestinationReleased);
	

}
//





