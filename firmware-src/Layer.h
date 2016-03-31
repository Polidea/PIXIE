#ifndef LAYER_H
#define LAYER_H

#include "AlphaAnimation.h"

#define NUM_LEDS 16
#define STATE_STARTING 0
#define STATE_RUNNING 1
#define STATE_FINISHING 2
#define STATE_FINISHED 3

#define COLOR_POSITIVE 0x1F3508
//63A81A
#define COLOR_NEUTRAL 0xc89664
#define COLOR_NEGATIVE 0xf05238
#define COLOR_STARTING 0x002C7F

class Layer {
  public: uint32_t *leds;
  public: int state;

  public: Layer() {
      leds = new uint32_t[NUM_LEDS];
      memset(leds,0,sizeof(uint32_t)*NUM_LEDS);
      state = STATE_STARTING;
    }
    virtual ~Layer(){
      delete[] leds;
    }
  public: virtual void animate() {}
  public: virtual void finish() {}
  public: int getState(){
      return state;
  }
  
    public: static uint32_t lerp(uint32_t c1, uint32_t c2, float amount) {
        uint32_t a1 = (c1 >> 24) & 0xff;
        uint32_t a2 = (c2 >> 24) & 0xff;
        uint32_t r1 = (c1 >> 16) & 0xff;
        uint32_t r2 = (c2 >> 16) & 0xff;
        uint32_t g1 = (c1 >> 8) & 0xff;
        uint32_t g2 = (c2 >> 8) & 0xff;
        uint32_t b1 = c1 & 0xff;
        uint32_t b2 = c2 & 0xff;
        uint32_t a = a1 * (1 - amount) + a2 * amount;
        uint32_t r = r1 * (1 - amount) + r2 * amount;
        uint32_t g = g1 * (1 - amount) + g2 * amount;
        uint32_t b = b1 * (1 - amount) + b2 * amount;
        uint32_t c = (a << 24) | (r << 16) | (g << 8) | b;
        return c;
    }

    public: static float frac(float f) {
        return f - floor(f);
    }

};

#endif