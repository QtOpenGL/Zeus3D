#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H
#include "../Scene/Scene.h"
#include "../Postprocess/Filter.h"
#include "../Interactive/Camera3D.h"
#include "RenderQueue.h"
#include "../Lighting/Lighting.h"
/*
 * RenderManager.h
 *
 *  Created on: 2018-5-29
 *      Author: Zeus
 */
class RenderManager
{
public:
    QVector3D lightDir;
    RenderState* state;
    RenderQueue *staticQueue;

    RenderManager(const QVector3D& light);
    ~RenderManager();

    void resize(Render* render, int width,int height);
    void clearRenderQueues();
    void pushToQueue(Entity *entity, DRAWCALL_DC dc = STATIC_DC);
    void renderScene(Render* render, Camera3D &camera, Scene* scene);
    void renderShadow(Render* render, Camera3D &camera, Lighting *dirLight);
    FrameBuffer *getDeferredFramebuffer();
    FrameBuffer *getBloomFramebuffer();
    void renderDeferred(Render* render, Camera3D &camera);
    void renderBloom(Render* render, Camera3D &camera);
    void animateQueue(long startTime, long currentTime);

    // lighting effect here
    void addLighting(const QString &name,Lighting *light);
    Lighting* getLighting(const QString &name);
    void setAllLightToUniform(Render *render);
    void setShadow(const int &width,const int &height);
    Shadow* getShadow();
private:
    ShaderProgram* entityShader;
    ShaderProgram* instanceShader;
    ShaderProgram* skyboxShader;
    ShaderProgram* animationShader;
    ShaderProgram* deferredShader;
    Filter* deferredFilter;
    Shadow* shadow;
    // light source here
    std::map<QString, Lighting*> lights;
};

#endif // RENDERMANAGER_H
