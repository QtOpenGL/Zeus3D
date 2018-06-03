#include "AnimationLoader.h"
#include "../Material/MaterialManager.h"
#include "../Scene/AssetManager.h"
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>
#include <QDebug>

AnimationLoader::AnimationLoader(
        const QString &path)
{
    importer = new Assimp::Importer();
    //import it by importer
    scene = importer->ReadFile(path.toStdString().c_str(),aiProcess_Triangulate
                               | aiProcess_GenSmoothNormals
                               | aiProcess_FlipUVs
                               | aiProcess_JoinIdenticalVertices);
    vertCount = 0;
    faceCount = 0;
    boneCount = 0;
    aVertices.clear();
    aNormals.clear();
    aTexcoords.clear();
    aTextures.clear();
    aAmbients.clear();
    aDiffuses.clear();
    aSpeculars.clear();
    aIndices.clear();
    aBoneids.clear();
    aWeights.clear();

    // load mesh information from importer
    loadModel();
    animCount = scene->mNumAnimations;
    animFrames.resize(animCount);
    for (int ai = 0; ai < animCount; ai++) {
        qDebug() << ai;
        animFrames[ai] = new AnimFrame();
        prepareFrameData(ai);
    }
}

AnimationLoader::~AnimationLoader()
{
    aVertices.clear();
    aNormals.clear();
    aTexcoords.clear();
    aTextures.clear();
    aAmbients.clear();
    aDiffuses.clear();
    aSpeculars.clear();
    aIndices.clear();
    aBoneids.clear();
    aWeights.clear();
    materialMap.clear();
    boneMap.clear();
    entrys.clear();

    for(unsigned int i=0;i<boneInfos.size();i++)
        delete boneInfos[i];
    boneInfos.clear();

    for(unsigned int i=0;i<scene->mNumAnimations;i++)
        channelMaps[i].clear();
    channelMaps.clear();


    importer->FreeScene();
    delete importer;

    for (int i = 0; i < animCount; i++)
        delete animFrames[i];
    animFrames.clear();
}

void AnimationLoader::bonesTransform(int animIndex, float time)
{
    aiAnimation* animation = scene->mAnimations[animIndex];
    float ticksPerSecond = (float)animation->mTicksPerSecond;
    float ticks = time*ticksPerSecond;
    float animTime = fmodf(ticks,animation->mDuration);

    AnimFrame* animFrame = animFrames[animIndex];
    Frame* frame = animFrame->frames[(int)(animTime*100)];
    boneTransformMats.assign(frame->data.begin(),frame->data.end());
}

void AnimationLoader::loadModel()
{
    // load materials
    loadMaterials();

    // load meshes
    int meshCount = scene->mNumMeshes;
    entrys.resize(meshCount);
    int base = 0;
    for(int i = 0;i < meshCount;i++) {
        // get each mesh's info
        aiMesh* mesh = scene->mMeshes[i];
        entrys[i].mesh = mesh;
        entrys[i].materialIndex = mesh->mMaterialIndex;
        entrys[i].baseVertex = base;
        base += mesh->mNumVertices;
        // load the mesh's data
        loadMeshes(&entrys[i]);
    }

    // load bones
    aBoneids.resize(vertCount,QVector4D(0,0,0,0));
    aWeights.resize(vertCount,QVector4D(0,0,0,0));
    for(int i = 0;i < meshCount;i++) {
        aiMesh* mesh = scene->mMeshes[i];
        loadBones(mesh,i);
    }

    rootToModelMat = scene->mRootNode->mTransformation;
    rootToModelMat = rootToModelMat.Inverse();

    initChannels();
}

void AnimationLoader::loadBones(aiMesh *mesh, int meshIndex)
{
    // We get bones from each aimesh.
    // Each aiMesh contains aiBone[] and vertices[] and so on.
    for(unsigned int i = 0;i < mesh->mNumBones;i++) {
        // get the ith bone
        aiBone* bone = mesh->mBones[i];
        QString boneName = bone->mName.data;
        int boneIndex = 0;
        // we use map data structure to avoid duplication
        if(boneMap.find(boneName) == boneMap.end()) {
            boneIndex = boneCount;
            ++boneCount;
            BoneInfo* boneInfo = new BoneInfo;
            boneInfo->offset = bone->mOffsetMatrix;
            // push to bone list
            boneInfos.push_back(boneInfo);
            // record the corresponding index
            boneMap[boneName] = boneIndex;
        } else
            boneIndex = boneMap[boneName];

        // get the weight array
        for(unsigned int j = 0;j < bone->mNumWeights;j++) {
            aiVertexWeight boneWeight = bone->mWeights[j];
            // calculate the index
            int vertexid = entrys[meshIndex].baseVertex + boneWeight.mVertexId;
            float weight = boneWeight.mWeight;
            pushWeightToVertex(vertexid,boneIndex,weight);
        }
    }
}

