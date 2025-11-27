/*
PROJECT: Bank management system
Date: 26-nov-2025
Developer: Yuvraj Kumar Singh
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>


#define MAX_USERS 50

struct account{
	char username[30];
	char password[30];
	int balance;
}users[MAX_USERS];

int usercount = 0;
int withdraw_limit = 0;

//project function prototype
void createaccount();
int login();
void deposit(int i);
void withdraw(int i);
void display_balance(int i);
void show_history(char username[]);
void add_transaction(char username[], char type[], int amount);
void loaddata();
void savedata();

int main(){
	loaddata();
	int user_index = -1, choice, logout = 0;
	
	//main menu of project!
	while(1){
		printf("\n==========================================\n");
    	printf("           BANK MANAGEMENT SYSTEM\n");
    	printf("==========================================\n");
    	printf("1. Create Account\n");
    	printf("2. Login Account\n");
    	printf("3. Exit\n");
    	printf("------------------------------------------\n");
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
        			while(logout != 1){
        				 printf("\n------------ Welcome, %s -------------\n", users[user_index].username);
        				 printf("1. Deposit Money\n");
        				 printf("2. Withdrawn Money\n");
        				 printf("3. Check Balance\n");
        				 printf("4. Transaction History\n");
        				 printf("5. Logout\n");
        				 printf("------------------------------------------\n");
        				 printf("Enter your choice: ");
        				 scanf("%d", &option);
        				 
        				 switch(option){
        				 	case 1:
        				 		deposit(user_index);
        				 		break;
        				 	case 2:
        				 		withdraw(user_index);
        				 		break;
        				 	case 3:
        				 		display_balance(user_index);
        				 		break;
        				 	case 4:
        				 		show_history(users[user_index].username);
        				 		break;
        				 	case 5:
        				 		printf("Press enter to Logout Account!\n");
								getch();
								printf("\nLogging Out.......\nThank You!\n");
								logout = 1;
								break;
							default:
								printf("Invalid choice! Please select a number between 1–5.\n");
						 }
					}
					logout = 0;
				}
				break;
			case 3:
				printf("Press enter to exit program!\n");
				getch();
				savedata();
				printf("\nExiting program.......\nThank You!");
				return 0;
			default:
				printf("Invalid choice! Please select a number between 1–3.\n");
		}
	}
	return 0;
}

//project function define
//1. Create user account
void createaccount(){
	int i;
	char uname[30], pword[30];
	if(usercount >= MAX_USERS){
		printf("Maximum account limit has been reached, Try again!\n");
		return;
	}else{
		printf("\n--- Create New Account ---\n");
		printf("Enter Username: ");
		scanf("%29s", uname);   
		
		//check if username is empty or not
		if(strlen(uname)==0){ 
			printf("Invalid username, Please try again!\n");
			return;
		}
		
		// Check duplicate username
    	for(i = 0; i < usercount; i++) {
        	if(strcmp(users[i].username, uname) == 0) {
            	printf("Username already exists! Choose another.\n");
            	return;
        	}
    	}
		
		printf("Enter Password: ");
		scanf("%29s", pword);   
		
		//check if password is empty or not
		if(strlen(pword)==0){              
			printf("Invalid password, Please try again!\n");
			return;
		}
		
		//storing values of users
		strcpy(users[usercount].username, uname);
		strcpy(users[usercount].password, pword);
		users[usercount].balance = 0;
		usercount++;
		printf("Account created successfully, Please login!\n");
		//return;
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
			printf("\nLogin successful! Welcome %s.\n", users[i].username);
			return i;
		}
	}
	printf("Invalid username & password, Please try again!\n");
	return -1;
}

//3. deposit money
void deposit(int i){
	int amt;
	printf("Enter amount to deposit: ");
	scanf("%d", &amt);
	
	if(amt <= 0){
		printf("Invalid amount! Please enter a positive value.\n");
		return;
	} else{
		users[i].balance+=amt;
		add_transaction(users[i].username, "DEPOSIT", amt);
		printf("\nDeposit Successful!\n");
		printf("Amount: RS %d\n", amt);
		printf("Updated Balance: RS %d\n\n", users[i].balance);
	}
}

//4. withdraw money
void withdraw(int i){
	int amt;
	printf("Enter amount to withdraw: ");
	scanf("%d", &amt);
	
	//check amt is not smaller than 0
	if(amt <= 0) {
        printf("Invalid amount! Amount must be greater than RS 0.\n");
        return;
    }
	
	//check withdraw limit
	if(amt < withdraw_limit){
		printf("Minimum withdrawal amount is RS %d, please try again!\n", withdraw_limit);
		return;
	}
	
	//check if amt is not greater than user balance
	if(amt > users[i].balance){
		printf("Insufficient  balance!\n");
		return;
	}
	
	users[i].balance -= amt;
	add_transaction(users[i].username, "WITHDRAW", amt);
	printf("\nWithdrawal Successful!\n");
	printf("Amount: RS %d\n", amt);
	printf("Remaining Balance: RS %d\n\n", users[i].balance);

	return;
}

//5. Check balance
void display_balance(int i){
	printf("\nYour current balance is: RS %d\n", users[i].balance);
	return;
}

//6. Show transaction history
void show_history(char username[]){
	char filename[100];
    sprintf(filename, "%s_history.txt", username);

    FILE *fp = fopen(filename, "r");

    if(fp == NULL) {
        printf("\nNo transaction history found!\n");
        return;
    }

    printf("\n===============================================\n");
    printf("         TRANSACTION HISTORY (%s)\n", username);
    printf("===============================================\n");
    printf("DATE         TIME        TYPE        AMOUNT\n");
    printf("-----------------------------------------------\n");

    char line[200];
    while(fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    printf("===============================================\n");

    fclose(fp);
}

//7. add transaction history
void add_transaction(char username[], char type[], int amount){
    char filename[100];
    sprintf(filename, "%s_history.txt", username);

    FILE *fp = fopen(filename, "a");
    if(fp == NULL) {
        printf("Error saving transaction!\n");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    fprintf(fp, "%02d-%02d-%04d  %02d:%02d:%02d  %-10s  %d\n",
            t->tm_mday,
            t->tm_mon + 1,
            t->tm_year + 1900,
            t->tm_hour,
            t->tm_min,
            t->tm_sec,
            type,
            amount
    );

    fclose(fp);
}

//8. load data
void loaddata(){
	int i;
    FILE *fp = fopen("bankdata.txt", "r");
    if(fp == NULL) {
        usercount = 0;
        return;
    }

    fscanf(fp, "%d", &usercount);

    for(i = 0; i < usercount; i++) {
        fscanf(fp, "%s %s %d",
               users[i].username,
               users[i].password,
               &users[i].balance);
    }

    fclose(fp);
}

//9. save data
void savedata(){
	int i;
    FILE *fp = fopen("bankdata.txt", "w");
    if(fp == NULL) {
        printf("Error saving data!\n");
        return;
    }

    fprintf(fp, "%d\n", usercount);

    for(i = 0; i < usercount; i++) {
        fprintf(fp, "%s %s %d\n",
                users[i].username,
                users[i].password,
                users[i].balance);
    }

    fclose(fp);
}
