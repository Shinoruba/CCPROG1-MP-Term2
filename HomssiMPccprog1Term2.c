/***************************************************************************

This is to certify that this project is my own work, based on my personal efforts
in studying and applying the concepts learned. I have constructed the
functions and their respective algorithms and corresponding code by myself.
The program was run, tested, and debugged by my own efforts. I further
certify that I have not copied in part or whole or otherwise plagiarized the
work of other students and/or persons.
Yazan M. Homssi, 
12206824

***************************************************************************/


/*
	Description: A game of chance. 
			There will be 4 doors for each room. 
			One leads to the next room; 
			one leads to an empty room; 
			one leads to a room of chance; and, 
			one leads to death. 
		The user is initially given 3 lives. 
		Every death reduces the number of lives. 
		The user wins if they reach the exit. The user loses if they run out of lives. 
		
	Programmed by: Homssi, Yazan M. S12
	Last modified: April 8, 2023
	Version: 3.2

	Acknowledgements: 
https://gcc.gnu.org/onlinedocs/gcc/
https://www.geeksforgeeks.org/
https://www.cprogramming.com/
https://www.codecademy.com/learn/learn-c
=	https://www.codecademy.com/courses/learn-c/lessons/loops-c/exercises/introduction-to-loops
https://www.tutorialspoint.com/index.htm
=	https://www.tutorialspoint.com/cprogramming/c_do_while_loop.htm
=	https://www.tutorialspoint.com/c_standard_library/c_function_pow.htm
https://codeforwin.org/c-programming/conditional-operator-programming-exercise
=	https://codeforwin.org/c-programming/c-program-to-find-maximum-using-ternary-operator
*/


// --------------------------------------------------------------

// Preprocessor directives used for the program
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Function prototypes that are going to be used later for the implementation of game creation & game play logic
void gameCreation(int *numRooms, int *correctDoors, int *deathDoors, int *chanceDoors, char name);
void gamePlay(int lives, int numRooms, int correctDoors, int deathDoors, int chanceDoors);


