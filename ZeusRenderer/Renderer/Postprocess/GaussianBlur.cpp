#include "GaussianBlur.h"
#include "../Context.h"
#include <QDebug>

GaussianBlur::GaussianBlur(ShaderProgram *shader)
{
    this->blurShader = shader;
}

GaussianBlur::~GaussianBlur() {}

void GaussianBlur::blurProcess(FrameTexture2D *input, FrameTexture2D *output)
{
    blurShader->use();
    for(int i = 0;i < 4;++i){
        GlobalContext::contextFunc->glBindImageTexture(0,input->id ,
                                                       0, GL_FALSE, 0, GL_READ_ONLY,
                                                       GL_RGBA32F);
        GlobalContext::contextFunc->glBindImageTexture(1,output->id ,
                                                       0, GL_FALSE, 0, GL_WRITE_ONLY,
                                                       GL_RGBA32F);
        GlobalContext::contextFunc->glDispatchCompute(1,
                                                      1024, 1);
        GlobalContext::contextFunc->glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

        GlobalContext::contextFunc->glBindImageTexture(0,output->id ,
                                                       0, GL_FALSE, 0, GL_READ_ONLY,
                                                       GL_RGBA32F);
        GlobalContext::contextFunc->glBindImageTexture(1,input->id ,
                                                       0, GL_FALSE, 0, GL_WRITE_ONLY,
                                                       GL_RGBA32F);
        GlobalContext::contextFunc->glDispatchCompute(1,
                                                      1024, 1);
        GlobalContext::contextFunc->glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    }
}
