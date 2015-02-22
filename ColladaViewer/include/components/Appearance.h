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

#ifndef APPEARANCE_H_
#define APPEARANCE_H_

#include <dom/domProfile_COMMON.h>
#include "prerequisites.h"
#include "core/Component.h"

//DOM forward declarations
class domBind_material;
class domCommon_newparam_type;

namespace ColladaLoader
{

class Appearance: public Component
{
public:
	Appearance(Node* ownerNode, ParamListPtr parameters);
	virtual ~Appearance();

	const bool initialise(void);
	Material* getMaterial(const std::string& materialID);
	void listMaterials();
private:
	std::map<std::string,Material*> materials_;
	std::map<std::string, domCommon_newparam_type*> newParameters_;

	const bool processBindMaterial(domBind_material* bindMaterial);
	const bool processEffect(domInstance_effectRef effectInstance, Material* material);

	void processConstant(domProfile_COMMON::domTechnique::domConstant* constant, Material* material);
	void processLambert(domProfile_COMMON::domTechnique::domLambert* lambert, Material* material);
	void processBlinn(domProfile_COMMON::domTechnique::domBlinn* blinn, Material* material);
	void processPhong(domProfile_COMMON::domTechnique::domPhong* phong, Material* material);

	const Vector4 readColor(domCommon_color_or_texture_typeRef color);
	const std::string getTextureName(domCommon_color_or_texture_type::domTexture* texture, Material* material);
};

}

#endif /* APPEARANCE_H_ */
