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
#include <set>

/** MQTT Lib */
MQTT mqtt_lib;
/** Tracked pins */
std::set<uint8_t> tracked_pins;
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

/**
 * @brief Turn on pin and track for fail safe
 * 
 * @param pin 
 */
void pin_on(uint8_t pin)
{
  R_LOG("PC", "Pin " + String(pin) + " on");
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  /** Keep track of all pins used for fail safe */
  bool found = tracked_pins.find(pin) != tracked_pins.end();
  if(!found)
  {
    R_LOG("PC", "Added tracked pin " + String(pin));
    tracked_pins.insert(pin);
  }
}

/**
 * @brief Turn pin off
 * 
 * @param pin 
 */
void pin_off(uint8_t pin)
{
  R_LOG("PC", "Pin " + String(pin) + " off");
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

/**
 * @brief Fail safe for tracked pins
 * 
 */
void pin_fail()
{
  for (auto& str : tracked_pins)
  {
    digitalWrite(str, LOW);
  }
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
