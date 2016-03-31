#ifndef STANDBYLAYER_H
#define STANDBYLAYER_H

#include "Image.h"
#include "Layer.h"

class StandbyLayer: public Layer {
  private: AlphaAnimation *anim;
  private: float offset;
  private: long prevTime;
  private: uint32_t color;

  public: StandbyLayer(uint32_t color){
    anim = new AlphaAnimation(0,1,1000,1000);
    offset = 0;
    prevTime = millis();
    this->color = color;
  }
  public: ~StandbyLayer(){
    delete anim;
  }

  /*public: void animate() {
      if(state==STATE_FINISHED)
      return;
    float animAlpha =1.0f;
    if(state == STATE_STARTING){
      animAlpha = anim->getAlpha();
      if(anim->isFinished()){
        delete anim;
        anim = NULL;
        state = STATE_RUNNING;
      }
    }else if(state == STATE_FINISHING){
      animAlpha = anim->getAlpha();
      if(anim->isFinished()){
        state = STATE_FINISHED;
        return;
      }
    }
    long currTime = millis();
    offset += (currTime-prevTime)/20.0f;
    prevTime = currTime;
    float blend = cos(offset / 180.0f * 3.14f * 2) / 2.0f + 0.5f;
    blend = blend *0.7f+0.3f;
    uint32_t a = animAlpha*blend * 0xff;
    uint32_t alpha  = a<<24;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = ((color&0xffffff)|alpha);
    }
  }*/
  public: void animate() {
    if(state==STATE_FINISHED)
      return;
    float animAlpha =1.0f;
    if(state == STATE_STARTING){
      animAlpha = anim->getAlpha();
      if(anim->isFinished()){
        delete anim;
        anim = NULL;
        state = STATE_RUNNING;
      }
    }else if(state == STATE_FINISHING){
      animAlpha = anim->getAlpha();
      if(anim->isFinished()){
        state = STATE_FINISHED;
        return;
      }
    }
    long currTime = millis();
    offset += (currTime-prevTime)/20.0f;
    prevTime = currTime;

    uint32_t alpha  = 255<<24;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = ((color&0xffffff)|alpha);
    }
  }
  public: void finish(){
    if(state == STATE_FINISHING)
      return;
    anim = new AlphaAnimation(1,0,1000,0);
    state = STATE_FINISHING;
  }
};

#endif