//#ifndef STATICENTITYNODE_H
//#define STATICENTITYNODE_H
//#include "EntityNode.h"
//#include "../Mesh/batch.h"

//class StaticEntityNode : public EntityNode
//{
//public:
//    Batch* batch;
//    int batchVertexCount,batchIndexCount;
//    bool fullStatic;

//    StaticEntityNode(const QVector3D& position);
//    virtual ~StaticEntityNode();

//    virtual void addEntity(Entity* entity);
//    virtual Entity* removeEntity(Entity* entity);
//    void addEntitys(std::vector<Entity*> &entityArray,int count);

//    // drawcall
//    virtual void prepareDrawcall();
//    virtual void updateRenderData(Camera3D* camera, int pass);
//    virtual void updateDrawcall(int pass);

//private:
//    void createBatch();
//};

//#endif // STATICENTITYNODE_H
