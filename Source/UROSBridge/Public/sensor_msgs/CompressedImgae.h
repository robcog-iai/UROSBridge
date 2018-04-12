#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "std_msgs/String.h"

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
		(std_msgs::Header InHeader, FString InFormat, TArray<uint8> InData) :
			Header(InHeader), Format(InFormat), Data(InData)
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

		void SetHeader(const std_msgs::Header & InHeaders)
		{
			Header = InHeaders;
		}

		void SetFormat(const FString & InFormat)
		{
			Format = InFormat;
		}

		void SetData(const TArray<uint8> & InData)
		{
			Data = InData;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
			
			Format = JsonObject->GetStringField(TEXT("Format"));

			Data.Empty();
			TArray<TSharedPtr<FJsonValue>> DataPtrArr;
			DataPtrArr = JsonObject->GetArrayField(TEXT("data"));
			for (auto &ptr : DataPtrArr)
				Data.Add(ptr->AsNumber());
		}

		static CompressedImage GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			CompressedImage Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			FString ArrayData = "[ ";
			for (auto &datum : Data)
				ArrayData += FString::FromInt(datum) + TEXT(", ");
			ArrayData += " ]";

			return TEXT("CompressedImage {") + 
				TEXT(" format = ") + *Format +
				TEXT(", data = ") + ArrayData +
				TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			TArray<TSharedPtr<FJsonValue>> DataArray;
			for (auto &datum : Data)
				DataArray.Add(MakeShareable<FJsonValue>(new FJsonValueNumber(datum)));

			Object->SetObjectField("header", Header.ToJsonObject());
			Object->SetStringField(TEXT("format"), Format);
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
} // namespace sensor_msgs