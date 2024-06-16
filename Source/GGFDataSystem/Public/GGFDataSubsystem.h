// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFDefinitionBase.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Logging.h"
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

    /**
     * 데이터 복사가 이루어지기 때문에 런타임에서는 관련 데이터 서브 시스템을 이용하거나,
     * GetCastedDefinition 사용을 권장드립니다.
     *
     * @return 데이터 테이블로부터 ID에 해당하는 데이터를 가져옵니다.
     */
    template <typename T>
    FORCEINLINE static T* GetData(TSubclassOf<UGGFDefinitionBase> DefinitionClass, int32 ID)
    {
        check(DefinitionClass);
        static_assert(std::is_base_of_v<FGGFDataTableRowBase, T>, "type parameter of this class must derive from BaseClass");

        if(UDataTable* DataTable = GetDataTable(DefinitionClass))
        {
            if(T* DataPtr = DataTable->FindRow<T>(FName(FString::FromInt(ID)), ""))
            {
                return DataPtr;
            }
        }

        return nullptr;
    }

    /**
     * 데이터 복사가 이루어지기 때문에 런타임에서는 관련 데이터 서브 시스템을 이용하거나,
     * GetCastedDefinitionList 사용을 권장드립니다.
     *
     * @return 데이터 테이블로부터 모든 데이터를 가져옵니다.
     */
    template <typename T>
    FORCEINLINE static bool GetDataList(TSubclassOf<UGGFDefinitionBase> DefinitionClass, int32 ID, TArray<T>& DataList)
    {
        static_assert(std::is_base_of_v<FGGFDataTableRowBase, T>, "type parameter of this class must derive from BaseClass");

        // 초기화
        DataList.Reset();

        if(UDataTable* DataTable = GetDataTable(DefinitionClass))
        {
            const auto& RowNames = DataTable->GetRowNames();
            DataList.Reserve(RowNames.Num());
            for (const auto& RowName : RowNames)
            {
                if(T* DataPtr = DataTable->FindRow<T>(FName(FString::FromInt(ID)), ""))
                {
                    DataList.Emplace(*DataPtr);
                }
            }

            return true;
        }

        return false;
    }

    /**
     * 관련 데이터 서브 시스템이 없는 경우 사용합니다.
     *
     * @return ID에 해당하는 캐스팅된 데이터 에셋
     */
    template <class T>
    FORCEINLINE T* GetCastedDefinition(TSubclassOf<UGGFDefinitionBase> DefinitionClass, int32 ID)
    {
        static_assert(std::is_base_of_v<UGGFDefinitionBase, T>, "type parameter of this class must derive from BaseClass");

        auto DefinitionBase = GetDefinitionBase(DefinitionClass, ID);
        return DefinitionBase && DefinitionBase->IsValid() ? CastChecked<T>(DefinitionBase) : nullptr;
    }

    /**
     * 관련 데이터 서브 시스템이 없는 경우 사용합니다.
     *
     * @return 캐스팅된 모든 데이터 에셋
     */
    template <class T>
    FORCEINLINE TArray<T*> GetCastedDefinitionList(TSubclassOf<UGGFDefinitionBase> DefinitionClass)
    {
        static_assert(std::is_base_of_v<UGGFDefinitionBase, T>, "type parameter of this class must derive from BaseClass");

        // 검색
        const auto& DefinitionBaseList = GetDefinitionBaseList(DefinitionClass);
        const int32 MaxNum = DefinitionBaseList.Num();

        // 초기화
        TArray<T*> CastedDefinitionList;
        CastedDefinitionList.Reserve(MaxNum);

        // 캐스팅
        for (auto DefinitionBase : DefinitionBaseList)
        {
            CastedDefinitionList.Emplace(CastChecked<T>(DefinitionBase));
        }

        return CastedDefinitionList;
    }

    /**
     * 관련 데이터 서브 시스템이 없는 경우 사용합니다.
     *
     * @return 캐스팅된 모든 데이터 에셋 매핑 정보
     */
    template <class T>
    FORCEINLINE TMap<int32, T*> GetCastedDefinitionMap(TSubclassOf<UGGFDefinitionBase> DefinitionClass)
    {
        static_assert(std::is_base_of_v<UGGFDefinitionBase, T>, "type parameter of this class must derive from BaseClass");

        // 검색
        const auto& DefinitionBaseList = GetDefinitionBaseList(DefinitionClass);
        const int32 MaxNum = DefinitionBaseList.Num();

        // 초기화
        TMap<int32, T*> CastedDefinitionMap;
        CastedDefinitionMap.Reserve(MaxNum);

        // 캐스팅
        for (auto DefinitionBase : DefinitionBaseList)
        {
            CastedDefinitionMap.Emplace(DefinitionBase->GetID(), CastChecked<T>(DefinitionBase));
        }

        return CastedDefinitionMap;
    }

    /**
     * 관련 데이터 서브 시스템에서 데이터 에셋을 캐싱할 때 사용합니다.
     *
     * @param CastedDefinitionList 관련 데이터 서브 시스템에 정의된 멤버 변수
     * @param CastedDefinitionMap 관련 데이터 서브 시스템에 정의된 멤버 변수
     */
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

    // 데이터 테이블 가져오기
    UFUNCTION(BlueprintPure)
    static UDataTable* GetDataTable(TSubclassOf<UGGFDefinitionBase> DefinitionClass);

    // 데이터 테이블로부터 생성된 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, meta = (DeterminesOutputType = DefinitionClass))
    UGGFDefinitionBase* GetDefinitionBase(TSubclassOf<UGGFDefinitionBase> DefinitionClass, int32 ID) const;

    // 데이터 테이블로부터 생성된 모든 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, meta = (DeterminesOutputType = DefinitionClass))
    const TArray<UGGFDefinitionBase*>& GetDefinitionBaseList(TSubclassOf<UGGFDefinitionBase> DefinitionClass) const;

    // 데이터 테이블로부터 생성된 모든 데이터 에셋 가져오기
    UFUNCTION(BlueprintPure, meta = (DeterminesOutputType = DefinitionClass))
    const TMap<int32, UGGFDefinitionBase*>& GetDefinitionBaseMap(TSubclassOf<UGGFDefinitionBase> DefinitionClass) const;

protected:
    // 프로젝트 설정 가져오기
    virtual void FetchProjectSettings();

    // 런타임에 데이터 테이블로부터 데이터 에셋 생성
    virtual void CreateDefinitionsFromDataTable(TSubclassOf<UGGFDefinitionBase> DefinitionClass, UDataTable* DataTable);
};
