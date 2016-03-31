#ifndef IMAGE_H
#define IMAGE_H

#include "neopixel.h"
#include "Layer.h"
#include <math.h>
#undef min
#undef max
#include <vector>
#include <algorithm>

class Image{
  public: std::vector<Layer*> layers;
  public: Adafruit_NeoPixel *strip;

  public: Image(int pin,int leds){
    strip = new Adafruit_NeoPixel(leds, pin, WS2812B);
    strip->begin();
      strip->show(); // Initialize all pixels to 'off'
  }
  public: ~Image(){
      clear();
      delete strip;
  }
  
  public: void addLayer(Layer *layer){
    layers.push_back(layer);
  }
  
  void clear(){
    for(int i=0;i<layers.size();i++){
      delete layers[i];
    }
    layers.clear();
  }
  
  public: void removeLayer(Layer *layer){
    //Find new end iterator
    std::vector<Layer*>::iterator newEnd = std::remove(layers.begin(), layers.end(), layer);

    //Erase the "removed" elements.
    layers.erase(newEnd, layers.end());
  }
  
  void draw(){
    for (int i = layers.size()-1; i >=0; i--) {
      layers[i]->animate();
      if(layers[i]->getState()==STATE_FINISHED)
        removeLayer(layers[i]);
    }
    
    for (int i = 0; i < NUM_LEDS; i++) {
      uint32_t color = 0;
      for (int l = 0; l < layers.size(); l++) {
        color = Layer::lerp(color,layers[l]->leds[i],((layers[l]->leds[i]>>24)&0xff)/255.0f);
      }
      strip->setPixelColor(i, color);
    }
    strip->show();
  }
};

#endif