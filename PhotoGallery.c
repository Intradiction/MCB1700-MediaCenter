#include <stdbool.h>
#include <LPC17xx.H>
#include "GLCD.h"
#include "KBD.h"
#include "PhotoGallery.h"

void startPhotoGallery () {
	bool running = true;
	int joystick_val;
	int carouselIndex = 0; // Index of photo array
	int numImages = 3;
	
	GLCD_Clear(White);
	while (running) {
		
		GLCD_SetBackColor(DarkCyan);
		GLCD_SetTextColor(White);
		GLCD_DisplayString(0, 0, 1, "   Photo  Gallery   ");
		
		GLCD_SetBackColor(White);
		GLCD_SetTextColor(Black);
		GLCD_DisplayString(8, 0, 1, "DOWN = return to MM");
		GLCD_DisplayString(9, 0, 1, "LEFT, RIGHT = scroll");
		
		
		// Display images
		
		//GLCD_Bitmap(90, 64, 64, 64, UFO64_pixel_data);
		//GLCD_Bitmap(90, 64, 64, 64, GALAXY64_PIXEL_DATA);
		

		switch (carouselIndex) {
			case 0:
				GLCD_Bitmap(90, 64, 64, 64, UFO64_pixel_data);
				break;
			case 1:
				GLCD_Bitmap(90, 64, 64, 64, GALAXY64_pixel_data);
				break;
			case 2:
				//GLCD_Bitmap(90, 64, 64, 64, SATELITE64_pixel_data);
				break;
		}

		
		// Get user joystick input
		joystick_val = get_button();
		switch (joystick_val) {
			// Reset GLCD settings and go back to main menu
			case KBD_DOWN:
				GLCD_Clear(White);
				GLCD_SetBackColor(DarkCyan);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(0, 0, 1, "    Media Center    ");
				GLCD_DisplayString(1, 0, 1, "     Main  Menu     ");
				GLCD_SetTextColor(Black);			
				
				running = 0;
				break;
			case KBD_RIGHT:
				if (carouselIndex < numImages-1){
					carouselIndex++;
				} else {
					carouselIndex = 0;
				}
				break;
			case KBD_LEFT:
				if (carouselIndex > 0){
					carouselIndex--;
				} else {
					carouselIndex = numImages-1;
				}
				break;
		}
	}
}
