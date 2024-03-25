// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GGFGA_Montage.h"

#include "Animation/AnimInstance.h"
#include "Character/Interface/GGFCharacterMeshInterface.h"

void UGGFGA_Montage::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    // 커밋
    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        return;
    }

    // 인터페이스 구현 여부 검사
    if(!ActorInfo->AvatarActor->GetClass()->ImplementsInterface(UGGFCharacterMeshInterface::StaticClass())) return;

    // 지역 변수 선언
    USkeletalMeshComponent* Mesh;

    // 1인칭 애니메이션 재생
    Mesh = IGGFCharacterMeshInterface::Execute_GetFirstPersonArmsMesh(ActorInfo->AvatarActor.Get());
    PlayMontage(Mesh, FirstPersonMontage);

    // 3인칭 애니메이션 재생
    Mesh = IGGFCharacterMeshInterface::Execute_GetThirdPersonFullBodyMesh(ActorInfo->AvatarActor.Get());
    PlayMontage(Mesh, ThirdPersonMontage);

    /*
     * FirstPersonLegsMesh는 일반적으로 애니메이션 블루프린트에서 CopyPose를 3인칭 메시의 움직임을 이용합니다.
     * 만약 별도의 애니메이션을 사용할 경우에는 오버라이드 하여 사용하셔야 합니다.
     */
}

void UGGFGA_Montage::PlayMontage(USkeletalMeshComponent* Mesh, const FGGFMontageConfig& MontageConfig)
{
    // null 검사
    if(Mesh == nullptr) return;

    // 애님 인스턴스 가져오기
    UAnimInstance* AnimInstance = Mesh->GetAnimInstance();

    // 유효성 검사
    if(MontageConfig.MontageToPlay == nullptr || AnimInstance == nullptr) return;

    // 몽타주 재생
    float const Duration = AnimInstance->Montage_Play(MontageConfig.MontageToPlay, MontageConfig.PlayRate);

    // 몽타주 섹션 점프
    if (!MontageConfig.SectionName.IsNone())
    {
        AnimInstance->Montage_JumpToSection(MontageConfig.SectionName);
    }
}
