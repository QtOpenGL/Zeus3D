#include "Scene.h"
#include "../Mesh/Cube.h"
#include "../Mesh/Sphere.h"
#include "../Render/RenderManager.h"
#include "../Entity/StaticEntity.h"
#include "../Entity/AnimationEntity.h"
#include "AssetManager.h"
#include <QDebug>

void Scene::setEntityTranslate(const QString &target, const QVector3D &translation)
{
    if(entitys.find(target) == entitys.end())return;
    entitys[target]->setPosition(translation.x(),translation.y(),translation.z());
}

void Scene::setEntityScale(const QString &target, const QVector3D &scale)
{
    if(entitys.find(target) == entitys.end())return;
    entitys[target]->setSize(scale.x(),scale.y(),scale.z());
}

void Scene::setEntityRotation(const QString &target, const float &angle,
                              const QVector3D &axis)
{
    if(entitys.find(target) == entitys.end())return;
    entitys[target]->setRotation(angle,axis.x(),axis.y(),axis.z());
}

void Scene::addStaticEntity(const QString &name, const QString &drawcall,
                            Mesh *mesh, Material *mat)
{
    if(entitys.find(name) != entitys.end())return;
    Entity* newone = new StaticEntity(drawcall, mesh);
    entitys[name] = newone;
    if(mat) newone->bindMaterial(static_cast<int>(mat->id));
}

void Scene::addAnimateEntity(const QString &name, const QString &drawcall,
                             AnimationLoader *loader, Material *mat)
{
    if(entitys.find(name) != entitys.end())return;
    Entity* newone = new AnimationEntity(drawcall, loader);
    entitys[name] = newone;
    if(mat) newone->bindMaterial(static_cast<int>(mat->id));
}

void Scene::pushEntityToRender(const QString &name, RenderManager *mgr, DRAWCALL_DC dc)
{
    if(entitys.find(name) == entitys.end()){
        qDebug() << QObject::tr("%1 not found.").arg(name);
        return;
    }
    mgr->pushToQueue(entitys[name], dc);
}

Entity *Scene::getEntity(const QString &target)
{
    if(entitys.find(target) == entitys.end()){
        qDebug() << QObject::tr("%1 not found.").arg(target);
        return nullptr;
    }
    return entitys[target];
}

Scene::Scene()
{
    skyBox = nullptr;
    entitys.clear();
    InstanceBatch::instanceTable.clear();
}

Scene::~Scene()
{
    for(auto it = entitys.begin();it != entitys.end();++it)
        delete it->second;
    entitys.clear();
}
