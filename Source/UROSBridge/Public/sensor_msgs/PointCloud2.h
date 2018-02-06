#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "sensor_msgs/PointField.h"
#include "Base64.h"

class FROSBridgeMsgSensormsgsPointCloud2 : public FROSBridgeMsg
{

	FROSBridgeMsgStdmsgsHeader header;
	uint32 height;
	uint32 width;
	TArray<FROSBridgeMsgSensormsgsPointField> fields;
	bool is_bigendian;
	uint32 point_step;
	uint32 row_step;
	// NB: ROSBridge encodes uint8[] as a Base64 string
	TArray<uint8> data;
	bool is_dense;

public:

    FROSBridgeMsgSensormsgsPointCloud2()
    {
        Type = "sensor_msgs/PointCloud2";
    }

    FROSBridgeMsgSensormsgsPointCloud2
    (FROSBridgeMsgStdmsgsHeader header_, uint32 height_, uint32 width_,
		const TArray<FROSBridgeMsgSensormsgsPointField>& fields_, bool is_bigendian_,
		uint32 point_step_, uint32 row_step_, const TArray<uint8>& data_, bool is_dense_)
		:
        header(header_),
		height(height_),
		width(width_),
		fields(fields_),
		is_bigendian(is_bigendian_),
		point_step(point_step_),
		row_step(row_step_),
		data(data_),
		is_dense(is_dense_)
    {
        Type = "sensor_msgs/PointCloud2";
    }

    ~FROSBridgeMsgSensormsgsPointCloud2() override {}
	
	FROSBridgeMsgStdmsgsHeader GetHeader() const { return header; }
	uint32 GetHeight() const { return height; }
	uint32 GetWidth() const { return width; }
	TArray<FROSBridgeMsgSensormsgsPointField> GetFields() const { return fields; }
	bool GetIsBigEndian() const { return is_bigendian; }
	uint32 GetPointStep() const { return point_step; }
	uint32 GetRowStep() const { return row_step; }
	TArray<uint8> GetData() const { return data; }
	bool GetIsDense() const { return is_dense; }

	void SetHeader(FROSBridgeMsgStdmsgsHeader header_) { header = header_; }
	void SetHeight(uint32 height_) { height = height_; }
	void SetWidth(uint32 width_) { width = width_; }
	void SetFields(const TArray<FROSBridgeMsgSensormsgsPointField>& fields_) { fields = fields_; }
	void SetIsBigEndian(bool is_big_endian_) { is_bigendian = is_big_endian_; }
	void SetPointStep(uint32 point_step_) { point_step = point_step_; }
	void SetRowStep(uint32 row_step_) { row_step = row_step_; }
	void SetData(const TArray<uint8>& data_) { data = data_; }
	void SetIsDense(bool is_dense_) { is_dense = is_dense_; }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
	{
		header = FROSBridgeMsgStdmsgsHeader::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
		height = JsonObject->GetNumberField(TEXT("height"));
		width = JsonObject->GetNumberField(TEXT("width"));
		fields.Empty();
		TArray<TSharedPtr<FJsonValue>> FieldsPtrArr = JsonObject->GetArrayField(TEXT("fields"));
		for (auto &ptr : FieldsPtrArr)
			fields.Add(FROSBridgeMsgSensormsgsPointField::GetFromJson(ptr->AsObject()));
		is_bigendian = JsonObject->GetBoolField(TEXT("is_bigendian"));
		point_step = JsonObject->GetNumberField(TEXT("point_step"));
		row_step = JsonObject->GetNumberField(TEXT("row_step"));
		data.Empty();
		FBase64::Decode(JsonObject->GetStringField(TEXT("data")), data);
		is_dense = JsonObject->GetBoolField(TEXT("is_dense"));
    }

    static FROSBridgeMsgSensormsgsPointCloud2 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgSensormsgsPointCloud2 Result;
        Result.FromJson(JsonObject);
        return Result;
    }

    virtual FString ToString() const override
    {
		FString FieldsString = "[ ";
		for (auto &value : fields)
			FieldsString += value.ToString() + TEXT(", ");
		FieldsString += " ]";

		FString DataString = "[ ";
		for (auto &value : data)
			DataString += FString::FromInt(value) + TEXT(", ");
		DataString += " ]";

		return TEXT("PointCloud2 { header = ") + header.ToString() +
			TEXT(", height = ") + FString::FromInt(height) +
			TEXT(", width = ") + FString::FromInt(width) +
			TEXT(", fields = ") + FieldsString +
			TEXT(", is_bigendian = ") + FString::FromInt(is_bigendian) +
			TEXT(", point_step = ") + FString::FromInt(point_step) +
			TEXT(", row_step = ") + FString::FromInt(row_step) +
			TEXT(", data = ") + DataString +
			TEXT(", is_dense = ") + FString::FromInt(is_dense) +
			TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

		TArray<TSharedPtr<FJsonValue>> FieldsPtrArray;
		for (auto &field : fields)
		{
			TSharedPtr<FJsonValue> Ptr = MakeShareable(new FJsonValueObject(field.ToJsonObject()));
			FieldsPtrArray.Add(Ptr);
		}

		TArray<TSharedPtr<FJsonValue>> DataArray;
		for (auto &datum : data)
		{
			TSharedPtr<FJsonValue> Ptr = MakeShareable(new FJsonValueNumber(datum));
			DataArray.Add(Ptr);
		}

		Object->SetObjectField(TEXT("header"), header.ToJsonObject());
        Object->SetNumberField(TEXT("height"), height);
		Object->SetNumberField(TEXT("width"), width);
		Object->SetArrayField(TEXT("fields"), FieldsPtrArray);
		Object->SetBoolField(TEXT("is_bigendian"), is_bigendian);
		Object->SetNumberField(TEXT("point_step"), point_step);
		Object->SetNumberField(TEXT("row_step"), row_step);
		Object->SetStringField(TEXT("data"), *(FBase64::Encode(data)));
		Object->SetBoolField(TEXT("is_dense"), is_dense);

        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString;
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};
