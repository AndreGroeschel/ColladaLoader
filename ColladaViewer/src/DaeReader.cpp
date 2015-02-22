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
#include "DaeDocument.h"
#include "SceneReader.h"
#include "core/NodeManager.h"
#include "core/ComponentFactory.h"
#include "DaeReader.h"


namespace ColladaLoader
{

DaeReader::DaeReader() :
	dae_(new DAE), daeDocument_(new DaeDocument),
			nodeManager_(new NodeManager), componentFactory_(new ComponentFactory), sceneReader_(new SceneReader), filePath_("")
{

}

DaeReader::~DaeReader()
{
	delete sceneReader_;
	delete componentFactory_;
	delete nodeManager_;
	delete daeDocument_;
	dae_->close(filePath_);
	delete dae_;
}

void DaeReader::load(const std::string& path)
{
	filePath_ = path;

	LOG("Loading " + path);

	bool isLoaded = daeDocument_->load(dae_->open(filePath_));
	if (!isLoaded)
		ERROR("An error occurred while reading the document.")

	//print meta information of asset
	daeDocument_->printAssetInformation();

	//start visual scene reader
	sceneReader_->readVisualScene(daeDocument_->getVisualScene());

}

}
