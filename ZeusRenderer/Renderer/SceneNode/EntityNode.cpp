//#include "EntityNode.h"

//std::vector<EntityNode*> EntityNode::nodesToUpdate;
//std::vector<EntityNode*> EntityNode::nodesToRemove;

//EntityNode::EntityNode(const QVector3D &position, const QVector3D &size)
//{
//    // set initial properties
//    this->position = position;
//    this->position.setW(1);
//    this->size = size;

//    boundingBox = new AABB(position,size.x(),size.y(),size.z());
//    entitys.clear();
//    entitysBBs.clear();

//    drawcall = nullptr;
//    singleSide = false;
//    needUpdateDrawcall = false;
//    needCreateDrawcall = false;
//    needUpdateNormal = false;
//    needUpdateNode = false;

//    uTransformMatrix = nullptr;
//    uNormalMatrix = nullptr;

//    parent = nullptr;
//    children.clear();
//    nodeBBs.clear();

//    type = NODE_TYPE::NODE_NULL;
//}

//EntityNode::~EntityNode()
//{
//    // release dynamic memory
//    if (uTransformMatrix) delete uTransformMatrix;
//    uTransformMatrix = nullptr;
//    if (uNormalMatrix) delete uNormalMatrix;
//    uNormalMatrix = nullptr;

//    if(boundingBox) delete boundingBox;
//    boundingBox = nullptr;

//    entitysBBs.clear();
//    for (uint i = 0; i < entitys.size(); i++)
//        delete entitys[i];
//    entitys.clear();

//    if(drawcall) delete drawcall;
//    drawcall = nullptr;

//    nodeBBs.clear();
//    clearChildren();
//}

//void EntityNode::clearChildren()
//{
//    // Destroy current entity's children.
//    // Before we destroy a child, we also need to destroy child's children.
//    // Hence we need call child's clearChildren() function recursively.
//    for(unsigned int i = 0;i < children.size();i++) {
//        EntityNode* child = children[i];
//        child->clearChildren();
//        delete child;
//    }
//    children.clear();
//}

//bool EntityNode::checkInFrustum(Frustum *frustum)
//{
//    // visible detection
//    if (boundingBox)
//        return boundingBox->checkWithFrustum(frustum, false, false);
//    return true;
//}

//void EntityNode::updateEntityBoundingInNode(Entity *entity)
//{
//    // transfer Object's bounding box from local to world
//    BoundingBox* objectBB = entity->bounding;
//    if (objectBB) {
//        QMatrix4x4 nodeMat;
//        nodeMat.setToIdentity();
//        recursiveTransform(nodeMat);
//        QVector4D localBB4(entity->localBoundPosition.x(),
//                           entity->localBoundPosition.y(),
//                           entity->localBoundPosition.z(),
//                           1.0);
//        // transfered from local to world by nodeMat
//        QVector4D bb4 = nodeMat * localBB4;
//        objectBB->update(QVector3D(bb4.x() / bb4.w(),
//                                   bb4.y() / bb4.w(),
//                                   bb4.z() / bb4.w()));
//    }
//}

//void EntityNode::addEntity(Entity *entity)
//{
//    // add it to the entity list
//    entitys.push_back(entity);
//    // calculate bounding box
//    entity->caculateLocalAABB(false, false);
//    BoundingBox* objectBB = entity->bounding;
//    if (objectBB) {
//        updateEntityBoundingInNode(entity);
//        entitysBBs.push_back(objectBB);

//        // merge these boundingBox
//        boundingBox->merge(entitysBBs);

//        // update entity's bounding box from bottom to top
//        EntityNode* superior = parent;
//        while (superior) {
//            superior->updateBounding();
//            superior = superior->parent;
//        }
//    }
//    // now it's time to create a new drawcall
//    needCreateDrawcall = true;

//    // push to update
//    pushToUpdate();
//}

//Entity *EntityNode::removeEntity(Entity *entity)
//{
//    // remove the target eneity.
//    // General speaking, the follwing operations are
//    // the oppisite of addEntity.
//    std::vector<Entity*>::iterator it;
//    std::vector<BoundingBox*>::iterator itbb;
//    // find entity in entitys list
//    for (it = entitys.begin(); it != entitys.end(); ++it) {
//        // if we find the target
//        if ((*it) == entity) {
//            // remove it from entitys list
//            entitys.erase(it);

//            // meanwhile we also need to remove it's corresponding aabb box.
//            for (itbb = entitysBBs.begin(); itbb != entitysBBs.end(); ++itbb) {
//                if ((*itbb) == entity->bounding) {
//                    entitysBBs.erase(itbb);
//                    break;
//                }
//            }
//            // after that, we recaculate the box
//            boundingBox->merge(entitysBBs);

//            // update it from bottom to top
//            EntityNode* superior = parent;
//            while (superior) {
//                superior->updateBounding();
//                superior = superior->parent;
//            }

//            // it's time to create a new drawcall
//            needCreateDrawcall = true;
//            pushToUpdate();

//            return entity;
//        }
//    }
//    return nullptr;
//}

//void EntityNode::updateBaseNodeBounding()
//{
//    // Update the Node's bounding with objects maybe its children's.

