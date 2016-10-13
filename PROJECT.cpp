
//SUPERMARKET MANAGEMENT SYSTEM PROJECT 

//Made by A.ADITYA

//Class 12 - CS Project



// HEADER FILES USED IN PROJECT

#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>
#include<string.h>



// Global declarations

fstream f;

char*password;
void mainmenu();
int c=1;




// CLASS USED IN PROJECT

class product
{
	int pno;
	char name[50];
	float price,qty,tax,dis;
	public:
	void create_product()
	{
	 pno=c;
	 cout<<"\nProduct number is:"<<pno;
	 getch();c++;
	 cout<<"\n\nPlease Enter The Name of The Product: ";
	 gets(name);
	 cout<<"\nPlease Enter The Price of The Product: ";
	 cin>>price;
	 cout<<"\nPlease Enter The Discount (%): ";
	 cin>>dis;


	}
	void show_product()
	{
	cout<<"\nThe Product No. of The Product : "<<pno;
	cout<<"\nThe Name of The Product : ";
	puts(name);
	cout<<"\nThe Price of The Product : "<<price;
	cout<<"\nDiscount : "<<dis;
	}
	int retpno()
	{return pno;}
	float retprice()
	{return price;}
	char* retname()
	{return name;}
	int retdis()
	{return dis;}
}; //class ends here


product pr;



// function to write in file

void write_product()
{

	f.open("Shop.dat",ios::out|ios::app);
	pr.create_product();
	f.write((char*)&pr,sizeof(product));
	f.close();
	cout<<"\n\nThe Product Has Been Created ";
	getch();
}


// function to read all records from file

void display_all()
{
	clrscr();
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	f.open("Shop.dat",ios::in);
	while(f.read((char*)&pr,sizeof(product)))
	{
		pr.show_product();
		cout<<"\n\n====================================\n";
		getch();
	}
	f.close();
	getch();
}


// function to read specific record from file

void display_sp(int n)
{
	int flag=0;
	f.open("Shop.dat",ios::in);
	while(f.read((char*)&pr,sizeof(product)))
	{
		if(pr.retpno()==n)
		{
			clrscr();
			pr.show_product();
			flag=1;
		}
	}
	f.close();
	if(flag==0)
	cout<<"\n\nrecord not exist";
	getch();
}


// function to modify record of file


void modify_product()
{
	int no,found=0;
	clrscr();
	cout<<"\n\n\tTo Modify ";
	cout<<"\n\n\tPlease Enter The Product No. of The Product";
	cin>>no;
	f.open("Shop.dat",ios::in|ios::out);
	while(f.read((char*)&pr,sizeof(product)) && found==0)
	{
		if(pr.retpno()==no)
		{
			pr.show_product();
			cout<<"\nPlease Enter The New Details of Product"<<endl;
			pr.create_product();
			int pos=-1*sizeof(pr);
			f.seekp(pos,ios::cur);
			f.write((char*)&pr,sizeof(product));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}
	f.close();

	if(found==0)
	cout<<"\n\n Record Not Found ";
	getch();
}


// function to delete record of file

void delete_product()
{
	int no;
	clrscr();
	cout<<"\n\n\n\tDelete Record";
	cout<<"\n\nPlease Enter The product no. of The Product You Want To Delete";
	cin>>no;
	f.open("Shop.dat",ios::in|ios::out);
	fstream f2;
	f2.open("Temp.dat",ios::out);
	f.seekg(0,ios::beg);
	while(f.read((char*)&pr,sizeof(product)))
	{
		if(pr.retpno()!=no)
		{
			f2.write((char*)&pr,sizeof(product));
		}
	}
	f2.close();
	f.close();
	remove("Shop.dat");
	rename("Temp.dat","Shop.dat");
	cout<<"\n\n\tRecord Deleted ..";
	getch();
}


// function to display all products price list

void menu()
{
	clrscr();
	f.open("Shop.dat",ios::in);
	if(!f)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create file";

		cout<<"\n\n\n Program is closing ....";
		getch();
		exit(0);
	}
	cout<<"\n\n\t\tProduct MENU\n\n";
	cout<<"====================================================\n";
	cout<<"P.NO.\t\tNAME\t\tPRICE\n";
	cout<<"====================================================\n";
	while(f.read((char*)&pr,sizeof(product)))
	{
		cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
	}
	f.close();
}
 

