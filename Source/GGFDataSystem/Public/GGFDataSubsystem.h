// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GGFDataSubsystem.generated.h"

class UGGFDefinitionBase;

USTRUCT(Atomic, BlueprintType)
struct FGGFDefinitionContainer
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UDataTable> DataTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<int32, TObjectPtr<UGGFDefinitionBase>> DefinitionMap;
};

/**
 * 런타임에 데이터 테이블로부터 데이터 에셋 생성 및 관리를 담당하는 서브 시스템 클래스입니다.
 */
UCLASS()
class GGFDATASYSTEM_API UGGFDataSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

protected:
    UPROPERTY(Transient)
    TMap<TSubclassOf<UGGFDefinitionBase>, FGGFDefinitionContainer> DefinitionContainerMap;

public:
    /* Subsystem */

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    /* API */

    // 데이터 테이블로부터 생성된 데이터 에셋 가져오기
    UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = DefinitionClass))
    UGGFDefinitionBase* GetOrCreateDefinition(TSubclassOf<UGGFDefinitionBase> DefinitionClass, int32 ID);

    // 데이터 테이블에서 데이터 직접 가져오기
    template <typename T>
    static T* GetDefinitionData(TSubclassOf<UGGFDefinitionBase> DefinitionClass, int32 ID);
};
