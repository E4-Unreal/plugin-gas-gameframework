#include "GGFSkillGameplayTags.h"

namespace GGFGameplayTags
{
    /* 플레이어 입력 */
    namespace Input
    {
        namespace Skill
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Input.Skill", "스킬 전용 입력 태그")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "Input.Skill.Test", "테스트 전용 스킬 입력 태그")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Q, "Input.Skill.Q", "Q 스킬 입력 태그")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(E, "Input.Skill.E", "E 스킬 입력 태그")
        }
    }
}
