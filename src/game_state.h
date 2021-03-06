/*
 * game_state.h
 *
 * Author: Landon Gilbert-Bland
 */

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "ship.h"
#include "linked_list.h"
#include "level.h"

/* Width of the screen for the playable game area */
#define GAME_WIDTH 640

/* Height of the screen for the playable game area */
#define GAME_HEIGHT 480

/* How many pixels the player moves per update */
#define PLAYER_SPEED 4

/* Handle for the game state object */
typedef struct {
    ship_t *player_ship;    /* The player controlled ship */
    int player_move_up;     /* Indicates the player ship wants to move up */
    int player_move_down;   /* Indicates the player ship wants to move down */
    int player_move_left;   /* Indicates the player ship wants to move left */
    int player_move_right;  /* Indicates the player ship wants to move right */
    int player_fire;        /* Indicates the player ship wants to firing */
    ll_t *player_bullets;   /* Linked list of all currently active bullets */
    ll_t *alien_bullets;    /* Linked list of all currently active bullets */
    level_t *level;         /* Currently level being played */
} game_state_t;

/**
 * Initalizes everything needed for the game state
 *
 * @param state The game state being initalized
 * @return 0 on success, errcode (< 0) on failure
 */
game_state_t* game_state_init();

/**
 * Frees all the memory used by the game state
 *
 * @param state The game state to free
 */
void game_state_free(game_state_t *state);

/**
 * Updates the game state by 1 step
 */
void game_state_update(game_state_t *state);

#endif

