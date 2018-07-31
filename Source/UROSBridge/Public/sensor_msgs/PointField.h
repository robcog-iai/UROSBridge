#pragma once

#include "ROSBridgeMsg.h"


namespace sensor_msgs
{
	class PointField : public FROSBridgeMsg
	{
		uint8 Int8;
		uint8 Uint8;
		uint8 Int16;
		uint8 Uint16;
		uint8 Int32;
		uint8 Uint32;
		uint8 Float32;
		uint8 Float64;
		FString Name;
		uint32 Offset;
		uint8 Datatype;
		uint32 Count;
	public:
		PointField()
		{
			MsgType = "sensor_msgs/PointField";
		}

		PointField
		(
			uint8 InInt8,
			uint8 InUint8,
			uint8 InInt16,
			uint8 InUint16,
			uint8 InInt32,
			uint8 InUint32,
			uint8 InFloat32,
			uint8 InFloat64,
			FString InName,
			uint32 InOffset,
			uint8 InDatatype,
			uint32 InCount
		):
			Int8(InInt8),
			Uint8(InUint8),
			Int16(InInt16),
			Uint16(InUint16),
			Int32(InInt32),
			Uint32(InUint32),
			Float32(InFloat32),
			Float64(InFloat64),
			Name(InName),
			Offset(InOffset),
			Datatype(InDatatype),
			Count(InCount)
		{
			MsgType = "sensor_msgs/PointField";
		}

		~PointField() override {}

		uint8 GetInt8() const
		{
			return Int8;
		}

		uint8 GetUint8() const
		{
			return Uint8;
		}

		uint8 GetInt16() const
		{
			return Int16;
		}

		uint8 GetUint16() const
		{
			return Uint16;
		}

		uint8 GetInt32() const
		{
			return Int32;
		}

		uint8 GetUint32() const
		{
			return Uint32;
		}

		uint8 GetFloat32() const
		{
			return Float32;
		}

		uint8 GetFloat64() const
		{
			return Float64;
		}

		FString GetName() const
		{
			return Name;
		}

		uint32 GetOffset() const
		{
			return Offset;
		}

		uint8 GetDatatype() const
		{
			return Datatype;
		}

		uint32 GetCount() const
		{
			return Count;
		}

		void SetInt8(uint8 InInt8)
		{
			Int8 = InInt8;
		}

		void SetUint8(uint8 InUint8)
		{
			Uint8 = InUint8;
		}

		void SetInt16(uint8 InInt16)
		{
			Int16 = InInt16;
		}

		void SetUint16(uint8 InUint16)
		{
			Uint16 = InUint16;
		}

		void SetInt32(uint8 InInt32)
		{
			Int32 = InInt32;
		}

		void SetUint32(uint8 InUint32)
		{
			Uint32 = InUint32;
		}

		void SetFloat32(uint8 InFloat32)
		{
			Float32 = InFloat32;
		}

		void SetFloat64(uint8 InFloat64)
		{
			Float64 = InFloat64;
		}

		void SetName(FString InName)
		{
			Name = InName;
		}

		void SetOffset(uint32 InOffset)
		{
			Offset = InOffset;
		}

		void SetDatatype(uint8 InDatatype)
		{
			Datatype = InDatatype;
		}

		void SetCount(uint32 InCount)
		{
			Count = InCount;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Int8 = JsonObject->GetNumberField(TEXT("int8"));

			Uint8 = JsonObject->GetNumberField(TEXT("uint8"));

			Int16 = JsonObject->GetNumberField(TEXT("int16"));

			Uint16 = JsonObject->GetNumberField(TEXT("uint16"));

			Int32 = JsonObject->GetNumberField(TEXT("int32"));

			Uint32 = JsonObject->GetNumberField(TEXT("uint32"));

			Float32 = JsonObject->GetNumberField(TEXT("float32"));

			Float64 = JsonObject->GetNumberField(TEXT("float64"));

			Name = JsonObject->GetStringField(TEXT("name"));

			Offset = JsonObject->GetNumberField(TEXT("offset"));

			Datatype = JsonObject->GetNumberField(TEXT("datatype"));

			Count = JsonObject->GetNumberField(TEXT("count"));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Int8 = BsonObject->GetNumberField(TEXT("int8"));

			Uint8 = BsonObject->GetNumberField(TEXT("uint8"));

			Int16 = BsonObject->GetNumberField(TEXT("int16"));

			Uint16 = BsonObject->GetNumberField(TEXT("uint16"));

			Int32 = BsonObject->GetNumberField(TEXT("int32"));

			Uint32 = BsonObject->GetNumberField(TEXT("uint32"));

			Float32 = BsonObject->GetNumberField(TEXT("float32"));

			Float64 = BsonObject->GetNumberField(TEXT("float64"));

			Name = BsonObject->GetStringField(TEXT("name"));

			Offset = BsonObject->GetNumberField(TEXT("offset"));

			Datatype = BsonObject->GetNumberField(TEXT("datatype"));

			Count = BsonObject->GetNumberField(TEXT("count"));

		}

		static PointField GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			PointField Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static PointField GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			PointField Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetNumberField(TEXT("int8"), Int8);
			Object->SetNumberField(TEXT("uint8"), Uint8);
			Object->SetNumberField(TEXT("int16"), Int16);
			Object->SetNumberField(TEXT("uint16"), Uint16);
			Object->SetNumberField(TEXT("int32"), Int32);
			Object->SetNumberField(TEXT("uint32"), Uint32);
			Object->SetNumberField(TEXT("float32"), Float32);
			Object->SetNumberField(TEXT("float64"), Float64);
			Object->SetStringField(TEXT("name"), Name);
			Object->SetNumberField(TEXT("offset"), Offset);
			Object->SetNumberField(TEXT("datatype"), Datatype);
			Object->SetNumberField(TEXT("count"), Count);
			return Object;
		}
		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetNumberField(TEXT("int8"), Int8);
			Object->SetNumberField(TEXT("uint8"), Uint8);
			Object->SetNumberField(TEXT("int16"), Int16);
			Object->SetNumberField(TEXT("uint16"), Uint16);
			Object->SetNumberField(TEXT("int32"), Int32);
			Object->SetNumberField(TEXT("uint32"), Uint32);
			Object->SetNumberField(TEXT("float32"), Float32);
			Object->SetNumberField(TEXT("float64"), Float64);
			Object->SetStringField(TEXT("name"), Name);
			Object->SetNumberField(TEXT("offset"), Offset);
			Object->SetNumberField(TEXT("datatype"), Datatype);
			Object->SetNumberField(TEXT("count"), Count);
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