
#define LED_COUNT 5

typedef struct
{
    unsigned int led0:5;
    unsigned int led1:5;
    unsigned int led2:5;
    unsigned int led3:5;
    unsigned int led4:5;
    unsigned int count:5;
} led_pattern;

_Static_assert(sizeof(led_pattern) == 4, "led_pattern is not 4");

typedef struct 
{
    const led_pattern* array;
    uint8_t len;
    uint8_t divisor;
} pattern_t;


const led_pattern blink[] PROGMEM = {
    {12,  0,  0,  0,  0, .count =  1},
    { 2,  0,  0,  0,  0, .count =  1},
    {15,  0,  0,  0,  0, .count =  1},
    { 8,  0,  0,  0,  0, .count =  1},
    {13,  0,  0,  0,  0, .count =  1},
    { 2,  0,  0,  0,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count = 20},
    { 0,  0,  0,  0,  2, .count =  1},
    { 0,  0,  0,  0, 12, .count =  1},
    { 0,  0,  0,  0,  5, .count =  1},
    { 0,  0,  0,  0,  0, .count = 25},
    { 0,  0, 12,  0,  0, .count =  1},
    { 0,  0,  2,  0,  0, .count =  1},
    { 0,  0,  6,  0,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count = 20},
    { 0,  1,  0,  0,  0, .count =  1},
    { 0,  8,  0,  0,  0, .count =  1},
    { 0,  4,  0,  0,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count = 10},
    { 0,  0,  0, 12,  0, .count =  1},
    { 0,  0,  0,  2,  0, .count =  1},
    { 0,  0,  0, 15,  0, .count =  1},
    { 0,  0,  0,  8,  0, .count =  1},
    { 0,  0,  0, 13,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count = 10},
};

const led_pattern blink_more[] PROGMEM = {
    {12,  0,  0,  0,  0, .count =  1},
    { 2,  0,  0,  0,  0, .count =  1},
    {18,  2,  0,  0,  0, .count =  1},
    { 0, 10,  0,  0,  0, .count =  1},
    { 0,  2,  0,  0,  0, .count =  1},
    { 0,  0,  0,  0,  1, .count =  1},
    { 0,  0,  0,  0,  0, .count =  1},
    { 0,  0,  0, 30,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count =  8},
    { 0,  0,  0,  0,  1, .count =  1},
    { 1,  0,  0,  0,  0, .count =  1},
    {30,  0,  0,  0,  0, .count =  1},
    { 6,  0,  0,  0,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count =  1},
    { 0,  0,  3,  0,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count =  1},
    { 0, 10,  0,  0,  0, .count =  1},
    { 0, 30,  0,  0,  0, .count =  1},
    { 0, 10,  0,  0,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count =  8},
    { 0,  0, 10,  0,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count =  1},
    { 0,  0, 10,  0,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count =  1},
    { 0,  0, 10,  0,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count =  8},
    { 0,  8,  0,  0,  0, .count =  1},
    { 0, 18,  0,  0,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count =  1},
    { 0,  0,  0,  2,  0, .count =  1},
    { 0,  0,  0, 12,  0, .count =  1},
    { 0,  0,  0,  8,  0, .count =  1},
    { 0,  0,  0,  2,  0, .count =  1},
    { 0,  0,  0,  0,  3, .count =  1},
    { 0,  0,  0,  0, 13, .count =  1},
    { 2,  0,  0,  0,  0, .count =  1},
    {18,  0,  0,  0,  0, .count =  1},
    { 2,  0,  0,  0,  0, .count =  1},
    {14,  0,  0,  0,  0, .count =  1},
    { 3,  0,  0,  0,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count =  8},
    { 0, 30,  0,  0,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count =  1},
    { 0,  0,  0,  0,  2, .count =  1},
    { 0,  0,  0,  0, 12, .count =  1},
    { 0,  0,  0,  0,  2, .count =  1},
    { 0,  0,  0,  0, 20, .count =  1},
    { 0,  0,  0,  0,  0, .count =  6},
    { 1,  0,  8,  0,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count =  1},
    { 0,  0,  2,  0,  0, .count =  1},
    { 0,  0,  8,  0,  0, .count =  1},
    { 0,  3,  0,  0,  0, .count =  1},
    { 0,  4,  0,  4,  0, .count =  1},
    { 0,  0,  0,  3,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count =  1},
    { 4,  0,  0,  0,  0, .count =  1},
    { 8,  0,  0,  0,  0, .count =  1},
    { 1,  0,  0,  0,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count =  8},
    { 0,  0,  0,  0,  3, .count =  1},
    { 0,  0, 20,  0,  0, .count =  1},
    { 0,  0,  2,  0,  0, .count =  1},
    { 0,  0,  0,  0,  3, .count =  1},
    {30,  0,  0,  0,  0, .count =  1},
    { 0,  1,  0,  0,  8, .count =  1},
    { 0, 20,  0,  0,  0, .count =  1},
    { 0,  1,  0,  0,  0, .count =  1},
};
    
    
//_Static_assert(sizeof(led_pattern) == 5, "led_pattern is not 5");
//_Static_assert((sizeof(blink)/sizeof(led_pattern)) == 32, "blink is not 32");

