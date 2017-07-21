#pragma once

#include "CoreMinimal.h"
#include "Json.h"

class ROSBRIDGEPLUGIN_API FROSTime {
public:
	uint32 sec, usec; 

	FROSTime(uint32 sec_, uint32 usec_) :
		sec(sec_), usec(usec_) {
	}

	FROSTime()
	{
		auto NowTime = FROSTime::Now();
		sec = NowTime.sec;
		usec = NowTime.usec;
	}

	static FROSTime Now() {
		FDateTime NowDateTime = FDateTime::Now(); 
		uint32 sec = (uint32)NowDateTime.ToUnixTimestamp();
		uint32 usec = (uint32)NowDateTime.GetMillisecond() * 1000000;
		return FROSTime(sec, usec); 
	}

	static FROSTime GetFromJson(TSharedPtr<FJsonObject> JsonObject) {
		uint32 sec = (uint32)(JsonObject->GetNumberField("sec"));
		uint32 usec = (uint32)(JsonObject->GetNumberField("usec"));
		return FROSTime(sec, usec); 
	}

	FString ToString() const
	{
		return TEXT("Time { sec = ") + FString::FromInt(sec) 
			     + TEXT(", usec = ") + FString::FromInt(usec) + TEXT(" }");
	}
	
	TSharedPtr<FJsonObject> ToJsonObject() const {
		TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
		Object->SetNumberField(TEXT("sec"), sec);
		Object->SetNumberField(TEXT("usec"), usec);
		return Object;
	}

	FString ToYamlString() const {
		FString OutputString;
		FJsonObject Object;
		Object.SetNumberField(TEXT("sec"), sec);
		Object.SetNumberField(TEXT("usec"), usec);

		TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(MakeShared<FJsonObject>(Object), Writer);
		return OutputString;
	}

};