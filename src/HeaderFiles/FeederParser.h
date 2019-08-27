#include "HeaderFiles/FeederSchedule.h"
#include <ESP8266WiFi.h>


void parse_and_add_response(String response, FeederSchedule* schedule ){
    response = response.substring(1,response.length()-1); //remove [..]
    int number_of_moments = 1;
    for (int i = 0; i< response.length();i++){
        if(response.charAt(i) == ',') number_of_moments++;
    }
    Serial.print("parsing!\n");
    Serial.print("\n number_of_moments=");
    Serial.print(number_of_moments);
    Serial.print("\n");
    while(number_of_moments > 0) {
        //actual parsing
        String moment = response.substring(0,response.indexOf(',')-1);
        response = response.substring(response.indexOf(',')+2);
        moment = moment.substring(1,response.length()-1); //remove '..'
        ////Serial.print(moment);
        ////Serial.print("\n");
        int minutes = (moment.substring(0,moment.indexOf('-'))).toInt();
        moment = moment.substring(moment.indexOf('-')+1);
        ////Serial.print(moment);
        //Serial.print("\n");
        int amount = (moment.substring(0,moment.indexOf('-'))).toInt();
        moment = moment.substring(moment.indexOf('-')+1);
        //Serial.print(moment);
        //Serial.print("\n");
        int unix = (moment.substring(0,moment.indexOf('-'))).toInt();
        //Serial.print("\n---\n");
        //Serial.print(minutes);
        //Serial.print("\n");
        //Serial.print(amount);
        //Serial.print("\n");
        //Serial.print(unix);
        //Serial.print("\n---\n");
        number_of_moments--;
        //add moment to petfeeder
        schedule->add_moment(minutes / 60, minutes % 60, amount);
    
    }
    
}