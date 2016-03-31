#include "BuildStatus.h"

BuildStatus::BuildStatus(String result, String previous_result, unsigned long elapsed, unsigned long estimate) : elapsedTime_(elapsed), executionEstimate_(estimate) {
    timestamp_ = millis();
    currentResult_ = parseResultString(result);
    previousResult_ = parseResultString(previous_result);
}

BuildStatus::BuildStatus(build::ExecutionResult result, build::ExecutionResult previous_result, unsigned long elapsed, unsigned long estimate) : elapsedTime_(elapsed), executionEstimate_(estimate) {
    timestamp_ = millis();
    currentResult_ = result;
    previousResult_ = previous_result;
}

BuildStatus::BuildStatus() : elapsedTime_(0), executionEstimate_(0) {
    timestamp_ = millis();
    currentResult_ = parseResultString("NONE");
    previousResult_ = parseResultString("NONE");
}

build::ExecutionResult BuildStatus::getCurrentResult() const {
    return currentResult_;
}

build::ExecutionResult BuildStatus::getPreviousResult() const {
    return previousResult_;
}

float BuildStatus::getProgress() const {
    return float(elapsedTime_+((millis()-timestamp_)/1000))/float(executionEstimate_);
}

build::ExecutionResult BuildStatus::parseResultString(String string) {
    switch (string.charAt(0)) {
        case 's':
            return build::SUCCESS;
            break;
        case 'f':
            return build::FAILED;
            break;
        case 'p':
            return build::PENDING;
            break;
        case 'r':
            return build::RUNNING;
            break;
        case 'c':
            return build::CANCELED;
            break;
    }
    return build::NOT_FOUND;
}

bool BuildStatus::isFound() const {
    return currentResult_ != build::NOT_FOUND && previousResult_ != build::NOT_FOUND;
}

bool BuildStatus::operator==(BuildStatus& rhs)const{
    return this->currentResult_==rhs.currentResult_;
}