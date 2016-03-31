#include <functional>
#include "Visualiser.h"
#include "StandbyLayer.h"
#include "RainbowLayer.h"

Visualiser::Visualiser(int pin,int leds) :  buildStatus_("NONE", "NONE", 0, 0), prevStatus_("NONE", "NONE", 0, 0) {
    image = new Image(pin,leds);
    image->addLayer(new StandbyLayer(COLOR_STARTING));
}

void Visualiser::setStatus(BuildStatus status) {
    prevStatus_ = buildStatus_;
    buildStatus_ = status;
    
    Serial.println("visualiser update");

    if(buildStatus_==prevStatus_)
        return;
        
    if(image->layers.size()>0){
        image->removeLayer(image->layers[0]);
    }

    switch (buildStatus_.getCurrentResult()){
        case build::SUCCESS:
            image->addLayer(new StandbyLayer(COLOR_POSITIVE));
            break;
        case build::FAILED:
            image->addLayer(new StandbyLayer(COLOR_NEGATIVE));
            break;
        case build::CANCELED:
            image->addLayer(new StandbyLayer(COLOR_NEGATIVE));
            break;
        case build::PENDING:
            break;
        case build::RUNNING:
            image->addLayer(new RainbowLayer());
            break;
        default:
            image->addLayer(new StandbyLayer(COLOR_NEGATIVE));
            break;
    }

    Serial.print("visualiser update sucessful: ");
    Serial.println(buildStatus_.getCurrentResult());
}

void Visualiser::animate() {
    image->draw();
}
