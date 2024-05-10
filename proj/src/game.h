#include "sprite.h"
#include <stdint.h>

#define COOLDOWN_PERIOD 1
#define ARENA_HEIGHT 768
#define ARENA_WIDTH 646
#define PLAYER_X 200
#define PLAYER_Y 500
#define V_ENEMY1_X 200
#define V_ENEMY1_Y 5
#define V_ENEMY2_X 400
#define V_ENEMY2_Y -100
#define LR_ENEMY_X 5
#define LR_ENEMY_Y 300
#define RL_ENEMY_X 610
#define RL_ENEMY_Y 100
/** 
 * @brief Struct to handle the game.
*/
typedef struct {
    int health;
    int score;
} game_t;

/**
 * @brief This function allows to check for collisions.
 * @param el The sprite of a screen object.
 * @param cursor The sprite that holds the cursor.
 * @return Boolean value that holds the result of the collision.
*/
bool check_collision_menu(sprite_t* el, sprite_t* cursor);
/**
 * @brief This function allows to handle the moviment according to the keyboard.
 * @param scancode Hexadecimal value of the key clicked.
 * @param sp Sprite that will move.
 * @param is_player Boolean value to check if it is the player. The player has different rules for the moviment.
*/
void handleMoviment(uint8_t scancode, sprite_t* sp, int is_player);
/**
 * @brief This function allows to handle the moviment according to the mouse.
 * @param pp Struct the has the information about the moviment of the mouse.
 * @param sp Sprite that will move.
*/
void handleMovimentCursorMouse(struct packet* pp, sprite_t* sp);
/**
 * @brief This function allows to handle the action of the player. 
 * For example, if the player interacts with the start button, the game will start.
 * @param scancode Hexadecimal value of the key clicked.
 * @param cursor Sprite that holds the cursor.
 * @param play Sprite that holds the play button.
 * @param exit Sprite that holds the exit button.
 * @param state Integer value that holds the state the game.
 * @param good Integer value that controls the while-loop.
 * @param game Game struct that holds important information about the game.
*/
void handleClick(uint8_t scancode, sprite_t* cursor, sprite_t* play, sprite_t* exit, int* state, int* good, game_t* game);
/**
 * @brief This function is responsible to draw the menu.
 * @param play Sprite that holds the play button.
 * @param exit Sprite that holds the exit button.
 * @param cursor Sprite that holds the cursor.
 * @param logo Sprite that holds the logo of the game.
*/
void drawMenu(sprite_t* play, sprite_t* exit, sprite_t* cursor, sprite_t* logo);
/**
 * @brief This function is responsible to draw the retry menu.
 * @param play Sprite that holds the play button.
 * @param exit Sprite that holds the exit button.
 * @param cursor Sprite that holds the cursor.
 * @param textScore Sprite that holds the score of the player.
 * @param score Score of the player.
*/
void drawRetryMenu(sprite_t* play, sprite_t* exit, sprite_t* cursor, sprite_t* textScore, int score);
/**
 * @brief This function is responsible to calcultate the new x for an enemy after he completes his moviment.
 * It makes the game more dynamic.
 * @param enemyA_width Width of the enemy A.
 * @param enemyB_x Position on X-axis of the enemy B.
*/
int calculate_new_x(int enemyA_width, int enemyB_x);~
/**
 * @brief This function is responsible to handle the moviment of an enemy which has travels in a vertical line.
 * @param verticalEnemy1 Sprite of the enemy 1.
 * @param verticalEnemy2 Sprite of the enemy 2.
 * @param elapsed_time Elapsed time.
*/
void handleVerticalMovementEnemy(sprite_t* verticalEnemy1, sprite_t* verticalEnemy2, int elapsed_time);
/**
 * @brief This function is responsible to calcultate the new x for an enemy after he completes his moviment.
 * It makes the game more dynamic.
 * @param enemyA_width Height of the enemy A.
 * @param enemyB_x Position on Y-axis of the enemy B.
*/
int calculate_new_y(int enemyA_height, int enemyB_y);
/**
 * @brief This function is responsible to handle the moviment of an enemy which has travels in a horizontal line.
 * @param verticalEnemy1 Sprite of the enemy 1.
 * @param verticalEnemy2 Sprite of the enemy 2.
 * @param elapsed_time Elapsed time.
*/
void handleHorizontalMovementEnemy(sprite_t* leftToRightEnemy, sprite_t* rightToLeftEnemy, int elapsed_time);
/**
 * @brief This function is transforms a number into many sprites of that number's digits.
 * @param number Number.
 * @param position_y Position in the Y-axis of those sprites.
 * @param position_x Position in the X-axis of those sprites.
*/
void draw_numbers(int number, int position_y, int position_x);
/**
 * @brief This function is transforms the string that holds the time of the RTC into many sprites.
 * @param string String of the time.
 * @param position_y Position in the Y-axis of those sprites.
 * @param position_x Position in the X-axis of those sprites.
*/
void draw_numbers_time(char* string, int position_y, int position_x);
/**
 * @brief This function allows to handle the collisions during the game.
 * @param player Sprite that holds the player.
 * @param explosion Sprite that holds the explosions.
 * @param enemy Sprite that holds the enemy.
 * @param enemies Array that holds the sprite of the enemies.
 * @param enemy_index Position of the enemy in the array.
 * @param last_collision_time Time of the last collision.
 * @param explosion_time Time of the explosion.
 * @param elapsed_time Elapsed time.
*/
bool check_collision(sprite_t* player, sprite_t* explosion, sprite_t* enemy, sprite_t* enemies[], int enemy_index, int* last_collision_time, int* explosion_time, int elapsed_time);
