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

#include "Graphics/Buffer/IVertexBuffer.h"
#include "Graphics/Device/GLDevice.h"
#include "Math/Vertex.h"

namespace Ivy
{
	namespace Graphics
	{
		class GLVertexBuffer : public IVertexBuffer
		{
			GLuint vertexArray;
			GLuint vertexBuffer;

			std::vector<Math::Vertex> vertices;
            short items;

		public:

			GLVertexBuffer() { }

			void Bind() override;
			bool Create() override;

			std::vector<Math::Vertex> GetVertices() override;
			void SetVertices(std::vector<Math::Vertex> vertices) override;
		
			void Unbind() override;
			void Draw() override;
		};
	}
}