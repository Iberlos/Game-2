#pragma once
#include "TweenFuncs.h"

class Tween
{
public:
    Tween();
    ~Tween();

    bool Update(float deltaTime);
    void Setup(TweenFunction* tweenFunction, vec3* var, vec3 startValue, vec3 endValue, double timeLength);

protected:
    TweenFunction * m_TweenFunction;
    vec3* m_Variable;
    vec3 m_Start;
    vec3 m_End;
    double m_ElapsedTime;
    double m_EndTime;
};