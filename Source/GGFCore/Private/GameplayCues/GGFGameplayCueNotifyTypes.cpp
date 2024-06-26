// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayCues/GGFGameplayCueNotifyTypes.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

#include "GameplayCues/GGFGameplayCueNotify_Burst.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GGFGameplayCueNotifyTypes)

#define LOCTEXT_NAMESPACE "GameplayCueNotify"

static EAttachLocation::Type GetAttachLocationTypeFromRule(EAttachmentRule AttachmentRule)
{
    switch (AttachmentRule)
    {
    case EAttachmentRule::KeepRelative:
        return EAttachLocation::KeepRelativeOffset;

    case EAttachmentRule::KeepWorld:
        return EAttachLocation::KeepWorldPosition;

    case EAttachmentRule::SnapToTarget:
        return EAttachLocation::SnapToTarget;

    default:
        checkf(false, TEXT("GameplayCueNotify: Invalid attachment rule [%d]\n"), (uint8)AttachmentRule);
    }

    return EAttachLocation::KeepWorldPosition;
}

bool FGGFGameplayCueNotify_CascadeInfo::PlayParticleEffect(AActor* Target, const FGameplayCueParameters& Parameters) const
{
    // 유효성 검사
    if(ParticleSystem == nullptr) return false;

    // 지역 변수 선언
    UFXSystemComponent* SpawnedFXSC;
    USceneComponent* TargetComponent;
    FVector SpawnLocation;
    FRotator SpawnRotation;
    FVector SpawnScale = Scale;
    const bool bAutoDestroy = false;
    const bool bAutoActivate = true;

    // HitResult 우선 취급
    const FHitResult* HitResultPtr = Parameters.EffectContext.GetHitResult();
    if(HitResultPtr && HitResultPtr->bBlockingHit)
    {
        SpawnLocation = HitResultPtr->ImpactPoint;
        SpawnRotation = HitResultPtr->ImpactNormal.ToOrientationRotator();
        TargetComponent = HitResultPtr->GetComponent();
    }
    else // Parameters
    {
        SpawnLocation = Parameters.Location;
        SpawnRotation = Parameters.Normal.ToOrientationRotator();
        TargetComponent = Parameters.TargetAttachComponent.IsValid() ? Parameters.TargetAttachComponent.Get() : Target ? Target->GetDefaultAttachComponent() : nullptr;
    }

    // 옵션 확인
    if(bIgnoreRotation) SpawnRotation = FRotator::ZeroRotator;

    // Attach
    if (bAttach && TargetComponent)
    {
        const EAttachLocation::Type AttachLocationType = GetAttachLocationTypeFromRule(EAttachmentRule::KeepWorld);

        SpawnedFXSC = UGameplayStatics::SpawnEmitterAttached(ParticleSystem, TargetComponent, AttachSocketName,
            SpawnLocation, SpawnRotation, SpawnScale, AttachLocationType, bAutoDestroy, EPSCPoolMethod::AutoRelease, bAutoActivate);
    }
    else // Location
    {
        SpawnedFXSC = UGameplayStatics::SpawnEmitterAtLocation(Target, ParticleSystem,
            SpawnLocation, SpawnRotation, SpawnScale, bAutoDestroy, EPSCPoolMethod::AutoRelease, bAutoActivate);
    }

    if (ensure(SpawnedFXSC))
    {
        SpawnedFXSC->SetCastShadow(bCastShadow);
    }

    return (SpawnedFXSC != nullptr);
}

void FGGFGameplayCueNotify_CascadeInfo::ValidateBurstAssets(const UObject* ContainingAsset, const FString& Context,
    FDataValidationContext& ValidationContext) const
{
#if WITH_EDITORONLY_DATA
    if (ParticleSystem != nullptr)
    {
        if (ParticleSystem->IsLooping())
        {
            ValidationContext.AddError(FText::Format(
                LOCTEXT("ParticleSystem_ShouldNotLoop", "Particle system [{0}] used in slot [{1}] for asset [{2}] is set to looping, but the slot is a one-shot (the instance will leak)."),
                FText::AsCultureInvariant(ParticleSystem->GetPathName()),
                FText::AsCultureInvariant(Context),
                FText::AsCultureInvariant(ContainingAsset->GetPathName())));
        }
    }
#endif // #if WITH_EDITORONLY_DATA
}

#undef LOCTEXT_NAMESPACE
