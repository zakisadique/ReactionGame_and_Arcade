/**
* \file arcadian.h
* \author Z. Sadique
* \date 08.12.2023
*
*
* \brief Implements the Reaction Game logic
*
* \copyright Copyright ©2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/

#include <time.h>
#include <stdlib.h>

#include "project.h"
#include "reactionGame.h"
#include "seven.h"
#include "button.h"
#include "Counter.h"
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

/**
 * @brief Variable representing the clock frequency for the reaction game module.
 */
static uint16_t countInOneSec = 12000;

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
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
RC_t REACTION_init(Game_t *game) {
    /* Initialize UART communication. */
    UART_Logs_Start();

    /* Start the clock counter for the Reaction Game. */
    Clock_Counter_RG_Start();

    /* Seed the random number generator. */
    srand(time(NULL));

    /* Set initial values for game state, maximum rounds, and round duration. */
    game->gameState = None;
    game->maxRounds = 10;
    game->durationOfRoundSec = 1;

    /* Display welcome message on UART. */
    UART_Logs_PutString("\nWelcome to the Reaction Game\n");
    UART_Logs_PutString("Press any of the right buttons for '1' and left buttons for '2' \n");

    UART_Logs_PutString("Press any key to begin\n\n");

    /* Set the game state to waiting for the start of a new round. */
    game->gameState = IsWaitingRoundStart;
    /* Set the initial round number to 1. */
    game->roundNumber = 1;

    return RC_SUCCESS;
}

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
RC_t REACTION_resetGame(Game_t *game) {
    /* Display a message on UART. */
    //UART_Logs_PutString("\nReset controller to play again\n");
    UART_Logs_PutString("\nPress any key to play again\n\n");

    /* Reset game parameters. */
    game->roundNumber = 1;
    game->maxRounds = 10;
    game->totalTime = 0;
    game->correctPresses = 0;
    game->gameState = IsWaitingRoundStart;
    
    return RC_SUCCESS;
}

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
RC_t REACTION_generateRandomNum(uint16_t *randomNumber, uint8_t limit) {
    /**
     * Generate a random number using the rand() function.
     * The generated number is within the range [1, limit].
     */
    *randomNumber = rand() % limit + 1;

    return RC_SUCCESS;
}

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
RC_t REACTION_startCounterForTime(uint16_t time) {
    /**
     * Multiply the required time by the global RGClockFrequency.
     * This calculation determines the count needed for the specified duration.
     */
    time = time * countInOneSec;

    /* Start the counter, stop it, set the counter value, and start it again. */
    Counter_Start();
    Counter_Stop();
    Counter_WriteCounter(time);
    Counter_Start();

    return RC_SUCCESS;
}

/**
 * @brief Displays details of the game on UART.
 *
 * This function displays details such as correct presses, total time, and average time
 * of the game on the UART output.
 *
 * @param game Pointer to the Game_t structure containing game details.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_displayDetails(const Game_t *game) {
    /* Display correct presses on UART. */
    UART_Logs_PutString("\nCorrect presses : ");
    char_t buffer[4];
    REACTION_convertToString(game->correctPresses, buffer);
    UART_Logs_PutString(buffer);

    /* Display total time on UART. */
    UART_Logs_PutString("\nTotal time : ");
    REACTION_convertToString(game->totalTime, buffer);
    UART_Logs_PutString(buffer);


    /* Display average time on UART. */
    UART_Logs_PutString("\nAverage time : ");
    REACTION_convertToString(game->totalTime / game->correctPresses, buffer);
    UART_Logs_PutString(buffer);

    return RC_SUCCESS;
}





/**
 * @brief Sets the SEVEN segment display with a specified number.
 *
 * This function sets the SEVEN segment display with the specified number for both SEVEN_0
 * and SEVEN_1 segments.
 *
 * @param randomNumberDisplay The number to be displayed on the SEVEN segment display.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_setDisplay(uint16_t randomNumberDisplay) {
    /* Set the SEVEN segment display for both segments. */
    SEVEN_Set(SEVEN_0, randomNumberDisplay);
    SEVEN_Set(SEVEN_1, randomNumberDisplay);

    return RC_SUCCESS;
}


/**
 * @brief Retrieves the reaction time in milliseconds.
 *
 * This function stops the counter, calculates the reaction time based on the counter value,
 * and returns the result through the provided pointer.
 *
 * @param reactionTime Pointer to the variable where the reaction time will be stored.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_getReactionTimeMS(uint16_t *reactionTime, Game_t game) {
    /* Stop the counter. */
    Counter_Stop();

    /** Calculate the reaction time based on the counter value.
     *  (Difference between clock frequency and current value)/ period * 1000 = reaction time in ms
     */
    
    *reactionTime = (countInOneSec*game.durationOfRoundSec - Counter_ReadCounter()) * 1000 / 
        countInOneSec*game.durationOfRoundSec;

    return RC_SUCCESS;
}


