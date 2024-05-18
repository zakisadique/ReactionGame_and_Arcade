/**
* \file PWM.c
* \author Z. Sadique
* \date 08.12.2023
*
* \brief Simple PWM driver
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "project.h"
#include "PWM.h"




/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/



/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/
/**
 * @brief Reads the current value of a specified PWM channel.
 *
 * This function reads the current value of the specified PWM channel and returns the result.
 *
 * @param pwm The PWM channel identifier.
 * @return The current value of the specified PWM channel.
 */
uint16_t PWM_Read(ePWM_t pwm){
    uint16_t value = 0;
    switch (pwm){
        case Led_Red:
            value = PWM_led_red_ReadCompare();
            break;
            
        case Led_Yellow:
            value = PWM_led_yellow_ReadCompare();
            break;
            
        case Led_Green:
            value = PWM_led_green_ReadCompare();
            break;
            
        case Led_RGB_Red:
            value = PWM_RGB_red_ReadCompare();
            break;
            
        case Led_RGB_Green:
            value = PWM_RGB_green_ReadCompare();
            break;
            
        case Led_RGB_Blue:
            value = PWM_RGB_blue_ReadCompare();
            break;   
    }
    
    return value;  
}

/**
 * @brief Writes a value to the specified PWM channel.
 *
 * This function writes the given value to the specified PWM channel.
 *
 * @param pwm The PWM channel identifier.
 * @param value The value to be written to the PWM channel.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t PWM_Write(ePWM_t pwm, uint16_t value) {
    switch (pwm) {
        case Led_Red:
            PWM_led_red_WriteCompare(value);
            break;

        case Led_Yellow:
            PWM_led_yellow_WriteCompare(value);
            break;

        case Led_Green:
            PWM_led_green_WriteCompare(value);
            break;

        case Led_RGB_Red:
            PWM_RGB_red_WriteCompare(value);
            break;

        case Led_RGB_Green:
            PWM_RGB_green_WriteCompare(value);
            break;

        case Led_RGB_Blue:
            PWM_RGB_blue_WriteCompare(value);
            break;
    }

    return RC_SUCCESS;
}


/**
 * @brief Initializes the specified PWM channel.
 *
 * This function initializes the specified PWM channel by starting it and setting the initial value to 0.
 *
 * @param pwm The PWM channel identifier.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t PWM_Init(ePWM_t pwm) {
    switch (pwm) {
        case Led_Red:
            PWM_led_red_Start();
            PWM_led_red_WriteCompare(0);
            break;

        case Led_Yellow:
            PWM_led_yellow_Start();
            PWM_led_yellow_WriteCompare(0);
            break;

        case Led_Green:
            PWM_led_green_Start();
            PWM_led_green_WriteCompare(0);
            break;

        case Led_RGB_Red:
            PWM_RGB_red_Start();
            PWM_RGB_red_WriteCompare(0);
            break;

        case Led_RGB_Green:
            PWM_RGB_green_Start();
            PWM_RGB_green_WriteCompare(0);
            break;

        case Led_RGB_Blue:
            PWM_RGB_blue_Start();
            PWM_RGB_blue_WriteCompare(0);
            break;
    }

    return RC_SUCCESS;
}

    
    
    


