#ifndef DVERTEX_H
#define DVERTEX_H
#include <QColor>
#include <QVector3D>
/*******************************************************************************
 * DVertex顶点类，包含顶点的位置和颜色数据
 ******************************************************************************/
class DVertex
{
public:
    // Constructors
    Q_DECL_CONSTEXPR DVertex();
    Q_DECL_CONSTEXPR explicit DVertex(const QVector3D &position);
    Q_DECL_CONSTEXPR DVertex(const QVector3D &position, const QVector3D &color);
    DVertex(const QVector3D &position, const QColor &color);

    // Accessors / Mutators
    Q_DECL_CONSTEXPR const QVector3D& position() const;
    Q_DECL_CONSTEXPR const QVector3D& color() const;
    void setPosition(const QVector3D& position);
    void setColor(const QVector3D& color);

    // OpenGL Helpers
    static const int PositionTupleSize = 3;
    static const int ColorTupleSize = 3;
    static Q_DECL_CONSTEXPR int positionOffset();
    static Q_DECL_CONSTEXPR int colorOffset();
    static Q_DECL_CONSTEXPR int stride();

private:
    QVector3D m_position;
    QVector3D m_color;
};

/*******************************************************************************
 * Inline Implementation
 ******************************************************************************/

// Note: Q_MOVABLE_TYPE means it can be memcpy'd.
Q_DECLARE_TYPEINFO(DVertex, Q_MOVABLE_TYPE);

// Constructors
Q_DECL_CONSTEXPR inline DVertex::DVertex() {}
Q_DECL_CONSTEXPR inline DVertex::DVertex(const QVector3D &position) : m_position(position), m_color(1.0f,1.0f,1.0f) {}
Q_DECL_CONSTEXPR inline DVertex::DVertex(const QVector3D &position, const QVector3D &color) : m_position(position), m_color(color) {}
inline DVertex::DVertex(const QVector3D &position, const QColor &color) : m_position(position), m_color(color.redF(), color.greenF(), color.blueF()) {}

// Accessors / Mutators
Q_DECL_CONSTEXPR inline const QVector3D& DVertex::position() const { return m_position; }
Q_DECL_CONSTEXPR inline const QVector3D& DVertex::color() const { return m_color; }
void inline DVertex::setPosition(const QVector3D& position) { m_position = position; }
void inline DVertex::setColor(const QVector3D& color) { m_color = color; }

// OpenGL Helpers
Q_DECL_CONSTEXPR inline int DVertex::positionOffset() { return offsetof(DVertex, m_position); }
Q_DECL_CONSTEXPR inline int DVertex::colorOffset() { return offsetof(DVertex, m_color); }
Q_DECL_CONSTEXPR inline int DVertex::stride() { return sizeof(DVertex); }

#endif // DVERTEX_H
