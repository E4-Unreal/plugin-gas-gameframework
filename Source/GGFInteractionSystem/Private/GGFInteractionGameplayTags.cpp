#include "GGFInteractionGameplayTags.h"

namespace GGFGameplayTags
{
    /* 상태 */
    namespace State
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Interactable, "State.Interactable", "상호작용 가능한 상태")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Interacting, "State.Interacting", "상호작용 중인 상태")
    }

    /* 입력 */
    namespace Input
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Interact, "Input.Interact", "상호작용 전용 입력 태그")
    }
}
