// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GGFCharacterInterface.generated.h"

struct FGameplayTag;
// This class does not need to be modified.
UINTERFACE(BlueprintType, Blueprintable)
class GGFEQUIPMENTSYSTEM_API UGGFCharacterInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * 캐릭터 인터페이스
 */
class GGFEQUIPMENTSYSTEM_API IGGFCharacterInterface
{
    GENERATED_BODY()

public:
    // 캐릭터 애니메이션 재생을 위한 메서드
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void PlayMontage(UAnimMontage* MontageToPlay);

    // 장비 태그에 대응하는 애님 인스턴스 클래스로 변경하기 위한 메서드
    // 장비 장착 애님 몽타주 재생 포함
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void ChangeAnimInstance(FGameplayTag EquipmentTag);
};
