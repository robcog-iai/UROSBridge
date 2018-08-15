#pragma once

#include "ROSBridgeMsg.h"


namespace std_msgs
{
	class String : public FROSBridgeMsg
	{
		FString Data;
	public:
		String()
		{
			MsgType = TEXT("std_msgs/String");
		}
		
		String(FString InData)
			:
			Data(InData)
		{
			MsgType = TEXT("std_msgs/String");
		}

		~String() override {}

		// Getters 
		FString GetData() const { return Data; }

		// Setters 
		void SetData(FString InData) { Data = InData; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Data = JsonObject->GetStringField(TEXT("data"));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Data = BsonObject->GetStringField(TEXT("data"));

		}

		static String GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			String Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static String GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			String Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetStringField(TEXT("data"), Data);

			return Object;

		}

		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetStringField(TEXT("data"), Data);

			return Object;

		}

		virtual FString ToString() const override
		{
							
			return TEXT("String { data = ") + Data +
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