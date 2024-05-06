#pragma once

#include "NativeGameplayTags.h"
#include "GEGameplayTags.h"

namespace GGFGameplayTags
{
    namespace State
    {
        /* 캐릭터 무브먼트 */
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Moving) // 움직이는 상태 (걷기, 달리기, 전속력 달리기)
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Running) // 달리기
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sprinting) // 전속력 달리기
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Falling) // 점프 혹은 낙하
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crouching) // 앉기

        /* 캐릭터 상태 */
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(ADS) // 조준
    }

    namespace Equipment
    {
        /* 루트 태그 */
        // 장비
        GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Equipment)

        // 무기
        namespace Weapon
        {
            GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon)

            // 화기
            namespace FireArm
            {
                GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(FireArm)

                // 화기 부착물
                namespace Attachment
                {
                    GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attachment)

                    GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Muzzle) // 총구
                    GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(IronSight) // 가늠쇠
                    GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Scope) // 조준경
                    GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Magazine) // 탄알집
                    GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Grip) // 손잡이
                    GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Laser) // 레이저
                }
            }
        }

        // 방어구
        namespace Armor
        {
            GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Armor)
        }

        // 장신구
        namespace Accessory
        {
            GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Accessory)
        }

        // 장비 슬롯
        namespace Slot
        {
            GASGAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Slot)
        }
    }
}
