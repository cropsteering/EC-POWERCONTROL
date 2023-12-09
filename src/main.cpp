/**
 * @file main.cpp
 * @author Jamie Howse (r4wknet@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/** Include libraries here */
#include <Arduino.h>
#include <MQTT.h>

/** MQTT Lib */
MQTT mqtt_lib;
/** Turn on/off debug output */
#define DEBUG 1

/** Forward declaration */
void R_LOG(String chan, String data);

/**
 * @brief Main setup
 * 
 */
void setup() 
{
  R_LOG("PC", "Edge power control");
  time_t timeout = millis();
  Serial.begin(115200);
  while (!Serial)
  {
    if ((millis() - timeout) < 5000)
    {
        delay(100);
    } else {
        break;
    }
  }

  /** Join WiFi and connect to MQTT */
  mqtt_lib.mqtt_setup();
}

/**
 * @brief Main loop
 * 
 */
void loop() 
{
  /** Loop our MQTT lib */
  mqtt_lib.mqtt_loop();
}

void pin_on(uint8_t pin)
{
  R_LOG("PC", "Pin " + String(pin) + " on");
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
}

void pin_off(uint8_t pin)
{
  R_LOG("PC", "Pin " + String(pin) + " off");
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

/**
 * @brief 
 * 
 * @param chan Output channel
 * @param data String to output
 */
void R_LOG(String chan, String data)
{
  #if DEBUG
  String disp = "["+chan+"] " + data;
  Serial.println(disp);
  #endif
}
