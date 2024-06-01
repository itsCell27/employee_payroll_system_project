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
#include <windows.h>
#include <time.h>


#define MAX_USERS 50             		// maximum number of users
#define MAX_USER_LENGTH 50		 		// maximum number of characters for usernames
#define MAX_PASSWORD_LENGTH 20   		// maximum number of characters for password
#define MAX_CHAR 100					// maximum number of characters for other char types
#define MAX_POSITION 50		 	 		// maximum number of positions
#define USERS "users.csv"  		 		// File name
#define POSITION "positions.csv" 		// File name
#define OTP_LENGTH 4

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
char adminName[] = "ADMIN";
char adminContact[] = "101";


void main_menu();                      // main-menu of employee payroll system

void create_file(const char *filename);														// Function to create the file
void writeUsersToCSV(const char *filename, User users[], int numUsers);						// for writing and saving users data to file
void readUsersFromCSV(const char *filename, User users[], int *numUsers);   				// for reading users file data
void writePositionsToCSV(const char *filename, Position positions[], int numPositions);		// for writing new position in file
void readPositionsFromCSV(const char *filename);											// Function to read positions in the file


User* find_user(const char *username); 			// Function to check if the username exists
void clean();                          			// clears console
void wait_clean();                     			// clears console after user press any key
void change_password(User* user);      			// changes user password
void change_username(User* user);      			// changes user username
void change_name(User* user);          			// changes user name
void change_contact(User* user);       			// changes user contact
void login_system();				   			// user login menu
int is_valid_username(char* username); 			// Check if the username contains any spaces 
int is_valid_password(char* password); 			// Check if the password contains any spaces
int is_valid_contact(char* contact);   			// Function to check if the contact number is at most 10 digits and only contains digits
void forgot_password();				   			// Function for password reset
void clear_input_buffer();			   			// Function to clear the input buffer
int get_password(char *password, size_t size);  // hides password

// employee menu
void user(User* user);                 // employee main-menu
void user_payslip(User* user);		   // displays salary payslip
void user_info_update(User* user);	   // displays & allows change of employee information

// admin menu
void admin(User* user);				   // admin main-menu
void admin_manage(User* user);		   // menu to manage employees
void edit_employee();				   // menu for editing anything about employee

void edit_salary();					   // for editing employee salary
void edit_all_salary();				   // for editing all employee salary details
void add_employee();				   // register's new employee
void delete_employee();                // for deleting a specific employee
void add_position();		   		   // for adding different employee positions
void change_employee_position();       // for changing employee position

void initialize_positions();		   // Function to initialize predefined positions

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


void enableVirtualTerminalProcessing();		// Enable virtual terminal processing for ANSI color support

int main() {
	
	// Enable virtual terminal processing for ANSI color support
    enableVirtualTerminalProcessing();
	
	// Ensure that files exist
    create_file(USERS);
    create_file(POSITION);
    
    // Read existing users and positions from CSV
    readUsersFromCSV(USERS, users, &numUsers);
    readPositionsFromCSV(POSITION);
    
	// Initialize positions if the positions array is empty
    initialize_positions();
    
    // Check if the admin acc already exists
    if (find_user(adminUsername) == NULL) {
    	
        // Add the admin user if it doesn't exist
        strcpy(users[numUsers].usernames, adminUsername);
        strcpy(users[numUsers].passwords, adminPassword);
        strcpy(users[numUsers].names, adminName);
        strcpy(users[numUsers].contacts, adminContact);
        users[numUsers].work_hours = 0;
        users[numUsers].overtime_hours = 0;
        users[numUsers].bonus = 0;
        users[numUsers].chosen_position = positions[0];
        users[numUsers].userTypes = 1; // set to admin
        numUsers++;

        // Write the updated users array to the users.csv file
        writeUsersToCSV(USERS, users, numUsers);
    }
    
    main_menu();
    
    // Before exiting, save the current state of users and positions back to the files
    writeUsersToCSV(USERS, users, numUsers);
    writePositionsToCSV(POSITION, positions, numPositions);
    
    return 0;
}


