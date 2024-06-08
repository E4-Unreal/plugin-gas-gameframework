#include "GGFGimmickGameplayTags.h"

namespace GGFGameplayTags
{
    /* 게임플레이 큐 */
    namespace GameplayCue
    {
        namespace Teleport
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "GameplayCue.Teleport", "순간이동 게임플레이 큐")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Default, "GameplayCue.Teleport.Default", "순간이동 게임플레이 큐")

            namespace In
            {
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "GameplayCue.Teleport.In", "순간이동 입장 게임플레이 큐")
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Default, "GameplayCue.Teleport.In.Default", "기본 순간이동 입장 효과")
            }

            namespace Out
            {
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "GameplayCue.Teleport.Out", "순간이동 퇴장 게임플레이 큐")
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Default, "GameplayCue.Teleport.Out.Default", "기본 순간이동 퇴장 효과")
            }
        }
    }
}
