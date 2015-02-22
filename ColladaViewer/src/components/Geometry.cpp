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

#include <dae.h>
#include <dom/domGeometry.h>
#include <boost/any.hpp>
#include "core/Node.h"
#include "core/ParamList.h"
#include "core/Mesh.h"
#include "components/Geometry.h"
#include "utils/StringUtils.h"

namespace ColladaLoader
{

Geometry::Geometry(Node* ownerNode, ParamListPtr parameters) :
	Component(ownerNode, parameters), geometryType_(GT_NO_TYPE), id_(""),
			name_("")
{

}

Geometry::~Geometry()
{
	for (size_t i = 0; i < meshes_.size(); i++)
	{
		if (meshes_[i] != NULL)
			delete meshes_[i];
	}
	meshes_.clear();
}
const bool Geometry::initialise()
{

	if (parameters_->hasParameter("domGeometry"))
	{
		domGeometry* geometry = boost::any_cast<domGeometry*>(
				parameters_->getValue("domGeometry"));
		id_ = geometry->getID();
		name_ = geometry->getName();

		LOG("Created Geometry component with ID: " + id_);
		initialised_ = processGeometry(geometry);
	}

	return initialised_;
}

const std::string& Geometry::getID()
{
	return id_;
}

const std::string& Geometry::getName(void)
{
	return name_;
}

const std::vector<Mesh*> Geometry::getMeshes(void)
{
	return meshes_;
}

bool Geometry::hasMeshes(void)
{
	if (meshes_.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const bool Geometry::processGeometry(domGeometry* geometry)
{

	//see what type of geometry we are dealing with
	domAsset* assetGeo = geometry->getAsset();
	domMesh* meshGeo = geometry->getMesh();
	domConvex_mesh* convexMeshGeo = geometry->getConvex_mesh();
	domSpline* splineGeo = geometry->getSpline();

	//unsupported geometry types
	if ((assetGeo != NULL) || (convexMeshGeo != NULL) || (splineGeo != NULL))
	{
		ERROR("Node: " + getOwnerNode()->getName() + " contains an unsupported geometry type");
		return false;
	}

	if (meshGeo == NULL)
	{
		ERROR("Error while loading mesh element");
		return false;
	}

	//triangles
	domTriangles_Array triangles = meshGeo->getTriangles_array();
	if (triangles.getCount() > 0)
	{
		//process first triangle group
		processTriangles(triangles);
	}
	return true;
}

void Geometry::processTriangles(const domTriangles_Array& triangleGroups)
{
	size_t triangleGroupCount = triangleGroups.getCount();
	for (size_t i = 0; i < triangleGroupCount; i++)
	{
		Mesh* currentMesh = new Mesh;
		meshes_.push_back(currentMesh);
		currentMesh->setMeshType(Mesh::MT_TRIANGLES);

		domTriangles* currentTriangleGroup = triangleGroups[i];

		//set associated material id
		currentMesh->setMaterialBinding(currentTriangleGroup->getMaterial());

		domP *currentPrimitive = currentTriangleGroup->getP();

		//allocate memory for points (each triangle is composed of 3 points)
		currentMesh->setPointCount((size_t) (currentTriangleGroup->getCount()
				* 3));

		domInputLocalOffset_Array& inputs =
				currentTriangleGroup->getInput_array();
		size_t maxOffset = inputs.getCount();
		for (size_t i = 0; i < maxOffset; i++)
		{
			domInputLocalOffset* currentInput = inputs[i];
			domString semantic = currentInput->getSemantic();
			domElement* sourceElement = currentInput->getSource().getElement();
			domUint offset = currentInput->getOffset();
			domUint set = currentInput->getSet();

			processElement(currentMesh, sourceElement, semantic);
			processPrimitive(currentMesh, currentPrimitive, semantic, offset,
					set, maxOffset);
		}
	}
}

void Geometry::processPrimitive(Mesh* mesh, domP* primitive,
		domString semantic, domUint offset, domUint set, size_t maxOffset)
{

	if (StringUtils::equals(semantic, "VERTEX"))
	{
		for (size_t i = offset; i < primitive->getValue().getCount(); i
				+= maxOffset)
		{
			//insert the triangle vertex index
			mesh->addVertexIndex((uint32) primitive->getValue().get(i));
		}
	}
	if (StringUtils::equals(semantic, "NORMAL"))
	{
		for (size_t i = offset; i < primitive->getValue().getCount(); i
				+= maxOffset)
		{
			//insert the triangle normal index
			mesh->addNormalIndex((uint32) primitive->getValue().get(i));
		}
	}
	if (StringUtils::equals(semantic, "TEXCOORD"))
	{
		for (size_t i = offset; i < primitive->getValue().getCount(); i
				+= maxOffset)
		{
			//insert the triangle normal index
			mesh->addTexCoordIndex((uint32) primitive->getValue().get(i));
		}
	}
	if (StringUtils::equals(semantic, "COLOR"))
	{
		for (size_t i = offset; i < primitive->getValue().getCount(); i
				+= maxOffset)
		{
			//insert the triangle normal index
			mesh->addColorIndex((uint32) primitive->getValue().get(i));
		}
	}
}

void Geometry::processElement(Mesh* mesh, domElement* element,
		domString semantic)
{
	if (element->getElementType() == COLLADA_TYPE::VERTICES)
	{
		domVertices* vertices = daeSafeCast<domVertices> (element);
		domInputLocal_Array* localInputs = &vertices->getInput_array();

		for (size_t i = 0; i < localInputs->getCount(); i++)
		{
			domInputLocal* localInput = localInputs->get(i);
			domString semantic = localInput->getSemantic();
			domElement* element = localInput->getSource().getElement();
			processElement(mesh, element, semantic);
		}
	}
	if (element->getElementType() == COLLADA_TYPE::SOURCE)
	{
		domSource* source = daeSafeCast<domSource> (element);
		domFloat_array* sourceValues = source->getFloat_array();

		if (StringUtils::equals(semantic, "POSITION"))
		{
			//allocate memory for vertices
			mesh->setVertexCount(sourceValues->getValue().getCount());

			size_t vertexCount = sourceValues->getValue().getCount();
			//insert vertex values into mesh
			for (size_t i = 0; i < vertexCount; i++)
			{
				mesh->addVertex((float) sourceValues->getValue().get(i));
			}
		}
		if (StringUtils::equals(semantic, "NORMAL"))
		{
			//allocate memory for normals
			mesh->setNormalCount(sourceValues->getValue().getCount());

			size_t normalCount = sourceValues->getValue().getCount();
			//insert normal values into mesh
			for (size_t i = 0; i < normalCount; i++)
			{
				mesh->addNormal((float) sourceValues->getValue().get(i));
			}
		}
		if (StringUtils::equals(semantic, "TEXCOORD"))
		{
			//allocate memory for texture coordinates
			mesh->setTexCoordCount(sourceValues->getValue().getCount());

			size_t texCoordCount = sourceValues->getValue().getCount();
			//insert texture coordinate values into mesh
			for (size_t i = 0; i < texCoordCount; i++)
			{
				mesh->addTexCoord((float) sourceValues->getValue().get(i));
			}
		}
		if (StringUtils::equals(semantic, "COLOR"))
		{
			//allocate memory for colors
			mesh->setColorCount(sourceValues->getValue().getCount());

			size_t colorCount = sourceValues->getValue().getCount();
			//insert color values into mesh
			for (size_t i = 0; i < colorCount; i++)
			{
				mesh->addColor((float) sourceValues->getValue().get(i));
			}
		}
	}
}
}
