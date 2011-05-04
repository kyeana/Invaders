#include <assert.h>
#include <stdlib.h>

#include "game_state.h"
#include "errors.h"
#include "ship.h"

/* Game state information */
enum {
    /* Width of the screen for the playable game area */
    GAME_WIDTH = 640,

    /* Height of the screen for the playable game area */
    GAME_HEIGHT = 480,

    /* How many pixels the player moves per update */
    PLAYER_SPEED = 4,
};


int game_state_init(game_state **state)
{
    int error;
    sprite *player_sprite; /* will be owned by the game_state object */

    /* malloc this */
    *state = malloc(sizeof(game_state));
    if(!*state)
        return ERR_MALLOC;

    /* Load the sprite for the player ship */
    error = sprite_load_bmp(&player_sprite, "player.bmp");
    if(error != HUGE_SUCCESS) {
        free(*state);
        return error;
    }

    /* Load the players ship for this game. This sprite will now be owned
     * by this player ship */
    error = ship_init(&(**state).player_ship, player_sprite, PLAYER_SPEED);
    if(error != HUGE_SUCCESS) {
        free(*state);
        sprite_free(player_sprite);
        return error;
    }

    return HUGE_SUCCESS;
}


void game_state_free(game_state* state)
{
    assert(state);

    ship_free(state->player_ship);
    sprite_free(state->player_ship->sprite);
    free(state);
}


int game_state_get_width()
{
    return GAME_WIDTH;
}


int game_state_get_height()
{
    return GAME_HEIGHT;
}


void game_state_move_up(game_state* state)
{
    ship *pship = state->player_ship;

    pship->ypos -= ship_get_speed(pship);
    if(pship->ypos < 0)
        pship->ypos = 0;
}


void game_state_move_down(game_state* state)
{
    ship *pship = state->player_ship;

    pship->ypos += ship_get_speed(pship);
    if(pship->ypos > GAME_HEIGHT)
        pship->ypos = GAME_HEIGHT;
}


void game_state_move_left(game_state* state)
{
    ship *pship = state->player_ship;

    pship->xpos -= ship_get_speed(pship);
    if(pship->xpos < 0)
        pship->xpos = 0;
}


void game_state_move_right(game_state* state)
{
    ship *pship = state->player_ship;

    pship->xpos += ship_get_speed(pship);
    if(pship->xpos > GAME_WIDTH)
        pship->xpos = GAME_WIDTH;
}