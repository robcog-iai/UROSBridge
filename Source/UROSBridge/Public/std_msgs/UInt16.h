#pragma once

#include "ROSBridgeMsg.h"


namespace std_msgs
{
	class UInt16 : public FROSBridgeMsg
	{
		uint16 Data;
	public:
		UInt16()
		{
			MsgType = TEXT("std_msgs/UInt16");
		}
		
		UInt16(uint16 InData)
			:
			Data(InData)
		{
			MsgType = TEXT("std_msgs/UInt16");
		}

		~UInt16() override {}

		// Getters 
		uint16 GetData() const { return Data; }

		// Setters 
		void SetData(uint16 InData) { Data = InData; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Data = JsonObject->GetNumberField(TEXT("data"));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Data = BsonObject->GetNumberField(TEXT("data"));

		}

		static UInt16 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			UInt16 Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static UInt16 GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			UInt16 Result;
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
							
			return TEXT("UInt16 { data = ") + FString::FromInt(Data) +
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