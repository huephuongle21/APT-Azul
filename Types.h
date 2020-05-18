#ifndef TYPES_H
#define TYPES_H

#include <vector>

#define STUDENT_CREDITS_LENGTH  3
#define FACTORY_SIZE            4
#define NUM_PLAYABLE_COLOURS    5
#define WALL_DIM                5 
#define PATTERN_LINES_SIZE      5
#define NUMBER_OF_FACTORY       5
#define FLOOR_LINE_SIZE         7
#define TILES_PER_COLOUR        20
#define TILE_BAG_MAXIMUM        100

#define USER_PROMPT             '>'
#define EMPTY_COLLECTION        '_'

#define COMMAND_TURN            "turn"
#define COMMAND_SAVE            "save"

#define NO_TILE       '.'
#define RED           'R'
#define YELLOW        'Y'
#define DARK_BLUE     'B'
#define LIGHT_BLUE    'L'
#define BLACK         'U'
#define FIRST_PLAYER  'F'

#define W_RED         'r'
#define W_YELLOW      'y'
#define W_DARK_BLUE   'b'
#define W_LIGHT_BLUE  'l'
#define W_BLACK       'u'


enum Option {
    newGame,
    loadGame,
    displayCredits,
    quit,
    OptionInvalid
};

typedef char Tile;
typedef char Factory[FACTORY_SIZE];
typedef char Wall[WALL_DIM][WALL_DIM];

#endif // TYPES_H