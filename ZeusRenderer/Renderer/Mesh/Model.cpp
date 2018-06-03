#include "Model.h"
#include <QDebug>

Model::Model(const QString &obj, const QString &mtl)
{
    vertexCount = 0;
    indexCount = 0;
    loadModel(obj,mtl);
}

Model::~Model() {
    if(loader)delete loader;
    loader = nullptr;
}

void Model::loadModel(const QString &obj, const QString &mtl)
{
    loader = new ObjLoader(obj,mtl);
    initFaces();
    delete loader;
    loader = nullptr;
}

void Model::initFaces()
{
    vertexCount = loader->vCount;
    indexCount = loader->faceCount*3;
    vertices.resize(indexCount);
    for(int i = 0;i < vertexCount;++i){
        vertices[i].setX(loader->vArr[i].x());
        vertices[i].setY(loader->vArr[i].y());
        vertices[i].setZ(loader->vArr[i].z());
        vertices[i].setW(1.0);
    }

    normals.resize(indexCount);
    texcoords.resize(indexCount);
    materialids.resize(indexCount);
    indices.resize(indexCount);

    // duplicate detection
    std::map<int,bool> texcoordMap;
    int dupIndex = vertexCount;
    // get the vertice according the

    for(int i = 0;i < loader->faceCount;++i){
        // get corresponding index
        QVector3D verIndex = QVector3D(loader->fvArr[i].x()-1,
                                       loader->fvArr[i].y()-1,
                                       loader->fvArr[i].z()-1);
        QVector3D norIndex = QVector3D(loader->fnArr[i].x()-1,
                                       loader->fnArr[i].y()-1,
                                       loader->fnArr[i].z()-1);
        QVector3D texIndex = QVector3D(loader->ftArr[i].x()-1,
                                       loader->ftArr[i].y()-1,
                                       loader->ftArr[i].z()-1);
        // get corresponding value
        QVector3D nor1 = QVector3D(loader->vnArr[norIndex.x()]);
        QVector3D nor2 = QVector3D(loader->vnArr[norIndex.y()]);
        QVector3D nor3 = QVector3D(loader->vnArr[norIndex.z()]);
        QVector2D tex1 = QVector2D(loader->vtArr[texIndex.x()]);
        QVector2D tex2 = QVector2D(loader->vtArr[texIndex.y()]);
        QVector2D tex3 = QVector2D(loader->vtArr[texIndex.z()]);
        // Duplicate vertex if texcoord not the same
        if (texcoordMap.find(verIndex.x()) != texcoordMap.end()
                && texcoords[verIndex.x()] != tex1) {
            int newIndex = dupIndex++;
            vertices[newIndex] = vertices[verIndex.x()];
            verIndex.setX(newIndex);
        }
        if (texcoordMap.find(verIndex.y()) != texcoordMap.end()
                && texcoords[verIndex.y()] != tex2) {
            int newIndex = dupIndex++;
            vertices[newIndex] = vertices[verIndex.y()];
            verIndex.setY(newIndex);
        }
        if (texcoordMap.find(verIndex.z()) != texcoordMap.end()
                && texcoords[verIndex.z()] != tex3) {
            int newIndex = dupIndex++;
            vertices[newIndex] = vertices[verIndex.z()];
            verIndex.setZ(newIndex);
        }

        normals[verIndex.x()] = nor1;
        normals[verIndex.y()] = nor2;
        normals[verIndex.z()] = nor3;
        texcoords[verIndex.x()] = tex1;
        texcoords[verIndex.y()] = tex2;
        texcoords[verIndex.z()] = tex3;
        texcoordMap[verIndex.x()] = true;
        texcoordMap[verIndex.y()] = true;
        texcoordMap[verIndex.z()] = true;

        indices[i * 3] = verIndex.x();
        indices[i * 3 + 1] = verIndex.y();
        indices[i * 3 + 2] = verIndex.z();

        // get material index
        int mid = loader->mtlLoader->objMtls[loader->mtArr[i]];
        materialids[verIndex.x()] = mid;
        materialids[verIndex.y()] = mid;
        materialids[verIndex.z()] = mid;
    }
    vertexCount = dupIndex;
}
