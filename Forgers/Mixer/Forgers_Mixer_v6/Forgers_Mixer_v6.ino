#include <Wire.h>
#include "A4988.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

/* Constants Definitions */
#define BACK_BUTTON       2
#define NEXT_BUTTON       4
#define SELECTOR          A0
#define DRIVER_ENABLE     13
#define DRIVER_STEPPER    8
#define DRIVER_DIRECTION  9
#define MOTOR_STEPS       200
#define BUZZER            7
/********************************/

/* Global Variables Definitions */
boolean nextButton, backButton;
int selectorPosition;
int modeId = 0;
/*  0 - Rotation
 *  1 - Seesaw
 *  2 - Seesaw with shake
 */
int speedRPM = 0;
int degreesLimit = 0;
unsigned long hours = 0;
unsigned long minutes = 0;
unsigned long seconds = 0;
unsigned long totalTime = 0;
unsigned long currentTime = 0;
unsigned long loopBeginTime, loopTime;
int progress;
/**********************************/

LiquidCrystal_I2C display(0x27,16,2);

A4988 motor(200,9,8);

void InitializeDevice() {
  digitalWrite(DRIVER_ENABLE,LOW);
  display.setBacklight(HIGH);
  display.clear();
  delay(1000);
  tone(7,1800);   
  delay(500);
  noTone(7);
  delay(500);
  display.setCursor(0, 0);
  display.print("  UNIFESP - SJC ");
  display.setCursor(0, 1);
  display.print("       ICT      ");
  delay(2000);
  display.clear();
  display.setCursor(0, 0);
  display.print("     Grupo      ");
  display.setCursor(0, 1);
  display.print("    Forgers     ");
  delay(2000);
  display.clear();
  display.setCursor(0, 0);
  display.print("    Forgers     ");
  display.setCursor(0, 1);
  display.print("     Mixer      ");
  delay(2000);
  display.clear();
  ConfigureDevice();
}

void ConfigureDevice() {
  display.setCursor(0, 0);  display.print("Aguarde"); delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.setCursor(0, 1);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  display.print(".");       delay(50);
  while(!digitalRead(NEXT_BUTTON)) {
    display.setCursor(0, 0);
    display.print("Pressione (B) p/");  
    display.setCursor(0, 1);
    display.print("configurar ciclo");
  }
  Pulse();
  delay(1000);
  ModeSelector(); 
}

void ModeSelector() {
  display.clear();
  display.setCursor(0, 0);  display.print("MODO DE OPERACAO");  
  display.setCursor(0, 1);  display.print(">>            ");
  while(!digitalRead(NEXT_BUTTON)) {
    selectorPosition = analogRead(SELECTOR);
    Serial.println(selectorPosition);
    display.setCursor(3,1);
    if( selectorPosition < 340) {
    modeId = 0;
    display.print("Rotacionar <<");
    } else {
      if( selectorPosition < 680) {
        modeId = 1;
        display.print("  Agitar   <<");
      } else {
        modeId = 2;
        display.print(" Misturar  <<");
      }
    }
  }
  display.clear();
  switch(modeId) {
    case 0:
      display.setCursor(0,0); display.print("SELECIONADO:    ");
      display.setCursor(0,1); display.print(">> Rotacionar   ");
      break;
    case 1:
      display.setCursor(0,0); display.print("SELECIONADO:    ");
      display.setCursor(0,1); display.print(">> Agitar       ");
      break;
    case 2:
      display.setCursor(0,0); display.print("SELECIONADO:    ");
      display.setCursor(0,1); display.print(">> Misturar     ");
      break;
    default:
      display.setCursor(0,0); display.print("Erro! Contacte  ");
      display.setCursor(0,1); display.print("o desenvolvedor ");
      break;
  }
  Pulse(); 
  delay(1000);
  SpeedSelector();
}

void SpeedSelector() {
  display.clear();
  display.setCursor(0, 0);  display.print("VELOCIDADE (rpm)");  
  display.setCursor(0, 1);  display.print(">>            <<");
  while(!digitalRead(NEXT_BUTTON)) {
    if(modeId == 0) speedRPM = map(analogRead(SELECTOR),2,971,10,60);  // 12 rpm - 30 Steps/s and 60 rpm - 200 Steps/s
    else speedRPM = map(analogRead(SELECTOR),2,971,10,30);  // 12 rpm - 30 Steps/s and 60 rpm - 200 Steps/s
    display.setCursor(7, 1); display.print(speedRPM);
    if(digitalRead(BACK_BUTTON)) ModeSelector();
  }
  display.clear();
  display.setCursor(0, 0);  display.print("SELECIONADO:    "); 
  display.setCursor(0, 1);  display.print(">>     rpm      ");
  display.setCursor(4, 1);  display.print(speedRPM);
  Pulse();
  delay(1000);
  DegreesLimitSelector();
}

