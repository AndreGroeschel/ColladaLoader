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

#include "utils/StringUtils.h"
#include "core/Material.h"


namespace ColladaLoader
{

Material::Material(const std::string& id) :
	materialType_(MT_NO_TYPE), id_(id), shininess_(0.0)
{
}

Material::~Material()
{

}

const std::string& Material::getID(void)
{
	return id_;
}

void Material::setName(const std::string& name)
{
	name_ = name;
}
const std::string& Material::getName(void)
{
	return name_;
}

void Material::setMaterialType(MaterialType materialType)
{
	materialType_ = materialType;
}

Material::MaterialType Material::getMaterialType(void) const
{
	return materialType_;
}


void Material::setDiffuseTextureName(const std::string& name)
{
	//search for beginning "/" in filename and strip it off
	size_t begin = name.find('/');

	if(begin != std::string::npos)
	{
		diffuseTextureName_ = name.substr(begin+1,name.length());
	} else {
		diffuseTextureName_ = name;
	}



}
const std::string& Material::getDiffuseTextureName(void)
{
	return diffuseTextureName_;
}


void Material::setEmmision(const Vector4& emmision)
{
	emmision_ = emmision;
}

void Material::setAmbient(const Vector4& ambient)
{
	ambient_ = ambient;
}
void Material::setDiffuse(const Vector4& diffuse)
{
	diffuse_ = diffuse;
}

void Material::setSpecular(const Vector4& specular)
{
	specular_ = specular;
}

void Material::setShininess(const float shininess)
{
	shininess_ = shininess;
}

Vector4 Material::getEmission(void)
{
	return emmision_;
}
Vector4 Material::getAmbient(void)
{
	return ambient_;
}

Vector4 Material::getDiffuse(void)
{
	return diffuse_;
}

Vector4 Material::getSpecular(void)
{
	return specular_;
}
float Material::getShininess(void)
{
	return shininess_;
}
}
