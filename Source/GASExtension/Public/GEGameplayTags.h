#pragma once

#include "NativeGameplayTags.h"

namespace GEGameplayTags
{
    /* 캐릭터 상태 */
    namespace State
    {
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State) // 루트
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Dead) // 죽음
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Knockdown) // 부활 전까지 행동 불가
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stun) // 일시적으로 행동 불가
    }

    /* 캐릭터 행동 */
    namespace Action
    {
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action) // 루트
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attack) // 공격
    }

    /* 플레이어 입력 */
    namespace Input
    {
        GASEXTENSION_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input) // 루트
    }
}
