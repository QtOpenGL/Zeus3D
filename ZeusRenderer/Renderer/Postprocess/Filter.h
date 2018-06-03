#ifndef FILTER_H
#define FILTER_H
#include "../Mesh/Board.h"
#include "../Render/Render.h"
#include "../Entity/StaticEntity.h"
#include "BloomEffect.h"
/*
 * Filter.h
 *
 * Describe: cascading shadow for parallel lighting
 *
 * Created on: 2018-5-29
 *      Author: Zeus
 */

class Filter
{
public:
    Filter(float width, float height, bool useFramebuffer,
           int precision, int component, ShaderProgram *shader);
    ~Filter();

    void renderDeferred(Camera3D* camera, Render* render, RenderState* state,
        const std::vector<FrameTexture2D*>& inputTextures,
              const FrameTexture2D* depthTexture,
              const FrameTexture2D* shadowTexture);

    void renderBloom(Camera3D *camera, Render *render,RenderState *state);

    void setBloom(ShaderProgram *shader);
    void blurProcess();

    FrameTexture2D* getOutput();
    FrameBuffer *getDeferredFramebuffer();
    FrameBuffer *getBloomFramebuffer();

protected:
    float width,height;
    FrameBuffer* framebuffer;
    StaticEntity* boardEntity;
    Board* board;
    BloomEffect *bloom;
};

inline void Filter::blurProcess()
{
    bloom->renderProcess();
}

inline FrameTexture2D* Filter::getOutput()
{
    if(framebuffer){
        return framebuffer->getColorBuffer(0);
    }
    return nullptr;
}

inline FrameBuffer *Filter::getDeferredFramebuffer()
{
    return framebuffer;
}

inline FrameBuffer *Filter::getBloomFramebuffer()
{
    return bloom->getFramebuffer();
}

#endif // FILTER_H
