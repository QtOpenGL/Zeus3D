//#ifndef ANIMATIONENTITYNODE_H
//#define ANIMATIONENTITYNODE_H
//#include "EntityNode.h"
//#include "../Entity/AnimationEntity.h"
///*
// * AnimationEntityNode.h
// *
// *  Created on: 2018-5-28
// *      Author: Zeus
// */

//class AnimationEntityNode : public EntityNode
//{
//public:
//    AnimationEntityNode(const QVector3D& boundingSize);
//    virtual ~AnimationEntityNode();
//    virtual void prepareDrawcall();
//    virtual void updateRenderData(Camera3D* camera, int pass);
//    virtual void updateDrawcall(int pass);
//    void setAnimation(AnimationLoader* anim);
//    AnimationEntity* getEntity();
//    // do animation here
//    void animate(int animIndex,long startTime,long currentTime);
//    virtual void translateNode(float x, float y, float z);
//    void translateNodeCenterAtWorld(float x, float y, float z);
//    void rotateNodeEntity(float ax, float ay, float az);

//private:
//    AnimationLoader *animation;
//};

//#endif // ANIMATIONENTITYNODE_H
