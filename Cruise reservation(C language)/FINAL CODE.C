#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

void dispchar(char a)																	//Display Char
{
	int i;
	for(i=0;i<70;i++)
	{
		printf("%c",a);
	}
}

void welcome()																			//Welcome Function
{
	printf("\n\n Welcome to INDIAN CRUISE LINES \n\n");
    
}

struct ship{
	int tno;
    char tname[100];
    char from[100];
    char dest[100];
	int fare;
	int fare_child;
    int no_of_seat;
};

struct res
{
	int tno;
    char tname[100];
    char from[100];
    char dest[100];
    char pname[100];
    int age;
    int fare;
    int d,m,y;
    long long int pnr;																	//PNR = Train_no + DOT + seat_no
    long long int real_pnr;
};

int seatno(long long int tr)															//Funtion to find no of seat book -> Argumen = Train_no + Date_Of_Travel
{
	struct res r;
	FILE *p;
	p=fopen("rese.txt","r");
	int count=0;
	while((fscanf(p,"%d",&r.tno),fscanf(p,"%s",r.tname),fscanf(p,"%s",r.from),fscanf(p,"%s",r.dest),fscanf(p,"%s",r.pname),fscanf(p,"%d",&r.age),fscanf(p,"%d",&r.fare),fscanf(p,"%d",&r.d),fscanf(p,"%d",&r.m),fscanf(p,"%d",&r.y),fscanf(p,"%lld",&r.pnr),fscanf(p,"%lld",&r.real_pnr))==1)
	{
		if(tr==r.pnr/100)																//PNR/100 = Train_no + Date_Of_Travel
		count++;
	}
	fclose(p);
	return(count);
}

void reservation()																		//Funtion for reservation
{
	struct res r;
	struct ship tr;
	FILE *p,*t;
	int get_seat_no,ch,found=0;
	long long int n;
	
	t=fopen("ship.txt","r");
	system("cls");
	dispchar('*');
	printf("\n\t\t\t\t RESERVATION\n");
	dispchar('*');
	printf("\n\n\nEnter ship no 		: ");
	scanf("%d",&r.tno);
	
	while((fscanf(t,"%d",&tr.tno),fscanf(t,"%s",&tr.tname),fscanf(t,"%s",&tr.from),fscanf(t,"%s",&tr.dest),fscanf(t,"%d",&tr.fare),fscanf(t,"%d",&tr.fare_child),fscanf(t,"%d",&tr.no_of_seat))==1)
	{
		if(tr.tno==r.tno)
		{
			strcpy(r.tname,tr.tname);
			strcpy(r.from,tr.from);
			strcpy(r.dest,tr.dest);
			
			printf("Ship name 		: %s",r.tname);
			printf("\nFrom 			: %s",r.from);
			printf("\nDestination 		: %s",r.dest);
			printf("\n\nEnter Passenger name 	: ");
			scanf("%s",r.pname);
			printf("Enter your age 		: ");
			scanf("%d",&r.age);
	
			if(r.age<=10)
			r.fare=500;
			else if(r.age>10 && r.age<60)
			r.fare=1000;
			else
			r.fare=650;
	
			printf("Fare 			: %d\n",r.fare);
			printf("\nDate Of Travelling (DD MM YYYY)\n\n");
			printf("\tEnter Day (DD) : ");
			scanf("%d",&r.d);
			printf("\tEnter Month (MM) : ");
			scanf("%d",&r.m);
			printf("\tEnter Year (YYYY) : ");
			scanf("%d",&r.y);
																						//PNR creation -> PNR = Train_no + Date_Of_Travel + Seat_no
			n=(((r.tno*100)+r.d)*100)+r.m;														//n=Train_no + Date_Of_Travel
			get_seat_no=seatno(n);																//get_seat_no = Seat_no
			r.pnr=(n*100)+get_seat_no+1;
			r.real_pnr=r.pnr;
			p=fopen("rese.txt","a");
	
			if(get_seat_no>=10)																	//If seat are full Asking passenger for wating
			{
				printf("\n\nSorry seats are full on required date.\n\nDo you want to Wating Seat\n\n1: Yes\n2: No\nEnter your choice : ");
				scanf("%d",&ch);
				if(ch==1)																		//If they agree to take wating seat
				{
					printf("\n\n\t\tPNR : %lld\n",r.pnr);
					fprintf(p,"%d\t",r.tno);
					fprintf(p,"%s\t",r.tname);
					fprintf(p,"%s\t",r.from);
					fprintf(p,"%s\t",r.dest);
					fprintf(p,"%s\t",r.pname);
					fprintf(p,"%d\t",r.age);
					fprintf(p,"%d\t",r.fare);
					fprintf(p,"%d\t",r.d);
					fprintf(p,"%d\t",r.m);
					fprintf(p,"%d\t",r.y);
					fprintf(p,"%lld\t",r.pnr);
					fprintf(p,"%lld\n",r.real_pnr);
					found=1;
				}
				else																			//If they don't agree to take wating seat
				printf("\nTry For Some Another Day\n");
			}
			else																				//If seat are empty
			{
				printf("\n\n\t\tPNR : %lld\n",r.pnr);
	
				fprintf(p,"%d\t",r.tno);
				fprintf(p,"%s\t",r.tname);
				fprintf(p,"%s\t",r.from);
				fprintf(p,"%s\t",r.dest);
				fprintf(p,"%s\t",r.pname);
				fprintf(p,"%d\t",r.age);
				fprintf(p,"%d\t",r.fare);
				fprintf(p,"%d\t",r.d);
				fprintf(p,"%d\t",r.m);
				fprintf(p,"%d\t",r.y);
				fprintf(p,"%lld\t",r.pnr);
				fprintf(p,"%lld\n",r.real_pnr);
				
				found=1;
			}	
			fclose(p);
		}
	}
	if(found==0)
	printf("\nShip Not found\n");
	fclose(t);	
}

