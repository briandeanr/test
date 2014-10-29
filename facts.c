/*

Name:  Brian Dean Richardson
UTEID: bdr555

Title:       "facts.c"
Description: Reads (file input) a set of facts and remembers them.
Then, it reads (file input) a set of questions, looks up the answer, and prints them (to stdio).
 */
//line 10


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **agrv){
	char *facts;
	char *qs;
	char name[80];
	int location = 0;
	facts = (char*) malloc(1000*sizeof(char));
	qs = (char*) malloc(1000*sizeof(char));
	
	//facts

	printf("\nEnter File name: \n");
	scanf("%s", name);
	printf("fileName: %s \n", name);
	FILE *file = fopen(name, "r");
	char nextChar;
	int i = 0;
	int pointer = 0;
	do{
		nextChar = getc(file);
		strcpy(&facts[i], &nextChar);
		printf("%c", facts[i]);
		i++;
	}while(nextChar != EOF);
	printf("\n");
	fclose(file);

	//questions
	char fileIn[1];
	printf("\nHave a Question File?\n (enter 'y' for yes, or 'n' for no)\n");
	scanf("%s",fileIn);

	if(fileIn[0] == 121 || fileIn[0] == 89){
	char qsFile[80];
	printf("Enter Questions File Name: \n");
	scanf("%s", qsFile);
	printf("questionFileName: %s \n", qsFile);
	FILE *qFile = fopen(qsFile, "r");
	char nextChars;
	int j = 0;
	do{
		nextChars = getc(qFile);
		strcpy(&qs[j], &nextChars);
		printf("%c", qs[j]);
		j++;
	}while(nextChars != EOF);
	printf("\n");
	fclose(qFile);
	}

	else{
	location = pointer;
	char qsChar[15]; 
	char qsCharTwo[15];
	char qsCharThree[15];
	printf("Enter a Question: ");
	scanf("%s", qsChar);
	scanf("%s", qsCharTwo);
	scanf("%s", qsCharThree);
	int counter = 0;
	while(qsChar[counter] > 31){
	++counter;
	}
	qsChar[counter] = 32;
	++counter;
	int position = 0;
	while(qsCharTwo[position] > 31){
	qsChar[counter] = qsCharTwo[position];
	++counter;
	++position;
	}
	qsChar[counter] = 32;
	++counter;
	while(qsCharThree[position] > 31){
	qsChar[counter] = qsCharThree[position];
	++counter;
	++position;
	}
	while(qsChar[pointer] != 10)
	  strcpy(&qs[pointer], &qsChar[pointer]);
	  ++pointer;
        }

	//processes answers
	char ansNextChar = 33; // pointer that searches Q file (1 of 2)
        char machine[10];      // stores machine name
	char question[10];     // stores question
	int machineSize = 0;
	int questionSize = 0;
	int p = 0;  	       // general pointer 
	int a = 0;
	int x = location-1;    // Q file pointer (2 of 2)
	int y = 0;	       // measurement pointer
	int z = 0;	       // facts[] pointer (1 of 2) , nextChar is pointer (2 of 2)
	int found = 0;	       // boolean, signifies if word match between machine[] and facts file
	int printed = 1;
	do{
		if(printed == 0){
		  printf("F ");
		  p = 0;
	          while(p < machineSize){
		    printf("%c", machine[p]);
		    ++p;
		  }
		  printf(": ");
		  p = 0;
		  while(p < questionSize){
		  printf("%c", question[p]);
		  ++p;
		  }
		  printf(" = unknown\n");
		}
		p = 0;
		printed = 0;
		found = 0;
		z = 0;
		++x;
		ansNextChar = qs[x];
		if(ansNextChar == 81){ // if ansNextChar is a "Q";
			ansNextChar = qs[++x];
			while(ansNextChar < 33 || ansNextChar > 126){ //Move to first char of machine
				x++;
				ansNextChar = qs[x];
			}
			y = 0;
			while(ansNextChar > 32 && ansNextChar < 127 && ansNextChar != 58){ // and set string "machine" equal to machine
				machine[y] = ansNextChar;
				x++;
				y++;
				ansNextChar = qs[x];
				}while(ansNextChar < 33 || ansNextChar > 126); //Move to first char of machine	}
			do{    //Move to first char of question
				x++;
				ansNextChar = qs[x];
			}while(ansNextChar < 33 || ansNextChar > 126 || ansNextChar == 61);
			machineSize = y;
			y = 0;
			while(ansNextChar > 32 && ansNextChar < 127){ //set string "question" equal to question
				question[y] = ansNextChar;
				x++;
				++y;
				ansNextChar = qs[x];
			}
			questionSize = y;
			nextChar = facts[z];
			while(nextChar != EOF){ //Next, search in facts[] to see if this machine is present
				if(nextChar == machine[0]){
					for(p = 0; p < machineSize; p++){
						if (nextChar != machine[p]){
							p = machineSize;
						}
						if((p == machineSize-1)){
							found = 1;
						}
						nextChar = facts[++a];
					}
					if(found == 1){
						z = a;
						do{
							++z;
							nextChar = facts[z];
						}while(nextChar < 33 || nextChar > 126 || nextChar == 58);
						a = z;
						if(nextChar == question[0]){
							for(p = 0; p < questionSize; p++){
								if (nextChar != question[p]){
									p = questionSize;
								}
								nextChar = facts[++a];
								if((p == questionSize - 1)){
									printed = 1;
									do{
										++a;
										nextChar = facts[a];
									}while(nextChar == 61 || nextChar < 33);
									    p = 0;
								  	    printf("F ");
									    while(p < machineSize){
										printf("%c", machine[p]);
										++p;
										}
									    printf(": ");
									    p = 0;	
									    while(p < questionSize){
										printf("%c", question[p]);
										++p;
										}
										printf(" = ");
									    while(nextChar > 32 && nextChar < 126){
										printf("%c", nextChar);
										++a;
										nextChar = facts[a];
									}
								printf("\n");
								}
							}

						}
						else{
						  found = 0;
						}
					} 
				}
			    else{
				z = z+1;
				a = z;
				nextChar = facts[z];
			}
		}
}

	}while(ansNextChar != EOF);
	free(facts);
	free(qs);
	return 0;
}