//    // transfer each node's box to the world space.
//    for(unsigned int i = 0;i < entitys.size();i++)
//        updateEntityBoundingInNode(entitys[i]);

//    // in the world space, we merge bounding box
//    if (entitys.size() > 0) {
//        if (entitysBBs.size() > 0)
//            boundingBox->merge(entitysBBs);
//        else if (entitysBBs.size() <= 0) {
//            // Base Node and without object boundings
//            QMatrix4x4 nodeTransform;
//            nodeTransform.setToIdentity();
//            recursiveTransform(nodeTransform);
//            // update the bounding box
//            QVector4D af = nodeTransform * QVector4D(0, 0, 0, 1);
//            boundingBox->update(QVector3D(af));
//        }
//    }

//    // do it recursively
//    for(unsigned int n = 0;n < children.size();n++)
//        children[n]->updateBaseNodeBounding();
//}

//void EntityNode::updateSelfAndDownwardNodesBounding()
//{
//    // Update Node's bounding & its children's & children's children...
//    nodeBBs.clear();
//    for(unsigned int n = 0;n < children.size();n++) {
//        // dfs algorithm to traverse
//        EntityNode* child = children[n];
//        child->updateSelfAndDownwardNodesBounding();
//        AABB* childAABB = static_cast<AABB*>(child->boundingBox);
//        // If it's a valid aabb-box, we push it to nodeBBS.
//        if(childAABB && (childAABB->size.x() > 0
//                         ||childAABB->size.y() > 0
//                         ||childAABB->size.z() > 0))
//            nodeBBs.push_back(child->boundingBox);
//    }
//    // Now that if nodeBBs is not empty, we merge to a new aabb-box.
//    if (nodeBBs.size() > 0)
//        boundingBox->merge(nodeBBs);
//}

//void EntityNode::moveBaseEntitysBounding(float dx, float dy, float dz)
//{
//    // Move Node's entity's bounding
//    QVector3D offset(dx, dy, dz);
//    for (uint i = 0; i < entitys.size(); i++) {
//        BoundingBox* objectBB = entitys[i]->bounding;
//        if (objectBB)
//            objectBB->update(objectBB->position + offset);
//    }
//    // also the same as their children
//    for (uint n = 0; n < children.size(); n++)
//        children[n]->moveBaseEntitysBounding(dx, dy, dz);
//}

//void EntityNode::moveSelfAndDownwardNodesBounding(float dx, float dy, float dz)
//{
//    // Just move Node's bounding & its children's & children's children...
//    if (boundingBox) {
//        QVector3D offset(dx, dy, dz);
//        boundingBox->update(boundingBox->position + offset);
//    }
//    for (uint n = 0; n < children.size(); n++)
//        children[n]->moveSelfAndDownwardNodesBounding(dx, dy, dz);
//}

//void EntityNode::updateBounding()
//{
//    // Update current Node's bounding.
//    // Not include their children.
//    nodeBBs.clear();
//    for (unsigned int n = 0; n < children.size(); n++) {
//        EntityNode* child = children[n];
//        AABB* childAABB = static_cast<AABB*>(child->boundingBox);
//        if (childAABB && (childAABB->size.x() > 0
//                          || childAABB->size.y() > 0
//                          || childAABB->size.z() > 0))
//            nodeBBs.push_back(child->boundingBox);
//    }
//    if (nodeBBs.size() > 0)
//        boundingBox->merge(nodeBBs);
//}

//void EntityNode::updateSelfAndDownwardNodesDrawcall(bool updateNormal)
//{
//    // Update Node's drawcall & its children's & children's children...
//    if (entitys.size() > 0) {
//        needUpdateNormal = updateNormal;
//        needUpdateDrawcall = true;
//        pushToUpdate();
//    }

//    for (unsigned int i = 0; i < children.size(); i++)
//        children[i]->updateSelfAndDownwardNodesDrawcall(updateNormal);
//}

//EntityNode *EntityNode::getAncestor()
//{
//    // Find ancestor of this Node
//    EntityNode* root = this;
//    EntityNode* superior = parent;
//    while (superior) {
//        root = superior;
//        superior = superior->parent;
//    }
//    return root;
//}

//void EntityNode::attachChild(EntityNode *child)
//{
//    // attach child, so current node is it's parent.
//    children.push_back(child);
//    child->parent = this;

//    child->updateBaseNodeBounding();
//    child->updateSelfAndDownwardNodesBounding();

//    // update parent's bounding
//    EntityNode* superior = this;
//    while (superior) {
//        superior->updateBounding();
//        superior = superior->parent;
//    }

//    updateSelfAndDownwardNodesDrawcall(false);
//}

//EntityNode *EntityNode::detachChild(EntityNode *child)
//{
//    // detach a child node from children set.
//    std::vector<EntityNode*>::iterator it;
//    for(it = children.begin();it != children.end();it++) {
//        // Here we got it.
//        if((*it) == child) {
//            child->parent = nullptr;
//            children.erase(it);

//            // update parents' boundings
//            EntityNode* superior = this;
//            while (superior) {
//                superior->updateBounding();
//                superior = superior->parent;
//            }

