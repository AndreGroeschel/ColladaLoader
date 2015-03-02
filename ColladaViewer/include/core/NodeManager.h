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

#ifndef NODEMANAGER_H_
#define NODEMANAGER_H_

#include "prerequisites.h"
#include "utils/Singleton.h"

namespace ColladaLoader
{
/**
* The @c NodeManager provides a central access point for adding, retrieving and removing nodes
*/
class NodeManager: public Singleton<NodeManager>
{
public:
	NodeManager();
	virtual ~NodeManager();

	Node* createNode(const std::string& id);
	Node* getNode(const std::string& name) const;
	void removeNode(const std::string& name);
	void listNodes(void);

	//returns node count
	const uint32 getCount(void);

	static NodeManager& getSingleton(void);
	static NodeManager* getSingletonPtr(void);

private:
	uint32 nodeCount_;
	std::map<std::string, Node*> nodes_;
	std::map<std::string, Node*>::const_iterator nodesIt_;
};
}
#endif /* NODEMANAGER_H_ */
