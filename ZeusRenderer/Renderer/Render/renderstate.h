#ifndef RENDERSTATE_H
#define RENDERSTATE_H

#include <QVector3D>
#include "../Shader/ShaderProgram.h"
#include "../Postprocess/Shadow.h"
/*
 * 渲染状态，设定OpenGL状态机
 */

enum CULL_MODE{CULL_NONE = 0,CULL_BACK = 1,CULL_FRONT = 2};
enum TEST_MODE{LESS = 0,LEQUAL = 1,GREATER = 2,GEQUAL = 3};

struct RenderState{
    std::pair<bool,int> cullMode;
    std::pair<bool,int> depthMode;
    bool polygonMode;
    // whether calc light effect or not
    bool lightEffect;
    // rendering sky or not
    bool skyPass;
    // draw pass type
    int pass;
    Shadow* shadow;
    // light ray
    QVector3D light;
    ShaderProgram *shader;
    //instance shaders
    ShaderProgram *shaderIns;

    RenderState() {
        reset();
        light = QVector3D(0, 0, 0);
    }

    RenderState(const RenderState& rhs) {
        cullMode = rhs.cullMode;
        depthMode = rhs.depthMode;
        polygonMode = rhs.polygonMode;
        lightEffect = rhs.lightEffect;
        skyPass = rhs.skyPass;
        pass = rhs.pass;
        shadow = rhs.shadow;
        light = rhs.light;
        shader = rhs.shader;
        shaderIns = rhs.shaderIns;
    }

    void reset() {
        cullMode = std::pair<bool,int>(true,CULL_BACK);
        depthMode = std::pair<bool,int>(true,LEQUAL);
        polygonMode = false;
        lightEffect = true;
        skyPass = false;
        pass = 4;
        shadow = nullptr;
        shader = nullptr;
        shaderIns = nullptr;
    }
};

#endif // RENDERSTATE_H
