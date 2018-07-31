#pragma once

#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Pose.h"

namespace geometry_msgs
{
	class PoseArray : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		TArray<geometry_msgs::Pose> Poses;
	public:
		PoseArray()
		{
			MsgType = "geometry_msgs/PoseArray";
		}

		PoseArray
		(
			std_msgs::Header InHeader,
			const TArray<geometry_msgs::Pose>& InPoses
		):
			Header(InHeader),
			Poses(InPoses)
		{
			MsgType = "geometry_msgs/PoseArray";
		}

		~PoseArray() override {}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		TArray<geometry_msgs::Pose> GetPoses() const
		{
			return Poses;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetPoses(TArray<geometry_msgs::Pose>& InPoses)
		{
			Poses = InPoses;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Poses.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("poses"));
			for (auto &ptr : ValuesPtrArr)
				Poses.Add(geometry_msgs::Pose::GetFromJson(ptr->AsObject()));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Header = std_msgs::Header::GetFromBson(BsonObject->GetObjectField(TEXT("header")));

			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

			Poses.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("poses"));
			for (auto &ptr : ValuesPtrArr)
				Poses.Add(geometry_msgs::Pose::GetFromBson(ptr->AsObject()));

		}

		static PoseArray GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			PoseArray Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static PoseArray GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			PoseArray Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			TArray<TSharedPtr<FJsonValue>> PosesArray;
			for (auto &val : Poses)
				PosesArray.Add(MakeShareable(new FJsonValueObject(val.ToJsonObject())));
			Object->SetArrayField(TEXT("poses"), PosesArray);
			return Object;
		}
		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToBsonObject());
			TArray<TSharedPtr<FBsonValue>> PosesArray;
			for (auto &val : Poses)
				PosesArray.Add(MakeShareable(new FBsonValueObject(val.ToBsonObject())));
			Object->SetArrayField(TEXT("poses"), PosesArray);
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