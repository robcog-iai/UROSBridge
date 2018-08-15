#pragma once

#include "ROSBridgeMsg.h"
#include "std_msgs/Header.h"
#include "sensor_msgs/RegionOfInterest.h"


namespace sensor_msgs
{
	class CameraInfo : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		uint32 Height;
		uint32 Width;
		FString DistortionModel;
		TArray<double> D;
		TArray<double> K;
		TArray<double> R;
		TArray<double> P;
		uint32 BinningX;
		uint32 BinningY;
		sensor_msgs::RegionOfInterest Roi;
	public:
		CameraInfo()
		{
			MsgType = TEXT("sensor_msgs/CameraInfo");
		}
		
		CameraInfo(std_msgs::Header InHeader,
			uint32 InHeight,
			uint32 InWidth,
			FString InDistortionModel,
			TArray<double> InD,
			TArray<double> InK,
			TArray<double> InR,
			TArray<double> InP,
			uint32 InBinningX,
			uint32 InBinningY,
			sensor_msgs::RegionOfInterest InRoi)
			:
			Header(InHeader),
			Height(InHeight),
			Width(InWidth),
			DistortionModel(InDistortionModel),
			D(InD),
			K(InK),
			R(InR),
			P(InP),
			BinningX(InBinningX),
			BinningY(InBinningY),
			Roi(InRoi)
		{
			MsgType = TEXT("sensor_msgs/CameraInfo");
		}

		~CameraInfo() override {}

		// Getters 
		std_msgs::Header GetHeader() const { return Header; }
		uint32 GetHeight() const { return Height; }
		uint32 GetWidth() const { return Width; }
		FString GetDistortionModel() const { return DistortionModel; }
		TArray<double> GetD() const { return D; }
		TArray<double> GetK() const { return K; }
		TArray<double> GetR() const { return R; }
		TArray<double> GetP() const { return P; }
		uint32 GetBinningX() const { return BinningX; }
		uint32 GetBinningY() const { return BinningY; }
		sensor_msgs::RegionOfInterest GetRoi() const { return Roi; }

		// Setters 
		void SetHeader(std_msgs::Header InHeader) { Header = InHeader; }
		void SetHeight(uint32 InHeight) { Height = InHeight; }
		void SetWidth(uint32 InWidth) { Width = InWidth; }
		void SetDistortionModel(FString InDistortionModel) { DistortionModel = InDistortionModel; }
		void SetD(TArray<double> InD) { D = InD; }
		void SetK(TArray<double> InK) { K = InK; }
		void SetR(TArray<double> InR) { R = InR; }
		void SetP(TArray<double> InP) { P = InP; }
		void SetBinningX(uint32 InBinningX) { BinningX = InBinningX; }
		void SetBinningY(uint32 InBinningY) { BinningY = InBinningY; }
		void SetRoi(sensor_msgs::RegionOfInterest InRoi) { Roi = InRoi; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			Height = JsonObject->GetNumberField(TEXT("height"));

			Width = JsonObject->GetNumberField(TEXT("width"));

			DistortionModel = JsonObject->GetStringField(TEXT("distortion_model"));

			D.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("d"));
			for (auto &ptr : ValuesPtrArr)
				D.Add(ptr->AsNumber());

