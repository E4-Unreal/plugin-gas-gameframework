// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/GGFInteractableInterface.h"
#include "GGFInteractableActorBase.generated.h"

/**
 * 인터페이스 상속 외에 아무런 기능도 구현되지 않은 가장 기본적인 상호작용 가능한 액터 클래스입니다.
 */
UCLASS()
class GGFINTERACTIONSYSTEM_API AGGFInteractableActorBase : public AActor, public IGGFInteractableInterface
{
    GENERATED_BODY()

    /* 컴포넌트 */

    // 루트 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintGetter = "GetDefaultScene", Category = "Component")
    TObjectPtr<USceneComponent> DefaultScene;

public:
    AGGFInteractableActorBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* GGFInteractableInterface */

    virtual bool Activate_Implementation(AActor* OtherActor) override;
    virtual bool Deactivate_Implementation(AActor* OtherActor) override;
    virtual bool StartInteraction_Implementation(AActor* OtherActor) override;
    virtual bool StopInteraction_Implementation(AActor* OtherActor) override;

protected:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USceneComponent* GetDefaultScene() const { return DefaultScene; }
};
