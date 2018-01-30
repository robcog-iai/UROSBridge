#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "sensor_msgs/PointField.h"

/* Raw definition for sensor_msgs/PointCloud2

# This message holds a collection of N-dimensional points, which may
# contain additional information such as normals, intensity, etc. The
# point data is stored as a binary blob, its layout described by the
# contents of the "fields" array.

# The point cloud data may be organized 2d (image-like) or 1d
# (unordered). Point clouds organized as 2d images may be produced by
# camera depth sensors such as stereo or time-of-flight.

# Time of sensor data acquisition, and the coordinate frame ID (for 3d
# points).
Header header

# 2D structure of the point cloud. If the cloud is unordered, height is
# 1 and width is the length of the point cloud.
uint32 height
uint32 width

# Describes the channels and their layout in the binary data blob.
PointField[] fields

bool    is_bigendian # Is this data bigendian?
uint32  point_step   # Length of a point in bytes
uint32  row_step     # Length of a row in bytes
uint8[] data         # Actual point data, size is (row_step*height)

bool is_dense        # True if there are no invalid points

*/


class FROSBridgeMsgSensormsgsPointCloud2 : public FROSBridgeMsg
{

	FROSBridgeMsgStdmsgsHeader header;
	uint32 height;
	uint32 width;
	TArray<FROSBridgeMsgSensormsgsPointField> fields;
	bool is_bigendian;
	uint32 point_step;
	uint32 row_step;
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
			fields.Add(FROSBridgeMsgSensormsgsPointField::GetFromJson(ptr->AsObject));
		is_bigendian = JsonObject->GetBoolField(TEXT("is_bigendian"));
		point_step = JsonObject->GetNumberField(TEXT("point_step"));
		row_step = JsonObject->GetNumberField(TEXT("row_step"));
		data.Empty();
		TArray<TSharedPtr<FJsonValue>> DataPtrArr = JsonObject->GetArrayField(TEXT("data"));
		for (auto &ptr : DataPtrArr)
			data.Add(ptr->AsNumber);
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
			DataString += FString::SanitizeFloat(value) + TEXT(", ");
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

		TArray<TSharedPtr<FJsonValue>> FieldsArray;
		for (auto &field : fields)
			FieldsArray.Add(MakeShareable<FJsonValue>(new FJsonValueObject(field.ToJsonObject())));

		TArray<TSharedPtr<FJsonValue>> DataArray;
		for (auto &datum : data)
			DataArray.Add(MakeShareable<FJsonValue>(new FJsonValueNumber(datum)));

		Object->SetObjectField(TEXT("header"), header.ToJsonObject());
        Object->SetNumberField(TEXT("height"), height);
		Object->SetNumberField(TEXT("width"), width);
		Object->SetArrayField(TEXT("fields"), FieldsArray);
		Object->SetBoolField(TEXT("is_bigendian"), is_bigendian);
		Object->SetNumberField(TEXT("point_step"), point_step);
		Object->SetNumberField(TEXT("row_step"), row_step);
		Object->SetArrayField(TEXT("data"), DataArray);
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
