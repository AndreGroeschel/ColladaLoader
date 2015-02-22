#include <dae.h>
#include <dom/domGeometry.h>
#include <dom/domMaterial.h>
#include <dom/domBind_material.h>
#include <dom/domEffect.h>
#include <dom/domCommon_newparam_type.h>
#include "core/ParamList.h"
#include "core/Material.h"
#include "math/Vector4.h"
#include "utils/StringUtils.h"
#include "components/Appearance.h"

namespace ColladaLoader
{

Appearance::Appearance(Node* ownerNode, ParamListPtr parameters) :
	Component(ownerNode, parameters)
{

}

Appearance::~Appearance()
{
	//delete all materials
	std::map<std::string, Material*>::const_iterator materialIt;
	for (materialIt = materials_.begin(); materialIt != materials_.end(); materialIt++)
	{
		delete materialIt->second;
	}
	materials_.clear();
}

const bool Appearance::initialise(void)
{
	if (parameters_->hasParameter("domBindMaterial"))
	{
		domBind_material* bindMaterial = boost::any_cast<domBind_material*>(
				parameters_->getValue("domBindMaterial"));

		initialised_ = processBindMaterial(bindMaterial);
		return initialised_;
	}
	return false;
}

Material* Appearance::getMaterial(const std::string& materialID)
{
	if (materials_.find(materialID) != materials_.end())
	{
		return materials_.find(materialID)->second;
	}
	return NULL;
}

const bool Appearance::processBindMaterial(domBind_material* bindMaterial)
{
	domInstance_material_Array &materials =
			bindMaterial->getTechnique_common()->getInstance_material_array();

	size_t materialCount = materials.getCount();
	for (size_t i = 0; i < materialCount; i++)
	{
		domInstance_materialRef materialInstance = materials.get(i);

		//find the material element to which the instance points
		domElement* element = materialInstance->getTarget().getElement();
		domMaterial* currentMaterial = daeSafeCast<domMaterial> (element);

		//create a new material
		Material* material = new Material(currentMaterial->getID());
		//add to material map using the instances symbol
		materials_[materialInstance->getSymbol()] = material;

		processEffect(currentMaterial->getInstance_effect(), material);

	}
	return true;
}

const bool Appearance::processEffect(domInstance_effectRef effectInstance,
		Material* material)
{
	//find the effect element to which the instance points
	domElement* element = effectInstance->getUrl().getElement();
	domEffect* effect = daeSafeCast<domEffect> (element);

	if (effect == NULL)
	{
		ERROR("Could not find effect" + std::string(effectInstance->getID()));
		return false;
	}

	domFx_profile_abstract_Array profiles =
			effect->getFx_profile_abstract_array();
	size_t profileCount = profiles.getCount();

	for (size_t i = 0; i < profileCount; i++)
	{
		if (profiles.get(i)->getElementType() == COLLADA_TYPE::PROFILE_COMMON)
		{
			domProfile_COMMON* profileCommon = daeSafeCast<domProfile_COMMON> (
					profiles.get(i));
			domProfile_COMMON::domTechniqueRef technique =
					profileCommon->getTechnique();

			//check what kind of technique we have
			domProfile_COMMON::domTechnique::domConstant* constant =
					technique->getConstant();
			domProfile_COMMON::domTechnique::domLambert* lambert =
					technique->getLambert();
			domProfile_COMMON::domTechnique::domBlinn* blinn =
					technique->getBlinn();
			domProfile_COMMON::domTechnique::domPhong* phong =
					technique->getPhong();

			//store all newparam element (texture ids can be found here)
			domCommon_newparam_type_Array newParams = profileCommon->getNewparam_array();
			size_t newParamCount = newParams.getCount();
			for (size_t i=0; i<newParamCount; i++) {
				newParameters_[newParams[i]->getSid()] = newParams[i];
			}

			//delegate to appropriate method
			if (constant != NULL)
				processConstant(constant, material);
			if (lambert != NULL)
				processLambert(lambert, material);
			if (blinn != NULL)
				processBlinn(blinn, material);
			if (phong != NULL)
				processPhong(phong, material);
		}
	}
	return true;
}

void Appearance::processConstant(
		domProfile_COMMON::domTechnique::domConstant* constant,
		Material* material)
{
	material->setMaterialType(Material::MT_CONSTANT);
}

void Appearance::processLambert(
		domProfile_COMMON::domTechnique::domLambert* lambert,
		Material* material)
{
	//check if there is a texture in the diffuse channel
	if(lambert->getDiffuse()->getTexture()!= NULL)
	{
		std::string fileName = getTextureName(lambert->getDiffuse()->getTexture(), material);
		material->setDiffuseTextureName(fileName);
	}

	material->setMaterialType(Material::MT_LAMBERT);
	material->setEmmision(readColor(lambert->getEmission()));
	material->setAmbient(readColor(lambert->getAmbient()));
	material->setDiffuse(readColor(lambert->getDiffuse()));
}

void Appearance::processBlinn(domProfile_COMMON::domTechnique::domBlinn* blinn,
		Material* material)
{
	//check if there is a texture in the diffuse channel
	if(blinn->getDiffuse()->getTexture()!= NULL)
	{
		std::string fileName = getTextureName(blinn->getDiffuse()->getTexture(), material);
		material->setDiffuseTextureName(fileName);
	}

	material->setMaterialType(Material::MT_BLINN);
	material->setEmmision(readColor(blinn->getEmission()));
	material->setAmbient(readColor(blinn->getAmbient()));
	material->setDiffuse(readColor(blinn->getDiffuse()));
	material->setSpecular(readColor(blinn->getSpecular()));
	material->setShininess(blinn->getShininess()->getFloat()->getValue());
}

void Appearance::processPhong(domProfile_COMMON::domTechnique::domPhong* phong,
		Material* material)
{
	//check if there is a texture in the diffuse channel
	if(phong->getDiffuse()->getTexture()!= NULL)
	{
		std::string fileName = getTextureName(phong->getDiffuse()->getTexture(), material);
		material->setDiffuseTextureName(fileName);
	}
	material->setMaterialType(Material::MT_PHONG);
	material->setEmmision(readColor(phong->getEmission()));
	material->setAmbient(readColor(phong->getAmbient()));
	material->setDiffuse(readColor(phong->getDiffuse()));
	material->setSpecular(readColor(phong->getSpecular()));
	material->setShininess(phong->getShininess()->getFloat()->getValue());
}

const Vector4 Appearance::readColor(
		domCommon_color_or_texture_typeRef colorOrTexture)
{
	if (colorOrTexture != NULL && colorOrTexture->getColor() != NULL)
	{
		domFx_color_common color = colorOrTexture->getColor()->getValue();
		return Vector4(color[0], color[1], color[2], color[3]);
	}
	return Vector4::ZERO;
}

const std::string Appearance::getTextureName(
		domCommon_color_or_texture_type::domTexture* texture,
		Material* material)
{
	//try to resolve the reference
	std::string sampler2D_SID = texture->getTexture();
	xsIDREF idRef(sampler2D_SID.c_str());
	idRef.setContainer(texture);
	daeElement* element = idRef.getElement();

	//if we cannot find the element via the reference we look in the newParams map
	if(element == NULL)
	{
		element = newParameters_.find(texture->getTexture())->second;
	}

	if(StringUtils::equals(element->getTypeName(), "common_newparam_type"))
	{
		domCommon_newparam_type* newParam = daeSafeCast<domCommon_newparam_type> (element);
		domFx_sampler2D_common* sampler2dCommon = newParam->getSampler2D();
		if(sampler2dCommon != NULL)
		{
			daeElement* sourceElement = newParameters_.find(sampler2dCommon->getSource()->getValue())->second;
			domCommon_newparam_type* source = daeSafeCast<domCommon_newparam_type>(sourceElement);
			domFx_surface_common* surface = daeSafeCast<domFx_surface_common>(source->getSurface());
			//get the first element of the init_from array -> this is the id of the image we are looking for
			idRef = surface->getFx_surface_init_common()->getInit_from_array()[0]->getValue();
			domImage* image = daeSafeCast<domImage>(idRef.getElement());
			//get the file name
			return image->getInit_from()->getValue().getOriginalURI();
		}
	}

	return "";
}

void Appearance::listMaterials()
{
	std::map<std::string, Material*>::iterator materialIt;
	for (materialIt = materials_.begin(); materialIt != materials_.end(); materialIt++)
	{
		LOG(materialIt->first);
	}
}

}
