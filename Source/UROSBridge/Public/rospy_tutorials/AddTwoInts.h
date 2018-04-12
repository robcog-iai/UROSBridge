#pragma once

#include "ROSBridgeSrv.h"

namespace rospy_tutorials
{
	class AddTwoInts : public FROSBridgeSrv 
	{

	public:
		AddTwoInts()
		{
			SrvType = TEXT("rospy_tutorials/AddTwoInts");
		}

		class Request : public SrvRequest 
		{
		private:
			int64 A;
			int64 B; 

		public:
			Request() {}
			Request(int64 InA, int64 InB) : A(InA), B(InB) {}

			int64 GetA() const 
			{ 
				return A; 
			}

			void SetA(int64 InA) 
			{ 
				A = InA; 
			}

			int64 GetB() const 
			{ 
				return B; 
			}

			void SetB(int64 InB) 
			{
				B = InB; 
			}

			virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
			{
				A = JsonObject->GetNumberField("a");
				B = JsonObject->GetNumberField("b");
			}

			static Request GetFromJson(TSharedPtr<FJsonObject> JsonObject)
			{
				Request Req;
				Req.FromJson(JsonObject);
				return Req;
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
			
			int64 GetSum() const 
			{
				return Sum;
			}

			void SetSum(int64 InSum) 
			{
				Sum = InSum; 
			}


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
} // namespace rospy_tutorials 