/**
 * @brief Displays a success message on UART with reaction time information.
 *
 * This function displays a success message on UART indicating that the correct button
 * was pressed. It also displays the reaction time in milliseconds.
 *
 * @param reactionTime The reaction time in milliseconds.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_displaySuccessMessage(uint16_t reactionTime) {
    /* Display a success message on UART. */
    UART_Logs_PutString("Great! Correct Button Pressed\n");
    UART_Logs_PutString("Reaction Time in ms: ");

    /* Convert reaction time to string and display it on UART. */
    char_t myBuffer[3];
    REACTION_convertToString(reactionTime, myBuffer);
    UART_Logs_PutString(myBuffer);

    /* Display a message prompting to continue. */
    UART_Logs_PutString("\nPress any button to continue\n\n");

    return RC_SUCCESS;
}


/**
 * @brief Displays a failure message on UART.
 *
 * This function displays a failure message on UART indicating that an incorrect button
 * was pressed. It prompts the user to press any button to continue.
 *
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_displayFailureMessage() {
    /* Display a failure message on UART. */
    UART_Logs_PutString("Incorrect Button Pressed\n");
    /* Display a message prompting to continue. */
    UART_Logs_PutString("Press any button to continue\n\n");

    return RC_SUCCESS;
}


/**
 * @brief Displays a timeout message on UART.
 *
 * This function displays a message on UART indicating that the time ran out.
 * It prompts the user to press any button to continue.
 *
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_displayTimeoutMessage() {
    /* Display a timeout message on UART. */
    UART_Logs_PutString("Time ran out\n");
    /* Display a message prompting to continue. */
    UART_Logs_PutString("Press any button to continue\n\n");

    return RC_SUCCESS;
}

/**
 * @brief Converts a number to a string.
 *
 * This function converts the given number to a string and stores it in the provided buffer.
 *
 * @param number The number to be converted to a string.
 * @param buffer Pointer to the buffer where the string representation will be stored.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_convertToString(uint16_t number, char_t *buffer) {
    if (number == 0){
        buffer[0] = '0';
        buffer[1] = '\0';
        return RC_SUCCESS;
    }
    
    int i = 0;

    /* Convert the number to a string in reverse order. */
    while (number != 0) {
        int digit = number % 10;
        buffer[i++] = digit + '0';
        number = number / 10;
    }

    /* Add null terminator to the end of the string. */
    buffer[i] = '\0';

    /* Reverse the string to get the correct order. */
    REACTION_reverseString(buffer, i);

    return RC_SUCCESS;
}

/**
 * @brief Reverses a string in-place.
 *
 * This function reverses the order of characters in the given string in-place.
 *
 * @param str Pointer to the string to be reversed.
 * @param length The length of the string.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_reverseString(char_t *str, uint8_t length) {
    int start = 0;
    int end = length - 1;

    /* Swap characters from start to end to reverse the string. */
    while (start < end) {
        char_t temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }

    return RC_SUCCESS;
}


/**
 * @brief Prints the start of a new round on UART.
 *
 * This function displays a message on UART indicating the start of a new round,
 * along with the round number.
 *
 * @param roundNumber The number of the current round.
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_printRoundNumber(uint8_t roundNumber) {
    /* Display a message indicating the start of a new round. */
    UART_Logs_PutString("\nRound ");

    /* Convert the round number to a string and display it on UART. */
    char_t myBuffer[2];
    REACTION_convertToString(roundNumber, myBuffer);
    UART_Logs_PutString(myBuffer);

    /* Display a message indicating that the round has started. */
    UART_Logs_PutString(" started!\n");

    return RC_SUCCESS;
}

/**
 * @brief Stops the counter.
 *
 * This function stops the counter used for measuring time.
 *
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_stopCounter() {
    Counter_Stop();
    return RC_SUCCESS;
}

/**
 * @brief Resets the SEVEN segment display.
 *
 * This function initializes the SEVEN segment display to its default state.
 *
 * @return Returns an RC_t (Return Code) indicating the success or failure of the operation.
 */
RC_t REACTION_resetDisplay() {
    SEVEN_Init();
    return RC_SUCCESS;
}

/**
 * @brief Checks if the correct button is pressed based on the SEVEN segment display value.
 *
 * This function retrieves the current value from the SEVEN segment display and checks
 * if the corresponding correct button is pressed.
 *
 * @return Returns TRUE if the correct button is pressed, FALSE otherwise.
 */
boolean_t REACTION_correctButtonPressed() {
    /* Retrieve the current value from the SEVEN segment display. */
    sint8_t currentDisplayVal = 0;
    SEVEN_Get(SEVEN_0, &currentDisplayVal);

    /* Check if the correct button is pressed based on the SEVEN segment display value. */
    if (currentDisplayVal == 1 && (BUTTON_IsPressed(Button_Right_1) || BUTTON_IsPressed(Button_Right_2))) {
        return TRUE;
    } else if (currentDisplayVal == 2 && (BUTTON_IsPressed(Button_Left_1) || BUTTON_IsPressed(Button_Left_2))) {
        return TRUE;
    } else {
        return FALSE;
    }
}

