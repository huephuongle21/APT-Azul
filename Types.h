#ifndef TYPES_H
#define TYPES_H

#include "Tile.h"
#include <vector>

#define STUDENT_CREDITS_LENGTH  3
#define USER_PROMPT             '>'
#define FACTORY_SIZE            4
#define NUM_PLAYABLE_COLOURS    5
#define WALL_DIM                5 
#define PATTERN_LINES_SIZE      5
#define NUMBER_OF_FACTORY       5
#define FLOOR_LINE_SIZE         7
#define TILES_PER_COLOUR        20
#define TILE_BAG_MAXIMUM        100
#define EMPTY_COLLECTION        '_'

enum Option {
    newGame,
    loadGame,
    displayCredits,
    quit,
    OptionInvalid
};

typedef TilePtr Factory[FACTORY_SIZE];
typedef TilePtr Wall[WALL_DIM][WALL_DIM];

#endif // TYPES_H