// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "GGFCoreSetting.generated.h"

/**
 *	Damage.Type 카테고리로 제한된 게임플레이 태그 래핑 구조체
 */
USTRUCT(Atomic, BlueprintType)
struct FGGFDamageTypeTag
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Damage.Type"))
    FGameplayTag Tag;

    /* 생성자 */

    FGGFDamageTypeTag() { }

    FGGFDamageTypeTag(FGameplayTag InTag)
    {
        Tag = InTag;
    }

    /* API */

    FORCEINLINE bool IsValid() const
    {
        return Tag.IsValid() && Tag.MatchesTag(Tag);
    }

    /* 연산자 */

    FORCEINLINE bool operator==(const FGGFDamageTypeTag& Other) const
    {
        return Equals(Other);
    }

    FORCEINLINE bool operator!=(const FGGFDamageTypeTag& Other) const
    {
        return !(*this == Other);
    }

    FORCEINLINE bool Equals(const FGGFDamageTypeTag& Other) const
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

    friend FORCEINLINE uint32 GetTypeHash(const FGGFDamageTypeTag& DamageTypeTag)
    {
        return GetTypeHash(DamageTypeTag.Tag);
    }

    FORCEINLINE FGGFDamageTypeTag& operator=(const FGameplayTag& Other)
    {
        Tag = Other;
        return *this;
    }
};

/**
 *	Buff.Immunity 카테고리로 제한된 게임플레이 태그 래핑 구조체
 */
USTRUCT(Atomic, BlueprintType)
struct FGGFImmunityTag
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Buff.Immunity"))
    FGameplayTag Tag;

    /* 생성자 */

    FGGFImmunityTag() { }

    FORCEINLINE FGGFImmunityTag(FGameplayTag InTag)
    {
        Tag = InTag;
    }

    /* API */

    FORCEINLINE bool IsValid() const
    {
        return Tag.IsValid() && Tag.MatchesTag(Tag);
    }

    /* 연산자 */

    FORCEINLINE bool operator==(const FGGFImmunityTag& Other) const
    {
        return Equals(Other);
    }

    FORCEINLINE bool operator!=(const FGGFImmunityTag& Other) const
    {
        return !(*this == Other);
    }

    FORCEINLINE bool Equals(const FGGFImmunityTag& Other) const
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

    friend FORCEINLINE uint32 GetTypeHash(const FGGFImmunityTag& ImmunityTag)
    {
        return GetTypeHash(ImmunityTag.Tag);
    }

    FORCEINLINE FGGFImmunityTag& operator=(const FGameplayTag& Other)
    {
        Tag = Other;
        return *this;
    }
};

/**
 * GASExtension 모듈 전용 프로젝트 설정
 */
UCLASS(Config = GASGameFramework)
class GGFCORE_API UGGFCoreSetting : public UObject
{
    GENERATED_BODY()

public:
    // 데미지 타입에 대한 면역 태그 매핑
    UPROPERTY(Config, EditAnywhere, Category = "Config")
    TMap<FGGFDamageTypeTag, FGGFImmunityTag> DamageImmunityMap;
};
