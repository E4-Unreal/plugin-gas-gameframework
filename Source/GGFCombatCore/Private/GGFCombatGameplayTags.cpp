﻿#include "GGFCombatGameplayTags.h"

namespace GGFGameplayTags
{
    /* 데미지 */
    namespace Damage
    {
        namespace Type
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Physical, "Damage.Type.Physical", "물리 속성 데미지")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fire, "Damage.Type.Fire", "불 속성 데미지")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Water, "Damage.Type.Water", "물 속성 데미지")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Electricity, "Damage.Type.Electricity", "전기 속성 데미지")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ice, "Damage.Type.Ice", "얼음 속성 데미지")

            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Gravity, "Damage.Type.Physical.Gravity", "중력 속성 데미지")
        }
    }

    /* 버프 */
    namespace Buff
    {
        /* 면역 */
        namespace Immunity
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Physical, "Buff.Immunity.Physical", "물리 속성 데미지") // 물리
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fire, "Buff.Immunity.Fire", "불 속성 데미지") // 불
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Water, "Buff.Immunity.Water", "물 속성 데미지") // 물
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Electricity, "Buff.Immunity.Electricity", "전기 속성 데미지") // 전기
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ice, "Buff.Immunity.Ice", "얼음 속성 데미지") // 얼음
        }
    }

    /* 오브젝트 */
    namespace Object
    {
        namespace Type
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Physical, "Object.Type.Physical", "물리 속성 오브젝트")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fire, "Object.Type.Fire", "불 속성 오브젝트")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Water, "Object.Type.Water", "물 속성 오브젝트")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Electricity, "Object.Type.Electricity", "전기 속성 오브젝트")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ice, "Object.Type.Ice", "얼음 속성 오브젝트")
        }
    }
}
