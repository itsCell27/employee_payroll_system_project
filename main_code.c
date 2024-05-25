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
	
	Position chosen_position; 					// To hold the chosen position for the user
	
	
	char passwords[MAX_PASSWORD_LENGTH]; 		// password of the user
	char usernames[MAX_USER_LENGTH];     		// username of the employee or admin   
	char names[MAX_CHAR];				 	    // name of the employee
	char contacts[11]; 							// Char array to handle contact number validation, max 10 digits + null terminator // contact number of the employee
	
	
	float work_hours;      				 		// total number of hours worked (in a Month).
	float overtime_hours;  				 		// total number of overtime in hours worked (in a Month).
	float bonus;                         		// amount of bonus of the employee (in a Month). 
	

	int userTypes;         				 		// 0 for employee, 1 for admin
	
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
int is_valid_username(char* username); // Check if the username contains any spaces 
int is_valid_password(char* password); // Check if the password contains any spaces
int is_valid_contact(char* contact);   // Function to check if the contact number is at most 10 digits and only contains digits
void forgot_password();				   // Function for password reset

// employee menu
void user(User* user);                 // employee main-menu
void user_payslip(User* user);		   // displays salary payslip
void user_info_update(User* user);	   // displays & allows change of employee information

// admin menu
void admin(User* user);				   // admin main-menu
void admin_manage(User* user);		   // menu to manage employees
void edit_salary();					   // for  editing employee salary
void add_employee();				   // register's new employee
void delete_employee();                // for deleting a specific employee
void add_position();		   		   // for adding different employee positions
void change_employee_position();       // for changing employee position

// salary computations
float calculate_basic_salary(User* user);   // calculates basic salary
float calculate_overtime(User* user);       // calculates overtime pay
float calculate_gross_pay(User* user);      // calculates gross pay

// deductions
float tax_computation(User* user);          // calculates tax deductions
float sss_computation(User* user);			// calculates SSS deductions
float pagibig_computation(User* user);      // calculates Pagibig deductions
float philhealth_computation(User* user);	// calculates Philhealth deductions
float total_deductions(User* user);         // calculates total deductions

float netpay(User* user);                   // calculates Netpay = gross pay - total deductions

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
    	printf("|    [2] Forgot Password                                 |\n");
    	printf("|    [9] Exit                                            |\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	
    	printf("\tEnter: ");
    	scanf("%d", &choice);
    
    	switch (choice){
    	
    		case 1:
    			login_system();
    			break;
    			
    		case 2:
    			forgot_password();
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
		
	}while (choice != 9);
	
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
    	
	}while (attempt != 0);
    
    
}

// Function to handle forgot password
void forgot_password() {
	
    char username[MAX_USER_LENGTH];
    char contact[11];
    
    clean();
    
    printf("\t\tForgot Password\n\n");
    printf("\tEnter your username: ");
    scanf("%s", username);
    
    // Find the user with the given username
    User *user = find_user(username);
    
    if (user != NULL) {
    	
        printf("\tEnter your contact number: ");
        scanf("%s", contact);
        
        // Check if the entered contact number matches the user's contact number
        if (strcmp(user->contacts, contact) == 0) {
        	
            char new_password[MAX_PASSWORD_LENGTH];
            char confirm_password[MAX_PASSWORD_LENGTH];
            
            printf("\tEnter your new password: ");
            scanf("%s", new_password);
            
            printf("\tConfirm your new password: ");
            scanf("%s", confirm_password);
            
            // Check if the new password and confirmation match
            if (strcmp(new_password, confirm_password) == 0) {
            	
                strcpy(user->passwords, new_password);
                wait_clean();
                printf("\tPassword successfully reset!\n");
            } else {
            	
                printf("\tPasswords do not match. Please try again.\n");
                wait_clean();
            }
        } else {
        	
            printf("\tContact number does not match. Password reset failed.\n");
            wait_clean();
        }
    } else {
    	
        printf("\tUsername not found.\n");
        wait_clean();
    }
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
		
	}while (choice != 9);
	
}

