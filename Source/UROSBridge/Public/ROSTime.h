// Copyright 2018, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "CoreMinimal.h"
#include "Json.h"

class UROSBRIDGE_API FROSTime 
{
public:
    uint32 Secs, NSecs;

    FROSTime(uint32 InSecs, uint32 InNSecs) :
        Secs(InSecs), NSecs(InNSecs) 
	{
	}

	FROSTime()
	{
		auto NowTime = FROSTime::Now();
        Secs = NowTime.Secs;
        NSecs = NowTime.NSecs;
	}

	static FROSTime Now() 
	{
		FDateTime NowDateTime = FDateTime::Now(); 
        uint32 Secs = (uint32)NowDateTime.ToUnixTimestamp();
        uint32 NSecs = (uint32)NowDateTime.GetMillisecond() * 1000000;
        return FROSTime(Secs, NSecs);
	}

	static FROSTime GetFromJson(TSharedPtr<FJsonObject> JsonObject) 
	{
        uint32 Secs = (uint32)(JsonObject->GetNumberField("secs"));
        uint32 NSecs = (uint32)(JsonObject->GetNumberField("nsecs"));
        return FROSTime(Secs, NSecs);
	}

	FString ToString() const
	{
        return TEXT("Time { secs = ") + FString::FromInt(Secs)
                 + TEXT(", nsecs = ") + FString::FromInt(NSecs) + TEXT(" }");
	}
	
	TSharedPtr<FJsonObject> ToJsonObject() const 
	{
		TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetNumberField(TEXT("secs"), Secs);
        Object->SetNumberField(TEXT("nsecs"), NSecs);
		return Object;
	}

	FString ToYamlString() const 
	{
		FString OutputString;
		FJsonObject Object;
        Object.SetNumberField(TEXT("secs"), Secs);
        Object.SetNumberField(TEXT("nsecs"), NSecs);

		TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(MakeShared<FJsonObject>(Object), Writer);
		return OutputString;
	}
};
