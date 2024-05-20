// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/GGFInteractableInterface.h"
#include "GGFInteractableActor.generated.h"

class UBoxComponent;
class UWidgetComponent;

/**
 * 상호작용이 가능한 액터 클래스입니다.
 */
UCLASS()
class GGFINTERACTIONSYSTEM_API AGGFInteractableActor : public AActor, public IGGFInteractableInterface
{
    GENERATED_BODY()

public:
    /* 서브 오브젝트 이름 */

    static FName InteractionWidgetName;

private:
    /* 컴포넌트 */

    // 루트 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintGetter = "GetDefaultScene", Category = "Component")
    TObjectPtr<USceneComponent> DefaultScene;

    // 상호작용 가능한 범위
    UPROPERTY(VisibleAnywhere, BlueprintGetter = "GetInteractableArea", Category = "Component")
    TObjectPtr<UBoxComponent> InteractableArea;

    // 플레이어가 오브젝트를 인식하기 위한 메시
    UPROPERTY(VisibleAnywhere, BlueprintGetter = "GetDisplayMesh", Category = "Component")
    TObjectPtr<UStaticMeshComponent> DisplayMesh;

    // 상호작용 안내를 위한 UI
    UPROPERTY(VisibleAnywhere, BlueprintGetter = "GetInteractionWidget", Category = "Component")
    TObjectPtr<UWidgetComponent> InteractionWidget;

protected:
    // 상호작용 가능한 범위 확장을 위한 추가 설정
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FVector InteractableAreaMargin;

public:
    AGGFInteractableActor();

    /* Actor */

    virtual void PostInitializeComponents() override;

    /* GGFInteractableInterface */

    virtual bool Activate_Implementation(AActor* OtherActor) override;
    virtual bool Deactivate_Implementation(AActor* OtherActor) override;
    virtual bool StartInteraction_Implementation(AActor* OtherActor) override;
    virtual bool StopInteraction_Implementation(AActor* OtherActor) override;

protected:
    // 로컬 플레이어 폰이 상호작용 가능 범위에 들어온 경우
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnLocalPlayerPawnBeginOverlap(APawn* LocalPlayerPawn);

    // 로컬 플레이어 폰이 상호작용 가능 범위에서 벗어난 경우
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnLocalPlayerPawnEndOverlap(APawn* LocalPlayerPawn);

    // 외곽선 활성화
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void EnableOutline(bool bEnable);

    // UI 표시
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void ActivateInteractionWidget(bool bActivate);

    // DisplayMesh에 따라 다른 컴포넌트들의 위치 및 크기 자동 조정
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void AdjustToDisplayMesh();

    /* 이벤트 메서드 */

    // InteractableArea::OnComponentBeginOverlap
    UFUNCTION()
    virtual void OnInteractableAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    // InteractableArea::OnComponentEndOverlap
    UFUNCTION()
    virtual void OnInteractableAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USceneComponent* GetDefaultScene() const { return DefaultScene; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UBoxComponent* GetInteractableArea() const { return InteractableArea; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UWidgetComponent* GetInteractionWidget() const { return InteractionWidget; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UStaticMeshComponent* GetDisplayMesh() const { return DisplayMesh; }
};
