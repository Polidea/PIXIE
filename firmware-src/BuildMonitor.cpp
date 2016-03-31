#include "jsmnSpark.h"
#include "BuildMonitor.h"

//const char SEPARATOR = '|';
int a = 0;

BuildMonitor::BuildMonitor() {
 
}

BuildStatus BuildMonitor::getProjectStatus(int pin){
    Serial.println("Getting status for: "+projects[pin]->endpoint);
    Serial.println("Getting status for: "+projects[pin]->path);
  
    String requestString = String(projects[pin]->path);
    int requestStringLength = requestString.length()+1;
    char * requestCharArray = new char[requestStringLength];
    requestString.toCharArray(requestCharArray, requestStringLength);
    
    String result = "";
    RestClient client_ = RestClient(projects[pin]->endpoint.c_str());
    int status = client_.get(requestCharArray, &result);
    delete [] requestCharArray;
    if (status != 200){
      Serial.println("STATUS: "+status);
      return projects[pin]->buildStatus;
    }

    jsmn_parser parser;
    jsmn_init(&parser);
    jsmntok_t tokens[9];

    int resultStringLength = result.length()+1;
    char * resultCharArray = new char[resultStringLength];
    result.toCharArray(resultCharArray, resultStringLength);
    int parsed = jsmn_parse(&parser, resultCharArray, tokens, 9);
    delete [] resultCharArray;
    
    if (parsed != JSMN_SUCCESS || tokens[0].size != 8){
        Serial.println("Could not parse status json.");
        //Serial.println(tokens[0].size);
        return projects[pin]->buildStatus;
    }
    
    int estimate = atoi(result.substring(tokens[4].start, tokens[4].end).c_str());
    int elapsed = atoi(result.substring(tokens[8].start, tokens[8].end).c_str());
    
    //Serial.println(result.substring(tokens[2].start, tokens[2].end));
    //Serial.println(estimate);
    //Serial.println(result.substring(tokens[6].start, tokens[6].end));
    //Serial.println(elapsed);
    //Serial.println("---");
    
    BuildStatus newBuildStatus = BuildStatus(result.substring(tokens[6].start, tokens[6].end), result.substring(tokens[2].start, tokens[2].end), elapsed, estimate);

    if (!newBuildStatus.isFound()) {
        Serial.println("No new build status.");
        return projects[pin]->buildStatus;
    }
    
    projects[pin]->buildStatus = newBuildStatus;
    Serial.print("New build status: ");
    Serial.println(newBuildStatus.getCurrentResult());
    return newBuildStatus;
}

time_t BuildMonitor::parseDate(String date_string){
    struct tm tm;

    int dateStringLength = date_string.length()+1;
    char * dateCharArray = new char[dateStringLength];
    date_string.toCharArray(dateCharArray, dateStringLength);
    
    if (strptime(dateCharArray, "%Y-%m-%dT%H:%M:%S", &tm) != NULL){
        delete [] dateCharArray;
        return mktime(&tm);
    }
    else {
        Serial.print("Could not parse date: ");
        Serial.println(date_string);
        delete [] dateCharArray;
        return 0;
    }
}
