#ifndef SKY_H
#define SKY_H
#include "../Mesh/Sphere.h"
#include "../Entity/StaticEntity.h"
#include "../Render/Render.h"
#include "../Interactive/Camera3D.h"
/*
 * Sky.h
 *
 *  Created on: 2018-5-29
 *      Author: Zeus
 */
class Sky
{
public:
    //StaticEntityNode *skyNode;

    Sky(Mesh *sphere, GLuint cubeTex);
    ~Sky();
    void render(Render* render,ShaderProgram* shader,Camera3D* camera);

private:
    GLuint cubeMap;
    RenderState* state;
    StaticEntity* skyEntity;
};

#endif // SKY_H
