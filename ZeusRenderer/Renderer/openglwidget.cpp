#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <QApplication>
#include <QOpenGLDebugLogger>
#include <QOpenGLDebugMessage>

#include "OpenGLWidget.h"
#include "Debug/DCommon.h"
#include "Debug/DebugDraw.h"
#include "Debug/DUpdateEvent.h"
#include "Debug/OpenGLFrameResults.h"
#include "Debug/OpenGLFrameTimer.h"
#include "Debug/OpenGLProfiler.h"
#include "Debug/OpenGLProfilerVisualizer.h"
#include "Interactive/InputManager.h"
#include "Context.h"

/*******************************************************************************
 * OpenGLWindowPrivate
 ******************************************************************************/
class OpenGLWidgetPrivate
{
public:
    OpenGLWidgetPrivate(QObject *parent = 0);

    // Rendering Statistics
    OpenGLProfiler m_profiler;
    OpenGLProfilerVisualizer m_profilerVisualizer;
    OpenGLFrameTimer m_frameTimer;
    QOpenGLDebugLogger *m_debugLogger;
    QString m_fps;
};

OpenGLWidgetPrivate::OpenGLWidgetPrivate(QObject *parent) :
    m_profiler(parent), m_profilerVisualizer(parent), m_frameTimer(parent), m_debugLogger(Q_NULLPTR)
  ,m_fps("FPS: ")
{
    // Intentionally Empty
}

/*******************************************************************************
 * OpenGLWindow
 ******************************************************************************/
#define P(c) c &p = *m_private

OpenGLWidget::OpenGLWidget(UpdateBehavior updateBehavior, QWidget *parent) :
    QOpenGLWidget(parent), m_private(new OpenGLWidgetPrivate(this))
{
    this->setUpdateBehavior(updateBehavior);
    P(OpenGLWidgetPrivate);
    connect(&p.m_frameTimer, SIGNAL(timeout(float)), this, SLOT(frameTimeout(float)));
    OpenGLError::pushErrorHandler(this);
}

OpenGLWidget::~OpenGLWidget()
{
    makeCurrent();
    delete m_private;
}

/*******************************************************************************
 * OpenGL Protected Methods
 ******************************************************************************/
void OpenGLWidget::initializeGL()
{
    P(OpenGLWidgetPrivate);

    // Initialize
    initializeOpenGLFunctions();
    GlobalContext::contextFunc = dynamic_cast<QOpenGLFunctions_4_3_Core*>(this);
    DebugDraw::initialize();

    if (p.m_profiler.initialize())
    {
        connect(&p.m_profiler, SIGNAL(frameResultsAvailable(OpenGLFrameResults)),
                &p.m_profilerVisualizer, SLOT(frameResultsAvailable(OpenGLFrameResults)));
    }
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    connect(this, SIGNAL(frameSwapped()), &p.m_frameTimer, SLOT(frameSwapped()));

    // Add a debug messanger if running in debug mode.
#ifdef    GL_DEBUG
    p.m_debugLogger = new QOpenGLDebugLogger(this);
    if (p.m_debugLogger->initialize())
    {
        qDebug() << "GL_DEBUG Debug Logger" << p.m_debugLogger;
        connect(p.m_debugLogger, SIGNAL(messageLogged(QOpenGLDebugMessage)),
                this, SLOT(messageLogged(QOpenGLDebugMessage)));
        p.m_debugLogger->startLogging();
    }
    else
    {
        qDebug() << "GL_DEBUG Debug Logger (NONE)";
    }
#endif // GL_DEBUG

    connect(&p.m_profiler, SIGNAL(frameResultsAvailable(OpenGLFrameResults)),
            this, SLOT(frameResultAvailable(OpenGLFrameResults)));
    QOpenGLWidget::initializeGL();
}

void OpenGLWidget::resizeGL(int width, int height)
{
    P(OpenGLWidgetPrivate);
    p.m_profilerVisualizer.resizeGL(width, height);
    QOpenGLWidget::resizeGL(width, height);
}

void OpenGLWidget::paintGL()
{
    P(OpenGLWidgetPrivate);
    //    draw fps
    //GlobalContext::contextFunc->glDisable(GL_DEPTH_TEST);
    QPainter painter;
    painter.begin(this);
    {
        QPen pen;
        pen.setColor(Qt::red);
        QFont font("Consolas",14);
        font.setBold(true);
        painter.setFont(font);
        painter.setPen(pen);
        painter.drawText(20,30,p.m_fps);
    }
    painter.end();

    //    draw profiler
    p.m_profilerVisualizer.paintGL(this);

    QOpenGLWidget::paintGL();
}

