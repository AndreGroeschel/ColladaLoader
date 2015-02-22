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

#include "core/NodeManager.h"
#include "core/Node.h"
#include "components/Geometry.h"
#include "render/GeometryRenderer.h"
#include "render/SceneRenderer.h"

namespace ColladaLoader
{

SceneRenderer::SceneRenderer() :
	rootNode_(NULL)
{
	//get a pointer to the scene's root node
	rootNode_ = NodeManager::getSingletonPtr()->getNode("root");
	if (rootNode_ == NULL)
	{
		ERROR("No root node found");
	}

	//create all component renderer
	preTraverseNodes(rootNode_);
}

SceneRenderer::~SceneRenderer()
{
	for(size_t i=0;i<componentRenderer_.size();i++)
		{
			if(componentRenderer_[i]!=NULL)
			{
				delete componentRenderer_[i];
			}
		}
		componentRenderer_.clear();
}

void SceneRenderer::update(double timeElapsed)
{
	for(size_t i =0;i<componentRenderer_.size();i++)
	{
		componentRenderer_[i]->render(timeElapsed);
	}
}

void SceneRenderer::preTraverseNodes(Node* node)
{
	Node* childNode = node->getChild();

	for (size_t i = 0; i < node->getChildrenCount(); i++)
	{
		//LOG(childNode->getName());
		if(childNode->hasComponents("Geometry"))
		{
			Node::Components geoComponents = childNode->getComponents("Geometry");

			for(size_t j=0;j<geoComponents.size();j++)
			{
				Geometry* geoComponent = dynamic_cast<Geometry*>(geoComponents[j].get());
				componentRenderer_.push_back(new GeometryRenderer(geoComponent));
			}
		}
		//Recursively traverse children
		if (childNode->hasChildren())
		{
			preTraverseNodes(childNode);
		}
		else
		{
			childNode = childNode->getNext();
		}
	}
}

}
