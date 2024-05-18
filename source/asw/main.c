/**
* \file main.c
* \author Z. Sadique
* \date 08.12.2023
*
* \brief <main.c>
*/


#include "global.h"
#include "project.h"
#include "arcadian.h"
#include "reactionGame.h"


/**
 * @brief RGB glow table for a specific pattern (RG_glowtable_1).
 *
 * This table defines a sequence of RGB glow patterns with associated time durations.
 */
const RG__Glow_t RG_glowtable_1[] = {
    /**< Red Green Blue TimeInMS */
    {20, 0, 0, 500},
    {0, 20, 0, 500},
    {0, 0, 20, 500},
    {0, 0, 0, 100},
    {10, 10, 10, 100},
    {0, 0, 0, 100},
    {10, 10, 10, 100},
    {0, 0, 0, 100},
    {10, 10, 10, 100}
};

Fader_t myFader;
RGBGlower_t myRGBGlower;
static Game_t myGame;

/**
 * @brief SysTick interrupt service routine.
 *
 * This function is the interrupt service routine (ISR) for the SysTick timer.
 * The purpose of this ISR is to increment the 'cnt_systick' counter.
 */
ISR(systick_handler)
{
    CounterTick(cnt_systick);
}


/**
 * @brief Task function for automatic system initialization.
 *
 * This task is responsible for initializing various components of the system,
 * including Arcadian and Reaction Ganme modules, configuring ISRs with OS parameters,
 * starting the SysTick timer, activating other tasks, and setting up an alarm for Arcadian
 * with a 1ms cycle time.
 */

TASK(tsk_auto){
    
    /* Initialise Reaction Game and Arcadian */

    ARCADIAN_init(&myFader, &myRGBGlower);
    REACTION_init(&myGame);
        
    /* Reconfigure ISRs with OS parameters.
     * This line MUST be called after the hardware driver initialization!
     */
    EE_system_init();
    
    /* Must be started after interrupt reconfiguration */
    EE_systick_start();
    
    /* Activate tasks for Reaction Game*/
    ActivateTask(tsk_reactionGame);
    
    /* Activate background task*/
    ActivateTask(tsk_background);
    
    /* Start the alarm with a 1ms cycle time */
    SetRelAlarm(alrm_fader ,100,1);
    SetRelAlarm(alrm_glower ,100,0);
    /* Terminate this task after initialization */
    TerminateTask();
}

/**
 * @brief Task function for controlling the Arcadian pattern.
 *
 * This task controls the Arcadian pattern by changing LED intensities
 * based on the current fader counter and updating the RGB LED intensity based on a
 * predefined table (RG_glowtable_1).
 */
TASK(tsk_fader){
    /* Fader Implementation */
    /* Pattern one */

    if (myFader.loopNumber == 0){
        ARCADIAN_changeIntensityBy(Led_Red, -1);
        ARCADIAN_changeIntensityBy(Led_Yellow, 1);
        ++myFader.faderCounter;
    }
    
    /* Pattern two */
    else if (myFader.loopNumber == 1){
        ARCADIAN_changeIntensityBy(Led_Yellow, -1);
        ARCADIAN_changeIntensityBy(Led_Green, 1);  
        ++myFader.faderCounter;
    }
    
    /* Pattern three */
    else if (myFader.loopNumber == 2){
        ARCADIAN_changeIntensityBy(Led_Green, -1);
        ARCADIAN_changeIntensityBy(Led_Red, 1);
        ++myFader.faderCounter;
    }
    
    /* Go to the next loop */
    if (myFader.faderCounter == 255){
        myFader.faderCounter = 0;
        myFader.loopNumber = (myFader.loopNumber + 1) % 3;
        
    } 
    else {
        // do nothing
    }
    
    TerminateTask();
}

TASK(tsk_glower){    
    /* RGB Implementation */ 
    
    /* Change RGB intensity */ 
    ARCADIAN_changeIntensityTo(Led_RGB_Red, RG_glowtable_1[myRGBGlower.currentPositionRGB].redValue);
    ARCADIAN_changeIntensityTo(Led_RGB_Green, RG_glowtable_1[myRGBGlower.currentPositionRGB].greenValue);
    ARCADIAN_changeIntensityTo(Led_RGB_Blue, RG_glowtable_1[myRGBGlower.currentPositionRGB].blueValue);
    
    /* Trigger alarm for next change */ 
    uint16_t nextTrigger = RG_glowtable_1[myRGBGlower.currentPositionRGB].timeInMS; 
    SetRelAlarm(alrm_glower, nextTrigger, 0);
    
    /* Change current position to next one*/ 
    myRGBGlower.currentPositionRGB = (myRGBGlower.currentPositionRGB + 1) % 
        (sizeof(RG_glowtable_1) / sizeof(RG_glowtable_1[0]));

    /* Terminate this task */        
    TerminateTask();
}

/**
 * @brief Task function for handling the Reaction Game events.
 *
 * This task manages the different states of the reaction game, such as
 * waiting for the round to start, waiting for the user's reaction, and handling
 * correct/incorrect responses and timeouts.
 */

