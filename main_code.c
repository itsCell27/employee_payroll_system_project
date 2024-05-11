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


// Define user structure
typedef struct{
	
	char passwords[MAX_PASSWORD_LENGTH]; 		// password of the user
	char usernames[MAX_USER_LENGTH];     		// username of the employee or admin   
	char names[MAX_CHAR];				 	    // name of the employee
	char positions[MAX_POSITION][MAX_CHAR];	 	// position of the employee
	int contacts;						 		// contact number of the employee
	
	
	float work_hours;      				 		// total number of hours worked.
	float hourly_rates[MAX_POSITION];    	 	// pay per hour
	float overtime_rates[MAX_POSITION];  	 	// overtime pay per hour
	float overtime_hours;  				 		// total number of overtime in hours worked.
	float bonus;                         		// amount of bonus of the employee 
	
	
	int num_positions;					 // number of positions for this user
	int userTypes;         				 // 0 for employee, 1 for admin
	
} User;

// Global arrays to store usernames, passwords, and user types
User users[MAX_USERS];
int numUsers = 0;

// Predefined admin credentials
char adminUsername[] = "admin";        // admin username
char adminPassword[] = "admin123";	   // admin password
char adminName[] = "ADMIN";			   // admin name 

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
void add_position(User* user);		   // for adding different employee positions

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
    strcpy(users[0].names, adminName);
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
    	printf("\t\tUsername: ");
    	scanf("%s", username);
    

    	User* index = find_user(username); // checks if username exists
    	if (index != NULL) { 
    		
    		attempt = 0; // stops the loop if username exists
    		
    		do{
    			
    			printf("\t\tPassword: ");
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
    	printf("| Position: %s                                           |\n", user->positions[0]);
    	printf("| Contact: %d                                            |\n", user->contacts);
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	printf("|                                                        |\n");
    	printf("| Regular Hours Worked: %.0f                             |\n", user->work_hours);
    	printf("| Hourly Rate: %.2f                                      |\n", user->hourly_rates[0]);
    	printf("| Overtime Hours Worked: %.0f                            |\n", user->overtime_hours);
    	printf("| Overtime Rate: %.2f                                    |\n", user->overtime_rates[0]);
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
		printf(" _________________________________________\n");
		printf("|\n\n\n\tUser Information                |\n");
    	printf("|________________________________________|\n");
    	printf("|\tUsername: %s                          |\n", user->usernames);
    	printf("|\tName: %s                              |\n", user->names);
    	printf("|\tPosition: %s                          |\n", user->positions);
    	printf("|\tContact: %d                           |\n", user->contacts);
    	printf("|________________________________________|\n");
    	// hanggang dito
    	
    	
		printf("\n ________________________________________________________\n");
    	printf("|                                                        |\n");
    	printf("|               Update Personal Information              |\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	printf("|                                                        |\n");
    	printf("|    [1] Username                                        |\n");
    	printf("|    [2] Full Name                                       |\n");
    	printf("|    [3] Contact                                         |\n");
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
    	if (numUsers == 0) {
    	
        	printf("\n\nNo account registered.\n");
        	
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
            	printf("|%d\t|%s\t\t|%s\t\t\t|%.2f\t\t|%.2f\t|%.2f\t|%.2f\t\t\t|\n", i, users[i].names, users[i].positions[0], basic_salary, overtime, users[i].bonus, gross_pay);
            	
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
    			add_position(user);
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
    if (numUsers == 0) {
        printf("\nNo employees registered.\n");
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
            printf("|%d\t|%s\t\t|%s\t\t\t|%.2f\t\t|%.2f\t|%.2f\t|%.2f\t\t\t|\n", i, users[i].names, users[i].positions[0], basic_salary, overtime, users[i].bonus, gross_pay);
        }
            printf("|_______|_______________________|_______________________|_______________________|_______________|_______________|_______________________________|\n");
	// hanggang DITO!
	
	
        // Prompt for employee ID to delete
        printf("\nEnter the ID of the employee to delete: ");
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
	
	if (users[0].num_positions == 0){
		
		printf("\n\tNo positions are available. Please add positon firts\n");
		wait_clean();
		return;
	}
	
	if (numUsers >= MAX_USERS) {
        printf("\n\t\tMaximum number of users reached.\n");
        return;
    }

	// need I-rework design
    printf("\n\t\tRegister New Employee\n\n");
    
    printf("\tUsername: ");
    scanf("%s", users[numUsers].usernames);
    
    printf("\tPassword: ");
    scanf("%s", users[numUsers].passwords);
    getchar(); // Consume the newline character left in the input buffer
    
    printf("\tName: ");
    scanf("%[^\n]s", users[numUsers].names);    // Use %[^\n] to read the entire line including spaces
    
    printf("\tContact: "); 
    scanf("%d", &users[numUsers].contacts);
    
    printf("\n\n\t\tEmployee Salary Computation\n\n");
    
    // Display available positions
    printf("\n\tPositions\n\n");
    
    for(i = 0; i < users[0].num_positions; i++){
    	
    	
    	printf("[%d] %s\n", i + 1, users[0].positions[i]);
	}
    
    int chosen_position;
    printf("\n\tChoose Position: ");
    scanf("%d", &chosen_position);
    
    chosen_position--; // adjust to 0 based index
    
    // assign selected position details to the new employee
    strcpy(users[numUsers].positions[0], users[0].positions[chosen_position]);
    users[numUsers].hourly_rates[0] = users[0].hourly_rates[chosen_position];
    users[numUsers].overtime_rates[0] = users[0].overtime_rates[chosen_position];
    
    users[numUsers].num_positions = 1; // new employee has only 1 position
    
    printf("\tTotal number of hours worked (in a month): "); 
    scanf("%f", &users[numUsers].work_hours);
    
    printf("\tTotal number of overtime hours worked (in a month): "); 
    scanf("%f", &users[numUsers].overtime_hours);
    
    printf("\tTotal Bonuses (in a month): "); 
    scanf("%f", &users[numUsers].bonus);
    
    users[numUsers].userTypes = 0; // automatically set to employee

    printf("\tRegistration successful.\n");

    numUsers++;
    
    wait_clean();
    
}

// basic salary computation
float calculate_basic_salary(User* user){
	
	float basic_salary = 0.0;
	int i;
	
	for(i = 0; i < user->num_positions; i++){
		
		basic_salary += user->work_hours * user->hourly_rates[i];
	}
	
	return basic_salary;
}

// overtime pay calculation
float calculate_overtime(User* user){
	
	float overtime = 0.0;
	int i;
	
	for(i = 0; i < user->num_positions; i++){
		
		overtime += user->overtime_hours * user->overtime_rates[i];
	}
	
	return overtime;
}

// gross pay computation
float calculate_gross_pay(User* user){
	
	float salary = calculate_basic_salary(user);
	float overtime = calculate_overtime(user);
	
	float gross_pay = salary + overtime + user->bonus;
	//float gross_pay = (user->work_hours * user->hourly_rates) + (user->overtime_hours * user->overtime_rates);
	
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
    
    if (strcmp(currentPassword, user->passwords) == 0) {
    	
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
	
	printf("\n\n\t\tAdd new position\n\n");
	
	if(user->num_positions >= MAX_POSITION){
		
		printf("\n\n\t\tMaximum positions reached.\n\n");
		wait_clean();
		return;
	}
	
	printf("\n\n\t\tPosition Name: ");
	scanf("%s", user->positions[user->num_positions]);
	
	printf("\n\n\t\tBasic Salary Rate: ");
	scanf("%f", &user->hourly_rates[user->num_positions]);
	
	
	printf("\n\n\t\tOvertime Rate: ");
	scanf("%f", &user->overtime_rates[user->num_positions]);
	
	user->num_positions++;
	
	printf("\n\t\tPosition Added Succesfully");
	
	wait_clean();
}















