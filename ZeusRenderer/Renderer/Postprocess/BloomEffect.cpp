#include "BloomEffect.h"

BloomEffect::BloomEffect(ShaderProgram *processShader)
{
    blurProcess = nullptr;
    blurProcess = new GaussianBlur(processShader);
    framebuffer = nullptr;
}

BloomEffect::~BloomEffect()
{
    if(blurProcess)delete blurProcess;
    blurProcess = nullptr;
    if(framebuffer)delete framebuffer;
    framebuffer = nullptr;
}

void BloomEffect::renderProcess()
{
    blurProcess->blurProcess(framebuffer->getColorBuffer(1),
                             framebuffer->getColorBuffer(2));
}

void BloomEffect::resize(int width, int height)
{
    if(framebuffer) delete framebuffer;
    framebuffer = new FrameBuffer(width,height,FrameTexture2D::HIGH_PRE,
                                  4);
    framebuffer->addColorBuffer(FrameTexture2D::TOP_PRE,4);
    framebuffer->addColorBuffer(FrameTexture2D::TOP_PRE,4);
}
