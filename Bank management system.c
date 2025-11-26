/*
PROJECT: Bank management system
Date: 26-nov-2025
Developer: Yuvraj Kumar Singh
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define MAX_USERS 50

struct account{
	char username[30];
	char password[30];
	int balance;
}users[100];

int usercount = 0;

//project function prototype
void createaccount();
//int login();

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
        
        switch(choice){
        	case 1:
        		createaccount();
        		break;
        	
		}
	}
	return 0;
}

//project function define

//1. Create user account
void createaccount(){
	if(usercount > MAX_USERS){
		printf("Maximum account limit has been reached, Try again!");
		return;
	}else{
		printf("\n--- Create New Account ---\n");
		printf("Enter Username: ");
		scanf("%s", users[usercount].username);
		printf("Enter Password: ");
		scanf("%s", users[usercount].username);
		users[usercount].balance = 0;
		usercount++;
		printf("Acoount created successfully, Please login!\n");
		return;
	}
}