// function to place order and generating bill for Products


void place_order()
{
	int order_arr[50],quan[50],c=0;
	float amt,damt,total=0;
	char ch='Y';
	menu();
	cout<<"\n============================";
	cout<<"\n PLACE YOUR ORDER";
	cout<<"\n============================\n";
	do
	{
		cout<<"\n\nEnter The Product No. Of The Product : ";
		cin>>order_arr[c];
		cout<<"\nQuantity in number : ";
		cin>>quan[c];
		c++;
		cout<<"\nDo You Want To Order Another Product ? (y/n)";
		cin>>ch;
	}while(ch=='y' ||ch=='Y');
	cout<<"\n\nThank You For Placing The Order";getch();clrscr();
	cout<<"\n\n********************************INVOICE************************\n";
	cout<<"\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";
	for(int x=0;x<=c;x++)
	{
		f.open("Shop.dat",ios::in);
		f.read((char*)&pr,sizeof(product));
		while(!f.eof())
		{
			if(pr.retpno()==order_arr[x])
			{
				amt=pr.retprice()*quan[x];
				damt=amt-(amt*pr.retdis()/100);
				cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()
				<<"\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;
				total+=damt;
			}
			f.read((char*)&pr,sizeof(product));
		}
		f.close();
	}
	cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;
	getch();
}


// INTRODUCTION FUNCTION

void intro()
{
	clrscr();
	gotoxy(16,10);
	cout<<"******WELCOME TO KVH SUPER MARKET******";

	gotoxy(25,15);
	cout<<"COMPUTER SCIENCE PROJECT";
	cout<<"\n\n\t\t\t  MADE BY : A.ADITYA";
	cout<<"\n\n\t\t\t  SCHOOL : KV HEBBAL";
	getch();
}
 

// ADMIN MENU FUNCTION

void admin_menu()
{
	clrscr();
	char ch2;
	do{     clrscr();
		cout<<"\n\n\n\tADMIN MENU";
		cout<<"\n\n\t1.CREATE PRODUCT";
		cout<<"\n\n\t2.DISPLAY ALL PRODUCTS";
		cout<<"\n\n\t3.QUERY ";
		cout<<"\n\n\t4.MODIFY PRODUCT";
		cout<<"\n\n\t5.DELETE PRODUCT";
		cout<<"\n\n\t6.VIEW PRODUCT MENU";
		cout<<"\n\n\t7.BACK TO MAIN MENU";
		cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
		cin>>ch2;
		switch(ch2)
		{
			case '1': clrscr();
			write_product();
			break;
			case '2': display_all();break;
			case '3':
			int num;
			clrscr();
			cout<<"\n\n\tPlease Enter The Product No. ";
			cin>>num;
			display_sp(num);
			break;
			case '4': modify_product();break;
			case '5': delete_product();break;
			case '6': menu();getch();break;

			case '7': mainmenu();
			default:cout<<"\a";admin_menu();
		}
	}while(ch2!=7);
}


void mainmenu()
{char ch;
 do
 {
	clrscr();
	cout<<"\n\n\n\tMAIN MENU";
	cout<<"\n\n\t01. CUSTOMER";
	cout<<"\n\n\t02. ADMINISTRATOR";
	cout<<"\n\n\t03. EXIT";
	cout<<"\n\n\tPlease Select Your Option (1-3) ";
	cin>>ch;
	switch(ch)
	{
		case '1':
		clrscr();
		place_order();
		getch();
		break;

		case '2':
		for(int i=1;i<4;i++)
		{
			cout<<"\n\n\nEnter ADMIN password: ";
			gets(password);

			if(strcmp("supermarket",password)==0)
			{	i=4 ;
				admin_menu();}
				else
				cout<<"\nIncorrect password!!! "<<3-i<<" tries remaining";
			}
			break;

		case '3':exit(0);

		default :cout<<"\a";

		}
}while(ch!='3');
}


// THE MAIN FUNCTION OF PROGRAM

void main()
{

	intro();
	mainmenu();

}

// END OF PROJECT
