#include "./BSP/PID/PID.h"

float PID_Loc(float SetValue, float ActualValue, PID_LocTypeDef* pidHandle)
{
  pidHandle->error = SetValue - ActualValue;

  /* Proportional Item */
  float p = pidHandle->kp * pidHandle->error;

  /* Integral Item */
  float i = pidHandle->ki * (pidHandle->error - pidHandle->ka * pidHandle->saturation) + pidHandle->integral;
  i = CONSTRAINT(i, MIN(0.f, -pidHandle->limit), MAX(0.f, pidHandle->limit));
  pidHandle->integral = i;

  /* Differential Item */
  float d = pidHandle->kd * pidHandle->ns * (pidHandle->error - pidHandle->errorLast) - \
            pidHandle->differ * (pidHandle->ns - 1.0f);

  pidHandle->errorLast = pidHandle->error;
  pidHandle->differ = d;

  /* Output value update and saturation value calculation */
  float val = p + i + d + pidHandle->feedforward;
  float out = CONSTRAINT(val, -pidHandle->limit, pidHandle->limit);
  pidHandle->saturation = val - out;

  return out;
}

