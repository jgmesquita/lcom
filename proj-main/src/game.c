#include "graphic.h"
#include "mouse.h"
#include "game.h"
#include <stdint.h>
#include <stdlib.h>

extern xpm_row_t ZERO_xpm[];
extern xpm_row_t ONE_xpm[];
extern xpm_row_t TWO_xpm[];
extern xpm_row_t THREE_xpm[];
extern xpm_row_t FOUR_xpm[];
extern xpm_row_t FIVE_xpm[];
extern xpm_row_t SIX_xpm[];
extern xpm_row_t SEVEN_xpm[];
extern xpm_row_t EIGHT_xpm[];
extern xpm_row_t NINE_xpm[];

bool check_collision_menu(sprite_t* el, sprite_t* cursor) {
    if (el->x <= cursor->x && el->x + el->w >= cursor->x) {
        if (el->y <= cursor->y && el->y + el->h >= cursor->y) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

void handleMoviment(uint8_t scancode, sprite_t* sp, int is_player) {
    if (is_player) {
        switch (scancode) {
            case 0x17: if (sp->y - 35 > 0) sp->y = sp->y - 35; break;
            case 0x26: if (sp->x + 35 + sp->w < ARENA_WIDTH) sp->x = sp->x + 35; break;
            case 0x25: if (sp->y + 35 + sp->h < ARENA_HEIGHT) sp->y = sp->y + 35; break;
            case 0x24: if (sp->x - 35 > 0) sp->x = sp->x - 35; break;
        }
    }
    else {
        switch (scancode) {
            case 0x17: if (sp->y - 35 > 0) sp->y = sp->y - 35; break;
            case 0x26: if (sp->x + 35 + sp->w < 1024) sp->x = sp->x + 35; break;
            case 0x25: if (sp->y + 35 + sp->h < ARENA_HEIGHT) sp->y = sp->y + 35; break;
            case 0x24: if (sp->x - 35 > 0) sp->x = sp->x - 35; break;
        }
    }
}

void handleMovimentCursorMouse(struct packet* pp, sprite_t* sp) {
    uint8_t b[3];
    for (int i = 0; i < 3; i++) {
        b[i] = pp->bytes[i];
    }
    int16_t x = pp->delta_x;
    int16_t y = pp->delta_y;
    if (b[0] & MSB_X_DELTA) {
        x |= 0xFF00; 
    }
    if (b[0] & MSB_Y_DELTA) {
        y |= 0xFF00;
    }
    sp->x = sp->x + (int8_t)x;
    sp->y = sp->y - (int8_t)y;
}

void handleClick(uint8_t scancode, sprite_t* cursor, sprite_t* play, sprite_t* exit, int* state, int* good, game_t* game, int* last_collision_time, int* explosion_time) {
    switch (scancode) {
        case 0x81: *good = 0; break;
        case 0x39: 
        if (check_collision_menu(play, cursor) && *state != 1) {
            *state = 1;
            game->score = 0;
            game->health = 100;
            *last_collision_time = -COOLDOWN_PERIOD;
            *explosion_time = -COOLDOWN_PERIOD;
            vg_draw_rectangle(0, 0, 1024, 768, BLACK);
        }
        if (check_collision_menu(exit, cursor)) {
            *good = 0;
        } break;
    }
}

void drawMenu(sprite_t* play, sprite_t* exit, sprite_t* cursor, sprite_t* logo) {
    sprite_set_pos(cursor, cursor->x, cursor->y);
    sprite_draw(logo);
    sprite_draw(play);
    sprite_draw(exit);
    sprite_draw(cursor);
}


void drawRetryMenu(sprite_t* play, sprite_t* exit, sprite_t* cursor, sprite_t* textScore, int score) {
    sprite_set_pos(cursor, cursor->x, cursor->y);
    sprite_draw(textScore);
    draw_numbers(score, 200, 500);
    sprite_draw(play);
    sprite_draw(exit);
    sprite_draw(cursor);
}


int calculate_new_x(int enemyA_width, int enemyB_x) {
    int new_x = 5 + rand() % (ARENA_WIDTH - enemyA_width - 5);
    while (abs(new_x - enemyB_x) < enemyA_width) {
        new_x = 5 + rand() % (ARENA_WIDTH - enemyA_width - 5);
    }
    return new_x;
}

void handleVerticalMovementEnemy(sprite_t* verticalEnemy1, sprite_t* verticalEnemy2, int elapsed_time) {
    if (elapsed_time <= 10) {
        verticalEnemy1->y = verticalEnemy1->y + 5;
        verticalEnemy2->y = verticalEnemy2->y + 5;
    }
    else if (elapsed_time > 10 && elapsed_time <= 20) {
        verticalEnemy1->y = verticalEnemy1->y + 7;
        verticalEnemy2->y = verticalEnemy2->y + 7;
    }
    else if (elapsed_time > 20 && elapsed_time <= 30) {
        verticalEnemy1->y = verticalEnemy1->y + 9;
        verticalEnemy2->y = verticalEnemy2->y + 9;
    }
    else if (elapsed_time > 30 && elapsed_time <= 40) {
        verticalEnemy1->y = verticalEnemy1->y + 11;
        verticalEnemy2->y = verticalEnemy2->y + 11;
    }
    else {
        verticalEnemy1->y = verticalEnemy1->y + 13;
        verticalEnemy2->y = verticalEnemy2->y + 13;
    }
    if (verticalEnemy1->y + verticalEnemy1->h > ARENA_HEIGHT) {
        verticalEnemy1->x = calculate_new_x(verticalEnemy1->w, verticalEnemy2->x);
        verticalEnemy1->y = V_ENEMY1_Y; 
    }
    if (verticalEnemy2->y + verticalEnemy2->h > ARENA_HEIGHT) {
        verticalEnemy2->x = calculate_new_x(verticalEnemy2->w, verticalEnemy1->x);
        verticalEnemy2->y = V_ENEMY2_Y; 
    }
}

int calculate_new_y(int enemyA_height, int enemyB_y) {
    int new_y = 5 + rand() % (ARENA_HEIGHT - enemyA_height - 5);
    while (abs(new_y - enemyB_y) < enemyA_height) {
        new_y = 5 + rand() % (ARENA_WIDTH - enemyA_height - 5);
    }
    return new_y;
}

void handleHorizontalMovementEnemy(sprite_t* leftToRightEnemy, sprite_t* rightToLeftEnemy, int elapsed_time) {
    if (elapsed_time <= 10) {
        leftToRightEnemy->x = leftToRightEnemy->x + 3;
        rightToLeftEnemy->x = rightToLeftEnemy->x - 3;
    }
    else if (elapsed_time > 10 && elapsed_time <= 20) {
        leftToRightEnemy->x = leftToRightEnemy->x + 5;
        rightToLeftEnemy->x = rightToLeftEnemy->x - 5;
    }
    else if (elapsed_time > 20 && elapsed_time <= 30) {
        leftToRightEnemy->x = leftToRightEnemy->x + 7;
        rightToLeftEnemy->x = rightToLeftEnemy->x - 7;
    }
    else if (elapsed_time > 30 && elapsed_time <= 40) {
        leftToRightEnemy->x = leftToRightEnemy->x + 9;
        rightToLeftEnemy->x = rightToLeftEnemy->x - 9;
    }
    else {
        leftToRightEnemy->x = leftToRightEnemy->x + 11;
        rightToLeftEnemy->x = rightToLeftEnemy->x - 11;
    }
    if (leftToRightEnemy->x + leftToRightEnemy->w > 646) {
        leftToRightEnemy->x = 5; 
        leftToRightEnemy->y = calculate_new_y(leftToRightEnemy->h, rightToLeftEnemy->y);
    }
    if (rightToLeftEnemy->x + rightToLeftEnemy->w < 0) {
        rightToLeftEnemy->x = 646 - rightToLeftEnemy->w; 
        rightToLeftEnemy->y = calculate_new_y(rightToLeftEnemy->h, leftToRightEnemy->y);
    }
}

void draw_numbers(int number, int position_y, int position_x) {
    sprite_t* n;
    while (number > 0) {
        int digit = number % 10;
        switch(digit) {
            case 0: vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(ZERO_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case 1: vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(ONE_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case 2: vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(TWO_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case 3: vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(THREE_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case 4: vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(FOUR_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case 5: vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(FIVE_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case 6: vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(SIX_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case 7: vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(SEVEN_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case 8: vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(EIGHT_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case 9: vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(NINE_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            default: break;
        }
        position_x = position_x - 50;
        number /= 10;
    }
}

void draw_numbers_time(char* string, int position_y, int position_x) {
    sprite_t* n;
    for (int i = 0; i <= 1; i++) {
        switch(string[i]) {
            case '0': vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(ZERO_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case '1': vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(ONE_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case '2': vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(TWO_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case '3': vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(THREE_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case '4': vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(FOUR_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case '5': vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(FIVE_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case '6': vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(SIX_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case '7': vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(SEVEN_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case '8': vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(EIGHT_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case '9': vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(NINE_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            default: break;
        }
        position_x = position_x + 50;
    }
    position_x = position_x + 50;
    for (int i = 3; i <= 4; i++) {
        switch(string[i]) {
            case '0': vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(ZERO_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case '1': vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(ONE_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case '2': vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(TWO_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case '3': vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(THREE_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case '4': vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(FOUR_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case '5': vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(FIVE_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case '6': vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(SIX_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case '7': vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(SEVEN_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case '8': vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(EIGHT_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            case '9': vg_draw_rectangle(position_x, position_y, 50, 50, BLACK);
                n = sprite_ctor(NINE_xpm); sprite_set_pos(n, position_x, position_y); sprite_draw(n); break;
            default: break;
        }
        position_x = position_x + 50;
    }
}


bool check_collision(sprite_t* player, sprite_t* explosion, sprite_t* enemy, sprite_t* enemies[], int enemy_index, int* last_collision_time, int* explosion_time, int elapsed_time) {
    if (elapsed_time - *last_collision_time < COOLDOWN_PERIOD) {
        return false;
    }

    if (player->x < enemy->x + enemy->w &&
        player->x + player->w > enemy->x &&
        player->y < enemy->y + enemy->h &&
        player->y + player->h > enemy->y) {
        vg_draw_rectangle(enemy->x, enemy->y, enemy->w, enemy->h, BLACK);
        vg_draw_rectangle(player->x, player->y, player->w, player->h, BLACK);
        sprite_set_pos(explosion, enemy->x, enemy->y);
        sprite_draw(explosion);
        switch(enemy_index) {
            case 0: 
                sprite_set_pos(enemy, calculate_new_x(enemy->w, enemies[1]->x), V_ENEMY1_Y);
                break;
            case 1:
                sprite_set_pos(enemy, calculate_new_x(enemy->w, enemies[0]->x), V_ENEMY2_Y);
                break;
            case 2:
                sprite_set_pos(enemy, LR_ENEMY_X, calculate_new_y(enemy->h, enemies[3]->y));
                break;
            case 3:
                sprite_set_pos(enemy, RL_ENEMY_X, calculate_new_y(enemy->h, enemies[2]->y));
                break;
        }
        sprite_draw(enemy);
        sprite_set_pos(player, PLAYER_X, PLAYER_Y);
        sprite_draw(player);
        *last_collision_time = elapsed_time;
        *explosion_time = elapsed_time;
        return true;
    }
    return false;
}
