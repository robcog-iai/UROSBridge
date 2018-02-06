// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

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

		TFMessage(const TArray<geometry_msgs::TransformStamped>& InTransforms)
		{
			MsgType = "tf2_msgs/TFMessage";
			for (int i = 0; i < InTransforms.Num(); i++)
			{
				Transforms.Add(InTransforms[i]);
			}
		}

		~TFMessage() override {}

		TArray<geometry_msgs::TransformStamped> GetTransforms() const
		{
			return Transforms;
		}

		geometry_msgs::TransformStamped GetTransformAt(int32 Index)
		{
			check(Index < Transforms.Num());
			return Transforms[Index];
		}

		void SetTransforms(const TArray<geometry_msgs::TransformStamped>& InTransforms)
		{
			Transforms = InTransforms;
		}

		void AddTransform(geometry_msgs::TransformStamped InTransform)
		{
			Transforms.Add(InTransform);
		}

		void AppendTransforms(const TArray<geometry_msgs::TransformStamped>& InTransforms)
		{
			Transforms.Append(InTransforms);
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			TArray<TSharedPtr<FJsonValue>> TransformsPtrArray = JsonObject->GetArrayField(TEXT("transforms"));
			for (auto &ptr : TransformsPtrArray)
			{
				geometry_msgs::TransformStamped Transform =
					geometry_msgs::TransformStamped::GetFromJson(ptr->AsObject());
				Transforms.Add(Transform);
			}
		}

		static TFMessage GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			TFMessage Result;
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

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
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

		virtual FString ToYamlString() const override 
		{
			FString OutputString;
			TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
			FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
			return OutputString;
		}
	};
}; // tf2_msgs namespace
