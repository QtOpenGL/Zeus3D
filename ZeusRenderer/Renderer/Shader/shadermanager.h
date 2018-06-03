#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#include "ShaderProgram.h"
/*
 * 着色器程序资源管理器
 */
class ShaderManager
{
public:
    ShaderManager();

    ~ShaderManager();

    ShaderProgram* addShader(const QString name,const QString comp);

    ShaderProgram* addShader(const QString name,const QString vert,const QString frag,const QString geom = "");

    ShaderProgram* findShader(const QString name);

private:
    std::map<QString,ShaderProgram*> shaders;
};

#endif // SHADERMANAGER_H
