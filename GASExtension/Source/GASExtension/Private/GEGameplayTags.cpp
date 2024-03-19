#include "GEGameplayTags.h"

namespace GEGameplayTags
{
    namespace State
    {
        /* 캐릭터 무브먼트 */
        UE_DEFINE_GAMEPLAY_TAG(CrouchingTag, "State.Crouching") // 앉기
        UE_DEFINE_GAMEPLAY_TAG(FallingTag, "State.Falling") // 점프 혹은 낙하

        /* 캐릭터 상태 */
        UE_DEFINE_GAMEPLAY_TAG(DeadTag, "State.Dead") // 죽음
        UE_DEFINE_GAMEPLAY_TAG(KnockdownTag, "State.Knockdown") // 기절 (배그)
        UE_DEFINE_GAMEPLAY_TAG(StunTag, "State.Stun") // CC
    }
}
