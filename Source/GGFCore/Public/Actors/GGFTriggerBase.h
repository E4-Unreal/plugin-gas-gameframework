// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGFTriggerBase.generated.h"

UCLASS(Abstract)
class GGFCORE_API AGGFTriggerBase : public AActor
{
    GENERATED_BODY()

public:
    /* 서브 오브젝트 이름 */

    static FName DefaultSceneName;
    static FName CollisionComponentName;
    static FName DisplayMeshName;

private:
    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetDefaultScene, Category = "Component")
    TObjectPtr<USceneComponent> DefaultScene;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetCollisionComponent, Category = "Component")
    TObjectPtr<UShapeComponent> CollisionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetDisplayMesh, Category = "Component")
    TObjectPtr<UStaticMeshComponent> DisplayMesh;

protected:
#if WITH_EDITORONLY_DATA
    // 로그 활성화 여부
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bEnableLog = false;
#endif

public:
    AGGFTriggerBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Actor */

    virtual void PostInitializeComponents() override;

protected:
    /* 메서드 */

    UFUNCTION(BlueprintCallable)
    virtual void BindOverlapEvents();

    UFUNCTION(BlueprintCallable)
    virtual void UnbindOverlapEvents();

    /* 이벤트 */

    UFUNCTION(BlueprintNativeEvent)
    void OnCollisionComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintNativeEvent)
    void OnCollisionComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION(BlueprintNativeEvent)
    void OnCollisionComponentBeginOverlapPawn(UPrimitiveComponent* OverlappedComponent, APawn* OtherPawn, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintNativeEvent)
    void OnCollisionComponentEndOverlapPawn(UPrimitiveComponent* OverlappedComponent, APawn* OtherPawn, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USceneComponent* GetDefaultScene() const { return DefaultScene; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UShapeComponent* GetCollisionComponent() const { return CollisionComponent; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UStaticMeshComponent* GetDisplayMesh() const { return DisplayMesh; }
};
