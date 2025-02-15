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

#include "GLVertexBuffer.h"

void Ivy::Graphics::GLVertexBuffer::Bind()
{
	// Positions.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Math::Vertex),
		reinterpret_cast<GLvoid*>offsetof(struct Math::Vertex, position));

	// Texture Coordinates.
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Math::Vertex),
		reinterpret_cast<GLvoid*>offsetof(struct Math::Vertex, texture));

	// Normals.
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Math::Vertex),
		reinterpret_cast<GLvoid*>offsetof(struct Math::Vertex, normal));
}

bool Ivy::Graphics::GLVertexBuffer::Create()
{
	// Generate our vertices array and Bind it to the first element.
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// Generate our vertices buffer and bind it.
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Math::Vertex), vertices.data(), GL_STATIC_DRAW);

	return true;
}


std::vector<Ivy::Math::Vertex> Ivy::Graphics::GLVertexBuffer::GetVertices()
{
	return vertices;
}

void Ivy::Graphics::GLVertexBuffer::SetVertices(std::vector<Math::Vertex> vertices)
{
	this->vertices = vertices;
}

void Ivy::Graphics::GLVertexBuffer::Unbind()
{
	// Unbind and delete the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &vertexArray);
}

void Ivy::Graphics::GLVertexBuffer::Draw()
{

}
