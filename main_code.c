#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

void main_menu();
void user();
void user_payslip();
void user_info_update();
void admin();
void admin_manage();
void check_attempts();

void main(){
	
	int option = 0;
	
	main_menu();
}

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
    	printf("*    [1] Employee Login                                  *\n");
    	printf("*    [2] Admin Login                                     *\n");
    	printf("*    [0] Exit                                            *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("\tEnter: ");
    	scanf("%d", &choice);
    
    	switch (choice){
    	
    		case 1:
    			user();
    			break;
    		case 2:
    			admin();
    			break;
    		case 0:
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 0);
	
}

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
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 0);
	
}

void user_payslip(){
	
	int choice;
	
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
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 0);
	
}

void user_info_update(){
	
	int choice;
	
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
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 0);
	
}

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
    			printf("\nN/a\n");
    			break;
    		case 2:
    			printf("\nN/a\n");
    			break;
    		case 0:
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 0);
	
}

void admin_manage(){
	
	int choice;
	
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
    			printf("\nN/a\n");
    			break;
    		case 0:
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 0);
	
}

void check_attempts(){
	
	printf("\t\t\tN/a");
}
