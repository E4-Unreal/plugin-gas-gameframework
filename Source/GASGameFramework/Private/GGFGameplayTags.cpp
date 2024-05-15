#include "GGFGameplayTags.h"

namespace GGFGameplayTags
{
    namespace State
    {
        /* 캐릭터 무브먼트 */
        UE_DEFINE_GAMEPLAY_TAG(Moving, "State.Move") // 움직이는 상태 (걷기, 달리기, 전속력 달리기)
        UE_DEFINE_GAMEPLAY_TAG(Running, "State.Move.Run") // 달리기
        UE_DEFINE_GAMEPLAY_TAG(Sprinting, "State.Move.Run.Sprint") // 전속력 달리기
        UE_DEFINE_GAMEPLAY_TAG(Falling, "State.Falling") // 점프 혹은 낙하
        UE_DEFINE_GAMEPLAY_TAG(Crouching, "State.Crouching") // 앉기

        /* 캐릭터 상태 */
        UE_DEFINE_GAMEPLAY_TAG(ADS, "State.ADS") // 조준
    }

    /* 입력 */
    namespace Input
    {
        UE_DEFINE_GAMEPLAY_TAG(Input, "Input") // 루트
        UE_DEFINE_GAMEPLAY_TAG(Fire, "Input.Fire") // 총기 발사
        UE_DEFINE_GAMEPLAY_TAG(ADS, "Input.ADS") // 총기 조준
        UE_DEFINE_GAMEPLAY_TAG(Reload, "Input.Reload") // 총기 재장전
        UE_DEFINE_GAMEPLAY_TAG(Interact, "Input.Interact") // 상호작용
    }
}
