

#include "ESPConfigurationWizard.hpp"


PubSubClient* _mqttClinet;
ESPConfigurationWizard _ESPConfigurationWizard;

void setup() {
  Serial.begin(57600);
  
  Config* config = _ESPConfigurationWizard.getConfigPt();
  config->addOption("DeviceName","ESPConfigurationWizard", false);
  config->addOption("Key","", false);
  config->addOption("Taste","", true);


  _ESPConfigurationWizard.setOnFilterOption(onFilterOption);
  _ESPConfigurationWizard.setOnStatusCallback(onStatusCallback);
  // connection mode. If there is no value required for connection, it automatically switches to configuration mode.
   _mqttClinet = _ESPConfigurationWizard.pubSubClient();
   _ESPConfigurationWizard.connect();

   
  Serial.println("printConfig");
  config->printConfig();
  Serial.println("printConfigEnd");
   
  // Enter configuration mode.
  // _ESPConfigurationWizard.startConfigurationMode();
  
}

void onStatusCallback(int status) {
  if(status == STATUS_CONFIGURATION) {
      Serial.println("\n\nStart configuration mode");
    }
  else if(status == WIFI_CONNECT_TRY) {
    Serial.println("Try to connect to Wifi.");
  }
  else if(status == WIFI_ERROR) {
    Serial.println("WIFI connection error.");
  }
  else if(status == WIFI_CONNECTED) {
    Serial.println("WIFI connected.");
  }
  else if(status == NTP_CONNECT_TRY) {
    Serial.println("Try to connect to NTP Server.");
  }
  else if(status == NTP_ERROR) {
    Serial.println("NTP Server connection error.");
  }
  else if(status == NTP_CONNECTED) {
    Serial.println("NTP Server connected.");
  }
  else if(status == MQTT_CONNECT_TRY) {
    Serial.println("Try to connect to MQTT Server.");
  }
  else if(status == MQTT_ERROR) {
    Serial.println("MQTT Server connection error.");
  }
  else if(status == MQTT_CONNECTED) {
    Serial.println("MQTT Server connected.");
  }
  else if(status == STATUS_OK) {
    Serial.println("All connections are fine.");

    int day = _ESPConfigurationWizard.getDay();
   int hour = _ESPConfigurationWizard.getHours();
   int min = _ESPConfigurationWizard.getMinutes();
   int sec = _ESPConfigurationWizard.getSeconds();

    //_mqttClinet->setCallback(callbackSubscribe);
    //_mqttClinet->subscribe("topic");
  }

}

const char* onFilterOption(const char* name, const char* value) {
  if(strcmp(name, "DeviceName") == 0) {
      int valueLen = strlen(value);
      if(valueLen > 16) {
        return "Please enter 16 characters or less.";
      }      
      for(int i = 0; i < valueLen; ++i) {
        if( !(('0' <= value[i] && value[i] <= '9') || 
              ('A' <= value[i] && value[i] <= 'Z') || 
              ('a' <= value[i] && value[i] <= 'z') ) ) 
        {
          return "Only numbers or English alphabets can be entered.";
        }
      }
  }
  return "";

}

void loop() {
  _ESPConfigurationWizard.loop();
  if(_ESPConfigurationWizard.isConfigurationMode()) return;
  
}