void user_payslip(User* user){
	
	int choice;
	
	float basic_salary = calculate_basic_salary(user);
	float overtime = calculate_overtime(user);
	float user_gross_pay = calculate_gross_pay(user);
	float tax =  tax_computation(user);
	float sss =  sss_computation(user);
	float pagibig = pagibig_computation(user);
	float philhealth = philhealth_computation(user);
	float total_deduction = total_deductions(user);
	float netpays = netpay(user);
	
	
	
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
    	printf("|                                                        \n");
    	printf("| Employee Name: %s                                      \n", user->names);
    	printf("| Position: %s                                           \n", user->chosen_position.position_name);
    	printf("| Contact: %d                                            \n", user->contacts);
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	printf("|                                                        |\n");
    	printf("| Regular Hours Worked: %.0f                             \n", user->work_hours);
    	printf("| Hourly Rate: %.2f                                      \n", user->chosen_position.hourly_rates);
    	printf("| Overtime Hours Worked: %.0f                            \n", user->overtime_hours);
    	printf("| Overtime Rate: %.2f                                    \n", user->chosen_position.overtime_rates);
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	printf("|                                                        |\n");
    	printf("| Earnings:                                              |\n");
    	printf("|                                                        \n");
    	printf("| Basic Salary: %.2f                                     \n", basic_salary);
    	printf("| Overtime: %.2f                                         \n", overtime);
    	printf("| Bonus: %.2f                                            \n", user->bonus);
    	printf("| Total Earnings: %.2f                                   \n", user_gross_pay);
    	printf("|                                                        |\n");
    	printf("|                                                        |\n");
    	printf("| Deductions:                                            |\n");
    	printf("|                                                        |\n");
    	printf("| Tax: %.2f                                              \n", tax);
    	printf("| SSS: %.2f                                              \n", sss);
    	printf("| Pagibig: %.2f                                          \n", pagibig);
    	printf("| Philhealth: %.2f                                       \n", philhealth);
    	printf("| Total Deductions: %.2f                                 \n", total_deduction);
    	printf("|                                                        |\n");
    	printf("| Net Pay: %.2f                                          \n", netpays);
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
		
	}while (choice != 9);
	
}

void user_info_update(User* user){
	
	int choice;
	
	clean();
	
	do{
	
		// need I rework ung design magmula dito
		printf("__________________________________________________________\n");
		printf("|\n\n\n\tUser Information                                |\n");
    	printf("|________________________________________________________|\n");
    	printf("|\tUsername: %s                          				 \n", user->usernames);
    	printf("|\tName: %s                                              \n", user->names);
    	printf("|\tPosition: %s                                          \n", user->chosen_position.position_name);
    	printf("|\tContact: %d                                           \n", user->contacts);
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
		
	}while (choice != 9);
	
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
		
	}while (choice != 9);
	
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
    	
        	printf("\n\n\tNo Employees registered.\n");
        	
    	} else {
    		
        	printf("\nEmployee List:\n");
        	printf("=================================================================================================================================================\n");
        	printf("|ID\t|Name\t|Position\t|Basic Salary\t|Overtime\t|Bonus\t|Total Earnings\t|Total Deductions\n");
        	printf("=================================================================================================================================================\n");

        	// Loop through each user and display their details
        	for (i = 1; i < numUsers; i++) {
        		
            	// Calculate basic salary, overtime, and gross pay
            	float basic_salary = calculate_basic_salary(&users[i]);
            	float overtime = calculate_overtime(&users[i]);
            	float gross_pay = calculate_gross_pay(&users[i]);
            	float total_deduction = total_deductions(&users[i]);

            	// Print employee details along with computed values
            	printf("|%d\t|%s\t|%s\t|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%.2f\n", i, users[i].names, users[i].chosen_position.position_name, basic_salary, overtime, users[i].bonus, gross_pay, total_deduction);
            	
        	}
            printf("=================================================================================================================================================\n");
    	}
    	
    	printf(" ________________________________________________________\n");
    	printf("|                                                        |\n");
    	printf("|    [1] Add employee                                    |\n");
    	printf("|    [2] Add position                                    |\n");
    	printf("|    [3] Delete employee                                 |\n");
    	printf("|    [4] Edit salary                                     |\n");
    	printf("|    [5] Change employee position                        |\n");
    	printf("|    [9] Back                                            |\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	// hanggang DITO!
    	
    	printf("\tEnter: ");
    	scanf("%d", &choice);
    
    	switch (choice){
    	
    		case 1:
    			add_employee();
    			break;
    			
    		case 2:
    			add_position();
    			break;
    			
    		case 3:
    			delete_employee();
    			break;
    			
    		case 4:
    			edit_salary();
    			break;
    		
    		case 5:
    			change_employee_position();
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
		
	}while (choice != 9);
	
}

