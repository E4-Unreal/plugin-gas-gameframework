// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFThirdPersonCharacter.h"
#include "GGFThirdPersonCharacter_Retarget.generated.h"

/**
 * 애니메이션 전용 스켈레탈 메시와 리타깃 전용 스켈레탈 메시가 존재하는 삼인칭 캐릭터 클래스입니다.
 * 샘플로 파라곤 에셋을 사용합니다.
 */
UCLASS()
class GGFCHARACTERSYSTEM_API AGGFThirdPersonCharacter_Retarget : public AGGFThirdPersonCharacter
{
    GENERATED_BODY()

public:
    /* 서브 오브젝트 이름 */

    static FName RetargetMeshName;

private:
    /* 컴포넌트 */

    // 리타깃 전용 스켈레탈 메시
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetRetargetMesh, Category = "Component")
    TObjectPtr<USkeletalMeshComponent> RetargetMesh;

public:
    AGGFThirdPersonCharacter_Retarget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Actor */

    virtual void PostInitializeComponents() override;

protected:
    virtual void HideBones() override;

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USkeletalMeshComponent* GetRetargetMesh() const { return RetargetMesh; }
};
