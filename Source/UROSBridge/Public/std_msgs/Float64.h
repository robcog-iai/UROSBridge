#pragma once

#include "ROSBridgeMsg.h"


namespace std_msgs
{
	class Float64 : public FROSBridgeMsg
	{
		double Data;
	public:
		Float64()
		{
			MsgType = TEXT("std_msgs/Float64");
		}
		
		Float64(double InData)
			:
			Data(InData)
		{
			MsgType = TEXT("std_msgs/Float64");
		}

		~Float64() override {}

		// Getters 
		double GetData() const { return Data; }

		// Setters 
		void SetData(double InData) { Data = InData; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Data = JsonObject->GetNumberField(TEXT("data"));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Data = BsonObject->GetNumberField(TEXT("data"));

		}

		static Float64 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Float64 Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static Float64 GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			Float64 Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetNumberField(TEXT("data"), Data);

			return Object;

		}

		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetNumberField(TEXT("data"), Data);

			return Object;

		}

		virtual FString ToString() const override
		{
							
			return TEXT("Float64 { data = ") + FString::SanitizeFloat(Data) +
				TEXT(" } ");

		}


		virtual FString ToYamlString() const override
		{
			FString OutputString;
			TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
			FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
			return OutputString;
		}
						
	};
	
}