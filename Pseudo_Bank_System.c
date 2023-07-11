#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *fp;
FILE *fp1;
FILE *fe;
FILE *fe1;
FILE *fm1;

int ecode[1000], len_ecode = 0;
int pcode[1000], len_pcode = 0;
int amount[1000], len_amount = 0;

struct Person{
	char name[20];
	char lastname[20];
	int nationalcode;
	int primarykey;
};

struct Employee{
	int employeekey;
	char position[20];
};

//sign up as customer
void Add_Account_customer(){
	struct Person ps;

	printf("Please enter your name : \n");
	scanf("%s", &ps.name);

	printf("Please enter your last name : \n");
	scanf("%s", &ps.lastname);

	printf("Please enter your national code : \n");
	scanf("%d", &ps.nationalcode);

	pcode[len_pcode++] = ps.nationalcode;
	ps.primarykey = ((ps.nationalcode%100)*10000)+11;
	
	fprintf(fp1, "%s - %s - %d - %d\n", ps.name, ps.lastname, ps.nationalcode, ps.primarykey);

	fseek(fp, 0, SEEK_END);
	fwrite(&ps, sizeof(struct Person), 1, fp);
}

//sign up as employee
void Add_Account_employee(){
	struct Person ps;
	struct Employee es;

	printf("Please enter your name : \n");
	scanf("%s", &ps.name);

	printf("Please enter your last name : \n");
	scanf("%s", &ps.lastname);

	printf("Please enter your national code : \n");
	scanf("%d", &ps.nationalcode);

	ps.primarykey = ((ps.nationalcode%100)*10000)+22;

	fprintf(fp1, "%s - %s - %d - %d\n", ps.name, ps.lastname, ps.nationalcode, ps.primarykey);

	fseek(fp, 0, SEEK_END);
	fwrite(&ps, sizeof(struct Person), 1, fp);

	printf("What is your EmployeeCode?\n");
	scanf("%d", &es.employeekey);

	ecode[len_ecode++] = es.employeekey;

	printf("What is your position?\n");
	scanf("%s", &es.position);

	fprintf(fe1, "%d - %d - %s\n", ps.primarykey, es.employeekey, es.position);

	fseek(fe, 0, SEEK_END);
	fwrite(&es, sizeof(struct Person), 1, fe);
}


//login as customer
void Login_customer(){
	int flag = 0;

	printf("Please enter your Password(national code) : \n");

	int vor;

	scanf("%d", &vor);

	for(int i=0;i<=len_pcode;i++){
		if(pcode[i] == vor){
			printf("Hi %d, You are entered\n", vor);
			flag = 1;

			break;
		}else{
			printf("Your password is incorrect, Please try again\n");
		}
	}
	while(flag){
		printf("Please choose what do you want to do : \n");
		printf("0 : Log out\n");
		printf("1 : Deposit Money\n");
		printf("2 : Withdraw Money\n");
		printf("3 : Loan Money\n");

		int v, nc, ac;
		int a, b, c, hm;
		int l, am, dam;

		scanf("%d", &v);

		switch(v){
		case 0:
			return;
		case 1:
			printf("Please enter your national code : \n");
			scanf("%d", &a);

			printf("Please enter the other persons national code : \n");
			scanf("%d", &b);

			printf("How much do you want to deposit?\n");
			scanf("%d", &c);

			for(int i=0;i<=len_amount;i++){
				if(amount[i] == a){
					amount[i+1] -= c;
					hm = amount[i+1];
				}
			}

			for(int i=0;i<=len_amount;i++){
				if(amount[i] == b){
					amount[i+1] += c;
				}
			}

			fprintf(fm1, "1/23/2022 : \n");
			fprintf(fm1, "%d is moved from %d to %d and %d is still remaining in account\n", c, a, b, hm);

			break;

		case 2:
			printf("Please enter your national code : \n");
			scanf("%d", &a);

			printf("How much do you want to take?\n");
			scanf("%d", &b);

			for(int i=0;i<=len_amount;i++){
				if(amount[i] == a){
					amount[i+1] -= b;
					hm = amount[i+1];
				}
			}

			fprintf(fm1, "1/23/2022 : \n");
			fprintf(fm1, "%d  money is taken from %d and %d is still remaining in account\n", b, a, hm);

			break;
		
		case 3:
		    printf("please enter your nationalcode : \n");
			scanf("%d", &l);

			printf("How much money do you want to get?!\n");
			scanf("%d", &am);

			for(int i=0;i<=len_amount;i++){
				if(amount[i] == l && amount[i+1] >= am/2){

					printf("You can have the loan\n");
					printf("Are you sure ?\n0 : N0\n1 : YES\n");
					scanf("%d", &dam);
					
					if(dam == 1){

						fprintf(fm1, "1/23/2022 : \n");
			            fprintf(fm1, "%d has %d $ and wants to loan %d $\n", l, amount[i+1], am);

						amount[i+1] += am;

						fprintf(fm1, "%d has %d $ now and has to give it back up until 1/23/2023\n", l, amount[i+1]);

					}
					if(dam == 0){

						return;

					}

				}else if(amount[i] == l && amount[i+1] <= am/2){
					printf("Sorry, you have not met the requierments to have loan!\n");
					printf("Please enter 1 to continue : \n");
					scanf("%d", &dam);
					
					return;
				}
			}

		    break;
	    }
	}
}


