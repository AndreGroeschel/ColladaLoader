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

#include "core/ComponentFactory.h"
#include "components/Geometry.h"
#include "components/Appearance.h"

namespace ColladaLoader
{

template<> ComponentFactory* Singleton<ComponentFactory>::ms_Singleton = 0;
ComponentFactory* ComponentFactory::getSingletonPtr(void)
{
	if (!ms_Singleton)
		ms_Singleton = new ComponentFactory();
	return ms_Singleton;
}
ComponentFactory& ComponentFactory::getSingleton(void)
{
	if (!ms_Singleton)
		ms_Singleton = new ComponentFactory();

	assert(ms_Singleton);
	return (*ms_Singleton);
}

ComponentFactory::ComponentFactory()
{

}

ComponentFactory::~ComponentFactory()
{

}

ComponentPtr ComponentFactory::getInstance(const std::string& componentType,
		Node* owner, ParamListPtr parameters)
{
	ComponentPtr componentPtr;

	if (componentType == "Geometry")
	{
		componentPtr = ComponentPtr(new Geometry(owner, parameters));
		componentPtr->setType("Geometry");
	}
	else if (componentType == "Appearance")
	{
		componentPtr = ComponentPtr(new Appearance(owner, parameters));
		componentPtr->setType("Appearance");
	}
	else
	{
		std::stringstream str;
		str << "Error while attempting to create Component: Component type ["
				<< componentType << "] does not exist.";
		ERROR(str.str());
	}
	return componentPtr;
}
}
