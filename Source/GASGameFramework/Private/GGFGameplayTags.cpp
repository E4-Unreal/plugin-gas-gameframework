#include "GGFGameplayTags.h"

namespace GGFGameplayTags
{
    /* 플레이어 입력 */
    namespace Input
    {
        namespace Ability
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Input.Ability", "스킬 전용 입력 태그")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "Input.Ability.Test", "테스트 전용 스킬 입력 태그")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Q, "Input.Ability.Q", "Q 스킬 입력 태그")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(E, "Input.Ability.E", "E 스킬 입력 태그")
        }
    }
}
