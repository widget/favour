
#define LED_COUNT 5

typedef uint8_t led_pattern[LED_COUNT];
typedef struct
{
    unsigned int led0:5;
    unsigned int led1:5;
    unsigned int led2:5;
    unsigned int led3:5;
    unsigned int led4:5;
} led_pattern2;

_Static_assert(sizeof(led_pattern2) == 4, "led_pattern2 is not 4");

typedef struct 
{
    const led_pattern2* array;
    uint8_t len;
    uint8_t divisor;
} pattern_t;


const led_pattern2 blink[] PROGMEM = {
    { 0,  0,  0,  0,  0},
    {12,  0,  0,  0,  0},
    { 2,  0,  0,  0,  0},
    {15,  0,  0,  0,  0},
    { 8,  0,  0,  0,  0},
    {13,  0,  0,  0,  0},
    { 2,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  0, 12,  0},
    { 0,  0,  0,  2,  0},
    { 0,  0,  0, 15,  0},
    { 0,  0,  0,  8,  0},
    { 0,  0,  0, 13,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0},
};

//_Static_assert(sizeof(led_pattern) == 5, "led_pattern is not 5");
//_Static_assert((sizeof(blink)/sizeof(led_pattern)) == 32, "blink is not 32");

const led_pattern2 off[] PROGMEM = {
    { 0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0},
};

const led_pattern2 all_fade[] PROGMEM = {
    { 1,  1,  1,  0,  0},
    { 2,  2,  2,  0,  0},
    { 3,  3,  3,  0,  0},
    { 4,  4,  4,  0,  0},
    { 5,  5,  5,  0,  0},
    { 6,  6,  6,  0,  0},
    { 7,  7,  7,  0,  0},
    { 8,  8,  8,  0,  0},
    { 9,  9,  9,  0,  0},
    {10, 10, 10,  0,  0},
    {11, 11, 11,  0,  0},
    {12, 12, 12,  0,  0},
    {13, 13, 13,  0,  0},
    {14, 14, 14,  0,  0},
    {15, 15, 15,  0,  0},
    {15, 15, 15,  0,  0},
    {15, 15, 15,  0,  0},
    {15, 15, 15,  0,  0},
    {14, 14, 14,  0,  0},
    {13, 13, 13,  0,  0},
    {12, 12, 12,  0,  0},
    {11, 11, 11,  0,  0},
    {10, 10, 10,  0,  0},
    { 9,  9,  9,  0,  0},
    { 8,  8,  8,  0,  0},
    { 7,  7,  7,  0,  0},
    { 6,  6,  6,  0,  0},
    { 5,  5,  5,  0,  0},
    { 4,  4,  4,  0,  0},
    { 3,  3,  3,  0,  0},
    { 2,  2,  2,  0,  0},
    { 1,  1,  1,  0,  0},
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
        .divisor = 3,
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
    }       
};

#define NUM_PATTERNS_LO (sizeof(PATTERNS_LO)/sizeof(pattern_t))
