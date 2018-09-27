#define M1_Temp_Pin A0
#define M2_Temp_Pin A1
#define Voltage_Pin A2
#define Current_Pin A3

void setup() {
Serial.begin(9600);
pinMode(Voltage_Pin,INPUT);
pinMode(Current_Pin,INPUT);
}

void loop() {
int i;
float M1_tempF = 0.0;
float M1_tempP = 0.0;
float M2_temp = 0.0;
int voltage = 0;
int current = 0;

for (i=0;i<50;i++){
M1_tempP += (float(analogRead(M1_Temp_Pin))*5/(1023))/0.01;
}

M1_tempF = M1_tempP/50;
M2_temp = (float(analogRead(M1_Temp_Pin))*5/(1023))/0.01;
voltage = analogRead(Voltage_Pin);
current = analogRead(Current_Pin);

Serial.print(M1_tempF);
Serial.print(',');
Serial.print(M2_temp);
Serial.print(',');
Serial.print(voltage);
Serial.print(',');
Serial.println(current);
delay(250);
}
