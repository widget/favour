
#include "Favour.h"
#include "Patterns.h"
#include <avr/sleep.h>

/** Buffer to hold the previously generated Keyboard HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevKeyboardHIDReportBuffer[sizeof(USB_KeyboardReport_Data_t)];

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_HID_Device_t Keyboard_HID_Interface =
{
    .Config =
    {
        .InterfaceNumber              = INTERFACE_ID_Keyboard,
        .ReportINEndpoint             =
        {
            .Address              = KEYBOARD_EPADDR,
            .Size                 = KEYBOARD_EPSIZE,
            .Banks                = 1,
        },
        .PrevReportINBuffer           = PrevKeyboardHIDReportBuffer,
        .PrevReportINBufferSize       = sizeof(PrevKeyboardHIDReportBuffer),
    },
}; 

#define soft_reset() \
do \
{ \
wdt_enable(WDTO_15MS); \
for(;;) \
{ \
} \
} while(0)

#define LED_MAX_BRIGHT 32
#define LED_FREQ 256
// Precalculate LED values, rather than in the interrupt
uint8_t led_pwm[LED_MAX_BRIGHT];
uint8_t count = 0;
uint8_t fcount = 0;
uint16_t ticks = 0;
/* Interrupt triggered by the timer every 5kHz,
 * a simple PWM control of all LEDs.
 */
ISR(TIMER0_COMPA_vect, ISR_BLOCK)
{
    count++;
    if (count >= LED_MAX_BRIGHT)
    {
        count = 0;
        fcount++;
    }
    if (fcount >= 2)
    {
        fcount = 0;
        ticks++;
    }
    
    LEDs_SetAllLEDs(led_pwm[count]);
}

#ifdef GAMMA_CORRECTION
// This also requires the PWM to be a period of 64
const uint8_t PROGMEM gamma10_lut[32] = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,
                                          34,36,38,40,42,44,46,48,50,52,54,56,58,60,62};

const uint8_t PROGMEM gamma12_lut[32] = {0,1,2,3,5, 6, 8,10,12,13,15,17,19,21,23,25,27,
                                          29,32,34,36,38,40,43,45,47,49,52,54,56,59,62};
#endif

void set_led_pwm(const uint8_t led, const uint8_t bright)
{
    //uint8_t val = pgm_read_byte_near(gamma12_lut + bright);
    const uint8_t led_on = _BV(led);
    const uint8_t led_off = ~led_on;
    
    for (uint8_t i = 0; i < LED_MAX_BRIGHT; i++)
    {
#ifdef STAGGER_LED_PWM
        // Shift LED PWM patterns some
        uint8_t which = (i + (led*3)) % LED_MAX_BRIGHT;
#else
        uint8_t which = i;
#endif
        if (i < bright)
            led_pwm[which] |= led_on;
        else
            led_pwm[which] &= led_off;
    }
}

bool vusb_present = true, hwb_last = false;
bool hid_present = false;
uint16_t last_press = 0;
bool toggle = false;
uint8_t pattern_count = 0;

uint8_t set_pattern_get_next(pattern_t *pt, uint8_t idx)
{
    if (vusb_present)
    {
        memcpy_P(pt, PATTERNS_HI+idx, sizeof(pattern_t));
        return (idx + 1) % NUM_PATTERNS_HI;
    }
    else
    {
        memcpy_P(pt, PATTERNS_LO+idx, sizeof(pattern_t));
        return (idx + 1) % NUM_PATTERNS_LO;
    }

}
    
