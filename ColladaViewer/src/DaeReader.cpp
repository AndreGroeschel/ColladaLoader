/*
 -----------------------------------------------------------------------------
 This file is part of ColladaLoader.

 Copyright (c) 2008, 2009 André Gröschel, Martin Maczkowski & Fiete Groth

 PooRacer is free software; you can redistribute it and/or modify it under
 the terms of the GNU Lesser General Public License as published by the Free Software
 Foundation; either version 2 of the License, or (at your option) any later
 version.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License along with
 this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 Place - Suite 330, Boston, MA 02111-1307, USA, or go to
 http://www.gnu.org/copyleft/lesser.txt.
 -----------------------------------------------------------------------------
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