void OpenGLWidget::teardownGL()
{
    DebugDraw::teardown();
}

/*******************************************************************************
 * Event Methods
 ******************************************************************************/
bool OpenGLWidget::event(QEvent *e)
{
    if (e->type() == OpenGLError::type())
    {
        errorEventGL(static_cast<OpenGLError*>(e));
        return true;
    }
    else if (e->type() == DUpdateEvent::type())
    {
        updateEvent(static_cast<DUpdateEvent*>(e));
        return true;
    }
    return QOpenGLWidget::event(e);
}

void OpenGLWidget::errorEventGL(OpenGLError *event)
{
    qFatal(
                "%s::%s => Returned an error!",
                event->callerName(),
                event->functionName()
                );
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
    {
        event->ignore();
    }
    else
    {
        InputManager::registerKeyPress(event->key());
    }
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
    {
        event->ignore();
    }
    else
    {
        InputManager::registerKeyRelease(event->key());
    }
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    InputManager::registerMousePress(event->button());
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    InputManager::registerMouseRelease(event->button());
}

void OpenGLWidget::wheelEvent(QWheelEvent *event)
{
    InputManager::setWheelDelta(event->angleDelta()/15);
}

void OpenGLWidget::moveEvent(QMoveEvent *event)
{
    P(OpenGLWidgetPrivate);
    p.m_profilerVisualizer.moveEvent(event);
    QOpenGLWidget::moveEvent(event);
}

void OpenGLWidget::updateEvent(DUpdateEvent *event)
{
    (void)event;
}

/*******************************************************************************
 * Public Slots
 ******************************************************************************/
void OpenGLWidget::update()
{
    InputManager::update();

    // Update Logic
    {
        // log error message
        DUpdateEvent ev;
        QApplication::sendEvent(this, &ev);
    }

    QOpenGLWidget::update();
}

void OpenGLWidget::frameTimeout(float fps)
{
    P(OpenGLWidgetPrivate);
    p.m_fps = tr("FPS: %1").arg(Debug::round(fps));
}

void OpenGLWidget::messageLogged(const QOpenGLDebugMessage &msg)
{
    QString error;

    // Format based on severity
    switch (msg.severity())
    {
    case QOpenGLDebugMessage::NotificationSeverity:
        error += "--";
        break;
    case QOpenGLDebugMessage::HighSeverity:
        error += "!!";
        break;
    case QOpenGLDebugMessage::MediumSeverity:
        error += "!~";
        break;
    case QOpenGLDebugMessage::LowSeverity:
        error += "~~";
        break;
    case QOpenGLDebugMessage::InvalidSeverity:
    case QOpenGLDebugMessage::AnySeverity:
        error += "??";
        break;
    }

    error += " (";

    // Format based on source
#define CASE(c) case QOpenGLDebugMessage::c: error += #c; break
    switch (msg.source())
    {
    CASE(APISource);
    CASE(WindowSystemSource);
    CASE(ShaderCompilerSource);
    CASE(ThirdPartySource);
    CASE(ApplicationSource);
    CASE(OtherSource);
    CASE(InvalidSource);
    CASE(AnySource);
    }
#undef CASE

    error += " : ";

    // Format based on type
#define CASE(c) case QOpenGLDebugMessage::c: error += #c; break
    switch (msg.type())
    {
    CASE(ErrorType);
    CASE(DeprecatedBehaviorType);
    CASE(UndefinedBehaviorType);
    CASE(PortabilityType);
    CASE(PerformanceType);
    CASE(OtherType);
    CASE(MarkerType);
    CASE(GroupPushType);
    CASE(GroupPopType);
    CASE(AnyType);
    CASE(InvalidType);
    }
#undef CASE

    error += ")";
    if(msg.type() != QOpenGLDebugMessage::OtherType)
        qDebug() << qPrintable(error) << "\n" << qPrintable(msg.message()) << "\n";
}

void OpenGLWidget::frameResultAvailable(const OpenGLFrameResults &result)
{
    (void)result;
}

/*******************************************************************************
 * Public Methods
 ******************************************************************************/
void OpenGLWidget::printVersionInformation()
{
    QString glType;
    QString glVersion;
    QString glProfile;

    // Get Version Information
    glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    // Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
    switch (format().profile())
    {
    CASE(NoProfile);
    CASE(CoreProfile);
    CASE(CompatibilityProfile);
    }
#undef CASE

    // qPrintable() will print our QString w/o quotes around it.
    qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}
