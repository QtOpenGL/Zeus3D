#ifndef BATCH_H
#define BATCH_H

#include "../Material/MaterialManager.h"
#include "Mesh.h"

#include <QMatrix4x4>
#include <vector>
/*
 * Batch processing the objects
 */
#ifndef MAX_OBJECT_COUNT
#define MAX_OBJECT_COUNT 100
#endif
class Batch
{
public:
    int vertexCount,indexCount;
    // All kinds of buffer here
    std::vector<float> vertexBuffer;
    std::vector<float> normalBuffer;
    std::vector<float> texcoordBuffer;
    std::vector<unsigned char> colorBuffer;
    std::vector<unsigned char> objectidBuffer;
    std::vector<unsigned int> indexBuffer;

    // The object is stati or not
    bool fullStatic;
    // Record the quantity of objects
    unsigned short objectCount;

    // Here comes model and normal matrices
    QMatrix4x4 modelMatrices;
    QMatrix4x4 normalMatrices;

    int textureChannel;

    Batch();
    ~Batch();

    void initBatchBuffers(int vertices,int indices);
    void pushMeshToBuffers(Mesh* mesh,int mid,bool fullStatic,
                           const QMatrix4x4& transformMatrix,const QMatrix4x4& normalMatrix);
    void updateMatrices(unsigned short objectId, const QMatrix4x4& transformMatrix,
                        const QMatrix4x4* normalMatrix);

    void releaseBuffers();

private:
    // Theses two mean that how many data have stored to buffer, we cache the last index of them.
    int storeVertexCount,storeIndexCount;
    inline void initMatrix(unsigned short currentObject,const QMatrix4x4& transformMatrix,
                    const QMatrix4x4& normalMatrix);
};

#endif // BATCH_H
