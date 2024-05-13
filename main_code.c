////////////////////////////////////////////////////////////////////////////////////////
//																					  //
//																					  //
// 		   					  Employee Payroll System								  //
// 		   					  			by								              //
// 		   					    Group 7echKnoLogist									  //
//																					  //
//																					  //
//																					  //
////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_USERS 50             // maximum number of users
#define MAX_USER_LENGTH 50		 // maximum number of characters for usernames
#define MAX_PASSWORD_LENGTH 20   // maximum number of characters for password
#define MAX_CHAR 100			 // maximum number of characters for other char types
#define MAX_POSITION 50		 	 // maximum number of positions

// position structure
typedef struct{
	
	char position_name[MAX_CHAR];
	float hourly_rates;    	 			// pay per hour
	float overtime_rates;  	 			// overtime pay per hour
	
} Position;

// Define user structure
typedef struct{
	
	Position chosen_position; 			// To hold the chosen position for the user
	
	
	char passwords[MAX_PASSWORD_LENGTH]; 		// password of the user
	char usernames[MAX_USER_LENGTH];     		// username of the employee or admin   
	char names[MAX_CHAR];				 	    // name of the employee
	//char positions[MAX_POSITION][MAX_CHAR];	 	// position of the employee
	int contacts;						 		// contact number of the employee
	
	
	float work_hours;      				 		// total number of hours worked (in a Month).
	float overtime_hours;  				 		// total number of overtime in hours worked (in a Month).
	float bonus;                         		// amount of bonus of the employee (in a Month). 
	
	
	//int num_positions;					 // number of positions for this user
	int userTypes;         				 // 0 for employee, 1 for admin
	
} User;


Position positions[MAX_POSITION]; 	    // Global arrays to store different employee positions
User users[MAX_USERS];					// Global arrays to store employee account & information

int numPositions = 0;					// Counts the total number different positions the admin has created
int numUsers = 0;						// Counts the total number of registered employees


// Predefined admin credentials 	   // THIS IS THE ADMIN DEFAULT USERNAME AND PASSWORD
char adminUsername[] = "admin";        // admin username
char adminPassword[] = "admin123";	   // admin password


void main_menu();                      // main-menu of employee payroll system


User* find_user(const char *username); // Function to check if the username exists
void clean();                          // clears console
void wait_clean();                     // clears console after user press any key
void change_password(User* user);      // changes user password
void change_username(User* user);      // changes user username
void change_name(User* user);          // changes user name
void change_contact(User* user);       // changes user contact
void login_system();				   // user login menu

// employee menu
void user(User* user);                 // employee main-menu
void user_payslip(User* user);		   // displays salary payslip
void user_info_update(User* user);	   // displays & allows change of employee information

// admin menu
void admin(User* user);				   // admin main-menu
void admin_manage(User* user);		   // menu to manage employees
void add_employee();				   // register's new employee
void delete_employee();                // for deleting a specific employee
void add_position();		   		   // for adding different employee positions

// salary computations
float calculate_basic_salary(User* user);   // calculates basic salary
float calculate_overtime(User* user);       // calculates overtime pay
float calculate_gross_pay(User* user);      // calculates gross pay

/*
// deductions
float calculate_tax(User* user); 			// calculates tax deductions
float calculate_sss(User* user); 			// calculates SSS deductions
float calculate_philhealth(User* user); 	// calculates Philhealth deductions
float calculate_pagibig(User* user); 		// calculates Pagibig deductions
*/

int main() {
	
    // Copy predefined admin account to array structure of "User"
    strcpy(users[0].usernames, adminUsername);
    strcpy(users[0].passwords, adminPassword);
    users[0].userTypes = 1; // set to admin
    numUsers++;
    
    main_menu();
    
    
    return 0;
}


