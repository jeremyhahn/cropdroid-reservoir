// SPDX-License-Identifier: AGPL-3.0-or-later
// SPDX-License-Identifier: commercial

#include <Arduino.h>
#include <SPI.h>
#include "Ethernet.h"
#include "DHT.h"
#include <Wire.h>
#include "OneWire.h"
#include "DallasTemperature.h"
#include "EEPROM.h"

#define DEBUG 1
#define EEPROM_DEBUG 1
#define BUFSIZE 255
#define CHANNEL_SIZE 16

#define ONE_WIRE_BUS 38
#define DHT_ENV_PIN  41
//#define UPPER_FLOAT A0
//#define LOWER_FLOAT A1

#define UPPER_FLOAT A14
#define LOWER_FLOAT A15

extern int  __bss_end;
extern int  *__brkval;

const char json_bracket_open[] = "{";
const char json_bracket_close[] = "}";
const char json_array_bracket_close[] = "]";
const char json_comma[] = ",";

const char string_initializing[] PROGMEM = "Initializing reservoir...";
const char string_dhcp_failed[] PROGMEM = "DHCP Failed";
const char string_http_200[] PROGMEM = "HTTP/1.1 200 OK";
const char string_http_404[] PROGMEM = "HTTP/1.1 404 Not Found";
const char string_http_500[] PROGMEM = "HTTP/1.1 500 Internal Server Error";
const char string_http_content_type_json[] PROGMEM = "Content-Type: application/json";
const char string_http_xpowered_by[] PROGMEM = "X-Powered-By: CropDroid";
const char string_rest_address[] PROGMEM = "REST service listening on: ";
const char string_switch_on[] PROGMEM = "Switching on";
const char string_switch_off[] PROGMEM = "Switching off";
const char string_json_key_metrics[] PROGMEM = "\"metrics\":{";
const char string_json_key_mem[] PROGMEM = "\"mem\":";
const char string_json_key_envTemp[] PROGMEM = ",\"envTemp\":";
const char string_json_key_envHumidity[] PROGMEM = ",\"envHumidity\":";
const char string_json_key_envHeatIndex[] PROGMEM = ",\"envHeatIndex\":";
const char string_json_key_ph[] PROGMEM = ",\"ph\":";
const char string_json_key_ec[] PROGMEM = ",\"ec\":";
const char string_json_key_tds[] PROGMEM = ",\"tds\":";
const char string_json_key_sal[] PROGMEM = ",\"sal\":";
const char string_json_key_sg[] PROGMEM = ",\"sg\":";
const char string_json_key_do_mgl[] PROGMEM = ",\"do_mgL\":";
const char string_json_key_do_per[] PROGMEM = ",\"do_per\":";
const char string_json_key_orp[] PROGMEM = ",\"orp\":";
const char string_json_key_resTemp[] PROGMEM = ",\"resTemp\":";
const char string_json_key_upperFloat[] PROGMEM = ",\"upperFloat\":";
const char string_json_key_lowerFloat[] PROGMEM = ",\"lowerFloat\":";
const char string_json_key_channels[] PROGMEM = ",\"channels\":[";
const char string_json_key_channel[] PROGMEM = "\"channel\":";
const char string_json_key_pin[] PROGMEM = ",\"pin\":";
const char string_json_key_position[] PROGMEM =  ",\"position\":";
const char string_json_key_value[] PROGMEM =  ",\"value\":";
const char string_json_key_address[] PROGMEM =  "\"address\":";
const char string_json_bracket_open[] PROGMEM = "{";
const char string_json_bracket_close[] PROGMEM = "}";
const char string_json_error_invalid_channel[] PROGMEM = "\"error\":\"Invalid channel\"";
const char string_json_reboot_true PROGMEM = "\"reboot\":true";
const char string_json_reset_true PROGMEM = "\"reset\":true";
const char string_hardware_version[] PROGMEM = "\"hardware\":\"res-v0.1b\",";
const char string_firmware_version[] PROGMEM = "\"firmware\":\"1.0.0b\"";
const char string_json_key_uptime[] PROGMEM = ",\"uptime\":";
const char * const string_table[] PROGMEM = {
  string_initializing,
  string_dhcp_failed,
  string_http_200,
  string_http_404,
  string_http_500,
  string_http_content_type_json,
  string_http_xpowered_by,
  string_rest_address,
  string_switch_on,
  string_switch_off,
  string_json_key_metrics,
  string_json_key_mem,
  string_json_key_envTemp,
  string_json_key_envHumidity,
  string_json_key_envHeatIndex,
  string_json_key_ph,
  string_json_key_ec,
  string_json_key_tds,
  string_json_key_sal,
  string_json_key_sg,
  string_json_key_do_mgl,
  string_json_key_do_per,
  string_json_key_orp,
  string_json_key_resTemp,
  string_json_key_upperFloat,
  string_json_key_lowerFloat,
  string_json_key_channels,
  string_json_key_channel,
  string_json_key_pin,
  string_json_key_position,
  string_json_key_value,
  string_json_key_address,
  string_json_bracket_open,
  string_json_bracket_close,
  string_json_error_invalid_channel,
  string_json_reboot_true,
  string_json_reset_true,
  string_hardware_version,
  string_firmware_version,
  string_json_key_uptime
};
int idx_initializing = 0,
    idx_dhcp_failed = 1,
	idx_http_200 = 2,
	idx_http_404 = 3,
	idx_http_500 = 4,
	idx_http_content_type_json = 5,
	idx_http_xpowered_by = 6,
	idx_rest_address = 7,
	idx_switch_on = 8,
	idx_switch_off = 9,
	idx_json_key_metrics = 10,
	idx_json_key_mem = 11,
	idx_json_key_envTemp = 12,
	idx_json_key_envHumidity = 13,
	idx_json_key_envHeatIndex = 14,
	idx_json_key_ph = 15,
	idx_json_key_ec = 16,
	idx_json_key_tds = 17,
	idx_json_key_sal = 18,
	idx_json_key_sg = 19,
	idx_json_key_do_mgl = 20,
	idx_json_key_do_per = 21,
	idx_json_key_orp = 22,
	idx_json_key_resTemp = 23,
	idx_json_key_upperFloat = 24,
	idx_json_key_lowerFloat = 25,
	idx_json_key_channels = 26,
	idx_json_key_channel = 27,
	idx_json_key_pin = 28,
	idx_json_key_position = 29,
	idx_json_key_value = 30,
	idx_json_key_address = 31,
	idx_json_key_bracket_open = 32,
	idx_json_key_bracket_close = 33,
	idx_json_error_invalid_channel = 34,
	idx_json_reboot_true = 35,
	idx_json_reset_true = 36,
	idx_hardware_version = 37,
	idx_firmware_version = 38,
	idx_json_key_uptime = 39;
