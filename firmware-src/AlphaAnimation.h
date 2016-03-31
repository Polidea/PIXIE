#ifndef ALPHAANIMATION_H
#define ALPHAANIMATION_H

#include <math.h>
#undef min
#undef max
#include <algorithm>

class AlphaAnimation{
  public: float a1,a2;
  public: long duration,delay;
  public: long startTime;
  public: boolean finished;
  
  public: AlphaAnimation(float a1,float a2,long duration,long delay){
    this->a1 = a1;
    this->a2 = a2;
    this->duration = duration;
    this->startTime = millis();
    this->delay = delay;
    finished = false;
  }
  
  public: float getAlpha(){
    long currTime = millis();
    float t = (float)(currTime-this->startTime-delay)/duration;
    finished = (t>=1);
    t = std::max(0.0f,std::min(t,1.0f));
    return a2*t+a1*(1-t);
  }
  public: boolean isFinished(){
    return finished;
  }
};

#endif