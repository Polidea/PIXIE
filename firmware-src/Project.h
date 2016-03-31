#ifndef PROJECT_H
#define PROJECT_H

#include "BuildStatus.h"

class Project {
    public: String endpoint;
    public: unsigned char endpointIP[4];
    public: String path;
    BuildStatus buildStatus;
    int leds;
    Project(String fullUrl,int leds){
        
      std::string domain = "";
      std::string path = "";
    std::string uri(fullUrl.c_str());
    int doubleSlashPos = uri.find("//", 0); 
    int thirdSlashPos = uri.find("/", doubleSlashPos+2);
    domain = uri.substr(doubleSlashPos+2, thirdSlashPos-doubleSlashPos-2); // extract domain
    path = uri.substr(thirdSlashPos, uri.length()-1);
      
        this->endpoint = String(domain.c_str());
        this->path = String(path.c_str());
        buildStatus=BuildStatus("NONE", "NONE", 0, 0);
        this->leds = leds;
    }
};

#endif