char string_buffer[60];
char float_buffer[10];

const int NULL_CHANNEL = 255;
const uint8_t channels[CHANNEL_SIZE] = {
	22, 23, 24, 25, 26, 27, 28, 29,
	30, 31, 32, 33, 34, 35, 36, 37
};
unsigned long channel_table[CHANNEL_SIZE][3] = {
	// channel, start, interval
   {NULL_CHANNEL, 0, 0},
   {NULL_CHANNEL, 0, 0},
   {NULL_CHANNEL, 0, 0},
   {NULL_CHANNEL, 0, 0},
   {NULL_CHANNEL, 0, 0},
   {NULL_CHANNEL, 0, 0},
   {NULL_CHANNEL, 0, 0},
   {NULL_CHANNEL, 0, 0},
   {NULL_CHANNEL, 0, 0},
   {NULL_CHANNEL, 0, 0},
   {NULL_CHANNEL, 0, 0},
   {NULL_CHANNEL, 0, 0},
   {NULL_CHANNEL, 0, 0},
   {NULL_CHANNEL, 0, 0},
   {NULL_CHANNEL, 0, 0},
   {NULL_CHANNEL, 0, 0}
};

DHT envDHT(DHT_ENV_PIN, DHT22);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float envTemp, envHumidity, envHeatIndex,
      PH, EC, TDS, SAL, SG, DO_mgL, DO_PER, ORP = 0.0,
	  pod0Temp, pod1Temp, resTemp;

