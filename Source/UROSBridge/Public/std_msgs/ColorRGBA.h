#pragma once

#include "ROSBridgeMsg.h"


namespace std_msgs
{
	class ColorRGBA : public FROSBridgeMsg
	{
		float R;
		float G;
		float B;
		float A;
	public:
		ColorRGBA()
		{
			MsgType = "std_msgs/ColorRGBA";
		}

		ColorRGBA
		(
			float InR,
			float InG,
			float InB,
			float InA
		):
			R(InR),
			G(InG),
			B(InB),
			A(InA)
		{
			MsgType = "std_msgs/ColorRGBA";
		}

		~ColorRGBA() override {}

		float GetR() const
		{
			return R;
		}

		float GetG() const
		{
			return G;
		}

		float GetB() const
		{
			return B;
		}

		float GetA() const
		{
			return A;
		}

		void SetR(float InR)
		{
			R = InR;
		}

		void SetG(float InG)
		{
			G = InG;
		}

		void SetB(float InB)
		{
			B = InB;
		}

		void SetA(float InA)
		{
			A = InA;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			R = JsonObject->GetNumberField(TEXT("r"));

			G = JsonObject->GetNumberField(TEXT("g"));

			B = JsonObject->GetNumberField(TEXT("b"));

			A = JsonObject->GetNumberField(TEXT("a"));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			R = BsonObject->GetNumberField(TEXT("r"));

			G = BsonObject->GetNumberField(TEXT("g"));

			B = BsonObject->GetNumberField(TEXT("b"));

			A = BsonObject->GetNumberField(TEXT("a"));

		}

		static ColorRGBA GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			ColorRGBA Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static ColorRGBA GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			ColorRGBA Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetNumberField(TEXT("r"), R);
			Object->SetNumberField(TEXT("g"), G);
			Object->SetNumberField(TEXT("b"), B);
			Object->SetNumberField(TEXT("a"), A);
			return Object;
		}
		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetNumberField(TEXT("r"), R);
			Object->SetNumberField(TEXT("g"), G);
			Object->SetNumberField(TEXT("b"), B);
			Object->SetNumberField(TEXT("a"), A);
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