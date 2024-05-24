// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GEPlayerCharacter.h"
#include "Interfaces/GGFCharacterInterface.h"
#include "GGFPlayerCharacter.generated.h"

struct FInputActionValue;
class UGGFEquipmentManager;

// TODO 플레이어 캐릭터가 아닌 GGFPlayerCharacter 클래스 작성
/*
 * 기본 움직임 및 입력 액션 바인딩만 담당
 */
UCLASS()
class GGFCHARACTERSYSTEM_API AGGFPlayerCharacter : public AGEPlayerCharacter,
    public IGGFCharacterInterface
{
    GENERATED_BODY()

public:
    // EquipmentManager 서브 오브젝트 이름
    static FName EquipmentManagerName;

private:
    /* 컴포넌트 */

    // 장비를 관리하기 위한 컴포넌트입니다.
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetEquipmentManager, Category = "Component")
    TObjectPtr<UGGFEquipmentManager> EquipmentManager;

protected:
    // TODO FEquipmentTag? 구조체로 합치기?
    // 장착 장비에 따른 애님 클래스 맵
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "Equipment"))
    TMap<FGameplayTag, TSubclassOf<UAnimInstance>> AnimInstanceMap;

    // 장비 장착 애님 몽타주
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "Equipment"))
    TMap<FGameplayTag, TObjectPtr<UAnimMontage>> EquipMontageMap;

public:
    AGGFPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Character */
    // 앉은 상태에서 점프가 가능하도록 설정
    virtual bool CanJumpInternal_Implementation() const override;

    // 점프 상태에서 앉기가 불가능하도록 설정
    virtual bool CanCrouch() const override;

public:
    // TODO GGFInputConfig_Character로 이전
    /* API */

    // 캐릭터 이동
    virtual void Move(const FInputActionValue& Value);

    // 컨트롤러 회전
    virtual void Look(const FInputActionValue& Value);

    // 앉기 입력 이벤트 핸들링
    void ToggleCrouch();

public:
    /* GGFCharacterInterface */
    virtual void PlayMontage_Implementation(UAnimMontage* MontageToPlay) override;
    virtual void ChangeAnimInstance_Implementation(FGameplayTag EquipmentTag) override;

protected:
    UFUNCTION(NetMulticast, Unreliable)
    virtual void NetMulticast_PlayMontage(UAnimMontage* MontageToPlay);

protected:
    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFEquipmentManager* GetEquipmentManager() const { return EquipmentManager; }
};