const led_pattern all_fade[] PROGMEM = {
    { 1,  1,  0,  1,  1, .count = 30},
    { 2,  2,  0,  2,  2, .count =  1},
    { 3,  3,  0,  3,  3, .count =  1},
    { 4,  4,  0,  4,  4, .count =  1},
    { 5,  5,  0,  5,  5, .count =  1},
    { 6,  6,  0,  6,  6, .count =  1},
    { 7,  7,  0,  7,  7, .count =  1},
    { 8,  8,  0,  8,  8, .count =  1},
    { 9,  9,  0,  9,  9, .count =  1},
    {10, 10,  0, 10, 10, .count =  1},
    {11, 11,  0, 11, 10, .count =  1},
    {12, 12,  0, 12, 12, .count =  1},
    {13, 13,  0, 13, 13, .count =  1},
    {14, 14,  1, 14, 14, .count =  1},
    {15, 15,  1, 15, 15, .count =  1},
    {16, 16,  1, 16, 16, .count =  1},
    {17, 17,  3, 17, 17, .count =  1},
    {18, 18,  5, 18, 18, .count =  1},
    {19, 19,  7, 19, 19, .count =  1},
    {20, 20,  9, 20, 20, .count =  1},
    {21, 21, 11, 21, 21, .count =  1},
    {22, 22, 13, 22, 22, .count =  1},
    {23, 23, 15, 23, 23, .count =  1},
    {24, 24, 17, 24, 24, .count =  1},
    {25, 25, 19, 25, 25, .count =  1},
    {26, 26, 21, 26, 26, .count =  1},
    {27, 27, 23, 27, 27, .count =  1},
    {28, 28, 25, 28, 28, .count =  1},
    {29, 29, 27, 29, 29, .count =  1},
    {30, 30, 29, 30, 30, .count =  1},
    {31, 31, 31, 31, 31, .count = 12},
    {30, 30, 29, 30, 30, .count =  1},
    {29, 29, 27, 29, 29, .count =  1},
    {28, 28, 25, 28, 28, .count =  1},
    {27, 27, 23, 27, 27, .count =  1},
    {26, 26, 21, 26, 26, .count =  1},
    {25, 25, 19, 25, 25, .count =  1},
    {24, 24, 17, 24, 24, .count =  1},
    {23, 23, 15, 23, 23, .count =  1},
    {22, 22, 13, 22, 22, .count =  1},
    {21, 21, 11, 21, 21, .count =  1},
    {20, 20,  9, 20, 20, .count =  1},
    {19, 19,  7, 19, 19, .count =  1},
    {18, 18,  5, 18, 18, .count =  1},
    {17, 17,  3, 17, 17, .count =  1},
    {16, 16,  1, 16, 16, .count =  1},
    {15, 15,  0, 15, 15, .count =  1},
    {14, 14,  0, 14, 14, .count =  1},
    {13, 13,  0, 13, 13, .count =  1},
    {12, 12,  0, 12, 12, .count =  1},
    {11, 11,  0, 11, 11, .count =  1},
    {10, 10,  0, 10, 10, .count =  1},
    { 9,  9,  0,  9,  9, .count =  1},
    { 8,  8,  0,  8,  8, .count =  1},
    { 7,  7,  0,  7,  7, .count =  1},
    { 6,  6,  0,  6,  6, .count =  1},
    { 5,  5,  0,  5,  5, .count =  1},
    { 4,  4,  0,  4,  4, .count =  1},
    { 3,  3,  0,  3,  3, .count =  1},
    { 2,  2,  0,  2,  2, .count =  1},
    { 1,  1,  0,  1,  1, .count = 10},
};

