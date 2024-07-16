/*
 * File:   application.c
 * Author: Hossam Gamal
 *
 * Created on October 12, 2023, 1:35 PM
 */

#include "application.h"

/*->>> LCD <<<-*/
chr_lcd_4bit_t lcd_obj = {
    /* RS */
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    /* EN */
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    /* 4-Pins */
    /* D0 */
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    /* D1 */
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[1].port = PORTC_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    /* D2 */
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[2].port = PORTC_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    /* D3 */
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW,
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = GPIO_PIN5,
};
/*->>> MOTOR-1 <<<-*/
dc_motor_t dc_motro_1 = {
    /* PIN1 */
    .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pin[0].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[0].port = PORTD_INDEX,
    .dc_motor_pin[0].pin = GPIO_PIN0,
    /* PIN2 */
    .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pin[1].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[1].port = PORTD_INDEX,
    .dc_motor_pin[1].pin = GPIO_PIN1,
};
/*->>> MOTOR-2 <<<-*/
dc_motor_t dc_motro_2 = {
    /* PIN1 */
    .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pin[0].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[0].port = PORTD_INDEX,
    .dc_motor_pin[0].pin = GPIO_PIN2,
    /* PIN2 */
    .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pin[1].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor_pin[1].port = PORTD_INDEX,
    .dc_motor_pin[1].pin = GPIO_PIN3,
};
/*->>> ADC <<<-*/
adc_conf_t adc_obj = {
    .ADC_InterruptHandler = NULL,
    .acquisition_time = ADC_12_TAD,
    .adc_channel = ADC_CHANNEL_AN0,
    .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .result_format = ADC_RESULT_RIGHT,
    .voltage_reference = ADC_VOLTAGE_REFERENCE_DISABLED,
};

/* ->>>> LM 35 <<<<-*/

uint16 lm35_res_1, lm35_res_2, lm35_res_1_Celsius_MV = 0, lm35_res_2_Celsius_MV = 0;
uint8 lm35_res_1_txt[7], lm35_res_2_txt[7];

int main()
{
    Std_ReturnType ret = E_NOT_OK;
    application_intialize();
    Lcd_Interface();
    while (1)
    {
        ret = ADC_GetConversion_Blocking(&adc_obj, ADC_CHANNEL_AN0, &lm35_res_1);
        ret = ADC_GetConversion_Blocking(&adc_obj, ADC_CHANNEL_AN1, &lm35_res_2);

        lm35_res_1_Celsius_MV = lm35_res_1 * 4.88f;
        lm35_res_2_Celsius_MV = lm35_res_2 * 4.88f;

        lm35_res_1_Celsius_MV /= 10;
        lm35_res_2_Celsius_MV /= 10;

        ret = convert_uint16_to_string(lm35_res_1_Celsius_MV, lm35_res_1_txt);
        ret = convert_uint16_to_string(lm35_res_2_Celsius_MV, lm35_res_2_txt);

        ret = lcd_4bit_send_string_data_pos(&lcd_obj, 2, 8, lm35_res_1_txt);
        ret = lcd_4bit_send_string_data_pos(&lcd_obj, 3, 8, lm35_res_2_txt);

        /* ->>>Condition of Motors <<<<-*/
        if (36 <= lm35_res_1_Celsius_MV)
        {
            ret = dc_motor_move_right(&dc_motro_1);
        }
        else
        {
            ret = dc_motor_stop(&dc_motro_1);
        }
        if (36 <= lm35_res_2_Celsius_MV)
        {
            ret = dc_motor_move_right(&dc_motro_2);
        }
        else
        {
            ret = dc_motor_stop(&dc_motro_2);
        }
    }
    return (EXIT_SUCCESS);
}

void application_intialize(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = lcd_4bit_initialize(&lcd_obj);
    ret = dc_motor_initialize(&dc_motro_1);
    ret = dc_motor_initialize(&dc_motro_2);
    ret = ADC_Init(&adc_obj);
}
void Lcd_Interface(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = lcd_4bit_send_string_data_pos(&lcd_obj, 1, 5, "Test LM35");
    ret = lcd_4bit_send_string_data_pos(&lcd_obj, 2, 1, "Temp1: ");
    ret = lcd_4bit_send_string_data_pos(&lcd_obj, 3, 1, "Temp2: ");
}
