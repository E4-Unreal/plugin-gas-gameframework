// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGFTriggerBase.generated.h"

/**
 * 콜리전 컴포넌트 오버랩 이벤트가 기본 바인딩된 베이스 액터 클래스
 */
UCLASS(Abstract)
class GGFCORE_API AGGFTriggerBase : public AActor
{
    GENERATED_BODY()

public:
    /* 서브 오브젝트 이름 */

    static FName DefaultSceneName;
    static FName CollisionName;
    static FName DisplayMeshName;

private:
    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetDefaultScene, Category = "Component")
    TObjectPtr<USceneComponent> DefaultScene;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetCollision, Category = "Component")
    TObjectPtr<UShapeComponent> Collision;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetDisplayMesh, Category = "Component")
    TObjectPtr<UStaticMeshComponent> DisplayMesh;

protected:
    // true 설정 시 서버에서만 오버랩 이벤트를 바인딩합니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bServerOnly = false;

    // 오버랩 이벤트를 호출할 액터 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TSubclassOf<AActor>> ClassFilters;

#if WITH_EDITORONLY_DATA
    // 로그 활성화 여부
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bEnableLog = false;
#endif

public:
    AGGFTriggerBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Actor */

    virtual void BeginPlay() override;

protected:
    /* 메서드 */

    // 오버랩 이벤트 발생 조건 검사
    virtual bool CheckOverlapCondition(AActor* OtherActor) const;

    // 오버랩 이벤트 바인딩
    UFUNCTION(BlueprintCallable)
    virtual void BindOverlapEvents();

    // 오버랩 이벤트 언바인딩
    UFUNCTION(BlueprintCallable)
    virtual void UnbindOverlapEvents();

    /* 이벤트 */

    UFUNCTION()
    virtual void InternalOnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    virtual void InternalOnCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION(BlueprintNativeEvent)
    void OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintNativeEvent)
    void OnCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USceneComponent* GetDefaultScene() const { return DefaultScene; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UShapeComponent* GetCollision() const { return Collision; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UStaticMeshComponent* GetDisplayMesh() const { return DisplayMesh; }
};
