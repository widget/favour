
#define LED_COUNT 5

typedef uint8_t led_pattern[LED_COUNT];
typedef struct
{
    unsigned int led0:5;
    unsigned int led1:5;
    unsigned int led2:5;
    unsigned int led3:5;
    unsigned int led4:5;
    unsigned int count:5;
} led_pattern2;

_Static_assert(sizeof(led_pattern2) == 4, "led_pattern2 is not 4");

typedef struct 
{
    const led_pattern2* array;
    uint8_t len;
    uint8_t divisor;
} pattern_t;


const led_pattern2 blink[] PROGMEM = {
    {12,  0,  0,  0,  0, .count =  1},
    { 2,  0,  0,  0,  0, .count =  1},
    {15,  0,  0,  0,  0, .count =  1},
    { 8,  0,  0,  0,  0, .count =  1},
    {13,  0,  0,  0,  0, .count =  1},
    { 2,  0,  0,  0,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count = 20},
    { 0,  0,  0, 12,  0, .count =  1},
    { 0,  0,  0,  2,  0, .count =  1},
    { 0,  0,  0, 15,  0, .count =  1},
    { 0,  0,  0,  8,  0, .count =  1},
    { 0,  0,  0, 13,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count = 10},
};

//_Static_assert(sizeof(led_pattern) == 5, "led_pattern is not 5");
//_Static_assert((sizeof(blink)/sizeof(led_pattern)) == 32, "blink is not 32");

const led_pattern2 off[] PROGMEM = {
    { 0,  0,  0,  0,  0, .count =  1},
    { 0,  0,  0,  0,  0, .count =  1},
};

const led_pattern2 all_fade[] PROGMEM = {
    { 1,  1,  1,  0,  0, .count =  12},
    { 2,  2,  2,  0,  0, .count =  1},
    { 3,  3,  3,  0,  0, .count =  1},
    { 4,  4,  4,  0,  0, .count =  1},
    { 5,  5,  5,  0,  0, .count =  1},
    { 6,  6,  6,  0,  0, .count =  1},
    { 7,  7,  7,  0,  0, .count =  1},
    { 8,  8,  8,  0,  0, .count =  1},
    { 9,  9,  9,  0,  0, .count =  1},
    {10, 10, 10,  0,  0, .count =  1},
    {11, 11, 11,  0,  0, .count =  1},
    {12, 12, 12,  0,  0, .count =  1},
    {13, 13, 13,  0,  0, .count =  1},
    {14, 14, 14,  0,  0, .count =  1},
    {15, 15, 15,  0,  0, .count =  6},
    {14, 14, 14,  0,  0, .count =  1},
    {13, 13, 13,  0,  0, .count =  1},
    {12, 12, 12,  0,  0, .count =  1},
    {11, 11, 11,  0,  0, .count =  1},
    {10, 10, 10,  0,  0, .count =  1},
    { 9,  9,  9,  0,  0, .count =  1},
    { 8,  8,  8,  0,  0, .count =  1},
    { 7,  7,  7,  0,  0, .count =  1},
    { 6,  6,  6,  0,  0, .count =  1},
    { 5,  5,  5,  0,  0, .count =  1},
    { 4,  4,  4,  0,  0, .count =  1},
    { 3,  3,  3,  0,  0, .count =  1},
    { 2,  2,  2,  0,  0, .count =  1},
};

const led_pattern2 middle_fade[] PROGMEM = {
    { 0,  0,  0,  0,  1, .count = 12},
    { 0,  0,  0,  0,  2, .count =  1},
    { 0,  0,  0,  0,  3, .count =  1},
    { 0,  0,  0,  0,  4, .count =  1},
    { 0,  0,  0,  0,  5, .count =  1},
    { 0,  0,  0,  0,  6, .count =  1},
    { 0,  0,  0,  0,  7, .count =  1},
    { 0,  0,  0,  0,  8, .count =  1},
    { 0,  0,  0,  0,  9, .count =  1},
    { 0,  0,  0,  0, 10, .count =  1},
    { 0,  0,  0,  0, 11, .count =  1},
    { 0,  0,  0,  0, 12, .count =  1},
    { 0,  0,  0,  0, 13, .count =  1},
    { 0,  0,  0,  0, 14, .count =  1},
    { 0,  0,  0,  0, 15, .count =  6},
    { 0,  0,  0,  0, 14, .count =  1},
    { 0,  0,  0,  0, 13, .count =  1},
    { 0,  0,  0,  0, 12, .count =  1},
    { 0,  0,  0,  0, 11, .count =  1},
    { 0,  0,  0,  0, 10, .count =  1},
    { 0,  0,  0,  0,  9, .count =  1},
    { 0,  0,  0,  0,  8, .count =  1},
    { 0,  0,  0,  0,  7, .count =  1},
    { 0,  0,  0,  0,  6, .count =  1},
    { 0,  0,  0,  0,  5, .count =  1},
    { 0,  0,  0,  0,  4, .count =  1},
    { 0,  0,  0,  0,  3, .count =  1},
    { 0,  0,  0,  0,  2, .count =  1},
};

const pattern_t PATTERNS_HI[] PROGMEM = 
{
    {
        .array = blink,
        .len = sizeof(blink)/sizeof(led_pattern2),
        .divisor = 2,
    },
    {
        .array = all_fade,
        .len = sizeof(all_fade)/sizeof(led_pattern2),
        .divisor = 4,
    },
    {
        .array = off,
        .len = sizeof(off)/sizeof(led_pattern2),
        .divisor = 2,
    }        
};

#define NUM_PATTERNS_HI (sizeof(PATTERNS_HI)/sizeof(pattern_t))

const pattern_t PATTERNS_LO[] PROGMEM = 
{
    {
        .array = blink,
        .len = sizeof(blink)/sizeof(led_pattern2),
        .divisor = 2,
    },
    {
        .array = off,
        .len = sizeof(off)/sizeof(led_pattern2),
        .divisor = 2
    }, 
    {
        .array = middle_fade,
        .len = sizeof(middle_fade)/sizeof(led_pattern2),
        .divisor = 4,
    },   
};

#define NUM_PATTERNS_LO (sizeof(PATTERNS_LO)/sizeof(pattern_t))
