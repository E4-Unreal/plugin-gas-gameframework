// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "GameplayTagContainer.h"
#include "Components/GGFActorComponent.h"
#include "GGFSkillManager.generated.h"

class UGGFSkillDefinition;
/**
 * 스킬 슬롯 구조체
 */
USTRUCT(Atomic, BlueprintType)
struct FGGFSkillSlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Input.Skill"))
    FGameplayTag InputTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Skill.Cooldown"))
    FGameplayTag CooldownTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ID = -1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UGGFSkillDefinition> Definition;

    UPROPERTY(Transient)
    FGameplayAbilitySpecHandle AbilitySpecHandle;

    FORCEINLINE bool IsEmpty() const { return Definition == nullptr; }

    FORCEINLINE void Clear()
    {
        ID = -1;
        Definition = nullptr;
        AbilitySpecHandle = FGameplayAbilitySpecHandle();
    }

    friend bool operator==(const FGGFSkillSlot& Lhs, const FGGFSkillSlot& Rhs)
    {
        return Lhs.InputTag == Rhs.InputTag;
    }

    friend bool operator==(const FGGFSkillSlot& Lhs, const FGameplayTag& Rhs)
    {
        return Lhs.InputTag == Rhs;
    }
};

struct FGGFSkillData;
class UGGFSkillDefinition;
class UGGFSkillDataSubsystem;

/**
 * 스킬 관리 전용 컴포넌트
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFSKILLSYSTEM_API UGGFSkillManager : public UGGFActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<FGGFSkillSlot> Slots;

public:
    /* GGFActorComponent */

    virtual void Reset() override;

    /* ActorComponent */

    virtual void BeginPlay() override;

    /* API */

    // 스킬 슬롯에 사용할 스킬 설정
    UFUNCTION(BlueprintCallable)
    virtual void SetSkillSlotByID(const FGameplayTag& InputTag, int32 ID);

    // 스킬 슬롯에 사용할 스킬 설정
    UFUNCTION(BlueprintCallable)
    virtual void SetSkillSlotByDefinition(const FGameplayTag& InputTag, UGGFSkillDefinition* Definition);

protected:
    /* 메서드 */

    UFUNCTION(BlueprintPure)
    UGGFSkillDefinition* GetSkillDefinition(int32 ID) const;

    UFUNCTION(BlueprintPure)
    UGGFSkillDataSubsystem* GetSkillDataSubsystem() const;

    UFUNCTION(BlueprintCallable)
    virtual void ClearSkillSlot(FGGFSkillSlot& Slot);
};
