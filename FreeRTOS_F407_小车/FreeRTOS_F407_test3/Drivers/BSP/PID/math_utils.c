#include "./BSP/PID/math_utils.h"

float Normalize(float angle)
{
  float a = fmod(angle, _2PI);
  return a >= 0 ? a : (a + _2PI);
}

// Square root approximation function using
// https://reprap.org/forum/read.php?147,219210
// https://en.wikipedia.org/wiki/Fast_inverse_square_root
float SqrtApprox(float value)
{
  long i;
  float y;

  y = value;
  i = *(long*) &y;
  i = 0x5f375a86 - (i >> 1);
  y = *(float*) &i;

  return value * y;
}
