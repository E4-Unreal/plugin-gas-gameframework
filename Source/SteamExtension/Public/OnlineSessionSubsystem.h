// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "OnlineSessionSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreateSessionCompletedSignature, bool, bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFindSessionsCompletedSignature, const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnJoinSessionCompletedSignature, EOnJoinSessionCompleteResult::Type Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDestroySessionCompletedSignature, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartSessionCompletedSignature, bool, bWasSuccessful);

/**
 * 온라인 서브 시스템에서 세션을 관리하기 위한 게임 인스턴스 서브 시스템
 */
UCLASS()
class STEAMEXTENSION_API UOnlineSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    /* 델리게이트 */

    // 생성
    UPROPERTY(BlueprintAssignable)
    FOnCreateSessionCompletedSignature OnCreateSessionCompleted;

    // 검색
    FOnFindSessionsCompletedSignature OnFindSessionsCompleted;

    // 참가
    FOnJoinSessionCompletedSignature OnJoinSessionCompleted;

    // 파괴
    UPROPERTY(BlueprintAssignable)
    FOnDestroySessionCompletedSignature OnDestroySessionCompleted;

    // 시작
    UPROPERTY(BlueprintAssignable)
    FOnStartSessionCompletedSignature OnStartSessionCompleted;

private:
    /* 세션 */
    IOnlineSessionPtr SessionInterface;
    TSharedPtr<FOnlineSessionSettings> LastSessionSettings;
    TSharedPtr<FOnlineSessionSearch> LastSessionSearch;

    // 생성
    FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
    FDelegateHandle CreateSessionCompleteDelegateHandle;

    // 검색
    FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
    FDelegateHandle FindSessionsCompleteDelegateHandle;

    // 참가
    FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
    FDelegateHandle JoinSessionCompleteDelegateHandle;

    // 파괴
    FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
    FDelegateHandle DestroySessionCompleteDelegateHandle;

    // 시작
    FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
    FDelegateHandle StartSessionCompleteDelegateHandle;

    bool bCreateSessionOnDestroy{ false };
    int32 LastNumPublicConnections;

public:
	UOnlineSessionSubsystem();

    /* Subsystem */

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/* API */

    UFUNCTION(BlueprintCallable)
	virtual void CreateSession(int32 MaxPlayerNum);

    UFUNCTION(BlueprintCallable)
	virtual void DestroySession();

    UFUNCTION(BlueprintCallable)
	virtual void StartSession();

    UFUNCTION(BlueprintCallable)
    virtual void FindSessions(int32 MaxSearchResults);

    // TODO UFUNCTION으로 리팩토링
    virtual void JoinSession(const FOnlineSessionSearchResult& SessionResult);

protected:
    UFUNCTION(BlueprintCallable)
	bool IsValidSessionInterface();

	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	virtual void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	virtual void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);

    // TODO 리팩토링
    void OnFindSessionsComplete(bool bWasSuccessful);
    void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};
