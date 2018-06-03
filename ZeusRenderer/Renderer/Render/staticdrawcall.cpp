#include "StaticDrawcall.h"
#include "../Context.h"
#include <QDebug>

StaticDrawcall::StaticDrawcall(){}

StaticDrawcall::StaticDrawcall(Batch *batch)
    :DrawCall()
{
    vertexCount = batch->vertexCount;
    indexCount = batch->indexCount;
    objectCount = batch->objectCount;
    // Indices or not
    indexed = indexCount > 0 ? true : false;
    this->batch = batch;
    batch->fullStatic = true;
    setFullStatic(batch->fullStatic);

    // Create four basic kinds of buffers
    int bufCount = 4;
    // Add more buffers as need
    bufCount = !isFullStatic() ? bufCount + 1 : bufCount;
    bufCount = indexed ? bufCount + 1 : bufCount;
    dataBuffer = new RenderBuffer(bufCount);
    dataBuffer->pushData(0, new RenderData(VERTEX_LOCATION, GL_FLOAT, vertexCount, 3, 1,
                                           dataBuffer->vbos[0], false, GL_STATIC_DRAW, -1, &batch->vertexBuffer[0]));
    dataBuffer->pushData(1, new RenderData(NORMAL_LOCATION, GL_FLOAT, vertexCount, 3, 1,
                                           dataBuffer->vbos[1], false, GL_STATIC_DRAW, -1, &batch->normalBuffer[0]));
    dataBuffer->pushData(2, new RenderData(TEXCOORD_LOCATION, GL_FLOAT, vertexCount, batch->textureChannel, 1,
                                           dataBuffer->vbos[2], false, GL_STATIC_DRAW, -1, &batch->texcoordBuffer[0]));
    dataBuffer->pushData(3, new RenderData(COLOR_LOCATION, GL_UNSIGNED_BYTE, vertexCount, 3, 1,
                                           dataBuffer->vbos[3], false, GL_STATIC_DRAW, -1, &batch->colorBuffer[0]));

    int indexVBO = 5;
    if (!isFullStatic())
        dataBuffer->pushData(4, new RenderData(OBJECTID_LOCATION, GL_UNSIGNED_BYTE, vertexCount, 1, 1,
                                               dataBuffer->vbos[4], false, GL_STATIC_DRAW, -1, &batch->objectidBuffer[0]));
    else
        indexVBO = 4;

    if (indexed)
        dataBuffer->pushData(indexVBO, new RenderData(GL_UNSIGNED_INT, indexCount,
                                                      dataBuffer->vbos[indexVBO], GL_STATIC_DRAW, &batch->indexBuffer[0]));

    dataBuffer->release();

    createSimple();

    uModelMatrix = batch->modelMatrices;
    uNormalMatrix = batch->normalMatrices;
    setType(STATIC_DC);

    batch->releaseBuffers();
}

StaticDrawcall::~StaticDrawcall()
{
    releaseSimple();
    delete dataBuffer;
    if(batch)delete batch;
    batch = nullptr;
}

void StaticDrawcall::createSimple()
{
    // simple buffer, there are only vertices and texcoords
    int bufCount = 2;
    bufCount = !isFullStatic() ? bufCount + 1 : bufCount;
    bufCount = indexed ? bufCount + 1 : bufCount;
    simpleBuffer = new RenderBuffer(bufCount);
    simpleBuffer->pushData(0, new RenderData(0, GL_FLOAT, vertexCount,
                                             3, 1,
                                             simpleBuffer->vbos[0],
                           false, GL_STATIC_DRAW, -1,
                           &batch->vertexBuffer[0]));
    simpleBuffer->pushData(1, new RenderData(1, GL_FLOAT, vertexCount,
                                             batch->textureChannel, 1,
                                             simpleBuffer->vbos[1],
                           false, GL_STATIC_DRAW, -1, &batch->texcoordBuffer[0]));

    // the same as above
    int indexVBO = 3;
    if (!isFullStatic()) {
        simpleBuffer->pushData(2, new RenderData(2, GL_UNSIGNED_BYTE, vertexCount, 1, 1,
                                                 simpleBuffer->vbos[2], false,
                               GL_STATIC_DRAW, -1, &batch->objectidBuffer[0]));
    }
    else
        indexVBO = 2;

    if (indexed) {
        simpleBuffer->pushData(indexVBO, new RenderData(GL_UNSIGNED_INT, indexCount,
                                                        simpleBuffer->vbos[indexVBO],
                                                        GL_STATIC_DRAW, &batch->indexBuffer[0]));
    }
}

void StaticDrawcall::releaseSimple()
{
    delete simpleBuffer;
}

void StaticDrawcall::draw(ShaderProgram *shader, int pass)
{
    Q_UNUSED(shader);
    switch (pass) {
    case 1:
    case 2:
    case 3:
    case 5:
    case 6:
    case 7:
        simpleBuffer->use();
        break;
    case 4:
        dataBuffer->use();
        break;
    }
    if(!indexed)
        GlobalContext::contextFunc->glDrawArrays(GL_TRIANGLES,0,vertexCount);
    else
        GlobalContext::contextFunc->glDrawElements(GL_TRIANGLES,indexCount,GL_UNSIGNED_INT,0);
}

void StaticDrawcall::updateMatrices(Batch *batch)
{
    uModelMatrix = batch->modelMatrices;
}
