#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

class Date{
	private:
		int dd;
		int mm;
		int yy;
		void rectifyDate(){
			if(dd > 30)
			{
				dd -= 30;
				mm++;
			}
			if (mm > 12)
			{
				mm -= 12;
				yy++;
				
			}
			}
		
		public:
			Date(){
				dd = 1;
				mm = 1;
				yy = 2024;
				
			}
			void setDate(){
				cout<<"enter date: ";
				cin>>dd;
				cout<<"enter month: ";
				cin>>mm;
				cout<<"enter year: ";
				cin>>yy;
				
			}
			
			void setDate(Date temp)
			{
				dd = temp.dd + 15;
				mm = temp.mm;
				yy = temp.yy;
				rectifyDate();
			
			}
			void showDate(){
				cout<<dd<<"/"<<mm<<"/"<<yy;
				
			}
};

class Menu{
	private:
		public:
			void mainMenu();
			void studentMenu();
			void bookMenu();
			void issueBook();
			void returnBook();
			
};

  void Menu::mainMenu(){
  	cout<<"########## MAIN MENU ##########"<<endl<<endl;
  	cout<<"1. STUDENT MENU\n 2. BOOK MENU\n3. ISSUE BOOK\n4. RETURN BOOK\n";
  	cout<<"5. EXIT"<<endl;
  }
  
  void Menu::studentMenu(){
  	cout<<"########## STUDENT MENU ##########"<<endl<<endl;
  	cout<<"1. NEW ENTRY\n2. MODIFY ENTRY\n 3.SEARCH ENTRY\n 4.DELETE ENTRY"<<endl;
  	cout<<"5. VIEW STUDENT DETAILS\n6. GO BACK TO PREVIOUS MENU"<<endl;
  }
  
  void Menu::bookMenu(){
  	cout<<"########## BOOK MENU ##########"<<endl<<endl;
  	cout<<"1. NEW ENTRY\n 2. MODIFY ENTRY\n 3. SEARCH ENTRY\n 4.DELETE ENTRY "<<endl;
  	cout<<"5. VIEW ALL BOOKS DETAIL\n6. GO BACK TO PREVIOUS MENU"<<endl;
  	
  }
  class BookData
  {
  	public:
  		char title[30];
  		char author[30];
  		char publisher[30];
  		int status;
  		float price;
  		int issuedRollNo;
  		Date issuedDate;
  		Date returnDate;
  		BookData(){
  			status = 0;
  			issuedRollNo = -9999;
  			
		  }
  		
  };
  
  class studentData
  {
  	public:
  		int rollNo;
  		char name[30];
  		char address[50];
  		char branch[5];
  		int status;
  		char booktitle[30];
  		StudentData(){
  			status = 0;
  			
		  }
  	
  };
  
  class Book{
  	public:
  		void inputDetails();
  		void modifyDetails();
  		void searchDetails();
  		void deleteDetails();
  		void viewAllBookDetail();
  		
  };
  
  void Book::inputDetails(){
  	fstream ofp;
  	ofp.open("bookDatabase.dat",ios :: out | ios:: binary | ios :: app);
  	
  	if(!ofp){
  		cout<<"UNABLE TO OPEN FILE"<<endl;
  		return;
  		
	  }
  
  
   BookData book;
   cout<<"ENTER THE BOOK TITLE: ";
   	cin>>book.title;
   	cout<<"ENTER AUTHOR'S NAME: ";
   	cin>>book.author;
   	cout<<"ENTER BOOK PUBLISHER: ";
   	cin>>book.publisher;
   	cout<<"ENTER BOOK PRICE: ";
   	cin>>book.price;
   	
   	
   	ofp.write((char*)&book,sizeof(BookData));
   	ofp.close();
   }
   
   void Book::modifyDetails(){
   	fstream file;
   	file.open("bookDatabase.dat", ios :: binary | ios :: in | ios :: out | ios :: ate);
   	
   	if(!file){
   		cout<<"UNABLE TO OPEN FILE"<<endl;
   		return;
	   }
	 
	file.seekg(0, ios :: beg);
	
	BookData book;
	char title[25];
	
	cout<<"ENTER THE TITLE OF THE BOOK YOU WANT TO MODIFY: ";
	cin>>title;
	
	while(file.read((char*)&book, sizeof(BookData))){
		if(strcmp(book.title, title) == 0)
        {
        	int position = (-1)*sizeof(BookData);
        	file.seekp(position, ios :: cur);
        	
        	cout<<"ENTER NEW BOOK TITLE: ";
        	cin>>book.title;
        	cout<<"ENTER NEW AUTHOR'S NAME: ";
        	cin>>book.author;
        	cout<<"ENTER NEW BOOK PUBLISHER: ";
        	cin>>book.publisher;
        	cout<<"ENTER NEW BOOK PRICE: ";
        	cin>>book.price;
        	
        	cout<<"RECORD UPDATED";
        	cin.get();
        	cin.get();
        	return;
        	
				}		
	}   
	cout<<"BOOK NOT FOUND";
	cin.get();
	cin.get();
	return;
   }
   
   void Book :: searchDetails()
   {
   	fstream file;
   	file.open("bookDatabase.dat", ios :: in | ios :: binary);
   	
   	if (!file)
   	{
   		cout<<"UNABLE TO OPEN THE FILE"<<endl;
   		cin.get();
   		cin.get();
   		return;
   		
   	 }
   	 
   	 BookData book;
   	 char title[30];
   	 
   	 cout<<"ENTER THE NAME OF THE BOOK YOU WANT TO MODIFY: ";
   	 cin>>title;
   	 while(file.read((char*)&book, sizeof(BookData)))
   	 {
   	 	if (strcmp(book.title, title) == 0){
   	 		cout<<"BOOK TITLE: "<<book.title<<endl;
			cout<<"BOOK AUTHOR: "<<book.author<<endl;
			cout<<"BOOK PUBLISHER: "<<book.publisher<<endl;
			cout<<"BOOK PRICE: "<<book.price<<endl;
			 if(book.status == 1)
			 {
			 	cout<<"ISSUED STATUS: "<<book.issuedRollNo<<endl;
			 	cout<<"ISSUED DATE: ";
			 	book.issuedDate.showDate();
			 	cout<<endl<<"RETURN DATE: ";
			 	book.returnDate.showDate();
			 	cout<<endl;
				  }	 
				  else
				  {
				  	cout<<"ISSUED STATUS: NONE"<<endl;
				  }
				  cin.get();
				  cin.get();
				  return;
				  }
			}
			
			cout<<"BOOK NOT FOUND"<<endl;
			cin.get();
			cin.get();
			return;
		}
   void Book :: deleteDetails()
   {
   	fstream file,temp;
   	file.open("bookDatabase.dat", ios :: binary | ios :: in);
   	temp.open("temp.dat", ios :: binary | ios :: out);
   	
   	char title[25];
   	BookData book;
   	int flag = 0;
   	
   	cout<<"ENTER THE BOOK TITLE TO REMOVE: ";
   	cin>>title;
   	
   	while(file.read((char*)&book,sizeof(BookData)))
   	{
   		if (strcmp(book.title, title) == 0){
   			flag++;
   			continue;
		   }
	     temp.write((char*)&book,sizeof(BookData));	   
	   }
   	
   	file.close();
   	temp.close();
   	remove("bookDatabase.dat");
   	rename("temp.dat","bookDatabase.dat");
   	
   	if (flag == 1)
   	cout<<"RECORD DELETED"<<endl;
   	else
   	cout<<"RECORD NOT FOUND"<<endl;
   	cin.get();
   	cin.get();
   	return;
   	}
   	
   	void Book::viewAllBookDetail()
{
	fstream file;
	file.open("bookDatabase.dat" , ios :: binary | ios :: in);
	
	BookData book;
	int choice = 1;
	
	while(file.read((char*)&book,sizeof(BookData)) && choice)
	{
		system("clear");
		cout<<"BOOK TITLE: "<<book.title<<endl;
		cout<<"BOOK PUBLISHER: "<<book.publisher<<endl;
		cout<<"BOOK AUTHOR: "<<book.author<<endl;
		cout<<"BOOK PUBLISHER:"<<book.price<<endl;
		if(book.status == 1)
		{
			cout<<"ISSUED STATUS: "<<book.issuedRollNo<<endl;
			cout<<"ISSUED DATE: ";
			book.issuedDate.showDate();
			cout<<endl<<"RETUEN DATE: ";
			book.returnDate.showDate();
			
		}
		else
		{
			cout<<"ISSUED STATUS : NONE"<<endl;
			
		}
		
		cout<<"Press 1 to view the next book else press 0";
		cin>>choice;
		
	}
	cin.get();
	cin.get();
	return;
	
   }
   
   class Student
   {
   	public:
   		void inputDetails();
   		void modifyDetails();
   		void searchDetails();
   		void deleteDetails();
   		void viewAllStudentDetail();
	  };
	  
	  void Student::inputDetails(){
	  	fstream ofp;//output file pointr
	  	ofp.open("studentDatabase.dat", ios :: out | ios :: app | ios :: binary);
	  	
	  	if(!ofp)
	  	{
	  		cout<<"UNABLE TO OPEN THE FILE"<<endl;
	  		return;
		  }
		  
	    
		
		StudentData student;
	     cout<<"ENTER THE STUDENT'S ROLL NUMBER: ";
	     cin>>student.rollNo;
	     cout<<"ENTER THE STUDENT'S NAME: ";
	     cin>>student.name;
	     cout<<"ENTER STUDENT'S ADDRESS: ";
	     cin>>student.address;
	     cout<<"ENTER STUDENT'S BRANCH: ";
	     cin>>student.branch;
	     
	     cout<<"RECORD ADDED TO DATABASE";
	     
	     ofp.write((char*)&student, sizeof(StudentData));
	     ofp.close();
	  
	  }
	    
	  void Student :: modifyDetails(){
	  	fstream fp;
	  	fp.open("studentDatabase.dat",ios :: binary | ios :: in | ios :: out | ios :: ate);
	  	
	  	if(!fp)
	  	{
	  		cerr<<"UNABLE TO OPEN THE FILE"<<endl;
	  		return;
		  }
		  
		  fp.seekg(0,ios :: beg);
		  int target;
		  cout<<"ENRTER THE STUDENT'S ROLL NUMBER TO MODIFY: ";
		  cin>>target;
		  
		  StudentData student;
		  
		  while (fp.read((char*)&student,sizeof(student)))
		  {
		  	if (target == student.rollNo){
		  		int position = (-1) * sizeof(StudentData);
		  		fp.seekp(position, ios :: cur);
		  		
		  		cout<<"ENTER THE STUDENT'S NEW ROLL NO: ";
		  		cin>>student.rollNo;
		  		cout<<"ENTER THE STUDENT'S NEW NAME: ";
		  		cin>>student.name;
		  		cout<<"ENTER THE STUDENT'S NEW ADDRESS: ";
		  		cin>>student.address;
		  		cout<<"ENTER THE STUDENT'S NEW BRANCH: ";
		  		cin>>student.branch;
		  		
		  		fp.write((char*)&student, sizeof(StudentData));
		  		fp.close();
		  		
		  		cout<<"RECORD UPDATED"<<endl;
		  		
		  		return;
		  		
			  }
		  }
		  cout<<"ROLL NUMBER NOT FOUND"<<endl;
		  return;
	  }
	
	void Student :: searchDetails(){
		ifstream ifp;
		ifp.open("studentDatabase.dat", ios :: in | ios :: binary);
		
		if (!ifp){
			cerr<<"UNABLE TO OPEN FILE"<<endl;
			return;
		}
		int target;
		cout<<"	ENTER THE ROLL NUMBER TO SEARCH: ";
		cin>>target;
	
	StudentData student;
	
	while (ifp.read((char*)&student, sizeof(student)))
	{
		if (target == student.rollNo)
		{
			cout<<"RECORD FOUND"<<endl;
			cout<<"STUDENT'S NAME : "<<student.name<<endl;
			cout<<"STUDENT'S ROLL NUMBER: "<<student.rollNo<<endl;
			cout<<"STUDENT'S BRANCH: "<<student.branch<<endl;
			cout<<"STUDENT'S ADDRESS: "<<student.address<<endl;
			
			if (student.status == 1)
			{
				cout<<"ISSUED BOOK NAME IS: "<<student.bookTitle<<endl;
				
			}
		}else
		{
			cout<<"NO BOOK IS ISSUED FOR THIS ROLL NUMBER"<<endl;
		}
		
		cin.get();
		cin.get();
		return;
		}	
	}  
  
   void Student :: viewAllStudentDetail()
   {
   	system("clear");
   	fstream ifp;
   	ifp.open("studentDatabase.dat", ios :: in | ios :: binary);
   	if(!ifp)
   	{
   		cerr<<"UNABLE TO OPEN FILE"<<endl;
   		return;
   		
	   }
	   
	   StudentData student;
	   int choice = 1;
	   
	   while (ifp.read((char*)&student, sizeof(student)) && choice)
	   {
	   	system("clear");
	   	cout<<"STUDENT'S NAME: "<<student.name<<endl;
	   	cout<<"STUDENT'S ROLL NUMBER: "<<student.rollNo<<endl;
	   	cout<<"STUDENT'S BRANCH: "<<student.branch<<endl;
	   	cout<<"STUDENT'S ADDRESS: "<<student.address<<endl<<endl;
	   	
	   	if (student.status ==1 )
	   	{
	   		cout<<"ISSUED BOOK NAME IS: "<<student.bookTitle<<endl;
		   }
	   	else
	   	{
	   		cout<<"NO BOOK IS ISSUED FOR THIS ROLL NUMBER"<<endl;
		   }
		   
		   cout<<"TO VIEW NEXT STUDENT PRESS 1 ELSE PRESS 0";
		   cin>>choice;
	
	   }
	   return;
	} 
	
	void Student :: deleteDetails()
	{
		fstream file;
		file.open("studentDatabase.dat", ios :: in | ios :: binary);
		fstream temp;
		temp.open("temp.dat", ios :: out | ios :: binary);
		
		StudentData student;
		int target;
		int flag = 0;
		 cout<<"ENTER THE ROLL NUMBER TO DELETE THE DATA:";
		 cin>>target;
		 
		 while (file.read((char*)&student, sizeof(Student)))
		 {
		 	if (student.rollNo == target){
		 		flag++;
		 		continue;
			 }
			 temp.write((char*)&student, sizeof(Student));
			 
			 
			 
		 }
file.close();
temp.close();
remove("studentDatabase.dat");
rename("temp.dat","studentDatabase.dat");

if (flag == 1)
cout<<"RECORD DELETED"<<endl;
else
cout<<"ROLL NUMBER IS NOT FOUND"<<endl;

cin.get();
cin.get();

return;
}

