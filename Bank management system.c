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
}users[MAX_USERS];

int usercount = 0;

//project function prototype
void createaccount();
int login();

int main()
{
	//loaddata();
	int user_index = -1, choice;
	
	//main menu of project!
	while(1){
		printf("\n=================================\n");
        printf("    BANKING MANAGEMENT SYSTEM\n");
        printf("=================================\n");
        printf("1. Create Account\n");
        printf("2. Login Account\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice){
        	case 1:
        		createaccount();
        		break;
        	case 2:
        		user_index = login();
        		if(user_index != -1){
        			int option;
        			
        			//login user menu of project
        			while(1){
        				 printf("\n----- Welcome, %s -----\n", users[user_index].username);
        				 printf("1. Deposite Money\n");
        				 printf("2. Withdrawn Money\n");
        				 printf("3. Check Balance\n");
        				 printf("4. Transaction History\n");
        				 printf("5. Logout\n");
        				 printf("Enter your choice: ");
        				 scanf("%d", &option);
					}
				}
				break;
			case 3:
				printf("Press enter to exit program!\n");
				getch();
				//savedata();
				printf("\nExiting program.......\nThank You!");
				return 0;
			default:
				printf("Invalid option, Please try again from (1-3) options.\n");
		}
	}
	return 0;
}

//project function define

//1. Create user account
void createaccount(){
	if(usercount >= MAX_USERS){
		printf("Maximum account limit has been reached, Try again!");
		return;
	}else{
		printf("\n--- Create New Account ---\n");
		printf("Enter Username: ");
		scanf("%29s", users[usercount].username);
		printf("Enter Password: ");
		scanf("%29s", users[usercount].password);
		users[usercount].balance = 0;
		usercount++;
		printf("Acoount created successfully, Please login!\n");
		return;
	}
}

//2. Login account
int login(){
	int i;
	char u[30], p[30];
	printf("\n--- Login Account ---\n");
	printf("Enter Username: ");
	scanf("%29s", u);
	printf("Enter Password: ");
	scanf("%29s", p);
	
	//check & match login details
	for(i=0; i<usercount; i++){
		if(strcmp(users[i].username, u) == 0 && strcmp(users[i].password, p) == 0){
			printf("Account login successfully!\n");
			return i;
		}
	}
	printf("Invalid username & password, Please try again!\n");
	return -1;
}

