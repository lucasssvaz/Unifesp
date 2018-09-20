#define M1_Temp_Pin A0
#define M2_Temp_Pin A1
#define Voltage_Pin A2
#define Current_Pin 4

float M1_temp[5];
float M2_temp[5];
float voltage;
float current;
int sensorValue_aux = 0;
float sensorValue = 0;
float voltsporUnidade = 0.004887586;

void setup() {
Serial.begin(9600);
pinMode(Voltage_Pin, INPUT);
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

for(int i=100; i>0; i--){
    sensorValue_aux = (analogRead(Voltage_Pin) -511); 
    sensorValue += pow(sensorValue_aux,2);
  }
sensorValue = (sqrt(sensorValue/ 100)) * voltsporUnidade;
current = (sensorValue/0.185);



Serial.print((M1_temp[0]+M1_temp[1]+M1_temp[2]+M1_temp[3]+M1_temp[4])/5);
Serial.print(',');
Serial.print((M2_temp[0]+M2_temp[1]+M2_temp[2]+M2_temp[3]+M2_temp[4])/5);
Serial.print(',');
Serial.print(voltage);
Serial.print(',');
Serial.println(current);
Serial.println(analogRead(A2));
delay(250);

sensorValue=0;
}
