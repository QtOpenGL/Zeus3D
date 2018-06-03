#include "AssetManager.h"
#include "../Mesh/Cube.h"
#include "../Mesh/Sphere.h"
#include "../Mesh/Quad.h"
#include "../Mesh/Board.h"

AssetManager* AssetManager::assetManager = nullptr;

void AssetManager::Init()
{
    if (!AssetManager::assetManager) {
        AssetManager::assetManager = new AssetManager();

        // Load some basic meshes
        AssetManager::assetManager->addMesh(QObject::tr("cube"), new Cube());
        AssetManager::assetManager->addMesh(QObject::tr("sphere"), new Sphere(16, 16));
        AssetManager::assetManager->addMesh(QObject::tr("board"), new Board());
        AssetManager::assetManager->addMesh(QObject::tr("quad"), new Quad());
    }
}

void AssetManager::Release()
{
    if (AssetManager::assetManager)
        delete AssetManager::assetManager;
    AssetManager::assetManager = nullptr;
}

void AssetManager::addMesh(const QString &name, Mesh *mesh)
{
    meshes[name] = mesh;
}

void AssetManager::addAnimation(const QString &name, AnimationLoader *animation)
{
    animations[name] = animation;
}

void AssetManager::initTextureArray(const QString &dir)
{
    textures->initTextureArray(dir);
}

AssetManager::AssetManager()
{
    textures = new TextureManager();
    meshes.clear();
    animations.clear();
}

AssetManager::~AssetManager()
{
    std::map<QString, Mesh*>::iterator itor;
    for (itor = meshes.begin(); itor != meshes.end(); itor++)
        delete itor->second;
    meshes.clear();

    std::map<QString, AnimationLoader*>::iterator iter;
    for (iter = animations.begin(); iter != animations.end(); iter++)
        delete iter->second;
    animations.clear();

    if (textures) delete textures;
    textures = nullptr;
}
