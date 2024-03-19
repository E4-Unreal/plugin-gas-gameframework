#pragma once

#include "NativeGameplayTags.h"

namespace GEGameplayTags
{
    namespace State
    {
        /* 루트 태그 */
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(StateTag)

        /* 캐릭터 무브먼트 */
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(CrouchingTag) // 앉기
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(FallingTag) // 점프 혹은 낙하

        /* 캐릭터 상태 */
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(DeadTag) // 죽음
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(KnockdownTag) // 기절 (배그)
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(StunTag) // CC
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(ADSTag) // 조준
    }

    namespace Input
    {
        /* 루트 태그 */
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag)
    }

    namespace Action
    {
        /* 루트 태그 */
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(ActionTag)

        /* 행동 */
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttackTag) // 공격
    }

    namespace Equipment
    {
        /* 루트 태그 */
        // 장비
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(EquipmentTag)
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(WeaponTag)
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(ArmorTag)

        // 슬롯
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(SlotTag)
    }
}