int EC_ID = 100, PH_ID = 99, DO_ID = 97, ORP_ID = 98, systemTemp = 0;

void readProbe(int channel, float *probe);
void readTempHumidity();
void readResTemp();
void debug(String msg);
void switchOn(int pin);
void switchOff(int pin);
void handleActiveChannels();
void handleWebRequest();
void send404();
void resetDefaults();
int availableMemory();
void(* resetFunc) (void) = 0;

byte defaultMac[] = { 0x04, 0x02, 0x00, 0x00, 0x00, 0x02 };

byte mac[] = {
	EEPROM.read(0),
	EEPROM.read(1),
	EEPROM.read(2),
	EEPROM.read(3),
	EEPROM.read(4),
	EEPROM.read(5)
};
IPAddress ip(
  EEPROM.read(6),
  EEPROM.read(7),
  EEPROM.read(8),
  EEPROM.read(9));

EthernetServer httpServer(80);
EthernetClient httpClient;

int main(void) {
  init();
  setup();

  for (;;)
    loop();

  return 0;
}

void setup(void) {

  //EEPROM.write(0, 255);

  Wire.begin();
  envDHT.begin();
  sensors.begin();

  analogReference(DEFAULT);

  for(int i=0; i<CHANNEL_SIZE; i++) {
    pinMode(channels[i], OUTPUT);
    digitalWrite(channels[i], LOW);
  }
  pinMode(UPPER_FLOAT, INPUT_PULLUP);
  pinMode(LOWER_FLOAT, INPUT_PULLUP);
  //pinMode(UPPER_FLOAT, INPUT);
  //pinMode(LOWER_FLOAT, INPUT);

  #if DEBUG || EEPROM_DEBUG
    Serial.begin(115200);

    strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_initializing])));
    Serial.println(string_buffer);
  #endif

  byte macByte1 = EEPROM.read(0);

  #if DEBUG || EEPROM_DEBUG
    Serial.print("EEPROM.read(0): ");
    Serial.println(macByte1);
  #endif

  if(macByte1 == 255) {
	resetDefaults();
    if(Ethernet.begin(defaultMac) == 0) {
	  #if DEBUG
	    strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_dhcp_failed])));
		Serial.println(string_buffer);
	  #endif
	  return;
	}
  }
  else {
    Ethernet.begin(mac, ip);
  }

  #if DEBUG || EEPROM_DEBUG
    Serial.print("MAC: ");
    for(int i=0; i<6; i++) {
      Serial.print(mac[i], HEX);
    }
    Serial.println();

    strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_rest_address])));
    Serial.print(string_buffer);
    Serial.println(Ethernet.localIP());
  #endif

    httpServer.begin();
}

void loop() {

  handleActiveChannels();
  handleWebRequest();

  sensors.requestTemperatures();
  readResTemp();
  readTempHumidity();
  handleActiveChannels();
  handleWebRequest();

  readProbe(PH_ID, &PH);
  handleActiveChannels();
  handleWebRequest();

  readProbe(EC_ID, NULL);
  handleActiveChannels();
  handleWebRequest();

  readProbe(DO_ID, NULL);
  handleActiveChannels();
  handleWebRequest();

  readProbe(ORP_ID, &ORP);
  handleActiveChannels();
  handleWebRequest();
}

void readResTemp() {
  debug("Reading OneWire temperatures");
  resTemp = sensors.getTempFByIndex(0);

  if(DEBUG) {
    Serial.print("Res Temp: ");
    Serial.println(resTemp);
  }
}

float zeroIfNan(float number) {
  if(isnan(number)) {
	number = 0.0;
  }
  return number;
}

