#include "Terrain.h"
#include <QDebug>

Terrain::Terrain(const QString &fileName, int maxH, int s)
    :size(s), maxHeight(maxH)
{
    if(!heightMap.load(fileName)){
        qDebug() << "Failed to load Height map->" << fileName;
        return;
    }
    width = heightMap.width();
    height = heightMap.height();
    blockCount = (width - 1) * (height - 1);
    vertexCount = width * height;
    indexCount = 6*blockCount;

    vertices.resize(vertexCount);
    normals.resize(vertexCount);
    texcoords.resize(vertexCount);
    indices.resize(indexCount);

    qDebug() << width << "," << height;
    initFaces();
}

Terrain::~Terrain() {}

float Terrain::getHeight(int px, int pz)
{
    //return 0.0f;
    if(px >= width || pz >= height || px < 0 || pz < 0)
        return 0.0f;
    QColor pixel = heightMap.pixel(px,pz);
//    int color = ((pixel.alpha() << 24)
//                 |(pixel.red() << 16)
//                 |(pixel.green() << 8)
//                 |(pixel.blue() << 0)
//                 );
//    float height = static_cast<float>(color);
   // height += MAX_PIXEL_COLOR/2.0f;
   // height += MAX_PIXEL_COLOR/2.0f;
    float target = pixel.red()*pixel.green()*pixel.blue();
    target += MAX_PIXEL_COLOR/2.0f;
    target /= MAX_PIXEL_COLOR/2.0f;
    target *= maxHeight;
    return target;
}

QVector3D Terrain::caculateNormal(int x, int y)
{
    float heightL = getHeight(x - 1, y);
    float heightR = getHeight(x + 1, y);
    float heightD = getHeight(x, y - 1);
    float heightU = getHeight(x, y + 1);
    QVector3D result(heightL - heightR, 2.0f, heightD - heightU);
    result.normalize();
    return result;
}

void Terrain::initFaces()
{
    int currentVertex = 0, currentIndex = 0;

    for(int i = 0;i < height;++i){
        for(int j = 0;j < width;++j){
            vertices[currentVertex] =
                    QVector4D((float)j/(width-1)*(float)size,
                              getHeight(j,i),
                              (float)i/(height-1)*(float)size,
                              1.0f
                              );
            texcoords[currentVertex] =
                    QVector2D((float)j/(float)(width-1),
                              (float)i/(float)(height-1)
                              );
//            qDebug() << texcoords[currentVertex].x()
//                     << ","
//                     << texcoords[currentVertex].y();
            normals[currentVertex] =
                    caculateNormal(j,i);
            ++ currentVertex;
        }
    }

    for(int gz = 0;gz < height - 1; ++gz){
        for(int gx = 0;gx < width - 1;++gx){
            uint topLeft = (gz*width) + gx;
            uint topRight = topLeft + 1;
            uint bottomLeft = ((gz+1)*width) + gx;
            uint bottomRight = bottomLeft + 1;
            indices[currentIndex++] = topLeft;
            indices[currentIndex++] = bottomLeft;
            indices[currentIndex++] = topRight;
            indices[currentIndex++] = topRight;
            indices[currentIndex++] = bottomLeft;
            indices[currentIndex++] = bottomRight;
        }
    }
}
