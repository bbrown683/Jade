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

#include <vector>
#include <directxmath.h>

#include "Core/Utility.h"
#include "Graphics/Device/DXDevice.h"
#include "Graphics/Mesh/IMesh.h"
#include "Math/Vertex.h"
#include "Math/Matrix.h"

namespace Jade
{
	namespace Graphics
	{
		class DXMesh : public IMesh
		{
		private:

			std::vector<Math::Vertex> vertices;
			std::vector<unsigned int> indices;
			std::shared_ptr<DXDevice> device;

			bool bufferSuccess;

			typedef struct ConstantBuffer 
			{
				DirectX::XMMATRIX world;
				DirectX::XMMATRIX view;
				DirectX::XMMATRIX projection;
			} Space;

			Space space;
			DirectX::XMMATRIX world;
			DirectX::XMMATRIX view;
			DirectX::XMMATRIX projection;

			ID3D11ShaderResourceView*	m_pTextureRV = nullptr;

			void Bind() override;
			void Unbind() override;

		public:

			DXMesh(std::vector<Math::Vertex> vertices, std::vector<unsigned int> indices, std::shared_ptr<DXDevice> device)
			{
				this->vertices = vertices;
				this->indices = indices;
				this->device = device;

				Bind();
			}

			~DXMesh()
			{
				Unbind();
			}

			void Draw() override;
		};
	}
}
