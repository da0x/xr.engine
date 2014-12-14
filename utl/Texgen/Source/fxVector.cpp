//---------------------------------------------------------------------------
#include "fxVector.h"
#include <math.h>
//---------------------------------------------------------------------------

fxVector::fxVector()
{
}

fxVector::fxVector(fxVectorData Data)
{
data[0] = Data[0];
data[1] = Data[1];
data[2] = Data[2];
}

fxVector::fxVector(float X, float Y, float Z)
{
data[0] = X;
data[1] = Y;
data[2] = Z;
}

fxVector * fxVector::Clone(void)
{
fxVector * p;
p = new fxVector(data);
return p;
}

void fxVector::Copy(fxVector * vector)
{
vector->data[0] = data[0];
vector->data[1] = data[1];
vector->data[2] = data[2];
}

void fxVector::Set(float X, float Y, float Z)
{
data[0] = X;
data[1] = Y;
data[2] = Z;
}

float * fxVector::Get(void)
{
return &data[0];
}

float fxVector::GetX(void)
{
return data[0];
}

float fxVector::GetY(void)
{
return data[1];
}

float fxVector::GetZ(void)
{
return data[2];
}

void fxVector::Add(float X, float Y, float Z)
{
data[0]+=X;
data[1]+=Y;
data[2]+=Z;
}

void fxVector::Add(fxVectorData Data)
{
data[0]+=Data[0];
data[1]+=Data[1];
data[2]+=Data[2];
}

void fxVector::Add(fxVector * vector)
{
data[0]+=vector->data[0];
data[1]+=vector->data[1];
data[2]+=vector->data[2];
}

void fxVector::Sub(float X, float Y, float Z)
{
data[0]-=X;
data[1]-=Y;
data[2]-=Z;
}

void fxVector::Sub(fxVectorData Data)
{
data[0]-=Data[0];
data[1]-=Data[1];
data[2]-=Data[2];
}

void fxVector::Sub(fxVector * vector)
{
data[0]-=vector->data[0];
data[1]-=vector->data[1];
data[2]-=vector->data[2];
}

void fxVector::Mul(float X, float Y, float Z)
{
data[0]*=X;
data[1]*=Y;
data[2]*=Z;
}

void fxVector::Mul(fxVectorData Data)
{
data[0]*=Data[0];
data[1]*=Data[1];
data[2]*=Data[2];
}

void fxVector::Mul(fxVector * vector)
{
data[0]*=vector->data[0];
data[1]*=vector->data[1];
data[2]*=vector->data[2];
}

void fxVector::Div(float X, float Y, float Z)
{
data[0]/=X;
data[1]/=Y;
data[2]/=Z;
}

void fxVector::Div(fxVectorData Data)
{
data[0]/=Data[0];
data[1]/=Data[1];
data[2]/=Data[2];
}

void fxVector::Div(fxVector * vector)
{
data[0]/=vector->data[0];
data[1]/=vector->data[1];
data[2]/=vector->data[2];
}

void fxVector::MulS(float scalar)
{
data[0]*=scalar;
data[1]*=scalar;
data[2]*=scalar;
}

void fxVector::DivS(float scalar)
{
data[0]/=scalar;
data[1]/=scalar;
data[2]/=scalar;
}

float fxVector::Length(void)
{
return (float)sqrt(data[0]*data[0]+data[1]*data[1]+data[2]*data[2]);
}

float fxVector::SquareLength(void)
{
return (data[0]*data[0]+data[1]*data[1]+data[2]*data[2]);
}

float fxVector::Normalize(void)
{
float length = Length();
if (length == 0) return 0;
data[0]/=length;
data[1]/=length;
data[2]/=length;
return length;
}

void fxVector::Invert(void)
{
data[0]*=-1;
data[1]*=-1;
data[2]*=-1;
}

float fxVector::Distance(float X, float Y, float Z)
{
fxVector * p2 = new fxVector(X, Y, Z);
p2->Sub(data);
return p2->Length();
}

float fxVector::Distance(fxVectorData Data)
{
fxVector * p2 = new fxVector(Data);
p2->Sub(data);
return p2->Length();
}

float fxVector::Distance(fxVector * vector)
{
fxVector * p2;
p2 = vector->Clone();
p2->Sub(data);
return p2->Length();
}

float fxVector::DotProduct(float X, float Y, float Z)
{
return (data[0]*X + data[1]*Y + data[2]*Z);
}

float fxVector::DotProduct(fxVectorData Data)
{
return (data[0]*Data[0] + data[1]*Data[1] + data[2]*Data[2]);
}

float fxVector::DotProduct(fxVector * vector)
{
return (data[0]*vector->data[0] + data[1]*vector->data[1] + data[2]*vector->data[2]);
}

fxVector * fxVector::CrossProduct(float X, float Y, float Z)
{
fxVector * r = new fxVector;
r->Set(data[1]*Z - data[2]*Y,
       data[2]*X - data[0]*Z,
       data[0]*Y - data[1]*X);
return r;
}

fxVector * fxVector::CrossProduct(fxVectorData Data)
{
fxVector * r = new fxVector;
r->Set(data[1]*Data[2] - data[2]*Data[1],
       data[2]*Data[0] - data[0]*Data[2],
       data[0]*Data[1] - data[1]*Data[0]);
return r;
}

fxVector * fxVector::CrossProduct(fxVector * vector)
{
fxVector * r = new fxVector;
r->Set(data[1]*vector->data[2] - data[2]*vector->data[1],
       data[2]*vector->data[0] - data[0]*vector->data[2],
       data[0]*vector->data[1] - data[1]*vector->data[0]);
return r;
}
/*
void fxVector::Transform(fxMatrix * matrix)
{
fxVector Result;
Result.data[0]=data[0]*matrix->data[0][0]+data[1]*matrix->data[0][1]+data[2]*matrix->data[0][2]+matrix->data[0][3];
Result.data[1]=data[0]*matrix->data[1][0]+data[1]*matrix->data[1][1]+data[2]*matrix->data[1][2]+matrix->data[1][3];
Result.data[2]=data[0]*matrix->data[2][0]+data[1]*matrix->data[2][1]+data[2]*matrix->data[2][2]+matrix->data[2][3];

data[0] = Result.data[0];
data[1] = Result.data[1];
data[2] = Result.data[2];
}
*/
