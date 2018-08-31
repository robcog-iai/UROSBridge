#pragma once

#include "ROSBridgeMsg.h"
#include "std_msgs/Header.h"
#include "sensor_msgs/PointField.h"


namespace sensor_msgs
{
	class PointCloud2 : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		uint32 Height;
		uint32 Width;
		TArray<sensor_msgs::PointField> Fields;
		bool IsBigendian;
		uint32 PointStep;
		uint32 RowStep;
		TArray<uint8> Data;
		bool IsDense;
	public:
		PointCloud2()
		{
			MsgType = TEXT("sensor_msgs/PointCloud2");
		}
		
		PointCloud2(std_msgs::Header InHeader,
			uint32 InHeight,
			uint32 InWidth,
			TArray<sensor_msgs::PointField> InFields,
			bool InIsBigendian,
			uint32 InPointStep,
			uint32 InRowStep,
			TArray<uint8> InData,
			bool InIsDense)
			:
			Header(InHeader),
			Height(InHeight),
			Width(InWidth),
			Fields(InFields),
			IsBigendian(InIsBigendian),
			PointStep(InPointStep),
			RowStep(InRowStep),
			Data(InData),
			IsDense(InIsDense)
		{
			MsgType = TEXT("sensor_msgs/PointCloud2");
		}

		~PointCloud2() override {}

		// Getters 
		std_msgs::Header GetHeader() const { return Header; }
		uint32 GetHeight() const { return Height; }
		uint32 GetWidth() const { return Width; }
		TArray<sensor_msgs::PointField> GetFields() const { return Fields; }
		bool GetIsBigendian() const { return IsBigendian; }
		
		// DEPRECATED! Will be removed when the generator is used again. Use GetIsBigendian instead.
		bool GetIsBigEndian() const { return IsBigendian; }
		
		uint32 GetPointStep() const { return PointStep; }
		uint32 GetRowStep() const { return RowStep; }
		TArray<uint8> GetData() const { return Data; }
		bool GetIsDense() const { return IsDense; }

		// Setters 
		void SetHeader(std_msgs::Header InHeader) { Header = InHeader; }
		void SetHeight(uint32 InHeight) { Height = InHeight; }
		void SetWidth(uint32 InWidth) { Width = InWidth; }
		void SetFields(TArray<sensor_msgs::PointField> InFields) { Fields = InFields; }
		void SetIsBigendian(bool InIsBigendian) { IsBigendian = InIsBigendian; }

		// DEPRECATED! Will be removed when the generator is used again. Use SetIsBigendian instead.
		void SetIsBigendian(bool InIsBigendian) { IsBigendian = InIsBigendian; }

		void SetPointStep(uint32 InPointStep) { PointStep = InPointStep; }
		void SetRowStep(uint32 InRowStep) { RowStep = InRowStep; }
		void SetData(TArray<uint8> InData) { Data = InData; }
		void SetIsDense(bool InIsDense) { IsDense = InIsDense; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			Height = JsonObject->GetNumberField(TEXT("height"));

			Width = JsonObject->GetNumberField(TEXT("width"));

			Fields.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("fields"));
			for (auto &ptr : ValuesPtrArr)
				Fields.Add(sensor_msgs::PointField::GetFromJson(ptr->AsObject()));

			IsBigendian = JsonObject->GetBoolField(TEXT("is_bigendian"));

			PointStep = JsonObject->GetNumberField(TEXT("point_step"));

			RowStep = JsonObject->GetNumberField(TEXT("row_step"));

			Data.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("data"));
			for (auto &ptr : ValuesPtrArr)
				Data.Add(ptr->AsNumber());

			IsDense = JsonObject->GetBoolField(TEXT("is_dense"));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

			Header = std_msgs::Header::GetFromBson(BsonObject->GetObjectField(TEXT("header")));

			Height = BsonObject->GetNumberField(TEXT("height"));

			Width = BsonObject->GetNumberField(TEXT("width"));

			Fields.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("fields"));
			for (auto &ptr : ValuesPtrArr)
				Fields.Add(sensor_msgs::PointField::GetFromBson(ptr->AsObject()));

			IsBigendian = BsonObject->GetBoolField(TEXT("is_bigendian"));

			PointStep = BsonObject->GetNumberField(TEXT("point_step"));

			RowStep = BsonObject->GetNumberField(TEXT("row_step"));

			Data.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("data"));
			for (auto &ptr : ValuesPtrArr)
				Data.Add(ptr->AsNumber());

			IsDense = BsonObject->GetBoolField(TEXT("is_dense"));

		}

		static PointCloud2 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			PointCloud2 Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static PointCloud2 GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			PointCloud2 Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());

			Object->SetNumberField(TEXT("height"), Height);

			Object->SetNumberField(TEXT("width"), Width);

			TArray<TSharedPtr<FJsonValue>> FieldsArray;
			for (auto &val : Fields)
				FieldsArray.Add(MakeShareable(new FJsonValueObject(val.ToJsonObject())));
			Object->SetArrayField(TEXT("fields"), FieldsArray);

			Object->SetBoolField(TEXT("is_bigendian"), IsBigendian);

			Object->SetNumberField(TEXT("point_step"), PointStep);

			Object->SetNumberField(TEXT("row_step"), RowStep);

			TArray<TSharedPtr<FJsonValue>> DataArray;
			for (auto &val : Data)
				DataArray.Add(MakeShareable(new FJsonValueNumber(val)));
			Object->SetArrayField(TEXT("data"), DataArray);

			Object->SetBoolField(TEXT("is_dense"), IsDense);

			return Object;

		}

		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToBsonObject());

			Object->SetNumberField(TEXT("height"), Height);

			Object->SetNumberField(TEXT("width"), Width);

			TArray<TSharedPtr<FBsonValue>> FieldsArray;
			for (auto &val : Fields)
				FieldsArray.Add(MakeShareable(new FBsonValueObject(val.ToBsonObject())));
			Object->SetArrayField(TEXT("fields"), FieldsArray);

			Object->SetBoolField(TEXT("is_bigendian"), IsBigendian);

			Object->SetNumberField(TEXT("point_step"), PointStep);

			Object->SetNumberField(TEXT("row_step"), RowStep);

			TArray<TSharedPtr<FBsonValue>> DataArray;
			for (auto &val : Data)
				DataArray.Add(MakeShareable(new FBsonValueNumber(val)));
			Object->SetArrayField(TEXT("data"), DataArray);

			Object->SetBoolField(TEXT("is_dense"), IsDense);

			return Object;

		}

		virtual FString ToString() const override
		{
							
			FString FieldsString = "[ ";
			for (auto &value : Fields)
				FieldsString += value.ToString() + TEXT(", ");
			FieldsString += " ] ";
			FString DataString = "[ ";
			for (auto &value : Data)
				DataString += FString::FromInt(value) + TEXT(", ");
			DataString += " ] ";
			return TEXT("PointCloud2 { header = ") + Header.ToString() +
				TEXT(", height = ") + FString::FromInt(Height) +
				TEXT(", width = ") + FString::FromInt(Width) +
				TEXT(", fields =") + FieldsString +
				TEXT(", is_bigendian = ") + FString::FromInt(IsBigendian) +
				TEXT(", point_step = ") + FString::FromInt(PointStep) +
				TEXT(", row_step = ") + FString::FromInt(RowStep) +
				TEXT(", data =") + DataString +
				TEXT(", is_dense = ") + FString::FromInt(IsDense) +
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