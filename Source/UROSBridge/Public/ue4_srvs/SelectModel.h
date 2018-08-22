#pragma once

#include "ROSBridgeSrv.h"



namespace ue4_srvs
{
	class SelectModel : public FROSBridgeSrv
	{
	public:
		SelectModel()
		{
			SrvType = TEXT("ue4_srvs/SelectModel");
		}

		class Request : public SrvRequest
		{
		private:
			FString ModelName;
					
		public:
			Request(){ }
			Request(FString InModelName)
				:
				ModelName(InModelName) { }
			
			
			// Getters 
			FString GetModelName() const { return ModelName; }
			
			
			// Setters 
			void SetModelName(FString InModelName) { ModelName = InModelName; }
			
			virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
			{
				ModelName = JsonObject->GetStringField(TEXT("model_name"));

			}
			
			virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
			{
				ModelName = BsonObject->GetStringField(TEXT("model_name"));

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
			
			virtual FString ToString() const override
			{
									
				return TEXT("SelectModel::Request { model_name = ") + ModelName +
					TEXT(" } ");

			}
			
			virtual TSharedPtr<FJsonObject> ToJsonObject() const
			{
				TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

				Object->SetStringField(TEXT("model_name"), ModelName);

				return Object;

			}
			
			virtual TSharedPtr<FBsonObject> ToBsonObject() const
			{
				TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

				Object->SetStringField(TEXT("model_name"), ModelName);

				return Object;

			}
		};
		
		class Response : public SrvResponse
		{
		private:
			bool Success;
			
			
		public:
			Response(){ }
			Response(bool InSuccess)
				:
				Success(InSuccess) { }
			
			
			// Getters 
			bool GetSuccess() const { return Success; }
			
			
			// Setters 
			void SetSuccess(bool InSuccess) { Success = InSuccess; }
			
			
			virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
			{
				Success = JsonObject->GetBoolField(TEXT("success"));

			}
			
			virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
			{
				Success = BsonObject->GetBoolField(TEXT("success"));

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
			
			virtual FString ToString() const override
			{
									
				return TEXT("SelectModel::Response { success = ") + FString::FromInt(Success) +
					TEXT(" } ");

			}
			
			virtual TSharedPtr<FJsonObject> ToJsonObject() const
			{
				TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

				Object->SetBoolField(TEXT("success"), Success);

				return Object;

			}
			
			virtual TSharedPtr<FBsonObject> ToBsonObject() const
			{
				TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

				Object->SetBoolField(TEXT("success"), Success);

				return Object;

			}
		};
		
	};
	
}