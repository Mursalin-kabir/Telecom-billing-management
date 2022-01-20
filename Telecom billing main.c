#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<windows.h>
#include<stdlib.h>


struct subscriber


{
char phonenumber[20];
char name[50];
float amount;
}s;


void addrecords();
void listrecords();
void modifyrecords();
void deleterecords();
void searchrecords();
void payment();
char get;
int main()
{	int password;
	int phonenumber;
	char choice;



	system("cls");


	printf("\n\n\n\n\n\n\n\t\t-WELCOME TO TELECOM BILLING MANAGEMENT SYSTEM-");

	Sleep(2000);
	getch();
    system("cls");


	while (1)
	{
		system("cls");
		printf("\n enter\n A : for adding new records.\n B : for list of records");
		printf("\n C : for modifying records.\n D : for payment");
		printf("\n E : for searching records.");
		printf("\n F : for deleting records.\n G : for exit\n");
		choice=getche();
		choice=toupper(choice);
		switch(choice)
		{
			case 'D':
				payment();break;
			case 'A':
				addrecords();break;
			case 'B':
				listrecords();break;
			case 'C':
				modifyrecords();break;
			case 'E':
				searchrecords();break;
			case 'F':
				deleterecords();break;
			case 'G':
				system("cls");
				printf("\n\n\t\t\t\tTHANK YOU");

				Sleep(2000);
				exit(0);
				break;
			default:
				system("cls");
				printf("Incorrect Input you entered");
				printf("\nAny key to continue");
				getch();
		}
	}
}


void addrecords()
{
	FILE *f;
	char test;
	f=fopen("c:/file.ojs","ab+");
	if(f==0)
	{   f=fopen("c:/file.ojs","wb+");
		system("cls");
		printf("please wait");
		printf("/npress any key to continue");
		getch();
	}


	while(1)
	{
		system("cls");
		printf("\n Enter phone number:");
		scanf("%s",&s.phonenumber);
		printf("\n Enter name:");
		fflush(stdin);
		scanf("%[^\n]",&s.name);
		printf("\n Enter amount:");
		scanf("%f",&s.amount);
		fwrite(&s,sizeof(s),1,f);
		fflush(stdin);
		system("cls");
		printf("1 record added successfully");
		printf("\n Press esc key to exit, any other key to add other record:");
		test=getche();
		if(test==27)
			break;
	}
	fclose(f);
}


void listrecords()
{
	FILE *f;
	int i;
	if((f=fopen("c:/file.ojs","rb"))==NULL)
		exit(0);
	system("cls");
	printf("Phone Number\t\tUser Name\t\t\tAmount\n");

	while(fread(&s,sizeof(s),1,f)==1)
	{
		printf("\n%-10s\t\t%-20s\t\tTk. %.2f /-",s.phonenumber,s.name,s.amount);
	}

fclose(f);
getch();
}


void deleterecords()


{
	FILE *f,*t;
	int i=1;
	char phonenumber[20];
	if((t=fopen("c:/temp.ojs","w+"))==NULL)
	exit(0);
	if((f=fopen("c:/file.ojs","rb"))==NULL)
	exit(0);
	system("cls");
	printf("Enter the phone number you want to delete");
	fflush(stdin);
	scanf("%[^\n]",phonenumber);

	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)

		{       i=0;
			continue;

		}
		else
			fwrite(&s,sizeof(s),1,t);
	}


	if(i==1)
	{       system("cls");
		printf("Phone number \"%s\" not found",phonenumber);
		remove("c:/file.ojs");
		rename("c:/temp.ojs","c:/file.ojs");
		getch();
		fclose(f);
		fclose(t);
		main();
	}


	remove("c:/file.ojs");
	rename("c:/temp.ojs","c:/file.ojs");
	system("cls");
	printf("The Number %s Deleted successfully ",phonenumber);
	fclose(f);
	fclose(t);
	getch();
}


void searchrecords()


{
	FILE *f;
	char phonenumber[20];
	int flag=1;
	f=fopen("c:/file.ojs","rb+");
	if(f==0)
		exit(0);
	fflush(stdin);
	system("cls");
	printf("Enter Phone Number to search");
	scanf("%s", phonenumber);
	while(fread(&s,sizeof(s),1,f)==1)

	{
		if(strcmp(s.phonenumber,phonenumber)==0)


		{	system("cls");
			printf(" Record Found ");
			printf("\n\nPhonenumber: %s\nName: %s\nAmount: Tk.%0.2f\n",s.phonenumber,s.name,s.amount);
			flag=0;
			break;
		}
		else if(flag==1)


		{	system("cls");
			printf("Entered Phone Number Not found");
		}
	}
	getch();
	fclose(f);
}


void modifyrecords()


{
	FILE *f;
	char phonenumber[20];
	long int size=sizeof(s);
	if((f=fopen("c:/file.ojs","rb+"))==NULL)
		exit(0);
	system("cls");
	printf("Enter phone number of the customer to modify:");
	scanf("%[^\n]",phonenumber);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{
			system("cls");
			printf("\n Enter phone number:");
			scanf("%s",&s.phonenumber);
			printf("\n Enter name: ");
			fflush(stdin);
			scanf("%[^\n]",&s.name);
			printf("\n Enter amount: ");
			scanf("%f",&s.amount);
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
	}
	fclose(f);
}


void payment()


{
	FILE *f;
	char phonenumber[20];
	long int size=sizeof(s);
	float amt;
	int i;
	if((f=fopen("c:/file.ojs","rb+"))==NULL)
		exit(0);
	system("cls");
	printf("Enter phone number of the customer for payment");
	scanf("%[^\n]",phonenumber);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{
			system("cls");
			printf("\n Phone No.: %s",s.phonenumber);
			printf("\n Name: %s",s.name);
			printf("\n Current amount: %f",s.amount);
			printf("\n");
			for(i=0;i<79;i++)
				printf("-");
			printf("\n\nEnter amount of payment :");
			fflush(stdin);
			scanf(" %f",&amt);
			s.amount=s.amount-amt;
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
	}


	system("cls");
	printf("THANK YOU %s FOR BEING WITH US",s.name);
	printf("\n\n\n stay tuned :)");
	getch();
	fclose(f);
}

