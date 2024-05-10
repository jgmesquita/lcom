#include <stdint.h>
#include <lcom/video_gr.h>

#ifndef GRAPHICS_MACROS_H_INCLUDED
#define GRAPHICS_MACROS_H_INCLUDED

#define VC_BIOS_SERV  0x10 
#define VBE_CALL      0x4F 

// Graphics Functions
#define VBE_CTRL_INFO       0x00
#define VBE_MD_INFO         0x01 
#define SET_VBE_MD          0x02 

// Graphics modes
#define INDEXED_1024_768        0x105
#define DIRECT_640_480          0x110
#define DIRECT_800_600          0x115
#define DIRECT_1280_1024_565    0x11A
#define DIRECT_1280_1024_888    0x11B
#define LINEAR_FRAME_BUFFER_MD  BIT(14)

// Colors
#define BLACK               0x00

// Functions
/**
 * @brief This function allows to set the graphic mode.
 * @param mode Mode.
 * @return Status of the function.
*/
int (set_graphics_mode)(uint16_t mode);
/**
 * @brief This function allows to get permission of the Minix. It calls the sys_privctl().
 * @param base_addr Base address of the VRAM.
 * @param size Size of the VRAM.
 * @return Status of the function.
*/
int (get_permission)(unsigned int base_addr, unsigned int size);
/**
 * @brief This function allows to map the VRAM. It calls the vm_map_phys().
 * @return Status of the function.
*/
int (map_vram)(void);
/**
 * @brief This function allows to change the color of a pixel.
 * @param x Position in the X-axis.
 * @param y Position in the Y-axis.
 * @param color Hexadecimal Value of the color.
 * @return Status of the function.
*/
int (set_pixel)(uint16_t x, uint16_t y, uint32_t color);
/**
 * @brief This function allows to change the color of a pixel. It ignores the black pixels.
 * @param x Position in the X-axis.
 * @param y Position in the Y-axis.
 * @param color Hexadecimal Value of the color.
 * @return Status of the function.
*/
int (set_pixel_no_black)(uint16_t x, uint16_t y, uint32_t color);
/**
 * @brief This function returns the size of the resolution in the X-axis.
 * @return Size of the width of the screen.
*/
uint16_t get_XRes(void);
/**
 * @brief This function returns the size of the resolution in the Y-axis.
 * @return Size of the height of the screen.
*/
uint16_t get_YRes(void);
/**
 * @brief This function returns the number of bits in each pixel.
 * @return Number of bits in each pixel.
*/
uint16_t get_bits_pixel(void);
/**
 * @brief This function returns the number of bytes in each pixel.
 * @return Number of bytes in each pixel.
*/
uint16_t get_bytes_pixel(void);

#endif
