#pragma once

#include "ROSBridgeSrv.h"

namespace std_srvs
{
	class SetBool : public FROSBridgeSrv 
	{
	public:
		SetBool()
		{
			SrvType = TEXT("srd_srvs/SetBool");
		}

		class Request : public SrvRequest 
		{
		private:
			uint8 Data;

		public:
			Request() { }
			Request(uint8 InData) : Data(InData) {}
			uint8 GetData() const { return Data; }
			void SetData(uint8 InData) { Data = InData; }

			virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
			{
				Data = JsonObject->GetIntegerField("data");
			}

			static Request GetFromJson(TSharedPtr<FJsonObject> JsonObject)
			{
				Request Req; 
				Req.FromJson(JsonObject);
				return Req;
			}

			virtual FString ToString() const override
			{
				return TEXT("SetBool::Request { data = ") + FString::FromInt(Data) + TEXT(" } ");
			}

			virtual TSharedPtr<FJsonObject> ToJsonObject() const 
			{
				TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
				Object->SetNumberField(TEXT("data"), Data);
				return Object;
			}
		};

		class Response : public SrvResponse 
		{
		private:
			uint8 Success;
			FString Message;

		public:
			Response() {}
			Response(uint8 InSuccess, FString InMessage) : Success(InSuccess), Message(InMessage) {}
			uint8 GetSuccess() const { return Success; }
			FString GetMessage() const { return Message; }
			void SetSuccess(uint8 InSuccess) { Success = InSuccess; }
			void SetMessage(FString InMessage) { Message = InMessage; }

			virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
			{
				Success = JsonObject->GetIntegerField("success");
				Message = JsonObject->GetStringField("message");
			}

			static Response GetFromJson(TSharedPtr<FJsonObject> JsonObject)
			{
				Response Resp; 
				Resp.FromJson(JsonObject);
				return Resp;
			}

			virtual FString ToString() const override
			{
				return TEXT("SetBool::Response { success = ") + FString::FromInt(Success) + TEXT(", ") +
					TEXT(" message = \"") + Message + TEXT("\" } ");
			}

			virtual TSharedPtr<FJsonObject> ToJsonObject() const 
			{
				TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
				Object->SetNumberField("success", Success);
				Object->SetStringField("message", Message);
				return Object;
			}
		};
	};
} // namespace std_srvs