#include "AnimationBatch.h"
#include "../Loader/AnimationLoader.h"
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>

AnimationBatch::AnimationBatch(AnimationLoader *anim)
{
    indexCount = anim->aIndices.size();
    vertexCount = anim->aVertices.size();
    boneCount = anim->boneCount;
    vertices.resize(vertexCount*3);
    normals.resize(vertexCount*3);
    texcoords.resize(vertexCount*4);
    colors.resize(vertexCount*3);
    boneids.resize(vertexCount*4);
    weights.resize(vertexCount*4);
    indices.resize(indexCount);

    for(uint i = 0;i < (uint)vertexCount;++i){
        // vertices
        vertices[i * 3] = anim->aVertices[i].x();
        vertices[i * 3 + 1] = anim->aVertices[i].y();
        vertices[i * 3 + 2] = anim->aVertices[i].z();

        // normals
        normals[i * 3] = anim->aNormals[i].x();
        normals[i * 3 + 1] = anim->aNormals[i].y();
        normals[i * 3 + 2] = anim->aNormals[i].z();

        // texcoords
        QVector2D texcoord = anim->aTexcoords[i];
        QVector4D texids = anim->aTextures[i];
        textureChannel = texids.y() >= 0 ? 4 : 3;
        texcoords[i * textureChannel] = texcoord.x();
        texcoords[i * textureChannel + 1] = texcoord.y();
        texcoords[i * textureChannel + 2] = texids.x();
        if (textureChannel == 4)
            texcoords[i * textureChannel + 3] = texids.y();

        // colors
        colors[i * 3] = (unsigned char)(anim->aAmbients[i].x() * 255);
        colors[i * 3 + 1] = (unsigned char)(anim->aDiffuses[i].x() * 255);
        colors[i * 3 + 2] = (unsigned char)(anim->aSpeculars[i].x() * 255);

        // bone id
        boneids[i * 4] = (unsigned char)(anim->aBoneids[i].x());
        boneids[i * 4 + 1] = (unsigned char)(anim->aBoneids[i].y());
        boneids[i * 4 + 2] = (unsigned char)(anim->aBoneids[i].z());
        boneids[i * 4 + 3] = (unsigned char)(anim->aBoneids[i].w());

        // bone weight
        weights[i * 4] = anim->aWeights[i].x();
        weights[i * 4 + 1] = anim->aWeights[i].y();
        weights[i * 4 + 2] = anim->aWeights[i].z();
        weights[i * 4 + 3] = anim->aWeights[i].w();
    }

    for (uint i = 0; i < (uint)indexCount; i++)
        indices[i] = (unsigned int)(anim->aIndices[i]);

    animation = anim;
}

AnimationBatch::~AnimationBatch() {}