void display_reservation()																//Function to display all reservation
{
	struct res r;
	FILE *p;
	p=fopen("rese.txt","r");
	
	system("cls");
	dispchar('*');
	printf("\n\t\t\t\t RESERVATION\n");
	dispchar('*');
	printf("\n\nShip no      Ship name        From            To      Name    Age    Fare     Date             PNR\n\n");
	while((fscanf(p,"%d",&r.tno),fscanf(p,"%s",r.tname),fscanf(p,"%s",r.from),fscanf(p,"%s",r.dest),fscanf(p,"%s",r.pname),fscanf(p,"%d",&r.age),fscanf(p,"%d",&r.fare),fscanf(p,"%d",&r.d),fscanf(p,"%d",&r.m),fscanf(p,"%d",&r.y),fscanf(p,"%lld",&r.pnr),fscanf(p,"%lld",&r.real_pnr))==1)
	{
		printf("%d\t",r.tno);
		printf("%s\t",r.tname);
		printf("%s\t",r.from);
		printf("%s\t",r.dest);
		printf("%s\t",r.pname);
		printf("%d\t",r.age);
		printf("%d\t",r.fare);
		printf("%d-",r.d);
		printf("%d-",r.m);
		printf("%d\t",r.y);
		printf("%lld\n",r.pnr);
	}
	fclose(p);
}

void cancel_reservation()																//Function for cancellation of ticket
{
	struct res r;
	FILE *p,*q;
	long long int key;
	int count=0;
	p=fopen("rese.txt","r");
	q=fopen("temp.txt","a");
	
	system("cls");
	dispchar('*');
	printf("\n\t\t\t\t\tCANCELATION OF RESERVATION\n");
	dispchar('*');
	printf("\n\nEnter PNR no :");
	scanf("%lld",&key);
	while((fscanf(p,"%d",&r.tno),fscanf(p,"%s",r.tname),fscanf(p,"%s",r.from),fscanf(p,"%s",r.dest),fscanf(p,"%s",r.pname),fscanf(p,"%d",&r.age),fscanf(p,"%d",&r.fare),fscanf(p,"%d",&r.d),fscanf(p,"%d",&r.m),fscanf(p,"%d",&r.y),fscanf(p,"%lld",&r.pnr),fscanf(p,"%lld",&r.real_pnr))==1)
	{
		if(key==r.pnr)
		{
			printf("\nBYE\n");
			count=1;
		}
		else
		{
			fprintf(q,"%d\t",r.tno);
			fprintf(q,"%s\t",r.tname);
			fprintf(q,"%s\t",r.from);
			fprintf(q,"%s\t",r.dest);
			fprintf(q,"%s\t",r.pname);
			fprintf(q,"%d\t",r.age);
			fprintf(q,"%d\t",r.fare);
			fprintf(q,"%d\t",r.d);
			fprintf(q,"%d\t",r.m);
			fprintf(q,"%d\t",r.y);
			
			if(count==1 && (key/100)==(r.pnr/100))										//Changing Waiting list
			fprintf(q,"%lld\t",r.pnr-1);
			else
			fprintf(q,"%lld\t",r.pnr);
			
			fprintf(q,"%lld\n",r.real_pnr);
		}
	}
	if(count==0)
	{
		printf("\n\nPNR not found\n\n");
	}
	fclose(p);
	fclose(q);
	
	remove("rese.txt");																	//deleting original file
	rename("temp.txt","rese.txt");														//old_name , new_name
}

