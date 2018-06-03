#ifndef DCOMMON_H
#define DCOMMON_H
#include <cmath>
/*******************************************************************************
 * 一些常见的操作->数字字符判断、数字字符转换、四舍五入
 ******************************************************************************/
namespace Debug
{

inline static bool isAlpha(int c)
{
  return (c >= 'A' && c <= 'z');
}

inline static bool isNumeric(int c)
{
  return (c >= '0' && c <= '9') || c == '-';
}

inline static int ctoi(int c)
{
  return c - '0';
}

inline static float ctof(int c)
{
  return static_cast<float>(ctoi(c));
}

//四舍五入
inline static int round(float f)
{
  return std::floor(f + 0.5f);
}

//四舍五入
inline static int round(double d)
{
  return std::floor(d + 0.5);
}

}
#endif // DCOMMON_H
