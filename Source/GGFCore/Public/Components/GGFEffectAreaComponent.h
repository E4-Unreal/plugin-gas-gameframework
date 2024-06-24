// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GGFEffectAreaComponent.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

/**
 * 모닥불처럼 주기적으로 오버랩된 액터들에게 GameplayEffect를 적용하기 위한 액터 컴포넌트입니다.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFCORE_API UGGFEffectAreaComponent : public UActorComponent
{
    GENERATED_BODY()

    // 오버랩 감지를 위한 콜라이더
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetEffectArea, Category = "Reference")
    TObjectPtr<UPrimitiveComponent> EffectArea;

public:
    // 오버랩된 액터에 적용할 GameplayEffect 목록입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
    TArray<TSubclassOf<UGameplayEffect>> EffectsToApply;

    // GameplayEffect 적용 간격
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
    float Period = 1.f;

protected:
    // 오버랩된 액터의 AbilitySystem과 오버랩된 시간입니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
    TMap<TObjectPtr<AActor>, float> OverlappedActors;

public:
    // 생성자
    UGGFEffectAreaComponent();

    /* ActorComponent */

    virtual void BeginPlay() override;

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    /* 초기화 */

    UFUNCTION(BlueprintCallable)
    virtual void Init(UPrimitiveComponent* InEffectArea);

protected:
    /* 이벤트 */

    UFUNCTION(BlueprintNativeEvent)
    void OnEffectAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintNativeEvent)
    void OnEffectAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    /* 메서드 */

    UFUNCTION(BlueprintNativeEvent)
    void ApplyEffectsToOverlappedActor(AActor* OtherActor);

private:
    /* 메서드 */

    // 오버랩된 액터들 중 AbilitySystemComponent를 가지고 있는 액터들과 오버랩된 시간을 기록합니다.
    void AddOverlappedActor(AActor* OtherActor);

protected:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UPrimitiveComponent* GetEffectArea() const { return EffectArea; }
};
