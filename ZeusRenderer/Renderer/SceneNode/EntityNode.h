//#ifndef ENTITYNODE_H
//#define ENTITYNODE_H
//#include "../Shape/AABB.h"
//#include "../Interactive/Camera3d.h"
//#include "../Entity/Entity.h"
//#include "../Render/DrawCall.h"

///*
// * EntityNode.h
// *
// *  Created on: 2018-5-24
// *      Author: Zeus
// */

//class EntityNode
//{
//public:
//    static std::vector<EntityNode*> nodesToUpdate;
//    static std::vector<EntityNode*> nodesToRemove;

//    // Node type
//    enum NODE_TYPE{NODE_NULL = 0,NODE_STATIC = 1,
//                   NODE_INSTANCE = 2,NODE_ANIMATE = 3};

//    // node attribute
//    QMatrix4x4 *uTransformMatrix;
//    QMatrix4x4 *uNormalMatrix;

//    QVector4D position;
//    QVector3D size;
//    NODE_TYPE type;
//    BoundingBox* boundingBox;

//    // record the transformation of current node.
//    QMatrix4x4 nodeTransform;

//    std::vector<Entity*> entitys;
//    std::vector<BoundingBox*> entitysBBs;

//    // children and parent
//    EntityNode* parent;
//    std::vector<EntityNode*> children;
//    std::vector<BoundingBox*> nodeBBs;

//    DrawCall* drawcall;
//    // some state
//    bool singleSide;
//    bool needUpdateNormal;
//    bool needUpdateDrawcall;
//    bool needCreateDrawcall;
//    bool needUpdateNode;

//    // Constructor/Destructor
//    EntityNode(const QVector3D& position,const QVector3D& size);
//    virtual ~EntityNode();

//    // Check with frustum
//    bool checkInFrustum(Frustum* frustum);

//    // abstract interface
//    virtual void prepareDrawcall() = 0;
//    virtual void updateRenderData(Camera3D* camera, int pass) = 0;
//    virtual void updateDrawcall(int pass) = 0;
//    void updateNode();
//    void pushToUpdate();
//    void updateBounding();

//    // add/remove an entity
//    virtual void addEntity(Entity* entity);
//    virtual Entity* removeEntity(Entity* entity);

//    // attach/detach a child
//    void attachChild(EntityNode* child);
//    EntityNode* detachChild(EntityNode* child);

//    // entity tranformation
//    virtual void translateNode(float x, float y, float z);
//    void translateNodeEntity(int i, float x, float y, float z);
//    void translateNodeEntityCenterAtWorld(int i, float x, float y, float z);
//    void rotateNodeEntity(int i, float ax, float ay, float az);
//    void scaleNodeEntity(int i, float sx, float sy, float sz);

//    // get ancestor
//    EntityNode* getAncestor();

//    // Destroy current entity's children.
//    void clearChildren();

//    // Push current node to the list->nodesToRemove
//    void pushToRemove();

//    // do transformation recursively
//    void recursiveTransform(QMatrix4x4& finalNodeMatrix);

//private:
//    // transfer Object's bounding box from local to world
//    void updateEntityBoundingInNode(Entity* entity);

//    // Update the Node's bounding with objects maybe its children's.
//    void updateBaseNodeBounding();

//    // Update Node's bounding & its children's & children's children...
//    void updateSelfAndDownwardNodesBounding();

//    // Update Node's drawcall & its children's & children's children...
//    void updateSelfAndDownwardNodesDrawcall(bool updateNormal);

//    // Move Node's entity's bounding
//    void moveBaseEntitysBounding(float dx,float dy,float dz);

//    // Just move Node's bounding & its children's & children's children...
//    void moveSelfAndDownwardNodesBounding(float dx,float dy,float dz);
//};

//#endif // ENTITYNODE_H
