#ifndef WINDOW_H
#define WINDOW_H

#include "Renderer/openglwidget.h"
//#include "assimp/Importer.hpp"

class DUpdateEvent;

class WindowPrivate;
class Window : public OpenGLWidget
{
  Q_OBJECT

public:
  Window(UpdateBehavior updateBehavior = NoPartialUpdate, QWidget *parent = 0);
  ~Window();

protected:

  // OpenGL Methods
  void initializeGL()override;
  void resizeGL(int width, int height)override;
  void paintGL()override;
  void teardownGL()override;

  // Events
  void updateEvent(DUpdateEvent *event)override;
private:
  WindowPrivate *m_private;
};

#endif // WINDOW_H
