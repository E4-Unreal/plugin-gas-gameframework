﻿#include "GGFCombatGameplayTags.h"

namespace GGFGameplayTags
{
    /* 게임플레이 큐 */
    namespace GameplayCue
    {
        namespace Hit
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "GameplayCue.Hit", "피격 이펙트")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "GameplayCue.Hit.Test", "테스트 전용 피격 이펙트")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Default, "GameplayCue.Hit.Default", "기본 피격 이펙트")
        }

        namespace Explosion
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "GameplayCue.Explosion", "폭발 이펙트")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "GameplayCue.Explosion.Test", "테스트 전용 폭발 이펙트")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Default, "GameplayCue.Explosion.Default", "기본 폭발 이펙트")
        }

        namespace Bounce
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "GameplayCue.Bounce", "바운스 이펙트")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "GameplayCue.Bounce.Test", "테스트 전용 바운스 이펙트")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Default, "GameplayCue.Bounce.Default", "기본 바운스 이펙트")
        }
    }

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
