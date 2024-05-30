#include "GGFCharacterGameplayTags.h"

namespace GGFGameplayTags
{
    /* 상태 */
    namespace State
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Moving, "State.Moving", "땅 위에서 움직이고 있는 상태")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Running, "State.Moving.Running", "달리고 있는 상태")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Sprinting, "State.Moving.Sprinting", "빠르게 달리고 있는 상태")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Falling, "State.Falling", "체공 상태")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Crouching, "State.Crouching", "앉아 있는 상태")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Proning, "State.Proning", "누워 있는 상태")
    }

    /* 플레이어 입력 */
    namespace Input
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Sprint, "Input.Sprint", "빠르게 달리기 전용 입력 태그")
    }
}