//login as employee
void Login_employee(){

	int flag = 0;

	printf("Please enter your Password(EmployeeCode) : \n");

	int vor;

	scanf("%d", &vor);
	
	for(int i=0;i<=len_ecode;i++){
		if(ecode[i] == vor){
			printf("Hi %d, You are entered\n", vor);
			flag = 1;
			
			break;
		}else{
			printf("Your password is incorrect, Please try again\n");
		}
	}

	while(flag){
		printf("Please choose what do you want to do : \n");
		printf("0 : Log out\n");
		printf("1 : Open an Account\n");
		printf("2 : Find and Account\n");
		printf("3 : Deposit Money\n");
		printf("4 : Withdraw Money\n");

		int v, nc, ac;
		int a, b, c, hm;

		scanf("%d", &v);

		switch(v){

		case 0:
			return;

		case 1:
			Add_Account_customer();

			printf("Please reenter your national code : \n");
			scanf("%d", &nc);

			amount[len_amount++] = nc;

			printf("Please enter how much money do you want to put in your account : \n");
			scanf("%d", &ac);

			amount[len_amount++] = ac;

			fprintf(fm1, "1/23/2022 : \n");
			fprintf(fm1, "%d is form %d is remaining in account\n", ac, nc);

			break;

		case 2:
			printf("The TextFile containing name, lastname, nationalcode and personkey is now available to use.\n");

			break;
		
		case 3:
			printf("Please enter your national code : \n");
			scanf("%d", &a);

			printf("Please enter the other persons national code : \n");
			scanf("%d", &b);

			printf("How much do you want to deposit?\n");
			scanf("%d", &c);

			for(int i=0;i<=len_amount;i++){
				if(amount[i] == a){
					amount[i+1] -= c;
					hm = amount[i+1];
				}
			}

			for(int i=0;i<=len_amount;i++){
				if(amount[i] == b){
					amount[i+1] += c;
				}
			}

			fprintf(fm1, "1/23/2022 : \n");
			fprintf(fm1, "%d is moved from %d to %d and %d is still remaining in account\n", c, a, b, hm);

			break;

		case 4:
			printf("Please enter your national code : \n");
			scanf("%d", &a);

			printf("How much do you want to take?\n");
			scanf("%d", &b);

			for(int i=0;i<=len_amount;i++){
				if(amount[i] == a){
					amount[i+1] -= b;
					hm = amount[i+1];
				}
			}

			fprintf(fm1, "1/23/2022 : \n");
			fprintf(fm1, "%d  money is taken from %d and %d is still remaining in account\n", b, a, hm);

			break;
	    }
	}
}

//options available for bank employees
int menu(){

	//system("cls");

	printf("Please choose what do you want to do :\n");
	printf("0 : Exit\n");
	printf("1 : Add a new account as an customer\n");
	printf("2 : Add a new account as an employee\n");
	printf("3 : Login as an customer\n");
	printf("4 : Login as an employee\n");
	
	int n;
	
	scanf("%d", &n);
	
	return n;
}

void action(int option){
	switch(option){
	
	case 1:
		Add_Account_customer();
		break;
	
	case 2:
	    Add_Account_employee();
		break;
	
	case 3:
	    Login_customer();
		break;
	
	case 4:
	    Login_employee();
		break;
	}
}

int main(){

	system("COLOR 2");

	printf("//////////////////////////////////////////////////////\n");
	printf(".___  ___. .______        ___      .__   __.  __  ___\n");
	printf("|   \/   | |   _  \      /   \     |  \ |  | |  |/  /\n");
	printf("|  \  /  | |  |_)  |    /  ^  \    |   \|  | |  '  /\n");
	printf("|  |\/|  | |   _  <    /  /_\  \   |  . `  | |    <\n");
	printf("|  |  |  | |  |_)  |  /  _____  \  |  |\   | |  .  \ \n");
	printf("|__|  |__| |______/  /__/     \__\ |__| \__| |__|\__\ \n");
	printf("//////////////////////////////////////////////////////\n");

	fp = fopen("Person.txt", "w+");
	fp1 = fopen("Person1.txt", "w+");
	fe = fopen("Employee.txt", "w+");
	fe1 = fopen("Employee1.txt", "w+");
	fm1 = fopen("Transaction1.txt", "w+");

    int n;
    
	printf("Hi, Welcome to MBank!\n\n");
    
	while(1){
		int option = menu();
		if(option == 0){
			printf("Hope You Enjoyed !\n");
			break;
		}
		action(option);
    }

    return 0;
}