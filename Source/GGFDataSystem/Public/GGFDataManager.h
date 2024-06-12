// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GGFActorComponent.h"
#include "GGFDataManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIDUpdated, int32, NewID);

/**
 * 데이터 서브 시스템을 사용하기 위한 전용 컴포넌트입니다.
 *
 * 자식 클래스에서는 주로 전용 데이터 서브 시스템을 사용하기 때문에
 * GetData, GetDefinition 메서드만 추가로 정의해주면 됩니다.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFDATASYSTEM_API UGGFDataManager : public UGGFActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnIDUpdated OnIDUpdated;

protected:
    // 데이터 ID
    UPROPERTY(EditAnywhere, BlueprintGetter = GetID, BlueprintSetter = SetID, Category = "Config")
    int32 ID;

public:
    /* ActorComponent */

    virtual void PostInitProperties() override;

protected:
    /* Static */

    template<class T>
    T* GetDataSubsystem() const
    {
        if(GetWorld() == nullptr) return nullptr;

        if(auto GameInstance = GetWorld()->GetGameInstance())
        {
            return GameInstance->GetSubsystem<T>();
        }

        return nullptr;
    }

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE int32 GetID() const { return ID; }

    /* Setter */

    UFUNCTION(BlueprintSetter)
    virtual void SetID(int32 NewID);
};
