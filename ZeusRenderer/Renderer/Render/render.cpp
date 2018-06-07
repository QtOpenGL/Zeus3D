#include "Render.h"
#include "../Mesh/Mesh.h"
#include "../Mesh/Batch.h"
#include "../Mesh/InstanceBatch.h"
#include "../Mesh/AnimationBatch.h"
#include "../Render/AnimationDrawcall.h"
#include "../Render/StaticDrawcall.h"
#include "../Lighting/DirLight.h"
#include "../Lighting/PointLight.h"
#include <QDebug>

Render::Render()
{
    shaders = new ShaderManager();
    initEnvironment();
}

Render::~Render()
{
    delete shaders;
    shaders = nullptr;
    textureInUse.clear();
    for(auto it = drawcallTable.begin();it != drawcallTable.end();++it)
        delete it->second;
    drawcallTable.clear();
}

void Render::addShader(const QString &name, const QString &vert, const QString &frag)
{
    this->shaders->addShader(name,vert,frag);
}

void Render::initEnvironment()
{
    // force to refresh states' configuration
    depthMode = std::pair<bool,int>(false,GREATER);
    cullMode = std::pair<bool,int>(false,CULL_NONE);
    polygonMode = true;
    setDepthMode(true,LEQUAL);
    setCullMode(true,CULL_BACK);
    setPolygonMode(false);
    setClearColor(0.5,0.5,0.5,1);
    currentShader = nullptr;
    defaultFramebuffer = 0;
    textureInUse.clear();
    // load shaders here
    shaders->addShader("DeferredRender",":/shaders/DeferredRender.vert",
                       ":/shaders/DeferredRender.frag");
    shaders->addShader("Animation",":/shaders/Animation.vert",
                       ":/shaders/Animation.frag");
    shaders->addShader("Instance",":/shaders/Instance.vert",
                       ":/shaders/Instance.frag");
    shaders->addShader("Entity",":/shaders/Entity.vert",
                       ":/shaders/Entity.frag");
    shaders->addShader("sky",":/shaders/sky.vert",
                       ":/shaders/sky.frag");

    // shadow shaders
    shaders->addShader("Animation_Shadow",":/shaders/Shadow/Animation_Shadow.vert",
                       ":/shaders/Shadow/Simple_Shadow.frag");
    shaders->addShader("Instance_Shadow",":/shaders/Shadow/Instance_Shadow.vert",
                       ":/shaders/Shadow/Simple_Shadow.frag");
    shaders->addShader("Entity_Shadow",":/shaders/Shadow/Entity_Shadow.vert",
                       ":/shaders/Shadow/Simple_Shadow.frag");

    // post-processing
    shaders->addShader("GaussianBlur",":/shaders/GaussianBlur.comp");
    shaders->addShader("Combine",":/shaders/DeferredRender.vert",
                       ":/shaders/Combine.frag");

    // set uniform variable
    ShaderProgram *tmp = nullptr;
    // instance shader
    tmp = shaders->findShader("Instance");
    tmp->use();
    tmp->setInt("image",0);
    // entity shader
    tmp = shaders->findShader("Entity");
    tmp->use();
    tmp->setInt("image",0);
    // sky shader
    tmp = shaders->findShader("sky");
    tmp->use();
    tmp->setInt("textureSky",0);
    // animation shader
    tmp = shaders->findShader("Animation");
    tmp->use();
    tmp->setInt("image",0);
    // bloom combined
    tmp = shaders->findShader("Combine");
    tmp->use();
    tmp->setInt("sceneTexture",0);
    tmp->setInt("bloomTexture",1);
    tmp->setFloat("exposure",2.0f);
    // defered rendering shader
    tmp = shaders->findShader("DeferredRender");
    tmp->use();
    tmp->setInt("posBuffer", 0);
    tmp->setInt("texBuffer", 1);
    tmp->setInt("normalBuffer", 2);
    tmp->setInt("specBuffer", 3);
    tmp->setInt("depthBuffer",4);
    tmp->setInt("shadowBuffer",5);
    tmp->setFloat("fog.fogDensity",0.005f);
    tmp->setVector3("fog.fogColor",QVector3D(0.2f,0.2f,0.2f));
}

void Render::setClearFrame(bool clearColor, bool clearDepth, bool clearStencil)
{
    // here we set the clear mask to clear frame
    GLbitfield clearMask = GL_COLOR_BUFFER_BIT;
    if(clearColor) clearMask |= GL_COLOR_BUFFER_BIT;
    if(clearDepth) clearMask |= GL_DEPTH_BUFFER_BIT;
    if(clearStencil) clearMask |= GL_STENCIL_BUFFER_BIT;
    GlobalContext::contextFunc->glClear(clearMask);
}

void Render::setDefaultFramebuffer(GLuint fbo)
{
    defaultFramebuffer = fbo;
}

