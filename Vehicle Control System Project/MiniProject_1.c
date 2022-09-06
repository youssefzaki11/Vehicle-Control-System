/*************************************************************************************************************
 Name: Vehicle Control System
 Author: Youssef Ahmed Zaki
 Project: Mini Project 1 - MT Full Embedded Systems Diploma
 *************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stddef.h>

#define ON 1
#define OFF 0
#define WITH_ENGINE_TEMP_CONTROLLER 1

unsigned char engine_state;
unsigned char AC;
unsigned char engine_temperature_controller;
unsigned short int vehicle_speed;
/*==========================================================================================================*/
int set_speed(unsigned char *TrafficLight_ptr) // input: traffic light condition - output: set of speed
{
	// checking condition, to make sure that any of the letters of the traffic colors entered by user.
	while (*TrafficLight_ptr != 'G' && *TrafficLight_ptr != 'g' && *TrafficLight_ptr != 'O' && *TrafficLight_ptr != 'o' && *TrafficLight_ptr != 'R' && *TrafficLight_ptr != 'r')
	{
		//this condition considers that the user may enter the letters (capital or small).
		printf("Please Try again!\n");
		printf("Enter the state of the traffic_light\n");
		puts("'G' for green - 'O' for orange - 'R' for red");
		scanf(" %c", &*TrafficLight_ptr);
	}
	// the following conditions are to meet the requirements
		if (*TrafficLight_ptr == 'G' || *TrafficLight_ptr == 'g')
		{
			vehicle_speed = 100;
			return vehicle_speed;
		}
		else if (*TrafficLight_ptr == 'O' || *TrafficLight_ptr == 'o')
		{
			vehicle_speed = 30;
			return vehicle_speed;
		}
		else if (*TrafficLight_ptr == 'R' || *TrafficLight_ptr == 'r')
		{
			vehicle_speed = 0;
			return vehicle_speed;
		}
} // this warning doesn't affect the process.
/*==========================================================================================================*/
void set_RoomTemperature(short int *temperature_ptr) // input: room temperature state - output AC state & setting of temperature
{
	if (*temperature_ptr < 10 || *temperature_ptr > 30)
	{
		AC = ON;
		*temperature_ptr = 20;
	}
	else
	{
		AC = OFF;
	}
}
/*==========================================================================================================*/
#if WITH_ENGINE_TEMP_CONTROLLER == 1
void set_EngineTemperature(unsigned short int *EngineTemp_ptr)
{
	if (*EngineTemp_ptr < 100 || *EngineTemp_ptr > 150)
	{
		engine_temperature_controller = ON;
		*EngineTemp_ptr = 125;
	}
	else
	{
		engine_temperature_controller = OFF;
	}
}
#endif
/*==========================================================================================================*/
void modification( short int *roomtemp_ptr, unsigned short int *enginetemp_ptr) //special case function
{
	if (vehicle_speed == 30)
	{
		if (AC == OFF)
		{
			AC = ON;
		}
		// to make sure that the entered room temperature = current room temperature * (5/4) + 1
		*roomtemp_ptr *= 5/4;
		*roomtemp_ptr += 1;
#if WITH_ENGINE_TEMP_CONTROLLER == 1

		if (engine_temperature_controller == OFF)
		{
			engine_temperature_controller = ON;
		}
		// to make sure that the entered engine temperature = current engine temperature * (5/4) + 1
		*enginetemp_ptr *= 5/4;
		*enginetemp_ptr += 1;
#endif

	}
}
/*==========================================================================================================*/
int main (void)
{
	unsigned char input;
	unsigned char traffic_light;
	short int room_temperature;
	unsigned short int engine_temperature = 0; // initialized to prevent garbage values

	// These Two sentences for avoiding any problems during using of "printf" and "scanf" functions.
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
/*==========================================================================================================*/
// let the user choose one of the following options
	printf("Welcome! Please choose any of the following options: \n\n");
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n\n");
	scanf(" %c",&input);

	while (input != 'c') // this loop to make sure that the program cannot be terminated only if the user entered "c"
	{
		while( input < 'a' || input > 'c') // safety loop to ensure that the user entered only a, b or c
		{
			printf("Invalid Input, please enter a, b or c \n");
			printf("a. Turn on the vehicle engine\n");
			printf("b. Turn off the vehicle engine\n");
			printf("c. Quit the system\n\n");

			scanf(" %c",&input);
		} // user entered input a, b or c
		if (input == 'b') // checking for "b" to meet the requirement (let the user choose again)
		{
			printf("Please choose any of the following options: \n\n");
			printf("a. Turn on the vehicle engine\n");
			printf("b. Turn off the vehicle engine\n");
			printf("c. Quit the system\n\n");

			scanf(" %c",&input);

			// checking again for safety
			while( input < 'a' || input > 'c')
			{
				printf("Invalid Input, please enter a, b or c \n");
				printf("a. Turn on the vehicle engine\n");
				printf("b. Turn off the vehicle engine\n");
				printf("c. Quit the system\n\n");

				scanf(" %c",&input);
			} // if the user ensured that turning the vehicle engine off, the state is displayed
			if (input == 'b')
			{
				engine_state = OFF; // state of engine is OFF
				printf("The vehicle engine is turned off! \n\n");
			}
		}
		// values arrived here cannot be any character except (a)
		switch (input)
		{
		case 'a':
			engine_state = ON;
			while(engine_state == ON)
			{
				fflush(stdin); // to prevent the duplicating of printf and puts
				printf("Sensors Set Menu: \n\n");

				puts("a. Turn off the engine");
				puts("b. Set the traffic light color.");
				puts("c. Set the room temperature");
#if WITH_ENGINE_TEMP_CONTROLLER == 1
				puts("d. Set the engine temperature");
#endif
				scanf(" %c",&input);

				if (input == 'a')
				{
					engine_state = OFF;
					break; // the program will display the main menu again
				}
				else if (input == 'b')
				{
					printf("Please enter the state of the traffic_light ");
					puts("('G' for green - 'O' for orange - 'R' for red)");
					scanf(" %c", &traffic_light);
					set_speed(&traffic_light); //calling the speed by "pass by address"
					printf("The speed is set to be %d Km/hr\n\n", set_speed(&traffic_light));
				}
				else if (input == 'c')
				{
					printf("Please enter the room temperature: ");
					scanf(" %hi", &room_temperature); // entering the value as short int
					set_RoomTemperature(&room_temperature); // calling the function "pass by address"
					printf("The room temperature is set to be: %hi\n\n", room_temperature);
				}
#if WITH_ENGINE_TEMP_CONTROLLER == 1 // bonus requirement
				else if (input == 'd')
				{
					printf("Please enter the engine temperature: ");
					scanf(" %hu", &engine_temperature); // entering the value "unsigned short int"
					set_EngineTemperature(&engine_temperature); // calling the function "pass by address"
					printf("The Engine Temperature is set to be: %hu\n\n", engine_temperature);
				}
#endif
				modification(&room_temperature, &engine_temperature); /* calling the function with the
				condition if the speed = 30 km/hr to meet the requirement */

				// displaying all the states
				if (engine_state == ON)
				{
					printf("Engine is ON\n");
				}
				else if (engine_state == OFF)
				{
					printf("Engine is OFF\n");
				}
				if(AC == ON)
				{
					printf("AC is ON\n");
				}
				else if (AC == OFF)
				{
					printf("AC is OFF\n");
				}

				printf("Vehicle Speed: %hu\n", vehicle_speed);
				printf("Room Temperature: %hi C\n", room_temperature);
#if WITH_ENGINE_TEMP_CONTROLLER == 1
				if (engine_temperature_controller == ON)
				{
					printf("Engine Temperature Controller is: ON\n");
				}
				else if (engine_temperature_controller == OFF)
				{
					printf("Engine Temperature Controller is: OFF\n");
				}
				printf("Engine Temperature: %hu C\n\n", engine_temperature);
#endif
			}
			break;
		default:
		}
		// returning to the main menu but still inside the loop -> while (input != 'c')
		printf("Please choose any of the following options: \n\n");
		printf("a. Turn on the vehicle engine\n");
		printf("b. Turn off the vehicle engine\n");
		printf("c. Quit the system\n\n");
		scanf(" %c",&input);
	}
	printf("Quit the system!\n\n");
}
