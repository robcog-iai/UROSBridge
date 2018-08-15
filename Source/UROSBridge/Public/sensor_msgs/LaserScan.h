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
			MsgType = TEXT("sensor_msgs/LaserScan");
		}
		
		LaserScan(std_msgs::Header InHeader,
			float InAngleMin,
			float InAngleMax,
			float InAngleIncrement,
			float InTimeIncrement,
			float InScanTime,
			float InRangeMin,
			float InRangeMax,
			TArray<float> InRanges,
			TArray<float> InIntensities)
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
			MsgType = TEXT("sensor_msgs/LaserScan");
		}

		~LaserScan() override {}

		// Getters 
		std_msgs::Header GetHeader() const { return Header; }
		float GetAngleMin() const { return AngleMin; }
		float GetAngleMax() const { return AngleMax; }
		float GetAngleIncrement() const { return AngleIncrement; }
		float GetTimeIncrement() const { return TimeIncrement; }
		float GetScanTime() const { return ScanTime; }
		float GetRangeMin() const { return RangeMin; }
		float GetRangeMax() const { return RangeMax; }
		TArray<float> GetRanges() const { return Ranges; }
		TArray<float> GetIntensities() const { return Intensities; }

		// Setters 
		void SetHeader(std_msgs::Header InHeader) { Header = InHeader; }
		void SetAngleMin(float InAngleMin) { AngleMin = InAngleMin; }
		void SetAngleMax(float InAngleMax) { AngleMax = InAngleMax; }
		void SetAngleIncrement(float InAngleIncrement) { AngleIncrement = InAngleIncrement; }
		void SetTimeIncrement(float InTimeIncrement) { TimeIncrement = InTimeIncrement; }
		void SetScanTime(float InScanTime) { ScanTime = InScanTime; }
		void SetRangeMin(float InRangeMin) { RangeMin = InRangeMin; }
		void SetRangeMax(float InRangeMax) { RangeMax = InRangeMax; }
		void SetRanges(TArray<float> InRanges) { Ranges = InRanges; }
		void SetIntensities(TArray<float> InIntensities) { Intensities = InIntensities; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			AngleMin = JsonObject->GetNumberField(TEXT("angle_min"));

			AngleMax = JsonObject->GetNumberField(TEXT("angle_max"));

			AngleIncrement = JsonObject->GetNumberField(TEXT("angle_increment"));

			TimeIncrement = JsonObject->GetNumberField(TEXT("time_increment"));

			ScanTime = JsonObject->GetNumberField(TEXT("scan_time"));

			RangeMin = JsonObject->GetNumberField(TEXT("range_min"));

			RangeMax = JsonObject->GetNumberField(TEXT("range_max"));

			Ranges.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("ranges"));
			for (auto &ptr : ValuesPtrArr)
				Ranges.Add(ptr->AsNumber());

			Intensities.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("intensities"));
			for (auto &ptr : ValuesPtrArr)
				Intensities.Add(ptr->AsNumber());

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

			Header = std_msgs::Header::GetFromBson(BsonObject->GetObjectField(TEXT("header")));

			AngleMin = BsonObject->GetNumberField(TEXT("angle_min"));

			AngleMax = BsonObject->GetNumberField(TEXT("angle_max"));

			AngleIncrement = BsonObject->GetNumberField(TEXT("angle_increment"));

			TimeIncrement = BsonObject->GetNumberField(TEXT("time_increment"));

			ScanTime = BsonObject->GetNumberField(TEXT("scan_time"));

			RangeMin = BsonObject->GetNumberField(TEXT("range_min"));

			RangeMax = BsonObject->GetNumberField(TEXT("range_max"));

			Ranges.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("ranges"));
			for (auto &ptr : ValuesPtrArr)
				Ranges.Add(ptr->AsNumber());

			Intensities.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("intensities"));
			for (auto &ptr : ValuesPtrArr)
				Intensities.Add(ptr->AsNumber());

		}

		static LaserScan GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			LaserScan Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static LaserScan GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			LaserScan Result;
			Result.FromBson(BsonObject);
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

		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToBsonObject());

			Object->SetNumberField(TEXT("angle_min"), AngleMin);

			Object->SetNumberField(TEXT("angle_max"), AngleMax);

			Object->SetNumberField(TEXT("angle_increment"), AngleIncrement);

			Object->SetNumberField(TEXT("time_increment"), TimeIncrement);

			Object->SetNumberField(TEXT("scan_time"), ScanTime);

			Object->SetNumberField(TEXT("range_min"), RangeMin);

			Object->SetNumberField(TEXT("range_max"), RangeMax);

			TArray<TSharedPtr<FBsonValue>> RangesArray;
			for (auto &val : Ranges)
				RangesArray.Add(MakeShareable(new FBsonValueNumber(val)));
			Object->SetArrayField(TEXT("ranges"), RangesArray);

			TArray<TSharedPtr<FBsonValue>> IntensitiesArray;
			for (auto &val : Intensities)
				IntensitiesArray.Add(MakeShareable(new FBsonValueNumber(val)));
			Object->SetArrayField(TEXT("intensities"), IntensitiesArray);

			return Object;

		}

		virtual FString ToString() const override
		{
							
			FString RangesString = "[ ";
			for (auto &value : Ranges)
				RangesString += FString::SanitizeFloat(value) + TEXT(", ");
			RangesString += " ] ";
			FString IntensitiesString = "[ ";
			for (auto &value : Intensities)
				IntensitiesString += FString::SanitizeFloat(value) + TEXT(", ");
			IntensitiesString += " ] ";
			return TEXT("LaserScan { header = ") + Header.ToString() +
				TEXT(", angle_min = ") + FString::SanitizeFloat(AngleMin) +
				TEXT(", angle_max = ") + FString::SanitizeFloat(AngleMax) +
				TEXT(", angle_increment = ") + FString::SanitizeFloat(AngleIncrement) +
				TEXT(", time_increment = ") + FString::SanitizeFloat(TimeIncrement) +
				TEXT(", scan_time = ") + FString::SanitizeFloat(ScanTime) +
				TEXT(", range_min = ") + FString::SanitizeFloat(RangeMin) +
				TEXT(", range_max = ") + FString::SanitizeFloat(RangeMax) +
				TEXT(", ranges =") + RangesString +
				TEXT(", intensities =") + IntensitiesString +
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