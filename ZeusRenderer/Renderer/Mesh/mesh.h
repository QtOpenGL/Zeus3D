#ifndef MESH_H
#define MESH_H

#include <QVector3D>
#include <QVector2D>
#include <QVector4D>
#include <vector>
/*
 * 网格类，表示一个网格object
 */
class Mesh
{
public:
    int vertexCount,indexCount;
    std::vector<QVector4D> vertices;
    std::vector<QVector3D> normals;
    std::vector<QVector2D> texcoords;
    std::vector<int> materialids;//材质id
    std::vector<int> indices;

    Mesh();
    Mesh(const Mesh& rhs);
    virtual ~Mesh();

private:
    virtual void initFaces() = 0;
};

#endif // MESH_H
