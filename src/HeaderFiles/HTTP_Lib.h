#ifndef _HTTP_LIB_h
#define _HTTP_LIB_h

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "Lips-Belaen";
const char *password = "Grommit123";

void connect(){
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED){
        delay(1000);
        Serial.print("connecting\n");
    }
}

String get_response(String url){

    if (WiFi.status() == WL_CONNECTED){ //Check WiFi connection status

        HTTPClient http; //Declare an object of class HTTPClient
        http.begin(url);           //Specify request destination
        int httpCode = http.GET(); //Send the request
        Serial.print(String(httpCode));
        Serial.print("\n");
        String payload = "";
        if (httpCode > 0){ //Check the returning code
            Serial.print("connection succeeded\n");
             payload = http.getString(); //Get the request response payload
            
        }
        http.end(); //Close connection
        return payload;
    }
    return "error";
}

#endif