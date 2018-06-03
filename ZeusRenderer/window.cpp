#include "window.h"
#include <QMatrix4x4>

#include "Renderer/Debug/DebugDraw.h"
#include "Renderer/Context.h"

#include "Renderer/Interactive/InputManager.h"
#include "Renderer/Interactive/Transform3d.h"

#include "Renderer/Controller/EngineController.h"
/*******************************************************************************
 * WindowPrivate
 ******************************************************************************/
class WindowPrivate
{
public:
    EngineController *engine;
};

/*******************************************************************************
 * Window
 ******************************************************************************/
#define P(c) c &p = *m_private

Window::Window(UpdateBehavior updateBehavior, QWidget *parent) :
    OpenGLWidget(updateBehavior, parent), m_private(new WindowPrivate)
{
    P(WindowPrivate);
    p.engine = nullptr;
}

Window::~Window()
{
    makeCurrent();
    if(m_private->engine)
        delete m_private->engine;
    delete m_private;
    teardownGL();
}

/*******************************************************************************
 * OpenGL Methods
 ******************************************************************************/
void Window::initializeGL()
{
    P(WindowPrivate);
    OpenGLWidget::initializeGL();
    printVersionInformation();

    p.engine = new EngineController();
    p.engine->init();
    p.engine->initScene();
}

void Window::resizeGL(int width, int height)
{
    P(WindowPrivate);
    // it's necessary to set the default fbo.
    p.engine->setDefaultFramebuffer(this->defaultFramebufferObject());
    p.engine->resize(width,height);
    OpenGLWidget::resizeGL(width, height);
}

void Window::paintGL()
{
    P(WindowPrivate);
    //qDebug() << "render frame buffer->" << this->defaultFramebufferObject();
    p.engine->draw();
    //DebugDraw::draw();
    OpenGLWidget::paintGL();
}

void Window::teardownGL()
{
    OpenGLWidget::teardownGL();
}

/*******************************************************************************
 * Events
 ******************************************************************************/
void Window::updateEvent(DUpdateEvent *event)
{
    P(WindowPrivate);
    (void)event;
    // Camera Transformation
    p.engine->player->move();
    p.engine->camera->move();
    p.engine->update(0,0);
}