void AnimationLoader::initChannels()
{
    // get each animations' channels array.
    // channels array contains name, positions, rotations and scalings.
    channelMaps.resize(scene->mNumAnimations);
    for(unsigned int i = 0;i < scene->mNumAnimations;i++) {
        // get this key frame
        aiAnimation* animation = scene->mAnimations[i];
        std::map<QString,aiNodeAnim*> channelMap;
        // get this frame's bone's channel
        for(unsigned int j = 0;j < animation->mNumChannels;j++) {
            aiNodeAnim* nodeAnim = animation->mChannels[j];
            QString boneName(nodeAnim->mNodeName.data);
            channelMap[boneName] = nodeAnim;
        }
        channelMaps[i] = channelMap;
    }
}

void AnimationLoader::pushWeightToVertex(int vertexid, int boneid, float weight)
{
    // we have maxnimun four bones for one vertex
    if(aWeights[vertexid].x() == 0) {
        aWeights[vertexid].setX(weight);
        aBoneids[vertexid].setX(boneid);
    }
    else if(aWeights[vertexid].y() == 0) {
        aWeights[vertexid].setY(weight);
        aBoneids[vertexid].setY(boneid);
    }
    else if(aWeights[vertexid].z() == 0) {
        aWeights[vertexid].setZ(weight);
        aBoneids[vertexid].setZ(boneid);
    }
    else if(aWeights[vertexid].w() == 0) {
        aWeights[vertexid].setW(weight);
        aBoneids[vertexid].setW(boneid);
    }
}

void AnimationLoader::loadMaterials()
{
    int matCount = scene->mNumMaterials;
    // traverse the material array
    for(int i = 0;i < matCount;i++) {
        // get aiMaterial
        aiMaterial* mat = scene->mMaterials[i];
        aiString path, name;
        aiColor4D ambient(0, 0, 0, 1), diffuse(0, 0, 0, 1), specular(0, 0, 0, 1);
        if(mat->Get(AI_MATKEY_NAME, name) != AI_SUCCESS)
            name = "animation_mat";
        // create the material in my way
        Material* mtl = new Material(name.data);
        // get texture
        if (mat->GetTexture(aiTextureType_DIFFUSE, 0, &path, nullptr,
                            nullptr, nullptr,nullptr, nullptr)
                == AI_SUCCESS) {
            TextureManager* textures = AssetManager::assetManager->textures;
            if (textures->findTexture(path.data) < 0)
                textures->addToTextureArray(path.data,"");
            int textureid = textures->findTexture(path.data);
            mtl->texture.setX(textureid);
        }
        // get light effect material
        aiGetMaterialColor(mat, AI_MATKEY_COLOR_AMBIENT, &ambient);
        aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &diffuse);
        aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &specular);
        mtl->ambient = QVector3D(ambient.r,ambient.g,ambient.b);
        mtl->diffuse = QVector3D(diffuse.r,diffuse.g,diffuse.b);
        mtl->specular = QVector3D(specular.r,specular.g,specular.b);
        materialMap[i] = MaterialManager::materials->add(mtl);
    }
}

