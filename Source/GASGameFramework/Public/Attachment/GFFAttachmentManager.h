// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "GFFAttachmentManager.generated.h"

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
    // 사용할 스태틱 메시 컴포넌트 클래스
    // 콜리전 설정 등 프로젝트에 따라 추가 설정한 C++ 혹은 블루프린트 클래스 사용 권장
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
    TSubclassOf<UStaticMeshComponent> StaticMeshComponentClass;

    // 기본 부착물
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
    TArray<TObjectPtr<UGFFAttachmentDefinition>> DefaultAttachments;

    // <슬롯 태그, 소켓 이름>
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
    TMap<FGameplayTag, FName> SlotMap;

    // 생성된 슬롯 (스태틱 메시 컴포넌트)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<FGameplayTag, TObjectPtr<UStaticMeshComponent>> Slots;

public:
    UGFFAttachmentManager();

    UFUNCTION(BlueprintCallable)
    void SetTargetMesh(UMeshComponent* InTargetMesh);

    void SetAttachment(UGFFAttachmentDefinition* Attachment);

private:
    void CreateSlots();

    UStaticMeshComponent* AttachStaticMeshComponentToTarget(const FName& SocketName) const;
};
