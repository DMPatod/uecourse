#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerCourseBase.generated.h"

class ADefaultHubBase;
class UInputAction;
class UInputMappingContext;
class UEnhancedInputComponent;
struct FInputActionValue;
class ACharacterCourseBase;

/**
 *
 */
UCLASS(Abstract)
class COURSE_API APlayerControllerCourseBase : public APlayerController
{
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	UInputAction* ActionMove = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	UInputAction* ActionLook = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	UInputAction* ActionJump = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	UInputAction* ActionToggleSprint = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Movement")
	UInputAction* ActionToggleCrouch = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|UI")
	UInputAction* ActionCycleUIMode = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Player Input|Character Movement")
	TObjectPtr<UInputMappingContext> InputMappingContent = nullptr;

protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	void HandleLook(const FInputActionValue& InputActionValue);
	void HandleMove(const FInputActionValue& InputActionValue);
	void HandleJump();
	void HandleToggleSprint();
	void HandleToggleCrouch();
	void HandleCycleUIMode();

private:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	UPROPERTY()
	ACharacterCourseBase* PlayerCharacter = nullptr;

	UPROPERTY()
	TObjectPtr<ADefaultHubBase> PlayerHud = nullptr;

	GENERATED_BODY()
};