void AnimationLoader::loadMeshes(Entry *entry)
{
    // load mesh's vertices
    aiMesh* aMesh = entry->mesh;
    int aVertCount = aMesh->mNumVertices;
    vertCount += aVertCount;
    // vertices
    for(int i = 0;i < aVertCount;i++) {
        // normal and vertex
        aiVector3D* vertex = &aMesh->mVertices[i];
        aiVector3D* normal = &aMesh->mNormals[i];
        aVertices.push_back(QVector3D(vertex->x,vertex->y,vertex->z));
        aNormals.push_back(QVector3D(normal->x,normal->y,normal->z));
        // texcoords
        if(aMesh->HasTextureCoords(0)) {
            aiVector3D* texcoord = &aMesh->mTextureCoords[0][i];
            aTexcoords.push_back(QVector2D(texcoord->x,texcoord->y));
        } else
            aTexcoords.push_back(QVector2D(0,0));

        int mid = materialMap[entry->materialIndex];
        Material* mat = MaterialManager::materials->find(mid);
        if (!mat) mat = MaterialManager::materials->find(0);
        aTextures.push_back(mat->texture);
        aAmbients.push_back(mat->ambient);
        aDiffuses.push_back(mat->diffuse);
        aSpeculars.push_back(mat->specular);
    }

    // faces
    int aFaceCount = aMesh->mNumFaces;
    faceCount += aFaceCount;
    for(int i = 0;i < aFaceCount;i++) {
        aiFace face = aMesh->mFaces[i];
        int index1 = entry->baseVertex + face.mIndices[0];
        int index2 = entry->baseVertex + face.mIndices[1];
        int index3 = entry->baseVertex + face.mIndices[2];
        aIndices.push_back(index1);
        aIndices.push_back(index2);
        aIndices.push_back(index3);
    }
}

int AnimationLoader::findPositionIndex(aiNodeAnim *anim, float animTime)
{
    for(unsigned int i = 0;i < anim->mNumPositionKeys - 1;i++) {
        if(animTime < anim->mPositionKeys[i+1].mTime)
            return i;
    }
    return 0;
}

int AnimationLoader::findRotationIndex(aiNodeAnim* anim, float animTime) {
    for(unsigned int i = 0;i < anim->mNumRotationKeys - 1;i++) {
        if(animTime < anim->mRotationKeys[i+1].mTime)
            return i;
    }
    return 0;
}

int AnimationLoader::findScaleIndex(aiNodeAnim* anim, float animTime) {
    for(unsigned int i = 0;i < anim->mNumScalingKeys-1;i++) {
        if(animTime < anim->mScalingKeys[i+1].mTime)
            return i;
    }
    return 0;
}

void AnimationLoader::calcPosition(aiNodeAnim *anim, float animTime, aiVector3D &position)
{
    // interpolate the position between two key frames
    if(anim->mNumPositionKeys == 1) {
        position=anim->mPositionKeys[0].mValue;
        return;
    }

    // find the key frames
    int startId = findPositionIndex(anim,animTime);
    int endId = startId + 1;
    aiVectorKey startKey = anim->mPositionKeys[startId];
    aiVectorKey endKey = anim->mPositionKeys[endId];
    float dKeyTime = (float)(endKey.mTime-startKey.mTime);
    float dTime = animTime - (float)startKey.mTime;
    // calculate the factor which is used to interpolate
    float factor = dTime/dKeyTime;
    aiVector3D startPosition = startKey.mValue;
    aiVector3D endPosition = endKey.mValue;
    aiVector3D dPosition = endPosition - startPosition;
    //  interpolation
    position = startPosition + factor * dPosition;
}

void AnimationLoader::calcRotation(aiNodeAnim *anim, float animTime, aiQuaternion &rotation)
{
    // interpolate the rotation using Quaternion
    if(anim->mNumRotationKeys == 1) {
        rotation = anim->mRotationKeys[0].mValue;
        return;
    }

    int startId = findRotationIndex(anim,animTime);
    int endId = startId+1;
    aiQuatKey startKey = anim->mRotationKeys[startId];
    aiQuatKey endKey = anim->mRotationKeys[endId];
    float dKeyTime = (float)(endKey.mTime-startKey.mTime);
    float dTime = animTime - (float)startKey.mTime;
    float factor = dTime/dKeyTime;
    aiQuaternion startRotation = startKey.mValue;
    aiQuaternion endRotation = endKey.mValue;
    aiQuaternion::Interpolate(rotation,startRotation,endRotation,factor);
    rotation = rotation.Normalize();
}

