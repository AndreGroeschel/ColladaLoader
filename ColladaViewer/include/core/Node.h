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

#ifndef NODE_H_
#define NODE_H_

#include "prerequisites.h"

namespace ColladaLoader
{
/**
* The @c Node class describes a single scene element. Uses Decorator pattern for dynamic behavior injection
*/
class Node
{
public:
	typedef std::vector<ComponentPtr> Components;
	typedef std::vector<ComponentPtr>::iterator ComponentsIt;
public:
	Node();
	virtual ~Node();

	void addChild(Node* childNode);
	void setParent(Node* parentNode);
	Node* setNextNode(Node* nextNode);

	Node* getNext(void) const;
	Node* getParent(void) const;
	Node* getChild(void) const;

	const uint32 getChildrenCount(void);
	bool hasChildren(void);

	void setName(const std::string& name);
	const std::string& getName(void) const;
	void setID(const std::string& id);
	const std::string& getID(void) const;
	void setScopedID(const std::string& sid);
	const std::string& getScopedID(void) const;

	ComponentPtr addComponent(const std::string& type, ParamListPtr parameters);
	ComponentPtr addComponent(ComponentPtr component);
	Components getComponents(const std::string& componentType);
	const bool hasComponents(const std::string& componentType);
	const uint32 getComponentCount(void);
	void listComponents(void);

private:
	Node* childNode_;
	Node* parentNode_;
	Node* nextNode_;
	uint32 childrenCount_;
	std::string name_;
	std::string ID_;
	std::string scopedID_;

	//stores components sorted by type
	std::map<std::string, std::vector<ComponentPtr> > components_;
	std::map<std::string, std::vector<ComponentPtr> >::const_iterator componentIt_;
};
}

#endif /* NODE_H_ */
