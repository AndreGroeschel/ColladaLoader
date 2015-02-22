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

#include "math/Vector4.h"

namespace ColladaLoader
{

Vector4::Vector4(const Vector4 &vector)
{
	vector4_[0] = vector.getX();
	vector4_[1] = vector.getY();
	vector4_[2] = vector.getZ();
	vector4_[3] = vector.getW();
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->setX(x);
	this->setY(y);
	this->setZ(z);
	this->setW(w);
}

Vector4::Vector4(float vector[4])
{
	vector4_[0] = vector[0];
	vector4_[1] = vector[1];
	vector4_[2] = vector[2];
	vector4_[3] = vector[3];
}

void Vector4::setX(float x)
{
	this->vector4_[0] = x;
}
void Vector4::setY(float y)
{
	this->vector4_[1] = y;
}
void Vector4::setZ(float z)
{
	this->vector4_[2] = z;
}
void Vector4::setW(float w)
{
	this->vector4_[3] = w;
}

float Vector4::getX() const
{
	return this->vector4_[0];
}
float Vector4::getY() const
{
	return this->vector4_[1];
}
float Vector4::getZ() const
{
	return this->vector4_[2];
}
float Vector4::getW() const
{
	return this->vector4_[3];
}

void Vector4::setXYZW(float x, float y, float z, float w)
{
	this->vector4_[0] = x;
	this->vector4_[1] = y;
	this->vector4_[2] = z;
	this->vector4_[3] = w;
}

float Vector4::getNormal() const
{
	return sqrt(this->dot(*this));
}

float Vector4::dot(const Vector4 &vector) const
{
	return vector4_[0] * vector.getX() + vector4_[1] * vector.getY()
			+ vector4_[2] * vector.getZ() + vector4_[3] * vector.getW();
}

float Vector4::operator*(const Vector4 &vector) const
{
	return this->dot(vector);
}

Vector4 Vector4::getVersor() const
{
	float normal = this->getNormal();
	return Vector4(vector4_[0] / normal, vector4_[1] / normal, vector4_[2]
			/ normal, vector4_[3] / normal);
}

void Vector4::normalize()
{
	float normal = this->getNormal();

	if (normal == 0.0f)
		return;

	vector4_[0] /= normal;
	vector4_[1] /= normal;
	vector4_[2] /= normal;
	vector4_[3] /= normal;
}

Vector4 Vector4::operator+(const Vector4 &vector) const
{
	return Vector4(vector4_[0] + vector.vector4_[0],
			vector4_[1] + vector.vector4_[1], vector4_[2] + vector.vector4_[2],
			vector4_[3] + vector.vector4_[3]);
}

Vector4 Vector4::operator+=(const Vector4 &vector)
{
	vector4_[0] += vector.vector4_[0];
	vector4_[1] += vector.vector4_[1];
	vector4_[2] += vector.vector4_[2];
	vector4_[3] += vector.vector4_[3];
	return *this;
}

Vector4 Vector4::operator-(const Vector4 &vector) const
{
	return Vector4(vector4_[0] - vector.vector4_[0],
			vector4_[1] - vector.vector4_[1], vector4_[2] - vector.vector4_[2],
			vector4_[3] - vector.vector4_[3]);
}

Vector4 Vector4::operator-=(const Vector4 &vector)
{
	vector4_[0] -= vector.vector4_[0];
	vector4_[1] -= vector.vector4_[1];
	vector4_[2] -= vector.vector4_[2];
	vector4_[3] -= vector.vector4_[3];
	return *this;
}

Vector4 Vector4::operator*(float factor) const
{
	return Vector4(vector4_[0] * factor, vector4_[1] * factor, vector4_[2]
			* factor, vector4_[3] * factor);
}

Vector4 Vector4::operator*=(float factor)
{
	vector4_[0] *= factor;
	vector4_[1] *= factor;
	vector4_[2] *= factor;
	vector4_[3] *= factor;
	return *this;
}

Vector4 Vector4::operator/(float factor) const
{
	return Vector4(vector4_[0] / factor, vector4_[1] / factor, vector4_[2]
			/ factor, vector4_[3] / factor);
}

Vector4 Vector4::operator/=(float factor)
{

	vector4_[0] /= factor;
	vector4_[1] /= factor;
	vector4_[2] /= factor;
	vector4_[3] /= factor;
	return *this;
}

Vector4 Vector4::operator=(const Vector4 &vector){
	vector4_[0] = vector.vector4_[0];
	vector4_[1] = vector.vector4_[1];
	vector4_[2] = vector.vector4_[2];
	vector4_[3] = vector.vector4_[3];

	return *this;
}

Vector4 *Vector4::operator=(Vector4 *vector){
	vector4_[0] = vector->vector4_[0];
	vector4_[1] = vector->vector4_[1];
	vector4_[2] = vector->vector4_[2];
	vector4_[3] = vector->vector4_[3];

	return this;
}
bool Vector4::operator==(const Vector4 &vector) const
{
	if ((vector4_[0] == vector.vector4_[0]) && (vector4_[1] == vector.vector4_[1])
			&& (vector4_[2] == vector.vector4_[2]) && (vector4_[3]
			== vector.vector4_[3]))
		return true;
	return false;

}

const float *Vector4::toArray()
{
	return vector4_;
}
const Vector4 Vector4::ZERO( 0, 0, 0, 0 );
}
