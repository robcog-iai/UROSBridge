// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "CoreMinimal.h"
#include "Json.h"

class UROSBRIDGE_API FROSTime {
public:
    uint32 secs, nsecs;

    FROSTime(uint32 secs_, uint32 nsecs_) :
        secs(secs_), nsecs(nsecs_) {
	}

	FROSTime()
	{
		auto NowTime = FROSTime::Now();
        secs = NowTime.secs;
        nsecs = NowTime.nsecs;
	}

	static FROSTime Now() {
		FDateTime NowDateTime = FDateTime::Now(); 
        uint32 secs = (uint32)NowDateTime.ToUnixTimestamp();
        uint32 nsecs = (uint32)NowDateTime.GetMillisecond() * 1000000;
        return FROSTime(secs, nsecs);
	}

	static FROSTime GetFromJson(TSharedPtr<FJsonObject> JsonObject) {
        uint32 secs = (uint32)(JsonObject->GetNumberField("secs"));
        uint32 nsecs = (uint32)(JsonObject->GetNumberField("nsecs"));
        return FROSTime(secs, nsecs);
	}

	FString ToString() const
	{
        return TEXT("Time { secs = ") + FString::FromInt(secs)
                 + TEXT(", nsecs = ") + FString::FromInt(nsecs) + TEXT(" }");
	}
	
	TSharedPtr<FJsonObject> ToJsonObject() const {
		TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetNumberField(TEXT("secs"), secs);
        Object->SetNumberField(TEXT("nsecs"), nsecs);
		return Object;
	}

	FString ToYamlString() const {
		FString OutputString;
		FJsonObject Object;
        Object.SetNumberField(TEXT("secs"), secs);
        Object.SetNumberField(TEXT("nsecs"), nsecs);

		TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(MakeShared<FJsonObject>(Object), Writer);
		return OutputString;
	}

};
