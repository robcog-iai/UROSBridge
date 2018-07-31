#pragma once

#include "ROSBridgeSrv.h"

namespace std_srvs
{
	class Empty : public FROSBridgeSrv
	{
	public:
		Empty()
		{
			SrvType = TEXT("std_srvs/Empty");
		}

		class Request : public SrvRequest
		{
		private:
			
					
		public:
			Request(){ }
			
			virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
			{
				
			}
			
			virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
			{
				
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

				return Object;

			}
			
			virtual TSharedPtr<FBsonObject> ToBsonObject() const
			{
				TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

				return Object;

			}
		};
		
		class Response : public SrvResponse
		{
		private:
			
			
			
		public:
			Response(){ }
			
			virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
			{
				
			}
			
			virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
			{
				
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

				return Object;

			}
			
			virtual TSharedPtr<FBsonObject> ToBsonObject() const
			{
				TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

				return Object;

			}
		};
		
	};
	
}