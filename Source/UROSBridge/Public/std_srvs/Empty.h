#pragma once

#include "ROSBridgeSrv.h"

namespace std_srvs
{
	class Empty : public FROSBridgeSrv
	{

	protected:
		FString SrvType;

	public:
		Empty()
		{
			SrvType = TEXT("srd_srvs/Empty");
		}

		class Request : public SrvRequest 
		{
		public:

			virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
			{
			}

			static Request GetFromJson(TSharedPtr<FJsonObject> JsonObject)
			{
				return Request();
			}

			virtual FString ToString() const override
			{
				return TEXT("Empty::Request {} ");
			}

			virtual TSharedPtr<FJsonObject> ToJsonObject() const 
			{
				TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
				return Object;
			}
		};

		class Response : public SrvResponse 
		{
		public:
			virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
			{
			}

			static Response GetFromJson(TSharedPtr<FJsonObject> JsonObject)
			{
				return Response();
			}

			virtual FString ToString() const override
			{
				return TEXT("Empty::Response {} ");
			}

			virtual TSharedPtr<FJsonObject> ToJsonObject() const 
			{
				TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
				return Object;
			}
		};
	};
} // namespace std_srvs

