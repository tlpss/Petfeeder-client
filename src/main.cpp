#include <Wire.h>
#include <ESP8266WiFi.h>
#include "HeaderFiles/FeederSchedule.h"
#include "HeaderFiles/HTTP_Lib.h"
#include "HeaderFiles/FeederParser.h"
#include "HeaderFiles/MotorDriver.h"
#include "HeaderFiles/RtcWrapper.h"


#define FEEDER_NAME "picasso"
#define DC_MOTOR_FACTOR 1000



MotorDriver motordriver =  MotorDriver();
RTCWrapper Rtc = RTCWrapper();



void setup(){
  
  Serial.begin(9600);
  //init motordriver
  motordriver.init();
  //http init
  connect();
  //RTC 
  //DONT USE rtc! global variable of the header...
  Rtc.init();
  /****test*/
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  rtc.SetIsRunning(true);
  RtcDateTime now = rtc.GetDateTime();
  rtc.SetDateTime(compiled-2*60*60+20); // heuristic (!! compensate for timezone to get UTC)
    
}

void loop(){
  //create feeder

  FeederSchedule* schedule  = new FeederSchedule();
  Serial.println("start loop");
  //get relevant moments

  char* url;
  long update_time = (long) rtc.GetDateTime().Epoch64Time();
  String url_s = String("http://tlpss.eu.pythonanywhere.com/petfeeder/api/raw/unix/next_moment/");
  String name_url = String(FEEDER_NAME);
  //String url_sep = String("?last_update=");
  //String time_url = String(schedule->get_last_update());
  //Serial.println("update time");
  //Serial.println(time_url);
  //String total_url = url_s + name_url + url_sep + time_url;
  String total_url = url_s + name_url;
  String  res = get_response(total_url);
  Serial.print("response received");
  FeedMoment current_moment = parse_and_add_response(res,schedule);
  //schedule->set_last_update(update_time);

  //get current moment
  //
  //FeedMoment* current_moment = schedule->get_current_moment();
  Serial.println("currentmoment");
  Serial.println(current_moment.hour);
  Serial.println(current_moment.minute);
  Serial.println(current_moment.amount);

  
//set time
  RtcDateTime time  =Rtc.get_current_time();
  Serial.println("time");
  Serial.println(time.Hour());
  Serial.println(time.Minute());
  Serial.println(time.Second());

  //set Alarm
  Rtc.setAlarm2(current_moment.hour,current_moment.minute);
  Rtc.attach_interrupt(D5);

  //wait for feedtime

  while(!interrupt_flag){
    Serial.println("waiting for interrupt");
    delay(60*1000); //TODO make sleep of this idle
  }
  //feed
  Serial.println("feeding");
  motordriver.rotate(255,1,current_moment.amount*DC_MOTOR_FACTOR);
  //reset interrupt
  Rtc.resetFlag();
  //next!
  //schedule->next();


  
  
  

    
}
