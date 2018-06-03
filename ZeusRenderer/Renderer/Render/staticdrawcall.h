#ifndef STATICDRAWCALL_H
#define STATICDRAWCALL_H
#include "DrawCall.h"
#include "../Mesh/Batch.h"

/*
 * Static objects' draw call
 */
class StaticDrawcall : public DrawCall
{
public:

    Batch* batch;

    // Constructor / Destructor
    StaticDrawcall();
    StaticDrawcall(Batch* batch);
    virtual ~StaticDrawcall();

    virtual void createSimple();
    virtual void releaseSimple();
    virtual void draw(ShaderProgram* shader,int pass);
    void updateMatrices(Batch* batch);

private:
    int vertexCount,indexCount;
    bool indexed;
};

#endif // STATICDRAWCALL_H
