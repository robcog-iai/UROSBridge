#pragma once

#include "ROSBridgeMsg.h"


namespace std_msgs
{
	class Int32 : public FROSBridgeMsg
	{
		int32 Data;
	public:
		Int32()
		{
			MsgType = TEXT("std_msgs/Int32");
		}
		
		Int32(int32 InData)
			:
			Data(InData)
		{
			MsgType = TEXT("std_msgs/Int32");
		}

		~Int32() override {}

		// Getters 
		int32 GetData() const { return Data; }

		// Setters 
		void SetData(int32 InData) { Data = InData; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Data = JsonObject->GetNumberField(TEXT("data"));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Data = BsonObject->GetNumberField(TEXT("data"));

		}

		static Int32 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Int32 Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static Int32 GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			Int32 Result;
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
							
			return TEXT("Int32 { data = ") + FString::FromInt(Data) +
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