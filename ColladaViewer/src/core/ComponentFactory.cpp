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
