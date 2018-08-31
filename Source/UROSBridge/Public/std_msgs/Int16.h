#pragma once

#include "ROSBridgeMsg.h"


namespace std_msgs
{
	class Int16 : public FROSBridgeMsg
	{
		int16 Data;
	public:
		Int16()
		{
			MsgType = TEXT("std_msgs/Int16");
		}
		
		Int16(int16 InData)
			:
			Data(InData)
		{
			MsgType = TEXT("std_msgs/Int16");
		}

		~Int16() override {}

		// Getters 
		int16 GetData() const { return Data; }

		// Setters 
		void SetData(int16 InData) { Data = InData; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Data = JsonObject->GetNumberField(TEXT("data"));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Data = BsonObject->GetNumberField(TEXT("data"));

		}

		static Int16 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Int16 Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static Int16 GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			Int16 Result;
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
							
			return TEXT("Int16 { data = ") + FString::FromInt(Data) +
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