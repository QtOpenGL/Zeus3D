#include "Filter.h"
#include "../Mesh/Board.h"
#include "../Entity/StaticEntity.h"
#include <QDebug>

Filter::Filter(float width, float height, bool useFramebuffer,
               int precision, int component, ShaderProgram *shader)
{
    this->width = width;
    this->height = height;
    framebuffer = useFramebuffer ?
                new FrameBuffer(width, height, precision, component) : nullptr;

    board = new Board();
    boardEntity = new StaticEntity("board_draw", board);

    bloom = nullptr;
    //bloom
    this->setBloom(shader);
    bloom->resize(width,height);
}

Filter::~Filter()
{
    if(framebuffer) {
        delete framebuffer;
        framebuffer = nullptr;
    }
    delete boardEntity;
    delete board;
    if(bloom){
        delete bloom;
        bloom = nullptr;
    }
}

void Filter::renderDeferred(Camera3D *camera, Render *render,RenderState *state,
                            const std::vector<FrameTexture2D*> &inputTextures,
                            const FrameTexture2D* depthTexture,
                            const FrameTexture2D* shadowTexture)
{
    render->clearTextureSlots();
    render->useShader(state->shader);
    state->shader->setVector3("CameraPos",camera->getPosition());
    uint bufferid;
    for (bufferid = 0; bufferid < inputTextures.size(); bufferid++)
        render->useTexture(Render::TEXTURE_2D, bufferid, inputTextures[bufferid]->id);
    if (depthTexture){
        render->useTexture(Render::TEXTURE_2D, bufferid++, depthTexture->id);
    }
    if(shadowTexture){
        render->useTexture(Render::TEXTURE_2D,bufferid,shadowTexture->id);
    }
    render->render(camera, boardEntity, state);
}

void Filter::renderBloom(Camera3D *camera, Render *render, RenderState *state)
{
    if(!bloom)return;
    render->clearTextureSlots();
    render->useShader(state->shader);
    render->useTexture(Render::TEXTURE_2D,
                       0,bloom->getFramebuffer()->getColorBuffer(0)->id);
    render->useTexture(Render::TEXTURE_2D,
                       1,bloom->getFramebuffer()->getColorBuffer(1)->id);
    render->render(camera, boardEntity, state);
}

void Filter::setBloom(ShaderProgram *shader)
{
    if(bloom)delete bloom;
    bloom = new BloomEffect(shader);
}
