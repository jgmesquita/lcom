#ifndef _LCOM_I8254_H_
#define _LCOM_I8254_H_

#include <lcom/lcf.h>
#include <stdint.h>

/** @defgroup i8254 i8254
 *
 * Constants for programming the i8254 Timer. Needs to be completed.
 */

#define TIMER_FREQ 1193182 /**< @brief clock frequency for timer in PC and AT */
#define TIMER0_IRQ 0 /**< @brief Timer 0 IRQ line */

/* I/O port addresses */

#define TIMER_0    0x40 /**< @brief Timer 0 count register */
#define TIMER_1    0x41 /**< @brief Timer 1 count register */
#define TIMER_2    0x42 /**< @brief Timer 2 count register */
#define TIMER_CTRL 0x43 /**< @brief Control register */

#define SPEAKER_CTRL 0x61 /**< @brief Register for speaker control  */

/* Timer control */

/* Timer selection: bits 7 and 6 */

#define TIMER_SEL0   0x00              /**< @brief Control Word for Timer 0 */
#define TIMER_SEL1   BIT(6)            /**< @brief Control Word for Timer 1 */
#define TIMER_SEL2   BIT(7)            /**< @brief Control Word for Timer 2 */
#define TIMER_RB_CMD (BIT(7) | BIT(6)) /**< @brief Read Back Command */

/* Register selection: bits 5 and 4 */

#define TIMER_LSB     BIT(4)                  /**< @brief Initialize Counter LSB only */
#define TIMER_MSB     BIT(5)                  /**< @brief Initialize Counter MSB only */
#define TIMER_LSB_MSB (TIMER_LSB | TIMER_MSB) /**< @brief Initialize LSB first and MSB afterwards */

/* Operating mode: bits 3, 2 and 1 */

#define TIMER_SQR_WAVE (BIT(2) | BIT(1)) /**< @brief Mode 3: square wave generator */
#define TIMER_RATE_GEN BIT(2)            /**< @brief Mode 2: rate generator */

/* Counting mode: bit 0 */

#define TIMER_BCD 0x01 /**< @brief Count in BCD */
#define TIMER_BIN 0x00 /**< @brief Count in binary */

/* READ-BACK COMMAND FORMAT */

#define TIMER_RB_COUNT_  BIT(5)
#define TIMER_RB_STATUS_ BIT(4)
#define TIMER_RB_SEL(n)  BIT((n) + 1)

/* Functions */
/**
 * @brief This function allows to subscribe the interupt for the timer.
 * @param bit_no Integer to save the address.
 * @return Status of the function.
*/
int (timer_subscribe_int)(uint8_t *bit_no);
/**
 * @brief This function allows to unsubscribe the interupt for the timer.
 * @return Status of the function.
*/
int (timer_unsubscribe_int)();
/**
 * @brief This function allows to handle the interupt. In this counts, it increments an integer "count" by 1 in each interupt.
*/
void (timer_int_handler)();
/**
 * @brief This function allows to get the configuration of the timer.
 * @param timer Port for the specific timer.
 * @param st Hexadecimal integer to save the response of the timer.
 * @return Status of the function.
*/
int (timer_get_conf)(uint8_t timer, uint8_t *st);
/**
 * @brief This function allows to display the configuration of the timer.
 * @param timer Port for the specific timer.
 * @param st Hexadecimal integer with the response of the timer.
 * @param field Struct to save the configuration.
 * @return Status of the function.
*/
int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field);
/**
 * @brief This function allows to set the frequency of the timer.
 * @param timer Port for the specific timer.
 * @param freq Integer that holds the frequency.
 * @return Status of the function.
*/
int (timer_set_frequency)(uint8_t timer, uint32_t freq);

#endif /* _LCOM_I8254_H */
