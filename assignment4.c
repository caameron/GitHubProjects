#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define maxSize 15		//Max size of arguments



//Struct to print out the menu to the user
typedef struct menuStruct
{
	int count;
	char * choices[maxSize];
}menu;


//Struct for function dispatch table
typedef struct fTable
{
	char * operation;
	void (*ptr)();
} functionTable;


//Struct that will be passed in to each function and hold the command line arguments
typedef struct functionArg
{
	int count;
	char ** arguments;
} funcArg;


//Function Prototypes
void exitProg(funcArg data);
void addition(funcArg data);
void subtraction(funcArg data);
void multiplication(funcArg data);
void division(funcArg data);
void modulo(funcArg data);
void reverse(funcArg data);
void printMenu(menu Menu);





int main(int argc, char * argv[])
{

	//Variables for printing the menu to the user. The menu will contain 7 items to choose from
	char * menuChoices[] = {"Exit", "Addition", "Subtraction", "Multiplication", "Division", "Modulo", "Reverse Input"};
	int count = sizeof(menuChoices)/sizeof(menuChoices[0]);		//Number of menu choices in struct
	menu Menu;							//Instance of the menu struct
	funcArg param;							//Parameter to be passed in
	int choice = 0;							//Number user will enter for menu choice

	
	//Variable for the function dispatch table
	functionTable dispatchTable[] = {{"Exit", exitProg}, {"Addition", addition}, {"Subtraction", subtraction}, {"Multiplication", multiplication},
					 {"Division", division}, {"Modulo", modulo}, {"Reverse Input", reverse}};


	//If statement to check that the number of arguments passed into argc does not exceed 15
	//If it is above 16 or a 0 then print out an error message
	if(argc > 16 || argc == 1)
	{
		printf("Error: Number of arguments passed in must be between 1 and 15\n");
		exit(EXIT_FAILURE);
	}


	//Set the count variable in menu to the amount of choices and copy over all of the menuChoices into the struct char * array
	Menu.count = count;
	for(int i = 0; i < Menu.count; ++i)
		Menu.choices[i] = menuChoices[i];


	//Fill in function argument struct with the the amount of arguments passed in from command line and have the arguments data member
	//of the struct point to argv to obtain the data passed in
	param.count = argc;
	param.arguments = argv;


	//Continue to ask user what they want to do with their arguments until they exit the function
	do
	{
		//Call print menu function
		printMenu(Menu);
	
	
		//Ask user to enter in the number corresponding to the operation they wish to execute
		printf("Enter Choice:");
		scanf("%d", &choice);
	
		
		//Call corresponding function in dispatch table
		printf("FUNCTION:%s\n", dispatchTable[choice].operation);
		dispatchTable[choice].ptr(param);
		printf("\n\n");
	}while(choice != 0);

	exit(EXIT_SUCCESS);
}


//Function that will simply exit the program
void exitProg(funcArg data)
{
	exit(EXIT_SUCCESS);
}


//Function that will sum all the arguments together left to right and display the result
void addition(funcArg data)
{
	int sum = 0;					//Variable to print the sum of all the arguments
	int convert;					//Variable to convert arguments to numbers
	char * temp;					//Temp char pointer for strtol arguments


	//Go through each argument summing them together into sum variable	
	for(int i = 1; i < data.count; ++i)
	{
		convert = strtol(data.arguments[i], &temp, 0);
		sum += convert;
	}
	printf("%d\n", sum);
	return;
}


//Function that will subtract all the arguments from left to right and display the result
void subtraction(funcArg data)
{
	int ret = 0;					//Variable to print the value of all the arguments
	int convert;					//Variable to convert arguments to numbers
	char * temp;					//Temp char pointer for strtol arguments
	
	//Set ret variable to the first argument passed in and subtract the numbers left to right and print the result
	ret = strtol(data.arguments[1], &temp, 0);
	for(int i = 2; i < data.count; ++i)
	{
		convert = strtol(data.arguments[i], &temp, 0);
		ret -= convert;
	}
	printf("%d\n", ret);
	return;
}


//Function that will multiply all the arguments from left to right and display the result
void multiplication(funcArg data)
{
	float ret = 0;					//Variable to print the value of all the arguments
	float convert;					//Variable to convert arguments to numbers
	char * temp;					//Temp char pointer for strtol arguments
	
	//Set ret to the first argument passed in and multiply the numbers left to right, then display the result
	ret = strtol(data.arguments[1], &temp, 0);
	for(int i = 2; i < data.count; ++i)
	{
		convert = strtol(data.arguments[i], &temp, 0);
		ret *= convert;
	}
	printf("%f\n", ret);
	return;

}


//Function that will divide the first two arguments and display the result
void division(funcArg data)
{
	float ret = 0;					//Variable to print the value of all the arguments
	float convert;					//Variable to convert arguments to numbers
	char * temp;					//Temp char pointer for strtol arguments


	//If there are not atleast two arguments passed in print an error statement
	if(data.count < 3)
	{
		printf("Error:Division operator needs two numbers\n");
		exit(EXIT_FAILURE);
	}	


	//Set ret to the first argument passed in and divide it with the second, then print the result
	ret = strtol(data.arguments[1], &temp, 0);
	convert = strtol(data.arguments[2], &temp, 0);
	ret /= convert;
	
	printf("%f\n", ret);
	return;
}


//Function that will modulo the first two arguments and display the result
void modulo(funcArg data)
{
	int ret = 0;					//Variable to print the value of all the arguments
	int convert;					//Variable to convert arguments to numbers
	char * temp;					//Temp char pointer for strtol arguments


	//If there are not atleast two arguments passed in print an error statement
	if(data.count < 3)
	{
		printf("Error:Modulo operator needs two numbers\n");
		exit(EXIT_FAILURE);
	}	


	//Set ret to the first argument passed in and mod it with the second, then display the result
	ret = strtol(data.arguments[1], &temp, 0);
	convert = strtol(data.arguments[2], &temp, 0);
	ret = ret%convert;
	
	printf("%d\n", ret);
	return;

}


//Function that will reverse the arguments as they were passed in
void reverse(funcArg data)
{

	char * temp;					//Variable to temporarily hold on to the argument
	int charSize;					//number of characters in argument
	
	//For loop that will go through each argument. Allocate space in ret the reverse and read it in.
	for(int i = data.count-1; i >= 1; --i)
	{
		charSize = strlen(data.arguments[i]);
		temp = data.arguments[i];
		
		//For loop that will go through each char in the argument starting from the last
		//and print it out
		for(int x = charSize; x >= 0; --x)
			printf("%c", temp[x]);
		
		printf(" ");
	}

	printf("\n");
	return;

}


//Function to go through the passed in struct and display all of the choices that are present in its
//array of choices
void printMenu(menu Menu)
{
	printf("Please select a choice from below\n");

	for(int i = 0; i < Menu.count; ++i)
		printf("%d. %s\n", i, Menu.choices[i]);
}

