#pragma once

#include "ROSBridgeSrv.h"

class UROSBRIDGE_API FROSBridgeSrvRospytutorialsAddTwoInts : public FROSBridgeSrv 
{

protected:
    FString Type;

public:
    FROSBridgeSrvRospytutorialsAddTwoInts()
    {
        Type = TEXT("rospy_tutorials/AddTwoInts");
    }

    class Request : public SrvRequest {
    private:
        int64 a;
        int64 b; 

    public:
        Request() { }
        Request(int64 a_, int64 b_) : a(a_), b(b_) {}
        int64 GetA() const { return a; }
        void SetA(int64 a_) { a = a_; }
        int64 GetB() const { return b; }
        void SetB(int64 b_) { b = b_; }

        virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
            a = JsonObject->GetNumberField("a");
            b = JsonObject->GetNumberField("b");
        }

        static Request GetFromJson(TSharedPtr<FJsonObject> JsonObject)
        {
            Request req; req.FromJson(JsonObject);
            return req;
        }

        virtual FString ToString() const override
        {
            return TEXT("AddTwoInts::Request { a = ") + FString::FromInt(a) +
                                       TEXT(", b = ") + FString::FromInt(b) + TEXT("} ");
        }

        virtual TSharedPtr<FJsonObject> ToJsonObject() const {
            TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
            Object->SetNumberField(TEXT("a"), a);
            Object->SetNumberField(TEXT("b"), b);
            return Object;
        }
    };

    class Response : public SrvResponse {
    private:
        int64 sum;

    public:
        Response() {}
        Response(int64 sum_) : sum(sum_) {}
        int64 GetSum() const { return sum; }
        void SetSum(int64 sum_) { sum = sum_; }

        virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
            sum = JsonObject->GetNumberField("sum");
        }

        static Response GetFromJson(TSharedPtr<FJsonObject> JsonObject)
        {
            Response rep; rep.FromJson(JsonObject);
            return rep;
        }

        virtual FString ToString() const override
        {
            return TEXT("AddTwoInts::Response { sum = ") + FString::SanitizeFloat(sum) + TEXT(" } ");
        }

        virtual TSharedPtr<FJsonObject> ToJsonObject() const {
            TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
            Object->SetNumberField("sum", sum);
            return Object;
        }
    };

};

/************************************************************************/
/* Namespace version                                                    */
/************************************************************************/
namespace tutorial_srvs
{
	class UROSBRIDGE_API AddTwoInts : public FROSBridgeSrv
	{

	protected:
		FString Type;

	public:
		AddTwoInts()
		{
			Type = TEXT("rospy_tutorials/AddTwoInts");
		}

		class Request : public SrvRequest 
		{
		private:
			int64 A;
			int64 B;

		public:
			Request() { }
			Request(int64 InA, int64 InB) : A(InA), B(InB) {}
			int64 GetA() const { return A; }
			void SetA(int64 InA) { A = InA; }
			int64 GetB() const { return B; }
			void SetB(int64 InB) { B = InB; }

			virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
			{
				A = JsonObject->GetNumberField("a");
				B = JsonObject->GetNumberField("b");
			}

			static Request GetFromJson(TSharedPtr<FJsonObject> JsonObject)
			{
				Request req; req.FromJson(JsonObject);
				return req;
			}

			virtual FString ToString() const override
			{
				return TEXT("AddTwoInts::Request { a = ") + FString::FromInt(A) +
					TEXT(", b = ") + FString::FromInt(B) + TEXT("} ");
			}

			virtual TSharedPtr<FJsonObject> ToJsonObject() const 
			{
				TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
				Object->SetNumberField(TEXT("a"), A);
				Object->SetNumberField(TEXT("b"), B);
				return Object;
			}
		};

		class Response : public SrvResponse 
		{
		private:
			int64 Sum;

		public:
			Response() {}
			Response(int64 InSum) : Sum(InSum) {}
			int64 GetSum() const { return Sum; }
			void SetSum(int64 InSum) { Sum = InSum; }

			virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
			{
				Sum = JsonObject->GetNumberField("sum");
			}

			static Response GetFromJson(TSharedPtr<FJsonObject> JsonObject)
			{
				Response rep; rep.FromJson(JsonObject);
				return rep;
			}

			virtual FString ToString() const override
			{
				return TEXT("AddTwoInts::Response { sum = ") + FString::SanitizeFloat(Sum) + TEXT(" } ");
			}

			virtual TSharedPtr<FJsonObject> ToJsonObject() const 
			{
				TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
				Object->SetNumberField("sum", Sum);
				return Object;
			}
		};
	};
} // namespace tutorial_srvs