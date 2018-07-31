#pragma once

#include "ROSBridgeMsg.h"

#include "geometry_msgs/TransformStamped.h"

namespace tf2_msgs
{
	class TFMessage : public FROSBridgeMsg
	{
		TArray<geometry_msgs::TransformStamped> Transforms;
	public:
		TFMessage()
		{
			MsgType = "tf2_msgs/TFMessage";
		}

		TFMessage
		(
			const TArray<geometry_msgs::TransformStamped>& InTransforms
		):
			Transforms(InTransforms)
		{
			MsgType = "tf2_msgs/TFMessage";
		}

		~TFMessage() override {}

		TArray<geometry_msgs::TransformStamped> GetTransforms() const
		{
			return Transforms;
		}

		void SetTransforms(TArray<geometry_msgs::TransformStamped>& InTransforms)
		{
			Transforms = InTransforms;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Transforms.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("transforms"));
			for (auto &ptr : ValuesPtrArr)
				Transforms.Add(geometry_msgs::TransformStamped::GetFromJson(ptr->AsObject()));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

			Transforms.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("transforms"));
			for (auto &ptr : ValuesPtrArr)
				Transforms.Add(geometry_msgs::TransformStamped::GetFromBson(ptr->AsObject()));

		}

		static TFMessage GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			TFMessage Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static TFMessage GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			TFMessage Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			TArray<TSharedPtr<FJsonValue>> TransformsArray;
			for (auto &val : Transforms)
				TransformsArray.Add(MakeShareable(new FJsonValueObject(val.ToJsonObject())));
			Object->SetArrayField(TEXT("transforms"), TransformsArray);
			return Object;
		}
		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			TArray<TSharedPtr<FBsonValue>> TransformsArray;
			for (auto &val : Transforms)
				TransformsArray.Add(MakeShareable(new FBsonValueObject(val.ToBsonObject())));
			Object->SetArrayField(TEXT("transforms"), TransformsArray);
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