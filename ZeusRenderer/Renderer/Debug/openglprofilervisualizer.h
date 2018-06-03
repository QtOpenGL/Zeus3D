#ifndef OPENGLPROFILERVISUALIZER_H
#define OPENGLPROFILERVISUALIZER_H

#include <QObject>

class OpenGLWidget;
class QMoveEvent;
class OpenGLFrameResults;
class QOpenGLWidget;
/*******************************************************************************
 * OpenGLProfilerVisualizer，性能检测可视化工具
 ******************************************************************************/
class OpenGLProfilerVisualizerPrivate;
class OpenGLProfilerVisualizer : public QObject
{
    Q_OBJECT
public:

    // Constructors / Destructors
    explicit OpenGLProfilerVisualizer(QObject *parent = 0);
    ~OpenGLProfilerVisualizer();

    // Public Methods
    void setBorder(int left, int right, int top, int bottom);
    void setOffset(float left, float right, float top, float bottom);

    // OpenGL Methods
    void resizeGL(int width, int height);
    void paintGL(QOpenGLWidget *target);

    // Events
    void moveEvent(const QMoveEvent *ev);
    //void setWindowPosition(const QPoint &target);
signals:
    //void resetWindowPosition(const QPoint &target);

public slots:
    void frameResultsAvailable(OpenGLFrameResults const &results);

private:
    OpenGLProfilerVisualizerPrivate *m_private;
};

#endif // OPENGLPROFILERVISUALIZER_H
