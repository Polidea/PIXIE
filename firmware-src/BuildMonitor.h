#ifndef JENKINS_CLIENT_H
#define JENKINS_CLIENT_H

#include <time.h>
#include "rest_client.h"
#include "BuildStatus.h"
#include <math.h>
#undef min
#undef max
#include <map>
#include "Project.h"
#include <string>

class BuildMonitor {
    public:
        explicit BuildMonitor();
        BuildStatus getProjectStatus(int i);
    private:
        static time_t parseDate(String date_string);
    public: std::map <int, Project*> projects;
};

#endif
