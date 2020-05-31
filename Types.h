#ifndef TYPES_H
#define TYPES_H

#define STUDENT_CREDITS_LENGTH  3
#define FACTORY_SIZE            4

#define WALL_DIM                5 
#define A_WALL_DIM              6

#define A_FLOOR_LINE_SIZE       8
#define FLOOR_LINE_SIZE         7

#define TILES_PER_COLOUR        20

#define A_TILE_BAG_MAXIMUM      120
#define TILE_BAG_MAXIMUM        100

#define NUM_PLAYABLE_COLOURS    5
#define A_NUM_PLAYABLE_COLOURS  6

#define USER_PROMPT             '>'
#define EMPTY_COLLECTION        '_'
#define NO_SEED_CHOICE          "?"
#define BREAK_LINE              "-------------------"

/* The file must contain that number of lines 
so that the game can be considered valid */
#define NUM_LINES_5TILE_BOARD   37
#define NUM_LINES_6TILE_BOARD   41


#define COMMAND_TURN            "turn"
#define COMMAND_SAVE            "save"
#define COMMAND_EXIST           "quit"
#define COMMAND_HELP            "help"
#define COMMAND_TURN_LENGTH     10
#define COMMAND_SAVE_LENGTH     2

#define POINT_HORIZONTAL        2
#define POINT_VERTICAL          7
#define POINT_1_COLOUR         10

#define C_RESET   "\033[0m"
#define C_BLACK   "\033[30m"                /* Black */
#define C_RED     "\033[31m"                /* Red */
#define C_GREEN   "\033[32m"                /* Green */
#define C_YELLOW  "\033[33m"                /* Yellow */
#define C_BLUE    "\033[34m"                /* Blue */
#define C_MAGENTA "\033[35m"                /* Magenta */
#define C_CYAN    "\033[36m"                /* Cyan */
#define C_WHITE   "\033[37m"                /* White */
#define C_PINK    "\u001b[38;5;198m"        /* Pink */
#define C_ORANGE  "\u001b[38;5;215m"        /* Orange */
#define C_LIGHTYELLOW  "\u001b[38;5;229m"
#define C_BROWN        "\u001b[38;5;130m"   /* Brown */
#define C_REDORANGE    "\u001b[38;5;9m"     /* Red orange */
#define C_ERRORMESSAGE "\u001b[38;5;161m"   /* Colour for error message */
#define C_GREY         "\u001b[38;5;243m"   /* Grey */

#define NO_TILE       '.'
#define RED           'R'
#define YELLOW        'Y'
#define DARK_BLUE     'B'
#define LIGHT_BLUE    'L'
#define BLACK         'U'
#define ORANGE        'O'
#define FIRST_PLAYER  'F'

#define W_RED         'r'
#define W_YELLOW      'y'
#define W_DARK_BLUE   'b'
#define W_LIGHT_BLUE  'l'
#define W_BLACK       'u'
#define W_ORANGE      'o'

enum Option {
    newGame,
    loadGame,
    displayCredits,
    quit,
    OptionInvalid
};

enum BoardOption {
    regular,
    grey,
    advanced6Tile,
    invalidBoard
};

typedef char Tile;
typedef Tile Factory[FACTORY_SIZE];
typedef Tile** Wall;

#define REGULAR_BOARD        1
#define GREY_BOARD           2
#define ADVANCED_6TILE_BOARD 3

#endif // TYPES_H