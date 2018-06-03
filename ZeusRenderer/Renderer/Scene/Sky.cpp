#include "Sky.h"
#include "../Entity/StaticEntity.h"

Sky::Sky(Mesh *sphere, GLuint cubeTex)
{
    // create mesh
    skyEntity = new StaticEntity("sphere_draw", sphere);
    Material* mat = new Material("sky_mat");
    mat->diffuse = QVector3D(0.5f, 0.7f, 0.8f);
    skyEntity->bindMaterial(MaterialManager::materials->add(mat));
    skyEntity->setPosition(0,0,0);

    cubeMap = cubeTex;

    // set render state
    state = new RenderState();
    state->cullMode = std::pair<bool,int>(true,CULL_FRONT);
    state->lightEffect = false;
    state->skyPass = true;
}

Sky::~Sky()
{
    delete state; state = nullptr;
    delete skyEntity; skyEntity = nullptr;
}

void Sky::render(Render *render, ShaderProgram *shader, Camera3D *camera)
{
    state->shader = shader;
    render->useShader(shader);
    render->useTexture(Render::TEXTURE_CUBE, 0, this->cubeMap);
    render->render(camera,skyEntity,state);
}
