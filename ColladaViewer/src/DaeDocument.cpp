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
#include <dom/domCOLLADA.h>
#include <dom/domAsset.h>
#include "DaeDocument.h"

namespace ColladaLoader
{

template<> DaeDocument* Singleton<DaeDocument>::ms_Singleton = 0;
DaeDocument* DaeDocument::getSingletonPtr(void)
{
	return ms_Singleton;
}
DaeDocument& DaeDocument::getSingleton(void)
{
	assert(ms_Singleton);
	return (*ms_Singleton);
}

DaeDocument::DaeDocument() :
	colladaDocument_(NULL), assetUpAxis_(UP_AXIS_Y)
{

}

DaeDocument::~DaeDocument()
{
}

bool DaeDocument::load(domCOLLADA* colladaDocument)
{
	colladaDocument_ = colladaDocument;

	//find scene
	if (colladaDocument_->getScene() == NULL)
	{
		ERROR("Collada document contains no scene");
		return false;
	}

	if (colladaDocument_->getScene()->getInstance_visual_scene() == NULL)
	{
		ERROR("Collada document contains no visual scene");
		return false;
	}

	//retrieve asset information
	if (colladaDocument_->getAsset())
	{
		domAsset* asset = colladaDocument_->getAsset();

		//up axis
		if (asset->getUp_axis())
		{
			domUpAxisType upAxis = asset->getUp_axis()->getValue();

			switch (upAxis)
			{
			case UPAXISTYPE_X_UP:
				assetUpAxis_ = UP_AXIS_X;
				break;
			case UPAXISTYPE_Z_UP:
				assetUpAxis_ = UP_AXIS_Z;
				break;
			case UPAXISTYPE_Y_UP:
			case UPAXISTYPE_COUNT:
				assetUpAxis_ = UP_AXIS_Y;
				break;
			}
		}
	}

	return true;
}

float DaeDocument::getAssetUnitMeter() const
{
	if (colladaDocument_->getAsset()->getUnit())
	{
		if (colladaDocument_->getAsset()->getUnit()->getMeter())
			return colladaDocument_->getAsset()->getUnit()->getMeter();
	}
	ERROR("Asset has no unit scale");
	return 0.0;
}

DaeDocument::UpAxis DaeDocument::getAssetUpAxis() const
{
	return assetUpAxis_;
}

domVisual_sceneRef DaeDocument::getVisualScene(void)
{
	domInstanceWithExtraRef visualSceneRef = colladaDocument_->getScene()->getInstance_visual_scene();

	if(visualSceneRef != NULL)
	{
		domVisual_sceneRef visualScene = daeSafeCast<domVisual_scene>(visualSceneRef->getUrl().getElement());
		return visualScene;
	}
	return NULL;
}

void DaeDocument::printAssetInformation(void)
{
	//retrieve asset information
	if (colladaDocument_->getAsset())
	{
		domAsset* asset = colladaDocument_->getAsset();

		//contributors
		const domAsset::domContributor_Array& contributors = asset->getContributor_array();

		for (size_t currContributor = 0; currContributor < contributors.getCount(); currContributor++)
		{
			//Author
			if(contributors[currContributor]->getAuthor())
			{
				std::stringstream str;
				str << "Author: " << contributors[currContributor]->getAuthor()->getValue();
				LOG(str.str());
			}

			//Authoring tool
			if(contributors[currContributor]->getAuthoring_tool())
			{
				std::stringstream str;
				str << "Authoring tool: " << contributors[currContributor]->getAuthoring_tool()->getValue();
				LOG(str.str());
			}
		}
	}
}

}
