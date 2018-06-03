#ifndef MODEL_H
#define MODEL_H
#include "Mesh.h"
#include "../Loader/ObjLoader.h"
/*
 * Model.h
 *
 *  Created on: 2018-5-26
 *      Author: Zeus
 */
class Model : public Mesh
{
public:
    Model(const QString &obj,const QString &mtl);
    virtual ~Model();
    void loadModel(const QString &obj,const QString &mtl);
private:
    ObjLoader *loader;
    virtual void initFaces();
};

#endif // MODEL_H
