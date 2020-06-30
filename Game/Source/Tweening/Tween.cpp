#include "GamePCH.h"
#include "Tween.h"

Tween::Tween()
{

}

Tween::~Tween()
{

}

bool Tween::Update(float deltaTime)
{
    m_ElapsedTime += deltaTime;
    bool isOver = false;
    if (m_ElapsedTime > m_EndTime)
    {
        m_ElapsedTime = m_EndTime;
        isOver = true;
    }

    for (int i = 0; i < 3; i++)
    {
        (*m_Variable)[i] = m_TweenFunction(m_Start[i], m_End[i] - m_Start[i], m_ElapsedTime, m_EndTime);
    }

    return isOver;
}

void Tween::Setup(TweenFunction* tweenFunction, vec3* vector, vec3 startValue, vec3 endValue, double timeLength)
{
    m_TweenFunction = tweenFunction;
    m_Variable = vector;
    m_Start = startValue;
    m_End = endValue;
    m_ElapsedTime = 0.0f;
    m_EndTime = timeLength;
}