void seat_availabilty()																	//Function to check seat Availabilty
{
	struct ship t;
	int tn,d,m,res,count=0;
	FILE *p;
	p=fopen("ship.txt","r");
	
	printf("\n\nEnter ship no : ");
	scanf("%d",&tn);
	while((fscanf(p,"%d",&t.tno),fscanf(p,"%s",&t.tname),fscanf(p,"%s",&t.from),fscanf(p,"%s",&t.dest),fscanf(p,"%d",&t.fare),fscanf(p,"%d",&t.fare_child),fscanf(p,"%d",&t.no_of_seat))==1)
	{
		if(tn==t.tno)
		{
			printf("\tEnter Day (DD) : ");
			scanf("%d",&d);
			printf("\tEnter Month (MM) : ");
			scanf("%d",&m);
			res=seatno((((tn*100)+d)*100)+m);											//Total seat booked = Comfirmed + Wating
			if(res<=10)
			printf("\n\nSeat Aval : %d",10-res);										//Displaying No of seat left
			else
			printf("\n\nWating %d",res-10);												//Displaying Wating no
			count=1;
		}
	}
	if(count==0)
	printf("\n\nShip no %d not found",tn);
	fclose(p);
}

void pnr_enquiry()																		//Function to check detail of user reservation
{
	struct res r;
	FILE *p;
	p=fopen("rese.txt","r");
	long long int key;
	int count=0;
	system("cls");
	dispchar('*');
	printf("\n\t\t\t\t RESERVATION\n");
	dispchar('*');
	printf("\n\n\nEnter you PNR no : ");
	scanf("%lld",&key);
	while((fscanf(p,"%d",&r.tno),fscanf(p,"%s",r.tname),fscanf(p,"%s",r.from),fscanf(p,"%s",r.dest),fscanf(p,"%s",r.pname),fscanf(p,"%d",&r.age),fscanf(p,"%d",&r.fare),fscanf(p,"%d",&r.d),fscanf(p,"%d",&r.m),fscanf(p,"%d",&r.y),fscanf(p,"%lld",&r.pnr),fscanf(p,"%lld",&r.real_pnr))==1)
	{
		if(key==r.real_pnr)
		{
			printf("\n\nShip no       : %d\n",r.tno);
			printf("Ship Name     : %s\n",r.tname);
			printf("From           : %s\n",r.from);
			printf("Destination    : %s\n",r.dest);
			printf("Passenger Name : %s\n",r.pname);
			printf("Passenger Age  : %d\n",r.age);
			printf("Fare           : %d\n",r.fare);
			printf("Date of Travel : %d-",r.d);
			printf("%d-",r.m);
			printf("%d\n",r.y);
			
			if((r.pnr%100)<=10)															//If seat if confirmed : Displaying Seat no
			printf("\n\nSeat no        : %d",r.pnr%100);
			else
			{
				printf("\n\nWaiting No.    : %d",r.pnr%100-10);							//If seat if not confirmed : Displaying Wating no
			}
			count=1;
		}
	}
	if(count==0)
	printf("\n\nPNR Not found");
	fclose(p);
}

void ship_detail()																		//Function for storing data of a train
{
	struct ship t;
	FILE *p;
	p=fopen("ship.txt","a");
	
	system("cls");
	dispchar('*');
	printf("\n\t\t\t\t\tENTER SHIP DETAILS\n");
	dispchar('*');
	
	printf("\n\nEnter ship no : ");
	scanf("%d",&t.tno);
	printf("Enter ship name : ");
	scanf("%s",t.tname);
	printf("Enter ship From : ");
	scanf("%s",t.from);
	printf("Enter ship Destination : ");
	scanf("%s",t.dest);
	printf("\nAdult fare : 1000");
	t.fare=1000;
	printf("\nChild fare : 500");
	t.fare_child=500;
	printf("\nSenior Citizen fare : 650");
 	printf("\nShips total no of seat : 10\n");
 	t.no_of_seat=10;
 	
 	fprintf(p,"%d\t",t.tno);
 	fprintf(p,"%s\t",t.tname);
 	fprintf(p,"%s\t",t.from);
 	fprintf(p,"%s\t",t.dest);
 	fprintf(p,"%d\t",t.fare);
 	fprintf(p,"%d\t",t.fare_child);
 	fprintf(p,"%d\n",t.no_of_seat);
 	fclose(p);
}

