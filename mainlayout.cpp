//19k-1361 / 19k-0154 / 19k-0151
#include<iostream>
#include "classheader.h"
using namespace std;
void mainlayout ();
void billing();
void billing_1();
void enter_product();
void inventory1();
void adminportal();
void employee();
void enter_emp();
void searchemp();
void viewemp();
int main()
{
	mainlayout();
}
void mainlayout ()
{
	int ch = 0;
	system("cls");
	fflush(stdin);
	cout<<"........................................WELCOME TO SUPERMARKET BILLING SYSTEM.......................................\n";
	cout<<"1 : BILLING "<<endl;
	cout<<"2 : INVENTORY "<<endl;
	cout<<"3 : ADMINISTRATION "<<endl;
	cout<<"4 : EXIT"<<endl;
	cout<<"CHOICE: ";
	cin >>ch;
	switch (ch){
	    case 1:
	    	billing();
	    	break;
	    case 2:
	    	system("cls");
	    	inventory1();
	    	break;
	    case 3:
	    	adminportal();
	    	break;
	    case 4:
	    	cout<<"\n............................THANK YOU FOR USING SUPERMARKET BILLING SYSTEM.................................\n";
	    	break;
    }
    exit;
}
void billing()
{
	int ch,exit;
	system("cls");
	cout<<"********************************************************BILLING PORTAL*************************************************\n";
	cout<<"1 : BILLING "<<endl;
	cout<<"2 : DELETE ITEMS "<<endl;
	cout<<"3 : GENERATE BILL "<<endl;
	cout<<"4 : EXIT"<<endl;
	cout<<"CHOICE: ";
	cin >>ch;
	switch (ch){
	    case 1:
	    	system("cls");
	    	bil.getBill();
	    	cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
			cin >>exit;
			if(exit == 1){
				billing();
			}
	    	break;
	    case 2:
	    	system("cls");
	    	bil.deleteprod();
	    	cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
			cin >>exit;
			if(exit == 1){
				billing();
			}
	    	break;
	    case 3:
	    	bill_file(bil);
	    	cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
			cin >>exit;
			if(exit == 1){
				billing();
			}
	    	break;
	    case 4:
	    	mainlayout();
	    	break;
    }
}
void inventory1()
{
	int ch;
	int exit;
	system("cls");
	cout<<"******************************************************INVENTORY PORTAL************************************************\n";
	cout<<"1 : ENTER ITEMS "<<endl;
	cout<<"2 : UPDATE STOCK "<<endl;
	cout<<"3 : DISPLAY ALL ITEMS "<<endl;
	cout<<"4 : EXIT"<<endl;
	cout<<"CHOICE: ";
	cin >>ch;
	switch (ch){
	    case 1:
	    	system("cls");
	    	cout<<"\n----------------------------PLEASE START ENTERING ITEMS-------------------------------\n";
	    	enter_product();
	    	break;
	    case 2:
	    	system("cls");
	    	updateprod();
	    	cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
	    	cin >>exit;
	    	if(exit == 1){
	    		inventory1();
			}
	    	break;
	    case 3:
	    	system("cls");
	    	display_prod();
	    	cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
	    	cin >>exit;
	    	if(exit == 1){
	    		inventory1();
			}
	    	break;
	    case 4:
	        mainlayout();
	        break;
    }
}
void enter_product()
{
	char ch;
	int exit;
	fstream fp;
	do{
		fp.open("inventory.txt",ios::out | ios::app);
		inv.getData();
        fp.write((char * ) & inv, sizeof(inventory));
        fp.close();
        cout<<"do you want to enter more <y/n> ? ";
		cin >>ch;
	}while(ch == 'y' || ch =='Y');
	cout<<"\n\n\n\n\t\t\t\t\t1 : EXIT\n";
	cin >>exit;
	if(exit == 1){
		inventory1();
	}
}
void adminportal()
{
	int ch;
	int exit;
	system("cls");
	cout<<"\n\n\t\t\tADMINISTATION PORTAL\n";
	cout<<"1 : EMPLOYEE "<<endl;
	cout<<"2 : VIEW SALES "<<endl;
	cout<<"3 : SEARCH BILLS "<<endl;
	cout<<"4 : EXIT"<<endl;
	cout<<"CHOICE: ";
	cin >>ch;
	switch (ch){
	    case 1:
	    	system("cls");
	    	employee();
	    	break;
	    case 2:
	    	system("cls");
	    	sales();
	    	cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
	    	cin >>exit;
	    	if(exit == 1){
	    		adminportal();
			}
	    	break;
	    case 3:
	    	system("cls");
	    	searchbills();
	    	cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
	    	cin >>exit;
	    	if(exit == 1){
	    		adminportal();
			}
	    	break;
	    case 4:
	        mainlayout();
	        break;
    }
}
void employee()
{
	int ch;
	int exit;
	system("cls");
	cout<<"\n\n\t\t\tEMPLOYEE PORTAL\n";
	cout<<"1 : ENTER EMPLOYEE "<<endl;
	cout<<"2 : UPDATE EMPLOYEE "<<endl;
	cout<<"3 : SEARCH EMPLOYEE "<<endl;
	cout<<"4 : VIEW EMPLOYEES "<<endl;
	cout<<"5 : DELETE EMPLOYEE "<<endl;
	cout<<"6 : EXIT"<<endl;
	cout<<"CHOICE: ";
	cin >>ch;
	switch (ch){
	    case 1:
	    	system("cls");
	    	cout<<"\n----------------------------PLEASE ENTER EMPLOYEE DATA-------------------------------\n";
	    	enter_emp();
	    	break;
	    case 2:
	    	system("cls");
	    	updateemp();
	    	cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
	    	cin >>exit;
	    	if(exit == 1){
	    		employee();
			}
	    	break;
	    case 3:
	    	system("cls");
	    	searchemp();
	    	cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
	    	cin >>exit;
	    	if(exit == 1){
	    		employee();
			}
	    	break;
	    case 4:
	    	system("cls");
	    	viewemp();
	    	cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
	    	cin >>exit;
	    	if(exit == 1){
	    		inventory1();
			}
	    	break;
	    case 5:
	    	deleteemp();
	    	cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
	    	cin >>exit;
	    	if(exit == 1){
	    		employee();
			}
	    case 6:
	    	adminportal();
	        break;
    }
}
void enter_emp()
{
	char ename[100],pn[30],gn[10],addr[50],em[30],ds[30],dn[30],ch;
	int age,flr,sal,hrs,exit,id;
	fstream fp;
	do{
		id = countemp();
		fflush(stdin);
		cout<<"-------------------------------EMPLOYEE'S ID : "<<id<<" --------------------------------------\n";
		cout<<"ENTER EMPLOYEE NAME : ";
		gets(ename);
		cout<<"ENTER EMPLOYEE AGE : ";
		cin >>age;
		fflush(stdin);
		cout<<"ENTER GENDER : ";
		gets(gn);
		cout<<"ENTER EMPLOYEE PHONE NUMBER : ";
		gets(pn);
		cout<<"ENTER EMPLOYEE ADDRESS : ";
		gets(addr);
		cout<<"ENTER EMPLOYEE EMAIL : ";
		gets(em);
		cout<<"ENTER EMPLOYEE DESIGNITION: ";
		gets(ds);
		cout<<"ENTER EMPLOYEE DEPARTMENT NAME: ";
		gets(dn);
		if(strcmp(ds,"department manager") == 0){
			fflush(stdin);
			cout<<"ENTER DUTY HOURS: ";
			cin >>hrs;
			cout<<"ENTER SALARY: ";
			cin >>sal;
			dept_manager dm(id,ename,age,pn,gn,em,addr,dn,hrs,sal);
			fp.open("deptmanager.txt" , ios :: app | ios :: out);
			fp.write((char *) &dm , sizeof(dept_manager));
			fp.close();
		}else if(strcmp(ds,"sales person") == 0){
			cout<<"ENTER DUTY HOURS: ";
			cin >>hrs;
			cout<<"ENTER SALARY: ";
			cin >>sal;
			cout<<"ENTER FLOOR NUMBER : ";
			cin >>flr;
			sales_person sp(id,ename,age,pn,gn,em,addr,dn,hrs,flr,sal);
			fp.open("salesperson.txt" , ios :: app | ios :: out);
			fp.write((char *) &sp , sizeof(sales_person));
			fp.close();
		}else if(strcmp(ds,"accountant") == 0){
			cout<<"ENTER DUTY HOURS: ";
			cin >>hrs;
			cout<<"ENTER SALARY: ";
			cin >>sal;
			accountant acn(id,ename,age,pn,gn,em,addr,dn,hrs,sal);
			fp.open("accountant.txt" , ios :: app | ios :: out);
			fp.write((char *) &acn , sizeof(accountant));
			fp.close();
		}
		cout<<"DO YOU WANT TO ENTER MORE EMPLOYEES <y/n> ? ";
		cin >>ch;
	}while(ch == 'y' || ch == 'Y');
	cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
	cin >>exit;
	if(exit == 1){
	    employee();
	}
}
void searchemp()
{
	int id,ds,exit;
	sales_person sp;
	dept_manager dm;
	accountant acn;
	fstream fp;
	system("cls");
	cout<<"\n\n\nENTER EMPLOYEE'S ID : ";
	cin >>id;
	do{
		fstream fp;
		cout<<"\n1 : SALES PERSON ";
		cout<<"\n2 : DEPARTMENT MANAGER ";
		cout<<"\n3 : ACCOUNTANT ";
		cout<<"\nPLEASE SELECT EMPLOYEE DESIGNATION : ";
		cin >>ds;
		if(ds>=3 && ds<=1){
			cout<<"\nSORRY INCORRECT CHOICE\n";
		}
	}while(ds <=1 && ds>=3);
	switch (ds){
	    case 1:
	    	system("cls");
	    	fp.open("salesperson.txt" , ios :: in);
	    	if(!fp){
		    	cout<<"\nPLEASE ENTER RECORD FIRST\n";
		    	getch();
		    	employee();
			}
	    	fp.read((char *) &sp , sizeof(sales_person));
	    	while(!fp.eof()){
	    		if(sp.retid() == id){
	    			sp.display();
				}
				fp.read((char *) &sp , sizeof(sales_person));
			}
			fp.close();
			cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
	    	cin >>exit;
	    	if(exit == 1){
	    		employee();
			}
	    	break;
	    case 2:
	    	system("cls");
	    	fp.open("deptmanager.txt.txt" , ios :: in);
	    	if(!fp){
		    	cout<<"\nPLEASE ENTER RECORD FIRST\n";
		    	getch();
		    	employee();
			}
	    	fp.read((char *) &dm , sizeof(dept_manager));
	    	while(!fp.eof()){
	    		if(dm.retid() == id){
	    			dm.display();
				}
				fp.read((char *) &dm , sizeof(dept_manager));
			}
			fp.close();
	    	cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
	    	cin >>exit;
	    	if(exit == 1){
	    		employee();
			}
	    	break;
	    case 3:
	    	system("cls");
	    	fp.open("accountant.txt.txt" , ios :: in);
	    	if(!fp){
		    	cout<<"\nPLEASE ENTER RECORD FIRST\n";
		    	getch();
		    	employee();
			}
	    	fp.read((char *) &acn , sizeof(accountant));
	    	while(!fp.eof()){
	    		if(acn.retid() == id){
	    			acn.display();
				}
				fp.read((char *) &acn , sizeof(accountant));
			}
			fp.close();
	    	cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
	    	cin >>exit;
	    	if(exit == 1){
	    		employee();
			}
	    	break;
	}
}
void viewemp()
{
	int ch;
	int exit;
	system("cls");
	cout<<"\n1 : VIEW EMPLOYEES BY DESIGNATION";
	cout<<"\n2 : VIEW EMPLOYEES BY DEPARTMENT";
	cout<<"\n3 : EXIT";
	cout<<"\nCHOICE : ";
	cin >>ch;
	switch(ch){
		case 1:
			system("cls");
			viewdes();
			cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
	    	cin >>exit;
	    	if(exit == 1){
	    		viewemp();
			}
			break;
		case 2:
			viewdep();
			system("cls");
			cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
	    	cin >>exit;
	    	if(exit == 1){
	    		viewemp();
			}
			break;
		case 3:
			employee();
			break;
	}
}
