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
			MsgType = TEXT("geometry_msgs/PoseArray");
		}
		
		PoseArray(std_msgs::Header InHeader,
			TArray<geometry_msgs::Pose> InPoses)
			:
			Header(InHeader),
			Poses(InPoses)
		{
			MsgType = TEXT("geometry_msgs/PoseArray");
		}

		~PoseArray() override {}

		// Getters 
		std_msgs::Header GetHeader() const { return Header; }
		TArray<geometry_msgs::Pose> GetPoses() const { return Poses; }

		// DEPRECATED! Will be removed when the generator is used again.
		geometry_msgs::Pose GetPoseAt(int32 Index)
		{
			check(Index < Poses.Num());
			return Poses[Index];
		}

		// Setters 
		void SetHeader(std_msgs::Header InHeader) { Header = InHeader; }
		void SetPoses(TArray<geometry_msgs::Pose> InPoses) { Poses = InPoses; }

		// DEPRECATED! Will be removed when the generator is used again.
		void AddPose(geometry_msgs::Pose InPose)
		{
			Poses.Add(InPose);
		}

		// DEPRECATED! Will be removed when the generator is used again.
		void AppendPoses(const TArray<geometry_msgs::Pose>& InPoses)
		{
			Poses.Append(InPoses);
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			Poses.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("poses"));
			for (auto &ptr : ValuesPtrArr)
				Poses.Add(geometry_msgs::Pose::GetFromJson(ptr->AsObject()));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

			Header = std_msgs::Header::GetFromBson(BsonObject->GetObjectField(TEXT("header")));

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

		virtual FString ToString() const override
		{
							
			FString PosesString = "[ ";
			for (auto &value : Poses)
				PosesString += value.ToString() + TEXT(", ");
			PosesString += " ] ";
			return TEXT("PoseArray { header = ") + Header.ToString() +
				TEXT(", poses =") + PosesString +
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