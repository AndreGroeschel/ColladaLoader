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

#ifndef DAEDOCUMENT_H_
#define DAEDOCUMENT_H_

#include "prerequisites.h"
#include "utils/Singleton.h"
#include <dom/domTypes.h>

namespace ColladaLoader
{

/**
 * Singleton + Proxy Pattern
 */

class DaeDocument: public Singleton<DaeDocument>
{
public:
	typedef enum {
		UP_AXIS_X = 0,
		UP_AXIS_Y,
		UP_AXIS_Z
	} UpAxis;

public:
	DaeDocument();
	virtual ~DaeDocument();

	bool load(domCOLLADA* colladaDocument);
	void readGeometry(void);

	float getAssetUnitMeter() const;
	UpAxis getAssetUpAxis() const;

	domVisual_sceneRef getVisualScene(void);

	void printAssetInformation(void);

	static DaeDocument& getSingleton(void);
	static DaeDocument* getSingletonPtr(void);

private:
	domCOLLADA* colladaDocument_;
	UpAxis assetUpAxis_;
};

}

#endif /* DAEDOCUMENT_H_ */
