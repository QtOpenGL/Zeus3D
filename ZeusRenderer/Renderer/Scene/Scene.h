#ifndef SCENE_H
#define SCENE_H
#include "../Loader/AnimationLoader.h"
#include "../Entity/StaticEntity.h"
#include "Sky.h"
/*
 * Scene.h
 *
 *  Created on: 2018-5-24
 *      Author: Zeus
 */
class RenderManager;
class Scene
{
public:
    Sky* skyBox;

    void setEntityTranslate(const QString &target,const QVector3D &translation);
    void setEntityScale(const QString &target,const QVector3D &scale);
    void setEntityRotation(const QString &target,const float &angle,
                           const QVector3D &axis);

    void addStaticEntity(const QString &name, const QString &drawcall,
                         Mesh *mesh, Material *mat);
    void addAnimateEntity(const QString &name,const QString &drawcall,
                          AnimationLoader *loader, Material *mat);
    void pushEntityToRender(const QString &name, RenderManager *mgr, DRAWCALL_DC dc = STATIC_DC);

    Entity *getEntity(const QString &target);

    Scene();
    ~Scene();
private:
    std::map<QString,Entity*> entitys;
};

#endif // SCENE_H
