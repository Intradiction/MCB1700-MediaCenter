#include <stdbool.h>
#include <LPC17xx.H>
#include <string.h>
#include "GLCD.h"
#include "KBD.h"
#include "quizgame.h"

#define NUM_QUESTIONS 3
#define NUM_ANSWERS 3

void startQuizGame() {
	char questions[NUM_QUESTIONS*(NUM_ANSWERS+1)][40] = {
	"Q1: 1 + 1 = ?", "a) 0", "b) 1", "c) 2",
	"Q2: Board's Name?", "a) MCB1700", "b) Keil uVision", "c) IBM1900",
	"Q3: What was Lab 4?", "a) RTX scheduling", "b) Prio Inv", "c) Debugging",
	};
	
	char answers[NUM_QUESTIONS][20] = {
		"c) 2",
		"a) MCB1700",
		"b) Prio Inv"
	};
	
	int currentUserSelection = 0, currentQuestionIndex = 0, score = 0;
	char scoreString[20];
	char indicator; 
	
	bool running = true, gameOverScreen = true;
	int joystick_val = 0, joystick_prev = 0;
	int i, j, k;
	
	GLCD_SetBackColor(DarkCyan);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(0, 0, 1, "     Quiz  Game     ");
	
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	


		

	//GLCD_DisplayString(8, 0, 1, "DOWN = return to MM");
	//GLCD_DisplayString(9, 0, 1, "LEFT, RIGHT = scroll");
	
	while(running) {
		// display current question
		GLCD_DisplayString(2, 1, 1, questions[currentQuestionIndex*(NUM_ANSWERS+1)]);
		
		// display current possible answers
		for (j = 0; j < NUM_ANSWERS; j++) {
			GLCD_DisplayString(4+j, 1, 1, questions[currentQuestionIndex*(NUM_ANSWERS+1)+j+1]);
		}
		
		joystick_val = get_button();
		
		if (joystick_val != joystick_prev){
			switch (joystick_val) {
				case KBD_DOWN:
					if (currentUserSelection < NUM_ANSWERS-1)
						currentUserSelection += 1;
					break;
				case KBD_UP:
					if (currentUserSelection > 0)
						currentUserSelection -= 1;
					break;
				case KBD_SELECT:
					// if answer right
					if (!strcmp(questions[currentQuestionIndex*(NUM_ANSWERS+1)+currentUserSelection+1], answers[currentQuestionIndex])){
						score++;
					}
					currentQuestionIndex++;
					// Check if game over
					if(currentQuestionIndex >= NUM_QUESTIONS){
						running = false;
					}
					break;
				case KBD_RIGHT:
					running = false;
					break;
			}
			joystick_prev = joystick_val;
		}
		
		// display indicator next to currentUserSelection
		for (k = 0; k < NUM_ANSWERS; k++) {
			GLCD_SetBackColor(White);
			GLCD_SetTextColor(Black);
			indicator = ' ';
			if (k == currentUserSelection)
				indicator = '>';
			GLCD_DisplayChar(4+k, 0, 1, indicator);
		}
		
		// display current score
		snprintf(scoreString, 20, "Score: %d", score);
		GLCD_SetBackColor(White);
		GLCD_DisplayString(8, 1, 1, scoreString);
	
	}
	GLCD_Clear(White);
	while(gameOverScreen){
		GLCD_DisplayString(4, 0, 1, "     Game Over!     ");
		GLCD_DisplayString(5, 6, 1, scoreString);
		
		joystick_prev = 0;
		joystick_val = get_button();
		if (joystick_val != joystick_prev){
			switch (joystick_val) {
				case KBD_SELECT:
					gameOverScreen = false;
					break;
			}
		}
	}
}