void readTempHumidity() {

  debug("Reading environment temp, humidity, & heat index");
  envTemp = zeroIfNan(envDHT.readTemperature(true));
  envHumidity = zeroIfNan(envDHT.readHumidity());
  envHeatIndex = zeroIfNan(envDHT.computeHeatIndex(envTemp, envHumidity));

  if(DEBUG) {
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

  if(DEBUG) {
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
    if(DEBUG) {
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
    if(DEBUG) {
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

void switchOn(int pin) {
#if DEBUG
  char sPin[3];
  itoa(pin, sPin, 10);
  strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_switch_on])));
  strcat(string_buffer, " pin ");
  strcat(string_buffer, sPin);
  Serial.println(string_buffer);
#endif
  digitalWrite(pin, HIGH);
}

void switchOff(int pin) {
#if DEBUG
  char sPin[3];
  itoa(pin, sPin, 10);
  strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_switch_off])));
  strcat(string_buffer, " pin ");
  strcat(string_buffer, sPin);
  Serial.println(string_buffer);
#endif
  digitalWrite(pin, LOW);
}

void debug(String msg) {
  if(DEBUG) {
    Serial.println(msg);
  }
}

void handleActiveChannels() {
	unsigned long currentMillis = millis();

	for(int i=0; i<CHANNEL_SIZE; i++) {
		if(channel_table[i][0] != NULL_CHANNEL) {
			if(currentMillis - channel_table[i][1] > channel_table[i][2]) {

				digitalWrite(channel_table[i][0], LOW);

				#if DEBUG
				  Serial.print("Turning channel ");
				  Serial.print(i);
				  Serial.print(" (pin ");
				  Serial.print(channel_table[i][0]);
				  Serial.print(") off after ");
				  Serial.print(channel_table[i][2] / 1000);
				  Serial.println(" seconds");
				#endif

				channel_table[i][0] = NULL_CHANNEL;
				channel_table[i][1] = 0;
				channel_table[i][2] = 0;
			}
		}
	}
}

