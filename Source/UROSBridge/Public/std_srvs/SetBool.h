#pragma once

#include "ROSBridgeSrv.h"

namespace std_srvs
{
	class SetBool : public FROSBridgeSrv
	{
	public:
		SetBool()
		{
			SrvType = TEXT("std_srvs/SetBool");
		}

		class Request : public SrvRequest
		{
		private:
			bool Data;
					
		public:
			Request(){ }
			Request(bool InData)
				:
				Data(InData) { }
			
			
			// Getters 
			bool GetData() const { return Data; }
			
			
			// Setters 
			void SetData(bool InData) { Data = InData; }
			
			virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
			{
				Data = JsonObject->GetBoolField(TEXT("data"));

			}
			
			virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
			{
				Data = BsonObject->GetBoolField(TEXT("data"));

			}
			
			static Request GetFromJson(TSharedPtr<FJsonObject> JsonObject)
			{
				Request Req;
				Req.FromJson(JsonObject);
				return Req;
			}
			
			static Request GetFromBson(TSharedPtr<FBsonObject> BsonObject)
			{
				Request Req;
				Req.FromBson(BsonObject);
				return Req;
			}
			
//			### TOSTRING ###
			
			virtual TSharedPtr<FJsonObject> ToJsonObject() const
			{
				TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

				Object->SetBoolField(TEXT("data"), Data);

				return Object;

			}
			
			virtual TSharedPtr<FBsonObject> ToBsonObject() const
			{
				TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

				Object->SetBoolField(TEXT("data"), Data);

				return Object;

			}
		};
		
		class Response : public SrvResponse
		{
		private:
			bool Success;
			FString Message;
			
			
		public:
			Response(){ }
			Response(bool InSuccess,
				FString InMessage)
				:
				Success(InSuccess),
				Message(InMessage) { }
			
			
			// Getters 
			bool GetSuccess() const { return Success; }
			FString GetMessage() const { return Message; }
			
			
			// Setters 
			void SetSuccess(bool InSuccess) { Success = InSuccess; }
			void SetMessage(FString InMessage) { Message = InMessage; }
			
			
			virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
			{
				Success = JsonObject->GetBoolField(TEXT("success"));

				Message = JsonObject->GetStringField(TEXT("message"));

			}
			
			virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
			{
				Success = BsonObject->GetBoolField(TEXT("success"));

				Message = BsonObject->GetStringField(TEXT("message"));

			}
			
			static Response GetFromJson(TSharedPtr<FJsonObject> JsonObject)
			{
				Response Resp;
				Resp.FromJson(JsonObject);
				return Resp;
			}
			
			static Response GetFromBson(TSharedPtr<FBsonObject> BsonObject)
			{
				Response Resp; 
				Resp.FromBson(BsonObject);
				return Resp;
			}			
			
//			### TOSTRING ###
			
			virtual TSharedPtr<FJsonObject> ToJsonObject() const
			{
				TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

				Object->SetBoolField(TEXT("success"), Success);

				Object->SetStringField(TEXT("message"), Message);

				return Object;

			}
			
			virtual TSharedPtr<FBsonObject> ToBsonObject() const
			{
				TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

				Object->SetBoolField(TEXT("success"), Success);

				Object->SetStringField(TEXT("message"), Message);

				return Object;

			}
		};
		
	};
	
}