const led_pattern middle_fade[] PROGMEM = {
    { 0,  0,  1,  0,  0, .count = 12},
    { 0,  0,  2,  0,  0, .count =  1},
    { 0,  0,  3,  0,  0, .count =  1},
    { 0,  0,  4,  0,  0, .count =  1},
    { 0,  0,  5,  0,  0, .count =  1},
    { 0,  0,  6,  0,  0, .count =  1},
    { 0,  0,  7,  0,  0, .count =  1},
    { 0,  0,  8,  0,  0, .count =  1},
    { 0,  0,  9,  0,  0, .count =  1},
    { 0,  0, 10,  0,  0, .count =  1},
    { 0,  0, 11,  0,  0, .count =  1},
    { 0,  0, 12,  0,  0, .count =  1},
    { 0,  0, 13,  0,  0, .count =  1},
    { 0,  0, 14,  0,  0, .count =  1},
    { 0,  0, 15,  0,  0, .count =  1},
    { 0,  0, 16,  0,  0, .count =  1},
    { 0,  0, 17,  0,  0, .count =  1},
    { 0,  0, 18,  0,  0, .count =  1},
    { 0,  0, 19,  0,  0, .count =  1},
    { 0,  0, 20,  0,  0, .count =  1},
    { 0,  0, 21,  0,  0, .count =  1},
    { 0,  0, 22,  0,  0, .count =  1},
    { 0,  0, 23,  0,  0, .count =  1},
    { 0,  0, 24,  0,  0, .count =  1},
    { 0,  0, 25,  0,  0, .count =  1},
    { 0,  0, 26,  0,  0, .count =  1},
    { 0,  0, 27,  0,  0, .count =  1},
    { 0,  0, 28,  0,  0, .count =  1},
    { 0,  0, 29,  0,  0, .count =  1},
    { 0,  0, 30,  0,  0, .count =  1},
    { 0,  0, 31,  0,  0, .count = 18},
    { 0,  0, 30,  0,  0, .count =  1},
    { 0,  0, 29,  0,  0, .count =  1},
    { 0,  0, 28,  0,  0, .count =  1},
    { 0,  0, 27,  0,  0, .count =  1},
    { 0,  0, 26,  0,  0, .count =  1},
    { 0,  0, 25,  0,  0, .count =  1},
    { 0,  0, 24,  0,  0, .count =  1},
    { 0,  0, 23,  0,  0, .count =  1},
    { 0,  0, 22,  0,  0, .count =  1},
    { 0,  0, 21,  0,  0, .count =  1},
    { 0,  0, 20,  0,  0, .count =  1},
    { 0,  0, 19,  0,  0, .count =  1},
    { 0,  0, 18,  0,  0, .count =  1},
    { 0,  0, 17,  0,  0, .count =  1},
    { 0,  0, 16,  0,  0, .count =  1},
    { 0,  0, 15,  0,  0, .count =  1},
    { 0,  0, 14,  0,  0, .count =  1},
    { 0,  0, 13,  0,  0, .count =  1},
    { 0,  0, 12,  0,  0, .count =  1},
    { 0,  0, 11,  0,  0, .count =  1},
    { 0,  0, 10,  0,  0, .count =  1},
    { 0,  0,  9,  0,  0, .count =  1},
    { 0,  0,  8,  0,  0, .count =  1},
    { 0,  0,  7,  0,  0, .count =  1},
    { 0,  0,  6,  0,  0, .count =  1},
    { 0,  0,  5,  0,  0, .count =  1},
    { 0,  0,  4,  0,  0, .count =  1},
    { 0,  0,  3,  0,  0, .count =  1},
    { 0,  0,  2,  0,  0, .count =  1},
};

