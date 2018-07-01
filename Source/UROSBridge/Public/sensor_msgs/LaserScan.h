// Copyright 2018 Kannan Thambiah. All rights reserved.
#pragma once
#include "ROSBridgeMsg.h"
#include "std_msgs/Header.h"

namespace sensor_msgs
{
	class LaserScan : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		float AngleMin;
		float AngleMax;
		float AngleIncrement;
		float TimeIncrement;
		float ScanTime;
		float RangeMin;
		float RangeMax;
		TArray<float> Ranges;
		TArray<float> Intensities;

		public:
		LaserScan()
		{
			MsgType = "sensor_msgs/LaserScan";
		}

		LaserScan
			(std_msgs::Header InHeader, float InAngleMin, float InAngleMax, float InAngleIncrement, float InTimeIncrement,
			 float InScanTime, float InRangeMin, float InRangeMax, TArray<float> const &InRanges, TArray<float> const &InIntensities)
			:
				Header(InHeader),
				AngleMin(InAngleMin),
				AngleMax(InAngleMax),
				AngleIncrement(InAngleIncrement),
				TimeIncrement(InTimeIncrement),
				ScanTime(InScanTime),
				RangeMin(InRangeMin),
				RangeMax(InRangeMax),
				Ranges(InRanges),
				Intensities(InIntensities)
		{
			MsgType = "sensor_msgs/LaserScan";
		}

		~LaserScan() override {}

		//--- Getters ---//
		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		float GetAngleMin() const
		{
			return AngleMin;
		}

		float GetAngleMax() const
		{
			return AngleMax;
		}

		float GetAngleIncrement() const
		{
			return AngleIncrement;
		}

		float GetTimeIncrement() const
		{
			return TimeIncrement;
		}

		float GetScanTime() const
		{
			return ScanTime;
		}

		float GetRangeMin() const
		{
			return RangeMin;
		}

		float GetRangeMax() const
		{
			return RangeMax;
		}

		TArray<float> GetRanges() const
		{
			return Ranges;
		}

		TArray<float> GetIntensities() const
		{
			return Intensities;
		}

		//--- Setters ---//
		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetAngleMin(float InAngleMin)
		{
			AngleMin = InAngleMin;
		}

		void SetAngleMax(float InAngleMax)
		{
			AngleMax = InAngleMax;
		}

		void SetAngleIncrement(float InAngleIncrement)
		{
			AngleIncrement = InAngleIncrement;
		}

		void SetTimeIncrement(float InTimeIncrement)
		{
			TimeIncrement = InTimeIncrement;
		}

		void SetScanTime(float InScanTime)
		{
			ScanTime = InScanTime;
		}

		void SetRangeMin(float InRangeMin)
		{
			RangeMin = InRangeMin;
		}

		void SetRangeMax(float InRangeMax)
		{
			RangeMax = InRangeMax;
		}

		void SetRanges(TArray<float> const &InRanges)
		{
			Ranges = InRanges;
		}

		void SetIntensities(TArray<float> const &InIntensities)
		{
			Intensities = InIntensities;
		}

		//--- methods ---//
		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			// Scalar values
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			AngleMin = JsonObject->GetNumberField(TEXT("angle_min"));
			AngleMax = JsonObject->GetNumberField(TEXT("angle_max"));
			AngleIncrement = JsonObject->GetNumberField(TEXT("angle_increment"));
			TimeIncrement = JsonObject->GetNumberField(TEXT("time_increment"));
			ScanTime = JsonObject->GetNumberField(TEXT("scan_time"));
			RangeMin = JsonObject->GetNumberField(TEXT("range_min"));
			RangeMax = JsonObject->GetNumberField(TEXT("range_max"));

			// Arrays
			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Ranges.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("ranges"));
			for (auto &ptr : ValuesPtrArr)
			{
				Ranges.Add(ptr->AsNumber());
			}

			Intensities.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("intensities"));
			for (auto &ptr : ValuesPtrArr)
			{
				Intensities.Add(ptr->AsNumber());
			}
		}

		static LaserScan GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			LaserScan Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			// Construct Array strings
			FString RangesString = "[ ";
			for (auto &value : Ranges)
			{
				RangesString += FString::SanitizeFloat(value) + TEXT(", ");
			}
			RangesString += "] ";

			FString IntensitiesString = "[ ";
			for (auto &value : Intensities)
			{
				IntensitiesString += FString::SanitizeFloat(value) + TEXT(", ");
			}

			return TEXT("LaserScan { header = ") + Header.ToString() +
				TEXT(", angle_min = ") + FString::FromInt(AngleMin) +
				TEXT(", angle_max = ") + FString::FromInt(AngleMax) +
				TEXT(", angle_increment = ") + FString::FromInt(AngleIncrement) +
				TEXT(", time_increment = ") + FString::FromInt(TimeIncrement) +
				TEXT(", scan_time = ") + FString::FromInt(ScanTime) +
				TEXT(", range_min = ") + FString::FromInt(RangeMin) +
				TEXT(", range_max = ") + FString::FromInt(RangeMax) +
				TEXT(", ranges = ") + RangesString  +
				TEXT(", intensities = ") + IntensitiesString +
				TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			// Construct Arrays
			TArray<TSharedPtr<FJsonValue>> RangesArray, IntensitiesArray;
			for (auto &range : Ranges)
			{
				RangesArray.Add(MakeShareable(new FJsonValueNumber(range)));
			}
			for (auto &intensity : Intensities)
			{
				IntensitiesArray.Add(MakeShareable(new FJsonValueNumber(intensity)));
			}

			// Construct JSON
			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetNumberField(TEXT("angle_min"), AngleMin);
			Object->SetNumberField(TEXT("angle_max"), AngleMax);
			Object->SetNumberField(TEXT("angle_increment"), AngleIncrement);
			Object->SetNumberField(TEXT("time_increment"), TimeIncrement);
			Object->SetNumberField(TEXT("scan_time"), ScanTime);
			Object->SetNumberField(TEXT("range_min"), RangeMin);
			Object->SetNumberField(TEXT("range_max"), RangeMax);
			Object->SetArrayField(TEXT("ranges"), RangesArray);
			Object->SetArrayField(TEXT("intensities"), IntensitiesArray);

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
} // namespace sensor_msgs
