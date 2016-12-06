#include <time.h>
#include <map>
#include "Led.h"
#include "Visualiser.h"
#include "BuildStatus.h"

std::map<int, Visualiser*> visualisers;
unsigned long lastConfigUpdate = millis();
unsigned long lastTimeSync = millis();
bool shouldUpdate;
const int NUMBER_OF_LEDS = 16;

void setPortStatus(int port, String status) {
    BuildStatus currentBuildStatus = visualisers[port]->getStatus();
    BuildStatus newBuildStatus = BuildStatus(
        BuildStatus::parseResultString(status),
        currentBuildStatus.getCurrentResult(),
        0, 0);

    visualisers[port]->setStatus(newBuildStatus);
}

int statusPort1(String status) {
    setPortStatus(D0, status);
    return 0;
}

int statusPort2(String status) {
    setPortStatus(D1, status);
    return 0;
}

int statusPort3(String status) {
    setPortStatus(D2, status);
    return 0;
}

int statusPort4(String status) {
    setPortStatus(D3, status);
    return 0;
}

int statusPort5(String status) {
    setPortStatus(D4, status);
    return 0;
}

int statusPort6(String status) {
    setPortStatus(D5, status);
    return 0;
}

int statusPort7(String status) {
    setPortStatus(D6, status);
    return 0;
}

int statusPort8(String status) {
    setPortStatus(D7, status);
    return 0;
}

void runPeriodically(void (*function)(), unsigned long period, unsigned long* lastCalled){
    if (millis() - *lastCalled > period){
        *lastCalled = millis();
        function();
    }
}

void syncTime(){
    Particle.syncTime();
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
        visualisers[D0] = new Visualiser(D0, NUMBER_OF_LEDS);
        visualisers[D1] = new Visualiser(D1, NUMBER_OF_LEDS);
        visualisers[D2] = new Visualiser(D2, NUMBER_OF_LEDS);
        visualisers[D3] = new Visualiser(D3, NUMBER_OF_LEDS);
        shouldUpdate = false;
    }
}


unsigned int status=0;
BuildStatus **stats= new BuildStatus*[11];

void setup() {
    Particle.function("statusPort1", statusPort1);
    Particle.function("statusPort2", statusPort2);
    Particle.function("statusPort3", statusPort3);
    Particle.function("statusPort4", statusPort4);
    Particle.function("statusPort5", statusPort5);
    Particle.function("statusPort6", statusPort6);
    Particle.function("statusPort7", statusPort7);
    Particle.function("statusPort8", statusPort8);

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
    animateVisualisers();

    delay(20);
}
