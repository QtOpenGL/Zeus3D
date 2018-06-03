#include "Mtlloader.h"
#include <QFile>
#include <QTextStream>
#include "../Scene/AssetManager.h"
#include <QDebug>

MtlLoader::MtlLoader(const QString &mtlPath)
{
    mtlFilePath=mtlPath;
    mtlCount=0;
    readMtlInfo();
}

MtlLoader::~MtlLoader()
{
    objMtls.clear();
}

void MtlLoader::readMtlInfo()
{
    QFile infile(mtlFilePath);
    if(!infile.open(QFile::ReadOnly)){
        qDebug() << "Could not open the file->" << mtlFilePath;
    }
    QTextStream in(&infile);
    QString sline, name, texture;
    Material* mtl = nullptr;
    QVector3D color;

    // Begin to read line by line
    while(!in.atEnd()){
        sline = in.readLine();
        sline = sline.simplified();
        QStringList words = sline.split(" ");
        if(words.isEmpty())continue; // skip empty line

        // now read the info according the first word of the line
        if(words.at(0) == QObject::tr("newmtl")){// A new mtl
            ++mtlCount;
            name = words.at(1);
            mtl = new Material(name);
            mtl->texture = QVector4D(-1,-1,-1,-1);
            objMtls[name] = MaterialManager::materials->add(mtl);
        }
        else if(words.at(0) == QObject::tr("map_Kd")){
            texture = words.at(1);
            if(mtl){
                TextureManager *textures = AssetManager::assetManager->textures;
                if(textures->findTexture(texture) < 0)
                    textures->addToTextureArray(texture,"");
                mtl->texture.setX(textures->findTexture(texture));
            }
        }
        else if(words.at(0) == QObject::tr("map_Ka")){
            texture = words.at(1);
            if(mtl){

            }
        }
        else if(words.at(0) == QObject::tr("Kd")){ // diffuse
            float red,green,blue;
            red = words.at(1).toFloat();
            green = words.at(2).toFloat();
            blue = words.at(3).toFloat();
            color = QVector3D(red,green,blue);
            if(mtl) {
                mtl->diffuse = color;
            }
        }
        else if(words.at(0) == QObject::tr("Ka")){ // ambient
            float red,green,blue;
            red = words.at(1).toFloat();
            green = words.at(2).toFloat();
            blue = words.at(3).toFloat();
            color = QVector3D(red,green,blue);
            if(mtl) {
                mtl->ambient = color;
            }
        }
        else if(words.at(0) == QObject::tr("Ks")){ // specular
            float red,green,blue;
            red = words.at(1).toFloat();
            green = words.at(2).toFloat();
            blue = words.at(3).toFloat();
            color = QVector3D(red,green,blue);
            if(mtl) {
                mtl->specular = color;
            }
        }
    }
    infile.close();
}
