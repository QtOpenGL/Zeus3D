//#include "StaticEntityNode.h"
//#include "../Render/StaticDrawcall.h"

//StaticEntityNode::StaticEntityNode(const QVector3D &position)
//    :EntityNode(position,QVector3D(0,0,0))
//{
//    batch = nullptr;
//    batchVertexCount = 0;
//    batchIndexCount = 0;
//    fullStatic = false;
//    type = EntityNode::NODE_STATIC;
//}

//StaticEntityNode::~StaticEntityNode()
//{
//    if(batch) delete batch;
//    batch = nullptr;
//}

//void StaticEntityNode::addEntity(Entity *entity)
//{
//    batchVertexCount += entity->mesh->vertexCount;
//    batchIndexCount += entity->mesh->indexCount;
//    EntityNode::addEntity(entity);
//}

//Entity *StaticEntityNode::removeEntity(Entity *entity)
//{
//    if(!entity) return NULL;
//    int beforeVertexCount = batchVertexCount;
//    int beforeIndexCount = batchIndexCount;
//    batchVertexCount -= entity->mesh->vertexCount;
//    batchIndexCount -= entity->mesh->indexCount;
//    Entity *entityDel = EntityNode::removeEntity(entity);
//    // Rollback
//    // ???
//    if(!entityDel) {
//        batchVertexCount = beforeVertexCount;
//        batchIndexCount = beforeIndexCount;
//    }
//    return entityDel;
//}

//void StaticEntityNode::addEntitys(std::vector<Entity *> &entityArray, int count)
//{
//    for(int i = 0;i < count;i++)
//        addEntity(entityArray[i]);
//}

//void StaticEntityNode::prepareDrawcall()
//{
//    createBatch();
//    needCreateDrawcall = false;
//}

//void StaticEntityNode::updateRenderData(Camera3D *camera, int pass)
//{
//    if (!batch) return;
//    Q_UNUSED(camera);
//    Q_UNUSED(pass);
//    for (unsigned int i = 0; i < entitys.size(); i++) {
//        Entity* entity = entitys[i];
//        batch->updateMatrices(i, entity->transformMatrix, nullptr);
//    }
//}

//void StaticEntityNode::updateDrawcall(int pass)
//{
//    if (!batch) return;
//    Q_UNUSED(pass);
//    if (!drawcall) {
//        drawcall = new StaticDrawcall(batch);
//        drawcall->setSide(singleSide);
//    } else
//        static_cast<StaticDrawcall*>(drawcall)->updateMatrices(batch);
//    needUpdateDrawcall = false;
//}

//void StaticEntityNode::createBatch()
//{
//    if (batch) delete batch;
//    batch = new Batch();
//    batch->initBatchBuffers(batchVertexCount, batchIndexCount);

//    for(unsigned int i = 0;i < entitys.size();i++) {
//        Entity* entity = entitys[i];
//        batch->pushMeshToBuffers(entity->mesh,
//                                 entity->material,
//                                 fullStatic,
//                                 entity->transformMatrix,
//                                 entity->normalMatrix);
//    }

//    if (drawcall) delete drawcall;
//    drawcall = new StaticDrawcall(batch);
//    drawcall->setSide(singleSide);
//}
