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

#define ONE_WIRE_BUS 5
#define DHT_ENV_PIN  7
#define RO_SOLENOID_PIN 8

extern int  __bss_end;
extern int  *__brkval;

const char json_bracket_open[] = "{";
const char json_bracket_close[] = "}";

const char string_initializing[] PROGMEM = "Initializing CropDroid reservoir controller...";
const char string_dhcp_failed[] PROGMEM = "DHCP Failed";
const char string_http_200[] PROGMEM = "HTTP/1.1 200 OK";
const char string_http_404[] PROGMEM = "HTTP/1.1 404 Not Found";
const char string_http_500[] PROGMEM = "HTTP/1.1 500 Internal Server Error";
const char string_http_content_type_json[] PROGMEM = "Content-Type: application/json";
const char string_http_xpowered_by[] PROGMEM = "X-Powered-By: CropDroid v1.0";
const char string_rest_address[] PROGMEM = "REST service listening on: ";
const char string_json_key_mem[] PROGMEM = "\"mem\":";
const char string_json_key_envTemp[] PROGMEM = ",\"envTemp\":";
const char string_json_key_envHumidity[] PROGMEM = ",\"envHumidity\":";
const char string_json_key_envHeatIndex[] PROGMEM = ",\"envHeatIndex\":";
const char string_json_key_ph[] PROGMEM = ",\"PH\":";
const char string_json_key_ec[] PROGMEM = ",\"EC\":";
const char string_json_key_tds[] PROGMEM = ",\"TDS\":";
const char string_json_key_sal[] PROGMEM = ",\"SAL\":";
const char string_json_key_sg[] PROGMEM = ",\"SG\":";
const char string_json_key_do_mgl[] PROGMEM = ",\"DO_mgL\":";
const char string_json_key_do_per[] PROGMEM = ",\"DO_PER\":";
const char string_json_key_orp[] PROGMEM = ",\"ORP\":";
const char string_json_key_resTemp[] PROGMEM = ",\"resTemp\":";
const char string_json_key_pin[] PROGMEM = "\"pin\":";
const char string_json_key_position[] PROGMEM =  ",\"position\":";
const char string_json_key_value[] PROGMEM =  ",\"value:\"";
const char string_json_key_address[] PROGMEM =  "\"address\":";
const char string_json_bracket_open[] PROGMEM = "{";
const char string_json_bracket_close[] PROGMEM = "}";
const char string_json_reboot_true PROGMEM = "{\"reboot\":true}";
const char string_json_reset_true PROGMEM = "{\"reset\":true}";
const char * const string_table[] PROGMEM = {
  string_initializing,
  string_dhcp_failed,
  string_http_200,
  string_http_404,
  string_http_500,
  string_http_content_type_json,
  string_http_xpowered_by,
  string_rest_address,
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
  string_json_key_pin,
  string_json_key_position,
  string_json_key_value,
  string_json_key_address,
  string_json_bracket_open,
  string_json_bracket_close,
  string_json_reboot_true,
  string_json_reset_true
};
int idx_initializing = 0,
    idx_dhcp_failed = 1,
	idx_http_200 = 2,
	idx_http_404 = 3,
	idx_http_500 = 4,
	idx_http_content_type_json = 5,
	idx_http_xpowered_by = 6,
	idx_rest_address = 7,
	idx_json_key_mem = 8,
	idx_json_key_envTemp = 9,
	idx_json_key_envHumidity = 10,
	idx_json_key_envHeatIndex = 11,
	idx_json_key_ph = 12,
	idx_json_key_ec = 13,
	idx_json_key_tds = 14,
	idx_json_key_sal = 15,
	idx_json_key_sg = 16,
	idx_json_key_do_mgl = 17,
	idx_json_key_do_per = 18,
	idx_json_key_orp = 19,
	idx_json_key_resTemp = 20,
	idx_json_key_pin = 21,
	idx_json_key_position = 22,
	idx_json_key_value = 23,
	idx_json_key_address = 24,
	idx_json_key_bracket_open = 25,
	idx_json_key_bracket_close = 26,
	idx_json_reboot_true = 27,
	idx_json_reset_true = 28;
char string_buffer[50];
char float_buffer[10];

DHT envDHT(DHT_ENV_PIN, DHT22);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//byte mac[] = { 0x04, 0x02, 0x00, 0x00, 0x00, 0x02 };
//IPAddress ip(192,168,0,102);

float envTemp, envHumidity, envHeatIndex,
      PH, EC, TDS, SAL, SG, DO_mgL, DO_PER, ORP = 0.0,
	  pod0Temp, pod1Temp, resTemp;

int EC_ID = 100, PH_ID = 99, DO_ID = 97, ORP_ID = 98, systemTemp = 0;

void readProbe(int channel, float *probe);
void readTempHumidity();
void readResTemp();
void debug(String msg);
void startRO();
void stopRO();
void handleWebRequest();
void send404();
void resetDefaults();
int availableMemory();
void(* resetFunc) (void) = 0;

byte defaultMac[] = { 0x04, 0x02, 0x00, 0x04, 0x02, 0x02 };

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

  Wire.begin();
  envDHT.begin();
  sensors.begin();

  analogReference(DEFAULT);

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

  digitalWrite(LED_BUILTIN, HIGH);

  handleWebRequest();

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

  if(DEBUG) {
    Serial.print("Res Temp: ");
    Serial.println(resTemp);
  }
}

void readTempHumidity() {

  debug("Reading environment temp, humidity, & heat index");
  envTemp = envDHT.readTemperature(true);
  envHumidity = envDHT.readHumidity();
  envHeatIndex = envDHT.computeHeatIndex(envTemp, envHumidity);

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

void startRO() {
	digitalWrite(RO_SOLENOID_PIN, HIGH);
}
void stopRO() {
	digitalWrite(RO_SOLENOID_PIN, LOW);
}

void debug(String msg) {
  if(DEBUG) {
    Serial.println(msg);
  }
}

void handleWebRequest() {

	httpClient = httpServer.available();

	char clientline[BUFSIZE];
	int index = 0;

	bool reboot = false;
	char json[275];
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

				// /status
				if (strncmp(resource, "status", 6) == 0) {

					strcpy(json, json_bracket_open);

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
					  itoa(resTemp, float_buffer, 10);
					  strcat(json, float_buffer);

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

				// /reboot
				else if (strncmp(resource, "reboot", 6) == 0) {
					#if DEBUG
						Serial.println("/reboot");
					#endif
					strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_reboot_true])));
					strcat(json, string_buffer);
					reboot = true;
				}

				// /reset
				else if (strncmp(resource, "reset", 5) == 0) {
					#if DEBUG
						Serial.println("/reset");
					#endif

					resetDefaults();

					strcpy_P(string_buffer, (char*)pgm_read_word(&(string_table[idx_json_reset_true])));
					strcat(json, string_buffer);
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