TASK(tsk_reactionGame){
    
    EventMaskType ev = 0;
    
    while (1){
        WaitEvent(ev_start_round | ev_start_calculation | ev_stop_calc_correct | ev_stop_calc_incorrect | ev_stop_calc_timeout | ev_restart_game);
        GetEvent(tsk_reactionGame, &ev);
        ClearEvent(ev); 
        
        if (ev & ev_start_round){
            /* if round number is greater than max round, display game details
            *  and set an event to reset the game
            */    
            if (myGame.roundNumber > myGame.maxRounds){
     
                REACTION_displayDetails(&myGame);
                SetEvent(tsk_reactionGame, ev_restart_game);
            }
            
            /* if round number is less than max round, prints the round number,
            * generates a random number, and sets the game state to wait for diplay
            * to show a number
            */
            else {

                //printRoundNumber();
                REACTION_printRoundNumber(myGame.roundNumber);
                
                // generate random time     
                uint16_t randomNumber = 0;
                REACTION_generateRandomNum(&randomNumber, 3);
                
                // trigger the alarm after random seconds                
                SetRelAlarm(alrm_seven, randomNumber*1000, 0);
                myGame.gameState = IsWaitingDisplay;
            }

        } 
        
        else if (ev & ev_restart_game){
            REACTION_resetGame(&myGame);    
        }
        
        else if (ev & ev_start_calculation){
            /* Generates a random number and shows on the 
            * 7 segment display. Once the disply is on, starts another counter 
            * for a maximum of 1 second, which which be used to calculate the reaction
            * time of the user
            */
            
            //REACTION_stopCounter();
            uint16_t randomNumberDisplay = 0;
            REACTION_generateRandomNum(&randomNumberDisplay, 2);
            REACTION_setDisplay(randomNumberDisplay);
            REACTION_startCounterForTime(myGame.durationOfRoundSec);
            myGame.gameState = IsWaitingUserReaction;
     
        }
        else if (ev & ev_stop_calc_correct){
            /* Stops the counter and calculates the rection time in seconds,
            * adds the current reaction time to total time, increments number of 
            * correct button presses, displays a success message, and increments 
            * the number of rounds
            */
            uint16 reactionTime = 0;
            REACTION_getReactionTimeMS(&reactionTime, myGame);
            myGame.totalTime += reactionTime;
            REACTION_resetDisplay();
            ++myGame.correctPresses;
            REACTION_displaySuccessMessage(reactionTime);
            myGame.gameState = IsWaitingRoundStart;
            ++myGame.roundNumber;
        }
        
        else if (ev & ev_stop_calc_incorrect){
            /* Stops the counter and calculates the rection time in seconds,
            * adds the current reaction time to total time, displays a failure
            * message, and increments the number of rounds
            */
            //uint16 reactionTime = 0;
            //REACTION_getReactionTimeMS(&reactionTime);            
            REACTION_resetDisplay();            
            REACTION_displayFailureMessage();            
            myGame.gameState = IsWaitingRoundStart;
            ++myGame.roundNumber;            
        }
        
        else if (ev & ev_stop_calc_timeout){
            /* Stops the counter and displays a timeout
            * message, and increments the number of rounds
            */
            REACTION_stopCounter();            
            REACTION_resetDisplay();            
            REACTION_displayTimeoutMessage();            
            myGame.gameState = IsWaitingRoundStart;            
            ++myGame.roundNumber; 
            
        }        
    }    
    TerminateTask();
}


/**
 * This task sets the event to display a random number on 7-segment display
 * and starts the counter for capturing user's reaction
 */
TASK(tsk_sevenSegment){
    SetEvent(tsk_reactionGame, ev_start_calculation);
    TerminateTask();  
}

/**
 * This ISR is triggered when a button is pressed. It checks the current
 * state of the reaction game and sets events accordingly, such as starting
 * a new round or indicating correct/incorrect user reactions.
 */
ISR2(isr_buttons){
    
    
    if (myGame.gameState == IsWaitingRoundStart){
        SetEvent(tsk_reactionGame, ev_start_round);
    }
    
    else if (myGame.gameState == IsWaitingUserReaction){
        if (REACTION_correctButtonPressed() == TRUE){
            SetEvent(tsk_reactionGame, ev_stop_calc_correct);
        } else {
            SetEvent(tsk_reactionGame, ev_stop_calc_incorrect);
        }
    }

}
/**
 * This ISR is triggered when the timer count reaches 0
 */
ISR2(isr_timer){
    
    if (myGame.gameState == IsWaitingUserReaction){
        SetEvent(tsk_reactionGame, ev_stop_calc_timeout);
    }
    

}

/**
 * @brief Background task function.
 *
 * This task is designed to run indefinitely, serving as a background task.
 */
TASK(tsk_background){
    
    while (1){}
    TerminateTask();
}

/**
 * @brief Main function for the embedded system.
 *
 * This function is the entry point for the embedded system. It enables global
 * interrupts, sets up and starts the SysTick timer with a period of 1 ms, and
 * enters an infinite loop that continuously starts the operating system.
 */
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    
    //Set systick period to 1 ms. Enable the INT and start it.
    EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
    EE_systick_enable_int();

    for(;;)
    {
        StartOS(OSDEFAULTAPPMODE);

    }
}

#if 0
const RG__Glow_t RG_glowtable_1[] = {
//Red Green Blue TimeInMS
{255, 0, 0, 500},
{0, 255, 0, 500},
{0, 0, 255, 500},
{0, 0, 0, 100},
{255, 255, 255, 100},
{0, 0, 0, 100},
{255, 255, 255, 100},
{0, 0, 0, 100},
{255, 255, 255, 100}
};
#endif

/* [] END OF FILE */
