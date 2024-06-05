#include "GEGameplayTags.h"

namespace GEGameplayTags
{
    /* 게임플레이 큐 */
    namespace GameplayCue
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "GameplayCue", "게임플레이 큐")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "GameplayCue.Test", "테스트 전용 게임플레이 큐")
    }

    /* 상태 */
    namespace State
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "State", "상태")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "State.Test", "테스트 전용 상태")

        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Dead, "State.Dead", "죽음")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Knockdown, "State.Knockdown", "부활 전까지 행동 불가")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Stun, "State.Stun", "일시적으로 행동 불가")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Invinsible, "State.Invinsible", "데미지가 들어가지 않는 무적 상태")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Reviving, "State.Reviving", "부활중")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Wait, "State.Wait", "조작이 불가능한 상태")
    }

    /* 행동 */
    namespace Action
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Action", "행동")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "Action.Test", "테스트 전용 행동")

        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attack, "Action.Attack", "공격")
    }

    /* 플레이어 입력 */
    namespace Input
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Input", "플레이어 입력")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "Input.Test", "테스트 전용 플레이어 입력")
    }

    /* 이벤트 */
    namespace Event
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Event", "게임플레이 이벤트")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "Event.Test", "테스트 전용 게임플레이 이벤트")
    }

    /* 데미지 */
    namespace Damage
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Damage", "데미지")

        namespace Type
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Damage.Type", "데미지 타입")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Default, "Damage.Type.Default", "기본 데미지 타입")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "Damage.Type.Test", "테스트 전용 데미지 타입")
        }
    }

    /* 버프 */
    namespace Buff
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Buff", "버프")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "Buff.Test", "테스트 전용 버프")

        /* 면역 */
        namespace Immunity
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Buff.Immunity", "특정 데미지 타입에 대한 면역")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "Buff.Immunity.Test", "테스트 전용 면역")
        }
    }

    /* 디버프 */
    namespace Debuff
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Debuff", "디버프")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "Debuff.Test", "테스트 전용 디버프")
    }

    /* 오브젝트 */
    namespace Object
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Object", "오브젝트")

        namespace Type
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Object.Type", "오브젝트 타입")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "Object.Type.Test", "테스트 전용 오브젝트 타입")
        }
    }
}
