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
		(
			std_msgs::Header InHeader,
			float InAngleMin,
			float InAngleMax,
			float InAngleIncrement,
			float InTimeIncrement,
			float InScanTime,
			float InRangeMin,
			float InRangeMax,
			const TArray<float>& InRanges,
			const TArray<float>& InIntensities
		):
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

		void SetRanges(const TArray<float>& InRanges)
		{
			Ranges = InRanges;
		}

		void SetIntensities(const TArray<float>& InIntensities)
		{
			Intensities = InIntensities;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			AngleMin = JsonObject->GetNumberField(TEXT("angle_min"));

			AngleMax = JsonObject->GetNumberField(TEXT("angle_max"));

			AngleIncrement = JsonObject->GetNumberField(TEXT("angle_increment"));

			TimeIncrement = JsonObject->GetNumberField(TEXT("time_increment"));

			ScanTime = JsonObject->GetNumberField(TEXT("scan_time"));

			RangeMin = JsonObject->GetNumberField(TEXT("range_min"));

			RangeMax = JsonObject->GetNumberField(TEXT("range_max"));

			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Ranges.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("ranges"));
			for (auto &ptr : ValuesPtrArr)
				Ranges.Add(ptr->AsNumber());

			Intensities.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("intensities"));
			for (auto &ptr : ValuesPtrArr)
				Intensities.Add(ptr->AsNumber());

		}

		static LaserScan GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			LaserScan Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetNumberField(TEXT("angle_min"), AngleMin);
			Object->SetNumberField(TEXT("angle_max"), AngleMax);
			Object->SetNumberField(TEXT("angle_increment"), AngleIncrement);
			Object->SetNumberField(TEXT("time_increment"), TimeIncrement);
			Object->SetNumberField(TEXT("scan_time"), ScanTime);
			Object->SetNumberField(TEXT("range_min"), RangeMin);
			Object->SetNumberField(TEXT("range_max"), RangeMax);
			TArray<TSharedPtr<FJsonValue>> RangesArray;
			for (auto &val : Ranges)
				RangesArray.Add(MakeShareable(new FJsonValueNumber(val)));
			Object->SetArrayField(TEXT("ranges"), RangesArray);
			TArray<TSharedPtr<FJsonValue>> IntensitiesArray;
			for (auto &val : Intensities)
				IntensitiesArray.Add(MakeShareable(new FJsonValueNumber(val)));
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
}