void handleWebRequest() {

	httpClient = httpServer.available();

	char clientline[BUFSIZE] = {0};
	int index = 0;

	bool reboot = false;
	char json[500];
	char sPin[3];
	char state[3];

	if (httpClient) {

		// reset input buffer
		index = 0;

		while (httpClient.connected()) {

			if (httpClient.available()) {

				char c = httpClient.read();
				if (c != '\n' && c != '\r' && index < BUFSIZE) {
					clientline[index++] = c;
					continue;
				}

				httpClient.flush();

				String urlString = String(clientline);
				String op = urlString.substring(0, urlString.indexOf(' '));
				urlString = urlString.substring(urlString.indexOf('/'), urlString.indexOf(' ', urlString.indexOf('/')));
				urlString.toCharArray(clientline, BUFSIZE);

				char *resource = strtok(clientline, "/");
				char *param1 = strtok(NULL, "/");
				char *param2 = strtok(NULL, "/");

				#if DEBUG
				  Serial.print("Resource: ");
				  Serial.println(resource);

				  Serial.print("Parm1: ");
				  Serial.println(param1);

				  Serial.print("Param2: ");
				  Serial.println(param2);
				#endif

				// /state
				if (strncmp(resource, "state", 5) == 0) {

					strcpy(json, json_bracket_open);

					  strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_metrics])));
					  strcat(json, string_buffer);

					    strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_mem])));
					    strcat(json, string_buffer);
					    itoa(availableMemory(), float_buffer, 10);
					    strcat(json, float_buffer);

					    strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_envTemp])));
					    strcat(json, string_buffer);
					    dtostrf(envTemp, 4, 2, float_buffer);
					    strcat(json, float_buffer);

					    strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_envHumidity])));
					    strcat(json, string_buffer);
					    dtostrf(envHumidity, 4, 2, float_buffer);
					    strcat(json, float_buffer);

					    strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_envHeatIndex])));
					    strcat(json, string_buffer);
                      	dtostrf(envHeatIndex, 4, 2, float_buffer);
                      	strcat(json, float_buffer);

                      	strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_ph])));
                      	strcat(json, string_buffer);
                      	dtostrf(PH, 4, 2, float_buffer);
                      	strcat(json, float_buffer);

                      	strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_ec])));
                      	strcat(json, string_buffer);
                      	dtostrf(EC, 4, 2, float_buffer);
                      	strcat(json, float_buffer);

                      	strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_tds])));
                      	strcat(json, string_buffer);
                      	dtostrf(TDS, 4, 2, float_buffer);
                      	strcat(json, float_buffer);

                      	strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_sal])));
                      	strcat(json, string_buffer);
                      	dtostrf(SAL, 4, 2, float_buffer);
                      	strcat(json, float_buffer);

                      	strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_sg])));
                      	strcat(json, string_buffer);
                      	dtostrf(SG, 4, 2, float_buffer);
                      	strcat(json, float_buffer);

                      	strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_do_mgl])));
                      	strcat(json, string_buffer);
                      	itoa(DO_mgL, float_buffer, 10);
                      	strcat(json, float_buffer);

                      	strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_do_per])));
                      	strcat(json, string_buffer);
                      	itoa(DO_PER, float_buffer, 10);
                      	strcat(json, float_buffer);

                      	strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_orp])));
                      	strcat(json, string_buffer);
                      	itoa(ORP, float_buffer, 10);
                      	strcat(json, float_buffer);

                      	strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_resTemp])));
                      	strcat(json, string_buffer);
                      	dtostrf(resTemp, 4, 2, float_buffer);
                      	strcat(json, float_buffer);

                      	strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_upperFloat])));
                      	strcat(json, string_buffer);
                      	dtostrf(analogRead(UPPER_FLOAT), 4, 2, float_buffer);
                      	strcat(json, float_buffer);

                      	strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_lowerFloat])));
                      	strcat(json, string_buffer);
                      	dtostrf(analogRead(LOWER_FLOAT), 4, 2, float_buffer);
                      	strcat(json, float_buffer);

					  strcat(json, json_bracket_close);

                      strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_channels])));
                      strcat(json, string_buffer);
						for(int i=0; i<CHANNEL_SIZE; i++) {
						  itoa(digitalRead(channels[i]), state, 10);
						  strcat(json, state);
						  if(i + 1 < CHANNEL_SIZE) {
						    strcat(json, ",");
						  }
						}
					  strcat(json, json_array_bracket_close);

					strcat(json, json_bracket_close);
				}

				// /eeprom
				else if (strncmp(resource, "eeprom", 6) == 0) {
					#if EEPROM_DEBUG
						Serial.println("/eeprom");
						Serial.println(param1);
						Serial.println(param2);
					#endif

					EEPROM.write(atoi(param1), atoi(param2));

					strcpy(json, json_bracket_open);

					  strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_address])));
					  strcat(json, string_buffer);
					  strcat(json, param1);

					  strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_value])));
					  strcat(json, string_buffer);
					  strcat(json, param2);

					strcat(json, json_bracket_close);
				}

				// /timer/{channel}/{seconds}
				else if (strncmp(resource, "timer", 5) == 0) {

					if(param1 == NULL || param1 == "") {
						Serial.println("parameter required");
						//send500("parameter required");
						break;
					}

					int channel = atoi(param1);
					unsigned long duration = strtoul(param2, NULL, 10);

					if(channel >= 0 && channel < CHANNEL_SIZE && duration > 0) {

						#if DEBUG
						  Serial.print("Channel: ");
						  Serial.println(channel);

						  Serial.print("Duration: ");
						  Serial.println(duration);
						#endif

						channel_table[channel][0] = channels[channel];
						channel_table[channel][1] = millis();
						channel_table[channel][2] = duration * 1000;

						digitalWrite(channels[channel], HIGH);
					}
					else {
					  #if DEBUG
						Serial.println("Invalid channel/duration");
					  #endif
					}

					strcpy(json, "{");

						strcat(json, "\"channel\":");
						itoa(channel, float_buffer, 10);
						strcat(json, float_buffer);

						strcat(json, ",\"duration\":");
						itoa(duration, float_buffer, 10);
						strcat(json, float_buffer);

					strcat(json, "}");
				}

				// /switch/{channel}/{position}     1 = on, else off
				else if (strncmp(resource, "switch", 6) == 0) {

					bool valid = false;
					int channel = atoi(param1);
					int position = atoi(param2);

					if(channel >= 0 && channel < CHANNEL_SIZE) {
						valid = true;
					}

					if(valid) {

						position == 1 ? switchOn(channels[channel]) : switchOff(channels[channel]);

						strcpy(json, json_bracket_open);

						  strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_channel])));
						  strcat(json, string_buffer);
						  strcat(json, param1);

						  strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_pin])));
						  strcat(json, string_buffer);
						  itoa(channels[channel], string_buffer, 10);
						  strcat(json, string_buffer);

						  strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_position])));
						  strcat(json, string_buffer);
						  itoa(digitalRead(channels[channel]), string_buffer, 10);
						  strcat(json, string_buffer);

						strcat(json, json_bracket_close);

						#if DEBUG
							Serial.print("/switch: ");
							Serial.println(json);
						#endif

					}
					else {
						strcpy(json, json_bracket_open);
							strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_error_invalid_channel])));
							strcat(json, string_buffer);
						strcat(json, json_bracket_close);
					}
				}

				// /reboot
				else if (strncmp(resource, "reboot", 6) == 0) {
					#if DEBUG
						Serial.println("/reboot");
					#endif

					strcpy(json, json_bracket_open);
						strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_reboot_true])));
						strcat(json, string_buffer);
					strcat(json, json_bracket_close);

					reboot = true;
				}

				// /reset
				else if (strncmp(resource, "reset", 5) == 0) {
					#if DEBUG
						Serial.println("/reset");
					#endif

					resetDefaults();

					strcpy(json, json_bracket_open);
						strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_reset_true])));
						strcat(json, string_buffer);
					strcat(json, json_bracket_close);

					reboot = true;
				}

				// /sys
				else if (strncmp(resource, "system", 6) == 0) {

					strcpy(json, json_bracket_open);

						strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_hardware_version])));
						strcat(json, string_buffer);

						strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_firmware_version])));
						strcat(json, string_buffer);

						strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_key_uptime])));
						strcat(json, string_buffer);
						itoa(millis(), string_buffer, 10);
						strcat(json, string_buffer);

					strcat(json, json_bracket_close);
				}

				else {
					send404();
					break;
				}

				strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_http_200])));
				httpClient.println(string_buffer);

				//httpClient.println("Access-Control-Allow-Origin: *");

				strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_http_xpowered_by])));
				httpClient.println(string_buffer);

				strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_http_content_type_json])));
				httpClient.println(string_buffer);

				httpClient.println();
				httpClient.println(json);

				break;
			}
		}
	}

	// give the web browser time to receive the data
	delay(100);

	// close the connection:
	httpClient.stop();

	if(reboot)  {
	  resetFunc();
	}
}

void send404() {

	strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_http_404])));
	httpClient.println(string_buffer);

	#if DEBUG
	  Serial.println(string_buffer);
	#endif

	strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_http_xpowered_by])));
	httpClient.println(string_buffer);

	httpClient.println();
}

void resetDefaults() {
	EEPROM.write(0, defaultMac[0]);
	EEPROM.write(1, defaultMac[1]);
	EEPROM.write(2, defaultMac[2]);
	EEPROM.write(3, defaultMac[3]);
	EEPROM.write(4, defaultMac[4]);
	EEPROM.write(5, defaultMac[5]);
	EEPROM.write(6, 192);
	EEPROM.write(7, 168);
	EEPROM.write(8, 0);
	EEPROM.write(9, 92);
}

int availableMemory() {
  int free_memory;
  return ((int) __brkval == 0) ? ((int) &free_memory) - ((int) &__bss_end) :
      ((int) &free_memory) - ((int) __brkval);
}
