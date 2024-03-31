#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_USERS 10
#define MAX_NAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 20


// Global arrays to store usernames, passwords, and user types
char usernames[MAX_USERS][MAX_NAME_LENGTH];
char passwords[MAX_USERS][MAX_PASSWORD_LENGTH];
int userTypes[MAX_USERS]; // 0 for employee, 1 for admin
int numUsers = 0;


void main_menu();


int check_user(const char *username); // Function to check if the username exists
int check_pass(const char *password); // Function to check password
void clean(); //clears console
void wait_clean(); //clears console after user press any key


void login_system();


void user();
void user_payslip();
void user_info_update();


void admin();
void admin_manage();
void add_employee();



void main(){
	
	// Predefined admin account
    strcpy(usernames[0], "admin");
    strcpy(passwords[0], "admin123");
    userTypes[0] = 1; // Admin
    numUsers++;
    
    
	main_menu();
	
}

// Function for the main menu
void main_menu(){
	
	int choice;
	
	do{
		//design
		printf("\n**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*                Welcome to Payroll System               *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*    [1] Login                                           *\n");
    	printf("*    [0] Exit                                            *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("\tEnter: ");
    	scanf("%d", &choice);
    
    	switch (choice){
    	
    		case 1:
    			login_system();
    			break;
    		case 0:
    			break;
    		default:
    			clean();
    			printf("\n\t\t\tnot in option\n");
    			wait_clean();
    			break;
		}
	}while(choice != 0);
	
}

// Function to check if the username exists
int check_user(const char *username){
	
	int i;
	
	for (i = 0; i < numUsers; i++) {
        if (strcmp(usernames[i], username) == 0) {
            return i; // Return index of the user if found
        }
    }
    return -1; // Return -1 if username not found
}

// Function to check password
int check_pass(const char *password){
	
	int i;
	
	for (i = 0; i < numUsers; i++) {
        if (strcmp(passwords[i], password) == 0) {
            return i; // Return index of the user if found
        }
    }
    return -1; // Return -1 if username not found
}


void login_system(){
	
	int attempt = 3;
	int admin_attempt = 3;
	int user_attempt = 3;
	
	char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    
    clean();
    
    do{
    	

    	printf("\n\t\tLogin\n\n");
    	printf("\t\tUsername: ");
    	scanf("%s", username);
    

    	int index = check_user(username); // checks inputted username
    	if (index != -1 && userTypes[index] == 1) { // checks if username is admin
    		
    		attempt = 0;
    		
    		do{
    			
    			printf("\t\tPassword: ");
    			scanf("%s", password);
    	
    			int index_pass = check_pass(password);
    			if (index_pass != -1){
    				
    				admin_attempt = 0;
    				clean();
    		
    				printf("\n\n\tAdmin login successful. Welcome, %s!\n\n", username);
    				wait_clean();
        			admin();
				} else {
					
					clean();
					admin_attempt--;
					printf("\n\n\tInvalid password. Please try again. [%d]\n\n", admin_attempt);
				}
    			
			}while(admin_attempt != 0);
    		
		
        
    	} else if (index != -1 && userTypes[index] == 0) { // checks if username is employee
    		
    		attempt = 0;
    		
    		do{
    			
    			printf("\t\tPassword: ");
    			scanf("%s", password);
    	
    			int index_pass = check_pass(password);
    			if (index_pass != -1){
    				
    				user_attempt = 0;
    				clean();
    		
    				printf("\n\n\tEmployee login successful. Welcome, %s!\n\n", username);
    				wait_clean();
        			user();
				} else {
			
					printf("\n\n\tInvalid password. Please try again. [%d]\n\n", user_attempt);
				}
    			
			}while(user_attempt != 0);
    	
        	
        
    	} else {
    	
    		clean();
    		attempt--;
    		printf("\n\n\tUser does not exist. Please try again. [%d]\n\n", attempt);
    		
		}
    	
	}while(attempt != 0);
    
    
}


// Function for the user menu
void user(){
	
	
	int choice;
	
	do{
		//design
		printf("\n**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*                      Employee Menu                     *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*    [1] View Payslip                                    *\n");
    	printf("*    [2] Change Password                                 *\n");
    	printf("*    [3] Update personal info                            *\n");
    	printf("*    [0] Logout                                          *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("\tEnter: ");
    	scanf("%d", &choice);
    
    	switch (choice){
    	
    		case 1:
    			printf("\nN/a\n");
    			break;
    		case 2:
    			printf("\nN/a\n");
    			break;
    		case 3:
    			printf("\nN/a\n");
    			break;
    		case 0:
    			clean();
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 0);
	
}

void user_payslip(){
	
	int choice;
	
	clean();
	
	do{
		//design
		printf("\n**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*                      Salary Payslip                    *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*    [1] Withdraw Salary                                 *\n");
    	printf("*    [0] Back                                            *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("\tEnter: ");
    	scanf("%d", &choice);
    
    	switch (choice){
    	
    		case 1:
    			printf("\nN/a\n");
    			break;
    		case 0:
    			wait_clean();
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 0);
	
}

void user_info_update(){
	
	int choice;
	
	clean();
	
	do{
		//design
		printf("\n**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*               Update Personal Information              *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*    [1] Full Name                                       *\n");
    	printf("*    [2] Address                                         *\n");
    	printf("*    [3] Contact                                         *\n");
    	printf("*    [0] Back                                            *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("\tEnter: ");
    	scanf("%d", &choice);
    
    	switch (choice){
    	
    		case 1:
    			printf("\nN/a\n");
    			break;
    		case 2:
    			printf("\nN/a\n");
    			break;
    		case 3:
    			printf("\nN/a\n");
    			break;
    		case 0:
    			clean();
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 0);
	
}


// Function for the admin menu
void admin(){
	
	int choice;
	
	do{
		//design
		printf("\n**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*                      Admin Menu                        *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*    [1] Manage Employees                                *\n");
    	printf("*    [2] Change Password                                 *\n");
    	printf("*    [0] Logout                                          *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("\tEnter: ");
    	scanf("%d", &choice);
    
    	switch (choice){
    	
    		case 1:
    			admin_manage();
    			break;
    		case 2:
    			printf("\nN/a\n");
    			break;
    		case 0:
    			clean();
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 0);
	
}

void admin_manage(){
	
	int choice;
	
	clean();
	
	do{
		//design
		printf("\n**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*                   Manage Employees                     *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*    [1] Edit salary                                     *\n");
    	printf("*    [2] Delete employee                                 *\n");
    	printf("*    [3] Add employee                                    *\n");
    	printf("*    [0] Back                                            *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("\tEnter: ");
    	scanf("%d", &choice);
    
    	switch (choice){
    	
    		case 1:
    			printf("\nN/a\n");
    			break;
    		case 2:
    			printf("\nN/a\n");
    			break;
    		case 3:
    			add_employee();
    			break;
    		case 0:
    			clean();
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 0);
	
}

void add_employee(){
	
	clean();
	
	if (numUsers >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return;
    }

    printf("\n\t\tRegister New Employee\n\n");
    printf("\tUsername: ");
    scanf("%s", usernames[numUsers]);
    printf("\tPassword: ");
    scanf("%s", passwords[numUsers]);
    printf("\tUser type (0: Employee, 1: Admin): ");
    scanf("%d", &userTypes[numUsers]);

    printf("\tRegistration successful.\n");

    numUsers++;
    
    wait_clean();
    
}

//clears console
void clean(){

	system("cls"); // Clear console on Windows
}

//clears console after user press any key
void wait_clean(){
	
	printf("\n\n\tpress any key to continue...");
	_getch(); // Wait for keypress
	system("cls"); // Clear console on Windows
}


