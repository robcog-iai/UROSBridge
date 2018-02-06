#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "sensor_msgs/PointField.h"
#include "Base64.h"

namespace sensor_msgs
{
	class PointCloud2 : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		uint32 Height;
		uint32 Width;
		TArray<sensor_msgs::PointField> Fields;
		bool bIsBigEndian;
		uint32 PointStep;
		uint32 RowStep;
		// NB: ROSBridge encodes uint8[] as a Base64 string
		TArray<uint8> Data;
		bool bIsDense;

	public:

		PointCloud2()
		{
			MsgType = "sensor_msgs/PointCloud2";
		}

		PointCloud2
		(std_msgs::Header InHeader, uint32 InHeight, uint32 InWidth,
			const TArray<sensor_msgs::PointField>& InFields, bool bInIsBigEndian,
			uint32 InPointStep, uint32 InRowStep, const TArray<uint8>& InData, bool bInIsDense)
			:
			Header(InHeader),
			Height(InHeight),
			Width(InWidth),
			Fields(InFields),
			bIsBigEndian(bInIsBigEndian),
			PointStep(InPointStep),
			RowStep(InRowStep),
			Data(InData),
			bIsDense(bInIsDense)
		{
			MsgType = "sensor_msgs/PointCloud2";
		}

		~PointCloud2() override {}

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

		TArray<sensor_msgs::PointField> GetFields() const 
		{
			return Fields;
		}

		bool GetIsBigEndian() const 
		{
			return bIsBigEndian;
		}

		uint32 GetPointStep() const 
		{
			return PointStep;
		}

		uint32 GetRowStep() const 
		{
			return RowStep; 
		}

		TArray<uint8> GetData() const 
		{
			return Data; 
		}

		bool GetIsDense() const 
		{
			return bIsDense; 
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

		void SetFields(const TArray<sensor_msgs::PointField>& InFields) 
		{
			Fields = InFields; 
		}

		void SetIsBigEndian(bool bInIsBigEndian)
		{
			bIsBigEndian = bInIsBigEndian; 
		}

		void SetPointStep(uint32 InPointStep) 
		{
			PointStep = InPointStep; 
		}

		void SetRowStep(uint32 InRowStep) 
		{
			RowStep = InRowStep; 
		}

		void SetData(const TArray<uint8>& InData) 
		{
			Data = InData; 
		}

		void SetIsDense(bool bInIsDense) 
		{
			bIsDense = bInIsDense; 
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
			Height = JsonObject->GetNumberField(TEXT("height"));
			Width = JsonObject->GetNumberField(TEXT("width"));
			Fields.Empty();
			TArray<TSharedPtr<FJsonValue>> FieldsPtrArr = JsonObject->GetArrayField(TEXT("fields"));
			for (auto &ptr : FieldsPtrArr)
				Fields.Add(sensor_msgs::PointField::GetFromJson(ptr->AsObject()));
			bIsBigEndian = JsonObject->GetBoolField(TEXT("is_bigendian"));
			PointStep = JsonObject->GetNumberField(TEXT("point_step"));
			RowStep = JsonObject->GetNumberField(TEXT("row_step"));
			Data.Empty();
			FBase64::Decode(JsonObject->GetStringField(TEXT("data")), Data);
			bIsDense = JsonObject->GetBoolField(TEXT("is_dense"));
		}

		static PointCloud2 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			PointCloud2 Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			FString FieldsString = "[ ";
			for (auto &value : Fields)
				FieldsString += value.ToString() + TEXT(", ");
			FieldsString += " ]";

			FString DataString = "[ ";
			for (auto &value : Data)
				DataString += FString::FromInt(value) + TEXT(", ");
			DataString += " ]";

			return TEXT("PointCloud2 { header = ") + Header.ToString() +
				TEXT(", height = ") + FString::FromInt(Height) +
				TEXT(", width = ") + FString::FromInt(Width) +
				TEXT(", fields = ") + FieldsString +
				TEXT(", is_bigendian = ") + FString::FromInt(bIsBigEndian) +
				TEXT(", point_step = ") + FString::FromInt(PointStep) +
				TEXT(", row_step = ") + FString::FromInt(RowStep) +
				TEXT(", data = ") + DataString +
				TEXT(", is_dense = ") + FString::FromInt(bIsDense) +
				TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			TArray<TSharedPtr<FJsonValue>> FieldsPtrArray;
			for (auto &field : Fields)
			{
				TSharedPtr<FJsonValue> Ptr = MakeShareable(new FJsonValueObject(field.ToJsonObject()));
				FieldsPtrArray.Add(Ptr);
			}

			TArray<TSharedPtr<FJsonValue>> DataArray;
			for (auto &datum : Data)
			{
				TSharedPtr<FJsonValue> Ptr = MakeShareable(new FJsonValueNumber(datum));
				DataArray.Add(Ptr);
			}

			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetNumberField(TEXT("height"), Height);
			Object->SetNumberField(TEXT("width"), Width);
			Object->SetArrayField(TEXT("fields"), FieldsPtrArray);
			Object->SetBoolField(TEXT("is_bigendian"), bIsBigEndian);
			Object->SetNumberField(TEXT("point_step"), PointStep);
			Object->SetNumberField(TEXT("row_step"), RowStep);
			Object->SetStringField(TEXT("data"), *(FBase64::Encode(Data)));
			Object->SetBoolField(TEXT("is_dense"), bIsDense);

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