void ship_display()																	//Function for displaying data of a train
{
	struct ship t;
	FILE *p;
	p=fopen("ship.txt","r");
	
	system("cls");
	dispchar('*');
	printf("\n\t\t\t\tSHIP DETAILS\n");
	dispchar('*');
	
	printf("\n\n  Ship no          Ship name           From           Destination      Adult fare\tChild fare\tTotal seat\n\n");
	while((fscanf(p,"%d",&t.tno),fscanf(p,"%s",&t.tname),fscanf(p,"%s",&t.from),fscanf(p,"%s",&t.dest),fscanf(p,"%d",&t.fare),fscanf(p,"%d",&t.fare_child),fscanf(p,"%d",&t.no_of_seat))==1)
	{
		printf("%10d\t",t.tno);
		printf("%20s\t",t.tname);
		printf("%10s\t",t.from);
		printf("%10s\t",t.dest);
		printf("%10d\t",t.fare);
		printf("%10d\t",t.fare_child);
		printf("%10d\n",t.no_of_seat);
	}
	fclose(p);
}

void ship_modify()																		//Function for modifying data of a train
{
	struct ship t;
	int key,found=0;
	FILE *p,*q;
	p=fopen("ship.txt","r");
	q=fopen("temp.txt","a");
	
	system("cls");
	dispchar('*');
	printf("\n\t\t\t\t\tMODIFY SHIP DETAILS\n");
	dispchar('*');
	
	printf("\n\nEnter ship no to modify : ");
	scanf("%d",&key);
	
	while((fscanf(p,"%d",&t.tno),fscanf(p,"%s",&t.tname),fscanf(p,"%s",&t.from),fscanf(p,"%s",&t.dest),fscanf(p,"%d",&t.fare),fscanf(p,"%d",&t.fare_child),fscanf(p,"%d",&t.no_of_seat))==1)
	{
		if(t.tno==key)
		{
			printf("Enter ship name : ");
			scanf("%s",t.tname);
			printf("Enter ship From : ");
			scanf("%s",t.from);
			printf("Enter ship Destination : ");
			scanf("%s",t.dest);
			printf("Enter Adult fare : ");
			scanf("%d",&t.fare);
			printf("Enter Child fare : ");
			scanf("%d",&t.fare_child);
 			printf("Enter ship's total no of seat : ");
 			scanf("%d",&t.no_of_seat);
 	
 			fprintf(q,"%d\t",t.tno);
 			fprintf(q,"%s\t",t.tname);
 			fprintf(q,"%s\t",t.from);
 			fprintf(q,"%s\t",t.dest);
 			fprintf(q,"%d\t",t.fare);
 			fprintf(q,"%d\t",t.fare_child);
 			fprintf(q,"%d\n",t.no_of_seat);
 			
 			found=1;
		}
		else
		{
			fprintf(q,"%d\t",t.tno);
 			fprintf(q,"%s\t",t.tname);
 			fprintf(q,"%s\t",t.from);
 			fprintf(q,"%s\t",t.dest);
 			fprintf(q,"%d\t",t.fare);
 			fprintf(q,"%d\t",t.fare_child);
 			fprintf(q,"%d\n",t.no_of_seat);
		}
	}
	fclose(p);
	fclose(q);
	
	if(found==0)
	printf("\n\nShip no %d not found",key);
	
	remove("ship.txt");																//deleting original file
	rename("temp.txt","ship.txt");														//old_name , new_name
}

void ship_delete()																		//Function for deleting data of a train
{
	struct ship t;
	int found=0;
	int key;
	FILE *p,*q;
	p=fopen("ship.txt","r");
	q=fopen("temp.txt","a");
	
	system("cls");
	dispchar('*');
	printf("\n\t\t\t\t\tDELETE SHIP DETAILS\n");
	dispchar('*');
	
	printf("\n\nEnter ship no to delete : ");
	scanf("%d",&key);
	
	while((fscanf(p,"%d",&t.tno),fscanf(p,"%s",&t.tname),fscanf(p,"%s",&t.from),fscanf(p,"%s",&t.dest),fscanf(p,"%d",&t.fare),fscanf(p,"%d",&t.fare_child),fscanf(p,"%d",&t.no_of_seat))==1)
	{
		if(t.tno==key)
		{
			printf("Ship no %d - %s data has been deleted\n",t.tno,t.tname);
			found=1;
		}
		else
		{
			fprintf(q,"%d\t",t.tno);
 			fprintf(q,"%s\t",t.tname);
 			fprintf(q,"%s\t",t.from);
 			fprintf(q,"%s\t",t.dest);
 			fprintf(q,"%d\t",t.fare);
 			fprintf(q,"%d\t",t.fare_child);
 			fprintf(q,"%d\n",t.no_of_seat);
		}
	}
	fclose(p);
	fclose(q);
	
	if(found==0)
	printf("\n\nShip no %d not found",key);
	
	remove("ship.txt");																//deleting original file
	rename("temp.txt","ship.txt");														//old_name , new_name
}

