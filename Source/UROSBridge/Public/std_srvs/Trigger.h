#pragma once

#include "ROSBridgeSrv.h"

namespace std_srvs
{
	class Trigger : public FROSBridgeSrv 
	{

	public:
		Trigger()
		{
			SrvType = TEXT("std_srvs/Trigger");
		}

		class Request : public SrvRequest 
		{
		public:
			Request() { }

			virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
			{
			}

			static Request GetFromJson(TSharedPtr<FJsonObject> JsonObject)
			{
				Request Req; 
				Req.FromJson(JsonObject);
				return Req;
			}

			virtual FString ToString() const override
			{
				return TEXT("Trigger::Request { } ");
			}

			virtual TSharedPtr<FJsonObject> ToJsonObject() const 
			{
				TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
				return Object;
			}
		};

		class Response : public SrvResponse 
		{
		private:
			bool Success;
			FString Message;

		public:
			Response() {}
			Response(bool InSuccess, FString InMessage) : Success(InSuccess), Message(InMessage) {}
			bool GetSuccess() const { return Success; }
			FString GetMessage() const { return Message; }
			void SetSuccess(bool InSuccess) { Success = InSuccess; }
			void SetMessage(FString InMessage) { Message = InMessage; }

			virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
			{
				Success = JsonObject->GetBoolField("success");
				Message = JsonObject->GetStringField("message");
			}

			static Response GetFromJson(TSharedPtr<FJsonObject> JsonObject)
			{
				Response Resp; Resp.FromJson(JsonObject);
				return Resp;
			}

			virtual FString ToString() const override
			{
				FString BoolString = Success ? "true" : "false";
				return TEXT("Trigger::Response { success = ") + BoolString + TEXT(", ") +
					TEXT(" message = \"") + Message + TEXT("\" } ");
			}

			virtual TSharedPtr<FJsonObject> ToJsonObject() const 
			{
				TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
				Object->SetBoolField("success", Success);
				Object->SetStringField("message", Message);
				return Object;
			}
		};
	};
} // namespace std_srvs