const led_pattern worm[] PROGMEM = {
    { 1,  0,  0,  0,  0, .count = 1},
    { 4,  0,  0,  0,  0, .count = 1},
    { 8,  0,  0,  0,  0, .count = 1},
    {16,  0,  0,  0,  0, .count = 1},
    {24,  0,  0,  0,  0, .count = 1},
    {31,  0,  0,  0,  0, .count = 1},
    {31,  1,  0,  0,  0, .count = 1},
    {31,  4,  0,  0,  0, .count = 1},
    {31,  8,  0,  0,  0, .count = 1},
    {31, 16,  0,  0,  0, .count = 1},
    {31, 24,  0,  0,  0, .count = 1},
    {31, 31,  0,  0,  0, .count = 1},
    {31, 31,  0,  1,  0, .count = 1},
    {31, 31,  0,  4,  0, .count = 1},
    {31, 31,  0,  8,  0, .count = 1},
    {31, 31,  0, 16,  0, .count = 1},
    {31, 31,  0, 24,  0, .count = 1},
    {31, 31,  0, 31,  0, .count = 1},
    {31, 31,  0, 31,  1, .count = 1},
    {31, 31,  0, 31,  4, .count = 1},
    {31, 31,  0, 31,  8, .count = 1},
    {31, 31,  0, 31, 16, .count = 1},
    {31, 31,  0, 31, 24, .count = 1},
    {31, 31,  0, 31, 31, .count = 1},
    {31, 31,  1, 31, 31, .count = 1},
    {31, 31,  4, 31, 31, .count = 1},
    {31, 31,  8, 31, 31, .count = 1},
    {31, 31, 16, 31, 31, .count = 1},
    {31, 31, 24, 31, 31, .count = 1},
    {31, 31, 31, 31, 31, .count = 1},
    {31, 31, 31, 31, 31, .count =12},
    {24, 31, 31, 31, 31, .count = 1},
    {16, 31, 31, 31, 31, .count = 1},
    { 8, 31, 31, 31, 31, .count = 1},
    { 4, 31, 31, 31, 31, .count = 1},
    { 1, 31, 31, 31, 31, .count = 1},
    { 0, 31, 31, 31, 31, .count = 1},
    { 0, 24, 31, 31, 31, .count = 1},
    { 0, 16, 31, 31, 31, .count = 1},
    { 0,  8, 31, 31, 31, .count = 1},
    { 0,  4, 31, 31, 31, .count = 1},
    { 0,  1, 31, 31, 31, .count = 1},
    { 0,  0, 31, 31, 31, .count = 1},
    { 0,  0, 31, 24, 31, .count = 1},
    { 0,  0, 31, 16, 31, .count = 1},
    { 0,  0, 31,  8, 31, .count = 1},
    { 0,  0, 31,  4, 31, .count = 1},
    { 0,  0, 31,  1, 31, .count = 1},
    { 0,  0, 31,  0, 31, .count = 1},
    { 0,  0, 31,  0, 24, .count = 1},
    { 0,  0, 31,  0, 16, .count = 1},
    { 0,  0, 31,  0,  8, .count = 1},
    { 0,  0, 31,  0,  4, .count = 1},
    { 0,  0, 31,  0,  1, .count = 1},
    { 0,  0, 31,  0,  0, .count = 1},
    { 0,  0, 24,  0,  0, .count = 1},
    { 0,  0, 16,  0,  0, .count = 1},
    { 0,  0,  8,  0,  0, .count = 1},
    { 0,  0,  4,  0,  0, .count = 1},
    { 0,  0,  1,  0,  0, .count = 1},
    { 0,  0,  0,  0,  0, .count =16},
};

const led_pattern one_circle[] PROGMEM = {
    { 1,  0,  0,  0, 12, .count = 1},
    { 2,  0,  0,  0,  9, .count = 1},
    { 6,  0,  0,  0,  6, .count = 1},
    { 9,  0,  0,  0,  2, .count = 1},
    {12,  0,  0,  0,  1, .count = 1},
    {12,  1,  0,  0,  0, .count = 1},
    { 9,  2,  0,  0,  0, .count = 1},
    { 6,  6,  0,  0,  0, .count = 1},
    { 2,  9,  0,  0,  0, .count = 1},
    { 1, 12,  0,  0,  0, .count = 1},
    { 0, 12,  0,  1,  0, .count = 1},
    { 0,  9,  0,  2,  0, .count = 1},
    { 0,  6,  0,  6,  0, .count = 1},
    { 0,  2,  0,  9,  0, .count = 1},
    { 0,  1,  0, 12,  0, .count = 1},
    { 0,  0,  0, 12,  1, .count = 1},
    { 0,  0,  0,  9,  2, .count = 1},
    { 0,  0,  0,  6,  6, .count = 1},
    { 0,  0,  0,  2,  9, .count = 1},
    { 0,  0,  0,  1, 12, .count = 1},
};

const led_pattern two_circle[] PROGMEM = {
    { 1, 12,  0,  1, 12, .count = 1},
    { 2,  9,  0,  2,  9, .count = 1},
    { 6,  5,  0,  6,  5, .count = 1},
    { 9,  1,  0,  9,  1, .count = 1},
    {12,  0,  0, 12,  0, .count = 1},
    {12,  1,  0, 12,  1, .count = 1},
    { 9,  2,  0,  9,  2, .count = 1},
    { 6,  6,  0,  6,  6, .count = 1},
    { 2,  9,  0,  2,  9, .count = 1},
    { 0, 12,  0,  0, 12, .count = 1},
    { 1, 12,  0,  1, 12, .count = 1},
    { 2,  9,  0,  2,  9, .count = 1},
    { 6,  5,  0,  6,  5, .count = 1},
    { 9,  1,  0,  9,  1, .count = 1},
    {12,  0,  0, 12,  0, .count = 1},
    {12,  1,  0, 12,  1, .count = 1},
    { 9,  2,  0,  9,  2, .count = 1},
    { 5,  6,  0,  5,  6, .count = 1},
    { 1,  9,  0,  1,  9, .count = 1},
    { 0, 12,  0,  0, 12, .count = 1},
};

