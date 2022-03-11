//19k-1361 , 19k-0154 ,19k-0151
#include<iostream>
#include<ctime>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<conio.h>
using namespace std;
class billing;
class inventory{
	long long int isbn;
	char item_name[100];
	float weight;
	float price;
	int quantity;
	float discount;
	char updated_time[100];
	friend class billing;
	public:
		void getData()
		{
			int isbncount(long long int ib);
			do{
				cout<<"ENTER ISBN NUMBER: ";
			    cin >>isbn;
			    if(isbncount(isbn) != 13){
			    	cout<<"WRONG ISBN NUMBER PLEASE INPUT CORRECT\n";
				}
			}while(isbncount(isbn) != 13);			
			fflush(stdin);
			cout<<"ENTER NAME OF PRODUCT: ";
			gets(item_name);
			cout<<"ENTER WEIGHT: ";
		    cin >>weight;
			cout<<"ENTER QUANTITY: ";
			cin >>quantity;
			do{
				cout<<"ENTER PRICE: ";
			    cin >>price;
			}while(price < 0);
			do{
				cout<<"ENTER DISCOUNT: ";
			    cin>>discount;
			}while(discount < 0 && discount > 100);
			time_t now = time(0);
		    strcpy(updated_time,ctime(&now));
		}
		void show_stock()
		{
			cout<<"ISBN NUMBER: "<<isbn<<endl;
			cout<<"NAME OF PRODUCT: "<<item_name;
			cout<<"\nWEIGHT: "<<weight<<endl;
			cout<<"QUANTITY: "<<quantity<<endl;
			cout<<"PRICE: "<<price<<endl;
			cout<<"DISCOUNT: "<<discount<<endl;
			cout<<"LAST UPDATED: "<<updated_time<<endl;
			cout<<"----------------------------------------------------------------------------------------------\n\n";
		}
		void operator = (const inventory & in)
		{
			isbn = in.isbn;
			strcpy(item_name,in.item_name);
			weight = in.weight;
			price = in.price;
			quantity = in.quantity;
			discount = in.discount;
			time_t now = time(0);
		    strcpy(updated_time,ctime(&now));
		}
		friend int searchisbninv(long long int isbn);
		friend void updateprod();
};
inventory inv;
class billing 
    {
	int trans_no;
	char user_name[100];
	char trans_date[100];
	int size;
	float invoice;
	int cash;
	float change;
	int tdiscount;
	struct bill{
		char prod_name[100];
		long long isbn;
		int quant,kilo;
		float discount;
		float price,total;
	}b[1000];
	public:
		void getBill()
		{
			int searchisbninv(long long int isbn);
			int isbncount(long long int ib);
			int count();
			fstream fn,fp,ft;
			inventory in;
			char ch;
			int exit;
			system("cls");
			trans_no = count() + 1;
			fflush(stdin);
			cout<<"****************************************************RECIEPT NUMBER: "<<trans_no<<"***************************************************"<<endl;
			cout<<"ENTER USER NAME: ";
			gets(user_name);
			system("cls");
			invoice = 0,tdiscount = 0;
			int n=0;
			do{
				do{
					cout<<"Isbn: ";
				    cin >>b[n].isbn;
				    if( isbncount(b[n].isbn) != 13){
				    	cout<<"INCORRECT ISBN NUMBER \n";
				    }else if(searchisbninv(b[n].isbn) == 0){
				    	cout<<"\nISBN NOT MATCHED\n";
					}
				}while( isbncount(b[n].isbn) != 13 || searchisbninv(b[n].isbn) == 0 );
				
				cout<<"In kg's: ";
				cin >>b[n].kilo;
				cout<<"Quantity: ";
				cin >>b[n].quant;
				fp.open("inventory.txt", ios::in);
				fp.read((char *) &inv , sizeof(inventory));
				while(!fp.eof()){
					long long int isbn = inv.isbn;
					if(isbn == b[n].isbn){
					    strcpy(b[n].prod_name,inv.item_name);
						b[n].price = inv.price;
						b[n].discount = inv.discount;
					}
					fp.read((char *) & inv , sizeof(inventory));
				}
				fp.close();
				fn.open("inventory.txt" , ios :: in);
		    	ft.open("temp.txt" , ios :: app | ios :: out );
		        fn.seekg( 0 ,ios :: beg);
		    	while(fn.read((char *) &inv , sizeof(inventory))){
					if(inv.isbn != b[n].isbn){
						ft.write((char *) &inv , sizeof(inventory));
					}else{
						in = inv;
						in.quantity =inv.quantity - b[n].quant;
						ft.write((char *) &in , sizeof(inventory));
					}
				}
				fn.close();
				ft.close();
				remove("inventory.txt");
		        rename("temp.txt","inventory.txt");				
				b[n].total = ((100 - b[n].discount) / 100) * b[n].price;
				b[n].total *=b[n].quant;
				invoice += b[n].total;
				cout<<"Do you to enter more <y / n> ?";
				cin >>ch;
				if(ch == 'y'){
					n++;
				}else{
					size = n + 1;
					cout<<"\n\n\tTOTAL AMOUNT : "<<invoice;
				}
			}while(ch == 'y' || ch == 'Y');
		}
		void setun(char *un,long int rn)
		{
			strcpy(user_name,un);
			trans_no = rn;
		}
		void print_bill()
		{
			int i = 0;
			system("cls");
			cout<<"\n\n\tTOTAL AMOUNT : "<<invoice;
			cout<<"\n\n\tENTER CASH RECIEVED: ";
			cin >>cash;
			fflush(stdin);
			time_t now = time(0);
		    strcpy(trans_date,ctime(&now));
			change = cash - invoice;
			cout<<"\n\n\n\tCHANGE : "<<change;
			system("cls");
			cout<<"\nTRANSACTION NO. : "<<trans_no;
			cout<<"\nTRANSACTION DATE: "<<trans_date;
			cout<<"\nUSER NAME: "<<user_name;
			cout<<"\n\n-----------------------------------------------------------------------------------------------------------------------\n";
			cout<<"\t\t\t\t\t\t   ORIGINAL RECIEPT\n";
			cout<<"-----------------------------------------------------------------------------------------------------------------------\n";
			cout<<"PRODUCT NAME\t\t\tQUANTITY\t\tPRICE\t\tDISCOUNT\t\tTOTAL";
			cout<<"\n-----------------------------------------------------------------------------------------------------------------------\n";
			cout<<"\t\t\t\t\t\t   SALES ITEM";
			cout<<"\n-----------------------------------------------------------------------------------------------------------------------\n";
			for(i = 0;i<size;i++){
				cout<<"\n"<<b[i].prod_name<<"\t\t\t   "<<b[i].quant<<"\t\t\t   "<<b[i].price<<"\t\t     "<<b[i].discount<<"\t\t\t    "<<b[i].total;
			}
			cout<<"\nTOTAL ITEMS: "<<size<<endl;
			cout<<"\nDISCOUNT: "<<tdiscount<<endl;
			cout<<"\nINVOICE VALUE: "<<invoice<<endl;
			cout<<"\n-----------------------------------------------------------------------------------------------------------------------\n";
			cout<<"\t\t\t\t\t\tPAYMENTS";
			cout<<"\n-----------------------------------------------------------------------------------------------------------------------\n";
			cout<<"CASH : "<<cash<<endl;
			cout<<"\n-----------------------------------------------------------------------------------------------------------------------\n";
			cout<<"CHANGE DUE: "<<change<<endl;
			cout<<"\n-----------------------------------------------------------------------------------------------------------------------\n";
		}
		void deleteprod()
		{
			long long int isbn;
			int isbncount(long long int ib);
			char ch;
			int i,j;
			system("cls");
			do{
				do{
				    cout<<"ENTER ISBN NUMBER OF PRODUCT YOU WANT TO DELETE: ";
			        cin >>isbn;
			        if(isbncount(isbn) != 13){
			    	cout<<"WRONG ISBN NUMBER PLEASE INPUT CORRECT\n";
				}
			    }while(isbncount(isbn) != 13); 
				for(i = 0 ; i<size ; i++){
				    if(b[i].isbn == isbn){
				    	invoice -=b[i].total;
						for(j=i;j<size - 1 ; j++){
							b[j].isbn = b[j+1].isbn;
							b[j].price = b[j+1].price;
							strcpy(b[j].prod_name,b[j+1].prod_name);
							b[j].discount=b[j+1].discount;
							b[j].quant = b[j+1].quant;
							b[j].kilo = b[j+1].kilo;
							b[j].total = b[j+1].total;
						}
						i--;
						size--;
				    }
		        }
		        cout<<"\n\n\n\t\t\t\tINVOICE : "<<invoice;
			    cout<<"\n\nDO YOU WANT TO DELETE MORE ITEMS? <y / n> : ";
				cin >>ch;
			}while(ch == 'y' || ch == 'Y');
		}
		int transno()
		{
			return trans_no;
		}
		friend void sales();
};
billing bil;
class employee{
    int id;
	char name[100];
	int age;
	char phno[30];
	char gender[10];
	char email[30];
	char address[50];
	char deptname[30];
	public:
		employee(int i,char *na,int a,char *pn,char *g,char *em,char *addr,char *den)
		{
			id = i;
			strcpy(name,na);
			age = a;
			strcpy(phno,pn);
			strcpy(gender,g);
			strcpy(email,em);
			strcpy(address,addr);
			strcpy(deptname,den);
		}
		employee(){}
		void display()
        {
        	cout<<"\nEMPLOYEE'S ID : "<<id;
			cout<<"\nEMPLOYEE NAME : "<<name;
        	cout<<"\nEMPLOYEE'S DEPARTMENT NAME : "<<deptname;
        	cout<<"\nEMPLOYEE'S AGE : "<<age;
        	cout<<"\nEMPLOYEE'S GENDER : "<<gender;
        	cout<<"\nEMPLOYEE'S PHONE NUMBER : "<<phno;
        	cout<<"\nEMPLOYEE'S ADDRESS : "<<address;
        	cout<<"\nEMPLOYEE'S EMAIL ADDRESS : "<<email;
		}
		int retid()
		{
			return id;
		}
		void setdn(char * dn)
		{
			strcpy(deptname,dn);
		}
		void setem(char *em)
		{
			strcpy(email,em);
		}
		void setadr(char *addr)
		{
			strcpy(address,addr);
		}
		void setpn(char *pn)
		{
			strcpy(phno,pn);
		}
		char * deptn()
		{
			return deptname;
		}
};
class dept_manager : public employee{
	int hours;
	int salary;
	public:
		dept_manager(int i,char *na,int a,char *pn,char *g,char *em,char *addr,char *den,int hrs,int sal):employee(i,na,a,pn,g,em,addr,den),hours(hrs),salary(sal){}
        dept_manager(){}
        void display()
        {
        	employee::display();
			cout<<"\nHOURS WORKED  : "<<hours;
        	cout<<"\nEMPLOYEE'S SALARY : "<<salary;
		}
		void sethrs(int hrs)
		{
			hours = hrs;
		}
		void setsal(int sal)
		{
			salary = sal;
		}
};
class sales_person : public employee{
	int hours;
	int floor;
	int salary;
	public:
		sales_person(int i,char *na,int a,char *pn,char *g,char *em,char *addr,char *den,int hrs,int flr,int sal):employee(i,na,a,pn,g,em,addr,den),hours(hrs),salary(sal),floor(flr){}
        sales_person(){}
        void display()
        {
        	employee::display();
			cout<<"\nHOURS WORKED  : "<<hours;
			cout<<"\nDUTY ON FLOOR : "<<floor;
        	cout<<"\nEMPLOYEE'S SALARY : "<<salary;
		}
		void sethrs(int hrs)
		{
			hours = hrs;
		}
		void setsal(int sal)
		{
			salary = sal;
		}
		void setflr(int flr)
		{
			floor = flr;
		}
};
class accountant : public employee{
	int hours;
	int salary;
	public:
		accountant(int i,char *na,int a,char *pn,char *g,char *em,char *addr,char *den,int hrs,int sal):employee(i,na,a,pn,g,em,addr,den),hours(hrs),salary(sal){}
        accountant(){}
        void display()
        {
        	employee::display();
			cout<<"\nHOURS WORKED  : "<<hours;
        	cout<<"\nEMPLOYEE'S SALARY : "<<salary;
		}
		void sethrs(int hrs)
		{
			hours = hrs;
		}
		void setsal(int sal)
		{
			salary = sal;
		}
};
void bill_file(billing bl);
void enter_product();
int count();
void searchbills();
void display_prod();
void bill_file(billing bl)
{
	system("cls");
	fstream fp;
	fp.open("bills.txt", ios::out | ios::app);
	bl.print_bill();
	fp.write((char *) &bl , sizeof(billing));
	fp.close();
}
int searchisbninv(long long int isbn)
{
	int flag = 0;
	fstream fp;
	fp.open("inventory.txt" , ios::in);
	while(!fp.eof()){
		if(isbn == inv.isbn){
			flag = 1;
		}
		fp.read((char *) & inv , sizeof(inventory));
	}
	fp.close();
	return flag;
}
int count()
{
	int n=0;
	fstream fp;
	fp.open("bills.txt", ios :: in);
	while(fp.read((char *) & bil , sizeof(billing))){
		n++;
	}
	fp.close();
	return n;
}
void display_prod()
{
    void inventory1();
    fstream fp;
	cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("inventory.txt", ios:: in );
    if(!fp){
    	cout<<"\nENTER ITEMS IN INVENTORY FIRST\n";
    	getch();
    	inventory1();
	}
    while (fp.read((char * ) & inv, sizeof(inventory))) 
    {
		inv.show_stock();
	}
    fp.close();
}
int isbncount(long long int ib)
{
	int m,n=0;
	while(ib != 0){
		m = ib % 10;
		n++;
		ib/=10;
	}
	return n;
}
void updateprod()
{			
    void inventory1();
	long long int isbn;
	fstream fp,ft;
    inventory in;
	int cho,ch;
	do{
		cout<<"\nPLEASE ENTER ISBN NUMBER OF THE PRODUCT YOU WANT TO UPDATE : ";
	    cin >>isbn;
		if( isbncount(isbn) != 13){
	       	cout<<"INCORRECT ISBN NUMBER \n";
	    }else if(searchisbninv(isbn) == 0){
	    	cout<<"\nISBN NOT FOUND\n";
	    	cout<<"\n1 : CONTINUE ";
	    	cout<<"\n2 : EXIT ";
	    	cin >>ch;
    	    if(ch == 1){
    	    	updateprod();
			}else{
				inventory1();
			}
	    }
	}while( isbncount(isbn) != 13 || searchisbninv(isbn) == 0 );
	fp.open("inventory.txt" , ios :: in);
	ft.open("temp.txt" , ios :: app | ios :: out );
	fp.seekg( 0 ,ios :: beg);
	cout<<"\n1 : UPDATE QUANTITY";
	cout<<"\n2 : UPDATE PRICE";
	cout<<"\n3 : UPDATE DISCOUNT";
	cout<<"\nENTER YOUR CHOICE : ";
	cin >>cho;
	while(fp.read((char *) &inv , sizeof(inventory))){
		if(inv.isbn != isbn){
			ft.write((char *) &inv , sizeof(inventory));
		}else{
			if(cho == 1){
				in = inv;
				cout<<"\n\nENTER QUANTITY : ";
				cin >>in.quantity;
			}else if(cho == 2){
				in = inv;
				cout<<"\n\nENTER PRICE : ";
				cin >>in.price;
			}else if(cho == 3){
				in = inv;
				cout<<"\n\nENTER DISCOUNT : ";
				cin >>in.discount;
			}
			ft.write((char *) &in , sizeof(inventory));
		}
	}
	fp.close();
	ft.close();
	remove("inventory.txt");
	rename("temp.txt","inventory.txt");
}
void updateemp()
{			
    int id,ds,exit,sal,flr,hrs;
    sales_person sp;
	dept_manager dm;
	accountant acn;
	fstream fp,ft;
	char dn[30],pn[30],em[30],addr[50];
	int cho;
	char ch;
	do{
			cout<<"\nPLEASE ENTER EMPLOYEE ID : ";
		    cin >>id;
		do{
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
	        	cout<<"\n1 : UPDATE DEPARTMENT NAME ";
	        	cout<<"\n2 : UPDATE PHONE NUMBER";
				cout<<"\n3 : UPDATE ADDRESS";
				cout<<"\n4 : UPDATE EMAIL ADDRESS";
				cout<<"\n5 : UPDATE SALARY";
				cout<<"\n6 : UPDATE WORKING HOURS";
				cout<<"\n7 : UPDATE FLOOR OF DUTY";
				cout<<"PLEASE CHOOSE FROM MENU : ";
				cin >>cho;
				fflush(stdin);
		    	system("cls");
		    	fp.open("salesperson.txt" , ios :: in);
		    	if(!fp){
		    		cout<<"\nPLEASE ENTER RECORD FIRST\n";
		    		getch();
		    		employee();
				}
		    	ft.open("tempe.txt" , ios :: app | ios :: out );
		        fp.seekg( 0 ,ios :: beg);
		    	while(fp.read((char *) &sp , sizeof(sales_person))){
					if(sp.retid() != id){
						ft.write((char *) &sp , sizeof(sales_person));
					}else{
						switch(cho){
							case 1:
								cout<<"\nENTER DEPARTMENT NAME : ";
								gets(dn);
								sp.setdn(dn);
								break;
							case 2:
							    cout<<"\nENTER PHONE NUMBER : ";
								gets(pn);
								sp.setpn(pn);
								break;
							case 3:
								cout<<"\nENTER ADDRESS : ";
								gets(addr);
								sp.setadr(addr);
							    break;
							case 4:
								cout<<"\nENTER EMAIL ADDRESS : ";
								gets(em);
								sp.setem(em);
								break;
							case 5:
							    cout<<"\nENTER SALARY : ";
								cin >>sal;
								sp.setsal(sal);
								break;
							case 6:
								cout<<"\nENTER WORKING HOURS : ";
								cin >>hrs;
								sp.sethrs(hrs);
							    break;
							case 7:
								cout<<"\nENTER FLOOR : ";
								cin >>flr;
								sp.setflr(flr);
							    break;
						}
						ft.write((char *) &sp , sizeof(sales_person));
						cout<<"\nRECORD UPDATED SUCCESSFULLY !!!!!!\n";
					}
				}
				fp.close();
				ft.close();
				remove("salesperson.txt");
				rename("tempe.txt","salesperson.txt");
			    break;
		    case 2:
		    	cout<<"\n1 : UPDATE DEPARTMENT NAME ";
	        	cout<<"\n2 : UPDATE PHONE NUMBER";
				cout<<"\n3 : UPDATE ADDRESS";
				cout<<"\n4 : UPDATE EMAIL ADDRESS";
				cout<<"\n5 : UPDATE SALARY";
				cout<<"\n6 : UPDATE WORKING HOURS";
				cout<<"PLEASE CHOOSE FROM MENU : ";
				cin >>cho;
				fflush(stdin);
		    	system("cls");
		    	fp.open("deptmanager.txt" , ios :: in);
		    	if(!fp){
		    		cout<<"\nPLEASE ENTER RECORD FIRST\n";
		    		getch();
		    		employee();
				}
		    	ft.open("tempe.txt" , ios :: app | ios :: out );
		        fp.seekg( 0 ,ios :: beg);
		    	while(fp.read((char *) &dm , sizeof(dept_manager))){
					if(dm.retid() != id){
						ft.write((char *) &dm , sizeof(dept_manager));
					}else{
						switch(cho){
							case 1:
								cout<<"\nENTER DEPARTMENT NAME : ";
								gets(dn);
								dm.setdn(dn);
								break;
							case 2:
							    cout<<"\nENTER PHONE NUMBER : ";
								gets(pn);
								dm.setpn(pn);
								break;
							case 3:
								cout<<"\nENTER ADDRESS : ";
								gets(addr);
								dm.setadr(addr);
							    break;
							case 4:
								cout<<"\nENTER EMAIL ADDRESS : ";
								gets(em);
								dm.setem(em);
								break;
							case 5:
							    cout<<"\nENTER SALARY : ";
								cin >>sal;
								dm.setsal(sal);
								break;
							case 6:
								cout<<"\nENTER WORKING HOURS : ";
								cin >>hrs;
								dm.sethrs(hrs);
							    break;
						}
						ft.write((char *) &dm , sizeof(dept_manager));
						cout<<"\nRECORD UPDATED SUCCESSFULLY !!!!!!\n";
					}
				}
				fp.close();
				ft.close();
				remove("deptmanager.txt");
				rename("tempe.txt","deptmanager.txt");
	   	  	    break;
			case 3:
			    cout<<"\n1 : UPDATE DEPARTMENT NAME ";
	        	cout<<"\n2 : UPDATE PHONE NUMBER";
				cout<<"\n3 : UPDATE ADDRESS";
				cout<<"\n4 : UPDATE EMAIL ADDRESS";
				cout<<"\n5 : UPDATE SALARY";
				cout<<"\n6 : UPDATE WORKING HOURS";
				cout<<"PLEASE CHOOSE FROM MENU : ";
				cin >>cho;
				fflush(stdin);
		    	system("cls");
		    	fp.open("accountant.txt" , ios :: in);
		    	if(!fp){
		    		cout<<"\nPLEASE ENTER RECORD FIRST\n";
		    		getch();
		    		employee();
				}
		    	ft.open("tempe.txt" , ios :: app | ios :: out );
		        fp.seekg( 0 ,ios :: beg);
		    	while(fp.read((char *) &acn , sizeof(accountant))){
					if(acn.retid() != id){
						ft.write((char *) &acn , sizeof(accountant));
					}else{
						switch(cho){
							case 1:
								cout<<"\nENTER DEPARTMENT NAME : ";
								gets(dn);
								acn.setdn(dn);
								break;
							case 2:
							    cout<<"\nENTER PHONE NUMBER : ";
								gets(pn);
								acn.setpn(pn);
								break;
							case 3:
								cout<<"\nENTER ADDRESS : ";
								gets(addr);
								acn.setadr(addr);
							    break;
							case 4:
								cout<<"\nENTER EMAIL ADDRESS : ";
								gets(em);
								acn.setem(em);
								break;
							case 5:
							    cout<<"\nENTER SALARY : ";
								cin >>sal;
								acn.setsal(sal);
								break;
							case 6:
								cout<<"\nENTER WORKING HOURS : ";
								cin >>hrs;
								acn.sethrs(hrs);
							    break;
						}
						ft.write((char *) &acn , sizeof(accountant));
						cout<<"\nRECORD UPDATED SUCCESSFULLY !!!!!!\n";
					}
				}
				fp.close();
				ft.close();
				remove("accountant.txt");
				rename("tempe.txt","accountant.txt");	
		    	break;
		    case 4:
		    	cout<<"\n\n\t\t\t\tWRONG CHOICE ";
		    	break;
	    }
	    cout<<"DO YOU WANT TO UPDATE MORE ACCOUNTS <y/n> ? ";
	    cin >>ch;
    }while(ch == 'y' || ch == 'Y');
}
void deleteemp()
{
	int id,ds;
	sales_person sp;
	dept_manager dm;
	accountant acn;
	fstream fp,ft;
	system("cls");
	cout<<"\nPLEASE ENTER EMPLOYEE ID : ";
	cin >>id;
	do{
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
		    fp.open("salesperson.txt" , ios :: in);
		    if(!fp){
		    	cout<<"\nPLEASE ENTER RECORD FIRST\n";
		    	getch();
		    	employee();
			}
		    ft.open("tempe.txt" , ios :: app | ios :: out );
		    fp.seekg( 0 ,ios :: beg);
		    while(fp.read((char *) &sp , sizeof(sales_person))){
			    if(sp.retid() != id){
					ft.write((char *) &sp , sizeof(sales_person));
				}
			}
			fp.close();
			ft.close();
			remove("salesperson.txt");
			rename("tempe.txt","salesperson.txt");
			cout<<"\n\t\t\tRECORD DELETED SUCCESSFULLY\n";
			break;
		case 2:
            fp.open("deptmanager.txt" , ios :: in);
            if(!fp){
		    	cout<<"\nPLEASE ENTER RECORD FIRST\n";
		    	getch();
		    	employee();
			}
		    ft.open("tempe.txt" , ios :: app | ios :: out );
		    fp.seekg( 0 ,ios :: beg);
		    while(fp.read((char *) &dm , sizeof(dept_manager))){
				if(dm.retid() != id){
					ft.write((char *) &dm , sizeof(dept_manager));
				}
			}
			fp.close();
			ft.close();
			remove("deptmanager.txt");
			rename("tempe.txt","deptmanager.txt");
			cout<<"\n\t\t\tRECORD DELETED SUCCESSFULLY\n";
	   	  	break;
		case 3:
		    fp.open("accountant.txt" , ios :: in);
		    if(!fp){
		    	cout<<"\nPLEASE ENTER RECORD FIRST\n";
		    	getch();
		    	employee();
			}
		    ft.open("tempe.txt" , ios :: app | ios :: out );
		    fp.seekg( 0 ,ios :: beg);
		    while(fp.read((char *) &acn , sizeof(accountant))){
				if(acn.retid() != id){
					ft.write((char *) &acn , sizeof(accountant));
				}
			}
			fp.close();
			ft.close();
			remove("accountant.txt");
			rename("tempe.txt","accountant.txt");	
			cout<<"\n\t\t\tRECORD DELETED SUCCESSFULLY\n";
		    break;
		case 4:
			cout<<"\n\n\t\t\t\tWRONG CHOICE ";
			break;
	}
}
int countemp()
{
	int n = 0;
	fstream fp;
	sales_person sp;
	dept_manager dm;
	accountant acn;
	fp.open("salesperson.txt" , ios :: in);
	while(fp.read((char *) &sp , sizeof(sales_person))){
		n++;
	}
	fp.close();
	fp.open("deptmanager.txt" , ios :: in);
	while(fp.read((char *) &dm , sizeof(dept_manager))){
		n++;
	}
	fp.close();
	fp.open("accountant.txt" , ios :: in);
	while(fp.read((char *) &acn , sizeof(accountant))){
		n++;
	}
	fp.close();
	return n+1;
}
void viewdes()
{
	sales_person sp;
	fstream fp;
	dept_manager dm;
	accountant acn;
	void viewemp();
	system("cls");
	int ch,exit;
	cout<<"\n1 : SALES PERSON";
	cout<<"\n2 : DEPARTMENT MANAGER";
	cout<<"\n3 : ACCOUNTANT";
	cout<<"\n4 : EXIT";
	cout<<"\nCHOICE : ";
	cin >>ch;
	fflush(stdin);
	switch(ch){
		case 1:
			system("cls");
			fp.open("salesperson.txt" , ios :: in);
			if(!fp){
				cout<<"\nNO RECORD FOUND\n";
				getch();
				viewdes();
			}
			while(fp.read((char *) &sp , sizeof(sales_person))){
				sp.display();
				cout<<"\n----------------------------------------------------------------------------------------------------------\n";
			}
			fp.close();
			cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
	    	cin >>exit;
	    	if(exit == 1){
	    		viewdes();
			}
			break;
		case 2:
			system("cls");
			fp.open("deptmanager.txt" , ios :: in);
			if(!fp){
				cout<<"\nNO RECORD FOUND\n";
				getch();
				viewdes();
			}
			while(fp.read((char *) &dm , sizeof(dept_manager))){
				dm.display();
				cout<<"\n----------------------------------------------------------------------------------------------------------\n";
			}
			fp.close();
			cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
	    	cin >>exit;
	    	if(exit == 1){
	    		viewdes();
			}
			break;
		case 3:
			system("cls");
			fp.open("accountant.txt" , ios :: in);
			if(!fp){
				cout<<"\nNO RECORD FOUND\n";
				getch();
				viewdes();
			}
			while(fp.read((char *) &acn , sizeof(accountant))){
				acn.display();
				cout<<"\n----------------------------------------------------------------------------------------------------------\n";
			}
			fp.close();
			cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
	    	cin >>exit;
	    	if(exit == 1){
	    		viewdes();
			}
			break;
		case 4:
			viewemp();
			break;
	}
}
void viewdep()
{
	char dn[30];
	int ch,exit;
	void viewemp();
	sales_person sp;
	dept_manager dm;
	accountant acn;
	fstream fp1,fp2,fp3;
	system("cls");
	cout<<"\n1 : GROCERY";
	cout<<"\n2 : CROCKERY";
	cout<<"\n3 : GARMENTS";
	cout<<"\n4 : EXIT";
	cout<<"\nCHOICE : ";
	cin >>ch;
	switch(ch){
		case 1:
			system("cls");
			fp1.open("deptmanager.txt" , ios :: in);
			while(fp1.read((char *) &dm , sizeof(dept_manager))){
				if(strcmp(dm.deptn(),"grocery") == 0){
					dm.display();
				    cout<<"\n----------------------------------------------------------------------------------------------------------\n";
				}
			}
			fp1.close();
			fp2.open("accountant.txt" , ios :: in);
			while(fp2.read((char *) &acn , sizeof(accountant))){
				if(strcmp(acn.deptn(),"grocery") == 0){
					acn.display();
					cout<<"\n----------------------------------------------------------------------------------------------------------\n";
			    }
			}
			fp2.close();
			fp3.open("salesperson.txt" , ios :: in);
			while(fp3.read((char *) &sp , sizeof(sales_person))){
				if(strcmp(sp.deptn(),"grocery") == 0){
					sp.display();
				    cout<<"\n----------------------------------------------------------------------------------------------------------\n";
				}
			}
			fp3.close();
			cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
	    	cin >>exit;
	    	if(exit == 1){
	    		viewdep();
			}
			break;
		case 2:
			system("cls");
			fp1.open("deptmanager.txt" , ios :: in);
			while(fp1.read((char *) &dm , sizeof(dept_manager))){
				if(strcmp(dm.deptn(),"crockery") == 0){
					dm.display();
				    cout<<"\n----------------------------------------------------------------------------------------------------------\n";
				}
			}
			fp1.close();
			fp2.open("accountant.txt" , ios :: in);
			while(fp2.read((char *) &acn , sizeof(accountant))){
				if(strcmp(acn.deptn(),"crockery") == 0){
					acn.display();
					cout<<"\n----------------------------------------------------------------------------------------------------------\n";
			    }
			}
			fp2.close();
			fp3.open("salesperson.txt" , ios :: in);
			while(fp3.read((char *) &sp , sizeof(sales_person))){
				if(strcmp(sp.deptn(),"crockery") == 0){
					sp.display();
				    cout<<"\n----------------------------------------------------------------------------------------------------------\n";
				}
			}
			fp3.close();
			cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
	    	cin >>exit;
	    	if(exit == 1){
	    		viewdep();
			}
			break;
		case 3:
			system("cls");
			fp1.open("deptmanager.txt" , ios :: in);
			while(fp1.read((char *) &dm , sizeof(dept_manager))){
				if(strcmp(dm.deptn(),"garmnets") == 0){
					dm.display();
				    cout<<"\n----------------------------------------------------------------------------------------------------------\n";
				}
			}
			fp1.close();
			fp2.open("accountant.txt" , ios :: in);
			while(fp2.read((char *) &acn , sizeof(accountant))){
				if(strcmp(acn.deptn(),"garments") == 0){
					acn.display();
					cout<<"\n----------------------------------------------------------------------------------------------------------\n";
			    }
			}
			fp2.close();
			fp3.open("salesperson.txt" , ios :: in);
			while(fp3.read((char *) &sp , sizeof(sales_person))){
				if(strcmp(sp.deptn(),"garments") == 0){
					sp.display();
				    cout<<"\n----------------------------------------------------------------------------------------------------------\n";
				}
			}
			fp3.close();
			cout<<"\n\n\n\t\t\t\t\t1 : EXIT ";
	    	cin >>exit;
	    	if(exit == 1){
	    		viewdep();
			}
			break;
		case 4:
			viewemp();
			break;
	}
}
void searchbills()
{
    int tn;
    void adminportal();
    fstream fp;
    system("cls");
    cout<<"\n\n\tENTER TRANSACTION NUMBER : ";
    cin >>tn;
    fp.open("bills.txt" , ios :: in);
    if(!fp){
    	cout<<"\n\tSORRY NO BILLS FOUND";
    	getch();
    	adminportal();
	}
    fp.read((char *) &bil , sizeof(billing));
    while(!fp.eof()){
    	if(bil.transno() == tn){
    		bil.print_bill();
		}
		fp.read((char *) &bil , sizeof(billing));
	}
}
struct data{
	long long int isbn;
	char name[100];
	int quan;
	float total;
};
void sales()
{
	int i,n=0;
	void adminportal();
    struct data s[1000],temp;
    fstream fp;
	fp.open("bills.txt" , ios :: in);
	if(!fp){
		cout<<"\nNO BILLS FOUND\n";
		getch();
		adminportal();
	}
	int k = 0;
	while(fp.read((char *) &bil , sizeof(billing))){
		for(i=0 ; i<bil.size ; i++){
			int j = 0;
			int flag = 0;
			if(n>0){
				do{
				    if(s[j].isbn == bil.b[i].isbn){
					    flag = 1;
					    break;				
				    }
				    j++;
			    }while(flag == 0 &&  j < n);
			}
			if(flag == 0){
				s[n].isbn = bil.b[i].isbn;
			    strcpy(s[n].name,bil.b[i].prod_name);
			    s[n].quan = bil.b[i].quant;
				s[n].total = bil.b[i].total;
				n++;
		    }else{
				s[j-1].quan += bil.b[i].quant;
				s[j-1].total += bil.b[i].total;
			}
		}
	}
	fp.close();
	for(i=0 ; i<n ;i++){
		for(int j=i+1 ; j<n ; j++){
			if(s[i].quan < s[j].quan){
				temp.isbn = s[i].isbn;
				temp.quan = s[i].quan;
				strcpy(temp.name,s[i].name);
				temp.total = s[i].total;
				s[i].isbn = s[j].isbn;
				s[i].quan = s[j].quan;
				strcpy(s[i].name,s[j].name);
				s[i].total = s[j].total;
				s[j].isbn = temp.isbn;
				s[j].quan = temp.quan;
				strcpy(s[j].name,temp.name);
				s[j].total = temp.total;
			}
		}
	}
	system("cls");
	for(i = 0 ;i < n ; i++){
		cout<<"\nISBN : "<<s[i].isbn;
		cout<<"\nPRODUCT NAME : "<<s[i].name;
		cout<<"\nQUANTITY : "<<s[i].quan;
		cout<<"\nTOTAL : "<<s[i].total;
		cout<<"\n---------------------------------------------------------------------------------------------------\n";
	}
}
