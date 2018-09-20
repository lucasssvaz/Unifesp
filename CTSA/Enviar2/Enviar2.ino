#include <IRLibAll.h>
     
IRsend mySender;

void AC_Liga(){
  mySender.send(NEC,0x2fed3128);
}
void AC_Desliga(){
  mySender.send(NEC,0x2fed3128);
}

void setup() {
Serial.begin(9600);
}
     
void loop() {
  if (Serial.read() == 49) {
  AC_Liga();
  }
  if (Serial.read() == 50) {
  AC_Desliga();
  }
}
