#pragma once

#include "NativeGameplayTags.h"

namespace GGFGameplayTags
{
    namespace State
    {
        /* 루트 태그 */
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State)

        /* 캐릭터 무브먼트 */
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Moving) // 움직이는 상태 (걷기, 달리기, 전속력 달리기)
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Running) // 달리기
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sprinting) // 전속력 달리기
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Falling) // 점프 혹은 낙하
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crouching) // 앉기

        /* 캐릭터 상태 */
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Dead) // 죽음
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Knockdown) // 기절 (배그)
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stun) // CC
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(ADS) // 조준
    }

    namespace Input
    {
        /* 루트 태그 */
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input)
    }

    namespace Action
    {
        /* 루트 태그 */
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action)

        /* 행동 */
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attack) // 공격
    }

    namespace Equipment
    {
        /* 루트 태그 */
        // 장비
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Equipment)
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon)
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Armor)

        namespace Slot
        {
            GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Slot)
        }
    }
}
