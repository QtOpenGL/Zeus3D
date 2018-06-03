#include "RenderManager.h"
#include "../Scene/AssetManager.h"
#include "../Texture/FrameTexture2D.h"

RenderManager::RenderManager(const QVector3D &light)
{

    // frame buffer
    lightDir = light;
    lightDir.normalize();

    // render queue
    staticQueue = new RenderQueue();
    state = new RenderState();

    instanceShader = nullptr;
    entityShader = nullptr;
    skyboxShader = nullptr;
    deferredShader = nullptr;
    animationShader = nullptr;
    deferredFilter = nullptr;
    shadow = nullptr;
}

RenderManager::~RenderManager()
{
    delete state; state = nullptr;
    delete staticQueue; staticQueue = nullptr;

    if(deferredFilter) delete deferredFilter;
    deferredFilter = nullptr;
    for(auto it = lights.begin();it != lights.end();++it){
        delete it->second;
    }
    lights.clear();
    if(shadow)delete shadow;
    shadow = nullptr;
}

void RenderManager::resize(Render *render, int width, int height)
{
    // reset the viewport.
    render->setViewPort(width,height);
    // we also need to reset the deferred rendering fbo
    if(deferredFilter) delete deferredFilter;
    deferredFilter = new Filter(width,height,true,FrameTexture2D::HIGH_PRE,
                                3,render->findShader("GaussianBlur"));
    deferredFilter->getDeferredFramebuffer()->addColorBuffer(FrameTexture2D::LOW_PRE,4);
    deferredFilter->getDeferredFramebuffer()->addColorBuffer(FrameTexture2D::LOW_PRE,3);
    deferredFilter->getDeferredFramebuffer()->addColorBuffer(FrameTexture2D::LOW_PRE,3);
    deferredFilter->getDeferredFramebuffer()->attachDepthBuffer(FrameTexture2D::LOW_PRE);
    render->clearTextureSlots();
}

void RenderManager::pushToQueue(Entity *entity, DRAWCALL_DC dc)
{
    if(dc == STATIC_DC)
        staticQueue->pushEntityToQueue(entity);
    else if(dc == INSTANCE_DC)
        staticQueue->pushEntityToInstanceQueue(entity);
    else if(dc == ANIMATE_DC)
        staticQueue->pushEntityToAnimateQueue(entity);
}


void RenderManager::clearRenderQueues()
{
    staticQueue->clearQueue();
}

void RenderManager::renderScene(Render *render, Camera3D &camera, Scene *scene)
{
    state->reset();
    if (!entityShader)
        entityShader = render->findShader("Entity");
    if(!instanceShader)
        instanceShader = render->findShader("Instance");
    if(!animationShader)
        animationShader = render->findShader("Animation");
    if (!skyboxShader)
        skyboxShader = render->findShader("sky");

    // bind texture array
    render->useTexture(Render::TEXTURE_2D_ARRAY,0,
                       AssetManager::assetManager->textures->arrayId);
    state->shaderIns = instanceShader;

    // static entity
    state->shader = render->findShader("Entity");
    staticQueue->renderStaticEntity(&camera,render,state);
    render->finishRender();

    // animate entity
    state->shader = render->findShader("Animation");
    staticQueue->renderAnimateEntity(&camera,render,state);
    render->finishRender();

    // instanced entity
    state->shader = render->findShader("Instance");
    staticQueue->renderInstanceEntity(&camera,render,state);
    render->finishRender();

    // Draw sky
    if (scene->skyBox){
        scene->skyBox->render(render, skyboxShader, &camera);
        render->finishRender();
    }
}

void RenderManager::renderShadow(Render *render, Camera3D &camera,
                                 Lighting *dirLight)
{
    Q_UNUSED(dirLight)
    // render shadow effect
    if(!shadow)return;
    state->reset();
    state->pass = 5;
    state->cullMode.first = true;
    state->cullMode.second = CULL_FRONT;
    // static entity
    state->shader = render->findShader("Entity_Shadow");
    staticQueue->renderStaticEntity(&camera,render,state);
    render->finishRender();

    // animate entity
    state->shader = render->findShader("Animation_Shadow");
    staticQueue->renderAnimateEntity(&camera,render,state);
    render->finishRender();

    // instanced entity
    state->shader = render->findShader("Instance_Shadow");
    staticQueue->renderInstanceEntity(&camera,render,state);
    render->finishRender();
}

FrameBuffer *RenderManager::getDeferredFramebuffer()
{
    return deferredFilter->getDeferredFramebuffer();
}

FrameBuffer *RenderManager::getBloomFramebuffer()
{
    return deferredFilter->getBloomFramebuffer();
}

void RenderManager::renderDeferred(Render *render, Camera3D &camera)
{
    state->reset();
    if(!deferredShader)
        deferredShader = render->findShader("DeferredRender");
    // set state
    state->cullMode.first = false;
    state->depthMode.first = false;
    state->pass = 6;
    state->shader = deferredShader;
    deferredFilter->renderDeferred(&camera, render, state,
                                   deferredFilter->getDeferredFramebuffer()->colorBuffers,
                                   deferredFilter->getDeferredFramebuffer()->depthBuffer,
                                   shadow->getFramebuffer()->depthBuffer);
}

void RenderManager::renderBloom(Render *render, Camera3D &camera)
{
    // blur it
    deferredFilter->blurProcess();
    // render to quad
    state->reset();
    state->cullMode.first = false;
    state->depthMode.first = false;
    state->pass = 7;
    state->shader = render->findShader("Combine");
    deferredFilter->renderBloom(&camera, render, state);
}

void RenderManager::animateQueue(long startTime, long currentTime)
{
    staticQueue->animate(startTime,currentTime);
}

void RenderManager::addLighting(const QString &name, Lighting *light)
{
    if(lights.find(name) != lights.end()){
        qDebug() << "Lighting already exists!->" << name;
        return;
    }
    lights[name] = light;
}

Lighting *RenderManager::getLighting(const QString &name)
{
    if(lights.find(name) == lights.end()){
        return nullptr;
    }
    return lights[name];
}

void RenderManager::setAllLightToUniform(Render *render)
{
    // set the light uniform
    for(auto it = lights.begin();it != lights.end();++it){
        render->setLightingUnfiorm(it->second);
    }
}

void RenderManager::setShadow(const int &width, const int &height)
{
    if(shadow)delete shadow;
    shadow = new Shadow(width,height);
}

Shadow *RenderManager::getShadow()
{
    return shadow;
}
