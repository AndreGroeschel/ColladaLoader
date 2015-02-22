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

#ifndef PREREQUISITES_H_
#define PREREQUISITES_H_

#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <iostream>

#define LOG(message) std::cout << message << std::endl;
#define ERROR(message) std::cerr << message << std::endl;

namespace ColladaLoader
{
//################ Constants ################
static const std::string MODEL_DIR = "media/models";
static const std::string TEXTURE_DIR = "media/textures";

//################ Forward declarations ################
class Scene;
class DaeReader;
class DaeDocument;
class SceneReader;
class Node;
class NodeManager;
class Component;
class ComponentFactory;
class ParamList;
class Geometry;
class Appearance;
class Mesh;
class Material;
class OpenGLRenderer;
class SceneRenderer;
class IComponentRenderer;
class GeometryRenderer;

class Vector4;

//################ typedefs ################
// Integer formats of fixed bit width
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef boost::shared_ptr<Component> ComponentPtr;
typedef boost::shared_ptr<ParamList> ParamListPtr;

}
#endif /* PREREQUISITES_H_ */
