#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdint.h>
#include <stdbool.h> 

/**
 * @brief This function allows to get the least significant byte.
 * @param val Value.
 * @param lsb Integer to save the least significant byte.
 * @return Status of the function.
*/
int(util_get_LSB)(uint16_t val, uint8_t *lsb);
/**
 * @brief This function allows to get the most significant byte.
 * @param val Value.
 * @param lsb Integer to save the most significant byte.
 * @return Status of the function.
*/
int(util_get_MSB)(uint16_t val, uint8_t *msb);
/**
 * @brief This function allows to call the sys_inb() with a value with 8 bits.
 * @param port Integer that holds the port.
 * @param value Integer to save the value received by the call.
 * @return Status of the function.
*/
int (util_sys_inb)(int port, uint8_t *value);

#endif
