#include "FrameBuffer.h"
#include <QDebug>

FrameBuffer::FrameBuffer(float width, float height, int precision, int component)
    :width(width),height(height)
{
    // set initial properties
    colorBufferCount = 0;
    depthBuffer = nullptr;
    GlobalContext::contextFunc->glGenFramebuffers(1,&fboId);
    // add an basic color buffer component
    addColorBuffer(precision, component);
}

FrameBuffer::~FrameBuffer()
{
    // release dynamic memory
    for(unsigned int i = 0;i < colorBuffers.size();i++)
        if(colorBuffers[i]) delete colorBuffers[i];
    colorBuffers.clear();

    if(depthBuffer) delete depthBuffer;
    depthBuffer = nullptr;
    GlobalContext::contextFunc->glDeleteFramebuffers(1,&fboId);
}

void FrameBuffer::addColorBuffer(int precision, int component, int w, int h)
{
    // add a new color buffer component to frame buffer
    ++colorBufferCount;
    int wi,he;
    if(w == -1 || h == -1){
        wi = width;
        he = height;
    }
    else{
        wi = w;
        he = h;
    }
    colorBuffers.push_back(new FrameTexture2D(wi,he,
                                              FrameTexture2D::TEXTURE_TYPE_COLOR,
                                              precision,component));
    GlobalContext::contextFunc->glBindFramebuffer(GL_FRAMEBUFFER,fboId);
    // attach the texture to the frame buffer
    GlobalContext::contextFunc->glFramebufferTexture2D(GL_FRAMEBUFFER,
                                                       GL_COLOR_ATTACHMENT0+(colorBufferCount-1),
                                                       GL_TEXTURE_2D,
                                                       colorBuffers[colorBufferCount-1]->id,
            0);
    GlobalContext::contextFunc->glDrawBuffers(colorBufferCount,ColorAttachments);

    // check error here
    if(GlobalContext::contextFunc->glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        qDebug() << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!";
    GlobalContext::contextFunc->glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void FrameBuffer::attachDepthBuffer(int precision)
{
    // add a depth component to the frame buffer
    if(depthBuffer) return;
    depthBuffer = new FrameTexture2D(width, height,
                                     FrameTexture2D::TEXTURE_TYPE_DEPTH,
                                     precision, 3);

    GlobalContext::contextFunc->glBindFramebuffer(GL_FRAMEBUFFER, fboId);
    GlobalContext::contextFunc->glFramebufferTexture2D
            (GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBuffer->id, 0);

    // check error here
    if(GlobalContext::contextFunc->glCheckFramebufferStatus(GL_FRAMEBUFFER)
            != GL_FRAMEBUFFER_COMPLETE)
        qDebug() << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!";
    GlobalContext::contextFunc->glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameTexture2D *FrameBuffer::getColorBuffer(int n)
{
    // Color buffer getter
    if((int)colorBuffers.size() < n+1)
        return nullptr;
    return colorBuffers[n];
}

void FrameBuffer::use()
{
    // Bind the frame buffer to be current frame
    GlobalContext::contextFunc->glBindFramebuffer(GL_FRAMEBUFFER,fboId);
    // we also need set clear mask and view port
}
