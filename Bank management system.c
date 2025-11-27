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

//project function prototype for users
void createaccount();
int login();
void deposit(int i);
void withdraw(int i);
void display_balance(int i);
void show_history(char username[]);
void add_transaction(char username[], char type[], int amount);
void loaddata();
void savedata();

//project function prototype for admin panel
int admin_login();
void admin_displayusers();
void admin_addmoney();
void admin_removeuser();

int main(){
	loaddata();
	int user_index = -1, choice, logout = 0, admin_index = -1, admin_logout = 0;
	int limit = 0;
	
	//main menu of project!
	while(1){
		printf("\n==========================================\n");
    	printf("           BANK MANAGEMENT SYSTEM\n");
    	printf("==========================================\n");
    	printf("1. Create Account\n");
    	printf("2. Login Account\n");
    	printf("3. Admin Login\n");
    	printf("4. Exit\n");
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
        			logout = 0;
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
								savedata();
								logout = 1;
								break;
							default:
								printf("Invalid choice! Please select a number between 1–5.\n");
						 }
					}
				}
				break;
			case 3:
				admin_index = admin_login();
				
				//check admin index
				if(admin_index!=-1){
					int admin_opt;
					admin_logout = 0;
					
					//admin main menu
					while(admin_logout!=1){
						printf("\n------------ Welcome Admin --------------\n");
        				printf("1. View all Users\n");
        				printf("2. Delete User\n");
        				printf("3. Money Transfer\n");
        				printf("4. Add Money\n");
        				printf("5. Set Minimum Withdrawal\n");
        				printf("6. Logout\n");
        				printf("-------------------------------------------\n");
        				printf("Enter your choice: ");
        				scanf("%d", &admin_opt);
        				
        				switch(admin_opt){
							case 1:
								admin_displayusers();
								break;
							case 2:
								admin_removeuser();
								break;
								break;
							case 4:
								admin_addmoney();
								break;
							case 5:
								printf("Enter withdraw amount limit: Rs ");
								scanf("%d", &limit);
								withdraw_limit = limit;
								break;
							case 6:
								printf("Press enter to Logout Admin!\n");
								getch();
								printf("\nAdmin Logging Out.......\nThank You!\n");
								savedata();
								admin_logout = 1;
								break;
							default:
								printf("Invalid choice! Please select a number between 1–6.\n");
						}
					}
				}
				break;
			case 4:
				printf("Press enter to exit program!\n");
				getch();
				savedata();
				printf("\nExiting program.......\nThank You!");
				return 0;
			default:
				printf("Invalid choice! Please select a number between 1–4.\n");
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
		savedata();
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
	savedata();
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

//10. admin login
admin_login(){
	char a_user[30], a_pass[30];
	printf("\n--- Login Admin Account ---\n");
	printf("Enter Admin Username: ");
	scanf("%29s", a_user);
	printf("Enter Admin Password: ");
	scanf("%29s", a_pass);
	
	if(strcmp("admin", a_user) == 0 && strcmp("admin12", a_pass) == 0){
		printf("\nLogin successful! Welcome %s.\n", a_user);
		return 1;
	}
	printf("Invalid username & password, Please try again!\n");
	return -1;
}

//11. display all users
void admin_displayusers(){
	int i;
    printf("\n================= USER LIST (ADMIN PANEL) =================\n");

    if(usercount == 0) {
        printf("No users found!\n");
        return;
    }

    printf("\n%-5s %-20s %-20s %-10s\n", "ID", "USERNAME", "PASSWORD", "BALANCE");
    printf("---------------------------------------------------------------\n");

    for(i = 0; i < usercount; i++) {
        printf("%-5d %-20s %-20s %-10d\n",
               i + 1,
               users[i].username,
               users[i].password,
               users[i].balance);
    }

    printf("---------------------------------------------------------------\n");
}

//12. admin add money
void admin_addmoney(){
	char user_n[30];
	int i, found = -1, add_amt;
	printf("Enter Username: ");
	scanf("%29s", user_n);
	
	//check usename exit in database or not
	for(i = 0; i < usercount; i++){
		if(strcmp(users[i].username, user_n) == 0){
			found = i;
			printf("User Founded Successful!\n");
			break;
		}
	}
	
	printf("Enter amount to add: Rs ");
	scanf("%d", &add_amt);
	
	if(add_amt <= 0){
		printf("Invalid amount! Please enter a positive value.\n");
		return;
	}	
	
	if(found!=-1){
		users[found].balance += add_amt;
		add_transaction(users[found].username, "ADMIN DEPOSIT", add_amt);
		printf("\nMoney Added Successful!\n");
		printf("Amount: RS %d\n", add_amt);
		printf("Updated User Balance: RS %d\n\n", users[found].balance);
		savedata();
		return;
	} else{
		printf("Invalid username, Please enter correct username!\n");
	}
}

//13. admin remove user
void admin_removeuser(){
	int i, found = -1;
	char s_user[30];
	printf("Enter Username: ");
	scanf("%29s", s_user);
	
	//check usename exit in database or not
	for(i = 0; i < usercount; i++){
		if(strcmp(users[i].username, s_user) == 0){
			found = i;
			printf("User Founded Successful!\n");
			break;
		}
	}
	
	//logic for remove user
	
	
}
