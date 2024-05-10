#ifndef __RTC_H__
#define __RTC_H__
#include <stdint.h>

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71
#define RTC_IRQ 8

#define RTC_SECONDS_ADDRESS 0
#define RTC_SECONDS_ALARM_ADDRESS 1
#define RTC_MINUTES_ADDRESS 2
#define RTC_MINUTES_ALARM_ADDRESS 3
#define RTC_HOURS_ADDRESS 4
#define RTC_HOURS_ALARM_ADDRESS 5
#define RTC_DAY_OF_WEEK_ADDRESS 6
#define RTC_DAY_OF_MONTH_ADDRESS 7
#define RTC_MONTH_ADDRESS 8
#define RTC_YEAR_ADDRESS 9
#define RTC_REGISTER_A 10
#define RTC_REGISTER_B 11
#define RTC_REGISTER_C 12
#define RTC_REGISTER_D 13

#define RTC_UF BIT(4)
#define RTC_AF BIT(5)
#define RTC_PF BIT(6)

//Functions
/**
 * @brief This function allows to subscribe the interupt for the RTC.
 * @param bit_no Integer to save the address.
 * @return Status of the function.
*/
int rtc_subscribe_int(uint8_t *bit_no);
/**
 * @brief This function allows to unsubscribe the interupt for the mouse.
*/
int rtc_unsubscribe_int();
/**
 * @brief This function allows to read a register from the RTC.
 * @param address Address of the register.
 * @param data Integer to save the response from the register.
 * @return Status of the function.
*/
int rtc_read_register(uint8_t address, uint8_t *data);
/**
 * @brief This function allows to set a register of the RTC.
 * @param address Address of the register.
 * @param data Integer that holds the data.
 * @return Status of the function.
*/
int rtc_set_register(uint8_t address, uint8_t data);
/**
 * @brief This function allows to read the time from the RTC.
 * @param string Array that holds the time.
 * @return Status of the function.
*/
int rtc_read_time(char *string);

#endif
