#include "MaterialManager.h"

MaterialManager* MaterialManager::materials = nullptr;

void MaterialManager::Init()
{
    if (!MaterialManager::materials)
        MaterialManager::materials = new MaterialManager();
}

void MaterialManager::Release()
{
    if (MaterialManager::materials)
        delete MaterialManager::materials;
    MaterialManager::materials = nullptr;
}

unsigned int MaterialManager::add(Material *material)
{
    materialList.push_back(material);
    materialMap[material->name] = material;
    int mid = materialList.size() - 1; // Start from 0
    material->id = mid; // id is the index of list
    return mid;
}

void MaterialManager::remove(unsigned int i)
{
    // Remove the material with id i
    if (materialList.size() < i + 1) return;
    int oldMid = materialList[i]->id;
    QString oldName = materialList[i]->name;
    delete materialList[i];
    // Create the empty material to replace it
    Material* mtlEmp = new Material(oldName);
    mtlEmp->id = oldMid;
    materialList[i] = mtlEmp;
    materialMap[oldName] = mtlEmp;
}

Material *MaterialManager::find(unsigned int i)
{
    // Get material
    if (materialList.size() < i + 1) return nullptr;
    return materialList[i];
}

int MaterialManager::find(QString name)
{
    // Get material id
    if (materialMap.count(name) <= 0) return 0;
    return materialMap[name]->id;
}

unsigned int MaterialManager::size()
{
    return materialList.size();
}

MaterialManager::MaterialManager()
{
    // Create two default material, it world be needed in some place
    Material* defaultMat = new Material(DEFAULT_MAT);
    add(defaultMat);
    Material* blackMat = new Material(BLACK_MAT);
    blackMat->ambient = QVector3D(0, 0, 0);
    blackMat->diffuse = QVector3D(0, 0, 0);
    add(blackMat);
}

MaterialManager::~MaterialManager()
{
    for (unsigned int i = 0; i < materialList.size(); i++)
        delete materialList[i];
    materialList.clear();
    materialMap.clear();
}
