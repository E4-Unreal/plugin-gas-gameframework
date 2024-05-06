#include "GEGameplayTags.h"

namespace GGFGameplayTags
{
    /* 캐릭터 상태 */
    namespace State
    {
        UE_DEFINE_GAMEPLAY_TAG(State, "State") // 루트
        UE_DEFINE_GAMEPLAY_TAG(Dead, "State.Dead") // 죽음
        UE_DEFINE_GAMEPLAY_TAG(Knockdown, "State.Knockdown") // 부활 전까지 행동 불가
        UE_DEFINE_GAMEPLAY_TAG(Stun, "State.Stun") // 일시적으로 행동 불가
    }

    /* 캐릭터 행동 */
    namespace Action
    {
        UE_DEFINE_GAMEPLAY_TAG(Action, "Action") // 루트
        UE_DEFINE_GAMEPLAY_TAG(Attack, "Action.Attack") // 공격
    }

    /* 플레이어 입력 */
    namespace Input
    {
        UE_DEFINE_GAMEPLAY_TAG(Input, "Input") // 루트
    }
}
