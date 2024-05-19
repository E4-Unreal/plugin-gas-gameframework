#include "GEGameplayTags.h"

namespace GEGameplayTags
{
    /* 상태 */
    namespace State
    {
        UE_DEFINE_GAMEPLAY_TAG(Root, "State") // 루트
        UE_DEFINE_GAMEPLAY_TAG(Dead, "State.Dead") // 죽음
        UE_DEFINE_GAMEPLAY_TAG(Knockdown, "State.Knockdown") // 부활 전까지 행동 불가
        UE_DEFINE_GAMEPLAY_TAG(Stun, "State.Stun") // 일시적으로 행동 불가
    }

    /* 행동 */
    namespace Action
    {
        UE_DEFINE_GAMEPLAY_TAG(Root, "Action") // 루트
        UE_DEFINE_GAMEPLAY_TAG(Attack, "Action.Attack") // 공격
    }

    /* 플레이어 입력 */
    namespace Input
    {
        UE_DEFINE_GAMEPLAY_TAG(Root, "Input") // 루트
    }

    /* 이벤트 */
    namespace Event
    {
        UE_DEFINE_GAMEPLAY_TAG(Root, "Event") // 루트
    }
}
