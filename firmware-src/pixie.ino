// This #include statement was automatically added by the Particle IDE.
#include "Project.h"

// This #include statement was automatically added by the Particle IDE.
#include "jsmnSpark.h"

// This #include statement was automatically added by the Particle IDE.
#include "BuildMonitor.h"

// This #include statement was automatically added by the Particle IDE.
#include "Visualiser.h"

// This #include statement was automatically added by the Particle IDE.
#include "rest_client.h"

// This #include statement was automatically added by the Particle IDE.
#include "Led.h"

// This #include statement was automatically added by the Particle IDE.
#include "BuildStatus.h"

// This #include statement was automatically added by the Particle IDE.
#include "AlphaAnimation.h"

// This #include statement was automatically added by the Particle IDE.
#include "RainbowLayer.h"

// This #include statement was automatically added by the Particle IDE.
#include "StandbyLayer.h"

// This #include statement was automatically added by the Particle IDE.
#include "Image.h"

// This #include statement was automatically added by the Particle IDE.
#include "Layer.h"

// This #include statement was automatically added by the Particle IDE.
#include "neopixel.h"

#include <time.h>
#include "jsmnSpark.h"
#include "Led.h"
#include "BuildMonitor.h"
#include "Visualiser.h"


BuildMonitor monitor;
std::map<int, Visualiser*> visualisers;
unsigned long lastConfigUpdate = millis();
unsigned long lastTimeSync = millis();
unsigned long lastStatusUpdate = millis();
bool shouldUpdate;


int setPort1Url(String url) {
    if(monitor.projects.count(D0) != 0) {
          delete monitor.projects[D0];
          monitor.projects.erase(D0);
    }
    monitor.projects[D0] = new Project(url, 16);
    shouldUpdate = true;
    updateConfig();
    return 1;
}

int setPort2Url(String url) {
    if(monitor.projects.count(D1) != 0) {
          delete monitor.projects[D1];
          monitor.projects.erase(D1);
    }
    monitor.projects[D1] = new Project(url, 16);
    shouldUpdate = true;
    updateConfig();
    return 1;
}

int setPort3Url(String url) {
    if(monitor.projects.count(D2) != 0) {
          delete monitor.projects[D2];
          monitor.projects.erase(D2);
    }
    monitor.projects[D2] = new Project(url, 16);
    shouldUpdate = true;
    updateConfig();
    return 1;
}

int setPort4Url(String url) {
    if(monitor.projects.count(D3) != 0) {
          delete monitor.projects[D3];
          monitor.projects.erase(D3);
    }
    monitor.projects[D3] = new Project(url, 16);
    shouldUpdate = true;
    updateConfig();
    return 1;
}

void runPeriodically(void (*function)(), unsigned long period, unsigned long* lastCalled){
    if (millis() - *lastCalled > period){
        *lastCalled = millis();
        function();
    }
}

void updateConfig(){
    if(shouldUpdate == true) {
        Serial.println("Updating config");
        //deleting
        if(visualisers.count(D0) != 0) {
            delete visualisers[D0];
            visualisers.erase(D0);
        }
        if(visualisers.count(D1) != 0) {
            delete visualisers[D1];
            visualisers.erase(D1);
        }
        if(visualisers.count(D2) != 0) {
            delete visualisers[D2];
            visualisers.erase(D2);
        }
        if(visualisers.count(D3) != 0) {
            delete visualisers[D3];
            visualisers.erase(D3);
        }
        
        //adding
        if(monitor.projects.count(D0) != 0) {
          visualisers[D0] = new Visualiser(D0,monitor.projects[D0]->leds);   
        }
        if(monitor.projects.count(D1) != 0) {
          visualisers[D1] = new Visualiser(D1,monitor.projects[D1]->leds);   
        }
        if(monitor.projects.count(D2) != 0) {
          visualisers[D2] = new Visualiser(D2,monitor.projects[D2]->leds);   
        }
        if(monitor.projects.count(D3) != 0) {
          visualisers[D3] = new Visualiser(D3,monitor.projects[D3]->leds);   
        }
        shouldUpdate = false;
    }
}

