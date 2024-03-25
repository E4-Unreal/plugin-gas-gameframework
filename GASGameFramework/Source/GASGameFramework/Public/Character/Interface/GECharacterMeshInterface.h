// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GECharacterMeshInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class GASGAMEFRAMEWORK_API UGECharacterMeshInterface : public UInterface
{
    GENERATED_BODY()
};

class USkeletalMeshComponent;

/**
 * 1인칭, 3인칭 캐릭터를 동시에 조작하는 경우에는 장비 부착 혹은 애니메이션 재생 등을 위해 여러 스켈레탈 메시를 사용합니다.
 * 캐릭터 클래스의 GetMesh만으로는 한계가 있기 때문에 필요에 따라 적절한 스켈레탈 메시를 가져다 쓸 수 있도록 도와주는 인터페이스입니다.
 */
class GASGAMEFRAMEWORK_API IGECharacterMeshInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    USkeletalMeshComponent* GetFirstPersonArmsMesh() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    USkeletalMeshComponent* GetFirstPersonLegsMesh() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    USkeletalMeshComponent* GetThirdPersonFullBodyMesh() const;
};