/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
    uint16_t next = 0;
    uint8_t idx = 0;
    uint8_t pattern_idx = 0;
    SetupHardware();

    pattern_t current_pattern;
    pattern_idx = set_pattern_get_next(&current_pattern, pattern_idx);
    GlobalInterruptEnable();
    
    while(1)
    {
        // Actually running through the selected LED pattern here
        if (ticks >= next)
        {
            uint32_t val = pgm_read_dword_near(&(current_pattern.array[idx]));
            led_pattern2* tmp = (led_pattern2*)(&val);
            
            set_led_pwm(0, tmp->led0);
            set_led_pwm(1, tmp->led1);
            set_led_pwm(2, tmp->led2);
            set_led_pwm(3, tmp->led3);
            set_led_pwm(4, tmp->led4);
            
            idx++;
            if (idx == current_pattern.len)
            {
                idx = 0;
                pattern_count++;
            }
            next = ticks + ((uint16_t)current_pattern.divisor * tmp->count);
            if (next == 0xffff)
            {
                next = 0; // could fuck up GTE check
            }
        }
        
        if (vusb_present)
        {
            // HID can't be detected if we don't do HID stuff
            HID_Device_USBTask(&Keyboard_HID_Interface);
            USB_USBTask();
        }
        
#ifdef BUTTON_CYCLE_PATTERN
        // Permit the button to toggle us round
        if (Buttons_GetStatus() & BUTTONS_HWB)
        {
            // check it was unpressed last cycle
            // and that we haven't done this in the last 2 ticks
            if (!hwb_last && (last_press != ticks))
            {
                toggle = true;
                last_press = ticks;
                hwb_last = true;
            }
        }
        else
        {
            hwb_last = false;
        }
#endif
        
        // Check power hasn't changed.  But VUSB doesn't tell us if we're running
        // on VUSB, just that it's present!
        bool new_vusb_present = !(Buttons_GetStatus() & BUTTONS_VCC);
        if (vusb_present != new_vusb_present)
        {
            // RESET
            soft_reset();
        }
        
        if (hid_present)
        {
            // Cycle onto the next pattern if caps is toggled
            if (toggle)
            {
                // Next pattern
                pattern_idx = set_pattern_get_next(&current_pattern, pattern_idx);
                // And restart
                idx = 0;
                next = 0;
                toggle = false;
            }
        }
        else // battery mode
        {
            if ((pattern_count == 150) || toggle)
            {
                pattern_idx = set_pattern_get_next(&current_pattern, pattern_idx);
                
                idx = 0;                // Start at the beginning of the cycle
                pattern_count = 0;      // Start the timer again
                next = 0;               // Trigger cycle to start now
                
                toggle = false;
            }
            
            // only sleep in battery mode
            sei();
            sleep_cpu();
        }
        
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware()
{
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~_BV(WDRF);
    wdt_disable();
    
    // Disable all pullups
    MCUCR |= _BV(PUD);
    
    Buttons_Init();
    
    // need to delay here 50ms, the VCC line can be held high
    // by capacitance.
    _delay_ms(50);
    
    // Check if we're on USB or battery,
    // BUTTONS_VCC will return true when VCC == 3V3
    vusb_present = !(Buttons_GetStatus() & BUTTONS_VCC);
    
    LEDs_Init(vusb_present);
    
    TCNT0  = 0x00; // start value
    TIFR0 = 0; // clear interrupt flags just in case
    TIMSK0 = _BV(OCIE0A); // Interrupt enable on compare A
    TCCR0A = 0x02; // Clear Timer on Compare (CTC) mode
    
    // Never using these, may as well leave them off
    power_spi_disable();
    power_timer1_disable();
    power_usart1_disable();
    // disable analogue comparator
    ACSR |= _BV(ACD);
    
    // Debug is disabled in fuses, but BOD isn't
    
    if (bit_is_set(CLKSEL0,CLKS))
    {
        // Turn off RC osc too
        CLKSEL0 &= ~(1 << RCE);
    }
    
    if (vusb_present)
    {
        /* Disable clock division */
        clock_prescale_set(clock_div_1);
        USB_Init();
        
        OCR0A  =   29; // 4096Hz
        // set timer0 to be 16MHz/64 = 8andabit kHz
        TCCR0B = 0x03;
    }
    else
    {
        // going slower than this leaves too little time for the interrupt
        clock_prescale_set(clock_div_16);
        
        USB_Disable();
        
        power_usb_disable();
        
        // this should be the default
        set_sleep_mode(SLEEP_MODE_IDLE);
        sleep_enable();
        
        OCR0A  =   119; // 4096Hz
        // Set timer0 to be 8/(16*1) - 125kHz
        TCCR0B = 0x01;
    }
    
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
    bool ConfigSuccess = true;

    ConfigSuccess &= HID_Device_ConfigureEndpoints(&Keyboard_HID_Interface);

    USB_Device_EnableSOFEvents();

    hid_present = true;
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
    HID_Device_ProcessControlRequest(&Keyboard_HID_Interface);
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void)
{
    HID_Device_MillisecondElapsed(&Keyboard_HID_Interface);
}

/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent)
 *
 *  \return Boolean \c true to force the sending of the report, \c false to let the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize)
{
/*
    USB_KeyboardReport_Data_t* KeyboardReport = (USB_KeyboardReport_Data_t*)ReportData;

    uint8_t ButtonStatus_LCL = Buttons_GetStatus();
    uint8_t UsedKeyCodes = 0;

    if (ButtonStatus_LCL & BUTTONS_HWB)
        KeyboardReport->KeyCode[UsedKeyCodes++] = HID_KEYBOARD_SC_F;

    if (UsedKeyCodes)
        KeyboardReport->Modifier = HID_KEYBOARD_MODIFIER_LEFTSHIFT;*/

    *ReportSize = sizeof(USB_KeyboardReport_Data_t);
    return false;
}

/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
    static bool caps = false;
    uint8_t* LEDReport = (uint8_t*)ReportData;

    // Check for capslock turning on
    if (*LEDReport & HID_KEYBOARD_LED_CAPSLOCK)
    {
        if (!caps)
        {
            toggle = true;
        }
        caps = true;
    }
    else
    {
        caps = false;
    }
}

