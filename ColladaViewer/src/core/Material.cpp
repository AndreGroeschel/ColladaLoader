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
