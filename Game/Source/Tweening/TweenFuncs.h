#ifndef __TweenFuncs_H__
#define __TweenFuncs_H__

float TweenFunc_Linear(float startvalue, float valuerange, double timeElapsed, double totaltime);
float TweenFunc_SineEaseIn(float startvalue, float valuerange, double timeElapsed, double totaltime);
float TweenFunc_SineEaseOut(float startvalue, float valuerange, double timeElapsed, double totaltime);
float TweenFunc_SineEaseInOut(float startvalue, float valuerange, double timeElapsed, double totaltime);
float TweenFunc_BounceEaseIn(float startvalue, float valuerange, double timeElapsed, double totaltime);
float TweenFunc_BounceEaseOut(float startvalue, float valuerange, double timeElapsed, double totaltime);
float TweenFunc_BounceEaseInOut(float startvalue, float valuerange, double timeElapsed, double totaltime);
float TweenFunc_ElasticEaseIn(float startvalue, float valuerange, double timeElapsed, double totaltime);
float TweenFunc_ElasticEaseOut(float startvalue, float valuerange, double timeElapsed, double totaltime);
float TweenFunc_ElasticEaseInOut(float startvalue, float valuerange, double timeElapsed, double totaltime);

typedef float (TweenFunction)(float startvalue, float valuerange, double timeElapsed, double totaltime);

const unsigned int NUM_TWEENS = 10;
#endif //__TweenFuncs_H__