int password(char a[25])																//password function
{
	char pwd[25], ch;
	int i=0;
	printf("Enter password : ");
	while (1) 
	{
		ch = getch();
		
		if (ch == 13)  																	//13 is ASCII value of ENTER
		{
			pwd[i]='\0';
			break;
		}
		
		if (ch==8) 																	    //8 is ASCII value of BACKSPACE
		{
			if(i==0)																	//when i=0 it will not accept BACKSPACE
			{
        		continue;
			}
			else
			{
				printf("\b \b");
        		i--;
        		continue;
			}			
    	}
    	pwd[i++] = ch;
    	printf("*");
   }
	if(strcmp(a,pwd)==0)
	return(1);
	else
	return(0);
}
 
int main()																				//main functon
{
	int choice,ch_user=1,ch_admin=1;
	char pwd[25] = {"ship"};
	welcome();
	system("pause");
	while(1)
	{
		ch_user=1;ch_admin=1;															//To assign admin & user Choice value as one so that it can be exicutalbe at 1st time
		
		system("cls");
		dispchar('*');
		printf("\n\t\t\t\tCRUISE RESERVATION\n");
		dispchar('*');
		
		printf("\n\n1: Admin \n2: User \n3: Exit \nEnter choice : ");
		scanf("%d",&choice);
		
		if(choice==1)																	//Admin Login
		{
			if(password(pwd))
			{
				printf("\nCorrect password");
				while(ch_admin!=6)
				{
					system("cls");
					dispchar('*');
					printf("\n\t\t\t\tCRUISE RESERVATION\n");
					dispchar('*');
					
					printf("\n\n1: Add ship detail \n");
					printf("2: Display ship detail \n");
					printf("3: Modify ship Details\n");
					printf("4: Delete ship details\n");
					printf("5: Check PNR info\n");
					printf("6: Exit\n");
					printf("\nEnter Choice : ");
					scanf("%d",&ch_admin);
			
					switch(ch_admin)
					{
						case 1:
							ship_detail();
							break;
						case 2:
							ship_display();
							break;
						case 3:
							ship_modify();
							break;
						case 4:
							ship_delete();
							break;
						case 5:
							display_reservation();
							break;
						case 6:
							printf("\n\nHave a Nice Day\n\n");
							break;
						default:
							printf("\nInvalid Input\n");
					}
					getch();
				}
			}
			else
			{
				printf("\nIncorrect password");
			}
		}
		
		else if(choice==2)																//User login
		{
			while(ch_user!=7)
			{
				system("cls");
				dispchar('*');
				printf("\n\t\t\t\tCRUISE RESERVATION\n");
				dispchar('*');
				
				printf("\n\n1: ship details \n");
				printf("2: Seat Availabilty\n");
				printf("3: Book Ticket\n");
				printf("4: PNR Enquiry\n");
				printf("5: Cancellation of Ticket\n");
				printf("6: Fare Enquiry\n");
				printf("7: Exit\n");
				printf("\nEnter Choice : ");
				scanf("%d",&ch_user);
			
				switch(ch_user)
				{
					case 1:
						ship_display();
						break;
					case 2:
						seat_availabilty();
						break;
					case 3:
						reservation();
						break;
					case 4:
						pnr_enquiry();
						break;
					case 5:
						cancel_reservation();
						break;
					case 6:
						printf("\n\n\tAge			Fare\n");
						printf("\n\t0-10 yrs		Rs.500");
						printf("\n\t10-60 yrs		Rs.1000");
						printf("\n\t60+ yrs			Rs.650");
						break;
					case 7:
						printf("\n\nHave a Nice Day\n\n");
						break;
					default:
						printf("\nInvalid Input\n");
				}
				getch();
			}
		}
		
		else if(choice==3)																//Exit
		{
			exit(0);
		}
		
		else
		printf("\nInvalid Input ");
		getch();
	}
	getch();
   return 0 ;
}
