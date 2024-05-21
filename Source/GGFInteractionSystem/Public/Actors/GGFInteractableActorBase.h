// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/GGFInteractableInterface.h"
#include "GGFInteractableActorBase.generated.h"

/**
 * 기본적인 상호작용 가능한 액터 클래스입니다.
 * 상호작용을 시도하는 대상은 기본적으로 Pawn 클래스라 가정합니다.
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
    /* 메서드 */

    // OtherActor가 플레이어 폰인 경우 플레이어 폰 반환
    static APawn* ConvertActorToPlayerPawn(AActor* OtherActor);

    // Activate 주체가 PlayerPawn인 경우
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnPlayerPawnActivate(APawn* PlayerPawn);

    // Deactivate 주체가 PlayerPawn인 경우
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnPlayerPawnDeactivate(APawn* PlayerPawn);

    // StartInteraction 주체가 PlayerPawn인 경우
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnPlayerPawnStartInteraction(APawn* PlayerPawn);

    // StopInteraction 주체가 PlayerPawn인 경우
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnPlayerPawnStopInteraction(APawn* PlayerPawn);

    // Activate 주체가 LocalPlayerPawn인 경우
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnLocalPlayerPawnActivate(APawn* LocalPlayerPawn);

    // Deactivate 주체가 LocalPlayerPawn인 경우
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnLocalPlayerPawnDeactivate(APawn* LocalPlayerPawn);

    // StartInteraction 주체가 LocalPlayerPawn인 경우
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnLocalPlayerPawnStartInteraction(APawn* LocalPlayerPawn);

    // StopInteraction 주체가 LocalPlayerPawn인 경우
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnLocalPlayerPawnStopInteraction(APawn* LocalPlayerPawn);

protected:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USceneComponent* GetDefaultScene() const { return DefaultScene; }
};
