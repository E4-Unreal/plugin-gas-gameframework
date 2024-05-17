#include "GGFShooterGameplayTags.h"

namespace GGFGameplayTags
{
    /* 상태 */
    namespace State
    {
        UE_DEFINE_GAMEPLAY_TAG(ADS, "State.ADS") // 조준
    }

    /* 입력 */
    namespace Input
    {
        UE_DEFINE_GAMEPLAY_TAG(Fire, "Input.Fire") // 총기 발사
        UE_DEFINE_GAMEPLAY_TAG(ADS, "Input.ADS") // 총기 조준
        UE_DEFINE_GAMEPLAY_TAG(Reload, "Input.Reload") // 총기 재장전
    }
}
