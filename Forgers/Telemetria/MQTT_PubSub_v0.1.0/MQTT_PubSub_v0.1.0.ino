//====================================================================================================================== Libraries and definitions

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define DEBUG

#ifdef DEBUG
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTLN(x) Serial.println(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
#endif

//======================================================================================================================= Variable declaration and initialization

// WiFi
const char* ssid = "Forgers_MQTT";
const char* wifi_password = "#GoForgers";

char M1_Temp[50], M2_Temp[50], Voltage[50], Current[50];
boolean halt = 0, sent1, sent2, sent3, sent4;
unsigned long int now = 0, last = 0;

// MQTT
const char* mqtt_server = "192.168.5.1";
const char* mqtt_topic_M1Temp = "Hockey_1/M1_Temp";
const char* mqtt_topic_M2Temp = "Hockey_1/M2_Temp";
const char* mqtt_topic_Voltage = "Hockey_1/Voltage";
const char* mqtt_topic_Current = "Hockey_1/Current";
const char* mqtt_topic_Commands = "Hockey_1/Commands";
const char* mqtt_username = "forgers";
const char* mqtt_password = "xxt";
const char* clientID = "Hockey_1";

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); // 1883 is the listener port for the Broker

//======================================================================================================================= Reconnect function

void reconnect() {
  
  while (!client.connected()) {
    digitalWrite(D4,HIGH);
    DEBUG_PRINT("Attempting MQTT connection...");
    
    if (client.connect(clientID, mqtt_username, mqtt_password)) {
      
      DEBUG_PRINTLN("connected");
      client.subscribe(mqtt_topic_Commands);
      digitalWrite(D4,LOW);
          
    } else {
      
      DEBUG_PRINT("failed, rc=");
      DEBUG_PRINT(client.state());
      DEBUG_PRINTLN(" try again in 5 seconds");
      delay(5000);
    }
  }
}

//======================================================================================================================= Callback function

void callback(char* topic, byte* payload, unsigned int length) {
  DEBUG_PRINT("Message arrived [");
  DEBUG_PRINT(topic);
  DEBUG_PRINT("] ");
  for (int i = 0; i < length; i++) {
    DEBUG_PRINT((char)payload[i]);
  }
  DEBUG_PRINTLN();

  if ((char)payload[0] == 'S') {
    halt = 1;
    digitalWrite(D4,HIGH);
  } else if ((char)payload[0] == 'G') {
    halt = 0;
    digitalWrite(D4,LOW);
  }
  
  DEBUG_PRINT("Halt = ");
  DEBUG_PRINTLN(halt);

}

//======================================================================================================================== Initial Configuration

void setup() {

  pinMode(D4, OUTPUT);
  digitalWrite(D4,HIGH);
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  DEBUG_PRINTLN();
  DEBUG_PRINT("Connecting to ");
  DEBUG_PRINT(ssid);
  
  WiFi.begin(ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    DEBUG_PRINT(".");
  }

  DEBUG_PRINTLN();
  DEBUG_PRINTLN("WiFi connected!");
  DEBUG_PRINT("IP address: ");
  DEBUG_PRINTLN(WiFi.localIP());

  client.setCallback(callback);
  boolean aux = client.connect(clientID, mqtt_username, mqtt_password);
  client.subscribe(mqtt_topic_Commands);

  if (aux) {
    DEBUG_PRINTLN("Connected to MQTT Broker!");
    client.subscribe(mqtt_topic_Commands);
    digitalWrite(D4,LOW);
  }
  else {
    DEBUG_PRINTLN("Connection to MQTT Broker failed...");
    reconnect();
  }
  
}

//========================================================================================================================= Loop

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  
  client.loop();

  now = millis();
  
  if (now - last > 1000){
    
    last = now;
  
    sprintf(M1_Temp,"%d",rand());
    sprintf(M2_Temp,"%d",rand());
    sprintf(Voltage,"%d",rand());
    sprintf(Current,"%d",rand());
    
      sent1 = client.publish(mqtt_topic_M1Temp, M1_Temp);
      sent2 = client.publish(mqtt_topic_M2Temp, M2_Temp);
      sent3 = client.publish(mqtt_topic_Voltage, Voltage);
      sent4 = client.publish(mqtt_topic_Current, Current);

    
    if (sent1 == 0 || sent2 == 0 || sent3 == 0 || sent4 == 0) {
      DEBUG_PRINTLN("Message failed to send. Reconnecting to MQTT Broker and trying again");
      reconnect();
      delay(10);
      client.publish(mqtt_topic_M1Temp, M1_Temp);
      client.publish(mqtt_topic_M2Temp, M2_Temp);
      client.publish(mqtt_topic_Voltage, Voltage);
      client.publish(mqtt_topic_Current, Current);
    } else {
      DEBUG_PRINTLN("Message sent!");
    }
  }
}
