#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>
#include<string.h>

class product
{
int pno;
char name[50];
char brand[50];
float price,qty,tax,dis;
public:
          void create_product()
{
  cout <<"Please Enter the Product Number"<<endl;
  cin>>pno;
 cout<<"Please Enter the brand of the item"<<endl;
  gets(brand);
 cout<<"PLease Enter the description of the item"<<endl;
gets(name);
 cout<<"Please Enter the Price of the item"<<endl;
cin>>price;
cout<<"Please Enter the discount (%)"<<endl;
cin>>dis;
}
 
void show_product()
{
 cout<<"Product no. Of the product :"<<pno<<endl;

cout<<"Brand of the product is:"; 
puts(brand);
cout<<endl;

cout<<"Price Of the product is :"<<price<<endl;

cout<<"Discount:"<<dis<<endl;
}

int  retpno()
{return pno;}

float retprice()
{return price;}

char * retname()
{return name;}

char * retbrand()
{return brand;}

int retdis()
{return dis;}

};

fstream file;
product prod;
void write_product()
{ 
     file.open("Stationery.dat",ios::app| ios::binary);
     prod.create_product();
file.write((char*)&prod,sizeof(product));
file.close();
cout<<endl;
cout<<"The product has been created.";
}

void display_all()
{
   cout<<"ALL RECORDS";
   cout<<endl<<endl;
file.open("Stationery.dat",ios::in|ios::binary);
while(file.read((char*)&prod,sizeof(product)))
{
  prod.show_product();
  cout<<endl<<"-------------"<<endl; 
 getch();
}
file.close();
getch();
}

void display_sp(int n)
{
     int flag=0;
     file.open("Stationery.dat",ios::in|ios::binary);
     while(file.read((char*)&prod,sizeof(product)))
{
 if(prod.retpno()==n)
      {
        prod.show_product();
        flag=1;
      }
}
if(flag==0)
cout<"\n\nrecord not exist";

file.close();
}


void modify_product()
{
              int no,found=0;
              cout<<"\n\n\tPlease enter the product No. of the Product";
              cin>>no;
				  file.open("Stationery.dat",ios::in|ios::out|ios::binary);
      while(file.read((char*)&prod,sizeof(product)) && found==0)
                {
                  if(prod.retpno()==no)
                           { 
                              prod.show_product();
                               cout<<"\nPlease Enter the New Details of product"<<endl;
                               prod.create_product();
                                int pos=-1*sizeof(prod);
                                file.seekp(pos,ios::cur);
                                file.write((char*)&prod,sizeof(product));
                               cout<<"\n\n\t Record Updated";
                               found=1;
                       }
} 
if(found==0)
cout<<"\n\n  Record Not Found";

 file.close();

}

void delete_product()
        {
    
           int no;
           cout<<"\n\n\n\t Delete Record";
           cout<<"\n\n Please Enter the Product no. Of the Product you want to Delete";
           cin>>no;
           file.open("Stationery.dat",ios::in|ios::out|ios::binary);
           fstream fp2;
           fp2.open("Temp.dat",ios::out|ios::binary);
           file.seekg(0,ios::beg);
           while(file.read((char*)&prod,sizeof(product)));
                 {
                    if(prod.retpno()!=no)
                          { 
                              fp2.write((char*)&prod,sizeof(product));
                           }
                 }             
           fp2.close();
           file.close();
           remove("Stationery.dat");
           rename("Temp.dat", "Stationery.dat");
           cout<<"\n\n\t Record Deleted..";
       }


   void menu()
{
  file.open("Stationery.dat",ios::in|ios::binary);
  if(!file)
{ 
   cout<<"ERROR!!!!! FILE COULD NOT BE OPEN \n\n\n GO TO ADMIN MENU TO CREATE FILE";
   cout<<"\n\n\n Program is Closing..........";
   getch();
   exit(0); 
}

cout<<"\n\n\t\t Product MENU \n\n";
cout<<"---------------------------------------------------\n";
cout<<"P.NO.\t\t NAME \t\t BRAND \t\t PRICE \n";
cout<<"-----------------------------------------------------\n";

           while(file.read((char*)&prod,sizeof(product)))
{

 cout<<prod.retpno()<<"\t\t"<<prod.retname()<<"\t\t"<<prod.retbrand()<<"\t\t"<<prod.retprice()<<
 endl;
  }
          file.close();}