void AnimationLoader::calcScale(aiNodeAnim *anim, float animTime, aiVector3D &scale)
{
    if(anim->mNumScalingKeys == 1) {
        scale = anim->mScalingKeys[0].mValue;
        return;
    }

    int startId = findScaleIndex(anim,animTime);
    int endId = startId + 1;
    aiVectorKey startKey = anim->mScalingKeys[startId];
    aiVectorKey endKey = anim->mScalingKeys[endId];
    float dKeyTime = (float)(endKey.mTime-startKey.mTime);
    float dTime = animTime - (float)startKey.mTime;
    float factor = dTime / dKeyTime;
    aiVector3D startScale = startKey.mValue;
    aiVector3D endScale = endKey.mValue;
    aiVector3D dScale = endScale-startScale;
    scale = startScale + factor * dScale;
}

aiNodeAnim *AnimationLoader::findNodeAnim(int animIndex, QString boneName)
{
    // get bone info
    std::map<QString,aiNodeAnim*> channelMap = channelMaps[animIndex];
    if(channelMap.find(boneName) != channelMap.end()) {
        aiNodeAnim* nodeAnim = channelMap[boneName];
        return nodeAnim;
    }
    return nullptr;
}

void AnimationLoader::readNode(int animIndex, float animTime,
                               aiNode *node, const aiMatrix4x4 &parentTransform)
{
    // traverse scene node
    QString boneName(node->mName.data);
    aiMatrix4x4 boneTransform = node->mTransformation;
    aiNodeAnim* boneAnim = findNodeAnim(animIndex,boneName);
    if(boneAnim) {
        aiVector3D scale;
        calcScale(boneAnim,animTime,scale);
        aiMatrix4x4 scaleMat;
        aiMatrix4x4::Scaling(scale,scaleMat);

        aiQuaternion rotation;
        calcRotation(boneAnim,animTime,rotation);
        aiMatrix4x4 rotateMat(rotation.GetMatrix());

        aiVector3D position;
        calcPosition(boneAnim,animTime,position);
        aiMatrix4x4 translateMat;
        aiMatrix4x4::Translation(position,translateMat);

        boneTransform = translateMat * rotateMat * scaleMat;
    }

    // update the bone transformation
    aiMatrix4x4 currentBoneTransform = parentTransform * boneTransform;
    if(boneMap.find(boneName) != boneMap.end()) {
        int boneIndex = boneMap[boneName];
        BoneInfo* boneInfo = boneInfos[boneIndex];
        aiMatrix4x4 aTransform = rootToModelMat*currentBoneTransform*boneInfo->offset;
        boneInfo->transformation = aTransform;
    }

    // tranverse children
    for(unsigned int i = 0;i < node->mNumChildren;i++) {
        aiNode* childNode = node->mChildren[i];
        readNode(animIndex,animTime,childNode,currentBoneTransform);
    }
}

void AnimationLoader::prepareFrameData(int animIndex)
{
    aiMatrix4x4 mat;
    aiAnimation* animation = scene->mAnimations[animIndex];
    AnimFrame* animFrame = animFrames[animIndex];
    for (float tick = 0; tick < animation->mDuration; tick += 0.01) {
        Frame* frame = new Frame(boneCount);
        int currIndex = 0;
        readNode(animIndex, tick, scene->mRootNode, mat);
        for (int bi = 0; bi < boneCount; bi++) {
            QMatrix4x4 tmp;
            tmp.setRow(0,QVector4D(boneInfos[bi]->transformation.a1,
                                      boneInfos[bi]->transformation.a2,
                                      boneInfos[bi]->transformation.a3,
                                      boneInfos[bi]->transformation.a4));
            tmp.setRow(1,QVector4D(boneInfos[bi]->transformation.b1,
                                      boneInfos[bi]->transformation.b2,
                                      boneInfos[bi]->transformation.b3,
                                      boneInfos[bi]->transformation.b4));
            tmp.setRow(2,QVector4D(boneInfos[bi]->transformation.c1,
                                      boneInfos[bi]->transformation.c2,
                                      boneInfos[bi]->transformation.c3,
                                      boneInfos[bi]->transformation.c4));
            tmp.setRow(3,QVector4D(boneInfos[bi]->transformation.d1,
                                      boneInfos[bi]->transformation.d2,
                                      boneInfos[bi]->transformation.d3,
                                      boneInfos[bi]->transformation.d4));
            frame->data[currIndex++] = tmp;
        }
        animFrame->frames.push_back(frame);
    }
}