// Function for the main menu
void main_menu(){
	
	int choice;
	
	do{
		//design
		printf("\n ________________________________________________________\n");
    	printf("|                                                        |\n");
    	printf("|           Welcome to Employee Payroll System           |\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	printf("|                                                        |\n");
    	printf("|    [1] Login                                           |\n");
    	printf("|    [9] Exit                                            |\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	
    	printf("\tEnter: ");
    	scanf("%d", &choice);
    
    	switch (choice){
    	
    		case 1:
    			login_system();
    			break;
    			
    		case 9:
    			break;
    			
    		default:
    			clean();
    			printf("\n\t\t\tnot in option\n");
    			while (getchar() != '\n');           // Clear the input buffer (consume remaining characters including newline)
    			wait_clean();						 // Wait for keypress and clear console
    			break;
		}
		
	}while(choice != 9);
	
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
    	printf("\t\tEnter Username: ");
    	scanf("%s", username);
    

    	User* index = find_user(username); // checks if username exists
    	if (index != NULL) { 
    		
    		attempt = 0; // stops the loop if username exists
    		
    		do{
    			
    			printf("\t\tEnter Password: ");
    			scanf("%s", password);
    		
				if (strcmp(index->passwords, password) == 0) { // checks inputted password
				
					attempt_pass = 0; // stops the loop if password is correct
					
					if (index->userTypes == 1){ //checks if its an admin
					
						clean();

    					printf("\n\n\tAdmin login successful. Welcome, %s!\n\n", username);
    					wait_clean(); // Wait for keypress and clear console
        				admin(index);
        				
					} else { // if not, prompts to employee menu
					
						clean();
					
						printf("\n\n\tEmployee login successful. Welcome, %s!\n\n", username);
    					wait_clean(); // Wait for keypress and clear console
        				user(index);
							
					}
				} else {	
				
					// if password is incorrect
					
					clean();
					attempt_pass--; // decrease the number of attempts
					
					if(attempt_pass == 0){
						
						clean();
					} else {
						
						printf("\n\n\tWrong password! Please try again. [%d]\n\n", attempt_pass);
					}
					
				}
    			
			}while(attempt_pass != 0);
			
    		
        
    	} else {
    		
    		// if username does not exists
    		
    		clean();
    		attempt--;	// decrease the number of attempts
    		
    		if(attempt == 0){
    			
    			clean();
			} else {
				
				printf("\n\n\tUser does not exist. Please try again. [%d]\n\n", attempt);
			}
			
		} 
    	
	}while(attempt != 0);
    
    
}


// Function for the user menu
void user(User* user){
	
	int choice;
	
	do{
		//design
		printf("\n\n\n\t\t*** Welcome: %s ***\n\n", user->usernames);                 //need I rework ung design 
		printf("\n ________________________________________________________\n");
    	printf("|                                                        |\n");
    	printf("|                      Employee Menu                     |\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	printf("|                                                        |\n");
    	printf("|    [1] View Payslip                                    |\n");
    	printf("|    [2] Update personal info                            |\n");
    	printf("|    [9] Logout                                          |\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	printf("\tEnter: ");
    	scanf("%d", &choice);
    
    	switch (choice){
    	
    		case 1:
    			user_payslip(user);
    			break;
    			
    		case 2:
    			user_info_update(user);
    			break;
    			
    		case 9:
    			clean();
    			break;
    			
    		default:
    			clean();
    			printf("\n\t\t\tnot in option\n");
    			while (getchar() != '\n');           // Clear the input buffer (consume remaining characters including newline)
    			wait_clean();						 // Wait for keypress and clear console
    			break;
    			
		}
		
	}while(choice != 9);
	
}

void user_payslip(User* user){
	
	int choice;
	
	float basic_salary = calculate_basic_salary(user);
	float overtime = calculate_overtime(user);
	float user_gross_pay = calculate_gross_pay(user);
	
	clean();
	
	do{
		//design & display payslip
		printf("\n ________________________________________________________\n");
    	printf("|                                                        |\n");
    	printf("|                      Salary Payslip                    |\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	printf("|                                                        |\n");
    	printf("| Personal Information:                                  |\n");
    	printf("|                                                        |\n");
    	printf("| Employee Name: %s                                      |\n", user->names);
    	printf("| Position: %s                                           |\n", user->chosen_position.position_name);
    	printf("| Contact: %d                                            |\n", user->contacts);
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	printf("|                                                        |\n");
    	printf("| Regular Hours Worked: %.0f                             |\n", user->work_hours);
    	printf("| Hourly Rate: %.2f                                      |\n", user->chosen_position.hourly_rates);
    	printf("| Overtime Hours Worked: %.0f                            |\n", user->overtime_hours);
    	printf("| Overtime Rate: %.2f                                    |\n", user->chosen_position.overtime_rates);
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	printf("|                                                        |\n");
    	printf("| Earnings:                                              |\n");
    	printf("|                                                        |\n");
    	printf("| Basic Salary: %.2f                                     |\n", basic_salary);
    	printf("| Overtime: %.2f                                         |\n", overtime);
    	printf("| Bonus: %.2f                                            |\n", user->bonus);
    	printf("| Total Earnings: %.2f                                   |\n", user_gross_pay);
    	printf("|                                                        |\n");
    	printf("|                                                        |\n");
    	printf("| Deductions:                                            |\n");
    	printf("|                                                        |\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	printf("|                                                        |\n");
    	printf("|    [9] Back                                            |\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	printf("\tEnter: ");
    	scanf("%d", &choice);
    
    	switch (choice){
    	
    		case 9:
    			clean();						
    			break;
    			
    		default:
    			clean();
    			printf("\n\t\t\tnot in option\n");
    			while (getchar() != '\n');           // Clear the input buffer (consume remaining characters including newline)
    			wait_clean();						 // Wait for keypress and clear console
    			break;
    			
		}
		
	}while(choice != 9);
	
}

void user_info_update(User* user){
	
	int choice;
	
	clean();
	
	do{
		//design
		// need I rework ung design magmula dito
		printf("__________________________________________________________\n");
		printf("|\n\n\n\tUser Information                                |\n");
    	printf("|________________________________________________________|\n");
    	printf("|\tUsername: %s                          				 |\n", user->usernames);
    	printf("|\tName: %s                                              |\n", user->names);
    	printf("|\tPosition: %s                                          |\n", user->chosen_position.position_name);
    	printf("|\tContact: %d                                           |\n", user->contacts);
    	printf("|________________________________________________________|\n");
    	// hanggang dito
    	
    	
		printf("\n ________________________________________________________\n");
    	printf("|                                                        |\n");
    	printf("|               Update Personal Information              |\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	printf("|                                                        |\n");
    	printf("|    [1] Change Username                                 |\n");
    	printf("|    [2] Change Full Name                                |\n");
    	printf("|    [3] Change Contact                                  |\n");
    	printf("|    [4] Change Password                                 |\n");
    	printf("|    [9] Back                                            |\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	printf("\tEnter: ");
    	scanf("%d", &choice);
    
    	switch (choice){
    	
    		case 1:
    			change_username(user);
    			break;
    			
    		case 2:
    			change_name(user);
    			break;
    			
    		case 3:
    			change_contact(user);
    			break;
    			
    		case 4:
    			change_password(user);
    			break;
    			
    		case 9:
    			clean();
    			break;
    			
    		default:
    			clean();
    			printf("\n\t\t\tnot in option\n");
    			while (getchar() != '\n');           // Clear the input buffer (consume remaining characters including newline)
    			wait_clean();						 // Wait for keypress and clear console
    			break;
    			
		}
		
	}while(choice != 9);
	
}


// Function for the admin menu
void admin(User* user){
	
	int choice;
	
	do{
		//design
		printf("\n ________________________________________________________\n");
    	printf("|                                                        |\n");
    	printf("|                      Admin Menu                        |\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	printf("|                                                        |\n");
    	printf("|    [1] Manage Employees                                |\n");
    	printf("|    [2] Change Password                                 |\n");
    	printf("|    [9] Logout                                          |\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	printf("\tEnter: ");
    	scanf("%d", &choice);
    
    	switch (choice){
    	
    		case 1:
    			admin_manage(user);
    			break;
    			
    		case 2:
    			change_password(user);
    			break;
    			
    		case 9:
    			clean();
    			break;
    			
    		default:
    			clean();
    			printf("\n\t\t\tnot in option\n");
    			while (getchar() != '\n');           // Clear the input buffer (consume remaining characters including newline)
    			wait_clean();						 // Wait for keypress and clear console
    			break;
    			
		}
		
	}while(choice != 9);
	
}

void admin_manage(User* user){
	
	int i, choice;
	
	clean();
	
	do{
		// Paayos ng display neto hindi pantay, magmula DITO.
		//design
		printf("\n ________________________________________________________\n");
    	printf("|                                                        |\n");
    	printf("|                   Manage Employees                     |\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	
    	// Check if there are any user account 
    	if (numUsers == 1) {
    	
        	printf("\n\nNo Employees registered.\n");
        	
    	} else {
    		
        printf("\nEmployee List:\n");
        	printf(" _______________________________________________________________________________________________________________________________________________\n");
        	printf("|ID\t|Name\t\t\t|Position\t\t|Basic Salary\t\t|Overtime\t|Bonus\t\t|Total Earnings                 |\n");
        	printf("|_______|_______________________|_______________________|_______________________|_______________|_______________|_______________________________|\n");

        	// Loop through each user and display their details
        	for (i = 1; i < numUsers; i++) {
        		
            	// Calculate basic salary, overtime, and gross pay
            	float basic_salary = calculate_basic_salary(&users[i]);
            	float overtime = calculate_overtime(&users[i]);
            	float gross_pay = calculate_gross_pay(&users[i]);

            	// Print employee details along with computed values
            	printf("|%d\t|%s\t\t|%s\t\t\t|%.2f\t\t|%.2f\t|%.2f\t|%.2f\t\t\t|\n", i, users[i].names, users[i].chosen_position.position_name, basic_salary, overtime, users[i].bonus, gross_pay);
            	
        	}
            printf("|_______|_______________________|_______________________|_______________________|_______________|_______________|_______________________________|\n");
    	}
    	
    	printf(" ________________________________________________________\n");
    	printf("|                                                        |\n");
    	printf("|    [1] Edit salary                                     |\n");
    	printf("|    [2] Delete employee                                 |\n");
    	printf("|    [3] Add employee                                    |\n");
    	printf("|    [4] Add positon                                     |\n");
    	printf("|    [9] Back                                            |\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	// hanggang DITO!
    	
    	printf("\tEnter: ");
    	scanf("%d", &choice);
    
    	switch (choice){
    	
    		case 1:
    			printf("\nN/a\n");
    			break;
    			
    		case 2:
    			delete_employee();
    			break;
    			
    		case 3:
    			add_employee();
    			break;
    			
    		case 4:
    			add_position();
    			break;
    			
    		case 9:
    			clean();
    			break;
    			
    		default:
    			clean();
    			printf("\n\t\t\tnot in option\n");
    			while (getchar() != '\n');           // Clear the input buffer (consume remaining characters including newline)
    			wait_clean();						 // Wait for keypress and clear console
    			break;
    			
		}
		
	}while(choice != 9);
	
}

// for deleting a specific employee
void delete_employee() {
	
	int i;
    clean(); // Clear console

	// paayos ng design neto hindi pantay, magmula DITO!
    printf(" ________________________________________________________\n");
    printf("|                                                        |\n");
    printf("|                   Delete Employee                      |\n");
    printf("|                                                        |\n");
    printf("|________________________________________________________|\n");

    // Display employee list with IDs
    if (numUsers == 1) {
    	
        printf("\n\nNo Employees registered.\n");
        
    } else {
    	
        printf("\nEmployee List:\n");
        printf(" _______________________________________________________________________________________________________________________________________________\n");
        printf("|ID\t|Name\t\t\t|Position\t\t|Basic Salary\t\t|Overtime\t|Bonus\t\t|Total Earnings                 |\n");
        printf("|_______|_______________________|_______________________|_______________________|_______________|_______________|_______________________________|\n");
        // Loop through each user and display their details
        for (i = 1; i < numUsers; i++) {
        	
        	// Calculate basic salary, overtime, and gross pay
            float basic_salary = calculate_basic_salary(&users[i]);
            float overtime = calculate_overtime(&users[i]);
            float gross_pay = calculate_gross_pay(&users[i]);

			// Print employee details along with computed values
            printf("|%d\t|%s\t\t|%s\t\t\t|%.2f\t\t|%.2f\t|%.2f\t|%.2f\t\t\t|\n", i, users[i].names, users[i].chosen_position.position_name, basic_salary, overtime, users[i].bonus, gross_pay);
        }
        printf("|_______|_______________________|_______________________|_______________________|_______________|_______________|_______________________________|\n");
	// hanggang DITO!
	
	
        // Prompt for employee number to delete
        printf("\nEnter the number of the employee to delete: ");
        int id;
        scanf("%d", &id);
        getchar(); // Consume the newline character left in the input buffer

        // Validate ID
        if (id >= 0 && id <= numUsers) {
            // Check if the selected user is the admin
            if (strcmp(users[id].usernames, "admin") == 0) {
                printf("\nYou cannot delete the admin account.\n");
            } else {
                // Shift elements to remove the selected employee
                for (i = id; i < numUsers - 1; i++) {
                    users[i] = users[i + 1]; // Shifts the selected id number "i" to the last element of array
                }
                numUsers--; // Decrement the number of users
                printf("\nEmployee deleted successfully.\n");
            }
        } else {
            printf("\nInvalid employee ID.\n");
        }
    }

    wait_clean(); // Wait for keypress and clear console
}

// register's new employee "ONLY ADMIN CAN REGISTER"
void add_employee(){
	
	int i;
	
	clean();
	
	// Check if positions are available
	if (numPositions == 0){
		
		printf("\n\tNo positions are available. Please add a position first\n");
		wait_clean();
		return;
	}
	
	// Check if maximum number of users reached
	if (numUsers >= MAX_USERS) {
		
        printf("\n\t\tMaximum number of users reached.\n");
        return;
    }

	// need I-rework design
    printf("\n\t\tRegister New Employee\n\n");
    
    User new_user;
    
    printf("\tEnter Username: ");
    scanf("%s", new_user.usernames);
    
    printf("\tEnter Password: ");
    scanf("%s", new_user.passwords);
    getchar(); // Consume the newline character left in the input buffer
    
    printf("\tEnter Name: ");
    scanf("%[^\n]s", new_user.names);    // Use %[^\n] to read the entire line including spaces
    
    printf("\tEnter Contact: "); 
    scanf("%d", &new_user.contacts);
    
    printf("\n\n\t\tEmployee Salary Computation\n\n");
    
    // Display available positions
    
    int chosen_index;
    
    do{
    	
    	chosen_index = 0;
    	
    	printf("\n\t\tAvailable Positions\n\n");
    
    	for(i = 0; i < numPositions; i++){
    	
    	
    		printf("\t\t[%d] %s\n", i + 1, positions[i].position_name);
		}
    
    	
    	printf("\n\tChoose Position (Enter number): ");
    	scanf("%d", &chosen_index);
    
    	// Validate the chosen position index
        if (chosen_index < 1 || chosen_index > numPositions) {
            printf("\n\tInvalid position choice. Please choose a valid position.\n");
        }
        
	}while (chosen_index < 1 || chosen_index > numPositions);
    
    new_user.chosen_position = positions[chosen_index - 1]; // Assign chosen position // adjust to 0 based index
    
    
    printf("\tEnter Total number of hours worked (in a month): "); 
    scanf("%f", &new_user.work_hours);
    
    printf("\tEnter Total number of overtime hours worked (in a month): "); 
    scanf("%f", &new_user.overtime_hours);
    
    printf("\tEnter Total Bonuses (in a month): "); 
    scanf("%f", &new_user.bonus);
    
    new_user.userTypes = 0; // automatically set to employee
    
    users[numUsers] = new_user;
    numUsers++;

    printf("\tRegistration successful.\n");
    
    wait_clean();
    
}

// basic salary computation
float calculate_basic_salary(User* user){
	
	float basic_salary = 0.0;
	
	basic_salary = user->work_hours * user->chosen_position.hourly_rates;
	
	return basic_salary;
}

// overtime pay calculation
float calculate_overtime(User* user){
	
	float overtime = 0.0;
	
	overtime = user->overtime_hours * user->chosen_position.overtime_rates;
	
	return overtime;
}

// gross pay computation
float calculate_gross_pay(User* user){
	
	float salary = calculate_basic_salary(user);
	float overtime = calculate_overtime(user);
	
	float gross_pay = salary + overtime + user->bonus;
	
	return gross_pay;
	
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

// change password
void change_password(User* user){
	
	clean();
	
	char currentPassword[MAX_PASSWORD_LENGTH];
	
    printf("\n\tEnter current password: ");
    scanf("%s", currentPassword);
    
    if (strcmp(currentPassword, user->passwords) == 0) { // checks inputted password
    	
        printf("\n\tEnter new password: ");
        scanf("%s", user->passwords);
            
        printf("\n\tPassword updated successfully.\n");
        wait_clean();
            
    } else {
    	
        printf("\n\tIncorrect password. Password not updated.\n");
        wait_clean();
    }
    
}

// for changing username
void change_username(User* user){
	
	clean();
	
	//getchar(); // Consume the newline character left in the input buffer
	printf("\nEnter new username: ");
    scanf(" %s", user->usernames); 
    printf("\nUsername updated successfully.\n");
    
    wait_clean();
}

// for changing name
void change_name(User* user){
	
	clean();
	
	printf("\nEnter new name: ");
    scanf(" %[^\n]", user->names); // Use %[^\n] to read the entire line including spaces
    getchar(); // Consume the newline character left in the input buffer
    printf("\nName updated successfully.\n");
    
    wait_clean();
}

// for changing contact
void change_contact(User* user){
	
	clean();
	
	//getchar(); // Consume the newline character left in the input buffer
	printf("\nEnter new contact: ");
    scanf("%d", &user->contacts); 
    printf("\nContact updated successfully.\n");
    
    wait_clean();
}

// for adding employee position
void add_position(User* user){
	
	clean();
	
	if(numPositions >= MAX_POSITION){
		
		printf("\n\n\t\tMaximum positions reached.\n\n");
		wait_clean();
		return;
	}
	
	printf("\n\n\t\tAdd new position\n\n");
	
	Position new_position;
	
	printf("\n\n\t\tEnter Position Name: ");
	scanf("%s", new_position.position_name);
	
	printf("\n\n\t\tEnter Basic Salary Rate (Per Hour): ");
	scanf("%f", &new_position.hourly_rates);
	
	
	printf("\n\n\t\tEnter Overtime Rate (Per Hour): ");
	scanf("%f", &new_position.overtime_rates);
	
	positions[numPositions] = new_position;
	numPositions++;
	
	printf("\n\t\tPosition Added Succesfully");
	
	wait_clean();
}















