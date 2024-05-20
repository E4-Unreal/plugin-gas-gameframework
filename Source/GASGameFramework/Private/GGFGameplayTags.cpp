#include "GGFGameplayTags.h"

namespace GGFGameplayTags
{
    /* 상태 */
    namespace State
    {
        UE_DEFINE_GAMEPLAY_TAG(Root, "State") // 루트
        UE_DEFINE_GAMEPLAY_TAG(Moving, "State.Move") // 움직이는 상태 (걷기, 달리기, 전속력 달리기)
        UE_DEFINE_GAMEPLAY_TAG(Running, "State.Move.Run") // 달리기
        UE_DEFINE_GAMEPLAY_TAG(Sprinting, "State.Move.Run.Sprint") // 전속력 달리기
        UE_DEFINE_GAMEPLAY_TAG(Falling, "State.Falling") // 점프 혹은 낙하
        UE_DEFINE_GAMEPLAY_TAG(Crouching, "State.Crouching") // 앉기
    }
}
