#include <lcom/lcf.h>

#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

/**
 * @brief This struct saves all the necessary information about the sprite.
*/
struct sprite_t{
    int x, y;
    int w, h;
    int vx, vy;
    uint8_t *map;
};
typedef struct sprite_t sprite_t;
/**
 * @brief This function allows to create the sprite with the function xpm_load().
 * @param xpm Array that holds the xpm format.
 * @return Sprite struct that holds the xpm.
*/
sprite_t* sprite_ctor(const xpm_map_t xpm);
/**
 * @brief This function allows to free memory by deleting the sprite.
 * @param p Sprite.
*/
void sprite_dtor(sprite_t *p);
/**
 * @brief This function allows to change the parameter x of the sprite.
 * @param p Sprite.
 * @param x Integer that holds the value of x.
*/
void sprite_set_x(sprite_t *p, int x);
/**
 * @brief This function allows to change the parameter y of the sprite.
 * @param p Sprite.
 * @param x Integer that holds the value of y.
*/
void sprite_set_y(sprite_t *p, int y);
/**
 * @brief This function allows to change the parameter x and y of the sprite.
 * @param p Sprite.
 * @param x Integer that holds the value of x.
 * @param y Integer that holds the value of y.
*/
void sprite_set_pos(sprite_t *p, int x, int y);
/**
 * @brief This function allows to get the parameter h of the sprite.
 * @param p Sprite.
 * @return Parameter h of the sprite.
*/
int sprite_get_h(const sprite_t *p);
/**
 * @brief This function allows to get the parameter w of the sprite.
 * @param p Sprite.
 * @return Parameter w of the sprite.
*/
int sprite_get_w(const sprite_t *p);
/**
 * @brief This function allows to change the parameter vx of the sprite.
 * @param p Sprite.
 * @param vx Integer that holds the value of vx.
*/
void sprite_set_vx(sprite_t *p, int vx);
/**
 * @brief This function allows to change the parameter vy of the sprite.
 * @param p Sprite.
 * @param vy Integer that holds the value of vy.
*/
void sprite_set_vy(sprite_t *p, int vy);
/**
 * @brief This function allows to change the pixels of the screen according to the sprite map.
 * @param p Sprite.
*/
void sprite_draw(const sprite_t *p);

#endif //SPRITE_H_INCLUDED
