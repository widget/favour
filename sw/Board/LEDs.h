/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *  There are FIVE LIGHTS!  Which also run off 5V or 3V3 as Vcc is variable
 */

#ifndef __LEDS_MINIMUS_H__
#define __LEDS_MINIMUS_H__

bool high_power = true;

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_LEDS_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/LEDS.h instead.
		#endif

		
	/* Public Interface - May be used in end-application: */
		/* Macros: */
            #define LED_LOW1 (1 << 2)
            #define LED_LOW2 (1 << 4)
            #define LED_LOW3 (1 << 5)
            #define LED_LOW4 (1 << 6)
            #define LED_LOW5 (1 << 7)
            #define LED_LOW_ALL 0xf4

            #define LED_HIGH1 (1 << 0)
            #define LED_HIGH2 (1 << 4)
            #define LED_HIGH3 (1 << 5)
            #define LED_HIGH4 (1 << 6)
            #define LED_HIGH5 (1 << 7)
            #define LED_HIGH_ALL 0xf1
            
            #define LED1 (1 << 0)
            #define LED2 (1 << 1)
            #define LED3 (1 << 2)
            #define LED4 (1 << 3)
            #define LED5 (1 << 4)
            #define LED_ALL 0x1f

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void LEDs_Init(bool high)
			{
                high_power = high;
                if (high_power)
                {
                    // Ensure the low io pins are hiZ
                    DDRC &= ~(LED_LOW_ALL);
                    // Set the high io pins to output high (LED off)
                    DDRB  |= LED_HIGH_ALL;
                    PORTB |= LED_HIGH_ALL;
                }
                else
                {
                    // Ensure the low io pins are hiZ
                    DDRB &= ~(LED_HIGH_ALL);
                    // Set the high io pins to output high (LED off)
                    DDRC  |= LED_LOW_ALL;
                    PORTC |= LED_LOW_ALL;
                }
			}

			static inline void LEDs_Disable(void)
			{
                DDRB &= ~(LED_HIGH_ALL);
                DDRC &= ~(LED_LOW_ALL);
			}

			static inline void LEDs_TurnOnLEDs(const uint8_t LEDMask)
			{
                uint8_t m;
                if (high_power)
                {
                    m = ((LEDMask & 0x1e) << 3) | (LEDMask & 0x1);
                    PORTB &= ~m;
                }
                else
                {
                    m = ((LEDMask & 0x1e) << 3) | ((LEDMask & 0x1) << 2);
                    PORTC &= ~m;
                }
			}

			static inline void LEDs_TurnOffLEDs(const uint8_t LEDMask)
			{
                uint8_t m;
                if (high_power)
                {
                    m = ((LEDMask & 0x1e) << 3) | (LEDMask & 0x1);
                    PORTB |= m;
                }
                else
                {
                    m = ((LEDMask & 0x1e) << 3) | ((LEDMask & 0x1) << 2);
                    PORTC |= m;
                }
			}

			static inline void LEDs_SetAllLEDs(const uint8_t LEDMask)
			{
                uint8_t m;
                if (high_power)
                {
                    m = ((LEDMask & 0x1e) << 3) | (LEDMask & 0x1);
                    PORTB = (PORTB | LED_HIGH_ALL) & ~m;
                }
                else
                {
                    m = ((LEDMask & 0x1e) << 3) | ((LEDMask & 0x1) << 2);
                    PORTC = (PORTC | LED_LOW_ALL)  & ~m;
                }
			}

			static inline void LEDs_ChangeLEDs(const uint8_t LEDMask,
			                                   const uint8_t ActiveMask)
			{
				//PORTD = ((PORTD & ~LEDMask) | ActiveMask);
			}

			static inline void LEDs_ToggleLEDs(const uint8_t LEDMask)
			{
                uint8_t m;
                if (high_power)
                {
                    m = ((LEDMask & 0x1e) << 3) | (LEDMask & 0x1);
                    PINB = m;
                }
                else
                {
                    m = ((LEDMask & 0x1e) << 3) | ((LEDMask & 0x1) << 2);
                    PINC = m;
                }
			}

			static inline uint8_t LEDs_GetLEDs(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t LEDs_GetLEDs(void)
			{
				//return (~PORTD & LEDS_ALL_LEDS);
                return false;
			}
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

