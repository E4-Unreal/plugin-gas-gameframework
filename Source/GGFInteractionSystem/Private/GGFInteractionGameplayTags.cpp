#include "GGFInteractionGameplayTags.h"

namespace GGFGameplayTags
{
    /* 상태 */
    namespace State
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Interactable, "State.Interactable", "상호작용 가능한 물체가 주변에 있는 상태") // 상호작용 가능한 상태
    }

    /* 입력 */
    namespace Input
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Interact, "Input.Interact", "상호작용 전용 입력 태그") // 상호작용
    }
}
