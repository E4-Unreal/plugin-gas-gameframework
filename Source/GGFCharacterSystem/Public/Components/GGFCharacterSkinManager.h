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

    // TODO 부위별 메시
    // 캐릭터 풀 메시
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetCharacterMesh, Category = "State", Transient)
    TObjectPtr<USkeletalMeshComponent> CharacterMesh;

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

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetCharacterMesh(USkeletalMeshComponent* NewCharacterMesh);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetSkinData(const FGGFCharacterSkinData& NewSkinData);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetSkinDefinition(UGGFCharacterSkinDefinition* NewSkinDefinition);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetSkinID(int32 ID);

protected:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USkeletalMeshComponent* GetCharacterMesh() const { return CharacterMesh; }
};
