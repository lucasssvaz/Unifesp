#define M1_Temp_Pin A0
#define M2_Temp_Pin A1
#define Voltage_Pin 3
#define Current_Pin 4

float M1_temp[5];
float M2_temp[5];
float voltage;
float current;

void setup() {
Serial.begin(9600);
pinMode(Voltage_Pin,INPUT);
pinMode(Current_Pin,INPUT);
M1_temp[0] = (float(analogRead(M1_Temp_Pin))*5/(1023))/0.01;
M1_temp[1] = (float(analogRead(M1_Temp_Pin))*5/(1023))/0.01;
M1_temp[2] = (float(analogRead(M1_Temp_Pin))*5/(1023))/0.01;
M1_temp[3] = (float(analogRead(M1_Temp_Pin))*5/(1023))/0.01;
M1_temp[4] = (float(analogRead(M1_Temp_Pin))*5/(1023))/0.01;
M2_temp[0] = (float(analogRead(M1_Temp_Pin))*5/(1023))/0.01;
M2_temp[1] = (float(analogRead(M1_Temp_Pin))*5/(1023))/0.01;
M2_temp[2] = (float(analogRead(M1_Temp_Pin))*5/(1023))/0.01;
M2_temp[3] = (float(analogRead(M1_Temp_Pin))*5/(1023))/0.01;
M2_temp[4] = (float(analogRead(M1_Temp_Pin))*5/(1023))/0.01;
}

void loop() {

M1_temp[4]=M1_temp[3];
M1_temp[3]=M1_temp[2];
M1_temp[2]=M1_temp[1];
M1_temp[1]=M1_temp[0];
M2_temp[4]=M2_temp[3];
M2_temp[3]=M2_temp[2];
M2_temp[2]=M2_temp[1];
M2_temp[1]=M2_temp[0];

M1_temp[0] = (float(analogRead(M1_Temp_Pin))*5/(1023))/0.01;
M2_temp[0] = (float(analogRead(M1_Temp_Pin))*5/(1023))/0.01;
voltage = analogRead(Voltage_Pin);
current = analogRead(Current_Pin);

Serial.print((M1_temp[0]+M1_temp[1]+M1_temp[2]+M1_temp[3]+M1_temp[4])/5);
Serial.print(',');
Serial.print((M2_temp[0]+M2_temp[1]+M2_temp[2]+M2_temp[3]+M2_temp[4])/5);
Serial.print(',');
Serial.print(voltage);
Serial.print(',');
Serial.println(current);
delay(500);
}
