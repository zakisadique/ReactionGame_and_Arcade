/**
* \file arcadian.h
* \author Z. Sadique
* \date 08.12.2023
*
* \brief <reactionGame.h>
*
* Implements the logic for reaction game
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
 
#ifndef REACTION_GAME_H
#define REACTION_GAME_H

#include "global.h"
    
/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/


typedef enum {
    IsWaitingRoundStart,    /**< Waiting for the start of a new round.    */
    IsWaitingDisplay,       /**< Waiting for the display to show a digit. */
    IsWaitingUserReaction,  /**< Waiting for the user to react.           */
    None                    /**< No specific state (uninitialized).       */
} GameStates;

/**
 * @brief Structure representing the state and statistics of the game.
 */
typedef struct Game_t{
    GameStates gameState;          /**< Current state of the game. */
    uint8_t  roundNumber;          /**< Current round number. */
    uint16_t totalTime;            /**< Total time accumulated across all rounds. */
    uint8_t correctPresses;        /**< Number of correct user presses. */
    uint8_t  maxRounds;            /**< Maximum number of rounds for the game. */
    uint8_t durationOfRoundSec;    /**< Duration of each round in seconds. */
} Game_t;

// Wrapper to allow representing the file in Together as class
#ifdef TOGETHER

class reactionGame
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
 * @brief Initializes the REACTION module.
 *
 * This function initializes the Reaction Game module by performing the following steps:
 * - Initializing UART communication.
 * - Starting the clock counter for the Reaction Game.
 * - Seeding the random number generator.
 * - Setting initial values for the game state, maximum rounds, and round duration.
 * - Displaying a welcome message on the UART.
 * - Setting the game state to waiting for the start of a new round.
 * - Setting the initial round number to 1.
 *
 * @param game Pointer to the Game_t structure.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_init(Game_t* game);
/**
 * @brief Prints the start of a new round on UART.
 *
 * This function displays a message on UART indicating the start of a new round,
 * along with the round number.
 *
 * @param roundNumber The number of the current round.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_printRoundNumber(uint8_t roundNumber);
/**
 * @brief Displays details of the game on UART.
 *
 * This function displays details such as correct presses, total time, and average time
 * of the game on the UART output.
 *
 * @param game Pointer to the Game_t structure containing game details.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_displayDetails(const Game_t* game);
/**
 * @brief Resets the game state for playing again.
 *
 * This function resets the game state to prepare for playing again. It displays a
 * message on UART, resets the round number, total time, correct presses, and sets
 * the game state to waiting for the start of a new round.
 *
 * @param game Pointer to the Game_t structure containing game details.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_resetGame(Game_t* game);
/**
 * @brief Displays a success message on UART with reaction time information.
 *
 * This function displays a success message on UART indicating that the correct button
 * was pressed. It also displays the reaction time in milliseconds.
 *
 * @param reactionTime The reaction time in milliseconds.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_displaySuccessMessage(uint16_t reactionTime);
/**
 * @brief Displays a failure message on UART.
 *
 * This function displays a failure message on UART indicating that an incorrect button
 * was pressed. It prompts the user to press any button to continue.
 *
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_displayFailureMessage();
/**
 * @brief Displays a timeout message on UART.
 *
 * This function displays a message on UART indicating that the time ran out.
 * It prompts the user to press any button to continue.
 *
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_displayTimeoutMessage();
/**
 * @brief Sets the SEVEN segment display with a specified number.
 *
 * This function sets the SEVEN segment display with the specified number for both SEVEN_0
 * and SEVEN_1 segments.
 *
 * @param randomNumberDisplay The number to be displayed on the SEVEN segment display.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_setDisplay(uint16_t randomNumberDisplay);
/**
 * @brief Stops the counter.
 *
 * This function stops the counter used for measuring time.
 *
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_stopCounter();
/**
 * @brief Resets the SEVEN segment display.
 *
 * This function initializes the SEVEN segment display to its default state.
 *
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_resetDisplay();
/**
 * @brief Generates a random number within a specified limit.
 *
 * This function generates a random number within the specified limit and
 * returns it through the provided pointer.
 *
 * @param randomNumber Pointer to the variable where the random number will be stored.
 * @param limit The upper limit for the random number (exclusive).
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_generateRandomNum (uint16_t* randomNumber,  uint8_t limit);

/**
 * @brief Starts a counter for a specified duration.
 *
 * This function starts a counter for a duration specified by the provided random number,
 * which is multiplied by the global RGClockFrequency. The counter is configured to
 * stop after reaching the specified count.
 *
 * @param randomNumber The random number used to calculate the counter duration.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_startCounterForTime(uint16_t randomNumber);
/**
 * @brief Retrieves the reaction time in milliseconds.
 *
 * This function stops the counter, calculates the reaction time based on the counter value,
 * and returns the result through the provided pointer.
 *
 * @param reactionTime Pointer to the variable where the reaction time will be stored.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_getReactionTimeMS(uint16_t* reactionTime, Game_t game);
/**
 * @brief Converts a number to a string.
 *
 * This function converts the given number to a string and stores it in the provided buffer.
 *
 * @param number The number to be converted to a string.
 * @param buffer Pointer to the buffer where the string representation will be stored.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_convertToString(uint16_t number, char_t* buffer);
/**
 * @brief Reverses a string in-place.
 *
 * This function reverses the order of characters in the given string in-place.
 *
 * @param str Pointer to the string to be reversed.
 * @param length The length of the string.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_reverseString(char_t* str, uint8_t length);
/**
 * @brief Checks if the correct button is pressed based on the SEVEN segment display value.
 *
 * This function retrieves the current value from the SEVEN segment display and checks
 * if the corresponding correct button is pressed.
 *
 * @return Returns TRUE if the correct button is pressed, FALSE otherwise.
 */
boolean_t REACTION_correctButtonPressed();


/*****************************************************************************/
/* Private stuff, only visible for Together, declared static in cpp - File   */
/*****************************************************************************/


#ifdef TOGETHER
//Not visible for compiler, only used for document generation
private:
};
#endif /* Together */

#endif /* REACTION_GAME_H */
