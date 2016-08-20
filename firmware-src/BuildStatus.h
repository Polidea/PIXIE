#ifndef BUILD_STATUS_H
#define BUILD_STATUS_H

#include "application.h"

namespace build {
    enum ExecutionResult {
        SUCCESS,
        FAILED,
        PENDING,
        RUNNING,
        CANCELED,
        NOT_FOUND
    };
}

class BuildStatus {
    
    public:
        BuildStatus();
        BuildStatus(String result, String previous_result, unsigned long elapsed, unsigned long estimate);
        BuildStatus(build::ExecutionResult result, build::ExecutionResult previous_result, unsigned long elapsed, unsigned long estimate);
        build::ExecutionResult getCurrentResult() const;
        build::ExecutionResult getPreviousResult() const;
        float getProgress() const;
        bool isFound() const;
        bool operator==(BuildStatus& rhs)const;
        static build::ExecutionResult parseResultString(String string);
    private:
        build::ExecutionResult currentResult_;    
        build::ExecutionResult previousResult_;
        unsigned long timestamp_;
        unsigned long elapsedTime_;
        unsigned long executionEstimate_;
};

#endif
