// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/GGFCharacterSkinDefinition.h"
#include "GGFCharacterSkinManager.generated.h"

// TODO 캐릭터 ID를 관리할 방법? 리플리케이트 순서 고민
/**
 * 캐릭터 스킨 관리 전용 액터 컴포넌트입니다.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFCHARACTERSYSTEM_API UGGFCharacterSkinManager : public UActorComponent
{
    GENERATED_BODY()

    /* 레퍼런스 */

    // TODO 부위별 메시
    // 캐릭터 풀 메시
    TWeakObjectPtr<USkeletalMeshComponent> CharacterMesh;

protected:
    // 기본 적용할 스킨 ID 목록
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<int32> DefaultIDList;

    // TODO Enum 대신 게임플레이 태그로 대체
    // 현재 적용된 스킨 ID 매핑 정보
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<EGGFCharacterSkinType, TObjectPtr<UGGFCharacterSkinDefinition>> DefinitionMap;

public:
    UGGFCharacterSkinManager();

    /* ActorComponent */

    virtual void InitializeComponent() override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

    /* API */

    // 스킨 설정 시 스켈레탈 메시를 설정할 스켈레탈 메시 컴포넌트
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetCharacterMesh(USkeletalMeshComponent* NewCharacterMesh);

    // 구조체를 통해 스킨 설정
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetSkinByData(const FGGFCharacterSkinData& NewSkinData);

    // 데이터 에셋을 통해 스킨 설정
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetSkinByDefinition(UGGFCharacterSkinDefinition* NewSkinDefinition);

    // 스킨 ID를 통해 스킨 설정
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetSkinByID(int32 ID);

    // 캐릭터 스킨 정보를 초기화합니다. 캐릭터가 변경되는 경우 호출하면 됩니다.
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Reset();

    // 현재 설정된 스킨 ID 목록
    UFUNCTION(BlueprintPure)
    TArray<int32> GetCurrentSkinIDList() const;

protected:
    /* Getter */

    UFUNCTION(BlueprintPure)
    FORCEINLINE USkeletalMeshComponent* GetCharacterMesh() const { return CharacterMesh.Get(); }
};
