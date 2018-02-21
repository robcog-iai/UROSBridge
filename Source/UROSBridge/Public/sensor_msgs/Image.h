#pragma once
#include "ROSBridgeMsg.h"
#include "std_msgs/Header.h"
#include "Base64.h"

namespace sensor_msgs
{
	class Image : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		uint32 Height;
		uint32 Width;
		FString Encoding; // reference http://docs.ros.org/kinetic/api/sensor_msgs/html/image__encodings_8h_source.html
		uint8 IsBigEndian;
		uint32 Step;
		// NB: ROSBridge encodes uint8[] as a Base64 string
		TArray<uint8> Data;

	public:

		Image()
		{
			MsgType = "sensor_msgs/Image";
		}

		Image
		(std_msgs::Header InHeader, uint32 InHeight, uint32 InWidth,
			FString InEncoding, uint8 InIsBigEndian,
			uint32 InStep, const TArray<uint8>& InData)
			:
			Header(InHeader),
			Height(InHeight),
			Width(InWidth),
			Encoding(InEncoding),
			IsBigEndian(InIsBigEndian),
			Step(InStep),
			Data(InData)
		{
			MsgType = "sensor_msgs/Image";
		}

		~Image() override {}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		uint32 GetHeight() const
		{
			return Height;
		}

		uint32 GetWidth() const
		{
			return Width;
		}

		FString GetEncoding() const
		{
			return Encoding;
		}

		uint8 GetIsBigEndian() const
		{
			return IsBigEndian;
		}

		uint32 GetStep() const
		{
			return Step;
		}

		TArray<uint8> GetData() const
		{
			return Data;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetHeight(uint32 InHeight)
		{
			Height = InHeight;
		}

		void SetWidth(uint32 InWidth)
		{
			Width = InWidth;
		}

		void SetEncoding(FString InEncoding)
		{
			Encoding = InEncoding;
		}

		void SetIsBigEndian(uint8 InIsBigEndian)
		{
			IsBigEndian = InIsBigEndian;
		}

		void SetStep(uint32 InStep)
		{
			Step = InStep;
		}

		void SetData(const TArray<uint8>& InData)
		{
			Data = InData;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
			Height = JsonObject->GetNumberField(TEXT("height"));
			Width = JsonObject->GetNumberField(TEXT("width"));
			Encoding = JsonObject->GetStringField(TEXT("encoding"));
			IsBigEndian = JsonObject->GetNumberField(TEXT("is_bigendian"));
			Step = JsonObject->GetNumberField(TEXT("step"));
			Data.Empty();
			FBase64::Decode(JsonObject->GetStringField(TEXT("data")), Data);
		}

		static Image GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Image Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			FString DataString = "[ ";
			for (auto &value : Data)
				DataString += FString::FromInt(value) + TEXT(", ");
			DataString += " ]";

			return TEXT("Image { header = ") + Header.ToString() +
				TEXT(", height = ") + FString::FromInt(Height) +
				TEXT(", width = ") + FString::FromInt(Width) +
				TEXT(", encoding =") + Encoding +
				TEXT(", is_bigendian = ") + FString::FromInt(IsBigEndian) +
				TEXT(", step = ") + FString::FromInt(Step) +
				TEXT(", data = ") + DataString +
				TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			TArray<TSharedPtr<FJsonValue>> DataArray;
			for (auto &datum : Data)
			{
				TSharedPtr<FJsonValue> Ptr = MakeShareable(new FJsonValueNumber(datum));
				DataArray.Add(Ptr);
			}

			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetNumberField(TEXT("height"), Height);
			Object->SetNumberField(TEXT("width"), Width);
			Object->SetStringField(TEXT("encoding"), Encoding);
			Object->SetNumberField(TEXT("is_bigendian"), IsBigEndian);
			Object->SetNumberField(TEXT("step"), Step);
			Object->SetStringField(TEXT("data"), *(FBase64::Encode(Data)));

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