const led_pattern perlin_hi[] PROGMEM = 
{
    {11, 18, 14, 17, 11, .count = 1},
    {11, 18, 15, 19, 10, .count = 1},
    {11, 17, 16, 19,  9, .count = 1},
    {10, 17, 16, 19,  9, .count = 1},
    { 8, 17, 17, 19, 10, .count = 1},
    { 7, 17, 17, 19, 10, .count = 1},
    { 6, 17, 17, 21,  9, .count = 1},
    { 6, 17, 16, 22,  8, .count = 1},
    { 5, 18, 16, 23,  8, .count = 1},
    { 4, 18, 16, 24,  9, .count = 1},
    { 4, 17, 16, 24, 11, .count = 1},
    { 5, 16, 15, 23, 12, .count = 1},
    { 6, 15, 14, 22, 12, .count = 1},
    { 8, 14, 13, 21, 12, .count = 1},
    {10, 13, 12, 20, 12, .count = 1},
    {12, 12, 11, 19, 12, .count = 1},
    {14, 13, 11, 18, 13, .count = 1},
    {14, 14, 11, 18, 14, .count = 1},
    {15, 16, 12, 17, 14, .count = 1},
    {15, 18, 13, 15, 14, .count = 1},
    {16, 19, 13, 13, 14, .count = 1},
    {16, 21, 13, 11, 14, .count = 1},
    {17, 22, 13,  9, 14, .count = 1},
    {19, 21, 14,  8, 13, .count = 1},
    {20, 21, 15,  8, 13, .count = 1},
    {21, 20, 17,  8, 13, .count = 1},
    {22, 20, 19,  9, 12, .count = 1},
    {23, 19, 21, 10, 12, .count = 1},
    {25, 19, 22, 10, 12, .count = 1},
    {26, 21, 23, 10, 11, .count = 1},
    {26, 23, 23,  9,  9, .count = 1},
    {25, 25, 24,  8,  6, .count = 1},
    {25, 27, 24,  7,  4, .count = 1},
    {24, 29, 24,  6,  2, .count = 1},
    {24, 30, 23,  6,  0, .count = 1},
    {24, 31, 22,  6,  0, .count = 1},
    {25, 30, 21,  7,  1, .count = 1},
    {26, 28, 20,  8,  2, .count = 1},
    {27, 27, 19,  9,  4, .count = 1},
    {28, 26, 18, 10,  6, .count = 1},
    {29, 25, 17, 11,  7, .count = 1},
    {29, 25, 15, 11,  7, .count = 1},
    {28, 24, 15, 10,  9, .count = 1},
    {27, 22, 16,  8, 11, .count = 1},
    {26, 20, 17,  7, 13, .count = 1},
    {25, 18, 19,  7, 16, .count = 1},
    {24, 16, 20,  6, 18, .count = 1},
    {23, 16, 20,  7, 19, .count = 1},
    {22, 15, 20,  8, 19, .count = 1},
    {23, 15, 20, 11, 20, .count = 1},
    {22, 14, 20, 13, 20, .count = 1},
    {22, 14, 19, 15, 21, .count = 1},
    {21, 14, 19, 17, 22, .count = 1},
    {19, 13, 19, 18, 23, .count = 1},
    {17, 12, 19, 20, 24, .count = 1},
    {16, 11, 20, 21, 24, .count = 1},
    {16,  8, 22, 23, 25, .count = 1},
    {16,  6, 23, 26, 26, .count = 1},
    {15,  4, 23, 28, 25, .count = 1},
    {14,  2, 23, 30, 25, .count = 1},
    {13,  1, 21, 30, 24, .count = 1},
    {12,  1, 19, 29, 24, .count = 1},
    {12,  2, 17, 28, 24, .count = 1},
    {13,  3, 16, 26, 24, .count = 1},
    {13,  3, 14, 25, 23, .count = 1},
    {11,  3, 12, 25, 22, .count = 1},
    {10,  2,  9, 24, 20, .count = 1},
    { 8,  2,  8, 23, 18, .count = 1},
    { 7,  2,  7, 21, 16, .count = 1},
    { 7,  3,  8, 18, 15, .count = 1},
    { 7,  3,  9, 16, 14, .count = 1},
    { 7,  4, 10, 15, 13, .count = 1},
    { 7,  4, 11, 14, 12, .count = 1},
    { 6,  4, 12, 14, 12, .count = 1},
    { 6,  5, 11, 14, 13, .count = 1},
    { 6,  7, 11, 12, 14, .count = 1},
    { 6,  9, 11, 11, 15, .count = 1},
    { 6, 11, 12, 11, 16, .count = 1},
    { 6, 13, 14, 11, 16, .count = 1},
    { 6, 14, 15, 11, 16, .count = 1},
    { 7, 14, 16, 11, 15, .count = 1},
    { 8, 14, 16,  9, 15, .count = 1},
    { 9, 14, 15,  8, 15, .count = 1},
    {10, 14, 14,  7, 14, .count = 1},
    {11, 15, 13,  6, 12, .count = 1},
    {11, 16, 12,  6, 12, .count = 1},
    {11, 17, 12,  7, 11, .count = 1},
    {11, 16, 11,  7, 12, .count = 1},
    {12, 16, 11,  7, 12, .count = 1},
    {13, 16, 10,  8, 13, .count = 1},
    {13, 16,  8,  8, 13, .count = 1},
    {13, 16,  7,  9, 13, .count = 1},
    {13, 17,  6, 10, 13, .count = 1},
    {14, 16,  7, 11, 12, .count = 1},
    {15, 15,  8, 12, 11, .count = 1},
    {15, 14,  9, 13, 11, .count = 1},
    {14, 15, 11, 13, 12, .count = 1},
    {13, 16, 12, 13, 13, .count = 1},
    {11, 17, 13, 14, 13, .count = 1},
    {11, 18, 13, 16, 13, .count = 1},
};


