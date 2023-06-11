/***************************************************************
*
* Mark Foudy
* mark@foudy.io
* August 15, 2022
* pumaMenu.c
*
* This is my menu for my Penguin User Management Assistant (PUMA).
*
************************************************************ */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "list.c"

#define MAXIPLENGTH 15 

void printMenu();
int getUserChoice();
int executeMenu();
void showListADT();

node **headPtr;


/*  ***************************************************************** *
 * function mainMenu prints the menu choices for available for Users
 *  ***************************************************************** */
void mainMenu() {
	system("clear");
	printf("----------------------------------- \n");
	printf("Welcome to the PENGUIN USER MANAGEMENT ASSISTANT (PUMA): \n");
	printf("Please select one of the choices below: \n");
	printf("----------------------------------- \n");
	printf("     1 -- INPUT RAW DATA FILE \n");
	printf("     2 -- PRINT USER DATA\n");
	printf("     3 -- SEARCH BY USERNAME \n");
	printf("     4 -- SEARCH ON IP ADDRESS \n");
	printf("     5 -- SEARCH ON MAC ADDRESS \n");
	printf("     6 -- SORT BY USERNAME\n");
	printf("     7 -- DELETE USER CREDENTIALS LIST\n");
	printf("     8 -- Quit \n");
	printf("----------------------------------- \n");
}

/*  ******************************************************************
 *     function printMenu is the function called
 *     whenever a system administrator wants to retrieve a list of users.
 *  ******************************************************************/
void printMenu() {
	int tempChoice = 0;

	while(tempChoice != 6){
		system("clear");
		printf("----------------------------------- \n");
		printf("PRINT USER DATA MENU: \n");
        printf("Please select one of the choices below: \n");
        printf("----------------------------------- \n");
		printf("     1 -- Print Raw Data File TO CONSOLE\n");  
		printf("     2 -- Print authorized user list TO CONSOLE\n");  
		printf("     3 -- Print unauthorized user list TO CONSOLE\n");
		printf("     4 -- Print authorized user list TO FILE\n");  
		printf("     5 -- Print unauthorized user list TO FILE\n");
		printf("     6 -- Back to Main Menu \n");
		printf("----------------------------------- \n");

		printf("Enter choice (1-6): ");
		fflush(stdin);
		scanf("%d", &tempChoice);
		printf("\n");

		switch (tempChoice) {

		case (1):
			printf("Print Raw Data File TO CONSOLE\n");
			printListAllToConsole(*headPtr);
			break;
		case (2):
			printf("Print authorized user list TO CONSOLE\n");
			printAuthListToConsole(*headPtr);
			break;
		case (3):
			printf("Print unauthorized user list TO CONSOLE\n");
			printUnauthListToConsole(*headPtr);
			break;
		case (4):
			printf("Print authorized user list TO EXPORT FILE\n");
			printAuthListToFile(*headPtr);
			break;
		case (5):
			printf("Print unauthorized user list TO EXPORT FILE\n");
			printUnauthListToFile(*headPtr);
			break;
		case (6):
			printf("Back to Main Menu \n");
			mainMenu();
			break;
		default:
			printf("Back to Main Menu \n");
			mainMenu();
			break;
		}
		if(tempChoice != 6){
			printf("Press any key to continue\n");
			getchar();
			fflush(stdin);
			getchar();
			fflush(stdout);
		}
	}
}

/* ************************************************************************
 *  function GETUSERCHOICE gets input from user and returns integer
 * ***********************************************************************/

int getUserChoice() {
	int tempChoice = 0;

	mainMenu();
	printf("Enter choice (1-8): ");
	fflush(stdin);
	scanf("%d", &tempChoice);
	printf("\n");
	return tempChoice;

}

/***************************************************************
 *  function EXECUTE_MENU displays menu and implements user choice.
 *
 * **************************************************************/
int executeMenu() {
	int tempChoice = 0;
	char uname[30];
	char ip[16];
	char mac[18];
	node *returnNode = (node *)malloc(sizeof(node));
	clock_t t;
	long double time_taken;

	tempChoice = getUserChoice();

	switch (tempChoice) {

	case (1):
		printf("THIS SELECTION WILL INPUT ALL USER DATA.\n");
		populateList(headPtr);
		break;

	case (2):
		printf("THIS SELECTION WILL PRINT ALL USER DATA\n");
		printMenu();
		break;

	case(3):
		printf("THIS SELECTION WILL SEARCH BY USERNAME.\n");
		printf("Enter a username to search on: ");
		scanf("%s", uname);

        // initialize clock
		t = clock();
		returnNode = findItem(*headPtr, 0, uname);

        // prompt System Admin if User isn't located
		if (returnNode == NULL)
			printf("User not found.\n");
		else
			printNode(returnNode);

        // stop clock
		t = clock() - t;

        // calculate time_taken
		time_taken = ((double) t)/CLOCKS_PER_SEC;
		printf("Search by UserName took %.25Lf seconds to execute\n", time_taken);
		break;


	case (4):
		printf("THIS SELECTION WILL SEARCH BY IP ADDRESS.\n");
		printf("Enter a IP Address to search on: ");
		scanf("%s", ip);

        // initialize clock
        t = clock();

        returnNode = findItem(*headPtr, 1, ip);

        // prompt system admin if IP isn't located
        if (returnNode == NULL)
            printf("IP ADDRESS not found.\n");
        else
            printNode(returnNode);

        // stop clock
        t = clock() - t;

        // calculate time_taken
        time_taken = ((double) t)/CLOCKS_PER_SEC;
        printf("Search by IP Address took %.25Lf seconds to execute\n", time_taken);
		break;

	case (5):
		printf("THIS SELECTION WILL SEARCH BY MAC ADDRESS.\n");
		printf("Enter a MAC Address to search on: ");
		scanf("%s", mac);

        // initialize clock
        t = clock();

        returnNode = findItem(*headPtr, 2, mac);

        // prompt System Admin if MAC Address is not located
        if (returnNode == NULL)
            printf("MAC ADDRESS not found.\n");
        else
            printNode(returnNode);

        // stop the clock
        t = clock() - t;

        // calculate time taken
        time_taken = ((double) t)/CLOCKS_PER_SEC;
        printf("Search by MAC Address took %.25Lf seconds to execute\n", time_taken);
        break;

		break;

	case (6):
		printf("THIS SELECTION WILL SORT BY USERNAME. \n");
		sortList(headPtr);
		break;

    case (7):
       printf("THIS SELECTION WILL DELETE USER CREDENTIAL LIST. \n");
       deleteList(headPtr);
       break;

	case (8):
		printf("Quitting now.  Bye.  \n");
		break;

	default:
		printf("invalid choice ... choose again \n");
		break;

	} //SWITCH

	printf("Press any key to continue\n");
	getchar();
	fflush(stdin);
	getchar();
	fflush(stdout);
	return tempChoice;

}

/*  ***************************************************************** *
 *     FUNCTION showListADT
 *  ***************************************************************** */
void showListADT(){

	int userChoice = -1;

	do {
		userChoice = executeMenu();
	} while (userChoice != 8);

}
/******************************************/

int main(){
	srand(time(0));
	headPtr = (node **) malloc (sizeof(node **));

	// creation of the list
	*headPtr = createList();

	showListADT();

	return 0;
}
