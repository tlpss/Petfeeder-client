#ifndef _RTCWRAPPER_h
#define _RTCWRAPPER_h

#include <RtcDS3231.h>
#include <Wire.h>

RtcDS3231<TwoWire> rtc(Wire);

volatile boolean interrupt_flag = false;
/***ISR****/
ICACHE_RAM_ATTR // ISR's must be in the IRAM!
void setFlag(){
        interrupt_flag = true;
        Serial.println("interruptflag=true");
        rtc.LatchAlarmsTriggeredFlags(); //clear old active alarm-flags

    }
/**********/
class RTCWrapper{
    public:
    
    void init(){
        rtc._wire.begin(D7,D6); //made _wire protected and I don't use the begin... 
        rtc.Enable32kHzPin(false);
        rtc.SetSquareWavePin(DS3231SquareWavePin_ModeAlarmBoth);
        
    }
    RtcDateTime get_current_time(){
        return rtc.GetDateTime();
    }

    void setAlarm2(uint8_t hour, uint8_t min){
        uint8_t zero = 0;
        DS3231AlarmTwo alarm(0,hour,min,DS3231AlarmTwoControl_HoursMinutesMatch);
        rtc.SetAlarmTwo(alarm);
        rtc.LatchAlarmsTriggeredFlags(); //clear old active alarm-flags
    }

    void attach_interrupt(byte interrupt_pin){
        pinMode(interrupt_pin, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(interrupt_pin),
        setFlag,FALLING);

    }

    void resetFlag(){
        interrupt_flag = false;
        Serial.println("interruptflag=false");
    }

    
};



#endif