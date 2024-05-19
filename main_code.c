#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_USERS 10
#define MAX_NAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 20
#define MAX_LENGTH 50


// Global arrays to store usernames, passwords, and user types
char usernames[MAX_USERS][MAX_NAME_LENGTH];
char passwords[MAX_USERS][MAX_PASSWORD_LENGTH];
char name[MAX_USERS][MAX_NAME_LENGTH];
char address[MAX_USERS][MAX_NAME_LENGTH];
char position[MAX_USERS][MAX_LENGTH];
int contact[MAX_USERS];

int userTypes[MAX_USERS]; // 0 for employee, 1 for admin
int numUsers = 0;

//salary


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
	
	char choice;
	
	do{
		//design
		printf("\n**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*                Welcome to Payroll System               *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*    [A] Login                                           *\n");
    	printf("*    [X] Exit                                            *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("\tEnter: ");
    	scanf(" %c", &choice);
    	choice = toupper(choice);
    	getchar(); // Consume the newline character left in the input buffer
    
    	switch (choice){
    	
    		case 'A':
    			login_system();
    			break;
    		case 'X':
    			break;
    		default:
    			clean();
    			printf("\n\t\t\tnot in option\n");
    			wait_clean();
    			break;
		}
	}while(choice != 'X');
	
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
    	getchar(); // Consume the newline character left in the input buffer
    

    	int index = check_user(username); // checks inputted username
    	if (index != -1 && userTypes[index] == 1) { // checks if username is admin
    		
    		attempt = 0;
    		
    		do{
    			
    			printf("\t\tPassword: ");
    			scanf("%s", password);
    			getchar(); // Consume the newline character left in the input buffer
    	
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
    			getchar(); // Consume the newline character left in the input buffer
    	
    			int index_pass = check_pass(password);
    			if (index_pass != -1){
    				
    				user_attempt = 0;
    				clean();
    		
    				printf("\n\n\tEmployee login successful. Welcome, %s!\n\n", username);
    				wait_clean();
        			user(index);
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
void user(int index){
	
	
	char choice;
	
	do{
		//design
		printf("\n**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*                      Employee Menu                     *\n");
    	printf("*                                                        *\n");
    	printf("\nUsername: %s\n", usernames[index]);
        printf("Name: %s\n", name[index]);
        printf("Address: %s\n", address[index]);
        printf("Position: %s\n", position[index]);
        printf("Contact: %d\n", contact[index]);
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*    [A] View Payslip                                    *\n");
    	printf("*    [B] Change Password                                 *\n");
    	printf("*    [C] Update personal info                            *\n");
    	printf("*    [X] Logout                                          *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("\tEnter: ");
    	scanf(" %c", &choice);
    	choice = toupper(choice);
    	
    
    	switch (choice){
    	
    		case 'A':
    			printf("\nN/a\n");
    			break;
    		case 'B':
    			printf("\nN/a\n");
    			break;
    		case 'C':
    			printf("\nN/a\n");
    			break;
    		case 'X':
    			clean();
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 'X');
	
}

void user_payslip(){
	
	char choice;
	
	clean();
	
	do{
		//design
		printf("\n**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*                      Salary Payslip                    *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*    [A] Withdraw Salary                                 *\n");
    	printf("*    [X] Back                                            *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("\tEnter: ");
    	scanf(" %c", &choice);
    	choice = toupper(choice);
    	
    
    	switch (choice){
    	
    		case 'A':
    			printf("\nN/a\n");
    			break;
    		case 'X':
    			wait_clean();
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 'X');
	
}

void user_info_update(int index){
	
	char choice;
	
	clean();
	
	do{
		//design
		printf("\n**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*               Update Personal Information              *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("\nUsername: %s\n", usernames[index]);
        printf("Name: %s\n", name[index]);
        printf("Address: %s\n", address[index]);
        printf("Position: %s\n", position[index]);
        printf("Contact: %d\n", contact[index]);
        printf("*                                                        *\n");
    	printf("*    [A] Full Name                                       *\n");
    	printf("*    [B] Address                                         *\n");
    	printf("*    [C] Contact                                         *\n");
    	printf("*    [X] Back                                            *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("\tEnter: ");
    	scanf(" %c", &choice);
    	choice = toupper(choice);
    	
    
    	switch (choice){
    	
    		case 'A':
    			printf("\nN/a\n");
    			break;
    		case 'B':
    			printf("\nN/a\n");
    			break;
    		case 'C':
    			printf("\nN/a\n");
    			break;
    		case 'X':
    			clean();
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 'X');
	
}


// Function for the admin menu
void admin(){
	
	char choice;
	
	do{
		//design
		printf("\n**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*                      Admin Menu                        *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*    [A] Manage Employees                                *\n");
    	printf("*    [B] Change Password                                 *\n");
    	printf("*    [X] Logout                                          *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("\tEnter: ");
    	scanf(" %c", &choice);
    	getchar(); // Consume the newline character left in the input buffer
    	choice = toupper(choice);
    	
    
    	switch (choice){
    	
    		case 'A':
    			admin_manage();
    			break;
    		case 'B':
    			printf("\nN/a\n");
    			break;
    		case 'X':
    			clean();
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 'X');
	
}

void admin_manage(){
	
	char choice;
	
	clean();
	
	do{
		//design
		printf("\n**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*                   Manage Employees                     *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*    [A] Edit salary                                     *\n");
    	printf("*    [B] Delete employee                                 *\n");
    	printf("*    [C] Add employee                                    *\n");
    	printf("*    [X] Back                                            *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("\tEnter: ");
    	scanf(" %c", &choice);
    	choice = toupper(choice);
    	getchar(); // Consume the newline character left in the input buffer
    
    	switch (choice){
    	
    		case 'A':
    			printf("\nN/a\n");
    			break;
    		case 'B':
    			printf("\nN/a\n");
    			break;
    		case 'C':
    			add_employee();
    			break;
    		case 'X':
    			clean();
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 'X');
	
}

void add_employee(){
	
	clean();
	
	if (numUsers >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return;
    }

    printf("\n\t\tRegister New Employee\n\n");
    
    
    printf("Username: ");
    fgets(usernames[numUsers], MAX_NAME_LENGTH, stdin);
    strtok(usernames[numUsers], "\n"); // Remove the trailing newline character

    printf("Password: ");
    fgets(passwords[numUsers], MAX_PASSWORD_LENGTH, stdin);
    strtok(passwords[numUsers], "\n"); // Remove the trailing newline character

    printf("Name: ");
    fgets(name[numUsers], MAX_NAME_LENGTH, stdin);
    strtok(name[numUsers], "\n"); // Remove the trailing newline character

    printf("Address: ");
    fgets(address[numUsers], MAX_NAME_LENGTH, stdin);
    strtok(address[numUsers], "\n"); // Remove the trailing newline character

    printf("Position: ");
    fgets(position[numUsers], MAX_LENGTH, stdin);
    strtok(position[numUsers], "\n"); // Remove the trailing newline character

    printf("Contact: ");
    scanf("%d", &contact[numUsers]);
    getchar(); // Consume the newline character left in the input buffer after scanf
    
    userTypes[numUsers] = 0;
    

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