// for editing employee salary
void edit_salary() {
	
	int i;
    int id;
    int choice;
    float new_value;

	do{
		
		clean();
		
		if(numUsers == 1){
    	
    		printf("\n\n\tNo Employees registered.\n");
    		wait_clean();
    		return;
		}

    	printf("\nEmployee List:\n");
        printf("=================================================================================================================================================\n");
        printf("|ID\t|Name\t|Position\t|Basic Salary\t|Overtime\t|Bonus\t|Total Earnings\t|Total Deductions\n");
        printf("=================================================================================================================================================\n");

        // Loop through each user and display their details
        for (i = 1; i < numUsers; i++) {
        		
            // Calculate basic salary, overtime, and gross pay
            float basic_salary = calculate_basic_salary(&users[i]);
            float overtime = calculate_overtime(&users[i]);
            float gross_pay = calculate_gross_pay(&users[i]);
            float total_deduction = total_deductions(&users[i]);

            // Print employee details along with computed values
            printf("|%d\t|%s\t|%s\t|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%.2f\n", i, users[i].names, users[i].chosen_position.position_name, basic_salary, overtime, users[i].bonus, gross_pay, total_deduction);
            	
        }
        printf("=================================================================================================================================================\n");

    	// Prompt for employee ID to change details
    	printf("\nEnter the ID of the employee whose details you want to change: ");
    	scanf("%d", &id);
    	

    	// Validate ID
    	if (id < 1 || id >= numUsers) {  // Adjusted to start ID from 1 and ensure it's within the valid range
    
        	printf("\nInvalid employee ID.\n");
        	wait_clean();
       		return;
    	}
    	
	}while (id < 1 || id >= numUsers);
    
	
		
		// Display options to change
   		printf(" ________________________________________________________\n");
    	printf("|                                                        |\n");
    	printf("|    Select the detail to change                         |\n");
    	printf("|                                     					 |\n");
    	printf("|    [1] Work Hours                          	         |\n");
    	printf("|    [2] Overtime Hours                                  |\n");
    	printf("|    [3] Bonus                                           |\n");
    	printf("|    [9] Cancel                                          |\n");
	    printf("|                                                        |\n");
	    printf("|________________________________________________________|\n\n");
    	
    	printf("\n\tEnter your choice: ");
    	scanf("%d", &choice);

    	// Validate choice and update the corresponding detail
    	switch (choice) {
    	
        	case 1:
            	printf("\nEnter new Work Hours: ");
            	scanf("%f", &new_value);
            	users[id].work_hours = new_value;
            	printf("\nWork Hours updated successfully for employee '%s'.\n", users[id].usernames);
            	wait_clean();
            	break;
            
        	case 2:
            	printf("\nEnter new Overtime Hours: ");
            	scanf("%f", &new_value);
            	users[id].overtime_hours = new_value;
            	printf("\nOvertime Hours updated successfully for employee '%s'.\n", users[id].usernames);
            	wait_clean();
            	break;
            
        	case 3:
            	printf("\nEnter new Bonus: ");
            	scanf("%f", &new_value);
            	users[id].bonus = new_value;
            	printf("\nBonus updated successfully for employee '%s'.\n", users[id].usernames);
            	wait_clean();
            	break;
            
        	case 9:
        		printf("\nOperation Cancelled\n");
    			wait_clean();
    			break;
            
        	default:
            	clean();
    			printf("\n\t\t\tnot in option\n");
    			while (getchar() != '\n');           // Clear the input buffer (consume remaining characters including newline)
    			wait_clean();						 // Wait for keypress and clear console
    			break;
            
    	}

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
    	
        printf("\n\n\tNo Employees registered.\n");
        
    } else {
    	
        // Paayos ng display neto hindi pantay, magmula DITO.
    	// Check if there are any user account 
    	if (numUsers == 1) {
    	
        	printf("\n\nNo Employees registered.\n");
        	
    	} else {
    		
        	printf("\nEmployee List:\n");
        	printf("=================================================================================================================================================\n");
        	printf("|ID\t|Name\t|Position\t|Basic Salary\t|Overtime\t|Bonus\t|Total Earnings\t|Total Deductions\n");
        	printf("=================================================================================================================================================\n");

        	// Loop through each user and display their details
        	for (i = 1; i < numUsers; i++) {
        		
            	// Calculate basic salary, overtime, and gross pay
            	float basic_salary = calculate_basic_salary(&users[i]);
            	float overtime = calculate_overtime(&users[i]);
            	float gross_pay = calculate_gross_pay(&users[i]);
            	float total_deduction = total_deductions(&users[i]);

            	// Print employee details along with computed values
            	printf("|%d\t|%s\t|%s\t|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%.2f\n", i, users[i].names, users[i].chosen_position.position_name, basic_salary, overtime, users[i].bonus, gross_pay, total_deduction);
            	
        	}
            printf("=================================================================================================================================================\n");
    	}
	// hanggang DITO!
	
	
        // Prompt for employee number to delete
        printf("\n\n\tEnter the number of the employee to delete (Enter 0 to cancel): ");
        int id;
        scanf("%d", &id);
        getchar(); // Consume the newline character left in the input buffer
        
        if(id == 0){
        	
        	printf("\n\tOperation Cancelled\n");
    		wait_clean();
    		return;
		}

        // Validate ID
        if (id >= 0 && id <= numUsers) {
        	
            // Check if the selected user is the admin
            if (strcmp(users[id].usernames, "admin") == 0) {
            	
                printf("\n\tYou cannot delete the admin account.\n");
            } else {
            	
                // Shift elements to remove the selected employee // Shifts the selected id number "i" to the last element of array
                for (i = id; i < numUsers - 1; i++) {
                	
                    users[i] = users[i + 1]; // Shifts the selected id number
                }
                
                numUsers--; // Decrement the number of users
                printf("\n\tEmployee deleted successfully.\n");
            }
        } else {
        	
            printf("\n\tInvalid employee ID.\n");
        }
    }

    wait_clean(); // Wait for keypress and clear console
}

