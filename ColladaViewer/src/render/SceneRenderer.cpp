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
