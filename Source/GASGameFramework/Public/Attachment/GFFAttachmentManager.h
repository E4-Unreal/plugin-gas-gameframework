// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "GFFAttachmentManager.generated.h"

class IGFFAttachmentSlotInterface;
class UGFFAttachmentDefinition;
// TODO EquipmentManager와 병합
/**
 * 총기 부품 장착 기능 구현을 위한 액터 컴포넌트 클래스입니다.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class GASGAMEFRAMEWORK_API UGFFAttachmentManager : public UActorComponent
{
    GENERATED_BODY()

    // Attachment를 부착할 대상 메시
    TWeakObjectPtr<UMeshComponent> TargetMesh;

protected:
    // 기본 부착물
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
    TArray<TObjectPtr<UGFFAttachmentDefinition>> DefaultAttachments;

    // 생성된 슬롯 (스태틱 메시 컴포넌트)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<FGameplayTag, TObjectPtr<UActorComponent>> Slots;

public:
    UGFFAttachmentManager();

    virtual void InitializeComponent() override;

    UFUNCTION(BlueprintCallable)
    void SetTargetMesh(UMeshComponent* InTargetMesh);

    void SetAttachment(UGFFAttachmentDefinition* Attachment);

private:
    void GetSlots();
};
