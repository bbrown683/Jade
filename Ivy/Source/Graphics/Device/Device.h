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

#include "Core/Include.h"
#include "Graphics/Device/GraphicsAPI.h"
#include "Graphics/Device/IDevice.h"
#include "Graphics/Device/DXDevice.h"
#include "Graphics/Device/GLDevice.h"
#include "Graphics/Device/Specification.h"
#include "System/Window/Window.h"

namespace Ivy
{
    namespace Graphics
    {
        class Device
        {
            System::Window window;
            GraphicsAPI api;
            Specification specification;
            DrawType type;

            std::shared_ptr<IDevice> device;
            std::shared_ptr<IDevice> Initialize();

        public:						

            Device() : device(nullptr) {} 

            // Default device constructor.
            Device(System::Window window, GraphicsAPI api)
            {
                this->window = window;
                this->api = api;

                // Fill some default values.
                specification.backBufferHeight = window.GetHeight();
                specification.backBufferWidth = window.GetWidth();
                specification.colorBits = 32;
                specification.samples = 1;
                specification.vsync = true;
            }

            Device(System::Window window, Specification specification)
            {
                this->window = window;
                this->specification = specification;
            }

            Device(System::Window window, GraphicsAPI api, Specification specification)
            {
                this->window = window;
                this->api = api;
                this->specification = specification;
            }

            // Adjusts the window viewport.
            void AdjustViewport() const
            {
                device->AdjustViewport();
            }

            // Clears the buffer to the specified color.
            void Clear(Math::Color color) const
            {
                device->Clear(color);
            }

            // Creates the device and returns a boolean if it was successful.
            bool Create()
            {
                device = Initialize();
                return device != nullptr;
            }

            // Presents the back buffer to the front for display.
            void Present() const
            {
                device->Present();
            }

            bool Multisampling() const
            {
                return specification.samples > 1;
            }

            // Returns the interface that contains the device data.
            std::shared_ptr<IDevice> GetIDevice() const
            {
                return device;
            }

            // Returns the window that the device is attached to.
            System::Window GetWindow() const
            {
                return window;
            }

            GraphicsAPI GetGraphicsAPI() const
            {
                return api;
            }

            DrawType GetDrawType() const
            {
                return device->GetDrawType();
            }

            void SetDrawType(DrawType type)
            {
                device->SetDrawType(type);
            }

            void TakeScreenshot()
            {
                device->TakeScreenshot();
            }
        };
    }
}

