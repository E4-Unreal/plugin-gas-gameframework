#include "GGFCharacterGameplayTags.h"

namespace GGFGameplayTags
{
    /* 상태 */
    namespace State
    {
        UE_DEFINE_GAMEPLAY_TAG(Moving, "State.Move") // 움직이는 상태 (걷기, 달리기, 전속력 달리기)
        UE_DEFINE_GAMEPLAY_TAG(Running, "State.Move.Run") // 달리기
        UE_DEFINE_GAMEPLAY_TAG(Sprinting, "State.Move.Sprinting") // 빠르게 달리기
        UE_DEFINE_GAMEPLAY_TAG(Falling, "State.Falling") // 점프 혹은 낙하
        UE_DEFINE_GAMEPLAY_TAG(Crouching, "State.Crouching") // 앉기
    }

    /* 플레이어 입력 */
    namespace Input
    {
        UE_DEFINE_GAMEPLAY_TAG(Sprint, "Input.Sprint") // 빠르게 달리기
    }
}
