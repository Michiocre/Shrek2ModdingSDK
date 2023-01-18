/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include "Shrek2ModdingSDK.h"

Shrek2Vector3::Shrek2Vector3() 
{
	X = 0;
	Y = 0;
	Z = 0;
}
Shrek2Vector3::Shrek2Vector3(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}
Shrek2Vector3::Shrek2Vector3(float size)
{
	X = size;
	Y = size;
	Z = size;
}

Shrek2Vector3 Shrek2Vector3::operator - (Shrek2Vector3 obj) {
		Shrek2Vector3 res;
		res.X = X - obj.X;
		res.Y = Y - obj.Y;
		res.Z = Z - obj.Z;
		return res;
	}

float Shrek2Vector3::length()
{
	return sqrtf(X*X + Y*Y + Z*Z);
}


Shrek2Vector3Int::Shrek2Vector3Int() 
{
	X = 0;
	Y = 0;
	Z = 0;
}
Shrek2Vector3Int::Shrek2Vector3Int(int x, int y, int z)
{
	X = x;
	Y = y;
	Z = z;
}
Shrek2Vector3Int::Shrek2Vector3Int(int size)
{
	X = size;
	Y = size;
	Z = size;
}

Shrek2Vector3Int Shrek2Vector3Int::operator - (Shrek2Vector3Int obj) {
	Shrek2Vector3Int res;
	res.X = X - obj.X;
	res.Y = Y - obj.Y;
	res.Z = Z - obj.Z;
	return res;
}

int Shrek2Vector3Int::length()
{
	return sqrt(X*X + Y*Y + Z*Z);
}