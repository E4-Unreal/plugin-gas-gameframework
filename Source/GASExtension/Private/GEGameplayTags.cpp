#include "GEGameplayTags.h"

namespace GEGameplayTags
{
    /* 상태 */
    namespace State
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "State", "상태")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Dead, "State.Dead", "죽음")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Knockdown, "State.Knockdown", "부활 전까지 행동 불가")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Stun, "State.Stun", "일시적으로 행동 불가")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Invinsible, "State.Invinsible", "데미지가 들어가지 않는 무적 상태")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Reviving, "State.Reviving", "부활중")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ready, "State.Ready", "준비중인 상태로 조작이 불가능합니다.")
    }

    /* 행동 */
    namespace Action
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Action", "특정 행동") // 루트
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attack, "Action.Attack", "공격") // 공격
    }

    /* 플레이어 입력 */
    namespace Input
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Input", "플레이어 입력") // 루트
    }

    /* 이벤트 */
    namespace Event
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Event", "게임플레이 이벤트 전용") // 루트
    }
}
