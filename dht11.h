/******************************************************************************
 * File Name    : dht11.h
 * Description  : DHT11 sensor function declarations
 ******************************************************************************/

#ifndef _DHT11_H_
#define _DHT11_H_

// Send request signal to DHT11 sensor
void dht11_request(void);

// Wait for DHT11 response
void dht11_response(void);

// Read 8-bit data from DHT11 sensor
unsigned char dht11_data(void);

#endif