#include <stdint.h>

#define NEW_PISKEL_FRAME_COUNT 10
#define NEW_PISKEL_FRAME_WIDTH 7
#define NEW_PISKEL_FRAME_HEIGHT 7

/* Piskel data for "Numbers" */

static const uint32_t numbers[10][49] = {
{ // 0
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000, 
0xff000000, 0xff66ff66, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff66ff66, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 
0xff000000, 0xff66ff66, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff66ff66, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000
}, 
{ // 1
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000
},
{ // 2
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000, 
0xff000000, 0xff66ff66, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 
0xff000000, 0xff66ff66, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000
},
{ // 3
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000
},
{ // 4
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 
0xff000000, 0xff66ff66, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff66ff66, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000
},
{ // 5
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000, 
0xff000000, 0xff66ff66, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 
0xff000000, 0xff66ff66, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000
},
{ // 6
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000, 
0xff000000, 0xff66ff66, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 
0xff000000, 0xff66ff66, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000, 
0xff000000, 0xff66ff66, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff66ff66, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000
},
{ // 7
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000
},
{ // 8
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000, 
0xff000000, 0xff66ff66, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff66ff66, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000, 
0xff000000, 0xff66ff66, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff66ff66, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000
},
{ // 9
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000, 
0xff000000, 0xff66ff66, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff66ff66, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff66ff66, 0xff66ff66, 0xff66ff66, 0xff000000, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff66ff66, 0xff000000, 
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000
}
};