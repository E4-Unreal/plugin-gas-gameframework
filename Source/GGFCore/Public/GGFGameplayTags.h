#pragma once

#include "NativeGameplayTags.h"

namespace GGFGameplayTags
{
    namespace Data
    {
        namespace Damage
        {
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(True)
        }

        namespace Attribute
        {
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Health)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mana)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shield)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stamina)
        }

        namespace MaxAttribute
        {
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Health)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mana)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shield)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stamina)
        }

        namespace AttributeRegenRate
        {
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Health)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mana)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shield)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stamina)
        }

        namespace Stat
        {
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attack)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Defense)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(MoveSpeed)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttackSpeed)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AbilityHaste)
        }

        namespace MaxStat
        {
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attack)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Defense)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(MoveSpeed)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttackSpeed)
            GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AbilityHaste)
        }
    }

    namespace State
    {
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)

        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Knockdown)
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Dead)
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Respawn)
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Reviving)

        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Snare)
        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stun)

        GGFCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Invinsible)
    }
}

using namespace GGFGameplayTags;
