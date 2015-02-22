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

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "prerequisites.h"
#include "math/Vector4.h"

namespace ColladaLoader
{

class Material
{
public:
	//topological identity
	typedef enum
	{
		MT_NO_TYPE = 0,
		MT_CONSTANT,
		MT_LAMBERT,
		MT_BLINN,
		MT_PHONG
	} MaterialType;
public:
	Material(const std::string& id);
	virtual ~Material();

	const std::string& getID(void);
	void setName(const std::string& name);
	const std::string& getName(void);
	void setMaterialType(MaterialType materialType);
	MaterialType getMaterialType(void) const;

	void setDiffuseTextureName(const std::string& name);
	const std::string& getDiffuseTextureName(void);

	void setEmmision(const Vector4& emmision);
	void setAmbient(const Vector4& ambient);
	void setDiffuse(const Vector4& diffuse);
	void setSpecular(const Vector4& specular);
	void setShininess(const float shininess);

	Vector4 getEmission(void);
	Vector4 getAmbient(void);
	Vector4 getDiffuse(void);
	Vector4 getSpecular(void);
	float getShininess(void);
private:
	MaterialType materialType_;
	const std::string id_;
	std::string name_;

	std::string diffuseTextureName_;

	Vector4 emmision_;
	Vector4 ambient_;
	Vector4 diffuse_;
	Vector4 specular_;

	float shininess_;

};

}

#endif /* MATERIAL_H_ */
