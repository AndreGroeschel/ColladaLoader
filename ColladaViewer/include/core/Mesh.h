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

#ifndef MESH_H_
#define MESH_H_

#include <dom/domElements.h>
#include "prerequisites.h"

namespace ColladaLoader
{
class Mesh
{
public:
	//topological identity
	typedef enum
	{
		MT_NO_TYPE = 0,
		MT_LINES,
		MT_LINE_STRIP,
		MT_POLYGONS,
		MT_TRIANGLES,
		MT_TRIANGLE_FAN,
		MT_TRIANGLE_STRIP
	} MeshType;

public:
	Mesh();
	virtual ~Mesh();

	void setPointCount(const uint32 pointCount);
	void setVertexCount(const uint32 vertexCount);
	void setNormalCount(const uint32 normalCount);
	void setTexCoordCount(const uint32 texCoordCount);
	void setColorCount(const uint32 colorCount);

	uint32 getPointCount(void) const;

	void addVertexIndex(const uint32 index);
	void addNormalIndex(const uint32 index);
	void addTexCoordIndex(const uint32 index);
	void addColorIndex(const uint32 index);

	void addVertex(const float vertex);
	void addNormal(const float normal);
	void addTexCoord(const float texCoord);
	void addColor(const float texCoord);


	std::vector<uint32>& getVertexIndices();
	std::vector<uint32>& getNormalIndices();
	std::vector<uint32>& getTexCoordIndices();
	std::vector<uint32>& getColorIndices();

	std::vector<float>& getVertices();
	std::vector<float>& getNormals();
	std::vector<float>& getTexCoords();
	std::vector<float>& getColors();

	void setMeshType(MeshType meshType);
	MeshType getMeshType(void) const;

	void setMaterialBinding(const std::string& materialID);
	const std::string& getMaterialBinding(void);

private:
	MeshType meshType_;

	std::vector<float> vertices_;
	std::vector<float> normals_;
	std::vector<float> texCoords_;
	std::vector<float> colors_;

	uint32 pointCount_;
	uint32 vertexCount_;
	uint32 normalCount_;
	uint32 texCoordCount_;
	uint32 colorCount_;

	std::vector<uint32> vertexIndices_;
	std::vector<uint32> normalIndices_;
	std::vector<uint32> texCoordIndices_;
	std::vector<uint32> colorIndices_;

	std::string materialBindingID_;
	};

}

#endif /* MESH_H_ */