const led_pattern perlin_lo[] PROGMEM = 
{
    {6, 6, 4, 3, 4, .count = 1},
    {6, 6, 4, 3, 4, .count = 1},
    {8, 6, 4, 4, 4, .count = 1},
    {9, 7, 5, 4, 4, .count = 1},
    {9, 7, 6, 4, 5, .count = 1},
    {10, 7, 7, 5, 6, .count = 1},
    {10, 7, 8, 5, 7, .count = 1},
    {11, 7, 8, 6, 8, .count = 1},
    {11, 7, 9, 7, 9, .count = 1},
    {11, 6, 10, 8, 9, .count = 1},
    {11, 6, 10, 8, 9, .count = 1},
    {11, 6, 9, 8, 9, .count = 1},
    {11, 6, 9, 8, 9, .count = 1},
    {12, 7, 8, 8, 9, .count = 1},
    {11, 7, 8, 8, 8, .count = 1},
    {11, 7, 7, 9, 8, .count = 1},
    {10, 6, 7, 9, 7, .count = 1},
    {9, 6, 7, 10, 7, .count = 1},
    {8, 5, 7, 9, 7, .count = 1},
    {8, 5, 7, 9, 8, .count = 1},
    {7, 5, 7, 8, 7, .count = 1},
    {7, 6, 8, 8, 7, .count = 1},
    {6, 6, 8, 7, 7, .count = 1},
    {6, 6, 8, 7, 6, .count = 1},
    {6, 5, 8, 7, 6, .count = 1},
    {7, 5, 8, 7, 6, .count = 1},
    {7, 5, 7, 7, 7, .count = 1},
    {7, 4, 7, 7, 7, .count = 1},
    {8, 4, 6, 6, 7, .count = 1},
    {7, 3, 6, 5, 6, .count = 1},
    {7, 3, 6, 4, 5, .count = 1},
    {6, 3, 5, 3, 4, .count = 1},
    {5, 3, 5, 2, 4, .count = 1},
    {4, 3, 5, 1, 3, .count = 1},
    {4, 3, 4, 0, 3, .count = 1},
    {3, 2, 4, 0, 2, .count = 1},
    {3, 2, 3, 1, 3, .count = 1},
    {4, 2, 3, 1, 3, .count = 1},
    {4, 2, 2, 1, 4, .count = 1},
    {5, 2, 2, 2, 4, .count = 1},
    {5, 3, 3, 2, 4, .count = 1},
    {5, 3, 3, 3, 4, .count = 1},
    {5, 3, 3, 3, 4, .count = 1},
    {5, 2, 3, 3, 4, .count = 1},
    {4, 2, 3, 3, 5, .count = 1},
    {4, 2, 2, 2, 5, .count = 1},
    {5, 2, 2, 2, 5, .count = 1},
    {5, 2, 3, 2, 5, .count = 1},
    {6, 3, 3, 3, 5, .count = 1},
    {6, 4, 4, 3, 5, .count = 1},
    {7, 5, 5, 4, 5, .count = 1},
    {7, 6, 5, 5, 5, .count = 1},
    {8, 7, 6, 5, 5, .count = 1},
    {8, 8, 7, 6, 5, .count = 1},
    {9, 8, 8, 6, 5, .count = 1},
    {10, 8, 9, 5, 6, .count = 1},
    {10, 8, 9, 5, 6, .count = 1},
    {10, 8, 9, 4, 6, .count = 1},
    {10, 7, 8, 4, 7, .count = 1},
    {10, 8, 8, 4, 7, .count = 1},
    {10, 8, 7, 4, 7, .count = 1},
    {10, 8, 8, 4, 6, .count = 1},
    {10, 8, 8, 4, 5, .count = 1},
    {10, 7, 8, 3, 5, .count = 1},
    {10, 7, 7, 3, 4, .count = 1},
    {10, 7, 7, 3, 4, .count = 1},
    {10, 8, 6, 3, 3, .count = 1},
    {9, 8, 6, 3, 4, .count = 1},
    {8, 8, 5, 3, 4, .count = 1},
    {8, 8, 6, 3, 4, .count = 1},
    {7, 8, 6, 3, 5, .count = 1},
    {7, 8, 6, 3, 5, .count = 1},
    {7, 9, 6, 3, 5, .count = 1},
    {7, 9, 7, 3, 6, .count = 1},
    {7, 9, 7, 3, 6, .count = 1},
    {6, 9, 8, 3, 7, .count = 1},
    {6, 9, 8, 3, 7, .count = 1},
    {6, 8, 9, 3, 8, .count = 1},
    {6, 8, 10, 3, 8, .count = 1},
    {6, 8, 10, 3, 8, .count = 1},
    {6, 8, 10, 4, 7, .count = 1},
    {6, 8, 9, 4, 7, .count = 1},
    {6, 8, 9, 4, 7, .count = 1},
    {6, 7, 8, 4, 7, .count = 1},
    {6, 7, 8, 3, 7, .count = 1},
    {5, 6, 7, 3, 7, .count = 1},
    {5, 5, 6, 2, 6, .count = 1},
    {5, 4, 5, 2, 5, .count = 1},
    {5, 4, 4, 1, 5, .count = 1},
    {4, 3, 3, 1, 4, .count = 1},
    {4, 3, 3, 0, 3, .count = 1},
    {3, 2, 2, 0, 3, .count = 1},
    {3, 2, 2, 0, 3, .count = 1},
    {3, 3, 1, 0, 3, .count = 1},
    {3, 3, 1, 0, 3, .count = 1},
    {3, 3, 1, 1, 3, .count = 1},
    {4, 4, 1, 2, 3, .count = 1},
    {4, 4, 2, 2, 3, .count = 1},
    {4, 5, 3, 2, 3, .count = 1},
    {5, 5, 3, 3, 3, .count = 1},
};

