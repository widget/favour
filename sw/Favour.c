
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

// TODO change to 31
#define LED_MAX_BRIGHT 16
#define LED_FREQ 248
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
    if (fcount >= (LED_FREQ >> 5))
    {
        fcount = 0;
        ticks++;
    }
    
    LEDs_SetAllLEDs(led_pwm[count]);
}

void set_led_pwm(const uint8_t led, const uint8_t bright)
{
    for (uint8_t i = 0; i < LED_MAX_BRIGHT; i++)
    {
        // Shift LED PWM patterns some
        uint8_t which = (i + (led*3)) % LED_MAX_BRIGHT;
        if (i < bright)
            led_pwm[which] |= _BV(led);
        else
            led_pwm[which] &= (uint8_t)~_BV(led);
    }
}

// default to zero, save ram, the AVR way
bool usb_present = true, hwb_last;
uint16_t last_press;
bool toggle;
uint8_t pattern_count;
    
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
    if (usb_present)
    {
        memcpy_P(&current_pattern, PATTERNS_HI, sizeof(pattern_t));
    }
    else
    {
        memcpy_P(&current_pattern, PATTERNS_LO, sizeof(pattern_t));
    }
    GlobalInterruptEnable();
    for (;;)
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
        
        if (usb_present)
        {
            HID_Device_USBTask(&Keyboard_HID_Interface);
            USB_USBTask();
            
            // Cycle onto the next pattern if caps is toggled and numlock is off
            if (toggle)
            {
                // Next pattern
                pattern_idx = (pattern_idx + 1) % NUM_PATTERNS_HI;
                // Copy it in
                memcpy_P(&current_pattern, PATTERNS_HI+pattern_idx, sizeof(pattern_t));
                // And restart
                idx = 0;
                
                toggle = false;
            }
        }
        else
        {
            if (pattern_count == 150)
            {
                pattern_idx = (pattern_idx + 1) % NUM_PATTERNS_LO;
                memcpy_P(&current_pattern, PATTERNS_LO+pattern_idx, sizeof(pattern_t));
                idx = 0;
                pattern_count = 0;
            }
            sei();
            sleep_cpu();
        }
        
        // TODO Check if HWB is pressed, and cycle pattern based on it
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
        
        // Check power hasn't changed
        bool new_usb_present = !(Buttons_GetStatus() & BUTTONS_VCC);
        if (usb_present != new_usb_present)
        {
            // RESET
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
    usb_present = !(Buttons_GetStatus() & BUTTONS_VCC);
    
    LEDs_Init(usb_present);
    
    TCNT0  = 0x00; // start value
    TIFR0 = 0; // clear interrupt flags just in case
    TIMSK0 = _BV(OCIE0A); // Interrupt enable on compare A
    TCCR0A = 0x02; // Clear Timer on Compare (CTC) mode
        
    if (usb_present)
    {
        /* Disable clock division */
        clock_prescale_set(clock_div_1);
        USB_Init();
        
        OCR0A  =   33; // 4.96kHz
        // set timer0 to be 16MHz/64 = 8andabit kHz
        TCCR0B = 0x03;
    }
    else
    {
        // once tested, try 128
        clock_prescale_set(clock_div_8);
        
        USB_Disable();
        
        power_usb_disable();
        power_spi_disable();
        power_timer1_disable();
        power_usart1_disable();
        // disable analogue comparator
        ACSR |= _BV(ACD);
        
        // TODO we need to disable BOD and debug fuses
        
        if (bit_is_set(CLKSEL0,CLKS))
        {
            // Turn off RC osc too
            CLKSEL0 &= ~(1 << RCE);
        }
        
        // this should be the default
        set_sleep_mode(SLEEP_MODE_IDLE);
        sleep_enable();
        
        OCR0A  =   249; // 400Hz
        // Set timer0 to be 8/(8*1) - 125kHz
        TCCR0B = 0x01;
    }
    
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
    //LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
    //LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
    bool ConfigSuccess = true;

    ConfigSuccess &= HID_Device_ConfigureEndpoints(&Keyboard_HID_Interface);

    USB_Device_EnableSOFEvents();

    //LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
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
    USB_KeyboardReport_Data_t* KeyboardReport = (USB_KeyboardReport_Data_t*)ReportData;

    uint8_t ButtonStatus_LCL = Buttons_GetStatus();

    uint8_t UsedKeyCodes = 0;

    /*if (ButtonStatus_LCL & BUTTONS_HWB)
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

