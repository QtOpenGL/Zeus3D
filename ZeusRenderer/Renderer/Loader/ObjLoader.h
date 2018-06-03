#ifndef OBJLOADER_H
#define OBJLOADER_H
#include "mtlloader.h"
#include <QString>
#include <QVector3D>
#include <QVector2D>
/*
 * ObjLoader.h
 *
 *  Created on: 2018-5-26
 *      Author: Zeus
 */
class ObjLoader
{
public:
    int vCount,faceCount;
    std::vector<QVector3D> vArr;
    std::vector<QVector2D> vtArr;
    std::vector<QVector3D> vnArr;
    std::vector<QVector3D> fvArr;
    std::vector<QVector3D> fnArr;
    std::vector<QVector3D> ftArr;
    // record material the face using
    std::vector<QString> mtArr;
    // material loader
    MtlLoader* mtlLoader;

    ObjLoader(const QString &objPath,const QString &mtlPath);
    ~ObjLoader();

private:
    const QString objFilePath;
    const QString mtlFilePath;
    int vtCount,vnCount;

    int readObjInfo();

};

#endif // OBJLOADER_H
