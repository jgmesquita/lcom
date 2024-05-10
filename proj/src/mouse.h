#include <stdint.h>
#include <lcom/lcf.h>

#ifndef MOUSE_MACROS_H_INCLUDED
#define MOUSE_MACROS_H_INCLUDED

// Mouse Data Packet 
// Byte 0 - Button States
#define LEFT_BUTTON     BIT(0) 
#define RIGHT_BUTTON    BIT(1) 
#define MIDDLE_BUTTON   BIT(2) 
#define FIRST_BYTE_ID   BIT(3) 
#define MSB_X_DELTA     BIT(4)
#define MSB_Y_DELTA     BIT(5) 
#define X_OVERFLOW      BIT(6) 
#define Y_OVERFLOW      BIT(7) 
// Byte 1 - X delta
// Byte 2 - Y delta

//Functions
/**
 * @brief This function allows to subscribe the interupt for the mouse.
 * @param bit_no Integer to save the address.
 * @return Status of the function.
*/
int (mouse_subscribe_int)(uint8_t *bit_no);
/**
 * @brief This function allows to unsubscribe the interupt for the keyboard.
 * @return Status of the function.
*/
int (mouse_unsubscribe_int)();
/**
 * @brief This function allows to read the status of the mouse.
 * @param status Integer to status of the mouse.
 * @return Status of the function.
*/
int (mouse_read_status)(uint8_t* status);
/**
 * @brief This function allows to read the byte from an interupt.
 * @param status Integer to status of the mouse.
 * @param byte Integer to save the byte.
 * @return Status of the function.
*/
int (mouse_read_byte)(uint8_t status, uint8_t* byte);
/**
 * @brief This function allows to handle the interupt of the mouse.
*/
void (mouse_ih)();
/**
 * @brief This function allows to build the struct packet.
 * @param pp Struct packet that holds the information about the mouse.
*/
void (build_packet)(struct packet* pp);
/**
 * @brief This function allows to send a command to the mouse.
 * @param command Integer that holds the command.
 * @return Status of the function.
*/
int (send_command)(uint8_t command);

#endif // MOUSE_MACROS_H_INCLUDED
