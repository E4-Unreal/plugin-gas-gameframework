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

        namespace Buff
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "GameplayCue.Buff", "버프 전용 이펙트")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "GameplayCue.Buff.Test", "테스트 전용 버프 이펙트")
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Default, "GameplayCue.Buff.Test", "기본 버프 이펙트")

            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Invinsible, "GameplayCue.Buff.Invinsible", "무적 버프 이펙트")

            namespace Attribute
            {
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Heal, "GameplayCue.Buff.Attribute.Heal", "힐 전용 이펙트")
            }

            namespace Stat
            {
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attack, "GameplayCue.Buff.Stat.Attack", "공격 버프 전용 이펙트")
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Defense, "GameplayCue.Buff.Stat.Defense", "방어 버프 전용 이펙트")
            }

            namespace Immunity
            {
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "GameplayCue.Buff.Immunity", "데미지 면역 버프 전용 이펙트")
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Test, "GameplayCue.Buff.Immunity.Test", "테스트 전용 데미지 면역 버프 이펙트")
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Physical, "GameplayCue.Buff.Immunity.Physical", "물리 데미지 면역 버프 이펙트")
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fire, "GameplayCue.Buff.Immunity.Fire", "불 데미지 면역 버프 이펙트")
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Water, "GameplayCue.Buff.Immunity.Water", "물 데미지 면역 버프 이펙트")
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Electricity, "GameplayCue.Buff.Immunity.Electricity", "전기 데미지 면역 버프 이펙트")
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ice, "GameplayCue.Buff.Immunity.Ice", "얼음 데미지 면역 버프 이펙트")
            }
        }
    }

    /* 데이터 */
    namespace Data
    {
        namespace Damage
        {
            namespace Type
            {
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Physical, "Data.Damage.Type.Physical", "물리 속성 데미지")
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fire, "Data.Damage.Type.Fire", "불 속성 데미지")
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Water, "Data.Damage.Type.Water", "물 속성 데미지")
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Electricity, "Data.Damage.Type.Electricity", "전기 속성 데미지")
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ice, "Data.Damage.Type.Ice", "얼음 속성 데미지")

                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Gravity, "Data.Damage.Type.Physical.Gravity", "중력 속성 데미지")
            }
        }
    }

    /* 상태 */
    namespace State
    {
        namespace Buff
        {
            namespace Immunity
            {
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Physical, "State.Buff.Immunity.Physical", "물리 속성 데미지 면역")
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Fire, "State.Buff.Immunity.Fire", "불 속성 데미지 면역")
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Water, "State.Buff.Immunity.Water", "물 속성 데미지 면역")
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Electricity, "State.Buff.Immunity.Electricity", "전기 속성 데미지 면역")
                UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ice, "State.Buff.Immunity.Ice", "얼음 속성 데미지 면역")
            }
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
