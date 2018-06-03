#ifndef DRAWCALL_H
#define DRAWCALL_H
#include <QMatrix4x4>
#include "RenderState.h"
#include "RenderBuffer.h"
#include "../Shader/ShaderProgram.h"
/*
 * drawcall handler
 */

enum VBO_TYPE{
    VERTEX_VBO = 0, NORMAL_VBO = 1, TEXCOORD_VBO = 2, COLOR_VBO = 3,
    OBJECTID_VBO = 4, BONEID_VBO = 4, WEIGHT_VBO = 5, MODEL_MATRIX_VBO = 4
};

enum VBO_LOCATION{
    VERTEX_LOCATION = 0,NORMAL_LOCATION = 1,TEXCOORD_LOCATION = 2,COLOR_LOCATION = 3,
    OBJECTID_LOCATION = 4,BONEIDS_LOCATION = 4,WEIGHTS_LOCATION = 5,MODEL_MATRIX_LOCATION = 4
};

enum DRAWCALL_DC{
    NULL_DC = 0,STATIC_DC = 1,INSTANCE_DC = 2,ANIMATE_DC = 3
};

class DrawCall
{
public:
    QMatrix4x4 uModelMatrix;
    QMatrix4x4 uNormalMatrix;
    int objectCount;
    RenderBuffer* dataBuffer;
    RenderBuffer* simpleBuffer;

    DrawCall();
    virtual ~DrawCall();

    virtual void createSimple() = 0;
    virtual void releaseSimple() = 0;

    // Draw call
    virtual void draw(ShaderProgram* shader,int pass) = 0;

    // Setter / Accessor
    void setSide(bool single);
    bool isSingleSide();
    void setType(int typ);
    int getType();
    void setFullStatic(bool stat);
    bool isFullStatic();

private:
    // should cull face or not
    bool singleSide;
    // dracll type
    DRAWCALL_DC type;
    bool fullStatic;
};

inline void DrawCall::setSide(bool single){singleSide = single;}

inline bool DrawCall::isSingleSide(){return singleSide;}

inline void DrawCall::setType(int typ){type = static_cast<DRAWCALL_DC>(typ);}

inline int DrawCall::getType(){return type;}

inline void DrawCall::setFullStatic(bool stat){fullStatic = stat;}

inline bool DrawCall::isFullStatic(){return fullStatic;}

#endif // DRAWCALL_H