void syncTime(){
    Spark.syncTime();
}

void updateStatus(){
    if(visualisers.count(D0) != 0) {
        visualisers[D0]->setStatus(monitor.getProjectStatus(D0));
    }
    if(visualisers.count(D1) != 0) {
        visualisers[D1]->setStatus(monitor.getProjectStatus(D1));
    }
    if(visualisers.count(D2) != 0) {
        visualisers[D2]->setStatus(monitor.getProjectStatus(D2));
    }
    if(visualisers.count(D3) != 0) {
        visualisers[D3]->setStatus(monitor.getProjectStatus(D3));
    }
}

unsigned int status=0;
BuildStatus **stats= new BuildStatus*[11];

void hackStatus(){
    
    if(visualisers.count(D0) != 0) {
        Serial.println("hack for D0");
        visualisers[D0]->setStatus(*stats[status]);
    }
    if(visualisers.count(D1) != 0) {
        Serial.println("hack for D1");
        visualisers[D1]->setStatus(*stats[10]);
    }
    if(visualisers.count(D2) != 0) {
        Serial.println("hack for D2");
        visualisers[D2]->setStatus(*stats[10]);
    }
    if(visualisers.count(D3) != 0) {
        Serial.println("hack for D3");
        visualisers[D3]->setStatus(*stats[10]);
    }
    
    status++;
    status%=11;
}


void setup() {
    Particle.function("setPort1Url", setPort1Url);
    Particle.function("setPort2Url", setPort2Url);
    Particle.function("setPort3Url", setPort3Url);
    Particle.function("setPort4Url", setPort4Url);
    
    Serial.begin(9600);
    //while(!Serial.available());
    delay(10000);
    shouldUpdate = true;
    updateConfig();
    Serial.println("setup done");
    
    int i=0;
    stats[i++] = new BuildStatus(build::FAILED, build::SUCCESS, 0, 0);
    stats[i++] = new BuildStatus(build::FAILED, build::SUCCESS, 0, 0);
    stats[i++] = new BuildStatus(build::FAILED, build::SUCCESS, 0, 0);
    stats[i++] = new BuildStatus(build::FAILED, build::SUCCESS, 0, 0);
    stats[i++] = new BuildStatus(build::FAILED, build::SUCCESS, 0, 0);
    stats[i++] = new BuildStatus(build::RUNNING, build::FAILED, 0, 0);
    stats[i++] = new BuildStatus(build::SUCCESS, build::RUNNING, 0, 0);
    stats[i++] = new BuildStatus(build::SUCCESS, build::RUNNING, 0, 0);
    stats[i++] = new BuildStatus(build::SUCCESS, build::RUNNING, 0, 0);
    stats[i++] = new BuildStatus(build::SUCCESS, build::RUNNING, 0, 0);
    stats[i++] = new BuildStatus(build::SUCCESS, build::RUNNING, 0, 0);
}

void animateVisualisers() {
    if(visualisers.count(D0) != 0) {
        visualisers[D0]->animate();
    }
    if(visualisers.count(D1) != 0) {
        visualisers[D1]->animate();
    }
    if(visualisers.count(D2) != 0) {
        visualisers[D2]->animate();
    }
    if(visualisers.count(D3) != 0) {
        visualisers[D3]->animate();
    }
}

void loop() {
    runPeriodically(updateConfig, 30000, &lastConfigUpdate); //every 3 minutes
    runPeriodically(syncTime, 3600000, &lastTimeSync); //every hour
    runPeriodically(updateStatus, 5000, &lastStatusUpdate); //every 5s
    //runPeriodically(hackStatus, 2000, &lastStatusUpdate);
    animateVisualisers();
    
    delay(20);
}


