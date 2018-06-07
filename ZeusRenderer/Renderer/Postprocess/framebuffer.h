#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <vector>
#include "../Texture/FrameTexture2d.h"
#include <QOpenGLContext>
/*
 * frame buffer object
 */

// color attachment location of OpenGL Color buffer component
const GLenum ColorAttachments[] =
{
    GL_COLOR_ATTACHMENT0,
    GL_COLOR_ATTACHMENT1,
    GL_COLOR_ATTACHMENT2,
    GL_COLOR_ATTACHMENT3,
    GL_COLOR_ATTACHMENT4,
    GL_COLOR_ATTACHMENT5,
    GL_COLOR_ATTACHMENT6,
    GL_COLOR_ATTACHMENT7
};

class FrameBuffer
{
public:
    float width,height;

    std::vector<FrameTexture2D*> colorBuffers;
    FrameTexture2D* depthBuffer;

    FrameBuffer(float width, float height, int precision, int component);
    ~FrameBuffer();

    // Adder
    void addColorBuffer(int precision, int component, int w = -1, int h = -1);
    void attachDepthBuffer(int precision);

    // Getter/Using
    FrameTexture2D* getColorBuffer(int n);
    void use();

private:
    GLuint fboId;
    int colorBufferCount;
};

#endif // FRAMEBUFFER_H
