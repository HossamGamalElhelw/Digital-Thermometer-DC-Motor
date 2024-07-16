/*
 * File:   application.h
 * Author: Hossam Gamal
 *
 * Created on October 12, 2023, 2:28 PM
 */

#ifndef APPLICATION_H
#define APPLICATION_H
/*Section : Includes */
#include "ECU_Layer/ecu_layer_init.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "MCAL_Layer/ADC/hal_adc.h"
#include "ECU_Layer/Chr_LCD/ecu_chr_lcd.h"
#include "ECU_Layer/DC_Motor/ecu_dc_motor.h"
#include "ECU_Layer/LCD/ecu_led.h"

/*Section : Macro Declarations */

/*Section : Data Type Declarations*/
extern chr_lcd_4bit_t lcd_obj;
extern dc_motor_t dc_motor_1;
extern dc_motor_t dc_motor_2;

/*Section : Function Declarations*/
void application_intialize(void);
void Lcd_Interface(void);
#endif /* APPLICATION_H */
