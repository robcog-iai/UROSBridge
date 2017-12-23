// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once
#include "ROSBridgeMsg.h"

#include "geometry_msgs/TransformStamped.h"

class FROSBridgeMsgTF2msgsTFMessage : public FROSBridgeMsg
{
public:
	TArray<FROSBridgeMsgGeometrymsgsTransformStamped> Transforms;

	FROSBridgeMsgTF2msgsTFMessage()
	{
		Type = "tf2_msgs/TFMessage";
	}

	FROSBridgeMsgTF2msgsTFMessage
	(const TArray<FROSBridgeMsgGeometrymsgsTransformStamped>& InTransforms)
	{
		Type = "tf2_msgs/TFMessage";
		for (int i = 0; i < InTransforms.Num(); i++)
		{
			Transforms.Add(InTransforms[i]);
		}
	}

	~FROSBridgeMsgTF2msgsTFMessage() override {}

	TArray<FROSBridgeMsgGeometrymsgsTransformStamped> GetTFMessages() const
	{
		return Transforms;
	}

	FROSBridgeMsgGeometrymsgsTransformStamped GetTFMessageAt(int32 Index)
	{
		check(Index < Transforms.Num());
		return Transforms[Index];
	}

	void AddTransform(FROSBridgeMsgGeometrymsgsTransformStamped InTransform)
	{
		Transforms.Add(InTransform);
	}

	void SetTFMessages(const TArray<FROSBridgeMsgGeometrymsgsTransformStamped>& InTransforms)
	{
		for (int i = 0; i < InTransforms.Num(); i++)
		{
			Transforms.Add(InTransforms[i]);
		}
	}

	virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
		TArray<TSharedPtr<FJsonValue>> TransformsPtrArray = JsonObject->GetArrayField(TEXT("transforms"));
		for (auto &ptr : TransformsPtrArray)
		{
			FROSBridgeMsgGeometrymsgsTransformStamped Transform =
				FROSBridgeMsgGeometrymsgsTransformStamped::GetFromJson(ptr->AsObject());
			Transforms.Add(Transform);
		}
	}

	static FROSBridgeMsgTF2msgsTFMessage GetFromJson(TSharedPtr<FJsonObject> JsonObject)
	{
		FROSBridgeMsgTF2msgsTFMessage Result;
		Result.FromJson(JsonObject);
		return Result;
	}

	virtual FString ToString() const override
	{
		FString ArrayString = "[ ";
		for (auto &Transform : Transforms)
			ArrayString += Transform.ToString() + TEXT(", ");
		ArrayString += " ]";

		return TEXT("TFMessage { transforms = ") + ArrayString + TEXT(" } ");
	}

	virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
		TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
		TArray<TSharedPtr<FJsonValue>> TransformsPtrArray;
		for (auto &Transform : Transforms)
		{
			TSharedPtr<FJsonValue> Ptr = MakeShareable(new FJsonValueObject(Transform.ToJsonObject()));
			TransformsPtrArray.Add(Ptr);
		}

		Object->SetArrayField("transforms", TransformsPtrArray);
		return Object;
	}

	virtual FString ToYamlString() const override {
		FString OutputString;
		TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
		return OutputString;
	}
};
