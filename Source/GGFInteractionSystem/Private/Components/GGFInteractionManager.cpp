// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFInteractionManager.h"
#include "Logging.h"
#include "Components/GGFInteractableComponent.h"

void UGGFInteractionManager::Interact()
{
    if(CanInteract())
    {
        InteractableComponent->TryInteract(GetOwner());
    }
    else
    {
#if WITH_EDITOR
        LOG_ACTOR_COMPONENT_DETAIL(Warning, TEXT("상호작용이 불가능한 상태입니다."))
#endif
    }
}

bool UGGFInteractionManager::CanInteract() const
{
    return InteractableComponent && InteractableComponent->CanInteract(GetOwner());
}

void UGGFInteractionManager::SetInteractableActor(AActor* NewInteractableActor, bool bTraceResult)
{
    // 유효성 검사
    if(NewInteractableActor == nullptr) return;

    if(!bTraceResult)
    {
        // 중복호출 방지
        if(InteractableActor == nullptr || InteractableActor != NewInteractableActor) return;

        // InteractableActor 리셋
        InteractableActor = nullptr;
        InteractableComponent = nullptr;

#if WITH_EDITOR
        LOG_ACTOR_COMPONENT_DETAIL(Log, TEXT("Reset"))
#endif
    }
    else
    {
        // 중복호출 방지
        if(InteractableActor && InteractableActor == NewInteractableActor) return;

        // InteractableActor 설정
        InteractableActor = NewInteractableActor;
        InteractableComponent = InteractableActor->GetComponentByClass<UGGFInteractableComponent>();

#if WITH_EDITOR
        LOG_ACTOR_COMPONENT_DETAIL(Log, TEXT("%s"), *InteractableActor->GetName())
#endif
    }
}
