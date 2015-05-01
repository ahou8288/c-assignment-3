#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "snapshot.h"

#define NUM_FUNCTIONS 2

//Function Definitions
void getCommand(void);
void run(char* commandName, char* userCommand);
void BYE(char* args);
void SET(char* args);
char* strLower(char* inString);

entry* entry_head = NULL;
entry* entry_tail = NULL;

snapshot* snapshot_head = NULL;
snapshot* snapshot_tail = NULL;

int main(void) {
	getCommand();
	return 0;
}

void getCommand(void){
	//Get user input
	char userCommand[MAX_LINE_LENGTH];
	fgets(userCommand,MAX_LINE_LENGTH,stdin);
	
	//Duplicate string because original string is modified.
	char args[MAX_LINE_LENGTH];
	strcpy(args,userCommand);
	
	char * pch;
	pch = strtok (userCommand," "); //Split string
	if (pch != NULL)
	{
		//At this point send user command to get processed at run(pch,usercommand)
		run(pch,args);
	}
	
}

void run(char* commandName, char* arguments){
	//Create a list of function names and function pointers
	//Run the function with the arguments
	
	struct functionList{
		char* name;
		void (*ptr)();
		int args;
	};
	
	struct functionList myFnc[NUM_FUNCTIONS];
	
	myFnc[0].name="bye";
	myFnc[0].ptr=&BYE;
	myFnc[0].args=0;
	myFnc[1].name="set";
        myFnc[1].ptr=&SET;
        myFnc[1].args=1;

	printf("Command name is %s\n",strLower(commandName));
	for (int i=0; i<NUM_FUNCTIONS; i++){
		if (strcmp(strLower(commandName),myFnc[i].name)==0){
			if (myFnc[i].args>0){
				(myFnc[i].ptr)(arguments);
			} else {
				(myFnc[i].ptr)();
			}
		}else{printf("here");}
	}
}

char* strLower(char* inString){
	for (int i=0; inString[i];i++){
		inString[i] = tolower(inString[i]);
	}
	return inString;
}

void BYE(){
	printf("Bye function has been run\n");
}

void SET(char* args){
	char key[MAX_KEY_LENGTH];
	int value;
	char command[MAX_LINE_LENGTH]; //not used
	sscanf(args,"%s %s %d",command,key,&value);
	printf("set command has received key of %s, and value of %d.\n",key,value);


}
