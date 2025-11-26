/*
PROJECT: Bank management system
Date: 26-nov-2025
Developer: Yuvraj Kumar Singh
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct account{
	char username[30];
	char password[30];
	int balance;
}users[100];

int usercount = 0;

int main()
{
	//loaddata();
	int user_index = -1, choice;
	
	//main menu of project!
	while(1){
		printf("\n============================\n");
        printf("      BANKING SYSTEM\n");
        printf("============================\n");
        printf("1. Create Account\n");
        printf("2. Login Account\n");
        printf("3. Exit\n");
        
        printf("Enter your choice: ");
        scanf("%d", &choice);
	}
	return 0;
}

