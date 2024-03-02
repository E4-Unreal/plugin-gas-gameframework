#pragma once

DECLARE_LOG_CATEGORY_EXTERN(LogGASExtension, Log, All)

// 클래스명::함수이름(호출 위치)
#define CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

// Call Info를 로그로 출력
#define LOG_CALLINFO(Category, Verbosity) UE_LOG(Category, Verbosity, TEXT("%s"), *CALLINFO)

// Call Info와 추가 텍스트를 로그로 출력
#define LOG_CALLINFO_COMMENT(Category, Verbosity, Format, ...) UE_LOG(Category, Verbosity, TEXT("%s %s"), *CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

// Crash 없이 Assertion 로그 출력
#define LOG_CHECK(Category, Expr, ...) {if(Expr) {LOG_CALLINFO_COMMENT(Category, Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'"));}}
