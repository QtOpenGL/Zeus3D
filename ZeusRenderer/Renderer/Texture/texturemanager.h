#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <vector>
#include <map>
#include <QString>
#include "../Context.h"
/*
 * Texture manager
 */
enum Texture_Type{TEXTURE_2D,TEXTURE_CUBE};
class QOpenGLTexture;
class TextureManager
{
public:
    GLuint arrayId;

    TextureManager();
    ~TextureManager();

    void addToTextureArray(const QString &name,const QString &postfix,
                           const QString &subdir = "");

    int findTexture(const QString &name);

    void initTextureArray(const QString& dir);

    GLuint loadCubeTexture(const QString &name,
                           const QString &dir,
                           const std::vector<QString> &cuebmaps);

    GLuint findCubeTexture(const QString &name);

private:
    std::map<QString,int> textures;
    std::map<QString,GLuint> cubeMap;
    std::vector<QString> imageNames;

    void releaseTextureArray();
};

#endif // TEXTUREMANAGER_H
