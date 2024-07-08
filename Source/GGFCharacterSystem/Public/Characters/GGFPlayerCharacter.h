﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GEPlayerCharacter.h"
#include "Interfaces/GGFCharacterAnimationInterface.h"
#include "Interfaces/GGFCharacterInterface.h"
#include "Interfaces/GGFCharacterMeshInterface.h"
#include "GGFPlayerCharacter.generated.h"

/**
 * CharacterManager와 SkinManager 설정을 위한 구조체
 */
USTRUCT(Atomic, BlueprintType)
struct FGGFCharacterConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
    int32 CharacterID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
    TArray<int32> SkinIDList;
};

class UGGFInteractionManager;
class UGGFCharacterManager;
class UGGFCharacterSkinManager;
struct FInputActionValue;
class UGGFEquipmentManager;
class UGGFSkillManager;

// TODO 플레이어 캐릭터가 아닌 GGFPlayerCharacter 클래스 작성
/*
 * 기본 움직임 및 입력 액션 바인딩만 담당
 */
UCLASS()
class GGFCHARACTERSYSTEM_API AGGFPlayerCharacter : public AGEPlayerCharacter,
    public IGGFCharacterInterface,
    public IGGFCharacterAnimationInterface,
    public IGGFCharacterMeshInterface
{
    GENERATED_BODY()

public:
    /* 서브 오브젝트 이름 */

    static FName EquipmentManagerName;
    static FName CharacterManagerName;
    static FName SkinManagerName;
    static FName InteractionManagerName;
    static FName SkillManagerName;

private:
    /* 컴포넌트 */

    // 장비를 관리하기 위한 컴포넌트입니다.
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetEquipmentManager, Category = "Component")
    TObjectPtr<UGGFEquipmentManager> EquipmentManager;

    // 캐릭터 설정을 관리하기 위한 컴포넌트입니다.
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetCharacterManager, Category = "Component")
    TObjectPtr<UGGFCharacterManager> CharacterManager;

    // 캐릭터 스킨을 관리하기 위한 컴포넌트입니다.
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetSkinManager, Category = "Component")
    TObjectPtr<UGGFCharacterSkinManager> SkinManager;

    // 상호작용을 관리하기 위한 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetInteractionManager, Category = "Component")
    TObjectPtr<UGGFInteractionManager> InteractionManager;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetSkillManager, Category = "Component")
    TObjectPtr<UGGFSkillManager> SkillManager;

protected:
    /* CharacterManager & SkinManager */

    // CharacterManager 및 SkinManager를 위한 리플리케이트된 변수
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, ReplicatedUsing = OnRep_CharacterConfig)
    FGGFCharacterConfig CharacterConfig;

    // 캐릭터 HUD 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|UI")
    TSubclassOf<UUserWidget> HUDClass;

    // 캐릭터 HUD
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|UI", Transient)
    TObjectPtr<UUserWidget> HUD;

public:
    AGGFPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Actor */

    virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    virtual void SetActorHiddenInGame(bool bNewHidden) override;

    /* Pawn */

    virtual void PossessedBy(AController* NewController) override;
    virtual void OnRep_Controller() override;
    virtual void Restart() override;

    /* Character */

    // 앉은 상태에서 점프가 가능하도록 설정
    virtual bool CanJumpInternal_Implementation() const override;

    // 점프 상태에서 앉기가 불가능하도록 설정
    virtual bool CanCrouch() const override;

    /* API */

    // TODO GGFInputConfig_Character로 이전
    // 캐릭터 이동
    virtual void Move(const FInputActionValue& Value);

    // 컨트롤러 회전
    virtual void Look(const FInputActionValue& Value);

    // 앉기 입력 이벤트 핸들링
    void ToggleCrouch();

    /* GGFCharacterAnimationInterface */

    virtual void SetAnimInstanceClass_Implementation(TSubclassOf<UAnimInstance> NewAnimInstanceClass) override;
    virtual void PlayAnimMontage_Implementation(UAnimMontage* NewAnimMontage, float Duration) override;

    // TODO ServerInitialized 어빌리티
    /* GGFCharacterInterface */

    virtual void SetCharacter_Implementation(int32 NewCharacterID) override;
    virtual void SetCharacterSkin_Implementation(int32 NewSkinID) override;
    virtual int32 GetCharacterID_Implementation() const override;
    virtual TArray<int32> GetCharacterSkinIDList_Implementation() const override;

    /* GGFCharacterMeshInterface */

    virtual USkeletalMeshComponent* GetThirdPersonMesh_Implementation() const override { return GetMesh(); }

    UFUNCTION(Server, Reliable)
    void ServerSetCharacter(int32 NewCharacterID);

    UFUNCTION(Server, Reliable)
    void ServerSetCharacterSkin(int32 NewSkinID);

protected:
    /* 메서드 */

    UFUNCTION(BlueprintCallable)
    virtual void CreateHUD();

    /* 리플리케이트 */

    // 서버 캐릭터의 CharacterConfig 값 업데이트
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ServerOnly")
    void UpdateCharacterConfig();

    UFUNCTION()
    virtual void OnRep_CharacterConfig(const FGGFCharacterConfig& OldCharacterConfig);

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFEquipmentManager* GetEquipmentManager() const { return EquipmentManager; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFCharacterManager* GetCharacterManager() const { return CharacterManager; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFCharacterSkinManager* GetSkinManager() const { return SkinManager; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFInteractionManager* GetInteractionManager() const { return InteractionManager; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFSkillManager* GetSkillManager() const { return SkillManager; }
};
