//#include "InstanceEntityNode.h"
//#include "../Render/InstanceDrawcall.h"
//#include "../Mesh/InstanceBatch.h"

//InstanceEntityNode::InstanceEntityNode(const QVector3D &position)
//    :EntityNode(position,QVector3D(0,0,0))
//{
//    type = EntityNode::NODE_INSTANCE;
//}

//InstanceEntityNode::~InstanceEntityNode() {}

//void InstanceEntityNode::addEntity(Entity *entity)
//{
//    EntityNode::addEntity(entity);
//    // Add to instance table
//    if (InstanceBatch::instanceTable.find(entity->mesh)
//            == InstanceBatch::instanceTable.end())
//        InstanceBatch::instanceTable[entity->mesh] = 1;
//    else
//        InstanceBatch::instanceTable[entity->mesh]++;

//    // Add mid-level mesh
//    if (entity->meshMid) {
//        if (InstanceBatch::instanceTable.find(entity->meshMid)
//                == InstanceBatch::instanceTable.end())
//            InstanceBatch::instanceTable[entity->meshMid] = 1;
//        else
//            InstanceBatch::instanceTable[entity->meshMid]++;
//    }

//    // Add low-level mesh
//    if (entity->meshLow) {
//        if (InstanceBatch::instanceTable.find(entity->meshLow)
//                == InstanceBatch::instanceTable.end())
//            InstanceBatch::instanceTable[entity->meshLow] = 1;
//        else
//            InstanceBatch::instanceTable[entity->meshLow]++;
//    }
//}

//Entity *InstanceEntityNode::removeEntity(Entity *entity)
//{
//    Entity* object2Remove = EntityNode::removeEntity(entity);
//    if (object2Remove) {
//        InstanceBatch::instanceTable[object2Remove->mesh]--;
//        if (object2Remove->meshMid)
//            InstanceBatch::instanceTable[object2Remove->meshMid]--;
//        if (object2Remove->meshLow)
//            InstanceBatch::instanceTable[object2Remove->meshLow]--;
//    }
//    return object2Remove;
//}

//void InstanceEntityNode::addEntitys(std::vector<Entity *> &entityArray, int count)
//{
//    for(int i = 0;i < count;i++)
//        this->addEntity(entityArray[i]);
//}

//void InstanceEntityNode::prepareDrawcall()
//{
//    needCreateDrawcall = false;
//}

//void InstanceEntityNode::updateRenderData(Camera3D *camera, int pass)
//{
//    (void*)camera;
//    (void)pass;
//}

//void InstanceEntityNode::updateDrawcall(int pass)
//{
//    (void)pass;
//    needUpdateDrawcall = false;
//}
