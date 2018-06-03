#ifndef BLOOMEFFECT_H
#define BLOOMEFFECT_H
#include "FrameBuffer.h"
#include "GaussianBlur.h"
/*
 * BloomEffect.h
 *
 * Describe: BloomEffect post-processing
 *
 * Created on: 2018-6-2
 *      Author: Zeus
 */

class BloomEffect
{
public:
    BloomEffect(ShaderProgram *processShader);
    ~BloomEffect();

    FrameBuffer *getFramebuffer();

    void renderProcess();

    void resize(int width,int height);

private:
    GaussianBlur *blurProcess;
    FrameBuffer *framebuffer;
};

inline FrameBuffer *BloomEffect::getFramebuffer()
{
    return this->framebuffer;
}

#endif // BLOOMEFFECT_H
