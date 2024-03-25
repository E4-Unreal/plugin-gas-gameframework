// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GEGameplayAbility.h"
#include "Interface/GEWeaponAbilityInterface.h"
#include "GEWeaponAbility.generated.h"

/**
 * 무기 전용 어빌리티
 */
UCLASS()
class GASEXTENSION_API UGEWeaponAbility : public UGEGameplayAbility, public IGEWeaponAbilityInterface
{
    GENERATED_BODY()

    UPROPERTY(ReplicatedUsing = OnRep_Weapon)
    TWeakObjectPtr<AActor> Weapon;

public:
    UGEWeaponAbility();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    /* 리플리케이트 */
    // 필요한 무기 클래스로 캐스팅 진행
    UFUNCTION()
    virtual void OnRep_Weapon() { }

public:
    /* Getter */
    UFUNCTION(BlueprintCallable)
    FORCEINLINE AActor* GetWeapon() const { return Weapon.Get(); }

public:
    /* GEWeaponAbilityInterface 인터페이스 */
    void SetWeapon_Implementation(AActor* InWeapon);
};
