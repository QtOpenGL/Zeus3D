#include "ObjLoader.h"
#include <QTextStream>
#include <QFile>
#include <QDebug>

ObjLoader::ObjLoader(const QString &objPath, const QString &mtlPath)
    :objFilePath(objPath),mtlFilePath(mtlPath)
{
    vCount=0;
    vnCount=0;
    vtCount=0;
    faceCount=0;
    readObjInfo();
    mtlLoader = new MtlLoader(mtlFilePath);
}

ObjLoader::~ObjLoader()
{
    if(mtlLoader) delete mtlLoader;
    mtlLoader = nullptr;
}

int ObjLoader::readObjInfo()
{
    QFile infile(objFilePath);
    if(!infile.open(QFile::ReadOnly)){
        qDebug() << "Could not open the file->" << objFilePath;
    }
    QTextStream in(&infile);
    QString sline,mtl("");
    QStringList words,nums;
    while(!in.atEnd()){
        sline = in.readLine();
        sline = sline.simplified();
        words = sline.split(" ");
        if(words.isEmpty())continue;
        if(words.at(0) == "f"){ // face
            QVector3D tmp[3];
            for(int x = 0;x < 3;++x){
                sline = words.at(x+1);
                nums = sline.split("/");
                tmp[x] = QVector3D(nums.at(0).toFloat(),
                                   nums.at(1).toFloat(),
                                   nums.at(2).toFloat());
            }
            fvArr.push_back(QVector3D(tmp[0].x(),tmp[1].x(),tmp[2].x()));
            ftArr.push_back(QVector3D(tmp[0].y(),tmp[1].y(),tmp[2].y()));
            fnArr.push_back(QVector3D(tmp[0].z(),tmp[1].z(),tmp[2].z()));
            mtArr.push_back(mtl);
        }
        else if(words.at(0) == "usemtl"){ // material name
            mtl = words.at(1);
        }
        else if(words.at(0) == "v"){ // vertex
            vArr.push_back(QVector3D(words.at(1).toFloat(),
                                     words.at(2).toFloat(),
                                     words.at(3).toFloat()));
        }
        else if(words.at(0) == "vn"){ // normal
            vnArr.push_back(QVector3D(words.at(1).toFloat(),
                                      words.at(2).toFloat(),
                                      words.at(3).toFloat()));
        }
        else if(words.at(0) == "vt"){ // texcoord
            vtArr.push_back(QVector2D(words.at(1).toFloat(),
                                      words.at(2).toFloat()));
        }
    }
    infile.close();

    // cache these sizes
    vCount = vArr.size();
    vtCount = vtArr.size();
    vnCount = vnArr.size();
    faceCount = fvArr.size();
}
