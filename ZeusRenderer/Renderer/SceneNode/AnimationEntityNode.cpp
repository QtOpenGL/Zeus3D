//#include "AnimationEntityNode.h"
//#include "../Render/AnimationDrawcall.h"

//AnimationEntityNode::AnimationEntityNode(const QVector3D &boundingSize)
//    :EntityNode(QVector3D(0,0,0),boundingSize)
//{
//    animation = nullptr;
//    uTransformMatrix = new QMatrix4x4();
//    uNormalMatrix = new QMatrix4x4();
//    type = EntityNode::NODE_ANIMATE;
//}

//AnimationEntityNode::~AnimationEntityNode() {}

//void AnimationEntityNode::setAnimation(AnimationLoader *anim)
//{
//    animation = anim;
//    addEntity(new AnimationEntity(animation));
//}

//void AnimationEntityNode::prepareDrawcall()
//{
//    // create a new drawcall
//    if(drawcall) delete drawcall;
//    drawcall = new AnimationDrawcall(animation);
//    drawcall->setSide(singleSide);
//    needCreateDrawcall = false;
//}

//void AnimationEntityNode::updateRenderData(Camera3D *camera, int pass)
//{
//    (void*)camera;
//    (void)pass;
//}

//void AnimationEntityNode::updateDrawcall(int pass)
//{
//    (void)pass;
//    needUpdateDrawcall = false;
//}

//AnimationEntity *AnimationEntityNode::getEntity()
//{
//    if (entitys.size() > 0)
//        return static_cast<AnimationEntity*>(entitys[0]);
//    return nullptr;
//}

//void AnimationEntityNode::animate(int animIndex, long startTime, long currentTime)
//{
//    animation->bonesTransform(animIndex, (float)(currentTime - startTime)*0.001f);
//}

//void AnimationEntityNode::translateNode(float x, float y, float z)
//{
//    // translate this node
//    position = QVector4D(x,y,z,1.0);

//    recursiveTransform(nodeTransform);
//    QMatrix4x4 transform = nodeTransform * entitys[0]->localTransformMatrix;
//    QMatrix4x4 nTransform = entitys[0]->normalMatrix;
//    uTransformMatrix = new QMatrix4x4(transform);
//    uNormalMatrix = new QMatrix4x4(nTransform);

//    // translate this node's bounding box
//    QVector4D final4 = nodeTransform * QVector4D(0, 0, 0, 1);
//    float invw = 1.0 / final4.w();
//    QVector3D final3(final4.x() * invw, final4.y() * invw, final4.z() * invw);
//    boundingBox->update(final3);

//    EntityNode* superior = parent;
//    while (superior) {
//        superior->updateBounding();
//        superior = superior->parent;
//    }
//}

//void AnimationEntityNode::translateNodeCenterAtWorld(float x, float y, float z)
//{
//    // caculate the offset
//    QVector3D beforeWorldCenter = boundingBox->position;
//    QVector3D offset = QVector3D(x, y, z) - beforeWorldCenter;
//    // then translate
//    translateNode(position.x() + offset.x(),
//                  position.y() + offset.y(),
//                  position.z() + offset.z());
//}

//void AnimationEntityNode::rotateNodeEntity(float ax, float ay, float az)
//{
//    AnimationEntity* entity = static_cast<AnimationEntity*>(entitys[0]);
//    entity->setRotation(ax, ay, az);
//    uNormalMatrix = new QMatrix4x4(entity->normalMatrix);
//}
