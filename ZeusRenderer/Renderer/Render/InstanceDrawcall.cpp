#include "InstanceDrawcall.h"
#include "../Mesh/InstanceBatch.h"
#include "../Context.h"
#include <QDebug>

InstanceDrawcall::InstanceDrawcall(InstanceBatch *instance, bool simple)
    :DrawCall(), instanceBatch(instance)
{
    vertexCount = instance->vertexCount;
    indexCount = instance->indexCount;
    indexed = indexCount > 0 ? true : false;
    objectCount = instance->instanceCount;
    objectToDraw = objectCount;
    isSimple = simple;

    if (!isSimple) {
        dataBuffer = new RenderBuffer(indexed ? 6 : 5);
        dataBuffer->pushData(0, new RenderData(VERTEX_LOCATION, GL_FLOAT, vertexCount, 3, 1,
            dataBuffer->vbos[0], false, GL_STATIC_DRAW, 0, &instance->vertexBuffer[0]));

        dataBuffer->pushData(1, new RenderData(NORMAL_LOCATION, GL_FLOAT, vertexCount, 3, 1,
            dataBuffer->vbos[1], false, GL_STATIC_DRAW, 0, &instance->normalBuffer[0]));

        dataBuffer->pushData(2, new RenderData(TEXCOORD_LOCATION, GL_FLOAT, vertexCount,instance->textureChannel, 1,
            dataBuffer->vbos[2], false, GL_STATIC_DRAW, 0, &instance->texcoordBuffer[0]));

        dataBuffer->pushData(3, new RenderData(COLOR_LOCATION, GL_UNSIGNED_BYTE, vertexCount, 3, 1,
            dataBuffer->vbos[3], false, GL_STATIC_DRAW, 0, &instance->colorBuffer[0]));

        dataBuffer->pushData(4, new RenderData(MODEL_MATRIX_LOCATION, GL_FLOAT, objectCount, 4, 4,
            dataBuffer->vbos[4], false, GL_STATIC_DRAW, 1, &instance->modelMatrices[0]));

        if (indexed)
            dataBuffer->pushData(5, new RenderData(GL_UNSIGNED_INT, indexCount,
                dataBuffer->vbos[5], GL_STATIC_DRAW, &instance->indexBuffer[0]));
    } else {
        dataBuffer = new RenderBuffer(indexed ? 4 : 3);
        dataBuffer->pushData(0, new RenderData(0, GL_FLOAT, vertexCount, 3, 1,
            dataBuffer->vbos[0], false, GL_STATIC_DRAW, 0, &instance->vertexBuffer[0]));

        dataBuffer->pushData(1, new RenderData(1, GL_FLOAT, vertexCount, instance->textureChannel, 1,
            dataBuffer->vbos[1], false, GL_STATIC_DRAW, 0, &instance->texcoordBuffer[0]));

        dataBuffer->pushData(2, new RenderData(2, GL_FLOAT, objectCount, 4, 4,
            dataBuffer->vbos[2], false, GL_STATIC_DRAW, 1, &instance->modelMatrices[0]));

        if (indexed)
            dataBuffer->pushData(3, new RenderData(GL_UNSIGNED_INT, indexCount,
                dataBuffer->vbos[3], GL_STATIC_DRAW, &instance->indexBuffer[0]));
    }

    GlobalContext::contextFunc->glBindVertexArray(0);
    GlobalContext::contextFunc->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    GlobalContext::contextFunc->glBindBuffer(GL_ARRAY_BUFFER, 0);
    instanceBatch->releaseBuffer();
    setType(INSTANCE_DC);
}

InstanceDrawcall::~InstanceDrawcall()
{
    if(dataBuffer) delete dataBuffer;
    if(instanceBatch) delete instanceBatch;
    instanceBatch = nullptr;
}

void InstanceDrawcall::createSimple() {}

void InstanceDrawcall::releaseSimple() {}

void InstanceDrawcall::draw(ShaderProgram *shader, int pass)
{
    Q_UNUSED(shader);
    Q_UNUSED(pass);
    dataBuffer->use();
    if(!indexed){
        GlobalContext::contextFunc->glDrawArraysInstanced(GL_TRIANGLES,
                                                          0,
                                                          vertexCount,
                                                          objectToDraw);
    }
    else{
        GlobalContext::contextFunc->glDrawElementsInstanced(GL_TRIANGLES,
                                                            indexCount,
                                                            GL_UNSIGNED_INT,
                                                            0,
                                                            objectToDraw);
    }
}

void InstanceDrawcall::updateMatrices(const float *modelMatrices)
{
    int stream = isSimple ? 2 : 4;
    dataBuffer->streamDatas[stream]->updateAttrBuf(
                objectToDraw, (void*)modelMatrices, GL_STREAM_DRAW);
    GlobalContext::contextFunc->glBindBuffer(GL_ARRAY_BUFFER, 0);
}
