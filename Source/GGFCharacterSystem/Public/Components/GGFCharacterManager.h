// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/GGFCharacterDefinition.h"
#include "GGFCharacterManager.generated.h"

class UGGFCharacterSkinManager;
class UGGFCharacterDefinition;

/**
 * 캐릭터 설정을 담당하는 액터 컴포넌트입니다.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFCHARACTERSYSTEM_API UGGFCharacterManager : public UActorComponent
{
    GENERATED_BODY()

    /* 레퍼런스 */

    TWeakObjectPtr<USkeletalMeshComponent> CharacterMesh;

protected:
    // 캐릭터 ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int32 DefaultID;

    // 캐릭터 정의 데이터 에셋
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<UGGFCharacterDefinition> CharacterDefinition;

public:
    UGGFCharacterManager();

    /* ActorComponent */

    virtual void InitializeComponent() override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

    /* API */

    // 캐릭터 설정 시 스켈레탈 메시와 애님 인스턴스 클래스를 설정할 스켈레탈 메시 컴포넌트
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetCharacterMesh(USkeletalMeshComponent* NewCharacterMesh);

    // 구조체를 통해 캐릭터 설정
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetCharacterByData(const FGGFCharacterData& NewCharacterData);

    // 데이터 에셋을 통해 캐릭터 설정
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetCharacterByDefinition(UGGFCharacterDefinition* NewDefinition);

    // ID를 통해 캐릭터 설정
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetCharacterByID(int32 ID);

    // 현재 설정된 캐릭터 ID
    UFUNCTION(BlueprintPure)
    FORCEINLINE int32 GetCharacterID() const { return CharacterDefinition ? CharacterDefinition->GetID() : -1; }

protected:
    /* Getter */

    UFUNCTION(BlueprintPure)
    FORCEINLINE USkeletalMeshComponent* GetCharacterMesh() const { return CharacterMesh.Get(); }
};
