// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GGFCharacterMeshInterface.generated.h"

UINTERFACE(BlueprintType, Blueprintable)
class GGFCORE_API UGGFCharacterMeshInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * 캐릭터 메시 전용 인터페이스
 */
class GGFCORE_API IGGFCharacterMeshInterface
{
    GENERATED_BODY()

public:
    // 삼인칭 캐릭터 메시 (주로 애니메이션)
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    USkeletalMeshComponent* GetThirdPersonMesh() const;

    // 일인칭 캐릭터 메시 (주로 애니메이션)
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    USkeletalMeshComponent* GetFirstPersonMesh() const;

    // 삼인칭 캐릭터 메시 (주로 소켓 부착)
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    USkeletalMeshComponent* GetThirdPersonRetargetMesh() const;
    virtual USkeletalMeshComponent* GetThirdPersonRetargetMesh_Implementation() const
    {
        return Execute_GetThirdPersonMesh(Cast<UObject>(this));
    }

    // 일인칭 캐릭터 메시 (주로 소켓 부착)
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    USkeletalMeshComponent* GetFirstPersonRetargetMesh() const;
    virtual USkeletalMeshComponent* GetFirstPersonRetargetMesh_Implementation() const
    {
        return Execute_GetFirstPersonMesh(Cast<UObject>(this));
    }
};
