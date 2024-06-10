// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/GGFTimelineActor.h"
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

class USoundCue;

/**
 * 문
 */
UCLASS()
class GGFGIMMICKSYSTEM_API AGGFDoor : public AGGFTimelineActor, public IGGFActivationInterface
{
    GENERATED_BODY()

    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetDefaultSceneComponent, Category = "Component")
    TObjectPtr<USceneComponent> DefaultSceneComponent;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetDoorFrameMesh, Category = "Component")
    TObjectPtr<UStaticMeshComponent> DoorFrameMesh;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetDoorMesh, Category = "Component")
    TObjectPtr<UStaticMeshComponent> DoorMesh;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetAudioComponent, Category = "Component")
    TObjectPtr<UAudioComponent> AudioComponent;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Door")
    TObjectPtr<USoundCue> OpenSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Door")
    TObjectPtr<USoundCue> CloseSound;

    // 문이 열리는 방식
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Door")
    EGGFDoorType DoorType = EGGFDoorType::Swing;

    // 문이 열리는 최대 각도
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Door", meta = (ClampMin = 0, ClampMax = 180))
    float MaxAngle = 90;

    // 문이 움직이는 최대 거리
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Door", meta = (ClampMin = 0))
    float MaxDistance = 100;

    // 문이 열리기 위해 필요한 트리거 횟수
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Door", meta = (ClampMin = 1))
    int32 TriggerCount = 1;

    // 현재 발생한 트리거 횟수
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Door", Transient)
    int32 TriggerStack;

    // 처음 설정된 DoorMesh 오프셋
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Door", Transient)
    FTransform TransformOffset;

    // 활성화 상태
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Door", Transient, ReplicatedUsing = OnRep_Open)
    bool bOpen;

public:
    AGGFDoor();

    /* Actor */

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void PostInitializeComponents() override;

    /* ActivationInterface */

    virtual bool Activate_Implementation(AActor* InstigatorActor) override;
    virtual bool Deactivate_Implementation(AActor* InstigatorActor) override;

protected:
    /* TimelineActor */

    virtual void OnTimelineActivated_Implementation(float Value) override;

    /* OnRep */

    UFUNCTION()
    virtual void OnRep_Open(bool bOldOpen);

    /* 메서드 */

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Open();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Close();

    UFUNCTION(BlueprintCallable)
    void Toggle();

    UFUNCTION(BlueprintCallable)
    virtual void PlaySound(USoundCue* Sound);

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USceneComponent* GetDefaultSceneComponent() const { return DefaultSceneComponent; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UStaticMeshComponent* GetDoorFrameMesh() const { return DoorFrameMesh; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UStaticMeshComponent* GetDoorMesh() const { return DoorMesh; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UAudioComponent* GetAudioComponent() const { return AudioComponent; }
};
