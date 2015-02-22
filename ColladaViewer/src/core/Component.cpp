#include "core/Component.h"

namespace ColladaLoader
{
Component::Component(Node* ownerNode, ParamListPtr parameters) :
	ownerNode_(ownerNode), parameters_(parameters), initialised_(false)
{
}

Component::~Component()
{
}

void Component::setInitialised(const bool& isInitialised)
{
	initialised_ = isInitialised;
}

const bool Component::isInitialised(void)
{
	return initialised_;
}

void Component::setOwnerNode(Node* node)
{
	ownerNode_ = node;
}

Node* Component::getOwnerNode()
{
	return ownerNode_;
}

void Component::setType(const std::string& type)
{
	type_ = type;
}

const std::string& Component::getType()
{
	return type_;
}
}
