#include "core/Component.h"
#include "core/ComponentFactory.h"
#include "core/Node.h"

namespace ColladaLoader
{
Node::Node() :
	childNode_(NULL), parentNode_(NULL), nextNode_(NULL), childrenCount_(0),
			name_(""), ID_(""), scopedID_("")
{

}

Node::~Node()
{
	LOG("Node " + this->getName() + " deleted")

	//clear all component vectors
	for (componentIt_ = components_.begin(); componentIt_ != components_.end(); componentIt_++)
	{
		Components currComponents = componentIt_->second;
		currComponents.clear();
	}
	components_.clear();
}

void Node::addChild(Node* childNode)
{
	if (childNode_ == NULL)
	{
		childNode_ = childNode;
	}
	else
	{
		LOG("Added child node " + childNode->getID() + " to node " + this->getID());
		childNode->setNextNode(childNode_);
		childNode_ = childNode;
	}
	++childrenCount_;
}

void Node::setParent(Node* parentNode)
{
	parentNode_ = parentNode;
}

Node* Node::setNextNode(Node* nextNode)
{
	nextNode_ = nextNode;
	return this;
}

Node* Node::getNext(void) const
{
	return nextNode_;
}

Node* Node::getParent(void) const
{
	return parentNode_;
}

Node* Node::getChild(void) const
{
	return childNode_;
}

bool Node::hasChildren(void)
{
	if (childrenCount_ > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const uint32 Node::getChildrenCount(void)
{
	return childrenCount_;
}

void Node::setName(const std::string& name)
{
	name_ = name;
}

const std::string& Node::getName(void) const
{
	return name_;
}

void Node::setID(const std::string& id)
{
	ID_ = id;
}

const std::string& Node::getID(void) const
{
	return ID_;
}

void Node::setScopedID(const std::string& sid)
{
	scopedID_ = sid;
}

const std::string& Node::getScopedID(void) const
{
	return scopedID_;
}

const uint32 Node::getComponentCount()
{
	return components_.size();
}

ComponentPtr Node::addComponent(const std::string& type,
		ParamListPtr parameters)
{
	ComponentPtr component = ComponentFactory::getSingletonPtr()->getInstance(
			type, this, parameters);
	return addComponent(component);
}

ComponentPtr Node::addComponent(ComponentPtr component)
{
	if (component != NULL)
	{
		const std::string& componentType = component->getType();
		LOG("Type:" + componentType);
		components_[componentType].push_back(component);

		//initialise component
		bool initialised = component->initialise();
		if (!initialised)
		{
			ERROR("Could not initialise component " + component->getType() + " in node " + this->getName())
		}

		return component;
	}
	return ComponentPtr();
}

Node::Components Node::getComponents(const std::string& componentType)
{
	if (components_.find(componentType) != components_.end())
	{
		return components_.find(componentType)->second;
	}

	Components emptyVector;
	return emptyVector;
}

const bool Node::hasComponents(const std::string& componentType)
{
	if (components_.find(componentType) != components_.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Node::listComponents(void)
{
	for (componentIt_ = components_.begin(); componentIt_ != components_.end(); componentIt_++)
	{
		Components currComponents = componentIt_->second;
		std::cout << "Components of type: " << componentIt_->first
				<< currComponents.size() << std::endl;
	}
}
}
