#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include "../Mesh/Mesh.h"
#include "../Mesh/Batch.h"
#include "../Loader/AnimationLoader.h"
#include "../Texture/TextureManager.h"
/*
 * AssetManager.h
 *
 *  Created on: 2018-5-24
 *      Author: Zeus
 */
class AssetManager
{
public:
    static AssetManager* assetManager;

    std::map<QString, Mesh*> meshes;
    std::map<QString, AnimationLoader*> animations;
    TextureManager* textures;

    static void Init();
    static void Release();

    void addMesh(const QString &name, Mesh* mesh);
    void addAnimation(const QString &name, AnimationLoader* animation);
    void initTextureArray(const QString &dir);


private:
    AssetManager();
    ~AssetManager();
};

#endif // ASSETMANAGER_H
