#ifndef ANIMATIONLOADER_H
#define ANIMATIONLOADER_H
#include <map>
#include <cstring>
#include <assimp/Importer.hpp>
#include <QString>
#include <QMatrix4x4>
/*
 * AnimationLoader.h
 *
 * Describle:
 *      load the skeleton animation from file by Assimp.
 *
 *  Created on: 2018-5-27
 *      Author: Zeus
 */
class QVector2D;
class QVector3D;
class QVector4D;
class aiMesh;
class aiScene;
class aiNodeAnim;
class aiNode;
// represent a mesh
struct Entry {
    aiMesh* mesh;
    int baseVertex;
    int materialIndex;
};

struct BoneInfo {
    aiMatrix4x4 offset;
    aiMatrix4x4 transformation;
};

// a frame
struct Frame {
    int boneCount;
    std::vector<QMatrix4x4> data;
    Frame(int bc) {
        boneCount = bc;
        data.resize(boneCount);
    }
};

// animation frames
struct AnimFrame {
    std::vector<Frame*> frames;
    AnimFrame() {
        frames.clear();
    }
    ~AnimFrame() {
        for (unsigned int i = 0; i < frames.size(); i++)
            delete frames[i];
        frames.clear();
    }
};

class AnimationLoader
{
public:
    // Animation mesh
    int faceCount,vertCount,boneCount;
    std::vector<QVector3D> aVertices;
    std::vector<QVector3D> aNormals;
    std::vector<QVector2D> aTexcoords;
    std::vector<QVector4D> aTextures;
    std::vector<QVector3D> aAmbients;
    std::vector<QVector3D> aDiffuses;
    std::vector<QVector3D> aSpeculars;
    std::vector<int> aIndices;
    std::vector<QVector4D> aBoneids;
    std::vector<QVector4D> aWeights;
    std::map<int,int> materialMap;
    std::vector<QMatrix4x4> boneTransformMats;

    int animCount;
    std::vector<AnimFrame*> animFrames;
    //AnimFrame** animFrames;

    AnimationLoader(const QString &path);
    ~AnimationLoader();
    void bonesTransform(int animIndex,float time);

private:
    // information
    Assimp::Importer *importer;
    const aiScene* scene;
    std::vector<Entry> entrys;
    // a map from it's name to id
    std::map<QString,int> boneMap;
    // store bones
    std::vector<BoneInfo*> boneInfos;
    aiMatrix4x4 rootToModelMat;
    // each animation's channel
    std::vector<std::map<QString,aiNodeAnim*>> channelMaps;

    // loader
    void loadModel();
    void initChannels();
    void loadBones(aiMesh* mesh,int meshIndex);
    void loadMaterials();
    void loadMeshes(Entry* entry);
    void pushWeightToVertex(int vertexid,int boneid,float weight);

    // Get index
    int findPositionIndex(aiNodeAnim* anim,float animTime);
    int findRotationIndex(aiNodeAnim* anim,float animTime);
    int findScaleIndex(aiNodeAnim* anim,float animTime);

    // calc transformation
    void calcPosition(aiNodeAnim* anim,float animTime,aiVector3D& position);
    void calcRotation(aiNodeAnim* anim,float animTime,aiQuaternion& rotation);
    void calcScale(aiNodeAnim* anim,float animTime,aiVector3D& scale);
    aiNodeAnim* findNodeAnim(int animIndex,QString boneName);
    void readNode(int animIndex,float animTime,aiNode* node,
                  const aiMatrix4x4& parentTransform);

    void prepareFrameData(int animIndex);
};

#endif // ANIMATIONLOADER_H
