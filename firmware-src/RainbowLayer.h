#ifndef RAINBOWLAYER_H
#define RAINBOWLAYER_H

#include "Image.h"
#include "Layer.h"

class RainbowLayer: public Layer {
  private: uint32_t colors[7];
  private: int length;
  private: AlphaAnimation *anim;
  private: float offset;
  private: long prevTime;

  public: RainbowLayer() {
      colors[0] = 0xf05238;
      colors[1] = 0xfdb730;
      colors[2] = 0xf7ec36;
      colors[3] = 0xb9d532;
      colors[4] = 0x64cbe6;
      colors[5] = 0x9f53ff;
      colors[6] = 0xf06ea9;
      length = 7;
         anim = new AlphaAnimation(0,1,1000,0);
         offset=0;
         prevTime = millis();
    }
    public: ~RainbowLayer(){
      delete anim;
    }

  public: void animate() {
    if(state==STATE_FINISHED)
      return;
    float animAlpha = 1.0f;
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
    offset += (currTime-prevTime)/50.0f;
    prevTime = currTime;
    while(offset>=NUM_LEDS)
      offset-=NUM_LEDS;
    for (int i = 0; i < NUM_LEDS; i++) {
        float index = i + offset;
        float id = index / NUM_LEDS * length;
        if (id >= length)
          id -= length;
        float id2 = id + 1;
        if (id2 >= length)
          id2 -= length;
        uint32_t color = colors[(int)id];
        uint32_t color2 = colors[(int)id2];
        leds[i] = (lerp(color, color2, frac(id))|((uint32_t)(animAlpha*0xff)<<24));
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