/*
 * XMLNode.cpp
 *
 *  Created on: 26.03.2009
 *      Author: mart
 */

#include "../include/xml/XMLNode.h"

XMLNode::XMLNode()
	: name_(NULL), content_(NULL), parent_(NULL)
{
	// TODO Auto-generated constructor stub

}

XMLNode::~XMLNode()
{
	delete name_;
	delete content_;

	{
		for (std::vector<XMLNode*>::iterator it = children_.begin(); it != children_.end(); it++)
		{
			delete *it;
		}
	}

	{
		for (std::vector<XMLAttribute*>::iterator it = attributes_.begin(); it != attributes_.end(); it++)
		{
			delete *it;
		}
	}
	// TODO Auto-generated destructor stub
}

XMLNode* XMLNode::addChild(XMLNode* childNode)
{
	if (childNode)
	{
		children_.push_back(childNode);
		childNode->setParent(this);
		return childNode;
	}

	return NULL;
}

bool XMLNode::removeChild(XMLNode* childNode)
{
	for (std::vector<XMLNode*>::iterator it = children_.begin(); it != children_.end(); it++)
	{
		if (*it == childNode)
		{
			children_.erase(it);
			return true;
		}
	}

	return false;
}

XMLNode* XMLNode::getFirstChild()
{
	if (children_.size() > 0)
	{
		childIterator_ = children_.begin();
		return *childIterator_;
	}
	else
		return NULL;
}

XMLNode* XMLNode::getNextChild()
{
	if (childIterator_ < children_.end())
	{
		childIterator_++;
		if (childIterator_ < children_.end())
		{
			return *childIterator_;
		}
	}

	return NULL;
}

void XMLNode::addAttribute(XMLAttribute* attribute)
{
	if (attribute)
		attributes_.push_back(attribute);
}

bool XMLNode::removeAttribute(XMLAttribute* attribute)
{
	for (std::vector<XMLAttribute*>::iterator it = attributes_.begin(); it != attributes_.end(); it++)
	{
		if (*it == attribute)
		{
			attributes_.erase(it);
			return true;
		}
	}

	return false;
}

XMLAttribute* XMLNode::getFirstAttribute()
{
	if (attributes_.size() > 0)
	{
		attributeIterator_ = attributes_.begin();
		return *attributeIterator_;
	}
	else
		return NULL;
}

XMLAttribute* XMLNode::getNextAttribute()
{
	if (attributeIterator_ < attributes_.end())
	{
		attributeIterator_++;
		if (attributeIterator_ < attributes_.end())
		{
			return *attributeIterator_;
		}
	}


	return NULL;
}

void XMLNode::setParent(XMLNode* parent)
{
	if (parent)
		parent_ = parent;
}

XMLNode* XMLNode::getParent() const
{

	return parent_;
}

void XMLNode::setName(const char* name)
{
	name_ = name;
}

void XMLNode::setContent(const char* content)
{
	content_ = content;
}

const char* XMLNode::getName() const
{
	return name_;
}

const char* XMLNode::getContent() const
{
	return content_;
}
