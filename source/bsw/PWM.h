/**
* \file PWM.h
* \author Z. Sadique
* \date 08.12.2023
*
* \brief Simple PWM driver
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
 
#ifndef PWM_H
#define PWM_H

#include "global.h"
    
/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

//####################### Enumerations

/**
 * @brief Enumeration of PWM identifiers.
 */
typedef enum ePWM {
    Led_Red,        /**< Red LED */
    Led_Yellow,     /**< Yellow LED */
    Led_Green,      /**< Green LED */
    Led_RGB_Red,    /**< Red component of RGB LED */
    Led_RGB_Green,  /**< Green component of RGB LED */
    Led_RGB_Blue    /**< Blue component of RGB LED */
} ePWM_t;


// Wrapper to allow representing the file in Together as class
#ifdef TOGETHER

class PWM
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
 * @brief Initializes the specified PWM channel.
 *
 * This function initializes the specified PWM channel by starting it and setting the initial value to 0.
 *
 * @param pwm The PWM channel identifier.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t PWM_Init(ePWM_t pwm);
/**
 * @brief Reads the current value of a specified PWM channel.
 *
 * This function reads the current value of the specified PWM channel and returns the result.
 *
 * @param pwm The PWM channel identifier.
 * @return The current value of the specified PWM channel.
 */
uint16_t PWM_Read(ePWM_t pwm);
/**
 * @brief Writes a value to the specified PWM channel.
 *
 * This function writes the given value to the specified PWM channel.
 *
 * @param pwm The PWM channel identifier.
 * @param value The value to be written to the PWM channel.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t PWM_Write(ePWM_t pwm, uint16_t value);



/*****************************************************************************/
/* Private stuff, only visible for Together, declared static in cpp - File   */
/*****************************************************************************/


#ifdef TOGETHER
//Not visible for compiler, only used for document generation
private:
};
#endif /* Together */

#endif /* PWM_H */
