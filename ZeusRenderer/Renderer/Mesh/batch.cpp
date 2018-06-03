#include "Batch.h"
#include <QDebug>

Batch::Batch()
{
    // Initial value
    vertexCount = 0;
    indexCount = 0;
    storeVertexCount = 0;
    storeIndexCount = 0;
    fullStatic = false;
    objectCount = 0;
}

Batch::~Batch(){}

void Batch::initBatchBuffers(int vertices, int indices)
{
    // Initial all these bufferss according to the vertices and indices
    vertexCount = vertices;
    storeVertexCount = 0;
    indexCount = indices;

    // Allocate memory
    vertexBuffer.resize(vertexCount * 3);
    normalBuffer.resize(vertexCount * 3);
    texcoordBuffer.resize(vertexCount * 4);
    colorBuffer.resize(vertexCount * 3);
    objectidBuffer.resize(vertexCount);

    if (indexCount > 0)
        indexBuffer.resize(indexCount);
    modelMatrices.setToIdentity();
    normalMatrices.setToIdentity();
}

void Batch::pushMeshToBuffers(Mesh *mesh, int mid, bool fullStatic,
                              const QMatrix4x4 &transformMatrix,
                              const QMatrix4x4 &normalMatrix)
{
    // Get the buffer data from mesh
    this->fullStatic = fullStatic;
    // The last vertex index that have been stored
    int baseVertex = storeVertexCount;
    int currentObject = objectCount;
    for(auto i = 0;i < vertexCount;++i){
        QVector4D vertex = mesh->vertices[i];
        QVector4D normal(mesh->normals[i].x(),
                         mesh->normals[i].y(),
                         mesh->normals[i].z(),0);
        QVector2D texcoord = mesh->texcoords[i];

        // Create the material
        Material *mat = nullptr;
        // get texture index int texture array
        if(mesh->materialids.empty() && mid > 0){
            mat = MaterialManager::materials->find(mid);
            //qDebug() << "mid->" << mat->id << "," << mat->texture.x();
        }
        else if(!mesh->materialids.empty()){
            mat = MaterialManager::materials->find(mesh->materialids[i]);
        }
        if (!mat){
            // no material, set to deafult configure
            mat = MaterialManager::materials->find(0);
        }
        QVector3D ambient = mat->ambient;
        QVector3D diffuse = mat->diffuse;
        QVector3D specular = mat->specular;
        QVector4D textures = mat->texture;

        // Transfer it to the corresponding buffer.
        if(fullStatic){
            vertex = transformMatrix * vertex;
            normal = normalMatrix * vertex;
        }
        vertexBuffer[storeVertexCount * 3] = vertex.x() / vertex.w();
        vertexBuffer[storeVertexCount * 3 + 1] = vertex.y() / vertex.w();
        vertexBuffer[storeVertexCount * 3 + 2] = vertex.z() / vertex.w();

        normalBuffer[storeVertexCount * 3] = normal.x();
        normalBuffer[storeVertexCount * 3 + 1] = normal.y();
        normalBuffer[storeVertexCount * 3 + 2] = normal.z();

        // How many components
        textureChannel = textures.y() >= 0 ? 4 : 3;
        texcoordBuffer[storeVertexCount * textureChannel] = texcoord.x();
        texcoordBuffer[storeVertexCount * textureChannel + 1] = texcoord.y();
        texcoordBuffer[storeVertexCount * textureChannel + 2] = textures.x();
        if (textureChannel == 4)
            texcoordBuffer[storeVertexCount * textureChannel + 3] = textures.y();

        // Color buffer
        colorBuffer[storeVertexCount * 3] = (unsigned char)(ambient.x() * 255);
        colorBuffer[storeVertexCount * 3 + 1] = (unsigned char)(diffuse.x() * 255);
        colorBuffer[storeVertexCount * 3 + 2] = (unsigned char)(specular.x() * 255);

        objectidBuffer[storeVertexCount] = currentObject;

        storeVertexCount++;
    }

    if(!mesh->indices.empty()) {
        for(auto i = 0;i < mesh->indexCount;++i) {
            int index = baseVertex+mesh->indices[i];
            indexBuffer[storeIndexCount] = (uint)index;
            storeIndexCount++;
        }
    }

    initMatrix(currentObject, transformMatrix, normalMatrix);
    ++objectCount;
}

void Batch::updateMatrices(unsigned short objectId, const QMatrix4x4 &transformMatrix,
                           const QMatrix4x4 *normalMatrix)
{
    Q_UNUSED(objectId);
    modelMatrices = transformMatrix;
    normalMatrices = *normalMatrix;
}

void Batch::releaseBuffers()
{
    std::vector<float> v;
    std::vector<float> n;
    std::vector<float> t;
    std::vector<unsigned char> c;
    std::vector<unsigned char> o;
    std::vector<unsigned int> i;
    vertexBuffer.swap(v);
    normalBuffer.swap(n);
    texcoordBuffer.swap(t);
    colorBuffer.swap(c);
    objectidBuffer.swap(o);
    indexBuffer.swap(i);
}

inline void Batch::initMatrix(unsigned short currentObject, const QMatrix4x4 &transformMatrix,
                              const QMatrix4x4 &normalMatrix)
{
    Q_UNUSED(currentObject);
    modelMatrices = transformMatrix;
    normalMatrices = normalMatrix;
}
