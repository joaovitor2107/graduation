#ifndef consFile
#define consFile

    #define SQUARE_NUMBERS 8
    #define RED 1
    #define BLACK 2
    #define WHITE -1
    #define EMPTY 3 
    #define FULL -3
    #define UNDEFINED 4
    #define RIGHT 5
    #define LEFT 6
    #define WHITE_LEFT 9  /* White piece taking a red piece to the left */ 
    #define WHITE_RIGHT 10
    #define RED_LEFT 11 
    #define RED_RIGHT 12 
    #define MAX_DEPTH 3
    #define NO_CAPTURE 0
    
    #define TRUE 20 
    #define FALSE -20 

    typedef struct gridType gridType; 
    struct gridType {
        int state; // empty or full
        int color; // white or red
        int king; // true or false
    };

    typedef struct Positions Positions; 
    struct Positions {
        int x; 
        int y;
    };

    typedef struct {
        Positions from;
        Positions to;
    } Move;

#endif