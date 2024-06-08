// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFTimelineActor.h"
#include "Interfaces/GGFActivationInterface.h"
#include "GGFDoor.generated.h"

/**
 * 문이 열리는 방식
 */
UENUM(BlueprintType)
enum class EGGFDoorType : uint8
{
    Swing,
    Slide,
    SlideUp
};

/**
 * 여닫이 문
 */
UCLASS()
class GGFGIMMICKSYSTEM_API AGGFDoor : public AGGFTimelineActor, public IGGFActivationInterface
{
    GENERATED_BODY()

    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetDefaultSceneComponent, Category = "Component")
    TObjectPtr<USceneComponent> DefaultSceneComponent;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetDoorMesh, Category = "Component")
    TObjectPtr<UStaticMeshComponent> DoorMesh;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetDoorFrameMesh, Category = "Component")
    TObjectPtr<UStaticMeshComponent> DoorFrameMesh;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Door")
    EGGFDoorType DoorType = EGGFDoorType::Swing;

    // 문이 열리는 최대 각도
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Door", meta = (ClampMin = 0, ClampMax = 180))
    float MaxAngle = 90;

    // 문이 움직이는 최대 거리
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Door", meta = (ClampMin = 0))
    float MaxDistance = 100;

    // 처음 설정된 DoorMesh 오프셋
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Door", Transient)
    FTransform TransformOffset;

public:
    AGGFDoor();

    /* Actor */

    virtual void PostInitializeComponents() override;

    /* ActivationInterface */

    virtual bool Activate_Implementation(AActor* InstigatorActor) override;
    virtual bool Deactivate_Implementation(AActor* InstigatorActor) override;

protected:
    /* TimelineActor */

    virtual void OnTimelineActivated_Implementation(float Value) override;

    /* 메서드 */

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Open();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Close();

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USceneComponent* GetDefaultSceneComponent() const { return DefaultSceneComponent; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UStaticMeshComponent* GetDoorMesh() const { return DoorMesh; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UStaticMeshComponent* GetDoorFrameMesh() const { return DoorFrameMesh; }
};
