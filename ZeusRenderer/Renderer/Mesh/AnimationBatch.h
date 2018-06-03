#ifndef ANIMATIONBATCH_H
#define ANIMATIONBATCH_H
#include <vector>
/*
 * AnimationBatch.h
 *
 *  Created on: 2018-5-27
 *      Author: Zeus
 */
class AnimationLoader;
class AnimationBatch
{
public:
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texcoords;
    std::vector<unsigned char> colors;
    std::vector<unsigned char> boneids;
    std::vector<float> weights;
    std::vector<unsigned int> indices;
    int textureChannel;
    int indexCount, vertexCount, boneCount;
    AnimationLoader* animation;

    AnimationBatch(AnimationLoader* anim);
    ~AnimationBatch();
};

#endif // ANIMATIONBATCH_H
