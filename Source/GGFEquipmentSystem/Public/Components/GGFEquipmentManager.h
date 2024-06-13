// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GGFEquipmentManagerBase.h"
#include "GGFEquipmentManager.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FEquipmentSlotConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Equipment.Slot"))
    FGameplayTag SlotTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> SocketNames;
};

USTRUCT(Atomic, BlueprintType)
struct FEquipmentSlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag SlotTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Index;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SocketName;

    // 기본 구조체
    static const FEquipmentSlot EmptySlot;

    // 생성자
    FEquipmentSlot(){}

    FEquipmentSlot(FGameplayTag InSlotTag, int32 InIndex, FName InSocketName = NAME_None)
    {
        SlotTag = InSlotTag;
        Index = InIndex;
        SocketName = InSocketName;
    }

    /* 쿼리 */

    bool IsNotValid() const { return !IsValid(); }
    bool IsValid() const { return SlotTag != FGameplayTag::EmptyTag; }

    /* 연산자 오버로딩 */

    // 기본

    bool operator==(const FEquipmentSlot& Other) const
    {
        return Equals(Other);
    }

    bool operator!=(const FEquipmentSlot& Other) const
    {
        return !operator==(Other);
    }

    bool Equals(const FEquipmentSlot& Other) const
    {
        return SlotTag == Other.SlotTag && Index == Other.Index;
    }

    FORCEINLINE friend uint32 GetTypeHash(const FEquipmentSlot& Target)
    {
        return FCrc::MemCrc32(&Target, sizeof(FEquipmentSlot));
    }

    // 게임플레이 태그

    bool operator==(const FGameplayTag& OtherTag) const
    {
        return SlotTag == OtherTag;
    }
};

UCLASS(meta=(BlueprintSpawnableComponent))
class GGFEQUIPMENTSYSTEM_API UGGFEquipmentManager : public UGGFEquipmentManagerBase
{
    GENERATED_BODY()

protected:
    // 기본적으로 추가될 장비 목록입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = true, MustImplement = "GGFEquipmentInterface"))
    TArray<TSubclassOf<AActor>> DefaultEquipments;

    // 선택 장비를 부착할 소켓 이름입니다. 선택 장비는 손에 쥐고 있을 잘비를 의미합니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName HandSocketName = "weapon_r";

    // 사용 가능한 무기 슬롯 목록입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<FEquipmentSlotConfig> EquipmentSlotConfigs;

    // 실제 인게임 내에서 사용하는 무기 슬롯 목록입니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<FEquipmentSlot, TObjectPtr<AActor>> EquipmentSlots;

    // 손에 쥐고 있는 무기 슬롯입니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    FEquipmentSlot SelectedSlot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, ReplicatedUsing = OnRep_SelectedEquipment)
    TObjectPtr<AActor> SelectedEquipment;

public:

    /* ActorComponent */

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    virtual void InitializeComponent() override;
    virtual void BeginPlay() override;
    virtual void Activate(bool bReset) override;
    virtual void Deactivate() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

    /* API */

    UFUNCTION(BlueprintCallable)
    bool AddEquipment(TSubclassOf<AActor> EquipmentClass);

    UFUNCTION(BlueprintCallable)
    void RemoveEquipment(FGameplayTag Slot, int32 Index);

    UFUNCTION(BlueprintCallable, Server, Reliable)
    void Server_SelectEquipment(FGameplayTag Slot, int32 Index);

    UFUNCTION(BlueprintCallable)
    bool IsEquipmentExist(FGameplayTag Slot, int32 Index) const;

    UFUNCTION(BlueprintCallable)
    bool IsEquipmentSlotExist(FGameplayTag Slot, int32 Index) const;

    UFUNCTION(BlueprintCallable)
    AActor* GetEquipment(FGameplayTag Slot, int32 Index) const;

    UFUNCTION(BlueprintCallable)
    void ClearEquipmentSlot(FGameplayTag Slot, int32 Index);

    // 손에 쥐고 있는 장비 (SelectedEquipment) 가져오기
    UFUNCTION(BlueprintPure)
    FORCEINLINE AActor* GetSelectedEquipment() const { return SelectedEquipment; }

    // 손에 쥐고 있는 장비를 집어넣습니다. 장비를 제거하는 것이 아닙니다.
    UFUNCTION(BlueprintCallable)
    void Deselect();

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsSelectedEquipmentExist() const { return SelectedSlot.IsValid() && SelectedEquipment != nullptr; }

    virtual bool AttachEquipment(AActor* Equipment, FName SocketName) override;

    /* Query */

    UFUNCTION(BlueprintCallable)
    bool CanAddEquipment(TSubclassOf<AActor> EquipmentClass) const;

    UFUNCTION(BlueprintCallable)
    bool IsSlotAvailable(const FGameplayTag& InEquipmentSlot) const;

    UFUNCTION(BlueprintCallable)
    const FEquipmentSlot& GetAvailableSlot(const FGameplayTag& WeaponSlot) const;

protected:
    /* 메서드 */

    virtual void OnTargetMeshChanged() override;
    virtual void HideEquipments(bool bHidden);

private:
    // AvailableSlots로부터 EquipmentSlots를 생성합니다.
    void CreateEquipmentSlots();

    // 기본 장비를 추가합니다.
    void AddDefaultEquipments();

    /* 리플리케이트 */

    UFUNCTION()
    void OnRep_SelectedEquipment(AActor* OldEquipment);
};
