/*
The MIT License (MIT)

Copyright (c) 2010 Andre Groeschel

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef VECTOR4_H
#define VECTOR4_H
#include <cmath>
#include "prerequisites.h"

namespace ColladaLoader
{

class Vector4
{
public:
	Vector4(const Vector4 &vector);
	Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);
	Vector4(float vet[4]);

	~Vector4()
	{
	}

	//Setters
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setW(float w);
	void setXYZW(float x, float y, float z, float w);

	//Getters
	float getX() const;
	float getY() const;
	float getZ() const;
	float getW() const;
	float& operator[](const long i)
	{
		return vector4_[i];
	}

	float getNormal() const;
	float dot(const Vector4 &vector) const;
	Vector4 getVersor() const;
	float operator*(const Vector4 &vector) const;

	void normalize();

	//Operations
	Vector4 operator+(const Vector4 &vector) const;
	Vector4 operator+=(const Vector4 &vector);
	Vector4 operator-(const Vector4 &vector) const;
	Vector4 operator-=(const Vector4 &vector);
	Vector4 operator*(float factor) const;
	Vector4 operator*=(float factor);
	Vector4 operator/(float factor) const;
	Vector4 operator/=(float factor);
	Vector4 operator=(const Vector4 &vector);
	Vector4 *operator=(Vector4 *vector);
	bool operator==(const Vector4 &vector) const;

	const float *toArray();

	static const Vector4 ZERO;

private:
	float vector4_[4];
};
}
#endif // VECTOR4_H
