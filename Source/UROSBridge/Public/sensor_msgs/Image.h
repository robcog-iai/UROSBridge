#pragma once

#include "ROSBridgeMsg.h"
#include "std_msgs/Header.h"


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
			MsgType = TEXT("sensor_msgs/Image");
		}
		
		Image(std_msgs::Header InHeader,
			uint32 InHeight,
			uint32 InWidth,
			FString InEncoding,
			uint8 InIsBigendian,
			uint32 InStep,
			TArray<uint8> InData)
			:
			Header(InHeader),
			Height(InHeight),
			Width(InWidth),
			Encoding(InEncoding),
			IsBigendian(InIsBigendian),
			Step(InStep),
			Data(InData)
		{
			MsgType = TEXT("sensor_msgs/Image");
		}

		~Image() override {}

		// Getters 
		std_msgs::Header GetHeader() const { return Header; }
		uint32 GetHeight() const { return Height; }
		uint32 GetWidth() const { return Width; }
		FString GetEncoding() const { return Encoding; }
		uint8 GetIsBigendian() const { return IsBigendian; }
		uint32 GetStep() const { return Step; }
		TArray<uint8> GetData() const { return Data; }

		// Setters 
		void SetHeader(std_msgs::Header InHeader) { Header = InHeader; }
		void SetHeight(uint32 InHeight) { Height = InHeight; }
		void SetWidth(uint32 InWidth) { Width = InWidth; }
		void SetEncoding(FString InEncoding) { Encoding = InEncoding; }
		void SetIsBigendian(uint8 InIsBigendian) { IsBigendian = InIsBigendian; }
		void SetStep(uint32 InStep) { Step = InStep; }
		void SetData(TArray<uint8> InData) { Data = InData; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			Height = JsonObject->GetNumberField(TEXT("height"));

			Width = JsonObject->GetNumberField(TEXT("width"));

			Encoding = JsonObject->GetStringField(TEXT("encoding"));

			IsBigendian = JsonObject->GetNumberField(TEXT("is_bigendian"));

			Step = JsonObject->GetNumberField(TEXT("step"));

			Data.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("data"));
			for (auto &ptr : ValuesPtrArr)
				Data.Add(ptr->AsNumber());

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

			Header = std_msgs::Header::GetFromBson(BsonObject->GetObjectField(TEXT("header")));

			Height = BsonObject->GetNumberField(TEXT("height"));

			Width = BsonObject->GetNumberField(TEXT("width"));

			Encoding = BsonObject->GetStringField(TEXT("encoding"));

			IsBigendian = BsonObject->GetNumberField(TEXT("is_bigendian"));

			Step = BsonObject->GetNumberField(TEXT("step"));

			Data.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("data"));
			for (auto &ptr : ValuesPtrArr)
				Data.Add(ptr->AsNumber());

		}

		static Image GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Image Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static Image GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			Image Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());

			Object->SetNumberField(TEXT("height"), Height);

			Object->SetNumberField(TEXT("width"), Width);

			Object->SetStringField(TEXT("encoding"), Encoding);

			Object->SetNumberField(TEXT("is_bigendian"), IsBigendian);

			Object->SetNumberField(TEXT("step"), Step);

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

			Object->SetNumberField(TEXT("height"), Height);

			Object->SetNumberField(TEXT("width"), Width);

			Object->SetStringField(TEXT("encoding"), Encoding);

			Object->SetNumberField(TEXT("is_bigendian"), IsBigendian);

			Object->SetNumberField(TEXT("step"), Step);

			TArray<TSharedPtr<FBsonValue>> DataArray;
			for (auto &val : Data)
				DataArray.Add(MakeShareable(new FBsonValueNumber(val)));
			Object->SetArrayField(TEXT("data"), DataArray);

			return Object;

		}

		virtual FString ToString() const override
		{
							
			FString DataString = "[ ";
			for (auto &value : Data)
				DataString += FString::FromInt(value) + TEXT(", ");
			DataString += " ] ";
			return TEXT("Image { header = ") + Header.ToString() +
				TEXT(", height = ") + FString::FromInt(Height) +
				TEXT(", width = ") + FString::FromInt(Width) +
				TEXT(", encoding = ") + Encoding +
				TEXT(", is_bigendian = ") + FString::FromInt(IsBigendian) +
				TEXT(", step = ") + FString::FromInt(Step) +
				TEXT(", data =") + DataString +
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