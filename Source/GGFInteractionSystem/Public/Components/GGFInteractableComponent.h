// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GGFInteractableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractSignature, AActor*, OtherActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPawnBeginOverlapSignature, APawn*, OtherPawn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPawnEndOverlapSignature, APawn*, OtherPawn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLocalPawnBeginOverlapSignature, APawn*, OtherLocalPawn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLocalPawnEndOverlapSignature, APawn*, OtherLocalPawn);

/**
 * 상호작용이 가능한 대상 액터에 부착하는 상호작용 전용 컴포넌트입니다.
 * PostInitializeComponents 혹은 BeginPlay에서 Init 메서드 호출이 필수입니다.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFINTERACTIONSYSTEM_API UGGFInteractableComponent : public UWidgetComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnInteractSignature OnInteract;

    UPROPERTY(BlueprintAssignable)
    FOnPawnBeginOverlapSignature OnPawnBeginOverlap;

    UPROPERTY(BlueprintAssignable)
    FOnPawnEndOverlapSignature OnPawnEndOverlap;

    UPROPERTY(BlueprintAssignable)
    FOnLocalPawnBeginOverlapSignature OnLocalPawnBeginOverlap;

    UPROPERTY(BlueprintAssignable)
    FOnLocalPawnEndOverlapSignature OnLocalPawnEndOverlap;

protected:
    // UI에 표시할 오브젝트 이름
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|UI")
    FName DisplayName = "Interactable Object";

    // UI에 표시할 상호작용에 대한 설명
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|UI")
    FString InteractionInfo = "Interact";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Trace")
    float MaxDistance = 1000;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Trace")
    float SphereRadius = 20;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<TObjectPtr<APawn>> OverlappedPawns;

#if WITH_EDITORONLY_DATA
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bShowDebug;
#endif

private:
    TWeakObjectPtr<UShapeComponent> InteractableArea;

    TArray<TWeakObjectPtr<UMeshComponent>> OutlineTargets;

public:
    UGGFInteractableComponent();

    /* ActorComponent */

    virtual void InitializeComponent() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    virtual void DestroyComponent(bool bPromoteChildren) override;

    /* WidgetComponent */

    virtual void InitWidget() override;

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void Init(UShapeComponent* InInteractableArea, UMeshComponent* InOutlineTarget);

    UFUNCTION(BlueprintCallable)
    virtual void TryInteract(AActor* InstigatorActor);

    UFUNCTION(BlueprintPure)
    virtual FORCEINLINE bool CanInteract(AActor* InstigatorActor) const { return true; }

protected:
    /* 이벤트 */

    UFUNCTION()
    virtual void OnInteractableAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    virtual void OnInteractableAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    /* 메서드 */

    UFUNCTION(BlueprintCallable)
    virtual void SetInteractionManager(APawn* Target, bool bTraceResult);

    UFUNCTION(BlueprintCallable)
    virtual void AddOverlappedPawn(APawn* NewPawn);

    UFUNCTION(BlueprintCallable)
    virtual void RemoveOverlappedPawn(APawn* OldPawn);

    // 외곽선 효과 활성화
    UFUNCTION(BlueprintCallable)
    virtual void EnableOutline(bool bEnable = true);

    // 로컬 플레이어 카메라가 이 물체를 바라보고 있는지 확인
    UFUNCTION(BlueprintCallable)
    virtual bool TracePawnCamera(APawn* Target, float DeltaTime);
};