// register's new employee "ONLY ADMIN CAN REGISTER"
void add_employee() {
	
    int i;
    char new_username[MAX_USER_LENGTH];
    char new_password[MAX_USER_LENGTH];
    char confirmation;
    
    clean();
    
    // Check if positions are available
    if (numPositions == 0) {
    	
        printf("\n\tNo positions are available. Please add a position first\n");
        wait_clean(); // Wait for keypress and clear console
        return;
    }
    
    // Check if maximum number of users reached
    if (numUsers >= MAX_USERS) {
    	
        printf("\n\t\tMaximum number of users reached.\n");
        wait_clean();
        return;
    }

    printf("\n\t\tRegister New Employee\n\n");
    
    User new_user;
    
    // Loop to get a valid username
    do {
        // Prompt for username
        printf("\tEnter Username: ");
        if (scanf("%s", new_username) != 1 || !is_valid_username(new_username)) {
        	
            printf("\n\tInvalid input. Username must not contain spaces. Please try again.\n");
            while (getchar() != '\n'); // Clear input buffer
            wait_clean();
            continue;
        }
        
        // Check if username already exists
        if (find_user(new_username) != NULL) {
        	
            printf("\n\tUsername already exists. Try again.\n");
            while (getchar() != '\n'); // Clear input buffer
            wait_clean(); // Wait for keypress and clear console
        } else {
        	
            strcpy(new_user.usernames, new_username); // Copy new_username to new_user.usernames
        }
        
    } while (find_user(new_username) != NULL);
    
    // Loop to get a valid password
    do {
    	
        // Prompt for password
        printf("\tEnter Password: ");
        if (scanf("%s", new_password) != 1 || !is_valid_password(new_password)) {
        	
            printf("\n\tInvalid input. Password must not contain spaces. Please try again.\n");
            while (getchar() != '\n'); // Clear input buffer
            wait_clean();
            continue;
        }
        
        strcpy(new_user.passwords, new_password);
        
    } while (!is_valid_password(new_password));
    
    // Clear the newline character left in the input buffer
    while (getchar() != '\n');
    
    // Prompt for name
    printf("\tEnter Name: ");
    if (scanf("%[^\n]s", new_user.names) != 1) {
    	
        printf("\n\tInvalid input. Please try again.\n");
        while (getchar() != '\n'); // Clear input buffer
        wait_clean();
        return;
    }
    
    // Loop to get a valid contact number
    do {
    	
        // Prompt for contact number
        printf("\tEnter Contact (up to 10 digits): ");
        if (scanf("%10s", new_user.contacts) != 1 || !is_valid_contact(new_user.contacts)) {
        	
            printf("\n\tInvalid input. Contact must be up to 10 digits and only contain numbers. Please try again.\n");
            while (getchar() != '\n'); // Clear input buffer
            wait_clean();
            continue;
        }
        
    } while (!is_valid_contact(new_user.contacts));
    
    printf("\n\n\t\tEmployee Salary Computation\n\n");
    
    // Display available positions and get a valid position choice
    int chosen_index;
    do {
    	
        chosen_index = 0;
        
        printf("\n\t\tAvailable Positions\n\n");
    
        for (i = 0; i < numPositions; i++) {
        	
            printf("\t\t[%d] %s\n", i + 1, positions[i].position_name);
        }
        
        // Prompt for position choice
        printf("\n\tChoose Position (Enter number): ");
        if (scanf("%d", &chosen_index) != 1) {
        	
            printf("\n\tInvalid input. Please enter a valid number.\n");
            while (getchar() != '\n'); // Clear input buffer
            wait_clean();
            continue;
        }
        
        // Validate the chosen position index
        if (chosen_index < 1 || chosen_index > numPositions) {
        	
            clean();
            printf("\n\tInvalid position choice. Please choose a valid position.\n");
        }
        
    } while (chosen_index < 1 || chosen_index > numPositions);
    
    // Assign chosen position (adjust to 0-based index)
    new_user.chosen_position = positions[chosen_index - 1];
    
    // Loop to get a valid number of hours worked
    do {
    	
        // Prompt for total number of hours worked
        printf("\tEnter Total number of hours worked (in a month, 1-170): ");
        if (scanf("%f", &new_user.work_hours) != 1 || new_user.work_hours < 1 || new_user.work_hours > 170) {
        	
            printf("\n\tInvalid input. Please enter a valid number of hours (1-170).\n");
            while (getchar() != '\n'); // Clear input buffer
            wait_clean();
            continue;
        }
        
    } while (new_user.work_hours < 1 || new_user.work_hours > 170);
    
    // Loop to get a valid number of overtime hours worked
    do {
        // Prompt for total number of overtime hours worked
        printf("\tEnter Total number of overtime hours worked (in a month, 1-80): ");
        if (scanf("%f", &new_user.overtime_hours) != 1 || new_user.overtime_hours < 1 || new_user.overtime_hours > 80) {
        	
            printf("\n\tInvalid input. Please enter a valid number of overtime hours (1-80).\n");
            while (getchar() != '\n'); // Clear input buffer
            wait_clean();
            continue;
        }
        
    } while (new_user.overtime_hours < 1 || new_user.overtime_hours > 80);
    
    // Prompt for total bonuses (one-time validation)
    do {
        printf("\tEnter Total Bonuses (in a month): ");
        if (scanf("%f", &new_user.bonus) != 1) {
        	
            printf("\n\tInvalid input. Please enter a valid bonus amount.\n");
            while (getchar() != '\n'); // Clear input buffer
            wait_clean();
            continue;
        }
        
    } while (0); // Loop is not needed, just validate once
    
    // Prompt for confirmation before saving the new employee
    printf("\n\tAre you sure you want to save this employee? (y/n): ");
    while (getchar() != '\n'); // Clear any leftover newline character
    confirmation = getchar();
    
    if (confirmation == 'y' || confirmation == 'Y') {
    	
        // Automatically set user type to employee
        new_user.userTypes = 0;
        
        // Add the new user to the users array and increment the user count
        users[numUsers] = new_user;
        numUsers++;
        
        printf("\tRegistration successful.\n");
    } else {
    	
        printf("\tRegistration cancelled.\n");
    }
    
    wait_clean();
}

