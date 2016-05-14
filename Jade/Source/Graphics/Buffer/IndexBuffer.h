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

#include <Graphics/Buffer/IIndexBuffer.h>
#include <Graphics/Buffer/DXIndexBuffer.h>
#include <Graphics/Buffer/GLIndexBuffer.h>
#include <Graphics/Device/Device.h>

namespace Jade
{
	namespace Graphics
	{
		class IndexBuffer
		{
			std::shared_ptr<IIndexBuffer> indexBuffer;

		public:

			IndexBuffer() { } 

			IndexBuffer(Device device)
			{
				switch (device.GetGraphicsAPI())
				{
				case GraphicsAPI::DirectX:
					indexBuffer = std::make_shared<DXIndexBuffer>(std::dynamic_pointer_cast<DXDevice>(device.GetIDevice()));
					break;
				case GraphicsAPI::OpenGL:
					// OpenGL uses a state machine so we dont need to pass a device.
					indexBuffer = std::make_shared<GLIndexBuffer>();
					break;
				case GraphicsAPI::Vulkan:
					indexBuffer = nullptr;
					break;
				}
			}

			void Bind();
			bool Create();

			std::vector<unsigned short> GetIndices();
			void SetIndices(std::vector<unsigned short> indices);
		
			void Unbind();
			void Update();
		};
	}
}