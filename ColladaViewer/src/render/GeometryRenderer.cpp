#include "components/Geometry.h"
#include "components/Appearance.h"
#include "core/Node.h"
#include "core/Mesh.h"
#include "core/Material.h"
#include "math/Vector4.h"
#include "render/GeometryRenderer.h"

namespace ColladaLoader
{

GeometryRenderer::GeometryRenderer(Geometry* geometryComponent) :
	geometry_(geometryComponent)
{
	initialise();
}

GeometryRenderer::~GeometryRenderer()
{

}

void GeometryRenderer::initialise(void)
{


	if (geometry_->hasMeshes())
	{
		//create a new OpenGL Display List
		geometryDisplayList_ = glGenLists(1);
		glNewList(geometryDisplayList_, GL_COMPILE);

		GLuint textureID;
		glGenTextures( 1, &textureID);
		glBindTexture( GL_TEXTURE_2D, textureID);

		//get mesh vector
		std::vector<Mesh*> meshes = geometry_->getMeshes();
		for (size_t i = 0; i < meshes.size(); i++)
		{
			//check for material binding
			if (!meshes[i]->getMaterialBinding().empty())
			{
				//get the appearance component
				Node* ownerNode = geometry_->getOwnerNode();
				if (ownerNode->hasComponents("Appearance"))
				{
					Node::Components appearanceComponents =
							ownerNode->getComponents("Appearance");
					Appearance
							* appearanceComponent =
									dynamic_cast<Appearance*> (appearanceComponents[0].get());

					//find the associated material
					Material* meshMaterial = appearanceComponent->getMaterial(
							meshes[i]->getMaterialBinding());

					if (meshMaterial != NULL)
					{
						std::string texturePath =  TEXTURE_DIR + "/" + meshMaterial->getDiffuseTextureName();
						glfwLoadTexture2D(texturePath.c_str(), GLFW_BUILD_MIPMAPS_BIT );
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
						glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
						glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );


						const GLfloat *emission =
								meshMaterial->getEmission().toArray();
						const GLfloat *ambient =
								meshMaterial->getAmbient().toArray();
						const GLfloat *diffuse =
								meshMaterial->getDiffuse().toArray();

						glMaterialfv(GL_FRONT, GL_EMISSION, emission);
						glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
						glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

						if (meshMaterial->getMaterialType()
								== Material::MT_PHONG
								|| meshMaterial->getMaterialType()
										== Material::MT_BLINN)
						{
							const GLfloat *specular =
									meshMaterial->getSpecular().toArray();

							GLfloat shininess[] =
							{ meshMaterial->getShininess() };

							glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
							glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
						}

					}
				}
			}

			std::vector<uint32> vertexIndices = meshes[i]->getVertexIndices();
			std::vector<uint32> normalIndices = meshes[i]->getNormalIndices();
			std::vector<uint32> texCoordIndices =
					meshes[i]->getTexCoordIndices();
			std::vector<uint32> colorIndices = meshes[i]->getColorIndices();

			std::vector<float> vertices = meshes[i]->getVertices();
			std::vector<float> normals = meshes[i]->getNormals();
			std::vector<float> texCoords = meshes[i]->getTexCoords();
			std::vector<float> colors = meshes[i]->getColors();

			//enable blending of material and vertex colors
			if (colors.size() > 0)
				glEnable(GL_COLOR_MATERIAL);



			glBindTexture(GL_TEXTURE_2D, textureID);

			glBegin(GL_TRIANGLES);
			for (size_t i = 0; i < vertexIndices.size(); i++)
			{
				//check for texture coordinates
				if (texCoords.size() > 0)
				{
					glTexCoord2f(texCoords[(texCoordIndices[i]) * 2],
							texCoords[(texCoordIndices[i]) * 2 + 1]);
				}
				//check for normals
				if (normals.size() > 0)
				{
					//no normal indices -> use vertex index to get normal value
					if (normalIndices.size() == 0)
					{
						glNormal3f(normals[(vertexIndices[i]) * 3],
								normals[(vertexIndices[i]) * 3 + 1],
								normals[(vertexIndices[i]) * 3 + 2]);
					}
					else
					{
						glNormal3f(normals[(normalIndices[i]) * 3],
								normals[(normalIndices[i]) * 3 + 1],
								normals[(normalIndices[i]) * 3 + 2]);
					}
				}

				//check for colors
				if (colors.size() > 0)
				{

					//no color indices -> use vertex index to get color value
					if (colorIndices.size() == 0)
					{
						glColor4f(colors[(vertexIndices[i]) * 4],
								colors[(vertexIndices[i]) * 4 + 1],
								colors[(vertexIndices[i]) * 4 + 2],
								colors[(vertexIndices[i]) * 4 + 3]);
					}
					else
					{
						glColor4f(colors[(colorIndices[i]) * 4],
								colors[(colorIndices[i]) * 4 + 1],
								colors[(colorIndices[i]) * 4 + 2],
								colors[(colorIndices[i]) * 4 + 3]);
					}

					//disable blending of material and vertex colors
					if (colors.size() > 0)
						glDisable(GL_COLOR_MATERIAL);
				}

				//check for vertices
				if (vertices.size() > 0)
				{
					glVertex3f(vertices[(vertexIndices[i]) * 3],
							vertices[(vertexIndices[i]) * 3 + 1],
							vertices[(vertexIndices[i]) * 3 + 2]);
				}

			}
			glEnd();
		}

		glEndList();
	}
}

void GeometryRenderer::render(double timeElapsed)
{
	glCallList(geometryDisplayList_);
}

}
