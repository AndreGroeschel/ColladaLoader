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

#include "core/Node.h"
#include "core/NodeManager.h"

namespace ColladaLoader
{

template<> NodeManager* Singleton<NodeManager>::ms_Singleton = 0;
NodeManager* NodeManager::getSingletonPtr(void)
{
	return ms_Singleton;
}
NodeManager& NodeManager::getSingleton(void)
{
	assert(ms_Singleton);
	return (*ms_Singleton);
}

NodeManager::NodeManager() :
	nodeCount_(0)
{
}

NodeManager::~NodeManager()
{
	//delete all nodes
	for (nodesIt_ = nodes_.begin(); nodesIt_ != nodes_.end(); nodesIt_++)
	{
		delete nodesIt_->second;
	}
	nodes_.clear();
}

Node* NodeManager::createNode(const std::string& id)
{
	nodes_[id] = new Node();
	nodes_[id]->setID(id);
	return nodes_[id];
}

Node* NodeManager::getNode(const std::string& name) const
{
	if (nodes_.find(name) != nodes_.end())
	{
		return nodes_.find(name)->second;
	}
	return NULL;
}

void NodeManager::removeNode(const std::string& name)
{
	if (nodes_.find(name) != nodes_.end())
	{
		Node* node = nodes_.find(name)->second;
		nodes_.erase(name);
		delete node;
	}
	else
	{
		ERROR("Error while trying to remove Node: Node " + name + " does not exist");
	}
}

const uint32 NodeManager::getCount(void)
{
	return (uint32) nodes_.size();
}

void NodeManager::listNodes(void)
{
	for (nodesIt_ = nodes_.begin(); nodesIt_ != nodes_.end(); nodesIt_++)
	{
		Node* currNode = nodesIt_->second;

		std::stringstream str;
		str << "Entity ID: " << currNode->getID() << " Name: "
		<< currNode->getName();
		LOG(str.str());
	}
}
}
