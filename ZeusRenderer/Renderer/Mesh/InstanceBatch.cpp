#include "InstanceBatch.h"
#include "../Material/MaterialManager.h"
#include <QDebug>

std::map<Mesh*, int> InstanceBatch::instanceTable;

InstanceBatch::InstanceBatch()
{
    vertexCount = 0;
    indexCount = 0;
    instanceCount = 0;
    instanceMesh = nullptr;
    singleSide = false;
}

InstanceBatch::~InstanceBatch() {}

void InstanceBatch::initInstanceBuffers(int count,int vertices,int indices)
{
    instanceCount = count;
    vertexCount = vertices;
    indexCount = indices;
    vertexBuffer.resize(vertexCount*3);
    normalBuffer.resize(vertexCount*3);
    texcoordBuffer.resize(vertexCount*4);
    colorBuffer.resize(vertexCount*3);
    indexBuffer.resize(indexCount);
    modelMatrices.resize(instanceCount*16);
}

void InstanceBatch::pushMeshToBuffers(Mesh *mesh, int mid, bool fullStatic)
{
    this->instanceMesh = mesh;
    // get the data from mesh
    for(int i = 0;i < vertexCount;++i){
        QVector4D vertex = instanceMesh->vertices[i];
        QVector3D normal = instanceMesh->normals[i];
        QVector2D texcoord = instanceMesh->texcoords[i];

        // material
        Material *mat = nullptr;
        if(instanceMesh->materialids.empty() && mid >= 0)
            mat = MaterialManager::materials->find(mid);
        else if(!instanceMesh->materialids.empty())
            mat = MaterialManager::materials->find(instanceMesh->materialids[i]);
        if(!mat)mat = MaterialManager::materials->find(0);
        QVector4D textures = mat->texture;
        QVector3D ambient = mat->ambient;
        QVector3D diffuse = mat->diffuse;
        QVector3D specular = mat->specular;

        vertexBuffer[i*3] = vertex.x();
        vertexBuffer[i*3+1] = vertex.y();
        vertexBuffer[i*3+2] = vertex.z();

        normalBuffer[i*3] = normal.x();
        normalBuffer[i*3+1] = normal.y();
        normalBuffer[i*3+2] = normal.z();

        textureChannel = textures.y() >= 0 ? 4:3;
        texcoordBuffer[i*textureChannel] = texcoord.x();
        texcoordBuffer[i*textureChannel+1] = texcoord.y();
        texcoordBuffer[i*textureChannel+2] = textures.x();
        if(textureChannel == 4)
            texcoordBuffer[i*textureChannel+3] = textures.y();

        colorBuffer[i*3] = (unsigned char)(ambient.x()*255);
        colorBuffer[i*3+1] = (unsigned char)(diffuse.x()*255);
        colorBuffer[i*3+2] = (unsigned char)(specular.x()*255);
    }

    if(!instanceMesh->indices.empty()){
        for(int i = 0;i < indexCount;++i){
            indexBuffer[i] = instanceMesh->indices[i];
        }
    }
}

void InstanceBatch::setMatricesBuffer(int i, const QMatrix4x4 &transformMatrix)
{
    const float *data = transformMatrix.constData();
    for(int x = 0;x < 16;++x){
        modelMatrices[i*16+x] = data[x];
    }
}

void InstanceBatch::releaseBuffer()
{
    std::vector<float> v;
    std::vector<float> n;
    std::vector<float> t;
    std::vector<unsigned char> c;
    std::vector<unsigned char> o;
    std::vector<unsigned int> i;
    std::vector<float> m;
    vertexBuffer.swap(v);
    normalBuffer.swap(n);
    texcoordBuffer.swap(t);
    colorBuffer.swap(c);
    indexBuffer.swap(i);
    modelMatrices.swap(m);
}