const led_pattern binary[] PROGMEM = {
    { 1,  1,  1,  1,  1, .count =  1},
    { 3,  5,  2,  3,  5, .count =  1},
    { 5,  9,  3,  5,  9, .count =  1},
    { 7, 19,  4,  7, 19, .count =  1},
    { 9, 31,  5,  9, 31, .count =  1},
    {13, 19,  6, 13, 19, .count =  1},
    {19,  9,  7, 19,  9, .count =  1},
    {24,  5,  8, 24,  5, .count =  1},
    {31,  1,  9, 31,  1, .count =  1},
    {24,  5, 10, 24,  5, .count =  1},
    {19,  9, 13, 19,  9, .count =  1},
    {13, 19, 16, 13, 19, .count =  1},
    { 9, 31, 19,  9, 31, .count =  1},
    { 7,  9, 22,  7,  9, .count =  1},
    { 5,  5, 24,  5,  5, .count =  1},
    { 3,  3, 27,  3,  3, .count =  1},
    { 1,  1, 31,  1,  1, .count =  1},
    { 3,  5, 27,  3,  5, .count =  1},
    { 5,  9, 24,  5,  9, .count =  1},
    { 7, 19, 22,  7, 19, .count =  1},
    { 9, 31, 19,  9, 31, .count =  1},
    {13, 19, 16, 13, 19, .count =  1},
    {19,  9, 13, 19,  9, .count =  1},
    {24,  5, 10, 24,  5, .count =  1},
    {31,  1,  9, 31,  1, .count =  1},
    {24,  5,  8, 24,  5, .count =  1},
    {19,  9,  7, 19,  9, .count =  1},
    {13, 19,  6, 13, 19, .count =  1},
    { 9, 31,  5,  9, 31, .count =  1},
    { 7, 19,  4,  7, 19, .count =  1},
    { 5,  9,  3,  5,  9, .count =  1},
    { 3,  5,  2,  3,  5, .count =  1},
};

