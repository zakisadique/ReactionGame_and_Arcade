/**
* \file arcadian.h
* \author Z. Sadique
* \date 08.12.2023
*
* \brief Simple button driver
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "project.h"
#include "button.h"


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
 * @brief Checks if a specific button is pressed.
 *
 * This function checks the state of the specified button and returns TRUE if the button is pressed,
 * or FALSE if it is not pressed.
 *
 * @param button The identifier of the button to check.
 * @return Returns TRUE if the specified button is pressed, FALSE otherwise.
 */
boolean_t BUTTON_IsPressed(BUTTON_id_t button) {
    boolean_t result = FALSE;

    switch (button) {
        case Button_Right_1:
            if (Button_Right_1_Read() == 1) result = TRUE;
            break;
        case Button_Right_2:
            if (Button_Right_2_Read() == 1) result = TRUE;
            break;
        case Button_Left_1:
            if (Button_Left_1_Read() == 1) result = TRUE;
            break;
        case Button_Left_2:
            if (Button_Left_2_Read() == 1) result = TRUE;
            break;
    }

    return result;
}

