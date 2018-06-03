#include "ShaderProgram.h"
#include "../debug/OpenGLShaderProgram.h"

ShaderProgram::ShaderProgram(const QString &comp)
{
    program = new OpenGLShaderProgram;
    program->addShaderFromSourceFile(QOpenGLShader::Compute,comp);
    program->link();
}

ShaderProgram::ShaderProgram(const QString &vert, const QString &frag, const QString &geom)
{
    program = new OpenGLShaderProgram;
    program->addShaderFromSourceFile(QOpenGLShader::Vertex,vert);
    program->addShaderFromSourceFile(QOpenGLShader::Fragment,frag);
    if(!geom.isEmpty()){
        program->addShaderFromSourceFile(QOpenGLShader::Geometry,geom);
    }
    program->link();
}

ShaderProgram::~ShaderProgram()
{
    if(program)delete program;
    program = nullptr;
    uniformLocation.clear();
}

void ShaderProgram::use()
{
    if(this == nullptr || program == nullptr){
        qDebug() << "a nullptr shader program";
    }
    program->bind();
}

void ShaderProgram::release()
{
    program->release();
}

void ShaderProgram::addUniform(const QString &target)
{
    // Add uniform location that haven't been added before.
    GLuint location = program->uniformLocation(target);
    if(static_cast<int>(location) != INVALID_LOCATION){
        uniformLocation.insert(std::pair<QString,uint>(target,location));
    }
}

void ShaderProgram::setInt(const QString &param, int value)
{
    int location = findUniformLocations(param);
    if (location == INVALID_LOCATION) {
        addUniform(param);
        location = findUniformLocations(param);
    }
    if (location != INVALID_LOCATION)program->setUniformValue(location,value);
    else qDebug() << "INVALID_LOCATION->"  << param;
}

void ShaderProgram::setFloat(const QString &param, float value)
{
    int location = findUniformLocations(param);
    if (location == INVALID_LOCATION) {
        addUniform(param);
        location = findUniformLocations(param);
    }
    if (location != INVALID_LOCATION)program->setUniformValue(location,value);
}

void ShaderProgram::setVector2(const QString &param, float x, float y)
{
    setVector2(param,QVector2D(x,y));
}

void ShaderProgram::setVector2(const QString &param, QVector2D value)
{
    int location = findUniformLocations(param);
    if (location == INVALID_LOCATION) {
        addUniform(param);
        location = findUniformLocations(param);
    }
    if (location != INVALID_LOCATION)program->setUniformValue(location,value);
}

void ShaderProgram::setVector3(const QString &param, float x, float y, float z)
{
    setVector3(param,QVector3D(x,y,z));
}

void ShaderProgram::setVector3(const QString &param, QVector3D value)
{
    int location = findUniformLocations(param);
    if (location == INVALID_LOCATION) {
        addUniform(param);
        location = findUniformLocations(param);
    }
    if (location != INVALID_LOCATION)program->setUniformValue(location,value);
    //else qDebug() << "INVALID_LOCATION->"  << param;
}

void ShaderProgram::setVector4(const QString &param, float x, float y, float z, float w)
{
    setVector4(param,QVector4D(x,y,z,w));
}

void ShaderProgram::setVector4(const QString &param, QVector4D value)
{
    int location = findUniformLocations(param);
    if (location == INVALID_LOCATION) {
        addUniform(param);
        location = findUniformLocations(param);
    }
    if (location != INVALID_LOCATION)program->setUniformValue(location,value);
}

void ShaderProgram::setMatrix2(const QString &param, QMatrix2x2 value)
{
    int location = findUniformLocations(param);
    if (location == INVALID_LOCATION) {
        addUniform(param);
        location = findUniformLocations(param);
    }
    if (location != INVALID_LOCATION)program->setUniformValue(location,value);
}

void ShaderProgram::setMatrix3(const QString &param, QMatrix3x3 value)
{
    int location = findUniformLocations(param);
    if (location == INVALID_LOCATION) {
        addUniform(param);
        location = findUniformLocations(param);
    }
    if (location != INVALID_LOCATION)program->setUniformValue(location,value);
}

void ShaderProgram::setMatrix4(const QString &param, QMatrix4x4 value)
{
    int location = findUniformLocations(param);
    if (location == INVALID_LOCATION) {
        addUniform(param);
        location = findUniformLocations(param);
    }
    if (location != INVALID_LOCATION)program->setUniformValue(location,value);
    else qDebug() << "INVALID_LOCATION->"  << param;
}

void ShaderProgram::setMatrix4(const QString &param, int count,
                               std::vector<QMatrix4x4> &value)
{
    int location = findUniformLocations(param);
    if (location == INVALID_LOCATION) {
        addUniform(param);
        location = findUniformLocations(param);
    }
    if(location != INVALID_LOCATION)
        program->setUniformValueArray(location,&value[0],count);
    else qDebug() << "INVALID_LOCATION->" << param;
}

int ShaderProgram::findUniformLocations(const QString &target)
{
    auto it = uniformLocation.find(target);
    if(it != uniformLocation.end())
        return it->second;
    return INVALID_LOCATION;
}