// basic salary computation
float calculate_basic_salary(User* user){
	
	return user->work_hours * user->chosen_position.hourly_rates;
}

// overtime pay calculation
float calculate_overtime(User* user){
	
	return user->overtime_hours * user->chosen_position.overtime_rates;
}

// gross pay computation
float calculate_gross_pay(User* user){
	
	return calculate_basic_salary(user) + calculate_overtime(user) + user->bonus;
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
    
    // checks current password
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
	
	char new_username[MAX_USER_LENGTH];
	clean();
	
	do{
		
		printf("\n\tEnter new username: ");
    	scanf(" %s", new_username);
		
		// checks if username already exist
		if(find_user(new_username) != NULL){
			
			printf("\n\tUsername already exists. Try again.\n");
        	wait_clean(); // Wait for keypress and clear console
		}else{
			
			strcpy(user->usernames, new_username);
		}
		 
	}while (find_user(new_username) != NULL);
	
	//getchar(); // Consume the newline character left in the input buffer
    printf("\n\tUsername updated successfully.\n");
    
    wait_clean();
}

// for changing name
void change_name(User* user){
	
	clean();
	
	printf("\n\tEnter new name: ");
    scanf(" %[^\n]", user->names); // Use %[^\n] to read the entire line including spaces
    getchar(); // Consume the newline character left in the input buffer
    printf("\n\tName updated successfully.\n");
    
    wait_clean();
}

