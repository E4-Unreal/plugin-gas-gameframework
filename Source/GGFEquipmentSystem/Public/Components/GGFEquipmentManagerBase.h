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

    /* 레퍼런스 */

    // Owner의 스켈레탈 메시로 무기를 부착할 소켓을 찾는데 사용됩니다.
    TWeakObjectPtr<USkeletalMeshComponent> TargetMesh;

#if WITH_EDITORONLY_DATA
    UPROPERTY(VisibleAnywhere, Category = "State")
    bool bValid;
#endif

public:
    UGGFEquipmentManagerBase();

    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* API */

    UFUNCTION(BlueprintCallable)
    void SetTargetMesh(USkeletalMeshComponent* NewTargetMesh);

protected:
    /* 메서드 */

    virtual void OnTargetMeshChanged();

    // Owner 위치에 액터를 스폰한 뒤 반환합니다.
    UFUNCTION(BlueprintCallable)
    AActor* SpawnEquipment(TSubclassOf<AActor> EquipmentClass);

    // 스켈레탈 메시 소켓에 액터를 부착합니다.
    UFUNCTION(BlueprintCallable)
    virtual bool AttachEquipment(AActor* Equipment, FName SocketName);

    UFUNCTION(BlueprintCallable)
    static const FGameplayTag GetEquipmentSlot(TSubclassOf<AActor> EquipmentClass);

protected:
    /* Getter */

    UFUNCTION(BlueprintPure)
    FORCEINLINE USkeletalMeshComponent* GetTargetMesh() const { return TargetMesh.Get(); }
};
