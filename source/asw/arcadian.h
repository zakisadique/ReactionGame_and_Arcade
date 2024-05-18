/**
* \file arcadian.h
* \author Z. Sadique
* \date 08.12.2023
*
* \brief <arcadian.h>
*
* Implements the arcadian
*/

/**
 * Programming rules (may be deleted in the final release of the file)
 * ===================================================================
 *
 * 1. Naming conventions:
 *    - Prefix of your module in front of every function and static data. 
 *    - Scope _ for public and __ for private functions / data / types, e.g. 
 *       Public:  void CONTROL_straightPark_Init();
 *       Private: static void CONTROL__calcDistance();
 *       Public:  typedef enum {RED, GREEN, YELLOW} CONTROL_color_t
 *    - Own type definitions e.g. for structs or enums get a postfix _t
 *    - #define's and enums are written in CAPITAL letters
 * 2. Code structure
 *    - Be aware of the scope of your modules and functions. Provide only functions which belong to your module to your files
 *    - Prepare your design before starting to code
 *    - Implement the simple most solution (Too many if then else nestings are an indicator that you have not properly analysed your task)
 *    - Avoid magic numbers, use enums and #define's instead
 *    - Make sure, that all error conditions are properly handled
 *    - If your module provides data structures, which are required in many other files, it is recommended to place them in a file_type.h file
 *	  - If your module contains configurable parts, is is recommended to place these in a file_config.h|.c file
 * 3. Data conventions
 *    - Minimize the scope of data (and functions)
 *    - Global data is not allowed outside of the signal layer (in case a signal layer is part of your design)
 *    - All static objects have to be placed in a valid linker sections
 *    - Data which is accessed in more than one task has to be volatile and needs to be protected (e.g. by using messages or semaphores)
 *    - Do not mix signed and unsigned data in the same operation
 * 4. Documentation
 *    - Use self explaining function and variable names
 *    - Use proper indentation
 *    - Provide Javadoc / Doxygen compatible comments in your header file and C-File
 *    		- Every  File has to be documented in the header
 *			- Every function parameter and return value must be documented, the valid range needs to be specified
 *     		- Logical code blocks in the C-File must be commented
 *    - For a detailed list of doxygen commands check http://www.stack.nl/~dimitri/doxygen/index.html 
 * 5. Qualification
 *    - Perform and document design and code reviews for every module
 *    - Provide test specifications for every module (focus on error conditions)
 *
 * Further information:
 *    - Check the programming rules defined in the MIMIR project guide
 *         - Code structure: https://fromm.eit.h-da.de/intern/mimir/methods/eng_codestructure/method.htm
 *         - MISRA for C: https://fromm.eit.h-da.de/intern/mimir/methods/eng_c_rules/method.htm
 *         - MISRA for C++: https://fromm.eit.h-da.de/intern/mimir/methods/eng_cpp_rules/method.htm 
 **/
 
#ifndef ARCADIAN_H
#define ARCADIAN_H

#include "global.h"
#include "PWM.h"
    
/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/
    
///////////////////////////////////////////////////////////////////////////////  
    
/**
 * @brief Structure representing a fader.
 *
 * This structure contains information related to a fader, such as the
 * current fader counter and the maximum fader value.
 */
typedef struct {
    uint16_t faderCounter; /**< Current value of the fader counter. */
    uint8_t maxFader;      /**< Maximum value of the fader counter. */
    uint8_t loopNumber;    /**< Current loop of the fader counter.  */
} Fader_t;

/**
 * @brief Structure representing RGB glow parameters.
 *
 * This structure contains information about the intensity values for red, green,
 * and blue, along with the time duration in milliseconds for a specific RGB glow.
 */
typedef struct {
    uint8_t redValue;    /**< Red intensity value. */
    uint8_t greenValue;  /**< Green intensity value. */
    uint8_t blueValue;   /**< Blue intensity value. */
    uint16_t timeInMS;   /**< Time duration in milliseconds. */
} RG__Glow_t;

/**
 * @brief Structure representing RGB glower state.
 *
 * This structure maintains the current position in the RGB glow table and
 * the elapsed time for the current RGB glow.
 */
typedef struct {
    uint8_t currentPositionRGB;
}RGBGlower_t;

// Wrapper to allow representing the file in Together as class
#ifdef TOGETHER

class Arcadian
{
public:
#endif /* Together */

/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/



/*****************************************************************************/
/* API functions                                                             */
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
RC_t ARCADIAN_init(Fader_t *fader, RGBGlower_t* glower);

/**
 * @brief Changes the intensity of an LED by a specified amount.
 *
 * This function adjusts the intensity of the specified LED by the given change.
 *
 * @param ledId Identifier of the LED (e.g., Red, Green, Blue).
 * @param change Amount by which to change the LED intensity.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t ARCADIAN_changeIntensityBy(ePWM_t ledId, sint16_t change);

/**
 * @brief Changes the intensity of an LED to a specific value.
 *
 * This function sets the intensity of the specified LED to the provided value.
 *
 * @param ledId Identifier of the LED (e.g., Red, Green, Blue).
 * @param intensity New intensity value for the LED.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t ARCADIAN_changeIntensityTo(ePWM_t ledId, sint16_t change);


/*****************************************************************************/
/* Private stuff, only visible for Together, declared static in cpp - File   */
/*****************************************************************************/


#ifdef TOGETHER
//Not visible for compiler, only used for document generation
private:
};
#endif /* Together */

#endif /* ARCADIAN_H */
