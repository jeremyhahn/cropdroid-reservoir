#include <Arduino.h>
#include <SPI.h>
#include "Ethernet.h"
#include "DHT.h"
#include <Wire.h>
#include "OneWire.h"
#include "DallasTemperature.h"

#define DEBUG_MODE 1
#define AREST_NUMBER_VARIABLES 20

#include <aREST.h>

#define HYDRO_DEBUG 1
#define ONE_WIRE_BUS 5
#define DHT_ENV_PIN  7

DHT envDHT(DHT_ENV_PIN, DHT22);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xFE, 0x42 };
IPAddress ip(192,168,0,200);

EthernetClient client;
EthernetServer server(80);
aREST rest = aREST();

float envTemp, envHumidity, envHeatIndex,
      PH, EC, TDS, SAL, SG, DO_mgL, DO_PER, ORP = 0.0;

int EC_ID = 100, PH_ID = 99, DO_ID = 97, ORP_ID = 98, systemTemp = 0;

String systemTime, pod0Temp, pod1Temp, resTemp = "0";

void readProbe(int channel, float *probe);
void readTempHumidity();
void readResTemp();
void debug(String msg);

int main(void) {
  init();
  setup();

  for (;;)
    loop();

  return 0;
}

void setup(void) {

  Serial.begin(115200);
  Serial.println("Initializing reservoir controller...");

  if(Ethernet.begin(mac) == 0) {
    Serial.println("Failed to obtain DHCP address");
    Ethernet.begin(mac, ip);
  }

  server.begin();
  Serial.print("REST server listening on ");
  Serial.println(Ethernet.localIP());

  Wire.begin();
  envDHT.begin();

  readTempHumidity();

  rest.set_id("420");
  rest.set_name("room1-res");

  rest.variable("envTemp", &envTemp);
  rest.variable("envHumidity", &envHumidity);
  rest.variable("envHeatIndex", &envHeatIndex);

  rest.variable("PH", &PH);
  rest.variable("EC", &EC);
  rest.variable("TDS", &TDS);
  rest.variable("SAL", &SAL);
  rest.variable("SG", &SG);
  rest.variable("DO_mgL", &DO_mgL);
  rest.variable("DO_PER", &DO_PER);
  rest.variable("ORP", &ORP);

  rest.variable("resTemp", &resTemp);

  sensors.begin();
}

void loop() {

  digitalWrite(LED_BUILTIN, HIGH);

  EthernetClient client = server.available();
  rest.handle(client);

  sensors.requestTemperatures();
  readResTemp();

  readTempHumidity();

  readProbe(PH_ID, &PH);
  readProbe(EC_ID, NULL);
  readProbe(DO_ID, NULL);
  readProbe(ORP_ID, &ORP);

  digitalWrite(LED_BUILTIN, LOW);
}

void readResTemp() {
  debug("Reading OneWire temperatures");
  resTemp = sensors.getTempFByIndex(0);

  if(HYDRO_DEBUG) {
    Serial.print("Res Temp: ");
    Serial.println(resTemp);
  }
}

void readTempHumidity() {

  debug("Reading environment temp, humidity, & heat index");
  envTemp = envDHT.readTemperature(true);
  envHumidity = envDHT.readHumidity();
  envHeatIndex = envDHT.computeHeatIndex(envTemp, envHumidity);

  if(HYDRO_DEBUG) {
    Serial.print("Environment Temp: ");
    Serial.println(envTemp);
    Serial.print("Environment Humidity: ");
    Serial.println(envHumidity);
    Serial.print("Environment Heat Index: ");
    Serial.println(envHeatIndex);
  }
}

void readProbe(int channel, float *probe) {

  debug("Reading ISE probes");

  Wire.beginTransmission(channel);
  Wire.write('r');
  Wire.endTransmission();
  delay(1000);

  char sensordata[30];
  byte sensor_bytes_received = 0;
  byte code = 0;
  byte in_char = 0;

  sensor_bytes_received = 0;
  memset(sensordata, 0, sizeof(sensordata));

  Wire.requestFrom(channel, 48, 1);
  code = Wire.read();

  while(Wire.available()) {

    in_char = Wire.read();
    if (in_char == 0) {
      Wire.endTransmission();
      break;
    }
    else {
      sensordata[sensor_bytes_received] = in_char;
      sensor_bytes_received++;
    }
  }

  if(HYDRO_DEBUG) {
    switch (code) {                       // switch case based on what the response code is.
      case 1:                             // decimal 1  means the command was successful.
      Serial.println(sensordata);         // print the actual reading
      break;                              // exits the switch case.

      case 2:                             // decimal 2 means the command has failed.
      Serial.println("command failed");   // print the error
      break;                              // exits the switch case.

      case 254:                           // decimal 254  means the command has not yet been finished calculating.
      Serial.println("circuit not ready"); // print the error
      break;                              // exits the switch case.

      case 255:                           // decimal 255 means there is no further data to send.
      Serial.println("no data");          // print the error
      break;                              // exits the switch case.
    }
    Serial.print("[Sensordata] Channel: ");
    Serial.print(channel);
    Serial.print(", value: ");
    Serial.println(sensordata);
  }

  char * pch;

  if(channel == EC_ID) {
    pch = strtok(sensordata, ",");
    EC = atof(pch);
    TDS = atof(strtok(NULL, ","));
    SAL = atof(strtok(NULL, ","));
    SG = atof(strtok(NULL, ","));
    if(HYDRO_DEBUG) {
      Serial.print("EC: ");
      Serial.println(EC);
      Serial.print("TDS: ");
      Serial.println(TDS);
      Serial.print("SAL: ");
      Serial.println(SAL);
      Serial.print("SG: ");
      Serial.println(SG);
    }
    return;
  }
  else if (channel == DO_ID) {
    pch = strtok(sensordata, ",");
    DO_mgL = atof(pch);
    DO_PER = atof(strtok(NULL, ","));
    if(HYDRO_DEBUG) {
      Serial.print("DO mg/L: ");
      Serial.println(DO_mgL);
      Serial.print("DO Percent: ");
      Serial.println(DO_PER);
    }
    return;
  }
  else {
    *probe = atof(sensordata);
  }
}

void debug(String msg) {
  if(HYDRO_DEBUG) {
    Serial.println(msg);
  }
}
