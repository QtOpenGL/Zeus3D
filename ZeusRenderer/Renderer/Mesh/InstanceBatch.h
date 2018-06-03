#ifndef INSTANCEBATCH_H
#define INSTANCEBATCH_H
#include "../Mesh/Mesh.h"
#include "../Render/InstanceDrawcall.h"
/*
 * InstanceBatch.h
 *
 *  Created on: 2018-5-26
 *      Author: Zeus
 */
#define MAX_INSTANCE_COUNT 4096
class InstanceBatch
{
public:
    // record instance entity and it's instanced quantity
    static std::map<Mesh*, int> instanceTable;
    Mesh* instanceMesh;
    int vertexCount,indexCount;
    std::vector<float> vertexBuffer;
    std::vector<float> normalBuffer;
    std::vector<float> texcoordBuffer;
    std::vector<unsigned char> colorBuffer;
    std::vector<unsigned int> indexBuffer;
    std::vector<float> modelMatrices; // instanced matrix

    int textureChannel;
    int instanceCount;
    bool singleSide;

    InstanceBatch();
    ~InstanceBatch();
    void initInstanceBuffers(int instancedCount,int vertices,int indices);
    void pushMeshToBuffers(Mesh* mesh,int mid,bool fullStatic);
    void setMatricesBuffer(int i, const QMatrix4x4& transformMatrix);

    void releaseBuffer();
};

#endif // INSTANCEBATCH_H