// for changing contact
void change_contact(User* user){
	
	clean();
	
	//getchar(); // Consume the newline character left in the input buffer
	printf("\n\tEnter new contact: ");
    scanf("%d", &user->contacts); 
    printf("\n\tContact updated successfully.\n");
    
    wait_clean();
}

// for adding employee position
void add_position(User* user){
	
	clean();
	
	// checks if the maximum number of positions has been reached
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
	
	printf("\n\t\tPosition Added Successfully");
	
	wait_clean();
}

// tax computation
float tax_computation(User* user){
	
	float gross_pay = calculate_gross_pay(user);
	float tax = 0.0;
	
	// The following are based on Tax table of 2022
	
	if (gross_pay < 0) {
		
        // Handle potential error if gross pay is negative
        return tax = 404; // Indicating an error 
        
    } else if (gross_pay >= 666667) {
    	
        tax = 200833.33 + ((gross_pay - 666667) * 0.35); // 200,833.33 + 35% tax rate
    } else if (gross_pay >= 166667) {
    	
        tax = 40833.33 + ((gross_pay - 166667) * 0.32); // 40,833.33 + 32% tax rate 
    } else if (gross_pay >= 66667) {
    	
        tax = 10833.33 + ((gross_pay - 66667) * 0.30); // 10,833.33 + 30% tax rate
    } else if (gross_pay >= 33333) {
    	
        tax = 2500 + ((gross_pay - 33333) * 0.25); // 2,500 + 25% tax rate
    } else if (gross_pay >= 20833) {
    	
        tax = (gross_pay - 20833) * 0.20; // 20% tax rate
    } else {
    	
        tax = 0.0; // No tax for gross pay below 20,833
    }
	
	return tax;
}

