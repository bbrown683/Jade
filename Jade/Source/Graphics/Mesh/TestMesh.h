#pragma once

/*
The MIT License (MIT)

Copyright (c) 2015 Ben Brown

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Graphics/Buffer/PrimitiveType.h"
#include "Graphics/Device/Device.h"
#include "Graphics/Mesh/IMesh.h"
#include "Graphics/Mesh/DXMesh.h"
#include "Graphics/Mesh/GLMesh.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Texture/Texture.h"

// Note: This is a prototype of what I want the mesh class to resemble.
// No need to have interfaces to implement their own mesh, but rather
// implement buffer objects that are interfaces to an implementation needed
// for a mesh.

namespace Jade
{
	namespace Graphics
	{
		class TestMesh
		{
			Device device;
			Shader shader;
			PrimitiveType primitiveType;

			std::vector<Math::Vertex> vertices;
			std::vector<unsigned short> indices;
			std::vector<Texture> textures;

			VertexBuffer vBuffer;
			IndexBuffer iBuffer;
			ConstantBuffer cBuffer;

			Math::Matrix rotation;
			Math::Matrix scale;
			Math::Matrix translation;

		public:

			TestMesh(Device device, Shader shader, std::vector<Math::Vertex> vertices, PrimitiveType primitiveType)
			{
				
			}

			TestMesh(Device device, Shader shader, std::vector<Math::Vertex> vertices, std::vector<unsigned short> indices, PrimitiveType primitiveType)
			{

			}

			TestMesh(Device device, Shader shader, std::vector<Math::Vertex> vertices, std::vector<unsigned short> indices, std::vector<Texture> textures, PrimitiveType primitiveType)
			{
				this->device = device;
				this->shader = shader;
				this->vertices = vertices;
				this->indices = indices;
				this->textures = textures;
				this->primitiveType = primitiveType;

				vBuffer = VertexBuffer(device, primitiveType);
				iBuffer = IndexBuffer(device);
				cBuffer = ConstantBuffer(device);

				// These wont change.
				vBuffer.SetVertices(vertices);
				iBuffer.SetIndices(indices);

				// Create the buffers.
				// NOTE: vBuffer and iBuffer require data to be passed into their 
				// respective set method before creation.
				vBuffer.Create();
				iBuffer.Create();

				// Meshes should only have a world matrix.
				cBuffer.Create(true, false, false);

				// Create the textures.
				for (unsigned int i = 0; i < textures.size(); i++)
				{
					if (textures[i].CreateTextureFromFile())
						std::cout << "Texture " << textures[i].GetFilename() << " was bound successfully..." << std::endl;
					else
						std::cout << "Texture " << textures[i].GetFilename() << " failed to bind to mesh..." << std::endl;
				}

				// Set to identity matrix by default.
				rotation = Math::Matrix::Identity;
				translation = Math::Matrix::Identity;
				scale = Math::Matrix::Identity;
			}

			void Draw();
			
			void SetPosition(Math::Vector3 position);
			void SetScale(Math::Vector3 scale);
			void SetRotation(Math::Vector3 rotation);

			std::vector<Math::Vertex> GetVertices()	const
			{
				return vertices;
			}

			std::vector<unsigned short> GetIndices() const
			{
				return indices;
			}

			std::vector<Texture> GetTextures() const
			{
				return textures;
			}
		};
	}
}