const led_pattern sides[] PROGMEM = {
    {31, 31,  0,  1,  1, .count = 10},
    {30, 30,  0,  2,  2, .count =  1},
    {29, 29,  0,  3,  3, .count =  1},
    {28, 28,  0,  4,  4, .count =  1},
    {27, 27,  0,  5,  5, .count =  1},
    {26, 26,  0,  6,  6, .count =  1},
    {25, 25,  0,  7,  7, .count =  1},
    {24, 24,  0,  8,  8, .count =  1},
    {23, 23,  0,  9,  9, .count =  1},
    {22, 22,  0, 10, 10, .count =  1},
    {21, 21,  0, 11, 11, .count =  1},
    {20, 20,  0, 12, 12, .count =  1},
    {19, 19,  0, 13, 13, .count =  1},
    {18, 18,  0, 14, 14, .count =  1},
    {17, 17,  0, 15, 15, .count =  1},
    {16, 16,  0, 16, 16, .count =  1},
    {15, 15,  0, 17, 17, .count =  1},
    {14, 14,  0, 18, 18, .count =  1},
    {13, 13,  0, 19, 19, .count =  1},
    {12, 12,  0, 20, 20, .count =  1},
    {11, 11,  0, 21, 21, .count =  1},
    {10, 10,  0, 22, 22, .count =  1},
    { 9,  9,  0, 23, 23, .count =  1},
    { 8,  8,  0, 24, 24, .count =  1},
    { 7,  7,  0, 25, 25, .count =  1},
    { 6,  6,  0, 26, 26, .count =  1},
    { 5,  5,  0, 27, 27, .count =  1},
    { 4,  4,  0, 28, 28, .count =  1},
    { 3,  3,  0, 29, 29, .count =  1},
    { 2,  2,  0, 30, 30, .count =  1},
    { 1,  1,  0, 31, 31, .count = 10},
    { 2,  2,  0, 30, 30, .count =  1},
    { 3,  3,  0, 29, 29, .count =  1},
    { 4,  4,  0, 28, 28, .count =  1},
    { 5,  5,  0, 27, 27, .count =  1},
    { 6,  6,  0, 26, 26, .count =  1},
    { 7,  7,  0, 25, 25, .count =  1},
    { 8,  8,  0, 24, 24, .count =  1},
    { 9,  9,  0, 23, 23, .count =  1},
    {10, 10,  0, 22, 22, .count =  1},
    {11, 11,  0, 21, 21, .count =  1},
    {12, 12,  0, 20, 20, .count =  1},
    {13, 13,  0, 19, 19, .count =  1},
    {14, 14,  0, 18, 18, .count =  1},
    {15, 15,  0, 17, 17, .count =  1},
    {16, 16,  0, 16, 16, .count =  1},
    {17, 17,  0, 15, 15, .count =  1},
    {18, 18,  0, 14, 14, .count =  1},
    {19, 19,  0, 13, 13, .count =  1},
    {20, 20,  0, 12, 12, .count =  1},
    {21, 21,  0, 11, 11, .count =  1},
    {22, 22,  0, 10, 10, .count =  1},
    {23, 23,  0,  9,  9, .count =  1},
    {24, 24,  0,  8,  8, .count =  1},
    {25, 25,  0,  7,  7, .count =  1},
    {26, 26,  0,  6,  6, .count =  1},
    {27, 27,  0,  5,  5, .count =  1},
    {28, 28,  0,  4,  4, .count =  1},
    {29, 29,  0,  3,  3, .count =  1},
    {30, 30,  0,  2,  2, .count =  1},
};

//#define TEST_PATTERN

#ifdef TEST_PATTERN
const led_pattern one_on[] PROGMEM = {
    //{ 16,  0,  0,  0,  0, .count = 20}
    { 31,  0,  0,  0,  0, .count = 1},
    { 0,  0,  0,  0,  0, .count = 1}
};
#endif

/* Pattern ideas
 * 
 * - other twinkle effect like blink?
 * - light up one corner, then the diagonal, then the other corner, in turn
 */

#define PATTERN_ENTRY(name, div) { .array = (name), .len = sizeof(name)/sizeof(led_pattern), .divisor = div }

const pattern_t PATTERNS_HI[] PROGMEM = 
{
#ifdef TEST_PATTERN
    PATTERN_ENTRY(one_on, 1),
#endif
    PATTERN_ENTRY(perlin_hi, 2),
    PATTERN_ENTRY(worm, 2),
    PATTERN_ENTRY(blink_more, 2),
    PATTERN_ENTRY(sides, 1),
    PATTERN_ENTRY(one_circle, 2),
    PATTERN_ENTRY(binary, 3),
    PATTERN_ENTRY(blink, 2),
    PATTERN_ENTRY(two_circle, 2),
    PATTERN_ENTRY(all_fade, 3),
};

#define NUM_PATTERNS_HI (sizeof(PATTERNS_HI)/sizeof(pattern_t))

const pattern_t PATTERNS_LO[] PROGMEM = 
{
#ifdef TEST_PATTERN
    PATTERN_ENTRY(one_on, 1),
#endif
    PATTERN_ENTRY(perlin_lo, 2),
    PATTERN_ENTRY(blink_more, 2),
    PATTERN_ENTRY(one_circle, 2),
    PATTERN_ENTRY(blink, 2),
    PATTERN_ENTRY(sides, 1),
    PATTERN_ENTRY(middle_fade, 3)
};

#define NUM_PATTERNS_LO (sizeof(PATTERNS_LO)/sizeof(pattern_t))
