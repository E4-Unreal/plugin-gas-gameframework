#pragma once

DECLARE_LOG_CATEGORY_EXTERN(LogGGFCore, Log, All)

#define CATEGORY LogGGFCore

// 범용 로그
#define LOG(Verbosity, Format, ...) UE_LOG(CATEGORY, Verbosity, TEXT("%s > %s"), *CALL_INFO, *FString::Printf(Format, ##__VA_ARGS__))

// 액터 이름(Server or Client)
#define ACTOR_INFO (GetName() + TEXT("(") + (HasAuthority() ? FString("Server") : FString("Client")) + TEXT(")"))

// 액터 이름(Server or Client) - 액터 컴포넌트에서 호출
#define ACTOR_COMPONENT_INFO (GetOwner()->GetName() + TEXT("(") + (GetOwner()->HasAuthority() ? FString("Server") : FString("Client")) + TEXT(")"))

// 위젯 이름(Server or Client) - 위젯에서 호출
#define WIDGET_INFO (GetName() + TEXT("(") + (GetOwningPlayer()->HasAuthority() ? FString("Server") : FString("Client")) + TEXT(")"))

// 클래스명::함수이름(호출 위치)
#define CALL_INFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

// Server or Client > 오브젝트 이름 > 클래스::메서드(줄 위치) > 코멘트
#define LOG_ACTOR_DETAIL(Verbosity, Format, ...) UE_LOG(CATEGORY, Verbosity, TEXT("%s > %s > %s"), *ACTOR_INFO, *CALL_INFO, *FString::Printf(Format, ##__VA_ARGS__))

// Server or Client > 오브젝트 이름 > 클래스::메서드(줄 위치) > 코멘트
#define LOG_ACTOR_COMPONENT_DETAIL(Verbosity, Format, ...) UE_LOG(CATEGORY, Verbosity, TEXT("%s > %s > %s"), *ACTOR_COMPONENT_INFO, *CALL_INFO, *FString::Printf(Format, ##__VA_ARGS__))

// Server or Client > 오브젝트 이름 > 클래스::메서드(줄 위치) > 코멘트
#define LOG_WIDGET_DETAIL(Verbosity, Format, ...) UE_LOG(CATEGORY, Verbosity, TEXT("%s > %s > %s"), *WIDGET_INFO, *CALL_INFO, *FString::Printf(Format, ##__VA_ARGS__))

// Call Info를 로그로 출력
#define LOG_CALL_INFO(Verbosity) UE_LOG(CATEGORY, Verbosity, TEXT("%s"), *CALLINFO)

// Call Info와 추가 텍스트를 로그로 출력
#define LOG_CALL_INFO_COMMENT(Verbosity, Format, ...) UE_LOG(CATEGORY, Verbosity, TEXT("%s %s"), *CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

// Crash 없이 Assertion 로그 출력
#define LOG_CHECK(Expr, ...) {if(Expr) {LOG_CALLINFO_COMMENT(CATEGORY, Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'"));}}
