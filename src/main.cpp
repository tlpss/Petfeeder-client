#include <Wire.h>
#include <ESP8266WiFi.h>
#include "HeaderFiles/FeederSchedule.h"
#include "HeaderFiles/HTTP_Lib.h"
#include "HeaderFiles/FeederParser.h"
#include "HeaderFiles/MotorDriver.h"

MotorDriver motordriver =  MotorDriver();

void setup(){
  Serial.begin(9600);
  //init motordriver
  motordriver.init();
  //http init
  connect();
  //RTC
}

void loop(){
  /*//create feeder
  FeederSchedule* schedule  = new FeederSchedule();
  String  res = get_response("http://tlpss.eu.pythonanywhere.com/petfeeder/api/raw/testfeeder?last_update=2019-08-02%2018:15:27.243860");
  
  parse_and_add_response(res,schedule);
  // test
  FeedMoment* current_moment = schedule->get_current_moment();
  Serial.print(current_moment->hour);
  delay(10000);
  //
  Serial.print("\n-----new iteration------\n");*/
  digitalWrite(D1,1-digitalRead(D1));
  analogWrite(D3,255);
  delay(1000);
  analogWrite(D3,128);
  delay(1000);
  analogWrite(D3,0);
  delay(1000);

  
}
