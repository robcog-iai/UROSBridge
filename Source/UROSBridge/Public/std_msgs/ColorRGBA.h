#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgStdmsgsColorRGBA : public FROSBridgeMsg
{
    float r;
    float g;
    float b;
    float a;

public:
    FROSBridgeMsgStdmsgsColorRGBA()
    {
        MsgType = "std_msgs/ColorRGBA";
    }

    FROSBridgeMsgStdmsgsColorRGBA(FVector4 color_)
    {
      this->SetColor(color_);
      MsgType = "std_msgs/ColorRGBA";
    }

    FROSBridgeMsgStdmsgsColorRGBA(float r_, float g_, float b_, float a_)
    {
        MsgType = "std_msgs/ColorRGBA";
        r = r_; g = g_; b = b_; a = a_;
    }

    ~FROSBridgeMsgStdmsgsColorRGBA() override {}


    FVector GetColor() const
    {
        return FVector4(r, g, b, a);
    }

    void SetColor(const FVector4 & Vector)
    {
        r = Vector.X; g = Vector.Y; b = Vector.Z; a = Vector.W;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        r = (float)(JsonObject->GetNumberField(TEXT("r")));
        g = (float)(JsonObject->GetNumberField(TEXT("g")));
        b = (float)(JsonObject->GetNumberField(TEXT("b")));
        a = (float)(JsonObject->GetNumberField(TEXT("a")));
    }

    static FROSBridgeMsgStdmsgsColorRGBA GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgStdmsgsColorRGBA Result;
        Result.FromJson(JsonObject);
        return Result;
    }

    virtual FString ToString () const override
    {
        return TEXT("ColorRGBA { r = ") + FString::SanitizeFloat(r) +
                         TEXT(", g = ") + FString::SanitizeFloat(g) +
                         TEXT(", b = ") + FString::SanitizeFloat(b) +
                         TEXT(", a = ") + FString::SanitizeFloat(a) + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetNumberField(TEXT("r"), r);
        Object->SetNumberField(TEXT("g"), g);
        Object->SetNumberField(TEXT("b"), b);
        Object->SetNumberField(TEXT("a"), a);
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString;
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};

/************************************************************************/
/* Namespace version                                                    */
/************************************************************************/
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

		ColorRGBA(FVector4 InColor)
		{
			this->SetColor(InColor);
			MsgType = "std_msgs/ColorRGBA";
		}

		ColorRGBA(float InR, float InG, float InB, float InA)
		{
			MsgType = "std_msgs/ColorRGBA";
			R = InR; G = InG; B = InB; A = InA;
		}

		~ColorRGBA() override {}


		FVector GetColor() const
		{
			return FVector4(R, G, B, A);
		}

		void SetColor(const FVector4& Vector)
		{
			R = Vector.X; G = Vector.Y; B = Vector.Z; A = Vector.W;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			R = (float)(JsonObject->GetNumberField(TEXT("r")));
			G = (float)(JsonObject->GetNumberField(TEXT("g")));
			B = (float)(JsonObject->GetNumberField(TEXT("b")));
			A = (float)(JsonObject->GetNumberField(TEXT("a")));
		}

		static ColorRGBA GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			ColorRGBA Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("ColorRGBA { r = ") + FString::SanitizeFloat(R) +
				TEXT(", g = ") + FString::SanitizeFloat(G) +
				TEXT(", b = ") + FString::SanitizeFloat(B) +
				TEXT(", a = ") + FString::SanitizeFloat(A) + TEXT(" } ");
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

		virtual FString ToYamlString() const override 
		{
			FString OutputString;
			TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
			FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
			return OutputString;
		}
	};
} // namespace std_msgs