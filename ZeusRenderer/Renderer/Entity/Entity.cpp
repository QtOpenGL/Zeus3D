#include "Entity.h"

Entity::Entity()
{
    // Set initial properties
    position = QVector3D(0, 0, 0);
    size = QVector3D(1.0, 1.0, 1.0);
    modelMatrix.setToIdentity();
    normalMatrix.setToIdentity();

    mesh = nullptr;
    meshMid = nullptr;
    meshLow = nullptr;
    bounding = nullptr;
    drawcall = nullptr;
    material = -1;
    localBoundPosition = QVector3D(0,0,0);
}

Entity::Entity(const Entity &rhs)
{
    // Copu constructor
    position = rhs.position;
    size = rhs.size;
    mesh = rhs.mesh;
    meshMid = rhs.meshMid;
    meshLow = rhs.meshLow;
    drawcall = rhs.drawcall;
    material = rhs.material;
    modelMatrix = rhs.modelMatrix;
    normalMatrix = rhs.normalMatrix;
    localBoundPosition = rhs.localBoundPosition;
}

Entity::~Entity()
{
    if (bounding) delete bounding;
    bounding = nullptr;
}

void Entity::caculateLocalAABB(bool looseWidth, bool looseAll)
{
    // Caculate AABB box by ourselves
    if (!mesh) return;
    int vertexCount = mesh->vertexCount;
    if (vertexCount <= 0) return;

    // Get the mesh vertice
    std::vector<QVector4D> vertices(mesh->vertices);

    // Get the first vertex and tranform it to the world space
    QVector4D firstVert = modelMatrix * vertices[0];
    // Perspective division
    float minx = firstVert.x() / firstVert.w();
    float miny = firstVert.y() / firstVert.w();
    float minz = firstVert.z() / firstVert.w();
    float maxx = minx;
    float maxy = miny;
    float maxz = minz;
    // Begin to calc
    for (int i = 1; i < vertexCount; i++) {
        // transform it
        QVector4D worldVert = modelMatrix * vertices[i];
        QVector3D vertexCur(worldVert.x() / worldVert.w(),
                            worldVert.y() / worldVert.w(),
                            worldVert.z() / worldVert.w());
        // replace if need
        minx = minx > vertexCur.x() ? vertexCur.x() : minx;
        miny = miny > vertexCur.y() ? vertexCur.y() : miny;
        minz = minz > vertexCur.z() ? vertexCur.z() : minz;
        maxx = maxx < vertexCur.x() ? vertexCur.x() : maxx;
        maxy = maxy < vertexCur.y() ? vertexCur.y() : maxy;
        maxz = maxz < vertexCur.z() ? vertexCur.z() : maxz;
    }

    // Next we create the aabb box or update it
    QVector3D minVertex(minx, miny, minz), maxVertex(maxx, maxy, maxz);
    if (!bounding)
        bounding = new AABB(minVertex, maxVertex);
    else
        static_cast<AABB*>(bounding)->update(minVertex, maxVertex);

    // Update the width and length
    if (looseWidth) {
        AABB* aabb = static_cast<AABB*>(bounding);
        float maxWidth = aabb->size.x() > aabb->size.z() ?
                    aabb->size.x() : aabb->size.z();
        aabb->update(maxWidth, aabb->size.y(), maxWidth);
    }

    // Update the width, height and length
    if (looseAll) {
        AABB* aabb = static_cast<AABB*>(bounding);
        float maxSide = aabb->size.x();
        maxSide = maxSide < aabb->size.y() ? aabb->size.y() : maxSide;
        maxSide = maxSide < aabb->size.z() ? aabb->size.z() : maxSide;
        aabb->update(maxSide, maxSide, maxSide);
    }

    localBoundPosition = bounding->position;
}

void Entity::updateLocalMatrices()
{
    // Update the corresponding matrix
    vertexTransform();
    normalTransform();
}

void Entity::bindMaterial(int mid)
{
    material = mid;
}

bool Entity::checkInFrustum(Frustum *frustum)
{
    if (bounding)
        return bounding->checkWithFrustum(frustum, false, false, true);
    return true;
}
