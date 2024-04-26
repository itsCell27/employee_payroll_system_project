#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_USERS 10
#define MAX_USER_LENGTH 50
#define MAX_PASSWORD_LENGTH 20
#define MAX_CHAR 100


// Define user structure
typedef struct{
	
	char usernames[MAX_USER_LENGTH];
	char passwords[MAX_PASSWORD_LENGTH];
	char names[MAX_CHAR];
	char positions[MAX_CHAR];
	int contacts;
	int userTypes; // 0 for employee, 1 for admin
} User;

// Global arrays to store usernames, passwords, and user types
User users[MAX_USERS];
int numUsers = 0;

// Predefined admin credentials
char adminUsername[] = "admin";
char adminPassword[] = "admin123";

void main_menu();


User* find_user(const char *username); // Function to check if the username exists
void clean(); //clears console
void wait_clean(); //clears console after user press any key


void login_system();

// employee menu
void user();             
void user_payslip();
void user_info_update();

// admin menu
void admin();
void admin_manage();
void add_employee();



void main() {
	
    // Copy predefined admin account to array structure of "User"
    strcpy(users[0].usernames, adminUsername);
    strcpy(users[0].passwords, adminPassword);
    users[0].userTypes = 1; // set to admin
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
    	printf("*           Welcome to Employee Payroll System           *\n");
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
    			
		}
	}while(choice != 'X');
	
}

// Function to check if the username exists
User* find_user(const char *username){
    int i;
    
    for (i = 0; i < numUsers; i++) {
    	
    	if (strcmp(users[i].usernames, username) == 0) { // Checks if user exist
            	return &users[i]; // Return index of the user if found
        } 
    }
    return NULL; // Return NULL if username not found
}



void login_system(){
	
	int attempt = 4;       // number of attempts for username input
	int attempt_pass = 4;  // number of attempts for password input
	
	char username[MAX_USER_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    
    clean();
    
    do{ 
    	

    	printf("\n\t\tLogin\n\n");
    	printf("\t\tUsername: ");
    	scanf("%s", username);
    

    	User* index = find_user(username); // checks if username exists
    	if (index != NULL) { 
    		
    		attempt = 0; // stops the loop if username exists
    		
    		do{
    			
    			printf("\t\tPassword: ");
    			scanf("%s", password);
    			
    			int i;
    		
				if (strcmp(index->passwords, password) == 0) { // checks inputted password
				
					attempt_pass = 0; // stops the loop if password is corrects
					
					if (index->userTypes == 1){ //checks if its an admin
					
						clean();

    					printf("\n\n\tAdmin login successful. Welcome, %s!\n\n", username);
    					wait_clean();
        				admin();
					} else { // if not, prompts to employee menu
					
						clean();
					
						printf("\n\n\tEmployee login successful. Welcome, %s!\n\n", username);
    					wait_clean();
        				user(index);	
					}
				} else {
				
					clean();
					attempt_pass--;
					
					if(attempt_pass == 0){
						
						clean();
					} else {
						
						printf("\n\n\tWrong password! Please try again. [%d]\n\n", attempt_pass);
					}
					
				}
    			
			}while(attempt_pass != 0);
			
    		
        
    	} else {
    		
    		clean();
    		attempt--;
    		
    		if(attempt == 0){
    			
    			clean();
			} else {
				
				printf("\n\n\tUser does not exist. Please try again. [%d]\n\n", attempt);
			}
			
		} 
    	
	}while(attempt != 0);
    
    
}


// Function for the user menu
void user(){
	
	char choice;
	
	do{
		//design
		printf("\n**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*                      Employee Menu                     *\n");
    	printf("*                                                        *\n");
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
    	getchar(); // Consume the newline character left in the input buffer
    
    	switch (choice){
    	
    		case 'A':
    			user_payslip();
    			break;
    		case 'B':
    			user_info_update();
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
    	getchar(); // Consume the newline character left in the input buffer
    
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

void user_info_update(){
	
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
    	printf("*    [A] Full Name                                       *\n");
    	printf("*    [B] Address                                         *\n");
    	printf("*    [C] Contact                                         *\n");
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
    	choice = toupper(choice);
    	getchar(); // Consume the newline character left in the input buffer
    
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
    
    printf("\tUsername: ");
    scanf("%s", users[numUsers].usernames);
    
    printf("\tPassword: ");
    scanf("%s", users[numUsers].passwords);
    
    printf("\tName: ");
    scanf("%s", users[numUsers].names);
    
    printf("\tPosition: "); 
    scanf("%s", users[numUsers].positions);
    
    printf("\tContact: "); 
    scanf("%d", &users[numUsers].contacts);
    
    
    users[numUsers].userTypes = 0; // automatically set to employee

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

