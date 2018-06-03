#include "GaussianBlur.h"
#include "../Context.h"

GaussianBlur::GaussianBlur(ShaderProgram *shader)
{
    this->blurShader = shader;
}

GaussianBlur::~GaussianBlur() {}

void GaussianBlur::blurProcess(FrameTexture2D *horizontal,
                               FrameTexture2D *vertical)
{
    blurShader->use();
    GlobalContext::contextFunc->glBindImageTexture(0,horizontal->id ,
                                                   0, GL_FALSE, 0, GL_READ_WRITE,
                                                   GL_RGBA32F);
    GlobalContext::contextFunc->glBindImageTexture(1, vertical->id,
                                                   0, GL_FALSE, 0, GL_READ_WRITE,
                                                   GL_RGBA32F);
    GlobalContext::contextFunc->glDispatchCompute(horizontal->width,
                                                  horizontal->height, 1);
    GlobalContext::contextFunc->glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

