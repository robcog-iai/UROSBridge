#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "std_msgs/String.h"

namespace sensor_msgs
{
	class Image : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		uint32 Height;
		uint32 Width;
		FString Encoding;
		uint8 IsBigendian;
		uint32 Step;
		TArray<uint8> Data;

	public:
		Image()
		{
			MsgType = "sensor_msgs/Image";
		}

		Image
		(std_msgs::Header InHeader, uint32 InHeight,
			uint32 InWidth, FString InEncoding, uint8 InIsBigendian,
			uint32 InStep, TArray<uint8> InData) :
			Header(InHeader), Height(InHeight), Width(InWidth),
			Encoding(InEncoding), IsBigendian(InIsBigendian),
			Step(InStep), Data(InData)
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

		uint8 GetIsBigendian() const
		{
			return IsBigendian;
		}

		uint32 GetStep() const
		{
			return Step;
		}

		TArray<uint8> GetData() const
		{
			return Data;
		}

		void SetHeader(const std_msgs::Header & InHeaders)
		{
			Header = InHeaders;
		}

		void SetHeight(const uint32 & InHeight)
		{
			Height = InHeight;
		}

		void SetWidth(const uint32 & InWidth)
		{
			Width = InWidth;
		}

		void SetEncoding(const FString & InEncoding)
		{
			Encoding = InEncoding;
		}

		void SetIsBigendian(uint8 InIsBigendian)
		{
			IsBigendian = InIsBigendian;
		}

		void SetStep(const uint32 InStep)
		{
			Step = InStep;
		}

		void SetData(const TArray<uint8> & InData)
		{
			Data = InData;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
			
			Height = JsonObject->GetNumberField(TEXT("height"));
			Width = JsonObject->GetNumberField(TEXT("width"));
			Encoding = JsonObject->GetStringField(TEXT("encoding"));
			IsBigendian = JsonObject->GetNumberField(TEXT("is_bigendian"));
			Step = JsonObject->GetNumberField(TEXT("step"));

			Data.Empty();
			TArray<TSharedPtr<FJsonValue>> DataPtrArr;
			DataPtrArr = JsonObject->GetArrayField(TEXT("data"));
			for (auto &ptr : DataPtrArr)
				Data.Add(ptr->AsNumber());
		}

		static Image GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Image Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			FString ArrayData = "[ ";
			for (auto &datum : Data)
				ArrayData += FString::FromInt(datum) + TEXT(", ");
			ArrayData += " ]";

			return TEXT("Image { height = ") + FString::FromInt(Height) +
				TEXT(", width = ") + FString::FromInt(Width) +
				TEXT(", encoding = ") + *Encoding +
				TEXT(", is_bigendian = ") + FString::FromInt(IsBigendian) +
				TEXT(", step = ") + FString::FromInt(Step) +
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
			Object->SetNumberField(TEXT("height"), Height);
			Object->SetNumberField(TEXT("width"), Width);
			Object->SetStringField(TEXT("encoding"), Encoding);
			Object->SetNumberField(TEXT("is_bigendian"), IsBigendian);
			Object->SetNumberField(TEXT("step"), Step);
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