void Render::setLightingUnfiorm(Lighting *light)
{
    ShaderProgram *target = shaders->findShader("DeferredRender");
    target->use();
    // directional lighting here
    if(light->getType() == Lighting::DIRECTION_LIGHT)
    {
        target->setVector3("dirLight.direction",light->getDirection());
        target->setVector3("dirLight.ambient",light->getAmbient());
        target->setVector3("dirLight.diffuse",light->getDiffuse());
        target->setVector3("dirLight.specular",light->getSpecular());
    }
    else if(light->getType() == Lighting::POINT_LIGHT)
    {
        PointLight *plight = static_cast<PointLight*>(light);
        QString name = QObject::tr("pointLights[%1]").arg(plight->index);
        target->setVector3(name+".position",plight->getPosition());
        target->setVector3(name+".ambient",plight->getAmbient());
        target->setVector3(name+".diffuse",plight->getDiffuse());
        target->setVector3(name+".specular",plight->getSpecular());
        target->setFloat(name+".constant",plight->getAttenuation().x());
        target->setFloat(name+".linear",plight->getAttenuation().y());
        target->setFloat(name+".quadratic",plight->getAttenuation().z());
        target->setInt("pointLightsNum",plight->numPointLights);
    }
}

void Render::setState(const RenderState *state)
{
    // set the render state according to the given paramter
    setDepthMode(state->depthMode.first,state->depthMode.second);
    setCullMode(state->cullMode.first,state->cullMode.second);
    setPolygonMode(state->polygonMode);
}

void Render::setDepthMode(bool enable, int testMode)
{
    // set the depth testing state and testing mode
    // a bug here to uncomment the next line.
    //if(enable != depthMode.first) {
    depthMode.first = enable;
    if(enable){
        GlobalContext::contextFunc->glEnable(GL_DEPTH_TEST);
    }
    else{
        GlobalContext::contextFunc->glDisable(GL_DEPTH_TEST);
    }
    //}
    // set the corresponding comparsion mode of depth testing
    //if(testMode != depthMode.second) {
    depthMode.second = testMode;
    switch(testMode) {
    case LESS:
        GlobalContext::contextFunc->glDepthFunc(GL_LESS);
        break;
    case LEQUAL:
        GlobalContext::contextFunc->glDepthFunc(GL_LEQUAL);
        break;
    case GREATER:
        GlobalContext::contextFunc->glDepthFunc(GL_GREATER);
        break;
    case GEQUAL:
        GlobalContext::contextFunc->glDepthFunc(GL_GEQUAL);
        break;
    }
    //}
}

void Render::setCullMode(bool enable, int testMode)
{
    // set the cull testing state and testing mode
    if(enable != cullMode.first) {
        cullMode.first = enable;
        if(enable)
            GlobalContext::contextFunc->glEnable(GL_CULL_FACE);
        else
            GlobalContext::contextFunc->glDisable(GL_CULL_FACE);
    }
    if(!enable) return;
    // set the corresponding comparsion mode of cull testing
    if(testMode != cullMode.second) {
        cullMode.second = testMode;
        switch(testMode) {
        case CULL_BACK:
            GlobalContext::contextFunc->glCullFace(GL_BACK);
            break;
        case CULL_FRONT:
            GlobalContext::contextFunc->glCullFace(GL_FRONT);
            break;
        case CULL_NONE:
            GlobalContext::contextFunc->glCullFace(GL_NONE);
            break;
        }
    }
}

void Render::setFrameBuffer(FrameBuffer *framebuffer)
{
    // bind the given framebuffer to OpenGL.
    if(framebuffer){
        framebuffer->use();
        setClearColor(0.5,0.5,0.5,1);
        setClearFrame(true,true,false);
        setViewPort(framebuffer->width,framebuffer->height);
    }
    else {
        // if there is no framebuffer to set, we set it to default.
        GlobalContext::contextFunc->glBindFramebuffer(GL_FRAMEBUFFER,
                                                      defaultFramebuffer);
        setClearColor(0.5,0.5,0.5,1);
        setClearFrame(true,true,false);
        setViewPort(viewPort.first,viewPort.second);
    }
}

void Render::setPolygonMode(bool mode)
{
    // set the polygon mode of OpenGL
    if(!mode)
        GlobalContext::contextFunc->glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    else
        GlobalContext::contextFunc->glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
}

void Render::setClearColor(float r, float g, float b, float a)
{
    // set clearing color
    clearColor = QColor(r,g,b,a);
    GlobalContext::contextFunc->glClearColor(r,g,b,a);
}

void Render::setViewPort(int width, int height)
{
    if(height == 0) height = 1;
    viewPort = std::pair<int,int>(width,height);
    GlobalContext::contextFunc->glViewport(0,0,width,height);
}

void Render::setProjectPlane(float nearP, float farP)
{
    ShaderProgram *tmp = shaders->findShader("DeferredRender");
    tmp->use();
    tmp->setFloat("nearPlane",nearP);
    tmp->setFloat("farPlane",farP);
}

ShaderProgram *Render::findShader(const QString &shader)
{
    return shaders->findShader(shader);
}