void DegreesLimitSelector() {
  display.clear();
  if(modeId != 0) {
    display.clear();
    display.setCursor(0, 0);  display.print(" ANGULO LIMITE  ");  
    display.setCursor(0, 1);  display.print(">>            <<");
    display.setCursor(9, 1);  display.print((char)223);
    while(!digitalRead(NEXT_BUTTON)) {
      degreesLimit = map(analogRead(SELECTOR),2,971,10,90);  // 12 rpm - 30 Steps/s and 60 rpm - 200 Steps/s
      display.setCursor(6, 1); display.print(degreesLimit);
      if(digitalRead(BACK_BUTTON)) ModeSelector();
    }
    display.clear();
    display.setCursor(0, 0);  display.print("SELECIONADO:    "); 
    display.setCursor(0, 1);  display.print(">>              ");
    display.setCursor(6, 1);  display.print(degreesLimit);
    display.setCursor(9, 1);  display.print((char)223);
  }
  Pulse();
  delay(1000);
  HoursSelector();
}

void HoursSelector() {
  display.clear();
  display.setCursor(0,0); display.print("   DURACAO (h)  ");
  display.setCursor(0,1); display.print(">>            <<");
  while(!digitalRead(NEXT_BUTTON)) {
    hours = map(analogRead(SELECTOR),2,971,0,72);
    Serial.println(hours);
    display.setCursor(7,1);
    if(hours < 10) {
      display.print(" "); display.print(hours);
    } else {
      display.print(hours);
    }
    if(digitalRead(BACK_BUTTON)) SpeedSelector();
  }
  Pulse();
  delay(1000);
  MinutesSelector();
}

void MinutesSelector() {
  display.clear();
  display.setCursor(0,0); display.print("  DURACAO (min) ");
  display.setCursor(0,1); display.print(">>            <<");
  while(!digitalRead(NEXT_BUTTON)) {
    minutes = map(analogRead(SELECTOR),2,971,0,59);
    Serial.println(minutes);
    display.setCursor(7,1);
    if(minutes < 10) {
      display.print(" "); display.print(minutes);
    } else {
      display.print(minutes);
    }
    if(digitalRead(BACK_BUTTON)) HoursSelector();
  }
  Pulse();
  delay(1000);
  SecondsSelector(); 
}

void SecondsSelector() {
  display.clear();
  display.setCursor(0,0); display.print("   DURACAO (s)  ");
  display.setCursor(0,1); display.print(">>            <<");
  while(!digitalRead(NEXT_BUTTON)) {
    seconds = map(analogRead(SELECTOR),2,971,0,59);
    Serial.println(seconds);
    display.setCursor(6,1);
    if(seconds < 10) {
    display.print(" "); display.print(seconds);
    } else {
    display.print(seconds);
    }
    display.print(" s");
    if(digitalRead(BACK_BUTTON)) MinutesSelector();
  }
  display.clear();
  display.setCursor(0,0); display.print("Duracao total:  ");
  display.setCursor(0,1); display.print(hours);display.print(" h ");display.print(minutes); display.print(" min "); display.print(seconds); display.print(" s");
  totalTime = 3600*hours + 60*minutes + seconds;
  delay(2000);
  PrepareMix();
}

void PrepareMix() {
  display.clear();
  display.setCursor(0,0); display.print("Nivele a bandeja");
  display.setCursor(0,1); display.print("e aperte <B>    ");
  
  motor.begin(speedRPM, 16);
  while(!digitalRead(NEXT_BUTTON)) {
    if(digitalRead(BACK_BUTTON)) SecondsSelector();
  }
  motor.enable();
  StartMix();
}

void StartMix() {
  display.clear();
  display.setCursor(0,0); display.print("Comecando em    ");
  display.setCursor(13,0); display.print("3");
  Tone();
  delay(400);
  display.setCursor(13,0); display.print("2");
  Tone();
  delay(400);
  display.setCursor(13,0); display.print("1");
  Tone();
  delay(700);
  digitalWrite(DRIVER_ENABLE,HIGH);
  display.setCursor(0,0); display.print("Em progresso... ");
  updateDisplay(totalTime,0);
  MotorControl();
}

