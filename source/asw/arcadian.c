/**
* \file arcadian.c
* \author Z. Sadique
* \date 08.12.2023
*
* \brief <arcadian.c>
*
* Implements the arcadian
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "project.h"
#include "arcadian.h"
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

static const uint16_t PWMMax = 255;

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * @brief Initializes the ARCADIAN module.
 *
 * This function initializes the ARCADIAN module with the provided fader and
 * glower structures. It sets the initial values for the fader counter, maximum
 * fader value, LED colors, and returns RC_SUCCESS upon successful initialization.
 *
 * @param fader Pointer to the Fader_t structure.
 * @param glower Pointer to the RGBGlower_t structure.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t ARCADIAN_init(Fader_t *fader, RGBGlower_t *glower) {
    /* Initialize fader parameters */
    fader->faderCounter = 0;
    fader->maxFader = PWMMax;
    fader -> loopNumber = 0;

    /* Initialize LED colors for fader */
    PWM_Init(Led_Green);
    PWM_Init(Led_Yellow);
    PWM_Init(Led_Red);

    /* Set Red LED to maximum intensity */
    PWM_Write(Led_Red, PWMMax);

    /* Initialize RGB glower parameters */
    glower->currentPositionRGB = 0;

    /* Initialize LED colors for RGB glower */
    PWM_Init(Led_RGB_Red);
    PWM_Init(Led_RGB_Blue);
    PWM_Init(Led_RGB_Green);

    return RC_SUCCESS;
}

/**
 * @brief Changes the intensity of an LED by a specified amount.
 * This function adjusts the intensity of the specified LED by the given change.
 *
 * @param ledId Identifier of the LED (e.g., Red, Green, Blue).
 * @param change Amount by which to change the LED intensity.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t ARCADIAN_changeIntensityBy(ePWM_t ledId, sint16_t change) {
    /**
     * Adjust the intensity of the specified LED by the given change.
     * The new intensity is calculated by adding the change to the current intensity.
     */
    PWM_Write(ledId, PWM_Read(ledId) + change);

    return RC_SUCCESS;
}

/**
 * @file
 * @brief ARCADIAN module functions.
 */

/**
 * @brief Changes the intensity of an LED to a specific value.
 *
 * This function sets the intensity of the specified LED to the provided value.
 *
 * @param ledId Identifier of the LED (e.g., Red, Green, Blue).
 * @param value New intensity value for the LED.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t ARCADIAN_changeIntensityTo(ePWM_t ledId, sint16_t value) {
    /**
     * @note Set the intensity of the specified LED to the provided value.
    */
    PWM_Write(ledId, value);

    return RC_SUCCESS;
}
    