// SSS computation
float sss_computation(User* user){
	
	float gross_pay = calculate_gross_pay(user);
	float sss = 0.0;
	
	if (gross_pay < 0) {
		
		// Handle potential error if gross pay is negative
        return sss = 404; // Indicating an error 
	} else if (gross_pay >= 29750) {
		
		sss = 1350.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 29250) {
		
		sss = 1327.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 28750) {
		
		sss = 1305.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 28250) {
		
		sss = 1282.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 27750) {
		
		sss = 1260.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 27250) {
		
		sss = 1237.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 26750) {
		
		sss = 1215.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 26250) {
		
		sss = 1192.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 25750) {
		
		sss = 1170.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 25250) {
		
		sss = 1147.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 24750) {
		
		sss = 1125.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 24250) {
		
		sss = 1102.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 23750) {
		
		sss = 1080.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 23250) {
		
		sss = 1057.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 22750) {
		
		sss = 1035.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 22250) {
		
		sss = 1012.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 21750) {
		
		sss = 990.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 21250) {
		
		sss = 967.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 20750) {
		
		sss = 945.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 20250) {
		
		sss = 922.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 19750) {
		
		sss = 900.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 19250) {
		
		sss = 877.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 18750) {
		
		sss = 855.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 18250) {
		
		sss = 832.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 17750) {
		
		sss = 810.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 17250) {
		
		sss = 787.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 16750) {
		
		sss = 765.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 16250) {
		
		sss = 742.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 15750) {
		
		sss = 720.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 15250) {
		
		sss = 697.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 14750) {
		
		sss = 675.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 14250) {
		
		sss = 652.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 13750) {
		
		sss = 630.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 13250) {
		
		sss = 607.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 12750) {
		
		sss = 585.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 12250) {
		
		sss = 562.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 11750) {
		
		sss = 540.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 11250) {
		
		sss = 517.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 10750) {
		
		sss = 495.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 10250) {
		
		sss = 472.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 9750) {
		
		sss = 450.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 9250) {
		
		sss = 427.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 8750) {
		
		sss = 405.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 8250) {
		
		sss = 382.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 7750) {
		
		sss = 360.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 7250) {
		
		sss = 337.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 6750) {
		
		sss = 315.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 6250) {
		
		sss = 292.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 5750) {
		
		sss = 270.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 5250) {
		
		sss = 247.50; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 4750) {
		
		sss = 225.0; // based to Monthly SSS Contribution Table
	} else if (gross_pay >= 4250) {
		
		sss = 202.50; // based to Monthly SSS Contribution Table
	} else {
		
		sss = 180.0; // based to Monthly SSS Contribution Table
	}
	
	return sss;
}

// calculates Pagibig deductions
float pagibig_computation(User* user){
	
	float gross_pay = calculate_gross_pay(user);
	float pagibig = 0.0;
	
	if (gross_pay < 0) {
		
		// Handle potential error if gross pay is negative
        return pagibig = 404; // Indicating an error 
	} else if (gross_pay >= 10000) {
		
		pagibig = 200.0; // if gross pay is equal or over 10,000, P100.00 is the maximum deductions
	} else if (gross_pay >= 1500) {
		
		pagibig = gross_pay * 0.02; // 2% rate
	} else {
		
		pagibig = gross_pay * 0.01; // 1% rate
	}
	
	return pagibig;
}

// calculates Philhealth deductions
float philhealth_computation(User* user){
	
	float gross_pay = calculate_gross_pay(user);
	float philhealth = 0.0;
	
	if (gross_pay < 0) {
		
		// Handle potential error if gross pay is negative
        return philhealth = 404; // Indicating an error 
	} else {
		
		philhealth = (gross_pay * 0.05) / 2; // 5% rate based to 2024 philhealth contribution
	}
	
	return philhealth;
}

// calculates Total deductions
float total_deductions(User* user){
	
	return tax_computation(user) + sss_computation(user) + pagibig_computation(user) + philhealth_computation(user);
}

