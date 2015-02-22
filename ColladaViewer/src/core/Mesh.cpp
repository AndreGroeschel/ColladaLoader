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

#include <GL/gl.h>

#include <dae.h>
#include <dom/domCOLLADA.h>
#include "utils/StringUtils.h"
#include "core/Mesh.h"

namespace ColladaLoader
{

Mesh::Mesh() :
	meshType_(MT_NO_TYPE), pointCount_(0), vertexCount_(0), normalCount_(0),
			texCoordCount_(0), materialBindingID_("")
{
}

Mesh::~Mesh()
{
	vertexIndices_.clear();
	normalIndices_.clear();
	texCoordIndices_.clear();
	colorIndices_.clear();
	vertices_.clear();
	normals_.clear();
	texCoords_.clear();
	colors_.clear();

}

void Mesh::setPointCount(const uint32 pointCount)
{
	pointCount_ = pointCount;
	vertexIndices_.reserve(pointCount);
	normalIndices_.reserve(pointCount);
	texCoordIndices_.reserve(pointCount);
	colorIndices_.reserve(pointCount);
}

void Mesh::setVertexCount(const uint32 vertexCount)
{
	vertexCount_ = vertexCount;
	vertices_.reserve(vertexCount);
}

void Mesh::setNormalCount(const uint32 normalCount)
{
	normalCount_ = normalCount;
	normals_.reserve(normalCount);
}

void Mesh::setTexCoordCount(const uint32 texCoordCount)
{
	texCoordCount_ = texCoordCount;
	texCoords_.reserve(texCoordCount);
}

void Mesh::setColorCount(const uint32 colorCount)
{
	colorCount_ = colorCount;
	colors_.reserve(colorCount);
}

uint32 Mesh::getPointCount(void) const
{
	return pointCount_;
}

void Mesh::addVertexIndex(const uint32 index)
{
	//Triangle.vertexIndices[pos] = index;
	vertexIndices_.push_back(index);
}
void Mesh::addNormalIndex(const uint32 index)
{
	normalIndices_.push_back(index);
}
void Mesh::addTexCoordIndex(const uint32 index)
{
	texCoordIndices_.push_back(index);
}

void Mesh::addColorIndex(const uint32 index)
{
	colorIndices_.push_back(index);
}

void Mesh::addVertex(const float vertex)
{
	vertices_.push_back(vertex);
}

void Mesh::addNormal(const float normal)
{
	normals_.push_back(normal);
}

void Mesh::addTexCoord(const float texCoord)
{
	texCoords_.push_back(texCoord);
}

void Mesh::addColor(const float color)
{
	colors_.push_back(color);
}

std::vector<uint32>& Mesh::getVertexIndices()
{
	return vertexIndices_;
}

std::vector<uint32>& Mesh::getNormalIndices()
{
	return normalIndices_;
}

std::vector<uint32>& Mesh::getTexCoordIndices()
{
	return texCoordIndices_;
}

std::vector<uint32>& Mesh::getColorIndices()
{
	return colorIndices_;
}

std::vector<float>& Mesh::getVertices()
{
	return vertices_;
}

std::vector<float>& Mesh::getNormals()
{
	return normals_;
}

std::vector<float>& Mesh::getTexCoords()
{
	return texCoords_;
}

std::vector<float>& Mesh::getColors()
{
	return colors_;
}

void Mesh::setMeshType(MeshType meshType)
{
	meshType_ = meshType;
}

Mesh::MeshType Mesh::getMeshType(void) const
{
	return meshType_;
}

void Mesh::setMaterialBinding(const std::string& materialID)
{
	materialBindingID_ = materialID;
}

const std::string& Mesh::getMaterialBinding(void)
{
	return materialBindingID_;
}

}

