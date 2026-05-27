/******************************************************************************
 * File Name    : esp01.h
 * Description  : ESP8266 WiFi module function declarations
 ******************************************************************************/

#ifndef _ESP01_H_
#define _ESP01_H_

// Connect ESP8266 to WiFi Access Point
void esp01_connectAP(void);

// Send humidity and temperature data to ThingSpeak
void esp01_sendToThingspeak1(float,float);

// Send humidity data to ThingSpeak
void esp01_sendToThingspeak2(float);

// Send motor status data to ThingSpeak
void esp01_sendToThingspeak3(float);

#endif