int main() 
{
    // Initial values
int lives = 3;
int numRooms = 5;
int correctDoors = 32341;
int deathDoors = 44123;
int chanceDoors = 13412;
int roomNumber = 1;

	char name[100];
    printf("Enter your name: ");
    scanf("%s", name);	
    
    // Main menu
int choice;

	do 
	{
	printf("WELCOME %s\n", name);
    printf("Main Menu\n");
    printf("1. Game Creation\n");
    printf("2. Game Play\n");
    printf("3. Exit\n");
    	printf("Enter your choice: ");
        scanf("%d", &choice);
    		switch(choice) 
			{
            case 1:
                gameCreation(&numRooms, &correctDoors, &deathDoors, &chanceDoors, name);
                break;
            case 2:
                gamePlay(lives, numRooms, correctDoors, deathDoors, chanceDoors);
                break;
            case 3:
                printf("Exiting game\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        	}
    	}while(choice != 3);
    	
    return 0;
}

// --------------------------------------------------------

/* 
gameCreation function takes input from user to create game settings.
Precondition: numRooms, correctDoors, deathDoors, and chanceDoors are pointers to integers
@param numRooms: pointer, stores number of rooms user chooses for the game.
@param correctDoors: pointer, stores the correct combination of doors entered by the user.
@param deathDoors: pointer, stores the combination of doors that leads to death entered by the user.
@param chanceDoors: pointer, stores the combination of doors that offers a chance entered by the user.
@return none(?) <- coming from a void function, It returns multiple values with the use of pointers 
*/
    void gameCreation(int *numRooms, int *correctDoors, int *deathDoors, int *chanceDoors, char name) 
{
	// Variables declared to be used later on
	int n, i, digit, isValid;
    
    
    // To get the number of rooms
    do 
	{
        printf("Enter the number of rooms (3-8): ");
        scanf("%d", &n);
        if(n >= 3 && n <= 8) 
		{
            *numRooms = n;
            isValid = 1;
        } 
		else 
		{
        	printf("Invalid input. Please enter a number between 3 and 8.\n");
        	isValid = 0;
        }
    }while(!isValid);
    
    
    // To get the correct doors
    do 
	{
        printf("Enter the correct doors (must be %d digits, with digits between 1 and 4): ", *numRooms);
        isValid = 1;
        *correctDoors = 0;
        for(i = 0; i < *numRooms; i++) 
		{
            scanf("%1d", &digit);
            if (digit < 1 || digit > 4) 
			{
            isValid = 0;
            }
            *correctDoors = *correctDoors * 10 + digit;
        }
        if(!isValid || *correctDoors < pow(10, *numRooms - 1)) 
		{
            printf("Invalid input. Please enter a %d-digit number with digits between 1 and 4.\n", *numRooms);
            isValid = 0;
        }
    }while(!isValid);
    
    // To get the death doors
    do 
	{
        printf("Enter the death doors (must be %d digits, with digits between 1 and 4.\n Must not overlap with the correct doors): ", *numRooms);
        isValid = 1;
        *deathDoors = 0;
        for(i = 0; i < *numRooms; i++) 
		{
            scanf("%1d", &digit);
            if(digit < 1 || digit > 4 || digit == (*correctDoors / (int)pow(10, *numRooms - i - 1)) % 10) 
			{
                isValid = 0;
            }
            *deathDoors = *deathDoors * 10 + digit;
        }
        if(!isValid || *deathDoors < pow(10, *numRooms - 1)) 
		{
            printf("Invalid input. Please enter a %d-digit number with digits between 1 and 4. \n Must not overlap with the correct doors.\n", *numRooms);
            isValid = 0;
        }
    }while(!isValid);
    
    // To get the chance doors
    do 
	{
        printf("Enter the chance doors (must be %d digits, with digits between 1 and 4. \n Must not overlap with the correct or death doors): ", *numRooms);
        isValid = 1;
        for(i = 0; i < *numRooms; i++) 
		{
            scanf("%1d", &digit);
            if(digit < 1 || digit > 4 || digit == (*correctDoors / (int)pow(10, *numRooms - i - 1)) % 10 || digit == (*deathDoors / (int)pow(10, *numRooms - i - 1)) % 10) 
			{
                isValid = 0;
            }
            *chanceDoors = *chanceDoors * 10 + digit;
        }
        if(!isValid || *chanceDoors < pow(10, *numRooms - 1)) 
		{
            printf("Invalid input. Please enter a %d-digit number with digits between 1 and 4. \n Must not overlap with the correct or death doors.\n", *numRooms);
            isValid = 0;
            *chanceDoors = 0;
        }
    } while(!isValid);
    
    printf("Game created successfully!\n");
}


// -----------------------------------------------------------


/* 
gamePlay function simulates the game using the user-defined settings.
Precondition: lives, numRooms, correctDoors, deathDoors, and chanceDoors are integers
@param lives: integer, number of lives the player has for the game.
@param numRooms: integer, number of rooms chosen for the game.
@param correctDoors: integer, correct combination of doors for the game.
@param deathDoors: integer, combination of doors that leads to death in the game.
@param chanceDoors: integer, combination of doors that offers a chance in the game.
@return outcome of choices 
*/
void gamePlay(int lives, int numRooms, int correctDoors, int deathDoors, int chanceDoors) 
{
    int roomNumber = 1;
    int chosenDoor, doorResult;
    char name[100];
    srand(time(NULL)); // Seed the random number generator
    
    while(roomNumber <= numRooms) 
	{
        // Display current room number and lives
        printf("\nRoom %d\n", roomNumber);
        printf("Lives: %d\n", lives);
        
        // Get chance doors
        int chance = chanceDoors % 10;
        chanceDoors /= 10;
        
        // Get death doors
        int death = deathDoors % 10;
        deathDoors /= 10;
        
        // Get correct doors
        int correct = correctDoors % 10;
        correctDoors /= 10;
        
        // Get empty doors
        int empty = 10 - chance - death - correct;
        
        // Show the doors to the player
        printf("Doors:\n");
        printf("1. Door\n");
        printf("2. Door\n");
        printf("3. Door\n");
        printf("4. Door\n");
        printf("Enter the door number you want to open: ");
        scanf("%d", &chosenDoor);
        
        
        
        switch(chosenDoor) // Determine the result of the chosen door
		{
            case 1:
                doorResult = (correct % 10 == 1) ? 1 : (death % 10 == 1) ? -1 : (chance % 10 == 1) ? 0 : 2;
                break;
            case 2:
                doorResult = (correct % 10 == 2) ? 1 : (death % 10 == 2) ? -1 : (chance % 10 == 2) ? 0 : 2;
                break;
            case 3:
                doorResult = (correct % 10 == 3) ? 1 : (death % 10 == 3) ? -1 : (chance % 10 == 3) ? 0 : 2;
                break;
            case 4:
                doorResult = (correct % 10 == 4) ? 1 : (death % 10 == 4) ? -1 : (chance % 10 == 4) ? 0 : 2;
                break;
            default:
                printf("Invalid door number.\n");
                continue;
        }
        
        
        switch(doorResult) // Update lives and room number based on door result
		{
            case -1:
                printf("Oh no! You opened a death door! You lost a life.\n");
                lives--;
                break;
            case 0:
                printf("You opened a chance door!\n");
                int bonus = rand() % 3 + 1;
                printf("You got a bonus of %d extra lives! Great work!\n", bonus);
                lives += bonus;
                break;
            case 1:
                printf("You opened the correct door!\n");
                roomNumber++;
                break;
            case 2:
                printf("You opened an empty door.\n");
                break;
        }
        
        // Check if the player ran out of lives
        if(lives <= 0) 
		{
            printf("Game over. You ran out of lives.\n");
            return;
        }
    }
    
    // Player has won the game <3
    printf("Congrats! You have successfully completed all rooms.\n");
}
