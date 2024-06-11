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

        namespace Launch
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "GameplayCue.Launch", "점프대 전용 게임플레이 큐")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Default, "GameplayCue.Launch.Default", "기본 점프대 게임플레이 큐")
        }

        namespace Button
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "GameplayCue.Button", "버튼 전용 게임플레이 큐")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Default, "GameplayCue.Button.Default", "기본 버튼 게임플레이 큐")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Activate, "GameplayCue.Button.Activate", "버튼 활성화 게임플레이 큐")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Deactivate, "GameplayCue.Button.Deactivate", "버튼 비활서와 게임플레이 큐")
        }
    }
}
