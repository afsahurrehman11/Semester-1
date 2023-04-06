#include<iostream>
#include<windows.h>


using namespace std;

void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}


struct employee
{
	string eName;      // employee name 
	int eID;
	int salary;
	int kids;         // no of kids 
	int deptID;

};

// now if we want to use this struct or new data type of employee for every employee in a factory 



int  main()
{
	cout << "number of employee  : \n";
	int noe;
	cin >> noe;

	/*
	// don't get confuse over here !!!
	
	 look using a for loop till noe i can either read for file or take input from user 
	 let suppose uerv  is  a clerk which ha s assigined to enter all the employee data in server
	 but the question is raised how we will be able to store data i.e each struct 
	      1 ... we can hardcore by declearing 100 structs like 
					employee E1;
					employee E2;
					employee E3;
					employee E4;
					employee En;

		   2... when we have a lot of varaible OF SAME TYPE and we want to store all of them in 
	            an organized way, what we use hmm, array. 
				
				as we that if we want to store a lot of int we use a pointer of int type and make a 1D array out of it 
				(we can also make static array (a simple array like A[size] i.e without the use of pointers but i will use 
				dynamic  array (an array formed using pointers like int* A ;   A= new int [size] ) )

				as we know that data type of array and variables in it must be same so we will make a pointer of data type 
				employee which will store different variables of data type employee .

				employee * arr_of_employes ;

				(see a thing that now we are free from extra work of giving a unique name to each employee variable )
				(i mean this work )
					employee E1;
					employee E2;
					employee E3;
					employee E4;
					employee En;

				even by usin g pointer they are also organize in a manner of [0] [1] [2]...[n]			

				



	*/




	// allocating memoery 

	employee* arr_of_employes;
	arr_of_employes = new employee[noe];  // here new EMPLYEE is written bec this array will contain variable sof datatype employee 


	// initilization 

	for (int i = 0; i < noe; i++)
	{
		cout << "enter data for " << i + 1 << "employee" << endl;

		cout << "enter name : ";
		cin>> arr_of_employes[i].eName;


		cout << "ID : ";
		cin>>arr_of_employes[i].eID;


		cout << "salary : ";
		cin >> arr_of_employes[i].salary;


		cout << "kids : ";
		cin >> arr_of_employes[i].kids;

		cout << "dept ID : ";
		cin >> arr_of_employes[i].deptID;

		cout << endl << endl;

	}

	// lets print 
	// ik i am not making function cause ma kam choor hun :) 


	cout << "----------------------------------------------------------------------\n\n"; // just for repersentation

	

	for (int i = 0; i < noe; i++)
	{
		cout << "\t\t\t employee number : " << i+1 << endl;

		cout << "\tname : "<< arr_of_employes[i].eName << endl;

		cout << "\tID : "<< arr_of_employes[i].eID << endl;


		cout << "\tsalary : " << arr_of_employes[i].salary << endl;


		cout << "\tkids : "<< arr_of_employes[i].kids << endl;

		cout << "\tdept ID : "<< arr_of_employes[i].deptID << endl<<endl;

		cout << "----------------------------------------------------------------------\n";



	}


	/*
	
	main use of struct is to organize data and also it has a following benifit 
	suppose a function which take a data of single employee n tell that is this person eligible for a supportive fund or not 
	
	it will take 1 employee data at a  time 
	we will simply write 

	bool supportive fund_eligibility (employee E)      // E is just a name of varaible for function
	{
		if( E.salary < 50000 && E.kids >=3)
		{	
			return true;
		}
		return false ;
	}



	if we haven't made employee struct we were not able to store all emplye data at once 
	tab ya hona tha kaay 1 ka data enter kia process huya supportive fund_eligibility is kay leya check
	huya cout huya tab 2nd emplyee data ki barai 
	or wo kuxh asa hota 
		
		string eName;      
		int eID;
		int salary;
		int kids;         
		int deptID;

		cout << "enter data for this employee" << endl;

		cout << "enter name : ";
		cin>> Name;


		cout << "ID : ";
		cin>>ID;


		cout << "salary : ";
		cin >>salary;


		cout << "kids : ";
		cin >> kids;

		cout << "dept ID : ";
		cin >> deptID;

		cout << endl << endl;

			
						
						priniting work



		cout << "\t name : "<< Name << endl;

		cout << "\t ID : "<< ID << endl;

		cout << "\t salary : " <<salary << endl;

		cout << "\t kids : "<<kids << endl;

		cout << "\t dept ID : "deptID << endl<<endl;

		// assuming i don't have struct mujay ik ik kar kay sab variable s pass karnay party 
		// and my function will look like 

				bool supportive fund_eligibility (string name , int ID ,int salary  ,int kids ,int deptID)
				{
					if( salary < 50000 && kids >=3)
					{
						return true;
					}
					return false ;
				}



		if ( supportive fund_eligibility (Name,ID,salary,kids,deptID) )
			cout<<"congrats u r selected for supportive fund ";
	


		



	*/




	/*
	
	as there is a clear diiferance bw 
										bool supportive fund_eligibility (employee E) // only have 1 parameter
	and 
	
										bool supportive fund_eligibility (string name , int ID ,int salary  ,int kids ,int deptID)
	
	

	now same is the case if we have a func which process data on a single empolyee and return all values of that employee 

	if we do without struct we have to pass all am%ly
	like 

	void inilize (string& name , int &ID ,int &salary  ,int &kids ,int &deptID)


	if we use struct we can write it as a function with return type EMPLOYEE 


	employee inilize ()      // no need of parameters now 
	{
		employee E;
		cin>> E.salary ;
		cin>> E.name ;
		cin>> E.Id ;
		cin>> E.balabalabala ;     //nvm

		return E;

	}

	
	*/







}