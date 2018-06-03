#ifndef RENDER_H
#define RENDER_H
#include "../Shader/ShaderManager.h"
#include "../Postprocess/FrameBuffer.h"
#include "../Interactive/Camera3d.h"
#include "../Mesh/Mesh.h"
#include "../Entity/Entity.h"
#include "../Context.h"
#include "DrawCall.h"

#include <QColor>
/*
 * render.h: describle a render state and calling
 *
 *  Created on: 2018-5-24
 *      Author: Zeus
 */
class AnimationLoader;
class Lighting;
class Render
{
public:
    enum TEXTURE_TYPE{TEXTURE_2D = 1,TEXTURE_2D_ARRAY = 2,TEXTURE_CUBE = 3};

    // Global render state
    std::pair<bool,int>     cullMode;
    std::pair<bool,int>     depthMode;
    bool                    polygonMode;
    QColor                  clearColor;
    ShaderProgram           *currentShader;
    std::pair<int,int>      viewPort;
    ShaderManager           *shaders;
    std::map<uint, uint>    textureInUse;
    GLuint                  defaultFramebuffer;// record default framebuffer

    // Constructor/Destructor
    Render();
    ~Render();

    // Setting state here
    void setState(const RenderState* state);
    void setDepthMode(bool enable,int testMode);
    void setCullMode(bool enable,int testMode);
    void setPolygonMode(bool mode);
    void setClearColor(float r,float g,float b,float a);
    void setViewPort(int width,int height);
    void setProjectPlane(float near,float far);
    void setFrameBuffer(FrameBuffer* framebuffer);
    void setClearFrame(bool clearColor,bool clearDepth,bool clearStencil);
    void setDefaultFramebuffer(GLuint fbo);
    void setLightingUnfiorm(Lighting *light);
    DrawCall *getDrawcall(const QString &target);

    // Getter/Operating
    void addShader(const QString &name,const QString &vert, const QString &frag);
    // Get shader from shader manager
    ShaderProgram* findShader(const QString &shader);
    // Use the given shader program
    void useShader(ShaderProgram* shader);
    // Draw call
    void render(Camera3D* camera, Entity *target, RenderState* state);
    void finishRender();
    // Set current frame buffer
    void useTexture(uint type, uint slot, uint texid);
    void clearTextureSlots();

    // add a drawcall
    void addStaticDrawcall(const QString &callname, Mesh* mesh, Material *mat);
    void addInstanceDrawcall(const QString &callname, Mesh* mesh, Material *mat,
                             const std::vector<QMatrix4x4> &instanceMatrix);
    void addAnimateDrawcall(const QString &callname, AnimationLoader* loader,
                            Material *mat);

private:
    void initEnvironment();

    // record the drawcall to avoid duplication
    std::map<QString,DrawCall*> drawcallTable;
};

#endif // RENDER_H