//            // If child node is a instanced-type node
//            /*if (child->type == NODE_TYPE::TYPE_INSTANCE) {
//                for (uint i = 0; i < child->entitys.size(); i++) {
//                    Entity* entity = child->entitys[i];
//                    Instance::instanceTable[entity->mesh]--;
//                    if (entity->meshMid)
//                        Instance::instanceTable[entity->meshMid]--;
//                    if (entity->meshLow)
//                        Instance::instanceTable[entity->meshLow]--;
//                }
//            }*/
//            return child;
//        }
//    }
//    return nullptr;
//}

//void EntityNode::translateNode(float x, float y, float z)
//{
//    float dx = x - position.x();
//    float dy = y - position.y();
//    float dz = z - position.z();

//    position = QVector4D(x,y,z,position.w());

//    // move base  and downward entitys' bounding
//    moveBaseEntitysBounding(dx, dy, dz);
//    moveSelfAndDownwardNodesBounding(dx, dy, dz);

//    // update parents' bounding
//    EntityNode* superior = parent;
//    while (superior) {
//        superior->updateBounding();
//        superior = superior->parent;
//    }

//    // update drawcalls
//    updateSelfAndDownwardNodesDrawcall(false);
//}

//void EntityNode::translateNodeEntity(int i, float x, float y, float z)
//{
//    Entity* entity = entitys[i];
//    entity->setPosition(x, y, z);
//    entity->caculateLocalAABB(false, false);

//    // update and merge
//    updateEntityBoundingInNode(entity);
//    boundingBox->merge(entitysBBs);

//    // update parent's bounding
//    EntityNode* superior = parent;
//    while (superior) {
//        superior->updateBounding();
//        superior = superior->parent;
//    }

//    needUpdateNormal = false;
//    needUpdateDrawcall = true;
//    pushToUpdate();
//}

//void EntityNode::translateNodeEntityCenterAtWorld(int i, float x, float y, float z)
//{
//    Entity* entity = entitys[i];
//    // get it's bounding's position
//    QVector3D worldCenter = entity->bounding->position;

//    // calculate the offset
//    QVector3D offset = QVector3D(x, y, z) - worldCenter;
//    QVector3D localPosition = entity->position;
//    // then move it by offset
//    translateNodeEntity(i,
//                        localPosition.x() + offset.x(),
//                        localPosition.y() + offset.y(),
//                        localPosition.z() + offset.z());
//}

//void EntityNode::rotateNodeEntity(int i, float ax, float ay, float az)
//{
//    Entity* entity = entitys[i];
//    entity->setRotation(ax,ay,az);
//    entity->caculateLocalAABB(false, false);

//    updateEntityBoundingInNode(entity);
//    boundingBox->merge(entitysBBs);

//    EntityNode* superior = parent;
//    while (superior) {
//        superior->updateBounding();
//        superior = superior->parent;
//    }

//    // Rotation would change the normal of entity,
//    // hence it's time to update it.
//    needUpdateNormal = true;
//    needUpdateDrawcall = true;
//    pushToUpdate();
//}


//void EntityNode::scaleNodeEntity(int i, float sx, float sy, float sz)
//{
//    Entity* entity = entitys[i];
//    entity->setSize(sx, sy, sz);
//    entity->caculateLocalAABB(false, false);

//    updateEntityBoundingInNode(entity);
//    boundingBox->merge(entitysBBs);

//    EntityNode* superior = parent;
//    while (superior) {
//        superior->updateBounding();
//        superior = superior->parent;
//    }
//    // If it's a uniform scaling,
//    // there is no need to update normal.
//    if (sx == sy && sy == sz)
//        needUpdateNormal = false;
//    else
//        needUpdateNormal = true;
//    needUpdateDrawcall = true;
//    pushToUpdate();
//}

//void EntityNode::pushToUpdate()
//{
//    // Push it to the list -> nodesToUpdate.
//    if (!needUpdateNode) {
//        EntityNode::nodesToUpdate.push_back(this);
//        needUpdateNode = true;
//    }
//}

//void EntityNode::updateNode()
//{
//    if (type != NODE_TYPE::NODE_ANIMATE) {
//        recursiveTransform(nodeTransform);
//        for (unsigned int i = 0; i < entitys.size(); i++) {
//            Entity* entity = entitys[i];
//            entity->transformMatrix = nodeTransform * entity->localTransformMatrix;
//        }
//    }
//    needUpdateNode = false;
//}


//void EntityNode::pushToRemove()
//{
//    EntityNode::nodesToRemove.push_back(this);
//}

//void EntityNode::recursiveTransform(QMatrix4x4 &finalNodeMatrix)
//{
//    if(parent) {
//        QMatrix4x4 parentTransform,currentTransform;
//        parent->recursiveTransform(parentTransform);
//        currentTransform.setToIdentity();
//        currentTransform.translate(position.x(),position.y(),position.z());
//        finalNodeMatrix = parentTransform*currentTransform;
//    } else{
//        finalNodeMatrix.setToIdentity();
//        finalNodeMatrix.translate(position.x(),position.y(),position.z());
//    }
//}

