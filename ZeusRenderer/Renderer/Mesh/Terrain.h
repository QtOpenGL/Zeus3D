#ifndef TERRAIN_H
#define TERRAIN_H
#include "Mesh.h"
#include <QImage>
/*
 * Terrain.h
 *
 *  Created on: 2018-5-25
 *      Author: Zeus
 */
constexpr float MAX_PIXEL_COLOR = 16777216.0f;

class Terrain : public Mesh
{
public:
    int blockCount;

    Terrain(const QString &fileName, int maxH, int s = 512);
    virtual ~Terrain();

private:
    int width,height,size,maxHeight;
    QImage heightMap;

    float getHeight(int px,int pz);
    QVector3D caculateNormal(int x, int y);
    QVector3D getTerrainNormal(float x,float y,float z);
    virtual void initFaces();
};

#endif // TERRAIN_H
