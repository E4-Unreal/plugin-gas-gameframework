// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EffectArea.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
/**
 * 모닥불처럼 주기적으로 오버랩된 액터들에게 GameplayEffect를 적용하기 위한 액터 컴포넌트입니다.
 */
UCLASS(ClassGroup=(GASExtesion), meta=(BlueprintSpawnableComponent))
class GASGAMEFRAMEWORK_API UEffectArea : public UActorComponent
{
    GENERATED_BODY()

    // 오버랩 이벤트를 호출하는 주체입니다.
    UPROPERTY(BlueprintReadOnly, Category = "Dependency", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UPrimitiveComponent> Collider;

    // 오버랩된 액터에 적용할 GameplayEffect 목록입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
    TArray<TSubclassOf<UGameplayEffect>> EffectsToApply;

    // GameplayEffect 적용 간격
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
    float Period = 1.f;

    // 오버랩된 액터의 AbilitySystem과 오버랩된 시간입니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
    TMap<AActor*, float> OverlappedActors;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
    bool bInitialized;

public:
    // 생성자
    UEffectArea();

    /* ActorComponent */

    virtual void BeginPlay() override;

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    /* 초기화 */

    UFUNCTION(BlueprintCallable)
    void InjectDependencies(UPrimitiveComponent* InCollider);

protected:
    UFUNCTION(BlueprintNativeEvent)
    void ApplyEffectsToOverlappedActor(AActor* OtherActor);

private:
    /* 메서드 */

    // 오버랩된 액터들 중 AbilitySystemComponent를 가지고 있는 액터들과 오버랩된 시간을 기록합니다.
    void AddOverlappedActor(AActor* OtherActor);

    /* 이벤트 핸들링 메서드 */

    UFUNCTION()
    void OnComponentBeginOverlap_Event(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnComponentEndOverlap_Event(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
