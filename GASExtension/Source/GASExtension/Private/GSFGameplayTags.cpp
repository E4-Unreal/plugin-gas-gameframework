#include "GEGameplayTags.h"

namespace GEGameplayTags
{
    namespace State
    {
        /* 캐릭터 무브먼트 */
        UE_DEFINE_GAMEPLAY_TAG(CrouchingTag, "State.Crouching") // 앉기
        UE_DEFINE_GAMEPLAY_TAG(FallingTag, "State.Falling") // 점프 혹은 낙하
    }
}
