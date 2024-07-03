// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueInterface.h"
#include "Actors/GGFTriggerBox.h"
#include "GGFJumpPad.generated.h"

class UArrowComponent;

/**
 * 오버랩 시 화살표 컴포넌트가 가리키는 방향으로 날리는 점프 패드입니다.
 */
UCLASS()
class GGFGIMMICKSYSTEM_API AGGFJumpPad : public AGGFTriggerBox
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetLaunchDirectionComponent, Category = "Component")
    TObjectPtr<UArrowComponent> LaunchDirectionComponent;

protected:
    // 설정된 클래스에 해당하는 액터에만 동작합니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<AActor> ActorClassToLaunch;

    // 발사 속력
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 0))
    float LaunchPower = 2000;

    // 점프 이펙트
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FGameplayCueTag LaunchCueTag;

public:
    AGGFJumpPad();

protected:
    /* TriggerBox */

    virtual void OnCollisionComponentBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

    /* 메서드 */

    UFUNCTION(BlueprintNativeEvent)
    void Launch(AActor* Target);

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UArrowComponent* GetLaunchDirectionComponent() const { return LaunchDirectionComponent; }
};
