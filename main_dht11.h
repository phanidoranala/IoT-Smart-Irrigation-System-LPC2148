/******************************************************************************
 * File Name    : main_dht11.h
 * Description  : Function declarations for Smart Irrigation project
 ******************************************************************************/

#ifndef __MAIN_DHT11_H__
#define __MAIN_DHT11_H__

// Display DHT11 sensor values on LCD
void dht11_display(void);

// Initialize RTC timing values
void rtc_init(void);

// Compare temperature and humidity values
// and control irrigation motor
void compare_temp_hum(void);

// Interrupt based menu handling function
void menu_base_int(void);

// Configure irrigation motor timings
void SetIrrigationTiming(void);

// Configure temperature and humidity threshold values
void Set_Temp_Humidity(void);

#endif