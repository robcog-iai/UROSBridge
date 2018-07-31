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
			Request(){ }
			Request(int64 InA,
				int64 InB)
				:
				A(InA),
				B(InB) { }
			
			
			// Getters 
			int64 GetA() const { return A; }
			int64 GetB() const { return B; }
			
			
			// Setters 
			void SetA(int64 InA) { A = InA; }
			void SetB(int64 InB) { B = InB; }
			
			virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
			{
				A = JsonObject->GetNumberField(TEXT("a"));

				B = JsonObject->GetNumberField(TEXT("b"));

			}
			
			virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
			{
				A = BsonObject->GetNumberField(TEXT("a"));

				B = BsonObject->GetNumberField(TEXT("b"));

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

				Object->SetNumberField(TEXT("a"), A);

				Object->SetNumberField(TEXT("b"), B);

				return Object;

			}
			
			virtual TSharedPtr<FBsonObject> ToBsonObject() const
			{
				TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

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
			Response(){ }
			Response(int64 InSum)
				:
				Sum(InSum) { }
			
			
			// Getters 
			int64 GetSum() const { return Sum; }
			
			
			// Setters 
			void SetSum(int64 InSum) { Sum = InSum; }
			
			
			virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
			{
				Sum = JsonObject->GetNumberField(TEXT("sum"));

			}
			
			virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
			{
				Sum = BsonObject->GetNumberField(TEXT("sum"));

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

				Object->SetNumberField(TEXT("sum"), Sum);

				return Object;

			}
			
			virtual TSharedPtr<FBsonObject> ToBsonObject() const
			{
				TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

				Object->SetNumberField(TEXT("sum"), Sum);

				return Object;

			}
		};
		
	};
	
}