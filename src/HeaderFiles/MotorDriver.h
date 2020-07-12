/**************
     * Motorshield is the ESP 12 E
     * https://cdn.hackaday.io/files/8856378895104/user-mannual-for-esp-12e-motor-shield.pdf
     * https://www.instructables.com/id/Motorize-IoT-With-ESP8266/
     *  connection
     *      A+ (PWM) -> D3
     *      A- (direction) -> D1
     *************/ 

    #ifndef _MOTORDRIVER_h
    #define _MOTORDRIVER_h
#define PWM_MOTOR_PIN D1
#define DIR_MOTOR_PIN D3

#include <ESP8266WiFi.h>

class MotorDriver{
    public:
    
    void init(){
          pinMode(DIR_MOTOR_PIN,OUTPUT);

    }
    void rotate(int speed, int direction, int time){
        /***
         * speed in range 0-255 (pwm with analogwrite on a digital pin)
         * direction is 1 or 0
         * time is in ms 
        ***/
       if (speed > 255) speed = 255;
       if (speed < 0) speed = 0;

       digitalWrite(DIR_MOTOR_PIN,direction);
       analogWrite(PWM_MOTOR_PIN,speed);
       delay(time); 
       analogWrite(PWM_MOTOR_PIN, 0);
    
    }
};

#endif