			K.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("k"));
			for (auto &ptr : ValuesPtrArr)
				K.Add(ptr->AsNumber());

			R.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("r"));
			for (auto &ptr : ValuesPtrArr)
				R.Add(ptr->AsNumber());

			P.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("p"));
			for (auto &ptr : ValuesPtrArr)
				P.Add(ptr->AsNumber());

			BinningX = JsonObject->GetNumberField(TEXT("binning_x"));

			BinningY = JsonObject->GetNumberField(TEXT("binning_y"));

			Roi = sensor_msgs::RegionOfInterest::GetFromJson(JsonObject->GetObjectField(TEXT("roi")));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

			Header = std_msgs::Header::GetFromBson(BsonObject->GetObjectField(TEXT("header")));

			Height = BsonObject->GetNumberField(TEXT("height"));

			Width = BsonObject->GetNumberField(TEXT("width"));

			DistortionModel = BsonObject->GetStringField(TEXT("distortion_model"));

			D.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("d"));
			for (auto &ptr : ValuesPtrArr)
				D.Add(ptr->AsNumber());

			K.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("k"));
			for (auto &ptr : ValuesPtrArr)
				K.Add(ptr->AsNumber());

			R.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("r"));
			for (auto &ptr : ValuesPtrArr)
				R.Add(ptr->AsNumber());

			P.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("p"));
			for (auto &ptr : ValuesPtrArr)
				P.Add(ptr->AsNumber());

			BinningX = BsonObject->GetNumberField(TEXT("binning_x"));

			BinningY = BsonObject->GetNumberField(TEXT("binning_y"));

			Roi = sensor_msgs::RegionOfInterest::GetFromBson(BsonObject->GetObjectField(TEXT("roi")));

		}

		static CameraInfo GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			CameraInfo Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static CameraInfo GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			CameraInfo Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());

			Object->SetNumberField(TEXT("height"), Height);

			Object->SetNumberField(TEXT("width"), Width);

			Object->SetStringField(TEXT("distortion_model"), DistortionModel);

			TArray<TSharedPtr<FJsonValue>> DArray;
			for (auto &val : D)
				DArray.Add(MakeShareable(new FJsonValueNumber(val)));
			Object->SetArrayField(TEXT("d"), DArray);

			TArray<TSharedPtr<FJsonValue>> KArray;
			for (auto &val : K)
				KArray.Add(MakeShareable(new FJsonValueNumber(val)));
			Object->SetArrayField(TEXT("k"), KArray);

			TArray<TSharedPtr<FJsonValue>> RArray;
			for (auto &val : R)
				RArray.Add(MakeShareable(new FJsonValueNumber(val)));
			Object->SetArrayField(TEXT("r"), RArray);

			TArray<TSharedPtr<FJsonValue>> PArray;
			for (auto &val : P)
				PArray.Add(MakeShareable(new FJsonValueNumber(val)));
			Object->SetArrayField(TEXT("p"), PArray);

			Object->SetNumberField(TEXT("binning_x"), BinningX);

			Object->SetNumberField(TEXT("binning_y"), BinningY);

			Object->SetObjectField(TEXT("roi"), Roi.ToJsonObject());

			return Object;

		}

		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToBsonObject());

			Object->SetNumberField(TEXT("height"), Height);

			Object->SetNumberField(TEXT("width"), Width);

			Object->SetStringField(TEXT("distortion_model"), DistortionModel);

			TArray<TSharedPtr<FBsonValue>> DArray;
			for (auto &val : D)
				DArray.Add(MakeShareable(new FBsonValueNumber(val)));
			Object->SetArrayField(TEXT("d"), DArray);

			TArray<TSharedPtr<FBsonValue>> KArray;
			for (auto &val : K)
				KArray.Add(MakeShareable(new FBsonValueNumber(val)));
			Object->SetArrayField(TEXT("k"), KArray);

			TArray<TSharedPtr<FBsonValue>> RArray;
			for (auto &val : R)
				RArray.Add(MakeShareable(new FBsonValueNumber(val)));
			Object->SetArrayField(TEXT("r"), RArray);

			TArray<TSharedPtr<FBsonValue>> PArray;
			for (auto &val : P)
				PArray.Add(MakeShareable(new FBsonValueNumber(val)));
			Object->SetArrayField(TEXT("p"), PArray);

			Object->SetNumberField(TEXT("binning_x"), BinningX);

			Object->SetNumberField(TEXT("binning_y"), BinningY);

			Object->SetObjectField(TEXT("roi"), Roi.ToBsonObject());

			return Object;

		}

		virtual FString ToString() const override
		{
							
			FString DString = "[ ";
			for (auto &value : D)
				DString += FString::SanitizeFloat(value) + TEXT(", ");
			DString += " ] ";
			FString KString = "[ ";
			for (auto &value : K)
				KString += FString::SanitizeFloat(value) + TEXT(", ");
			KString += " ] ";
			FString RString = "[ ";
			for (auto &value : R)
				RString += FString::SanitizeFloat(value) + TEXT(", ");
			RString += " ] ";
			FString PString = "[ ";
			for (auto &value : P)
				PString += FString::SanitizeFloat(value) + TEXT(", ");
			PString += " ] ";
			return TEXT("CameraInfo { header = ") + Header.ToString() +
				TEXT(", height = ") + FString::FromInt(Height) +
				TEXT(", width = ") + FString::FromInt(Width) +
				TEXT(", distortion_model = ") + DistortionModel +
				TEXT(", d =") + DString +
				TEXT(", k =") + KString +
				TEXT(", r =") + RString +
				TEXT(", p =") + PString +
				TEXT(", binning_x = ") + FString::FromInt(BinningX) +
				TEXT(", binning_y = ") + FString::FromInt(BinningY) +
				TEXT(", roi = ") + Roi.ToString() +
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