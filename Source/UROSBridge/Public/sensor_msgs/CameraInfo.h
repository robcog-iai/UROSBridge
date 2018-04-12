#pragma once
#include "ROSBridgeMsg.h"
#include "std_msgs/Header.h"
#include "sensor_msgs/RegionOfInterest.h"
#include "Base64.h"

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
		sensor_msgs::RegionOfInterest ROI;

	public:

		CameraInfo()
		{
			MsgType = "sensor_msgs/CameraInfo";
		}

		CameraInfo
		(std_msgs::Header InHeader, uint32 InHeight, uint32 InWidth,
			FString InDistortionModel,
			const TArray<double>& InD,
			const TArray<double>& InK,
			const TArray<double>& InR,
			const TArray<double>& InP,
			uint32 InBinningX, uint32 InBinningY,
			sensor_msgs::RegionOfInterest InROI)
			:
			Header(InHeader),
			Height(InHeight),
			Width(InWidth),
			DistortionModel(InDistortionModel),
			D(InD),
			K(InK),
			R(InR),
			P(InP),
			BinningX(InBinningX), BinningY(InBinningY),
			ROI(InROI)
		{
			MsgType = "sensor_msgs/CameraInfo";
		}

		~CameraInfo() override {}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		uint32 GetHeight() const
		{
			return Height;
		}

		uint32 GetWidth() const
		{
			return Width;
		}

		FString GetDistortionModel() const
		{
			return DistortionModel;
		}

		TArray<double> GetD() const
		{
			return D;
		}

		TArray<double> GetK() const
		{
			return K;
		}

		TArray<double> GetR() const
		{
			return R;
		}

		TArray<double> GetP() const
		{
			return P;
		}

		uint32 GetBinningX() const
		{
			return BinningX;
		}

		uint32 GetBinningY() const
		{
			return BinningY;
		}

		sensor_msgs::RegionOfInterest GetROI() const
		{
			return ROI;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetHeight(uint32 InHeight)
		{
			Height = InHeight;
		}

		void SetWidth(uint32 InWidth)
		{
			Width = InWidth;
		}

		void SetDistortionModel(FString InDistortionModel)
		{
			DistortionModel = InDistortionModel;
		}

		void SetD(const TArray<double> &InD)
		{
			D = InD;
		}

		void SetK(const TArray<double> &InK)
		{
			K = InK;
		}
		
		void SetR(const TArray<double> &InR)
		{
			R = InR;
		}
		
		void SetP(const TArray<double> &InP)
		{
			P = InP;
		}

		void SetBinningX(uint32 InBinningX)
		{
			BinningX = InBinningX;
		}

		void SetBinningY(uint32 InBinningY)
		{
			BinningY = InBinningY;
		}

		void SetROI(sensor_msgs::RegionOfInterest InData)
		{
			ROI = InData;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
			Height = JsonObject->GetNumberField(TEXT("height"));
			Width = JsonObject->GetNumberField(TEXT("width"));
			DistortionModel = JsonObject->GetStringField(TEXT("distortion_model"));
			
			D.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("D"));
			for (auto &ptr : ValuesPtrArr)
				D.Add(ptr->AsNumber());

			K.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("K"));
			for (auto &ptr : ValuesPtrArr)
				K.Add(ptr->AsNumber());

			R.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("R"));
			for (auto &ptr : ValuesPtrArr)
				R.Add(ptr->AsNumber());

			P.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("P"));
			for (auto &ptr : ValuesPtrArr)
				P.Add(ptr->AsNumber());

			BinningX = JsonObject->GetNumberField(TEXT("binning_x"));
			BinningY = JsonObject->GetNumberField(TEXT("binning_y"));
			ROI = sensor_msgs::RegionOfInterest::GetFromJson(JsonObject->GetObjectField(TEXT("roi")));
		}

		static CameraInfo GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			CameraInfo Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			FString DString = "[ ";
			for (auto &value : D)
				DString += FString::SanitizeFloat(value) + TEXT(", ");
			DString += " ]";

			FString KString = "[ ";
			for (auto &value : K)
				KString += FString::SanitizeFloat(value) + TEXT(", ");
			KString += " ]";

			FString RString = "[ ";
			for (auto &value : R)
				RString += FString::SanitizeFloat(value) + TEXT(", ");
			RString += " ]";

			FString PString = "[ ";
			for (auto &value : P)
				PString += FString::SanitizeFloat(value) + TEXT(", ");
			PString += " ]";

			return TEXT("CameraInfo { header = ") + Header.ToString() +
				TEXT(", height = ") + FString::FromInt(Height) +
				TEXT(", width = ") + FString::FromInt(Width) +
				TEXT(", distortion_model =") + DistortionModel +
				TEXT(", D =") + DString +
				TEXT(", K =") + KString +
				TEXT(", R =") + RString +
				TEXT(", P =") + PString +
				TEXT(", binning_x =") + FString::FromInt(BinningX) +
				TEXT(", binning_y =") + FString::FromInt(BinningY) +
				TEXT(", roi = ") + ROI.ToString() +
				TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			TArray<TSharedPtr<FJsonValue>> DArray, KArray, RArray, PArray;
			for (auto &val : D)
				DArray.Add(MakeShareable(new FJsonValueNumber(val)));
			for (auto &val : K)
				KArray.Add(MakeShareable(new FJsonValueNumber(val)));
			for (auto &val : R)
				RArray.Add(MakeShareable(new FJsonValueNumber(val)));
			for (auto &val : P)
				PArray.Add(MakeShareable(new FJsonValueNumber(val)));

			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetNumberField(TEXT("height"), Height);
			Object->SetNumberField(TEXT("width"), Width);
			Object->SetStringField(TEXT("distortion_model"), DistortionModel);
			Object->SetArrayField(TEXT("D"), DArray);
			Object->SetArrayField(TEXT("K"), KArray);
			Object->SetArrayField(TEXT("R"), RArray);
			Object->SetArrayField(TEXT("P"), PArray);
			Object->SetNumberField(TEXT("binning_x"), BinningX);
			Object->SetNumberField(TEXT("binning_y"), BinningY);
			Object->SetObjectField(TEXT("roi"), ROI.ToJsonObject());

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