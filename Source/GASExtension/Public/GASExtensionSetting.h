// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "GASExtensionSetting.generated.h"

/**
 *	Damage.Type 카테고리로 제한된 게임플레이 태그 래핑 구조체
 */
USTRUCT(Atomic, BlueprintType)
struct FDamageTypeTag
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Damage.Type"))
    FGameplayTag Tag;

    /* 생성자 */

    FDamageTypeTag() { }

    FDamageTypeTag(FGameplayTag InTag)
    {
        Tag = InTag;
    }

    /* API */

    FORCEINLINE bool IsValid() const
    {
        return Tag.IsValid() && Tag.MatchesTag(Tag);
    }

    /* 연산자 */

    FORCEINLINE bool operator==(const FDamageTypeTag& Other) const
    {
        return Equals(Other);
    }

    FORCEINLINE bool operator!=(const FDamageTypeTag& Other) const
    {
        return !(*this == Other);
    }

    FORCEINLINE bool Equals(const FDamageTypeTag& Other) const
    {
        return Tag.MatchesTagExact(Other.Tag);
    }

    FORCEINLINE bool operator==(const FGameplayTag& Other) const
    {
        return Equals(Other);
    }

    FORCEINLINE bool operator!=(const FGameplayTag& Other) const
    {
        return !(*this == Other);
    }

    FORCEINLINE bool Equals(const FGameplayTag& Other) const
    {
        return Tag.MatchesTagExact(Other);
    }

    friend FORCEINLINE uint32 GetTypeHash(const FDamageTypeTag& DamageTypeTag)
    {
        return GetTypeHash(DamageTypeTag.Tag);
    }

    FORCEINLINE FDamageTypeTag& operator=(const FGameplayTag& Other)
    {
        Tag = Other;
        return *this;
    }
};

/**
 *	Buff.Immunity 카테고리로 제한된 게임플레이 태그 래핑 구조체
 */
USTRUCT(Atomic, BlueprintType)
struct FImmunityTag
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Buff.Immunity"))
    FGameplayTag Tag;

    /* 생성자 */

    FImmunityTag() { }

    FORCEINLINE FImmunityTag(FGameplayTag InTag)
    {
        Tag = InTag;
    }

    /* API */

    FORCEINLINE bool IsValid() const
    {
        return Tag.IsValid() && Tag.MatchesTag(Tag);
    }

    /* 연산자 */

    FORCEINLINE bool operator==(const FImmunityTag& Other) const
    {
        return Equals(Other);
    }

    FORCEINLINE bool operator!=(const FImmunityTag& Other) const
    {
        return !(*this == Other);
    }

    FORCEINLINE bool Equals(const FImmunityTag& Other) const
    {
        return Tag.MatchesTagExact(Other.Tag);
    }

    FORCEINLINE bool operator==(const FGameplayTag& Other) const
    {
        return Equals(Other);
    }

    FORCEINLINE bool operator!=(const FGameplayTag& Other) const
    {
        return !(*this == Other);
    }

    FORCEINLINE bool Equals(const FGameplayTag& Other) const
    {
        return Tag.MatchesTagExact(Other);
    }

    friend FORCEINLINE uint32 GetTypeHash(const FImmunityTag& ImmunityTag)
    {
        return GetTypeHash(ImmunityTag.Tag);
    }

    FORCEINLINE FImmunityTag& operator=(const FGameplayTag& Other)
    {
        Tag = Other;
        return *this;
    }
};

/**
 * GASExtension 모듈 전용 프로젝트 설정
 */
UCLASS(Config = GASGameFramework)
class GASEXTENSION_API UGASExtensionSetting : public UObject
{
    GENERATED_BODY()

public:
    // 데미지 타입에 대한 면역 태그 매핑
    UPROPERTY(Config, EditAnywhere, Category = "Config")
    TMap<FDamageTypeTag, FImmunityTag> DamageImmunityMap;
};
