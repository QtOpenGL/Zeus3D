#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLWidget>

class QEvent;
class OpenGLError;
class OpenGLFrameResults;
class QOpenGLDebugMessage;
class QKeyEvent;
class QMouseEvent;
class QMoveEvent;
class QWheelEvent;
class QTouchEvent;
class DUpdateEvent;

class OpenGLWidgetPrivate;
class OpenGLWidget : public QOpenGLWidget,
        public QOpenGLFunctions_4_3_Core
{
    Q_OBJECT

public:
    // Constructors / Destructors
    OpenGLWidget(UpdateBehavior updateBehavior = NoPartialUpdate, QWidget *parent = nullptr);
    ~OpenGLWidget();

    // Public Methods
    void printVersionInformation();

protected:

    // OpenGL Protected Methods
    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void paintGL();
    virtual void teardownGL();

    // Event Methods
    virtual bool event(QEvent *event);
    virtual void errorEventGL(OpenGLError *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void moveEvent(QMoveEvent *event);
    virtual void updateEvent(DUpdateEvent *event);

public slots:
    void update();
    void frameTimeout(float fps);
    void messageLogged(const QOpenGLDebugMessage &msg);
    void frameResultAvailable(const OpenGLFrameResults &result);

private:
    OpenGLWidgetPrivate *m_private;
};


#endif // OPENGLWIDGET_H
