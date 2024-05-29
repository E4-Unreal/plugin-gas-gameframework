// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFDefinitionBase.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GGFDataSubsystem.generated.h"

/**
 * DataSubsystem 전용 데이터 구조체
 */
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
    /* Static */

    template <class T>
    static void CachingDefinition(UGGFDefinitionBase* DefinitionBase, TArray<TObjectPtr<T>>& DefinitionList, TMap<int32, TObjectPtr<T>>& DefinitionIDMap)
    {
        static_assert(std::is_base_of_v<UGGFDefinitionBase, T>, "type parameter of this class must derive from BaseClass");

        // 유효성 검사
        if(DefinitionBase && DefinitionBase->IsValid())
        {
            // 캐스팅 후 저장
            T* Definition = CastChecked<T>(DefinitionBase);
            DefinitionList.Emplace(Definition);
            DefinitionIDMap.Emplace(Definition->GetID(), Definition);
        }
    }

    /* Subsystem */

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    /* API */

    // 데이터 테이블로부터 생성된 데이터 에셋 가져오기
    UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = DefinitionClass))
    UGGFDefinitionBase* GetOrCreateDefinition(TSubclassOf<UGGFDefinitionBase> DefinitionClass, int32 ID);

    // 데이터 테이블로부터 생성된 모든 데이터 에셋 가져오기
    UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = DefinitionClass))
    TArray<UGGFDefinitionBase*> GetOrCreateAllDefinitions(TSubclassOf<UGGFDefinitionBase> DefinitionClass);

#if WITH_EDITOR
    // 데이터 테이블로부터 특정 데이터 가져오기
    static const FGGFDataTableRowBase* GetDirectData(TSubclassOf<UGGFDefinitionBase> DefinitionClass, int32 ID);

    // 데이터 테이블로부터 모든 데이터 가져오기
    static const TArray<const FGGFDataTableRowBase*> GetAllDirectData(TSubclassOf<UGGFDefinitionBase> DefinitionClass);
#endif
};
