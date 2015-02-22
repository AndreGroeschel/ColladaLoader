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

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <dom/domElements.h>
#include "prerequisites.h"
#include "core/Component.h"

//DOM forward declarations
class domGeometry;

namespace ColladaLoader
{
class Geometry: public ColladaLoader::Component
{
public:
	typedef enum
	{
		GT_NO_TYPE = 0,
		GT_MESH,
		GT_CONVEX_MESH,
		GT_SPLINE,
		GT_EXTRA
	} GeometryType;
public:
	Geometry(Node* ownerNode, ParamListPtr parameters);
	virtual ~Geometry();

	const bool initialise(void);

	const std::string& getID(void);
	const std::string& getName(void);

	const std::vector<Mesh*> getMeshes(void);
	bool hasMeshes(void);

private:
	std::vector<Mesh*> meshes_;
	GeometryType geometryType_;
    std::string id_;
    std::string name_;

	const bool processGeometry(domGeometry* geometry);
	void processTriangles(const domTriangles_Array& triangleGroups);
	void processPrimitive(domInputLocalOffset* input, size_t maxOffset);
	void processPrimitive(Mesh* mesh, domP* primitive, domString semantic, domUint offset, domUint set, size_t inputCount);
	void processElement(Mesh* mesh, domElement* element, domString semantic);
};
}

#endif /* GEOMETRY_H_ */
