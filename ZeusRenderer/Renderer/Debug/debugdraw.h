#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H

class QColor;
class QMatrix4x4;
class QRectF;
class QVector3D;

/*******************************************************************************
 * 性能测试可视化绘制接口
 ******************************************************************************/
class DebugDraw
{
public:
  // Drawing in screen space [0,1] from top-let to bottom-right
  struct Screen
  {
    static void drawRect(const QRectF &rect, const QColor &color);
  };

  // Drawing points within the world. (Unmanipulated)
  struct World
  {
    static void drawLine(const QVector3D &from, const QVector3D &to, const QColor &color);
  };

  // Global states
  static void initialize();
  static void draw();
  static void teardown();
};

#endif // DEBUGDRAW_H
