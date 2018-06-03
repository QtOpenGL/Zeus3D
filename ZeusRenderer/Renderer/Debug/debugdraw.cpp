#include "DebugDraw.h"
#include <QRectF>
#include <vector>
#include "DVertex.h"
#include "OpenGLBuffer.h"
#include "OpenGLFunctions.h"
#include "OpenGLShaderProgram.h"
#include "OpenglVertexArrayObject.h"
#include "../Interactive/Transform3d.h"

/*******************************************************************************
 * DebugDrawPrivate
 ******************************************************************************/
static std::vector<DVertex> sg_lines;
static std::vector<DVertex> sg_rectangles;

static size_t sg_bufferSize = 0;
static OpenGLBuffer *sg_debugBuffer = Q_NULLPTR;
static OpenGLVertexArrayObject *sg_vertexArrayObject = Q_NULLPTR;
static OpenGLShaderProgram *sg_program = Q_NULLPTR;

static QRectF normalize(const QRectF &rect)
{
    float x = rect.x() * 2.0f - 1.0f;
    float y = rect.y() * -2.0f + 1.0f;
    float w = rect.width() * 2.0f;
    float h = rect.height() * 2.0f;
    return QRectF(x, y, w, h);
}

static size_t requiredSize()
{
    size_t verts = sg_lines.size() + sg_rectangles.size();
    return verts * sizeof(DVertex);
}

/*******************************************************************************
 * DebugDraw
 ******************************************************************************/
void DebugDraw::initialize()
{
    QOpenGLContext *ctx = QOpenGLContext::currentContext();
    OpenGLFunctions f(ctx);

    // Create shaders
    sg_program = new OpenGLShaderProgram();
    sg_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/debug.vert");
    sg_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/debug.frag");
    sg_program->link();

    // Create Vertex Array Object
    sg_vertexArrayObject = new OpenGLVertexArrayObject();
    sg_vertexArrayObject->create();
    sg_vertexArrayObject->bind();

    sg_debugBuffer = new OpenGLBuffer();
    sg_debugBuffer->create();
    sg_debugBuffer->bind();
    sg_debugBuffer->setUsagePattern(OpenGLBuffer::DynamicDraw);
    f.glEnableVertexAttribArray(0);
    f.glEnableVertexAttribArray(1);
    f.glVertexAttribPointer(0, DVertex::PositionTupleSize, GL_FLOAT, GL_FALSE, DVertex::stride(), (void*)DVertex::positionOffset());
    f.glVertexAttribPointer(1, DVertex::ColorTupleSize, GL_FLOAT, GL_FALSE, DVertex::stride(), (void*)DVertex::colorOffset());

    // Release (unbind) all
    sg_vertexArrayObject->release();
}

void DebugDraw::draw()
{
    QOpenGLContext *ctx = QOpenGLContext::currentContext();
    OpenGLFunctions f(ctx);

    // Early-out if there is nothing to draw
    size_t required = requiredSize();
    if (required == 0) return;

    // Prepare OpenGL Buffer data
    if (sg_bufferSize < required)
    {
        sg_debugBuffer->bind();
        sg_debugBuffer->allocate(required);
        sg_debugBuffer->release();
        sg_bufferSize = required;
    }

    // Send data to GPU，通过map写入顶点数据
    {
        size_t idx = 0;
        sg_debugBuffer->bind();
        DVertex *data = static_cast<DVertex*>(sg_debugBuffer->map(OpenGLBuffer::WriteOnly));
        for (auto &v : sg_lines)
        {
            data[idx++] = v;
        }
        for (auto &v : sg_rectangles)
        {
            data[idx++] = v;
        }
        sg_debugBuffer->unmap();
        sg_debugBuffer->release();
    }

    // Draw Data
    sg_vertexArrayObject->bind();
    {
        sg_program->bind();
        f.glDrawArrays(GL_LINES, 0, sg_lines.size());
        f.glDrawArrays(GL_TRIANGLES, sg_lines.size(), sg_rectangles.size());
        sg_program->release();
    }
    sg_vertexArrayObject->release();

    // Clear data
    sg_lines.clear();
    sg_rectangles.clear();
}

void DebugDraw::teardown()
{
    delete sg_debugBuffer;
    delete sg_vertexArrayObject;
    delete sg_program;
}

/*******************************************************************************
 * DebugDraw::Screen
 ******************************************************************************/
void DebugDraw::Screen::drawRect(const QRectF &rect, const QColor &color)
{
    // Move coordinates to OpenGL NDC
    QRectF nRect = normalize(rect);

    // Create key vertex positions
    float x1 = nRect.x();
    float y1 = nRect.y();
    float x2 = nRect.x() + nRect.width();
    float y2 = nRect.y() - nRect.height();

    // Create vertices
    sg_rectangles.push_back(DVertex( QVector3D(x1, y1, 0.0f), color ));
    sg_rectangles.push_back(DVertex( QVector3D(x1, y2, 0.0f), color ));
    sg_rectangles.push_back(DVertex( QVector3D(x2, y1, 0.0f), color ));
    sg_rectangles.push_back(DVertex( QVector3D(x2, y1, 0.0f), color ));
    sg_rectangles.push_back(DVertex( QVector3D(x1, y2, 0.0f), color ));
    sg_rectangles.push_back(DVertex( QVector3D(x2, y2, 0.0f), color ));
}

/*******************************************************************************
 * DebugDraw::World
 ******************************************************************************/
void DebugDraw::World::drawLine(const QVector3D &from, const QVector3D &to, const QColor &color)
{
    // Create vertices
    sg_lines.push_back(DVertex(from, color));
    sg_lines.push_back(DVertex(to, color));
}
