#pragma once

#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"

namespace sensor_msgs
{
	class CompressedImage : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		FString Format;
		TArray<uint8> Data;
	public:
		CompressedImage()
		{
			MsgType = "sensor_msgs/CompressedImage";
		}

		CompressedImage
		(
			std_msgs::Header InHeader,
			FString InFormat,
			const TArray<uint8>& InData
		):
			Header(InHeader),
			Format(InFormat),
			Data(InData)
		{
			MsgType = "sensor_msgs/CompressedImage";
		}

		~CompressedImage() override {}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		FString GetFormat() const
		{
			return Format;
		}

		TArray<uint8> GetData() const
		{
			return Data;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetFormat(FString InFormat)
		{
			Format = InFormat;
		}

		void SetData(TArray<uint8>& InData)
		{
			Data = InData;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			Format = JsonObject->GetStringField(TEXT("format"));

			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Data.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("data"));
			for (auto &ptr : ValuesPtrArr)
				Data.Add(ptr->AsNumber());

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Header = std_msgs::Header::GetFromBson(BsonObject->GetObjectField(TEXT("header")));

			Format = BsonObject->GetStringField(TEXT("format"));

			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

			Data.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("data"));
			for (auto &ptr : ValuesPtrArr)
				Data.Add(ptr->AsNumber());

		}

		static CompressedImage GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			CompressedImage Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static CompressedImage GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			CompressedImage Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetStringField(TEXT("format"), Format);
			TArray<TSharedPtr<FJsonValue>> DataArray;
			for (auto &val : Data)
				DataArray.Add(MakeShareable(new FJsonValueNumber(val)));
			Object->SetArrayField(TEXT("data"), DataArray);
			return Object;
		}
		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToBsonObject());
			Object->SetStringField(TEXT("format"), Format);
			TArray<TSharedPtr<FBsonValue>> DataArray;
			for (auto &val : Data)
				DataArray.Add(MakeShareable(new FBsonValueNumber(val)));
			Object->SetArrayField(TEXT("data"), DataArray);
			return Object;
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