// Function for the main menu
void main_menu(){
	
	int choice;
	
	do{
		//design
		printf("\033[1;36m _ _ ______                 _                            _____                      _ _    _____           _                _ _  \033[0m\n");
    	printf("\033[1;36m( | |  ____|               | |                          |  __ \\                    | | |  / ____|         | |              ( | ) \033[0m\n");
    	printf("\033[1;36m V V| |__   _ __ ___  _ __ | | ___  _   _  ___  ___     | |__) __ _ _   _ _ __ ___ | | | | (___  _   _ ___| |_ ___ _ __ ___ V V  \033[0m\n");
    	printf("\033[1;36m    |  __| | '_ ` _ \\| '_ \\| |/ _ \\| | | |/ _ \\/ _ \\    |  ___/ _` | | | | '__/ _ \\| | |  \\___ \\| | | / __| __/ _ \\| '_ ` _ \\     \033[0m\n");
    	printf("\033[1;36m    | |____| | | | | | |_) | | (_) | |_| |  __|  __/    | |  | (_| | |_| | | | (_) | | |  ____) | |_| \\__ \\ ||  __| | | | | |    \033[0m\n");
    	printf("\033[1;36m    |______|_| |_| |_| .__/|_|\\___/ \\__, |\\___|\\___|    |_|   \\__,_|\\__, |_|  \\___/|_|_| |_____/ \\__, |___/\\__\\___|_| |_| |_|    \033[0m\n");
    	printf("\033[1;36m                     | |             __/ |                           __/ |                        __/ |                          \033[0m\n");
    	printf("\033[1;36m                     |_|            |___/                           |___/                        |___/                           \033[0m\n");
    	printf("\n");
    	printf("                                 ________________________________________________________\n");
    	printf("                                |                                                        |\n");
    	printf("                                |           Welcome to Employee Payroll System           |\n");
    	printf("                                |                                                        |\n");
    	printf("                                |________________________________________________________|\n");
    	printf("                                |                                                        |\n");
    	printf("                                |    [1] Login                                           |\n");
    	printf("                                |    [2] Forgot Password                                 |\n");
    	printf("                                |    [9] Exit                                            |\n");
    	printf("                                |                                                        |\n");
    	printf("                                |________________________________________________________|\n");
    	printf("\n");
    	printf("\033[1;36m                                Enter: \033[0m");
    
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

// Function to enable virtual terminal processing for ANSI color support
void enableVirtualTerminalProcessing() {
	
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (hOut == INVALID_HANDLE_VALUE) return;

    if (!GetConsoleMode(hOut, &dwMode)) return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

// Function to create the file
void create_file(const char *filename) {
	
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error creating file %s\n", filename);
        exit(1); // Exit the program if file creation fails
    }
    fclose(file);
}

// Function to write a new position to the CSV file
void writePositionsToCSV(const char *filename, Position positions[], int numPositions) {
	
	int i;
	
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Unable to open file for writing positions");
        return;
    }

    // Write the header
    fprintf(file, "position_name,hourly_rate,overtime_rate\n");

    // Write each position
    for (i = 0; i < numPositions; i++) {
        fprintf(file, "%s,%.2f,%.2f\n",
                positions[i].position_name,
                positions[i].hourly_rates,
                positions[i].overtime_rates);
    }

    fclose(file);
}


// Function to read positions in the file
void readPositionsFromCSV(const char *filename) {
	
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file for reading positions");
        return;
    }

    char line[256];
    numPositions = 0;

    // Skip the header
    if (fgets(line, sizeof(line), file)) {
        while (fgets(line, sizeof(line), file)) {
            if (numPositions >= MAX_POSITION) {
                printf("Max positions limit reached\n");
                break;
            }

            Position position;
            char *token = strtok(line, ",");
            if (token) strcpy(position.position_name, token);

            token = strtok(NULL, ",");
            if (token) position.hourly_rates = atof(token);

            token = strtok(NULL, ",");
            if (token) position.overtime_rates = atof(token);

            positions[numPositions++] = position;
        }
    }

    fclose(file);
}


// for writing and saving data to file
void writeUsersToCSV(const char *filename, User users[], int numUsers) {
	
	int i;
	
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("\n\tUnable to open file for writing");
        return;
    }

    // Write the header
    fprintf(file, "username,password,name,contact,work_hours,overtime_hours,bonus,userType,position_name,hourly_rate,overtime_rate\n");

    // Write each user
    for (i = 0; i < numUsers; i++) {
        fprintf(file, "%s,%s,%s,%s,%.2f,%.2f,%.2f,%d,%s,%.2f,%.2f\n",
                users[i].usernames,
                users[i].passwords,
                users[i].names,
                users[i].contacts,
                users[i].work_hours,
                users[i].overtime_hours,
                users[i].bonus,
                users[i].userTypes,
                users[i].chosen_position.position_name,
                users[i].chosen_position.hourly_rates,
                users[i].chosen_position.overtime_rates);
    }

    fclose(file);
}