void Menu::issueBook()
{
	fstream sp, bp;
	sp.open("studentDatabase.dat", ios :: in | ios :: out | ios ::ate | ios :: binary);
	bp.open("bookDatabase.dat", ios :: in | ios :: out | ios :: ate | ios :: binary);
	bp.seekg(0, ios :: beg);
	sp.seekg(0, ios:: beg);
	
	int rollNo,flagS = 0,flagB = 0, position;
	char title[30];
	StudentData student;
	Bookdata book;
	
	cout<<"ENTER THE STUDENT'S ROLL NUMBER TO ISSUE BOOK: ";
	cin>>rollNo;
	
	while (sp.read((char*)&student, sizeof(StudentData))){
		if(student.rollNo == rollNo)
		{
			position = (-1)*sizeof(StudentData);
			sp.seekp(position, ios :: cur);
			flagS++;
			break;
		}
	}
	
      if (flagS !=1){
      	cout<<"RECORD NOT FOUND"<<endl;
      	cin.get();
      	cin.get();
      	sp.close();
      	bp.close();
      	return;
      
	  }
	  cout<<"ENTER THE BOOK TITLE YOU WANT TO ISSUE: ";
	  cin>>title;
	  
	  while (bp.read((char*)&book, sizeof(BookData)))
	  {
	  	if(strcmp(book.title,title) == 0){
	  		position = (-1)*sizeof(BookData);
	  		bp.seekp(position, ios :: cur);
	  		flagB++;
	  		break;
	  	
		  }
		  }
		  
		  if (flagB != 1)
		  {
		  	cout<<"RECORD NOT FOUND"<<endl;
		  	cin.get();
		  	cin.get();
		  	sp.close();
		  	bp.close();
		  	return;
			  }	
			  
			  if(student.status != 1 && book.status != 1)
			 {
			 	strcpy(student.bookTitle,title);
			 	student.status = 1;
			 	book.status = 1;
			 	book.issuedRollNo = student.rollNo;
			 	book.issuedDate.setDate();
			 	book.returnDate.setDate(book.issueDate);
			 	sp.write((char*)&student, sizeof(StudentData));
			 	bp.write((char*)&book, sizeof(BookData));
			 	sp.close();
			 	bp.close();
			 
			  }
			  else
			  {
			  	cout<<"BOOK IS ALREADY ISSUED"<<endl;
			  	cin.get();
			  	cin.get();
			  	sp.close();
			  	bp.close();
			  	return;
			  	
			   }
		}
	
	
	void Menu :: returnBook()
	{
		
		fstream sp, bp;
		sp.open("studentDatabase.dat", ios :: in | ios :: out | ios :: ate | ios :: binary);
		bp.open("bookDatabase.dat", ios :: in | ios :: out | ios :: ate | ios :: binary);
		bp.seekg(0, ios :: beg);
		sp.seekg(0, ios ::beg);
		
		int rollNo, flagS = 0, flagB = 0, position;
		char title[30];
		StudentData student;
		BookData book;
		
		cout<<"ENTER THE STUDENT'S ROLL NUMBER TO RETURN THE BOOK: ";
		cin>>rollNo;
		
		while (sp.read((char*)&student, sizeof(StudentData)))
		{
			if(student.rollNo == rollNo)
			{
				position = (-1)*sizeof(StudentData);
				sp.seekp(position, ios :: cur);
				flagS++;
				break;
				
			}
		}
          if (flagS != 1)
          {
          	cout<<"RECORD NOT FOUND"<<endl;
          	cin.get();
          	cin.get();
          	sp.close();
          	bp.close();
          	return;
		  }
		  while (bp.read((char*)&book, sizeof(BookData)))
		  {
		  	if(strcmp(book.title,student.bookTitle) == 0)
		  	{
		  		position = (-1)*sizeof(BookData);
		  		bp.seekp(position, ios :: cur);
		  		flagB++;
		  		break;
		  		
			  }
		  }
		  
		  if (flagB != 1)
		  {
		  	cout<<"RECORD NOT FOUND"<<endl;
		  	cin.get();
		  	cin.get();
		  	sp.close();
		  	bp.close();
		  	return;
		  	
		  }
		  if(student.status == 1 && book.status == 1){
		  	student.status = 0;
		  	book.status = 0;
		  	book.issuedRollNo = -9999;
		  	sp.write((char*)&student, sizeof(StudentData));
		  	bp.write((char*)&book, sizeof(BookData));
		  	sp.close();
		  	bp.close();
		  
		  }
		  else
		  {
		  	if(student.status == 0)
		  	{
		  		cout<<"STUDENT'S ACC ALREADY FULL"<<endl;
		  		cin.get();
		  		cin.get();
		  		sp.close();
		  		bp.close();
		  		return;
			  }
			  if(student.status==1 && book.status==1)
			  {
			  	student.status = 0;
			  	book.status = 0;
			  	book.issuedRollNo = -9999;
			  	sp.write((char*)&student, sizeof(StudentData));
			  	bp.write((char*)&book, sizeof(BookData));
			  	sp.close();
			  	bp.close();
			  }
		  }else
		  {
		  	if (student.status == 0)
		  	{
		  		cout<<"STUDENT'S ACC IS ALREADY FULL"<<endl;
		  		cin.get();
		  		cin.get();
		  		sp.close();
		  		bp.close();
		  		return;
			  }
			  
		  }
	}
	
	
	int main()
	{
		Menu menu;
		int quit = 0;
		char choice[3];
		
		while(!quit)
		{
			system("clear");
			menu.mainMenu();
			cout<<"ENTER YOUR CHOICE: "<<endl;
			cin>>choice;
			switch(atoi(choice))
			{
				// atoi le number in string lai integer ma covert garxa
				//"13" lai 13
				case 1:{
					system("clear");
					menu.studentMenu();
					cout<<"PLEASE ENTER YOUR CHOICE:" endl;
					cin>>choice;
					student s1;
					switch(atoi(choice))
					{
						case 1:s1.inputDetails();
						break;
						
						case 2:s1.modifyDetails();
						break;
						
						case 3:s1.searchDetails();
						break;
						
						case 4:s1.deleteDetails();
						break;
						
						case 5:s1.viewAllStudentDetail();
						break;
						
						case 6:break;
						
						default: cout<<"WRONG INPUT RECEIVED"<<endl;
												
					}
					break;
				}
			case 2:
			{
				system("clear");
				menu.bookMenu();
				cout<<"PLEASE ENTER YOUR CHOICE: "<<endl;
				cin>>choice;
				Book b1;
				switch(atoi(choice))
				{
					    case 1: b1.inputDetails();
						break;
						
						case 2:b1.modifyDetails();
						break;
						
						case 3:b1.searchDetails();
						break;
						
						case 4:b1.deleteDetails();
						break;
						
						case 5:b1.viewAllBookDetail();
						break;
						
						case 6:break;
						
						default: cout<<"WRONG INPUT RECEIVED"<<endl;
				}
				break;
				}	
				case 3: menu.issueBook();
					break;
					
				case 4: menu.returnBook();
				break;
				
				case 5: quit++;
				break;
				
				default: cerr<<"PLEASE ENTER THE CORRECT INPUT "<<endl;
				cin>>choice;
				
			}
		 } 
	return 0;
}}
	
