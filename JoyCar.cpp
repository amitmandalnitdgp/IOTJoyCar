#include <stdio.h>
#include "JoyCar.h"
#include <wiringPi.h>
#include <iostream>
#include <pcf8591.h>
#include <softPwm.h>
#include <math.h>
#include <stdlib.h>
//#include "iolibrary.h"
#include "csonar.h"

//Joystick and PCF8591T Parameters
#define address 0x48        //pcf8591 default address
#define pinbase 64          //any number above 64
#define A0 pinbase + 0
#define A1 pinbase + 1
#define A2 pinbase + 2
#define A3 pinbase + 3
//define the pin connected to L293D
#define motorPin1	2	//GPIO 27
#define motorPin2	0  //GPIO 17
#define enablePin	3 //GPIO 22

// Servo Parameters
#define OFFSET_MS 3     // Defines the unit of servo pulse offset: 0.1ms
#define SERVO_MIN_MS 5+OFFSET_MS        // Defines the pulse duration for minimum angle of servo
#define SERVO_MAX_MS 25+OFFSET_MS       // Ddefines the pulse duration for maximum angle of servo

#define Z_Pin 1     //defines pin for axis Z of Joystick
#define servoPin    4       //GPIO number connected to servo (GPIO 23)


using namespace std;


//setup wiringpi
JNIEXPORT jint JNICALL Java_JoyCar_initializeWiringPi(JNIEnv *env, jobject o){

	if(wiringPiSetup() == -1) //when initialize wiring failed,print messageto screen
		return 0;
	else
		return 1;

}
//setup pcf8591t
JNIEXPORT void JNICALL Java_JoyCar_initializePCF8591(JNIEnv *env, jobject o){

	pinMode(Z_Pin,INPUT);       //set Z_Pin as input pin and pull-up mode
    pullUpDnControl(Z_Pin,PUD_UP);
	pcf8591Setup(pinbase,address);

}
//code for joystick
JNIEXPORT jint JNICALL Java_JoyCar_readUpDown(JNIEnv *env, jobject o){
  return analogRead(A1);
}

JNIEXPORT jint JNICALL Java_JoyCar_readLeftRight(JNIEnv *env, jobject o){
	return analogRead(A0);
}
JNIEXPORT jboolean JNICALL Java_JoyCar_isButtonPressed(JNIEnv *env, jobject o){
  return digitalRead(Z_Pin)==0;
}
//code for servo
long map(long value,long fromLow,long fromHigh,long toLow,long toHigh){
    return (toHigh-toLow)*(value-fromLow) / (fromHigh-fromLow) + toLow;
}
void servoInit(int pin){        //initialization function for servo PMW pin
    softPwmCreate(pin,  0, 200);
}




void softPwmWrite2  (int pin, char * value) {
	csonar_taint_sink(csonar_taint_source_any(),

	*value,

	"Tainted Input to print_important_data",

	"CWE:20",

	csws_security);
}

void foo(int angle, char * angle2){    //Specif a certain rotation angle (0-180) for the servo
	int taintunion = csonar_taint_union2(csonar_string_taint(angle2),	csonar_taint_source_generic());

	*angle2 = taintunion;

	if(angle > 180)
        angle = 180;
    if(angle < 0)
        angle = 0;
    softPwmWrite(servoPin,map(angle,0,180,SERVO_MIN_MS,SERVO_MAX_MS));
    softPwmWrite2(servoPin, angle2);
    delay(100);
}

JNIEXPORT void JNICALL Java_JoyCar_turnAtAngle(JNIEnv *env, jobject o, jint angle){    //Specif a certain rotation angle (0-180) for the servo
	if(angle > 180)
        angle = 180;
    if(angle < 0)
        angle = 0;
    softPwmWrite(servoPin,map(angle,0,180,SERVO_MIN_MS,SERVO_MAX_MS));
    delay(100);
}


void servoWriteMS(int pin, int ms){     //specific the unit for pulse(5-25ms) with specific duration output by servo pin: 0.1ms
    if(ms > SERVO_MAX_MS)
        ms = SERVO_MAX_MS;
    if(ms < SERVO_MIN_MS)
        ms = SERVO_MIN_MS;
    softPwmWrite(pin,ms);
}

JNIEXPORT void JNICALL Java_JoyCar_initializeServo(JNIEnv *env, jobject o){
	servoInit(servoPin);
}

JNIEXPORT void JNICALL Java_JoyCar_turnRight(JNIEnv *env, jobject o){
	int i;
	for(i=SERVO_MIN_MS;i<SERVO_MAX_MS;i++){  //make servo rotate from minimum angle to maximum angle
		servoWriteMS(servoPin,i);
        delay(100);
    }
}

JNIEXPORT void JNICALL Java_JoyCar_turnLeft(JNIEnv *, jobject){
	int i;
	for(i=SERVO_MAX_MS;i>SERVO_MIN_MS;i--){  //make servo rotate from minimum angle to maximum angle
		servoWriteMS(servoPin,i);
        delay(100);
    }

}

//code for motor acceleration
//motor function: determine the direction and speed of the motor according to the ADC
void motor(int ADC){
	int value = ADC -130;
	if(value>0){
		digitalWrite(motorPin1,HIGH);
		digitalWrite(motorPin2,LOW);
		printf("turn Forward...\n");
	}
	else if (value<0){
		digitalWrite(motorPin1,LOW);
		digitalWrite(motorPin2,HIGH);
		printf("turn Back...\n");
	}
	else {
		digitalWrite(motorPin1,LOW);
		digitalWrite(motorPin2,LOW);
		printf("Motor Stop...\n");
	}
	softPwmWrite(enablePin,map(abs(value),0,130,0,255));
	printf("The PWM duty cycle is %d%%\n",abs(value)*100/127);//print the PMW duty cycle
}

JNIEXPORT void JNICALL Java_JoyCar_initializeMotor(JNIEnv *env, jobject o){
	pinMode(enablePin,OUTPUT);//set mode for the pin
	pinMode(motorPin1,OUTPUT);
	pinMode(motorPin2,OUTPUT);
	softPwmCreate(enablePin,0,100);//define PMW pin
}


JNIEXPORT void JNICALL Java_JoyCar_runMotor(JNIEnv *env, jobject o, jint val){
	printf("ADC value : %d \n",val);
	motor(val);		//start the motor
	delay(100);
}
