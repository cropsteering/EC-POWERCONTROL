/**
 * @file MQTT.h
 * @author Jamie Howse (r4wknet@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __MQTT_H__
#define __MQTT_H__

#include <map>
#include <vector>

/**
 * @brief MQTT Lib
 * 
 */
class MQTT
{
    public:
    void mqtt_setup();
    void mqtt_loop();
    void mqtt_publish(String addr, String data);
};

/** Overloads for config */
extern bool CSV;
extern const char* MQTT_ID;

void pin_on(uint8_t pin);
void pin_off(uint8_t pin);
void pin_fail();

#endif
