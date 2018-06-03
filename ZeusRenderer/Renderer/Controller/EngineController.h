#ifndef ENGINECONTROLLER_H
#define ENGINECONTROLLER_H
#include "../Scene/Scene.h"
#include "../Interactive/Player.h"
#include "../Render/RenderManager.h"
#include <QElapsedTimer>

/*
 * EngineController.h
 *
 * Describe: manager and control the renderer
 *
 * Created on: 2018-5-29
 *      Author: Zeus
 */
class EngineController
{
public:
    Scene* scene;
    Render* render;
    RenderManager* renderMgr;
    Camera3D *camera;
    Player *player;

    int windowWidth, windowHeight;
    bool willExit;

    EngineController();
    virtual ~EngineController();

    virtual void init();
    virtual void draw();
    virtual void update(long startTime,long currentTime);
    void prepare();
    void resize(int width,int height);
    void setDefaultFramebuffer(GLuint fbo);

    void initScene();
private:
    QElapsedTimer m_timer;
};

#endif // ENGINECONTROLLER_H
