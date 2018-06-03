//#include "TerrainEntityNode.h"
//#include "../Mesh/Terrain.h"
//#include "../Entity/StaticEntity.h"
//#include "AnimationEntityNode.h"
//#define STEP_SIZE 1
//TerrainEntityNode::TerrainEntityNode(const QVector3D &position)
//    :StaticEntityNode(position)
//{
//    triangles.clear();
//    blockCount = 0;
//    lineSize = 0;
//    offset = QVector3D(0, 0, 0);
//    offsize = QVector3D(1, 1, 1);
//}

//TerrainEntityNode::~TerrainEntityNode()
//{
//    for (uint i = 0; i < triangles.size(); i++)
//        delete triangles[i];
//    triangles.clear();
//}

//void TerrainEntityNode::prepareTriangles()
//{
//    // get triangles
//    StaticEntity* object = static_cast<StaticEntity*>(entitys[0]);
//    offsize = QVector3D(object->sizex,object->sizey,object->sizez);
//    offset = QVector3D(position.x() + object->position.x(),
//                       position.y() + object->position.y(),
//                       position.z() + object->position.z()
//                       );

//    Terrain* mesh =static_cast<Terrain*>(entitys[0]->mesh);
//    blockCount = mesh->blockCount;
//    lineSize = sqrt(blockCount);
//    // ???
//    std::vector<QVector4D>& vertices = mesh->vertices;
//    for (int i = 0; i < lineSize; ++i) {
//        for (int j = 0; j < lineSize; ++j) {
//            QVector4D a = vertices[i*(lineSize + 1) + j];
//            QVector4D b = vertices[i*(lineSize + 1) + (j + 1)];
//            QVector4D c = vertices[(i + 1)*(lineSize + 1) + j];
//            QVector4D d = vertices[(i + 1)*(lineSize + 1) + (j + 1)];

//            QVector3D pa = offset + offsize*QVector3D(a.x(),a.y(),a.z());
//            QVector3D pb = offset + offsize*QVector3D(b.x(),b.y(),b.z());
//            QVector3D pc = offset + offsize*QVector3D(c.x(),c.y(),c.z());
//            QVector3D pd = offset + offsize*QVector3D(d.x(),d.y(),d.z());

//            Triangle* t1 = new Triangle(pa, pb, pc);
//            Triangle* t2 = new Triangle(pb, pd, pc);
//            triangles.push_back(t1);
//            triangles.push_back(t2);
//        }
//    }
//}

//float TerrainEntityNode::cauculateY(float x, float z)
//{
//    // calculate height on the ground
//    float offx = x - offset.x();
//    float offz = z - offset.z();
//    offx /= offsize.x();
//    offz /= offsize.z();
//    float invStepSize = 1.0 / STEP_SIZE;
//    int ix = static_cast<int>(offx*invStepSize);
//    int iz = static_cast<int>(offz*invStepSize);
//    if (ix < lineSize && iz < lineSize) {
//        int ib = iz*lineSize + ix;
//        int ita = ib * 2, itb = ib * 2 + 1;

//        if (ita < 0 || itb < 0 ||
//                (uint)ita >= triangles.size() ||
//                (uint)itb >= triangles.size())
//            return 0.0;

//        Triangle* ta = triangles[ita];
//        Triangle* tb = triangles[itb];
//        QVector2D p2d = QVector2D(x, z);
//        if (ta->pointIsIn(p2d))
//            return ta->caculateY(x, z);
//        else
//            return tb->caculateY(x, z);
//    }
//    return 0.0;
//}

//void TerrainEntityNode::standEntitysOnGround(EntityNode *node,
//                                             TerrainEntityNode *terrain)
//{
//    // calculate the position that entity should stand on.
//    if (node->children.size() <= 0) {
//        if (node->type == EntityNode::NODE_ANIMATE) {
//            AnimationEntityNode* animNode = static_cast<AnimationEntityNode*>(node);
//            QVector3D worldCenter = animNode->boundingBox->position;
//            worldCenter.setY(terrain->cauculateY(worldCenter.x(), worldCenter.z())
//                    + static_cast<AABB*>(animNode->boundingBox)->size.y() * 0.5);
//            animNode->translateNodeCenterAtWorld(worldCenter.x(),
//                                                 worldCenter.y(),
//                                                 worldCenter.z());
//        }
//        else {
//            for (uint i = 0; i < node->entitys.size(); i++) {
//                StaticEntity* obj = static_cast<StaticEntity*>(node->entitys[i]);
//                QVector3D worldCenter = obj->bounding->position;
//                worldCenter.setY(terrain->cauculateY(worldCenter.x(), worldCenter.z())
//                                 + static_cast<AABB*>(obj->bounding)->size.y() * 0.499);
//                node->translateNodeEntityCenterAtWorld(i,
//                                                       worldCenter.x(),
//                                                       worldCenter.y(),
//                                                       worldCenter.z());
//            }
//        }
//    }
//    else if (node->children.size() > 0) {
//        // recursively
//        for (uint c = 0; c < node->children.size(); c++)
//            standEntitysOnGround(node->children[c], terrain);
//    }
//}
