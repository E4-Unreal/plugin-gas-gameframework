﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGFTriggerBox.generated.h"

class UBoxComponent;

/**
 * 기본적인 박스 오버랩 이벤트가 바인딩된 범용 액터 클래스입니다.
 */
UCLASS()
class GGFGIMMICKSYSTEM_API AGGFTriggerBox : public AActor
{
    GENERATED_BODY()

    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetDefaultScene, Category = "Component")
    TObjectPtr<USceneComponent> DefaultScene;

    // 오버랩 감지를 위한 박스 트리거
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetTriggerBox, Category = "Component")
    TObjectPtr<UBoxComponent> TriggerBox;

protected:
    // true로 설정된 경우 서버에서만 트리거 이벤트가 호출됩니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bServerOnly = true;

public:
    AGGFTriggerBox();

    /* Actor */

    virtual void PostInitializeComponents() override;
    virtual void OnConstruction(const FTransform& Transform) override;

protected:
    /* 메서드 */

    // 트리거 박스의 피벗 위치를 정중앙에서 정하단으로 변경
    UFUNCTION(BlueprintCallable)
    virtual void RefreshTriggerBox();

    /* 이벤트 */

    UFUNCTION()
    virtual void OnTriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    virtual void OnTriggerBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION(BlueprintNativeEvent)
    void OnTriggerBoxBeginOverlapPawn(UPrimitiveComponent* OverlappedComponent, APawn* OtherPawn, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintNativeEvent)
    void OnTriggerBoxEndOverlapPawn(UPrimitiveComponent* OverlappedComponent, APawn* OtherPawn, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UBoxComponent* GetTriggerBox() const { return TriggerBox; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USceneComponent* GetDefaultScene() const { return DefaultScene; }
};
