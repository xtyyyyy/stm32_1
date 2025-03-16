#ifndef __PID_H
#define __PID_H

//#pragma once

#include "./BSP/PID/math_utils.h"
#include <stdio.h>
#include "./SYSTEM/sys/sys.h"

typedef struct
{
  float error;       /**< Error feedback. */
  float errorLast;   /**< Error feedback history values. */
  float feedforward; /**< Feedforward item. */
  float integral;    /**< Integral item. */
  float saturation;  /**< Saturation value of the integral item. */
  float differ;      /**< Differential item. */
  float kp;          /**< Gained of the proportional item. */
  float ki;          /**< Gained of the integral item, multiplied by control period. */
  float kd;          /**< Gained of the differential item. */
  float ns;          /**< Filter parameter of the differential item. */
  float ka;          /**< Gained of the saturation item. */
  float limit;  /**< The upper limit value of the pid comp output. */
} PID_LocTypeDef;

float PID_Loc(float SetValue, float ActualValue, PID_LocTypeDef* PID);
#endif // __PID_H
