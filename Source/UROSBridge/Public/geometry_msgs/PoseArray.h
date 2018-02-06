#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Pose.h"

namespace geometry_msgs
{
	class PoseArray : FROSBridgeMsg
	{
	public:
		std_msgs::Header Header;
		TArray<geometry_msgs::Pose> Poses;

		PoseArray()
		{
			MsgType = "geometry_msgs/PoseArray";
		}

		PoseArray
		(std_msgs::Header InHeader, const TArray<geometry_msgs::Pose>& InPoses) :
			Header(InHeader), Poses(InPoses)
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

		geometry_msgs::Pose GetPoseAt(int32 Index)
		{
			check(Index < Poses.Num());
			return Poses[Index];
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetPoses(const TArray<geometry_msgs::Pose>& InPoses)
		{
			Poses = InPoses;
		}

		void AddPose(geometry_msgs::Pose InPose)
		{
			Poses.Add(InPose);
		}

		void AppendPoses(const TArray<geometry_msgs::Pose>& InPoses)
		{
			Poses.Append(InPoses);
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
			TArray<TSharedPtr<FJsonValue>> PosesPtrArray = JsonObject->GetArrayField(TEXT("poses"));
			for (auto &PoseItr : PosesPtrArray)
			{
				geometry_msgs::Pose Pose =
					geometry_msgs::Pose::GetFromJson(PoseItr->AsObject());
				Poses.Add(Pose);
			}
		}

		static PoseArray GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			PoseArray Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			FString ArrayString = "[ ";
			for (auto &Pose : Poses)
				ArrayString += Pose.ToString() + TEXT(", ");
			ArrayString += " ]";

			return TEXT("PoseArray { header = ") + Header.ToString() +
				TEXT(", poses = ") + ArrayString + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			TArray<TSharedPtr<FJsonValue>> PosePtrArray;
			for (auto &Pose : Poses)
			{
				TSharedPtr<FJsonValue> Ptr = MakeShareable(new FJsonValueObject(Pose.ToJsonObject()));
				PosePtrArray.Add(Ptr);
			}

			Object->SetArrayField("poses", PosePtrArray);
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
} // namespace geometry_msgs
