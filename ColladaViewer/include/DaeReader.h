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

#ifndef DAEREADER_H_
#define DAEREADER_H_

#include "prerequisites.h"

//forward declarations
class DAE;
class domCOLLADA;

namespace ColladaLoader
{

/**
* The @c daeIOPlugin class provides the input/output plugin interface, which is
* the interface between the COLLADA runtime and the backend storage. A native
* COLLADA XML plugin implementation is provided along with this interface.
*/
class DaeReader
{
public:
	DaeReader();
	virtual ~DaeReader();

	/**
	* Sets the top meta object.
	* Called by @c dae::setIOPlugin() when the IO plugin changes. It passes to this function the
	* top meta object, which is the root of a
	* hierarchy of @c daeMetaElement objects. This top meta object is capable of creating
	* any of the root objects in the DOM tree.
	* @param topMeta Top meta object to use to create objects to fill the database.
	* @return Returns DAE_OK if successful, otherwise returns a negative value defined in daeError.h.
	*/
	void load(const std::string& path);

private:
	DAE* dae_;
	DaeDocument* daeDocument_;
	NodeManager* nodeManager_;
	ComponentFactory* componentFactory_;
	SceneReader* sceneReader_;
	std::string filePath_;
};


}

#endif /* DAEREADER_H_ */
