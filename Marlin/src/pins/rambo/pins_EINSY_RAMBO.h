/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * Einsy-Rambo pin assignments
 */

#ifndef __AVR_ATmega2560__
  #error "Oops! Select 'Arduino Mega 2560 or Rambo' in 'Tools > Board.'"
#endif

#define BOARD_INFO_NAME "Einsy Rambo"

//
// TMC2130 Configuration_adv defaults for EinsyRambo
//
#if !AXIS_DRIVER_TYPE_X(TMC2130) || !AXIS_DRIVER_TYPE_Y(TMC2130) || !AXIS_DRIVER_TYPE_Z(TMC2130) || !AXIS_DRIVER_TYPE_E0(TMC2130)
  #error "You must set ([XYZ]|E0)_DRIVER_TYPE to TMC2130 in Configuration.h for EinsyRambo."
#endif

// TMC2130 Diag Pins (currently just for reference)
#define X_DIAG_PIN                            64
#define Y_DIAG_PIN                            69
#define Z_DIAG_PIN                            68
#define E0_DIAG_PIN                           65

//
// Limit Switches
//
// Only use Diag Pins when SENSORLESS_HOMING is enabled for the TMC2130 drivers.
// Otherwise use a physical endstop based configuration.
//
// SERVO0_PIN and Z_MIN_PIN configuration for BLTOUCH sensor when combined with SENSORLESS_HOMING.
//

#if DISABLED(SENSORLESS_HOMING)

  #define X_STOP_PIN                          12
  #define Y_STOP_PIN                          11
  #define Z_STOP_PIN                          10

#else

  #define X_STOP_PIN                  X_DIAG_PIN
  #define Y_STOP_PIN                  Y_DIAG_PIN

  #if ENABLED(BLTOUCH)
    #define Z_STOP_PIN                        11  // Y-MIN
    #define SERVO0_PIN                        10  // Z-MIN
  #else
    #define Z_STOP_PIN                        10
  #endif

#endif

//
// Z Probe (when not Z_MIN_PIN)
//
#ifndef Z_MIN_PROBE_PIN
  #define Z_MIN_PROBE_PIN                     10
#endif

//
// Filament Runout Sensor
//
#ifndef FIL_RUNOUT_PIN
  #define FIL_RUNOUT_PIN                      62
#endif

//
// Power Loss Detection
//
#ifndef POWER_LOSS_PIN
  #define POWER_LOSS_PIN                      2
#endif


//
// Steppers
//
#define X_STEP_PIN                            37
#define X_DIR_PIN                             49
#define X_ENABLE_PIN                          29
#define X_CS_PIN                              41

#define Y_STEP_PIN                            36
#define Y_DIR_PIN                             48
#define Y_ENABLE_PIN                          28
#define Y_CS_PIN                              39

#define Z_STEP_PIN                            35
#define Z_DIR_PIN                             47
#define Z_ENABLE_PIN                          27
#define Z_CS_PIN                              67

#define E0_STEP_PIN                           34
#define E0_DIR_PIN                            43
#define E0_ENABLE_PIN                         26
#define E0_CS_PIN                             66

//
// Software SPI pins for TMC2130 stepper drivers
//
#if ENABLED(TMC_USE_SW_SPI)
  #ifndef TMC_SW_MOSI
    #define TMC_SW_MOSI                     PB15
  #endif
  #ifndef TMC_SW_MISO
    #define TMC_SW_MISO                     PB14
  #endif
  #ifndef TMC_SW_SCK
    #define TMC_SW_SCK                      PB13
  #endif
#endif

//
// Temperature Sensors
//
#define TEMP_0_PIN                             0  // Analog Input
#define TEMP_1_PIN                             1  // Analog Input
#define TEMP_BED_PIN                           2  // Analog Input
#define TEMP_PROBE_PIN                         3  // Analog Input
//
// Heaters / Fans
//
#define HEATER_0_PIN                           3
#define HEATER_BED_PIN                         4

#ifndef FAN_PIN
  #define FAN_PIN                              8
#endif

#ifndef FAN1_PIN
  #define FAN1_PIN                             6
#endif

//
// Misc. Functions
//
#define SDSS                                  77
#define LED_PIN                               13

#ifndef CASE_LIGHT_PIN
  #define CASE_LIGHT_PIN                       9
#endif

//
// M3/M4/M5 - Spindle/Laser Control
//
// use P1 connector for spindle pins
#define SPINDLE_LASER_PWM_PIN                  9  // Hardware PWM
#define SPINDLE_LASER_ENA_PIN                 18  // Pullup!
#define SPINDLE_DIR_PIN                       19

//
// Průša i3 MK2 Multiplexer Support
//
#define E_MUX0_PIN                            17
#define E_MUX1_PIN                            16
#define E_MUX2_PIN                            78  // 84 in MK2 Firmware, with BEEPER as 78

/**
 * -------------------------------------Einsy 1.1a--------------------------------------------------------------------
 *                        _____                                                      _____                            |
 *      (OC3A/AIN1)PE3 5 | · · | GND                          |                   5V | · · | GND                      |
 *                nRESET | · · | 15 PJ0(RXD3/PCINT9) (SD_DET) |(LCD_D7)(TOSC2)PG3 71 | · · | 85 PH7(T4)(LCD_D6)       |
 *   (MOSI/PCINT2)PB2 51 | · · | 14 J1(TXD3/PCINT10)(BTN_EN2) |(LCD_D5)(TOSC1)PG4 70 | · · | 59 PF5(TMS/ADC5)(LCD_D4) |
 *(SD_SS)(PCINT15)PJ6 77 | · · | 72 PJ2(XCK3/PCINT11)(BTN_EN1)|(LCD_RS)(XCK1)PD5  82 | · · | 61 PF7(TDI/ADC7)(LCD_EN) |
 *    (SCK/PCINT1)PB1 52 | · · | 50 PB3(PCINT3/MISO)          |(BTN_ENC)(OC2B)PH6  9 | · · | 84 PH2(XCK2)(BEEPER)     |
 *                        ￣￣￣                                                      ￣￣                             |
 *                        EXP2                                                        EXP1                            |
 * -------------------------------------------------------------------------------------------------------------------
 */

//
// LCD / Controller
//
#if HAS_SPI_LCD || TOUCH_UI_ULTIPANEL

  #define KILL_PIN                            32

  #if ENABLED(ULTIPANEL) || TOUCH_UI_ULTIPANEL

    #if ENABLED(CR10_STOCKDISPLAY)
      #define LCD_PINS_RS                     85
      #define LCD_PINS_ENABLE                 71
      #define LCD_PINS_D4                     70
      #define BTN_EN1                         61
      #define BTN_EN2                         59
    #else
      #define LCD_PINS_RS                     82
      #define LCD_PINS_ENABLE                 61
      #define LCD_PINS_D4                     59
      #define LCD_PINS_D5                     70
      #define LCD_PINS_D6                     85
      #define LCD_PINS_D7                     71
      #define BTN_EN1                         14
      #define BTN_EN2                         72
    #endif

    #define BTN_ENC                            9  // AUX-2
    #define BEEPER_PIN                        84  // AUX-4
    #define SD_DETECT_PIN                     15

  #endif // ULTIPANEL || TOUCH_UI_ULTIPANEL
#endif // HAS_SPI_LCD