void Render::useShader(ShaderProgram *shader)
{
    // bind shader
    // a bug here to uncomment the next line.
    //if (shader == currentShader) return;
    currentShader = shader;
    shader->use();
}

DrawCall *Render::getDrawcall(const QString &target)
{
    if(drawcallTable.find(target) == drawcallTable.end())
        return nullptr;
    return drawcallTable[target];
}


void Render::render(Camera3D *camera, Entity *target, RenderState *state)
{
    // firstly load the RenderState.
    setState(state);

    // secondly load the ShaderProgram
    ShaderProgram *shader = state->shader;
    useShader(shader);

    // thirdly set uniform values of drawcall.
    if (state->pass <= 4) {
        if (!state->skyPass){
            if(getDrawcall(target->drawcall)->getType() != INSTANCE_DC){
                shader->setMatrix4("modelMatrix",target->modelMatrix);
                shader->setMatrix4("normalMatrix",target->normalMatrix);
            }
            shader->setMatrix4("viewProjectMatrix",
                               camera->getViewProjectMatrix());
        }
        else {
            shader->setMatrix4("viewMatrix", camera->getViewMatrix());
            shader->setMatrix4("projectMatrix", camera->getProjectMatrix());
        }
    }
    else if(state->pass == 5){//shadow map
        if(getDrawcall(target->drawcall)->getType() != INSTANCE_DC){
            shader->setMatrix4("modelMatrix",target->modelMatrix);
        }
        shader->setMatrix4("lightSpaceMatrix",
                           camera->getLightSpaceMatrix());
    }
    else if(state->pass == 6){// deferred rendering
        shader->setMatrix4("lightSpaceMatrix",
                           camera->getLightSpaceMatrix());
    }
    // fourthly call that drawcall function
    this->getDrawcall(target->drawcall)->draw(shader, state->pass);
}

void Render::finishRender()
{
    GlobalContext::contextFunc->glBindVertexArray(0);
}

void Render::useTexture(uint type, uint slot, uint texid)
{
    // slot is texture unit
    std::map<uint, uint>::iterator texItor = textureInUse.find(slot);
    // if it's already set, nothing to do.
    if (texItor != textureInUse.end() && texItor->second == texid){
        qDebug() << "confilct texture slot！！！";
        return;
    }
    GLenum textureType = GL_TEXTURE_2D;
    switch (type) {
    case TEXTURE_2D:
        textureType = GL_TEXTURE_2D;
        break;
    case TEXTURE_2D_ARRAY:
        textureType = GL_TEXTURE_2D_ARRAY;
        break;
    case TEXTURE_CUBE:
        textureType = GL_TEXTURE_CUBE_MAP;
        break;
    }
    GlobalContext::contextFunc->glActiveTexture(GL_TEXTURE0 + slot);
    GlobalContext::contextFunc->glBindTexture(textureType, texid);
    textureInUse[slot] = texid;
}

void Render::clearTextureSlots()
{
    textureInUse.clear();
}

void Render::addStaticDrawcall(const QString &callname, Mesh *mesh, Material *mat)
{
    // add a static drawcall to table
    if(drawcallTable.find(callname) != drawcallTable.end()){
        qDebug() << "drawcall exitsed->" << callname;
        return;
    }
    Batch *batch = new Batch();
    batch->initBatchBuffers(mesh->vertexCount,mesh->indexCount);
    QMatrix4x4 tmp;
    tmp.setToIdentity();
    if(mat)
        batch->pushMeshToBuffers(mesh,mat->id,false,tmp,tmp);
    else
        batch->pushMeshToBuffers(mesh,0,false,tmp,tmp);
    DrawCall *newone = new StaticDrawcall(batch);
    drawcallTable[callname] = newone;
}

void Render::addInstanceDrawcall(const QString &callname, Mesh *mesh,Material *mat,
                                 const std::vector<QMatrix4x4> &instanceMatrix)
{
    // add a instanced drawcall to table
    if(drawcallTable.find(callname) != drawcallTable.end())
        return;
    InstanceBatch *batch = new InstanceBatch();
    batch->initInstanceBuffers(instanceMatrix.size(),
                               mesh->vertexCount,
                               mesh->indexCount);
    if(mat) batch->pushMeshToBuffers(mesh,mat->id,false);
    else batch->pushMeshToBuffers(mesh,0,false);
    // set instanced matrix
    for(uint x = 0;x < instanceMatrix.size();++x){
        batch->setMatricesBuffer(x,instanceMatrix[x]);
    }

    InstanceDrawcall *newone = new InstanceDrawcall(batch,false);
    drawcallTable[callname] = newone;
}

void Render::addAnimateDrawcall(const QString &callname, AnimationLoader *loader,
                                Material *mat)
{
    // add a animate drawcall to table
    if(drawcallTable.find(callname) != drawcallTable.end())
        return;
    AnimationDrawcall *newone = new AnimationDrawcall(loader);
    Q_UNUSED(mat);
    drawcallTable[callname] = newone;
}