void MotorControl() {
  switch(modeId) {
    case 0:
    loopBeginTime = millis()/1000; 
    loopTime = millis()/1000;
    while(loopTime - loopBeginTime < totalTime) {
      motor.rotate(360); // One full rotation considering 1/16 steps configuration
      loopTime = millis()/1000;
      progress = currentTime/float(totalTime)*100; //Serial.println(progress);
      currentTime = (unsigned long)(ceil(float(loopTime-loopBeginTime)));
      updateDisplay(totalTime - currentTime,progress);   
    }
    break;
    case 1:
    motor.setSpeedProfile(motor.LINEAR_SPEED, 1500, 1500);
    loopBeginTime = millis()/1000; 
    loopTime = millis()/1000; 
    motor.rotate(-degreesLimit);
    while(loopTime - loopBeginTime < totalTime) {
      motor.rotate(degreesLimit*2);
      motor.rotate(-degreesLimit*2);
      loopTime = millis()/1000;
      progress = int(ceil(float(loopTime-loopBeginTime)/float(totalTime)*100));
      currentTime = (unsigned long)(ceil(float(loopTime-loopBeginTime)));
      updateDisplay(totalTime - currentTime,progress);
    }
    motor.rotate(degreesLimit);
    break;
    case 2:
    motor.setSpeedProfile(motor.LINEAR_SPEED, 2000, 2000);
    loopBeginTime = millis()/1000; //Serial.println(loopBeginTime);
    loopTime = millis()/1000; //Serial.println(loopTime);
    motor.rotate(degreesLimit);
    while(loopTime - loopBeginTime < totalTime) {
      motor.rotate(-degreesLimit*2);
      motor.rotate(-5); motor.rotate(5); motor.rotate(-5); motor.rotate(5); motor.rotate(-5); motor.rotate(5); motor.rotate(-5); motor.rotate(5);
      motor.rotate(degreesLimit*2);
      motor.rotate(5); motor.rotate(-5); motor.rotate(5); motor.rotate(-5); motor.rotate(5); motor.rotate(-5); motor.rotate(5); motor.rotate(-5);
      loopTime = millis()/1000;
      progress = int(ceil(float(loopTime-loopBeginTime)/float(totalTime)*100));
      currentTime = (unsigned long)(ceil(float(loopTime-loopBeginTime)));
      updateDisplay(totalTime - currentTime,progress);
    }
    motor.rotate(-degreesLimit);
    break;
  }
  Finalize();
}

void updateDisplay(unsigned long totalTimeInSec, int progress) {
  String TimeString;
  int hours =   (int)ceil((unsigned long)totalTimeInSec/3600);
  int minutes = (int)ceil((unsigned long)totalTimeInSec/60) - hours*60;
  int seconds = (int)(totalTimeInSec - minutes*60 - hours*3600);  
  display.setCursor(0,1); 

  if(progress <= 100) {  
    if(hours < 10) {
      display.print("0");  display.print(hours); display.print(":");  
    } else {
      display.print(hours); display.print(":");
    }
    if(minutes < 10) {
      display.print("0");  display.print(minutes); display.print(":");  
    } else {
      display.print(minutes); display.print(":");
    }
    if(seconds < 10) {
      display.print("0");  display.print(seconds); 
    } else {
      display.print(seconds);
    }  
  }
  display.setCursor(12,1);
  if(progress > 100) {
    display.print("100%");
  } else {
    if(progress < 10) {
      display.print("  "); display.print(progress); display.print("%");
    } else {
      if(progress < 100) {
        display.print(" "); display.print(progress); display.print("%");
      } else {
        display.print(progress); display.print("%");
      }
    }  
  } 
}

void Finalize() {
  boolean state;
  display.clear();
  display.setCursor(0,0); display.print("Fim! Pressione  ");
  display.setCursor(0,1); display.print("(A) p/ finalizar");
  while(!digitalRead(BACK_BUTTON)) {
    Tone();  
  }
  digitalWrite(DRIVER_ENABLE,LOW);
  ConfigureDevice();
}

void Tone() {
  tone(7,1800); delay(500); noTone(7); delay(100);  
}

void Pulse() {
  tone(7,1800); delay(20); noTone(7); delay(10);  
}
void setup() {
  Serial.begin(9600);
  display.init();
  motor.disable();
  motor.begin(60, 16);
  pinMode(DRIVER_ENABLE,OUTPUT);
  pinMode(BUZZER,OUTPUT);
  digitalWrite(DRIVER_ENABLE,LOW);
}

void loop() {
  InitializeDevice();
}
