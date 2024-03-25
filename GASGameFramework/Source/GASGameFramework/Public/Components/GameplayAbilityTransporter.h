// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayAbilityTransporter.generated.h"

class UGameplayAbility;
/*
 * 대상 액터에게 GameplayAbility를 부여할 수 있도록 도와주는 간단한 액터 컴포넌트입니다.
 * 무기를 장착하거나 아이템을 사용하였을 때 GameplayAbility를 부여하는 경우 사용할 수 있습니다.
 */
UCLASS(ClassGroup=(GASExtesion), meta=(BlueprintSpawnableComponent))
class GASGAMEFRAMEWORK_API UGameplayAbilityTransporter : public UActorComponent
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Config", meta = (AllowPrivateAccess = true))
    TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGive;

public:
    UFUNCTION(BlueprintCallable, Category = "GameplayAbilityTransporter")
    void GiveAbilitiesToTarget(AActor* Target);
};