float netpay(User* user){
	
	return calculate_gross_pay(user) - total_deductions(user);
}

void change_employee_position() {
	
    int i;
    clean(); // Clear console
    
    // Checks if their are any employee registered
    if(numUsers == 1){
    	
    	printf("\n\n\tNo Employees registered.\n");
    	wait_clean();
    	return;
	}
	
	// Check if positions are available
	if (numPositions == 0){
		
		printf("\n\tNo positions are available. Please add a position first\n");
		wait_clean();	// Wait for keypress and clear console
		return;
	}

    printf(" ________________________________________________________\n");
    printf("|                                                        |\n");
    printf("|                Change Employee Position                |\n");
    printf("|                                                        |\n");
    printf("|________________________________________________________|\n");

    // Display employee list with IDs
    if (numUsers <= 1) { // Check if there are no employees registered
    
        printf("\n\nNo Employees registered.\n");
        wait_clean();
        return;
        
    } else {

        printf("\nEmployee List:\n");
        printf("=================================================================================================================================================\n");
        printf("|ID\t|Name\t\t\t|Position\t\t|Basic Salary\t|Overtime\t|Bonus\t|Total Earnings\t|Total Deductions\n");
        printf("=================================================================================================================================================\n");

        // Loop through each user and display their details
        for (i = 1; i < numUsers; i++) {
        	
            // Calculate basic salary, overtime, and gross pay
            float basic_salary = calculate_basic_salary(&users[i]);
            float overtime = calculate_overtime(&users[i]);
            float gross_pay = calculate_gross_pay(&users[i]);
            float total_deduction = total_deductions(&users[i]);

            // Print employee details along with computed values
            printf("|%d\t|%-20s|%-20s|%.2f\t\t|%.2f\t\t|%.2f\t|%.2f\t\t|%.2f\n", i, users[i].names, users[i].chosen_position.position_name, basic_salary, overtime, users[i].bonus, gross_pay, total_deduction);
        }
        printf("=================================================================================================================================================\n");

        // Prompt for employee ID to change position
        printf("\nEnter the ID of the employee to change position: ");
        int id;
        scanf("%d", &id);
        getchar(); // Consume the newline character left in the input buffer

        // Validate ID
        if (id > 0 && id < numUsers) {
        	
            // Display available positions
            int chosen_index;
            
            do {
            	
                printf("\nAvailable Positions:\n");
                for (i = 0; i < numPositions; i++) {
                	
                    printf("[%d] %s\n", i + 1, positions[i].position_name);
                }
                
                printf("Choose new position (Enter number): ");
                scanf("%d", &chosen_index);
                getchar(); // Consume the newline character left in the input buffer

                // Validate the chosen position index
                if (chosen_index < 1 || chosen_index > numPositions) {
                	
                    clean();
                    printf("\nInvalid position choice. Please choose a valid position.\n");
                }
                
            } while (chosen_index < 1 || chosen_index > numPositions);

            users[id].chosen_position = positions[chosen_index - 1]; // Assign chosen position

            printf("\nEmployee position updated successfully.\n");
        } else {
        	
            printf("\nInvalid employee ID.\n");
        }
    }

    wait_clean(); // Wait for keypress and clear console
}

int is_valid_username(char* username) {
	
    // Check if the username contains any spaces
    for (int i = 0; i < strlen(username); i++) {
    	
        if (isspace(username[i])) {
        	
            return 0;
        }
    }
    return 1;
}

int is_valid_password(char* password) {
	
    // Check if the password contains any spaces
    for (int i = 0; i < strlen(password); i++) {
    	
        if (isspace(password[i])) {
        	
            return 0;
        }
    }
    return 1;
}

// Function to check if the contact number is at most 10 digits and only contains digits
int is_valid_contact(char* contact) {
	
    int length = strlen(contact);
    if (length > 10) {
    	
        return 0;
    }
    for (int i = 0; i < length; i++) {
    	
        if (!isdigit(contact[i])) {
        	
            return 0;
        }
    }
    return 1;
}