// for reading file data
void readUsersFromCSV(const char *filename, User users[], int *numUsers) {
	
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file for reading");
        return;
    }

    char line[1024];
    int count = 0;

    // Skip the header
    if (fgets(line, sizeof(line), file)) {
        while (fgets(line, sizeof(line), file)) {
            if (count >= MAX_USERS) {
                printf("Max users limit reached\n");
                break;
            }

            User user;
            char *token = strtok(line, ",");
            if (token) strcpy(user.usernames, token);

            token = strtok(NULL, ",");
            if (token) strcpy(user.passwords, token);

            token = strtok(NULL, ",");
            if (token) strcpy(user.names, token);

            token = strtok(NULL, ",");
            if (token) strcpy(user.contacts, token);

            token = strtok(NULL, ",");
            if (token) user.work_hours = atof(token);

            token = strtok(NULL, ",");
            if (token) user.overtime_hours = atof(token);

            token = strtok(NULL, ",");
            if (token) user.bonus = atof(token);

            token = strtok(NULL, ",");
            if (token) user.userTypes = atoi(token);

            token = strtok(NULL, ",");
            if (token) strcpy(user.chosen_position.position_name, token);

            token = strtok(NULL, ",");
            if (token) user.chosen_position.hourly_rates = atof(token);

            token = strtok(NULL, ",");
            if (token) user.chosen_position.overtime_rates = atof(token);

            users[count++] = user;
        }
    }

    *numUsers = count;
    fclose(file);
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
    
    FILE *file;
    int value;
    
    clean();
    
    do{ 

    	printf("\n\t\tLogin\n\n");
    	printf("\033[1;36m \t\tEnter Username:\033[0m ");
    	scanf("%s", username);
    
    	// Load users from CSV file
	    User users[MAX_USERS];
	    readUsersFromCSV(USERS, users, &numUsers); // Read users from CSV
	        
        // Find the user in the loaded data
        User* index = find_user(username);	// checks if username exists

    	if (index != NULL) { 
    		
    		attempt = 0; // stops the loop if username exists
    		
    		do{
    			
    			printf("\033[1;36m \t\tEnter Password:\033[0m ");
    			get_password(password, sizeof(password)); // hides password
    			
    		
				if (strcmp(index->passwords, password) == 0) { // checks inputted password
				
					attempt_pass = 0; // stops the loop if password is correct
					
					if (index->userTypes == 1){ //checks if its an admin
					
						clean();

    					printf("\n\n\tAdmin login successful. Welcome, %s!\n\n", username);
    					wait_clean(); // Wait for keypress and clear console
        				admin(index);
        				
					} else { // if not, prompts to employee menu
					
						clean();
					
						printf("\n\n\tEmployee login successful. Welcome,\033[1;36m %s! \033[1;0m\n\n", username);
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
						
						printf("\033[1;31m \n\n\tWrong password! Please try again. [%d]\n\n", attempt_pass);
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
				
				printf("\033[1;31m\n\n\tUser does not exist. Please try again. [%d]\n\n", attempt);
			}
			
		} 
    	
	}while (attempt != 0);
    
    
}

// Function to generate a random OTP
void generateOTP(char *otp) {
	
	int i;
    srand(time(0));
    
    for (i = 0; i < OTP_LENGTH; i++) {
    	
        otp[i] = '0' + rand() % 10;
    }
    
    otp[OTP_LENGTH] = '\0';
}

// Function to simulate sending an OTP to the user's contact number
void sendOTP(const char *otp, const char *contactNumber) {
	
    printf("\n\tSending OTP \033[0;32m %s \033[0m to contact number \033[0;36m %s \033[0m \n", otp, contactNumber);
}

// Function to handle forgot password functionality
void forgot_password() {
	
    char contact[11];
    char generatedOTP[OTP_LENGTH + 1];
    char enteredOTP[OTP_LENGTH + 1];
    int userIndex = -1;
    int i;
    
    clean();
    
    // Read the users from CSV
    readUsersFromCSV(USERS, users, &numUsers);
    
    printf("\n ________________________________________________________\n");
    printf("|                                                        |\n");
    printf("|                     Forgot Password                    |\n");
    printf("|                                                        |\n");
    printf("|________________________________________________________|\n");

    printf("\n\tEnter your contact number: ");
    scanf("%s", contact);

    // Find the user by contact number
    for (i = 0; i < numUsers; i++) {
    	
        if (strcmp(users[i].contacts, contact) == 0) {
        	
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1) {
    	
        printf("\n\tContact number not found.\n");
        wait_clean();
        return;
    }

    // Generate and send OTP
    generateOTP(generatedOTP);
    sendOTP(generatedOTP, contact);

    // Prompt user to enter the received OTP
    printf("\n\tEnter the OTP sent to your contact number: ");
    scanf("%s", enteredOTP);

    // Verify the entered OTP
    if (strcmp(generatedOTP, enteredOTP) == 0) {
    	
        printf("\n\tOTP verified successfully!\n");
        change_password(&users[userIndex]);

        // Update the users.csv file after changing the password
        writeUsersToCSV(USERS, users, numUsers);
        wait_clean();
    } else {
    	
        printf("\n\tInvalid OTP. Please try again.\n");
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
    	printf("\033[1;36m\tEnter:\033[0m ");
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
		printf("\n******************************************************************\n");
    	printf("\033[1;36m                     	Salary Payslip                     \033[1;0m\n");
    	printf("******************************************************************\n");
    	printf("\n");
    	printf(" Personal Information:\n");
    	printf("\n");
    	printf("  Employee Name:		%s\n", user->names);
    	printf("  Position:			%s\n", user->chosen_position.position_name);
    	printf("  Contact:			%s\n", user->contacts);
    	printf("\n");
    	printf("------------------------------------------------------------------\n");
    	printf("\n");
    	printf("  Regular Hours Worked:		%.0f\n", user->work_hours);
    	printf("  Hourly Rate:			%.2f\n", user->chosen_position.hourly_rates);
    	printf("  Overtime Hours Worked:	%.0f\n", user->overtime_hours);
    	printf("  Overtime Rate:		%.2f\n", user->chosen_position.overtime_rates);
    	printf("\n");
    	printf("==================================================================\n");
    	printf("\n");
    	printf(" Earnings:\n");
    	printf("\n");
    	printf("  Basic Salary:			%.2f\n", basic_salary);
    	printf("  Overtime:			%.2f\n", overtime);
    	printf("  Bonus:			%.2f\n", user->bonus);
    	printf("  Total Earnings:		%.2f\n", user_gross_pay);
    	printf("\n");
    	printf(" Deductions:\n");
    	printf("\n");
    	printf("  Tax:				%.2f\n", tax);
    	printf("  SSS:				%.2f\n", sss);
    	printf("  Pagibig:			%.2f\n", pagibig);
    	printf("  Philhealth:			%.2f\n", philhealth);
    	printf("  Total Deductions:		%.2f\n", total_deduction);
    	printf("\n");
    	printf("  Net Pay:			%.2f\n", netpays);
    	printf("\n");
    	printf("******************************************************************\n");
    	printf("     [9] Back\n");
    	printf("******************************************************************\n");
    	printf("\033[1;36m\tEnter: \033[1;0m");
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
    	printf("|\tContact: %s                                           \n", user->contacts);
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
    	printf("\033[1;36m\tEnter: \033[1;0m");
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
    	printf("|    [3] Change Contact                                  |\n");
    	printf("|    [9] Logout                                          |\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	printf("\033[1;36m\tEnter: \033[1;0m");
    	scanf("%d", &choice);
    
    	switch (choice){
    	
    		case 1:
    			admin_manage(user);
    			break;
    			
    		case 2:
    			change_password(user);
    			break;
    		
    		case 3:
    			change_contact(user);
    			break;
    			
    		case 9:
    			clean();
    			break;
    			
    		default:
    			clean();
    			printf("\033[1;31m\n\t\t\tnot in option\033[1;0m\n");
    			while (getchar() != '\n');           // Clear the input buffer (consume remaining characters including newline)
    			wait_clean();						 // Wait for keypress and clear console
    			break;
    			
		}
		
	}while (choice != 9);
	
}

void admin_manage(User* user){
	
	int i, choice;
	
	clean();
	
	// Read users from CSV before displaying
    readUsersFromCSV(USERS, users, &numUsers);
	
	do{
		// Paayos ng display neto hindi pantay, magmula DITO.
		//design
		printf("\n ________________________________________________________\n");
    	printf("|                                                        |\n");
    	printf("\033[1;36m|                   Manage Employees                     |\033[1;0m\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	
    	// Check if there are any user account 
    	if (numUsers == 1) {
    	
        	printf("\033[1;31m\n\n\tNo Employees registered.\033[1;0m\n");
        	
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
    	printf("|    [2] Delete employee                                 |\n");
    	printf("|    [3] Edit employee                                   |\n");
    	printf("|    [9] Back                                            |\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	// hanggang DITO!
    	
    	printf("\033[1;36m\tEnter: \033[1;0m");
    	scanf("%d", &choice);
    
    	switch (choice){
    	
    		case 1:
    			add_employee();
    			break;
    			
    		case 2:
    			delete_employee();
    			break;
    			
    		case 3:
    			edit_employee();
    			break;
    			
    		case 9:
    			clean();
    			break;
    			
    		default:
    			clean();
    			printf("\033[1;31m\n\t\t\tnot in option\n\033[1;0m");
    			while (getchar() != '\n');           // Clear the input buffer (consume remaining characters including newline)
    			wait_clean();						 // Wait for keypress and clear console
    			break;
    			
		}
		
	}while (choice != 9);
	
}

// menu for editing anything about employee
void edit_employee(){
	
	int i, choice;
	
	// Read users from CSV before displaying
    readUsersFromCSV(USERS, users, &numUsers);
	
	clean();
	
	if(numUsers == 1){
    	
    	printf("\033[1;31m\n\n\tNo Employees registered.\033[1;0m\n");
    	wait_clean();
    	return;
	}
	
	do{
		// Paayos ng display neto hindi pantay, magmula DITO.
		//design
		printf("\n ________________________________________________________\n");
    	printf("|                                                        |\n");
    	printf("|                    Edit Employee                       |\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	
    	// Check if there are any user account 
    	if (numUsers == 1) {
    	
        	printf("\033[1;31m\n\n\tNo Employees registered.\033[1;0m\n");
        	
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
    	printf("|    [1] Edit specific salary details                    |\n");
    	printf("|    [2] Edit all salary details                    	 |\n");
    	printf("|    [3] Add new position			                     |\n");
    	printf("|    [4] Change employee position                        |\n");
    	printf("|    [9] Back                                            |\n");
    	printf("|                                                        |\n");
    	printf("|________________________________________________________|\n");
    	// hanggang DITO!
    	
    	printf("\033[1;36m\tEnter: \033[1;0m");
    	scanf("%d", &choice);
    
    	switch (choice){
    	
    		case 1:
    			edit_salary();
    			break;
    			
    		case 2:
    			edit_all_salary();
    			break;
    			
    		case 3:
    			add_position();
    			break;
    			
    		case 4:
    			change_employee_position();
    			break;
    			
    		case 9:
    			clean();
    			break;
    			
    		default:
    			clean();
    			printf("\033[1;31m\n\t\t\tnot in option\n\033[1;0m");
    			while (getchar() != '\n');           // Clear the input buffer (consume remaining characters including newline)
    			wait_clean();						 // Wait for keypress and clear console
    			break;
    			
		}
		
	}while (choice != 9);
}

// for editing specific employee salary
void edit_salary() {
    int i;
    int id;
    int choice;
    float new_value;

    // Read users from CSV before displaying 
    readUsersFromCSV(USERS, users, &numUsers);

    do {
        clean();

        if (numUsers == 1) {
            printf("\033[1;31m\n\n\tNo Employees registered.\033[1;0m\n");
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
        printf("\n\033[1;36mEnter the ID of the employee whose details you want to change: \033[1;0m");
        scanf("%d", &id);

        // Validate ID
        if (id < 1 || id >= numUsers) {  // Adjusted to start ID from 1 and ensure it's within the valid range
            printf("\033[1;31m\nInvalid employee ID.\n\033[1;0m");
            wait_clean();
            return;
        }

    } while (id < 1 || id >= numUsers);

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

    printf("\033[1;36m\n\tEnter your choice: \033[1;0m");
    scanf("%d", &choice);

    // Validate choice and update the corresponding detail
    switch (choice) {
        case 1:
            // Loop to get a valid number of hours worked
            do {
                // Prompt for total number of hours worked
                printf("\033[1;36m\tEnter Total number of hours worked (in a month, 1-170): \033[1;0m");
                if (scanf("%f", &new_value) != 1 || new_value < 1 || new_value > 170) {
                    printf("\033[1;36m\n\tInvalid input. Please enter a valid number of hours (1-170).\033[1;0m\n");
                    while (getchar() != '\n'); // Clear input buffer
                    wait_clean();
                    continue;
                }
            } while (new_value < 1 || new_value > 170);
            users[id].work_hours = new_value;
            printf("\nWork Hours updated successfully for employee '%s'.\n", users[id].usernames);
            break;

        case 2:
            // Loop to get a valid number of overtime hours worked
            do {
                // Prompt for total number of overtime hours worked
                printf("\033[1;36m\tEnter Total number of overtime hours worked (in a month, 1-80): \033[1;0m");
                if (scanf("%f", &new_value) != 1 || new_value < 1 || new_value > 80) {
                    printf("\033[1;31m\n\tInvalid input. Please enter a valid number of overtime hours (1-80).\033[1;0m\n");
                    while (getchar() != '\n'); // Clear input buffer
                    wait_clean();
                    continue;
                }
            } while (new_value < 1 || new_value > 80);
            users[id].overtime_hours = new_value;
            printf("\nOvertime Hours updated successfully for employee '%s'.\n", users[id].usernames);
            break;

        case 3:
            printf("\033[1;36m\nEnter new Bonus:\033[1;0m ");
            scanf("%f", &new_value);
            users[id].bonus = new_value;
            printf("\nBonus updated successfully for employee '%s'.\n", users[id].usernames);
            break;

        case 9:
            printf("\033[1;31m\nOperation Cancelled\033[1;0m\n");
            wait_clean();
            return;

        default:
            clean();
            printf("\033[1;31m\n\t\t\tnot in option\033[1;0m\n");
            while (getchar() != '\n'); // Clear the input buffer (consume remaining characters including newline)
            wait_clean(); // Wait for keypress and clear console
            return;
    }

    // Write updated user data to CSV
    writeUsersToCSV(USERS, users, numUsers);
    printf("\nChanges saved successfully.\n");
    wait_clean();
}

// for editing all employee salary details
void edit_all_salary() {
	
    int id, i;

    // Read users from CSV before displaying 
    readUsersFromCSV(USERS, users, &numUsers);

    do {
        clean();

        if (numUsers == 1) {
            printf("\033[1;31m\n\n\tNo Employees registered.\033[1;0m\n");
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
        printf("\033[1;36m\nEnter the ID of the employee whose details you want to change:\033[1;0m ");
        scanf("%d", &id);

        // Validate ID
        if (id < 1 || id >= numUsers) {  // Adjusted to start ID from 1 and ensure it's within the valid range
            printf("\033[1;31m\nInvalid employee ID.\033[1;0m\n");
            wait_clean();
            return;
        }

        printf("\n\n\t\tEmployee Salary Computation\n\n");
    
        // Loop to get a valid number of hours worked
        do {
            // Prompt for total number of hours worked
            printf("\033[1;36m\tEnter Total number of hours worked (in a month, 1-170):\033[1;0m ");
            if (scanf("%f", &users[id].work_hours) != 1 || users[id].work_hours < 1 || users[id].work_hours > 170) {
                printf("\033[1;31m\n\tInvalid input. Please enter a valid number of hours (1-170).\033[1;0m\n");
                while (getchar() != '\n'); // Clear input buffer
                wait_clean();
                continue;
            }
        } while (users[id].work_hours < 1 || users[id].work_hours > 170);
        
        // Loop to get a valid number of overtime hours worked
        do {
            // Prompt for total number of overtime hours worked
            printf("\033[1;36m\tEnter Total number of overtime hours worked (in a month, 1-80): \033[1;0m");
            if (scanf("%f", &users[id].overtime_hours) != 1 || users[id].overtime_hours < 1 || users[id].overtime_hours > 80) {
                printf("\033[1;31m\n\tInvalid input. Please enter a valid number of overtime hours (1-80).\033[1;0m\n");
                while (getchar() != '\n'); // Clear input buffer
                wait_clean();
                continue;
            }
        } while (users[id].overtime_hours < 1 || users[id].overtime_hours > 80);
        
        // Prompt for total bonuses (one-time validation)
        do {
            printf("\033[1;36m\tEnter Total Bonuses (in a month): \033[1;0m");
            if (scanf("%f", &users[id].bonus) != 1) {
                printf("\033[1;31m\n\tInvalid input. Please enter a valid bonus amount.\033[1;0m\n");
                while (getchar() != '\n'); // Clear input buffer
                wait_clean();
                continue;
            }
        } while (0); // Loop is not needed, just validate once

    } while (id < 1 || id >= numUsers);

    // Write updated user data to CSV
    writeUsersToCSV(USERS, users, numUsers);
    printf("\nChanges saved successfully.\n");
    wait_clean();
}


// for deleting a specific employee
void delete_employee() {
    int i;
    clean(); // Clear console

    // Read users from CSV before displaying
    readUsersFromCSV(USERS, users, &numUsers);

    if(numUsers == 1){
        printf("\n\n\tNo Employees registered.\n");
        wait_clean();
        return;
    }

    printf(" ________________________________________________________\n");
    printf("|                                                        |\n");
    printf("|                   Delete Employee                      |\n");
    printf("|                                                        |\n");
    printf("|________________________________________________________|\n");

    // Display employee list with IDs
    if (numUsers == 1) {
        printf("\033[1;31m\n\n\tNo Employees registered.\033[1;0m\n");
    } else {
        // Display employee list
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

        // Prompt for employee number to delete
        printf("\033[1;36m\n\n\tEnter the number of the employee to delete (Enter 0 to cancel):\033[1;0m ");
        int id;
        scanf("%d", &id);
        getchar(); // Consume the newline character left in the input buffer

        if(id == 0){
            printf("\033[1;31m\n\tOperation Cancelled\n\033[1;0m");
            wait_clean();
            return;
        }

        // Validate ID
        if (id >= 0 && id < numUsers) {
            // Check if the selected user is the admin
            if (strcmp(users[id].usernames, "admin") == 0) {
                printf("\033[1;31m\n\tYou cannot delete the admin account.\033[1;0m\n");
            } else {
                // Shift elements to remove the selected employee
                for (i = id; i < numUsers - 1; i++) {
                    users[i] = users[i + 1];
                }

                numUsers--; // Decrement the number of users
                printf("\n\tEmployee deleted successfully.\n");

                // Write updated user data to CSV
                writeUsersToCSV(USERS, users, numUsers);
                printf("\nChanges saved successfully.\n");
            }
        } else {
            printf("\033[1;31m\n\tInvalid employee ID.\033[1;0m\n");
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
    
    // Read existing users from CSV
    readUsersFromCSV(USERS, users, &numUsers);
    
    // read the positions from the file to display it
    readPositionsFromCSV(POSITION);
    
    // Check if positions are available
    if (numPositions == 0) {
    	
        printf("\033[1;31m\n\tNo positions are available. Please add a position first\033[1;0m\n");
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
        printf("\033[1;36m\tEnter Username:\033[1;0m ");
        if (scanf("%s", new_username) != 1 || !is_valid_username(new_username)) {
        	
            printf("\033[1;31m\n\tInvalid input. Username must not contain spaces. Please try again.\033[1;0m\n");
            while (getchar() != '\n'); // Clear input buffer
            wait_clean();
            continue;
        }
        
        // Check if username already exists
        if (find_user(new_username) != NULL) {
        	
            printf("\033[1;31m\n\tUsername already exists. Try again.\033[1;0m\n");
            while (getchar() != '\n'); // Clear input buffer
            wait_clean(); // Wait for keypress and clear console
        } else {
        	
            strcpy(new_user.usernames, new_username); // Copy new_username to new_user.usernames
        }
        
    } while (find_user(new_username) != NULL);
    
    // Loop to get a valid password
    do {
    	
        // Prompt for password
        printf("\033[1;36m\tEnter Password:\033[1;0m ");
        if (scanf("%s", new_password) != 1 || !is_valid_password(new_password)) {
        	
            printf("\033[1;31m\n\tInvalid input. Password must not contain spaces. Please try again.\033[1;0m\n");
            while (getchar() != '\n'); // Clear input buffer
            wait_clean();
            continue;
        }
        
        strcpy(new_user.passwords, new_password);
        
    } while (!is_valid_password(new_password));
    
    // Clear the newline character left in the input buffer
    while (getchar() != '\n');
    
    // Prompt for name
    printf("\033[1;36m\tEnter Name: \033[1;0m");
    if (scanf("%[^\n]s", new_user.names) != 1) {
    	
        printf("\033[1;31m\n\tInvalid input. Please try again.\033[1;0m\n");
        while (getchar() != '\n'); // Clear input buffer
        wait_clean();
        return;
    }
    
    // Loop to get a valid contact number
    do {
    	
        // Prompt for contact number
        printf("\033[1;36m\tEnter Contact (up to 10 digits):\033[1;0m ");
        if (scanf("%10s", new_user.contacts) != 1 || !is_valid_contact(new_user.contacts)) {
        	
            printf("\033[1;31m\n\tInvalid input. Contact must be up to 10 digits and only contain numbers. Please try again.\033[1;0m\n");
            while (getchar() != '\n'); // Clear input buffer
            wait_clean();
            continue;
        }
        
    } while (!is_valid_contact(new_user.contacts));
    
    // Display available positions and get a valid position choice
    int chosen_index;
    do {
    	
        chosen_index = 0;
        
        printf("\n\t\tAvailable Positions\n\n");
    
        for (i = 0; i < numPositions; i++) {
        	
            printf("\t\t[%d] %s\n", i + 1, positions[i].position_name);
        }
        
        // Prompt for position choice
        printf("\033[1;36m\n\tChoose Position (Enter number): \033[1;0m");
        if (scanf("%d", &chosen_index) != 1) {
        	
            printf("\033[1;31m\n\tInvalid input. Please enter a valid number.\033[1;0m\n");
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
    
   
    
    // Prompt for confirmation before saving the new employee
    printf("\033[1;36m\n\tAre you sure you want to save this employee? (y/n): \033[1;0m");
    while (getchar() != '\n'); // Clear any leftover newline character
    confirmation = getchar();
    
    if (confirmation == 'y' || confirmation == 'Y') {
    	
    	// Automatically set employee salary
    	new_user.work_hours = 0.0;
    	new_user.overtime_hours = 0.0;
    	new_user.bonus = 0.0;
    	
        // Automatically set user type to employee
        new_user.userTypes = 0;
        
        // Add the new user to the users array and increment the user count
        users[numUsers] = new_user;
        numUsers++;
        
        printf("\033[1;33m\tRegistration successful.\033[1;0m\n");
        
        // Save the updated users array to CSV
        writeUsersToCSV(USERS, users, numUsers);
    } else {
    	
        printf("\033[1;31m\tRegistration cancelled.\033[1;0m\n");
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

// Function to change a user's password
void change_password(User* user) {
	
    char newPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your new password: ");
    scanf("%s", newPassword);

    // Check if the new password is the same as the current password
    if (strcmp(newPassword, user->passwords) == 0) {
    	
        printf("\n\tNew password is the same as the current password. Password not updated.\n");
        wait_clean();
        return;
    }

    // Validate the new password (ensure it doesn't contain spaces)
    if (!is_valid_password(newPassword)) {
    	
        printf("\n\tPassword is invalid. Please make sure it doesn't contain spaces.\n");
        wait_clean();
        return;
    }

    // Update the password
    strcpy(user->passwords, newPassword);
    printf("\n\tPassword has been successfully reset.\n");
    wait_clean();
}


void change_username(User* user) {
	
    char new_username[MAX_USER_LENGTH];
    clean();
    int username_changed = 0; // Flag to indicate if the username has been changed

    do {
        printf("\n\tEnter new username: ");
        scanf(" %s", new_username);

        // Check if username already exists
        if (find_user(new_username) != NULL) {
            printf("\n\tUsername already exists. Try again.\n");
            wait_clean(); // Wait for keypress and clear console
        } else {
            // Update username
            strcpy(user->usernames, new_username);
            username_changed = 1; // Set flag to indicate the username was changed
        }

    } while (!username_changed);

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
    scanf("%s", user->contacts); 
    printf("\n\tContact updated successfully.\n");
    
    wait_clean();
}

// Function to initialize predefined positions
void initialize_positions() {
	
    // Read existing positions from CSV
    readPositionsFromCSV(POSITION);

    // Check if any positions already exist, if so, return
    if (numPositions > 0) {
        return;
    }

    // Add predefined positions
    strcpy(positions[numPositions].position_name, "Manager");
    positions[numPositions].hourly_rates = 50.0;
    positions[numPositions].overtime_rates = 75.0;
    numPositions++;

    strcpy(positions[numPositions].position_name, "Developer");
    positions[numPositions].hourly_rates = 40.0;
    positions[numPositions].overtime_rates = 60.0;
    numPositions++;

    strcpy(positions[numPositions].position_name, "Designer");
    positions[numPositions].hourly_rates = 35.0;
    positions[numPositions].overtime_rates = 50.0;
    numPositions++;

    // Add more predefined positions as needed

    // Write the initialized positions to CSV
    writePositionsToCSV(POSITION, positions, numPositions);
}

// for adding employee position
void add_position(){
	
	clean();
	
	// Read existing positions from CSV
    readPositionsFromCSV(POSITION);
	
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
	
	// Write the updated positions to CSV
    writePositionsToCSV(POSITION, positions, numPositions);
	
	printf("\n\t\tPosition Added Successfully");
	
	wait_clean();
}

// tax computation
float tax_computation(User* user){
	
	float gross_pay = calculate_gross_pay(user);
	float tax = 0.0;
	
	if (gross_pay == 0) {
		
		return 0.0;
	}
	
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
	
	if (gross_pay == 0) {
		
		return 0.0;
	}
	
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
	
	if (gross_pay == 0) {
		
		return 0.0;
	}
	
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
	
	if (gross_pay == 0) {
		
		return 0.0;
	}
	
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
    
    // Read users from CSV before displaying
    readUsersFromCSV(USERS, users, &numUsers);
    
    // Read the positions from the file to display it
    readPositionsFromCSV(POSITION);
    
    // Check if there are any employees registered
    if (numUsers == 1) {
        printf("\n\n\tNo Employees registered.\n");
        wait_clean();
        return;
    }
    
    // Check if positions are available
    if (numPositions == 0) {
        printf("\n\tNo positions are available. Please add a position first\n");
        wait_clean(); // Wait for keypress and clear console
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

            // Write updated user data to CSV
            writeUsersToCSV(USERS, users, numUsers);
            printf("\nChanges saved successfully.\n");
        } else {
            printf("\nInvalid employee ID.\n");
        }
    }

    wait_clean(); // Wait for keypress and clear console
}


int is_valid_username(char* username) {
	
	int i;
    // Check if the username contains any spaces
    for (i = 0; i < strlen(username); i++) {
    	
        if (isspace(username[i])) {
        	
            return 0;
        }
    }
    return 1;
}

int is_valid_password(char* password) {
	
	int  i;
    // Check if the password contains any spaces
    for (i = 0; i < strlen(password); i++) {
    	
        if (isspace(password[i])) {
        	
            return 0;
        }
    }
    return 1;
}

// Function to check if the contact number is at most 10 digits and only contains digits
int is_valid_contact(char* contact) {
	
	int i;
    int length = strlen(contact);
    if (length > 10) {
    	
        return 0;
    }
    for (i = 0; i < length; i++) {
    	
        if (!isdigit(contact[i])) {
        	
            return 0;
        }
    }
    return 1;
}

// Function to clear the input buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// hides password
int get_password(char *password, size_t size) {
	
	int i = 0;
	char ch;

	while(1) {
		
		ch = _getch();
		if (ch == '\r') {
			
			break;
		} else if (ch == '\b') {
			
			if (i > 0) {
				
				printf("\b \b");
				i--;
			}
		} else if(i < size - 1) {
			
			password[i++] = ch;
			printf("*");
		}	
	}
	password[i] = '\0';
	printf("\n");
}

 

