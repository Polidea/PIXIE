#ifndef VISUALISER_H
#define VISUALISER_H

#include "application.h"
#include "BuildStatus.h"
#include "Led.h"
#include "Image.h"

class Visualiser {
    public:
        explicit Visualiser(int pin,int leds);
        ~Visualiser(){
            delete image;
        }
        void setStatus(BuildStatus status);
        BuildStatus getStatus() const;
        void animate();
    private:
    
        Image *image;

        BuildStatus buildStatus_;
        BuildStatus prevStatus_;
};

#endif
