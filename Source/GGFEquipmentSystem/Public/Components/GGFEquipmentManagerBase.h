// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GGFEquipmentManagerBase.generated.h"

struct FGameplayTag;

UCLASS(Abstract, NotBlueprintable)
class GGFEQUIPMENTSYSTEM_API UGGFEquipmentManagerBase : public UActorComponent
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dependency", meta = (AllowPrivateAccess = true))
    TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true))
    bool bInitialized;

protected:
    /* 메서드 */
    // Owner 위치에 액터를 스폰한 뒤 반환합니다.
    UFUNCTION(BlueprintCallable)
    AActor* SpawnEquipment(TSubclassOf<AActor> EquipmentClass);

    // 스켈레탈 메시 소켓에 액터를 부착합니다.
    UFUNCTION(BlueprintCallable)
    virtual bool AttachEquipment(AActor* Equipment, FName SocketName);

    UFUNCTION(BlueprintCallable)
    static const FGameplayTag GetEquipmentSlot(TSubclassOf<AActor> EquipmentClass);

    /* Getter */
    FORCEINLINE USkeletalMeshComponent* GetMesh() const { return SkeletalMesh; }

public:
    UGGFEquipmentManagerBase();

    UFUNCTION(BlueprintCallable)
    void InjectDependencies(USkeletalMeshComponent* InSkeletalMesh);
};
