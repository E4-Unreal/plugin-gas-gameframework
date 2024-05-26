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

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetMesh, Category = "Reference", Transient)
    TObjectPtr<USkeletalMeshComponent> Mesh;

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

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetMesh(USkeletalMeshComponent* NewMesh);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetData(const FGGFCharacterData& NewCharacterData);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetDefinition(UGGFCharacterDefinition* NewDefinition);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetID(int32 ID);

    UFUNCTION(BlueprintPure)
    FORCEINLINE int32 GetID() const { return CharacterDefinition ? CharacterDefinition->GetID() : -1; }

protected:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USkeletalMeshComponent* GetMesh() const { return Mesh; }
};
