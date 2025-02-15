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

#include "Model.h"

void Ivy::Graphics::Model::Draw()
{
    if(blending)
        blender.SetBlendState(0x000000FF);

    // Loop through and draw each mesh.
    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw();

    if (blending)
        blender.DisableBlendState();
}

void Ivy::Graphics::Model::Blending(bool blending)
{
    this->blending = blending;
}

void Ivy::Graphics::Model::Load(std::string filename)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(filename, aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_GenUVCoords |
        aiProcess_GenNormals |
        aiProcess_FlipUVs);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "Assimp: Error - " << importer.GetErrorString() << std::endl;

        return;
    }

    for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        aiMesh* aMesh = scene->mMeshes[i];

        // Components of a mesh.
        std::vector<Math::Vertex> vertices;
        std::vector<unsigned short> indices;
        std::vector<Texture> textures;

        // Grab the vertex position and colors for the mesh.
        for (unsigned int j = 0; j < aMesh->mNumVertices; j++)
        {
            // An individual vertex.
            Math::Vertex vertex;

            if (aMesh->HasPositions())
            {
                aiVector3D aPosition = aMesh->mVertices[j];
                vertex.position = Math::Vector4(aPosition.x, aPosition.y, aPosition.z);
            }
            else
                vertex.position = Math::Vector4();

            if (aMesh->HasTextureCoords(0))
            {
                aiVector3D aTexture = aMesh->mTextureCoords[0][j];
                vertex.texture = Math::Vector2(aTexture.x, aTexture.y);
            }
            else
                vertex.texture = Math::Vector2();

            if (aMesh->HasNormals())
            {
                aiVector3D aNormal = aMesh->mNormals[j];
                vertex.normal = Math::Vector3(aNormal.x, aNormal.y, aNormal.z);
            }
            else
                vertex.normal = Math::Vector3();

            if (aMesh->HasVertexColors(0))
            {
                aiColor4D aColor = aMesh->mColors[0][j];
                vertex.color = Math::Color(aColor.r, aColor.g, aColor.b, aColor.a);
            }
            else
                vertex.color = Math::Color::White;

            if (aMesh->mMaterialIndex >= 0)
            {
                // Check to see if a diffuse color exists for this mesh.
                aiMaterial* aMaterial = scene->mMaterials[aMesh->mMaterialIndex];

                aiColor4D diffuse;
                aMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
                vertex.color = Math::Color(diffuse.r, diffuse.g, diffuse.b, diffuse.a);
            }

            vertices.push_back(vertex);
        }

        if (aMesh->HasFaces())
        {
            // Grab the indices for the mesh.
            for (unsigned int j = 0; j < aMesh->mNumFaces; j++)
            {
                aiFace face = aMesh->mFaces[j];

                for (unsigned int k = 0; k < face.mNumIndices; k++)
                    indices.push_back(face.mIndices[k]);
            }
        }

        // Check to see if mesh has a texture.
        if (aMesh->mMaterialIndex >= 0)
        {
            aiMaterial* aMaterial = scene->mMaterials[aMesh->mMaterialIndex];
            
            // Iterate though each texture type if they exist.
            for (unsigned int j = 0; j < aMaterial->GetTextureCount(aiTextureType_DIFFUSE); j++)
            {
                // Get the texture for the material.
                aiString string;
                aMaterial->GetTexture(aiTextureType_DIFFUSE, j, &string);
                
                bool test = false;
                for(unsigned int k = 0; k < textures.size(); k++)
                {
                    if (textures[k].GetFilename() == string.C_Str())
                    {
                        test = true;
                        std::cout << "Duplicate texture found for " << string.C_Str() << std::endl;
                    }
                }
                
                if (!test)
                {
                    std::cout << "Diffuse texture " << string.C_Str() << " was found..." << std::endl;
                    textures.push_back(Texture(device, string.C_Str(), TextureType::Diffuse));
                }
            }
        }

        meshes.push_back(Mesh(device, shader, vertices, indices, textures, PrimitiveType::TriangleList));
    }
}

std::vector<Ivy::Graphics::Mesh> Ivy::Graphics::Model::GetMeshes() const
{
    return meshes;
}

Ivy::Math::Vector3 Ivy::Graphics::Model::GetPosition() const
{
    return position;
}

Ivy::Math::Vector3 Ivy::Graphics::Model::GetRotation() const
{
    return rotation;
}

Ivy::Math::Vector3 Ivy::Graphics::Model::GetScale() const
{
    return scale;
}

void Ivy::Graphics::Model::SetPosition(Math::Vector3 position)
{
    this->position = this->position + position;
    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].SetPosition(this->position);
}

void Ivy::Graphics::Model::SetRotation(Math::Vector3 rotation)
{
    this->rotation = this->rotation + rotation;
    
    // Ensure rotation values does not exceed + or - 2 Pi.
    // If this is not moderated, an overflow could eventually occur.
    if (this->rotation.GetX() > Math::Math::TwoPi || this->rotation.GetX() < -Math::Math::TwoPi)
        this->rotation.SetX(Math::Helper::WrapAngle(this->rotation.GetX()));
    if (this->rotation.GetY() > Math::Math::TwoPi || this->rotation.GetY() < -Math::Math::TwoPi)
        this->rotation.SetY(Math::Helper::WrapAngle(this->rotation.GetY()));
    if (this->rotation.GetZ() > Math::Math::TwoPi || this->rotation.GetZ() < -Math::Math::TwoPi)
        this->rotation.SetZ(Math::Helper::WrapAngle(this->rotation.GetZ()));
    
    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].SetRotation(this->rotation);
}

void Ivy::Graphics::Model::SetScale(Math::Vector3 scale)
{
    this->scale = this->scale + scale;
    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].SetScale(this->scale);
}
