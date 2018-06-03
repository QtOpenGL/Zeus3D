#include "Board.h"

Board::Board()
    :Mesh()
{
    vertexCount = 4;
    indexCount = 6;
    vertices.resize(vertexCount);
    normals.resize(vertexCount);
    texcoords.resize(vertexCount);
    indices.resize(indexCount);
    initFaces();  
}

Board::Board(const Board &rhs)
{
    vertexCount = rhs.vertexCount;
    indexCount = rhs.indexCount;

    vertices.assign(rhs.vertices.begin(),rhs.vertices.end());
    normals.assign(rhs.normals.begin(),rhs.normals.end());
    texcoords.assign(rhs.texcoords.begin(),rhs.texcoords.end());
    materialids.assign(rhs.materialids.begin(),rhs.materialids.end());
    indices.assign(rhs.indices.begin(),rhs.indices.end());
}

void Board::initFaces()
{
    vertices[0] = QVector4D(-1.0,-1.0,0.0,1.0);
    vertices[1] = QVector4D( 1.0,-1.0,0.0,1.0);
    vertices[2] = QVector4D( 1.0, 1.0,0.0,1.0);
    vertices[3] = QVector4D(-1.0, 1.0,0.0,1.0);
    normals[0] = QVector3D(0.0,0.0,1.0);
    normals[1] = QVector3D(0.0,0.0,1.0);
    normals[2] = QVector3D(0.0,0.0,1.0);
    normals[3] = QVector3D(0.0,0.0,1.0);
    texcoords[0] = QVector2D(0.0,0.0);
    texcoords[1] = QVector2D(1.0,0.0);
    texcoords[2] = QVector2D(1.0,1.0);
    texcoords[3] = QVector2D(0.0,1.0);

    indices[0] = 0;indices[1] = 1;indices[2] = 2;
    indices[3] = 0;indices[4] = 2;indices[5] = 3;
}

Board::~Board() {}
