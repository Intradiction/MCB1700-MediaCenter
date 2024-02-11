/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher and Graphic Demo
 * Note(s): 
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2008-2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/
                  
#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
#include "usbdmain.h"
#include "snake.h"
#include "PhotoGallery.h"
#include "quizgame.h"

extern int audio_main (void);


/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) 
{  	/* Main Program                       */
	int currentUserSelection = 0; // 0 = Photo Gallery, 1 = Audio Player, 2 = Quiz Game, 3 = Snake Game
	int joystick_val = 0, joystick_prev = 0;   // track joystick's prev val, stops joystick from skipping too fast
	
	KBD_Init();

  LED_Init ();
  GLCD_Init();

  GLCD_Clear  (White);
  SysTick_Config(SystemCoreClock/100); 
	GLCD_Clear(White);
	GLCD_SetBackColor(DarkCyan);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(0, 0, 1, "    Media Center    ");
	GLCD_DisplayString(1, 0, 1, "     Main  Menu     ");
	GLCD_SetTextColor(Black);

  for (;;)		//loop forever
	{
			
			joystick_val = get_button();	
		
			// this comparison prevents the joystick from skipping too many values
			if (joystick_val !=joystick_prev)	//this means that the user used the joystick
			{
				switch(joystick_val){
					case KBD_DOWN:
						currentUserSelection +=1;	//we are have only 3 modes so only 3 values of currentUserSelection
						currentUserSelection = currentUserSelection %5;		//are accepted, overflow is mapped back to beginning
						break;
					case KBD_UP:
						currentUserSelection -=1;
						if (currentUserSelection <=0)
							currentUserSelection = 1;
						break;
					case KBD_SELECT:
						if (currentUserSelection == 1) {
							startPhotoGallery();	//start Photo Gallery
							currentUserSelection = 0;
						} else if (currentUserSelection == 2) {
							audio_main();
							delay(10);
							GLCD_Clear(White);
							GLCD_SetBackColor(DarkCyan);
							GLCD_SetTextColor(White);
							GLCD_DisplayString(0, 0, 1, "    Media Center    ");
							GLCD_DisplayString(1, 0, 1, "     Main  Menu     ");
							GLCD_SetTextColor(Black);					
							currentUserSelection =0;
						} else if (currentUserSelection == 3) {
							GLCD_Clear(White);
							startQuizGame();	
							GLCD_Clear(White);
							GLCD_SetBackColor(DarkCyan);
							GLCD_SetTextColor(White);
							GLCD_DisplayString(0, 0, 1, "    Media Center    ");
							GLCD_DisplayString(1, 0, 1, "     Main  Menu     ");
							GLCD_SetTextColor(Black);
							currentUserSelection = 0;
						} else if(currentUserSelection ==4) {
							GLCD_Clear(White);
							snakegame();
							GLCD_Clear(White);
							GLCD_SetBackColor(DarkCyan);
							GLCD_SetTextColor(White);
							GLCD_DisplayString(0, 0, 1, "    Media Center    ");
							GLCD_DisplayString(1, 0, 1, "     Main  Menu     ");
							GLCD_SetTextColor(Black);
							currentUserSelection = 0;
						}
						break;
					}
					joystick_prev = joystick_val;	//update prev joystick 
			}
			
			/*this is to update the LCD each time the user interfaces with the joystick*/
			if (currentUserSelection == 1)	//for displaying now
				{
						GLCD_SetBackColor(Red);
						GLCD_SetTextColor(White);
						GLCD_DisplayString(4,0,1, "Photo Gallery");
						GLCD_SetBackColor(White);
						GLCD_SetTextColor(Blue);
						GLCD_DisplayString(5,0,1, "Audio Player");
						GLCD_DisplayString(6,0,1, "Quiz Game");
						GLCD_DisplayString(7,0,1, "Snake Game");
						
				}
			else if(currentUserSelection == 2)
				{
						GLCD_SetBackColor(White);
						GLCD_SetTextColor(Blue);
						GLCD_DisplayString(4,0,1, "Photo Gallery");
						GLCD_SetBackColor(Red);
						GLCD_SetTextColor(White);
						GLCD_DisplayString(5,0,1, "Audio Player");
						GLCD_SetBackColor(White);
						GLCD_SetTextColor(Blue);
						GLCD_DisplayString(6,0,1, "Quiz Game");
						GLCD_DisplayString(7,0,1, "Snake Game");
				}
			else if(currentUserSelection == 3)
				{
						GLCD_SetBackColor(White);
						GLCD_SetTextColor(Blue);
						GLCD_DisplayString(4,0,1, "Photo Gallery");
						GLCD_DisplayString(5,0,1, "Audio Player");
						GLCD_SetBackColor(Red);
						GLCD_SetTextColor(White);
						GLCD_DisplayString(6,0,1, "Quiz Game");
						GLCD_SetBackColor(White);
						GLCD_SetTextColor(Blue);
						GLCD_DisplayString(7,0,1, "Snake Game");
				}
			else if (currentUserSelection == 4)
			{
						GLCD_SetBackColor(White);
						GLCD_SetTextColor(Blue);
						GLCD_DisplayString(4,0,1, "Photo Gallery");
						GLCD_DisplayString(5,0,1, "Audio Player");
						GLCD_DisplayString(6,0,1, "Quiz Game");
						GLCD_SetBackColor(Red);
						GLCD_SetTextColor(White);
						GLCD_DisplayString(7,0,1, "Snake Game");
						GLCD_SetBackColor(White);
						GLCD_SetTextColor(Blue);
			}
			else
				{
						GLCD_SetBackColor(White);
						GLCD_SetTextColor(Blue);
						GLCD_DisplayString(4,0,1, "Photo Gallery");
						GLCD_DisplayString(5,0,1, "Audio Player");
						GLCD_DisplayString(6,0,1, "Quiz Game");
						GLCD_DisplayString(7,0,1, "Snake Game");
				}
	}
}