void place_order()
{
                      int order_arr[50],quan[50],c=0;
                     float amt,amt1,total=0;
                    char ch;
                    menu();
						  cout<<"\n----------------------------------------------------";
                    cout<<"\n            PLACE YOUR ORDER";
						  cout<<"\n----------------------------------------------------";
 
                   do 
                     { 
                         cout<<"\nEnter the Product No."<<endl;
                         cin>>order_arr[c];
                         cout<<endl;
 
                        cout<<"Quantity:";
                        cin>>quan[c];
                        cout<<endl;

							  c++;

                     cout<<"Do You Wish To Order Another Product?(y/n)";
                     cin>>ch;
						 }while((ch=='y')||(ch=='Y'));

                   cout<<"\n\n Thank You For Placing The Order."<<endl;
                   cout<<"**********************************INVOICE***********************************************\n";
cout<<"\nPrNo\tPrName\tQuantity\tCOST\tAmount\tDISCOUNT\n";

for(int x=0;x<=c;x++)
{
                   file.open("Stationery.dat",ios::in|ios::binary);
                   file.read((char*)&prod,sizeof(product));
                   while(!file.eof())
                                {
                                    if(prod.retpno()==order_arr[x])
                                                  { 
                                                    amt=prod.retprice()*quan[x];
                                                     amt1=amt-(amt*prod.retdis()/100);

cout<<order_arr[x]<<"\t"<<prod.retname()<<"\t\t"<<quan[x]<<"\t\t"<<prod.retprice()<<"\t"<<amt
<<"\t"<<amt1<<endl;
 
                                      total+=amt1;
                                                    }
                                     file.read((char*)&prod,sizeof(product));
                                  }
                 file.close();
              }
                               cout<<"TOTAL ="<<total<<endl<<endl;
           getch();
}


void admin_menu()
{
   char ch,c;

    do
     { 
		  cout<<"ADMIN MENU"<<endl;
		  cout<<"1.CREATE PRODUCT"<<endl;
		  cout<<"2.DISPLAY ALL PRODUCTS"<<endl;
		  cout<<"3.QUERY"<<endl;
		  cout<<"4.MODIFY PRODUCT"<<endl;
		  cout<<"5.DELETE PRODUCT"<<endl;
		  cout<<"6.VIEW PRODUCT MENU"<<endl;
		  cout<<"7.EXIT"<<endl;
 
        cout<<"Enter your option";
        cin>>ch;

        switch(ch)
                  {
                              case '1' :      write_product();
                                                    break;

                              case '2' :      display_all();
                                                    break;

                              case '3' :    {
                                                     int num;
                                                             cout<<"\n\nPlease Enter the Product No.";
                                                             cin>>num;
                                                             display_sp(num);
                                                 }  
                                                     break;
     

                              case '4' :      modify_product();
                                                    break;      

                              case '5' :      delete_product();
                                                    break;

                              case '6' :      menu();
                                                    break;

										case '7' :      cout<<"PROGRAM TERMINATED";
															 exit(0);
                                                  
                               default : cout<<"Please Enter your Choice b/w (1-7)";
                }
          cout<<"Do you wish to continue?:";
          cin>>c;
      } 
           while((c=='y')||(c=='Y'));

}

int main()
{
     char ch,c,pass[30];

     do
             {
                 cout<<"MAIN MENU"<<endl<<endl;
                 cout<<"1.CUSTOMER"<<endl;
                 cout<<"2.ADMINISTRATOR"<<endl;
               cout<<"3.EXIT"<<endl<<endl;
 
               cout<<"Enter your option : ";
               cin>>ch;


            switch(ch)
              {
                           case '1' :   {
                                                     place_order();
                                                     getch();
                                             }
                                                     break;

                           case '2' : {  
                                                cout<<"Please Enter The Password :";
                                                             gets(pass);
                                                             if(strcmp("stationery",pass)==0)
                                                             admin_menu();
                                                             cout<<endl;
                                            }
                                                           break;
   
		case'3' :cout<<"PROGRAM TERMINATED";
				exit(0);

	           default : cout<<"Please Select your Option b/w (1-3)";
               }


       cout<<"Do you wish to continue";
       cin>>c;
    }
   while((c=='y')||(c=='Y'));
  
   return 0;}
