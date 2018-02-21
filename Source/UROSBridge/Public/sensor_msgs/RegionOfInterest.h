#pragma once
#include "ROSBridgeMsg.h"
#include "std_msgs/Header.h"
#include "Base64.h"

namespace sensor_msgs
{
	class RegionOfInterest : public FROSBridgeMsg
	{
		uint32 XOffset;
		uint32 YOffset;
		uint32 Height;
		uint32 Width;
		bool DoRectify;

	public:

		RegionOfInterest()
		{
			MsgType = "sensor_msgs/RegionOfInterest";
		}

		RegionOfInterest
		(uint32 InXOffset, uint32 InYOffset, uint32 InHeight, uint32 InWidth, bool InDoRectify)
			:
			XOffset(InXOffset),
			YOffset(InYOffset),
			Height(InHeight),
			Width(InWidth),
			DoRectify(InDoRectify)
		{
			MsgType = "sensor_msgs/RegionOfInterest";
		}

		~RegionOfInterest() override {}

		uint32 GetXOffset() const
		{
			return XOffset;
		}
		uint32 GetYOffset() const
		{
			return YOffset;
		}

		uint32 GetHeight() const
		{
			return Height;
		}

		uint32 GetWidth() const
		{
			return Width;
		}

		bool GetDoRectify() const
		{
			return DoRectify;
		}

		void SetXOffset(uint32 InXOffset)
		{
			XOffset = InXOffset;
		}

		void SetYOffset(uint32 InYOffset)
		{
			YOffset = InYOffset;
		}

		void SetHeight(uint32 InHeight)
		{
			Height = InHeight;
		}

		void SetWidth(uint32 InWidth)
		{
			Width = InWidth;
		}

		void SetDoRectify(bool InDoRectify)
		{
			DoRectify = InDoRectify;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			XOffset = JsonObject->GetNumberField(TEXT("x_offset"));
			YOffset = JsonObject->GetNumberField(TEXT("y_offset"));
			Height = JsonObject->GetNumberField(TEXT("height"));
			Width = JsonObject->GetNumberField(TEXT("width"));
			DoRectify = JsonObject->GetBoolField(TEXT("do_rectify"));
		}

		static RegionOfInterest GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			RegionOfInterest Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("RegionOfInterest { x_offset = ") + FString::FromInt(XOffset) +
				TEXT(", y_offset = ") + FString::FromInt(YOffset) +
				TEXT(", height = ") + FString::FromInt(Height) +
				TEXT(", width = ") + FString::FromInt(Width) +
				TEXT(", do_rectify =") + FString::FromInt(DoRectify) +
				TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetNumberField(TEXT("x_offset"), XOffset);
			Object->SetNumberField(TEXT("y_offset"), YOffset);
			Object->SetNumberField(TEXT("height"), Height);
			Object->SetNumberField(TEXT("width"), Width);
			Object->SetBoolField(TEXT("do_rectify"), DoRectify);

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