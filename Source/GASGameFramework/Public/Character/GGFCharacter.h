// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GEPlayerCharacter.h"
#include "Interfaces/GGFCharacterInterface.h"
#include "GGFCharacter.generated.h"

struct FInputActionValue;
class UGGFEquipmentManager;

/*
 * 기본 움직임 및 입력 액션 바인딩만 담당
 */
UCLASS()
class GASGAMEFRAMEWORK_API AGGFCharacter : public AGEPlayerCharacter, public IGGFCharacterInterface
{
    GENERATED_BODY()

public:
    /* EquipmentManager의 이름으로 다른 클래스로 교체할 때 사용합니다. */
    static FName EquipmentManagerName;

private:
    /* 컴포넌트 */
    // 장비를 관리하기 위한 컴포넌트입니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UGGFEquipmentManager> EquipmentManager;

public:
    AGGFCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

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

protected:
    UFUNCTION(NetMulticast, Unreliable)
    virtual void NetMulticast_PlayMontage(UAnimMontage* MontageToPlay);
};
