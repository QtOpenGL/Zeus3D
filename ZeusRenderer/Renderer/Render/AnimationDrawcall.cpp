#include "AnimationDrawcall.h"
#include "../Loader/AnimationLoader.h"
#include "../Mesh/AnimationBatch.h"
#include "../Context.h"

AnimationDrawcall::AnimationDrawcall():DrawCall() {}

AnimationDrawcall::AnimationDrawcall(AnimationLoader *anim)
    :DrawCall()
{
    animData = new AnimationBatch(anim);
    vertexCount = animData->vertexCount;
    indexCount = animData->indexCount;
    objectCount = 1;

    dataBuffer = new RenderBuffer(7);
    dataBuffer->pushData(0, new RenderData(VERTEX_LOCATION, GL_FLOAT, vertexCount, 3, 1,
                                           dataBuffer->vbos[0], false, GL_STATIC_DRAW, -1, &animData->vertices[0]));
    dataBuffer->pushData(1, new RenderData(NORMAL_LOCATION, GL_FLOAT, vertexCount, 3, 1,
                                           dataBuffer->vbos[1], false, GL_STATIC_DRAW, -1, &animData->normals[0]));
    dataBuffer->pushData(2, new RenderData(TEXCOORD_LOCATION, GL_FLOAT, vertexCount, animData->textureChannel, 1,
                                           dataBuffer->vbos[2], false, GL_STATIC_DRAW, -1, &animData->texcoords[0]));
    dataBuffer->pushData(3, new RenderData(COLOR_LOCATION, GL_UNSIGNED_BYTE, vertexCount, 3, 1,
                                           dataBuffer->vbos[3], false, GL_STATIC_DRAW, -1, &animData->colors[0]));
    dataBuffer->pushData(4, new RenderData(BONEIDS_LOCATION, GL_UNSIGNED_BYTE, vertexCount, 4, 1,
                                           dataBuffer->vbos[4], false, GL_STATIC_DRAW, -1, &animData->boneids[0]));
    dataBuffer->pushData(5, new RenderData(WEIGHTS_LOCATION, GL_FLOAT, vertexCount, 4, 1,
                                           dataBuffer->vbos[5], false, GL_STATIC_DRAW, -1, &animData->weights[0]));
    dataBuffer->pushData(6, new RenderData(GL_UNSIGNED_INT, indexCount,
                                           dataBuffer->vbos[6], GL_STATIC_DRAW, &animData->indices[0]));

    createSimple();
    GlobalContext::contextFunc->glBindVertexArray(0);
    GlobalContext::contextFunc->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    GlobalContext::contextFunc->glBindBuffer(GL_ARRAY_BUFFER, 0);

    setType(ANIMATE_DC);
}

AnimationDrawcall::~AnimationDrawcall()
{
    releaseSimple();
    delete dataBuffer;
    delete animData;
    dataBuffer = nullptr;
    animData = nullptr;
}

void AnimationDrawcall::createSimple()
{
    simpleBuffer = new RenderBuffer(4);
    simpleBuffer->pushData(0, new RenderData(0, GL_FLOAT, vertexCount, 3, 1,
                                             simpleBuffer->vbos[0], false, GL_STATIC_DRAW, -1, &animData->vertices[0]));
    simpleBuffer->pushData(1, new RenderData(1, GL_UNSIGNED_BYTE, vertexCount, 4, 1,
                                             simpleBuffer->vbos[1], false, GL_STATIC_DRAW, -1, &animData->boneids[0]));
    simpleBuffer->pushData(2, new RenderData(2, GL_FLOAT, vertexCount, 4, 1,
                                             simpleBuffer->vbos[2], false, GL_STATIC_DRAW, -1, &animData->weights[0]));
    simpleBuffer->pushData(3, new RenderData(GL_UNSIGNED_SHORT, indexCount,
                                             simpleBuffer->vbos[3], GL_STATIC_DRAW, &animData->indices[0]));
}

void AnimationDrawcall::releaseSimple()
{
    delete simpleBuffer;
    simpleBuffer = nullptr;
}

void AnimationDrawcall::draw(ShaderProgram *shader, int pass)
{
    Q_UNUSED(shader);
    if (!animData->animation->boneTransformMats.empty()){
        shader->setMatrix4("boneMatrix", animData->boneCount,
                           animData->animation->boneTransformMats);
    }
    switch (pass) {
    case 1:
    case 2:
    case 3:
    case 5:
        simpleBuffer->use();
        break;
    case 4:
        dataBuffer->use();
        break;
    }
    GlobalContext::contextFunc->glDrawElements(GL_TRIANGLES,
                                               animData->indexCount,
                                               GL_UNSIGNED_INT,
                                               0
                                               );
}
