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

    // 데이터 테이블로부터 런타임에 생성된 모든 데이터 에셋 목록
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UGGFDefinitionBase*> List;

    // TMap<DefinitionID, Definition>
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<int32, UGGFDefinitionBase*> Map;

    /* 메서드 */

    // 데이터 테이블로부터 데이터 에셋 생성 및 매핑
    bool Init(UObject* Outer, TSubclassOf<UGGFDefinitionBase> DefinitionClass, UDataTable* DataTable);
};

// TODO 비동기로 전환
/**
 * 런타임에 데이터 테이블로부터 데이터 에셋 생성 및 관리를 담당하는 서브 시스템 클래스입니다.
 */
UCLASS()
class GGFDATASYSTEM_API UGGFDataSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    static FGGFDefinitionContainer EmptyDefinitionContainer;

protected:
    UPROPERTY(Transient)
    TMap<TSubclassOf<UGGFDefinitionBase>, FGGFDefinitionContainer> DefinitionContainerMap;

public:
    /* Static */

    template <class T>
    FORCEINLINE static void CachingDefinition(UGGFDefinitionBase* DefinitionBase, TArray<TObjectPtr<T>>& DefinitionList, TMap<int32, TObjectPtr<T>>& DefinitionIDMap)
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

    template <class T>
    FORCEINLINE T* GetCastedDefinition(TSubclassOf<T> DefinitionClass, int32 ID)
    {
        static_assert(std::is_base_of_v<UGGFDefinitionBase, T>, "type parameter of this class must derive from BaseClass");

        auto DefinitionBase = GetDefinitionBase(DefinitionClass, ID);
        return DefinitionBase && DefinitionBase->IsValid() ? CastChecked<T>(DefinitionBase) : nullptr;
    }

    template <class T>
    FORCEINLINE void GetCastedDefinitionListAndMap(TSubclassOf<UGGFDefinitionBase> DefinitionClass, TArray<TObjectPtr<T>>& CastedDefinitionList, TMap<int32, TObjectPtr<T>>& CastedDefinitionMap)
    {
        static_assert(std::is_base_of_v<UGGFDefinitionBase, T>, "type parameter of this class must derive from BaseClass");

        // 초기화
        CastedDefinitionList.Reset();
        CastedDefinitionMap.Reset();

        // 검색
        const auto& DefinitionBaseList = GetDefinitionBaseList(DefinitionClass);
        const int32 MaxNum = DefinitionBaseList.Num();

        // 메모리 할당
        CastedDefinitionList.Reserve(MaxNum);
        CastedDefinitionMap.Reserve(MaxNum);

        // 캐스팅
        for (auto DefinitionBase : DefinitionBaseList)
        {
            const int32 DefinitionID = DefinitionBase->GetID();
            T* CastedDefinition = CastChecked<T>(DefinitionBase);
            CastedDefinitionList.Emplace(CastedDefinition);
            CastedDefinitionMap.Emplace(DefinitionID, CastedDefinition);
        }
    }

    /* Subsystem */

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    /* API */

    // 데이터 테이블로부터 생성된 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, meta = (DeterminesOutputType = DefinitionClass))
    UGGFDefinitionBase* GetDefinitionBase(TSubclassOf<UGGFDefinitionBase> DefinitionClass, int32 ID) const;

    // 데이터 테이블로부터 생성된 모든 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, meta = (DeterminesOutputType = DefinitionClass))
    const TArray<UGGFDefinitionBase*>& GetDefinitionBaseList(TSubclassOf<UGGFDefinitionBase> DefinitionClass) const;

    // 데이터 테이블로부터 생성된 모든 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, meta = (DeterminesOutputType = DefinitionClass))
    const TMap<int32, UGGFDefinitionBase*>& GetDefinitionBaseMap(TSubclassOf<UGGFDefinitionBase> DefinitionClass) const;

#if WITH_EDITOR
    // 데이터 테이블로부터 특정 데이터 가져오기
    static const FGGFDataTableRowBase* GetDirectData(TSubclassOf<UGGFDefinitionBase> DefinitionClass, int32 ID);

    // 데이터 테이블로부터 모든 데이터 가져오기
    static const TArray<const FGGFDataTableRowBase*> GetAllDirectData(TSubclassOf<UGGFDefinitionBase> DefinitionClass);
#endif

protected:
    // 프로젝트 설정 가져오기
    virtual void FetchProjectSettings();

    // 런타임에 데이터 테이블로부터 데이터 에셋 생성
    virtual void CreateDefinitionsFromDataTable(TSubclassOf<UGGFDefinitionBase> DefinitionClass, UDataTable* DataTable);
};
