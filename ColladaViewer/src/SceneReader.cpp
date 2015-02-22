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

#include <dae.h>
#include <dom/domVisual_scene.h>
#include <dom/domGeometry.h>
#include "core/NodeManager.h"
#include "core/Node.h"
#include "core/ParamList.h"
#include "SceneReader.h"

namespace ColladaLoader
{

template<> SceneReader* Singleton<SceneReader>::ms_Singleton = 0;
SceneReader* SceneReader::getSingletonPtr(void)
{
	return ms_Singleton;
}
SceneReader& SceneReader::getSingleton(void)
{
	assert(ms_Singleton);
	return (*ms_Singleton);
}

SceneReader::SceneReader() :
	scene_(NULL), rootNode_(NULL)
{
	if (NodeManager::getSingletonPtr() != NULL)
		rootNode_ = NodeManager::getSingletonPtr()->createNode("root");
}

SceneReader::~SceneReader()
{
}

void SceneReader::readVisualScene(void)
{
	if (scene_ != NULL)
		readVisualScene(scene_);
	else
		ERROR("Error in SceneReader while trying to read scene: no scene set");
}

void SceneReader::readVisualScene(domVisual_sceneRef scene)
{
	scene_ = scene;

	std::stringstream str;
	str << "Visual scene name: " << scene->getName();
	LOG(str.str());

	if (scene->getName())
		rootNode_->setName(scene->getName());
	if (scene->getID())
		rootNode_->setID(scene->getID());

	//go through scene
	for (uint32 i = 0; i < scene_->getNode_array().getCount(); i++)
	{
		readVisualNode(scene_->getNode_array()[i], rootNode_);
	}
}

Node* SceneReader::readVisualNode(domNodeRef refNode, Node* parentNode)
{
	Node* findNode = NodeManager::getSingletonPtr()->getNode(refNode->getID());
	if (findNode != NULL)
		return findNode;

	//create new Node
	Node* node = NodeManager::getSingletonPtr()->createNode(refNode->getID());

	if (refNode->getName())
		node->setName(refNode->getName());
	if (refNode->getSid())
		node->setScopedID(refNode->getSid());

	node->setParent(parentNode);
	parentNode->addChild(node);

	//TODO: transformations
	//TODO: process geometries
	domInstance_geometry_Array geometryInstances =
			refNode->getInstance_geometry_array();
	for (size_t i = 0; i < geometryInstances.getCount(); i++)
	{
		processInstanceGeometry(geometryInstances[i], node);
	}

	//Recursively read children
	for (uint32 i = 0; i < refNode->getNode_array().getCount(); i++)
	{
		readVisualNode(refNode->getNode_array()[i], node);
	}
	return node;
}

void SceneReader::processInstanceGeometry(domInstance_geometry* instanceGeo,
		Node* parentNode)
{
	daeElement* element = instanceGeo->getUrl().getElement();
	domGeometry* geometry = daeSafeCast<domGeometry> (element);

	if (geometry != NULL)
	{
		ComponentPtr geometryComponent;

		//check if there is already a component with this geometry data
		if (geometryComponents_.find(geometry) != geometryComponents_.end())
		{
			geometryComponent = geometryComponents_.find(geometry)->second;
			parentNode->addComponent(geometryComponent);
		}
		else
		{
			//set up parameters
			ParamListPtr geometryParams(new ParamList);
			geometryParams->addParameter("domGeometry", geometry);

			//add geo component to current node
			geometryComponent = parentNode->addComponent("Geometry",geometryParams);

			//add component to geometry map. This is used to check if geo components share the same data
			geometryComponents_.insert(std::make_pair(geometry,
					geometryComponent));
		}

		//process material assigned to this geometry instance
		if (instanceGeo->getBind_material() != NULL)
		{
			//set up parameters
			domBind_material* bindMaterial = instanceGeo->getBind_material().cast();

			ParamListPtr appearanceParams(new ParamList);
			appearanceParams->addParameter("domBindMaterial", bindMaterial);


			parentNode->addComponent("Appearance",appearanceParams);
		}
	}
	else
	{
		ERROR("Could not find geometry");
	}
}

void SceneReader::setVisualScene(domVisual_sceneRef scene)
{
	scene_ = scene;
}
}
