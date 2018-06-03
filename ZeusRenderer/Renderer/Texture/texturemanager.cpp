#include "TextureManager.h"
#include <QDebug>
#include <QOpenGLTexture>


TextureManager::TextureManager()
{
    arrayId = 0;
}

TextureManager::~TextureManager()
{
    textures.clear();
    imageNames.clear();
    cubeMap.clear();
}

void TextureManager::addToTextureArray(const QString &name, const QString &postfix,
                                       const QString &subdir)
{
    // store index
    textures[name] = imageNames.size();
    imageNames.push_back(subdir+name+postfix);
}

int TextureManager::findTexture(const QString &name)
{
    // get index
    auto it = textures.find(name);
    if(it == textures.end()){
        return -1;
    }
    return it->second;
}

void TextureManager::initTextureArray(const QString &dir)
{
    // load texture arrary
    if (imageNames.size() <= 0) return;

    GlobalContext::contextFunc->glGenTextures(1,&arrayId);
    GlobalContext::contextFunc->glActiveTexture(GL_TEXTURE0);
    GlobalContext::contextFunc->glBindTexture(GL_TEXTURE_2D_ARRAY,arrayId);
    GlobalContext::contextFunc->glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    GlobalContext::contextFunc->glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    QString path = dir + "/";
    QString name("");
    for (unsigned int i = 0; i < imageNames.size(); i++) {
        name = imageNames[i];
        QImage target(path + name);
        if(target.isNull()){
            qDebug() << "Failed to load texture->" << (path+name);
        }
        target = target.mirrored().convertToFormat(QImage::Format_RGBA8888);
        if (i == 0){
            GlobalContext::contextFunc->glTexImage3D(GL_TEXTURE_2D_ARRAY,
                                                     0,
                                                     GL_RGBA,
                                                     target.width(),
                                                     target.height(),
                                                     imageNames.size(),
                                                     0,
                                                     GL_RGBA,
                                                     GL_UNSIGNED_BYTE,
                                                     nullptr);
        }
        GlobalContext::contextFunc->glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
                                                    0, 0, 0,i,
                                                    target.width(),
                                                    target.height(),1,
                                                    GL_RGBA, GL_UNSIGNED_BYTE,
                                                    target.bits());
    }
    GlobalContext::contextFunc->glBindTexture(GL_TEXTURE_2D_ARRAY,0);
}

GLuint TextureManager::loadCubeTexture(const QString &name,const QString &dir,
                                       const std::vector<QString> &cubemaps)
{
    // load cube map
    GLuint id;
    GlobalContext::contextFunc->glGenTextures(1,&id);
    GlobalContext::contextFunc->glActiveTexture(GL_TEXTURE0);
    GlobalContext::contextFunc->glBindTexture(GL_TEXTURE_CUBE_MAP,id);

    GlobalContext::contextFunc->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GlobalContext::contextFunc->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    GlobalContext::contextFunc->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    GlobalContext::contextFunc->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    GlobalContext::contextFunc->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    QString dirctory = dir + "/";
    for(uint x = 0;x < cubemaps.size();++x){
        QImage target(dirctory + cubemaps[x]);
        if(target.isNull()){
            qDebug() << "Failed to load -> " << (dirctory+cubemaps[x]);
        }
        target = target.convertToFormat(QImage::Format_RGBA8888);
        GlobalContext::contextFunc->glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+x,
                                                 0,GL_RGBA,
                                                 target.width(),target.height(),
                                                 0,GL_RGBA,GL_UNSIGNED_BYTE,
                                                 target.bits());
    }
    GlobalContext::contextFunc->glBindTexture(GL_TEXTURE_CUBE_MAP,0);
    cubeMap[name] = id;
    return id;
}

GLuint TextureManager::findCubeTexture(const QString &name)
{
    // get cubemap index
    auto it = cubeMap.find(name);
    if(it == cubeMap.end()){
        return -1;
    }
    return it->second;
}

void TextureManager::releaseTextureArray()
{
    if(arrayId > 0)
        GlobalContext::contextFunc->glDeleteTextures(1,&arrayId);
}
