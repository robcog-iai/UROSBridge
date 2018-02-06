#pragma once

#include "ROSBridgeSrv.h"

class UROSBRIDGE_API FROSBridgeSrvStdsrvsEmpty : public FROSBridgeSrv 
{

protected:
    FString Type;

public:
    FROSBridgeSrvStdsrvsEmpty() 
    {
        Type = TEXT("srd_srvs/Empty"); 
    }

    class Request : public SrvRequest {
    public:

        virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        }

        static Request GetFromJson(TSharedPtr<FJsonObject> JsonObject)
        {
            return Request();
        }

        virtual FString ToString() const override
        {
            return TEXT("Empty::Request {} ");
        }

        virtual TSharedPtr<FJsonObject> ToJsonObject() const {
            TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
            return Object;
        }
    };

    class Response : public SrvResponse {
    public:
        virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        }

        static Response GetFromJson(TSharedPtr<FJsonObject> JsonObject)
        {
            return Response();
        }

        virtual FString ToString() const override
        {
            return TEXT("Empty::Response {} ");
        }

        virtual TSharedPtr<FJsonObject> ToJsonObject() const {
            TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
            return Object;
        }
    };
};

/************************************************************************/
/* Namespace version                                                    */
/************************************************************************/
namespace std_srvs
{
	class UROSBRIDGE_API Empty : public FROSBridgeSrv
	{

	protected:
		FString Type;

	public:
		Empty()
		{
			Type = TEXT("srd_srvs/Empty");
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

