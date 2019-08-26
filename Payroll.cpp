#include <iostream> // Contains code that allows C++ programs to display output on the screen and read input from the keyboard.
#include <string>   // Allows for creating string type variables. As char's can only store one character.
#include <fstream>  // fstream allows the program to read from a file using ifstream and can also be displayed in the console. fstream also allows you to create and write to a file using ofstream.
#include <vector>	// The standard Template Libary. Vectors allow for storing data, additonally the STL is a collection of programmer-defined data types.

using namespace std;

// A class is describing the set of all objects that have certain characteristics. An object of a derived class inherits all the characteristics of the base class, so it can be regarded as belonging to the base class.
// Objects of the derived class are specialized objects of the base class. The derived class is often called a sub class of the base class, and the base class is called a superclass of the derived class.  
class OrganisationRecord
{
private:

public:
	string name;
	string occupation;
	string department;
};
// Multiple Inheritance which are derived classes simultaneiously derives from two or more classes. 
class HRRecord
{
private:

public:
	string address;
	string phonenumber;
	string ninumber;
};

class PayrollRecord
{
private: 

public:
	string ninumber;
	double salary;
};

class PayrollProcessing
{
private:
	ifstream inputfile; // fstream allows the program to read from a file using ifstream and can also be displayed in the console.
	ofstream outputfile; // fstream also allows you to create and write to a file using ofstream.
	vector <OrganisationRecord> organisationRecords; // Vectors allow for storing data, but when writing out a program we refer to the name that we give which is "salesrecord". Otherwise defines a number, a vector of ints.
													 // Usually a vector normally has "()" with a figure entered inside of the brackets and will take the nessacry amount of numbers into consideration when creating a program.
													 // However, we are not using a figure, but we are refering to the name of the vector and taking the informstion from within the inputfile.
	vector <HRRecord> HRRecords;
	vector <PayrollRecord> PayrollRecords;
 				
public:
	void loadOrganisationRecords(string filename); // This function is used to take the information from OrganisationRecords text file.
	void loadHRRecords(string filename); // This fucntion is used to take the information from the HRRecords text file.
	void loadPayrollRecords(string filename); // This function is used to take the information from PayrollRecords text file.0
	void displayEmployeeOfSalaryGTE(double salary); // This function will take all the information that had been loaded into the other functions and output all the data into the console and determines how much the specifed employees earn.
	//GTE = greater than or Equal to
};

void PayrollProcessing::loadOrganisationRecords(string filename)// records: employee number, name, occupation and department. is ordered by employee number in ascending order
{
	OrganisationRecord organ; // Takes the subclasses from the "OrganisationRecord" super class into consideration for the following function.
	
	string employeeID; // Making use of a string called employeeID and removing the employeeID's from the text files. 
	inputfile.open(filename); // Opens an existing text file.
	if (inputfile.fail())// Validation if statement which checks to see if the file exists within any of the directries.
	{
		cerr << "Error Opening organisation file" << endl; // If the file doesn't exist then this message will be output to the console.
		return; // Exits the if statement.
	}
		while (getline(inputfile, employeeID)) // This function reads an entire line, including leading and embeddeds spaces, and stores it in a string object. 
		// Where "inputfile" is the input stream it reads from and "employeeID" is the name of the string variable receiving the input string. 
		{
			
			getline(inputfile, organ.name); // Reads the names, occupation and department from the "OrganisationRecord" class.
			getline(inputfile, organ.occupation);
			getline(inputfile, organ.department);
			
			organisationRecords.push_back(organ); // This is apart of the vector, it allows a new element to be created holding however many figures within the brackets. 
		// It also allows for storing data, whether its taking data from another file or if we maunally enter data in. 
		}

	inputfile.close(); // Closes the corresponding text file.
}

void PayrollProcessing::loadHRRecords(string filename)
{
	HRRecord record;  // Takes the subclasses from the "HRRecord" super class into consideration for the following function.
	string employeeID; 
	inputfile.open(filename); 
	if (inputfile.fail())
	{
		cerr << "Error Opening hr File" << endl; 
		return; // Exits the if statement.
	}

	while (getline(inputfile, employeeID))
	{
		getline(inputfile, record.address); // Reads the address, phonenumber and ninumber from the "HHRecord" class.
		getline(inputfile, record.phonenumber);
		getline(inputfile, record.ninumber);

		HRRecords.push_back(record); // This is apart of the vector, it allows a new element to be created holding however many figures within the brackets. 
		// It also allows for storing data, whether its taking data from another file or if we maunally enter data in. 
	}
	inputfile.close();
}

void PayrollProcessing::loadPayrollRecords(string filename)
{
	PayrollRecord pay;  // Takes the subclasses from the "PayrollRecord" super class into consideration for the following function.
	string employeeID; 

	inputfile.open(filename);
	if (inputfile.fail())
	{
		cerr << "Error Opening Payroll File" << endl;
		return; // Exits the if statement.
	}
	while (getline(inputfile, employeeID))
	{
		getline(inputfile, pay.ninumber); // Reads the ninumber and salary from the "PayrollRecord" class.
		inputfile >> pay.salary;
		inputfile.ignore(); // Inputfile.ignore function tells the getline object to skip one or more characters in the keyboard buffer.
		// It causes the getline getline object function to be bypassed forcing to getline to end and proceed with the program.

		PayrollRecords.push_back(pay); // This is apart of the vector, it allows a new element to be created holding however many figures within the brackets. 
		// It also allows for storing data, whether its taking data from another file or if we maunally enter data in. 
	}

	inputfile.close();
}

void PayrollProcessing::displayEmployeeOfSalaryGTE(double salary)
{
	// Unsigned int is a variable that can only accept postive numbers.
	unsigned int size = organisationRecords.size();
				
				cout << endl; // Creates a new line.
				cout << "--------------------------------------------------" << endl;
				cout << "Payroll Records" << endl;
				cout << "--------------------------------------------------" << endl;
	// A name is created for the unsigned int with a starting value of 0. It then proceeds through the text files until it reaches the end of the text files.
	// The end of the file is the "organisationRecords.size".
	// The data is taken using the pushback method from the 3 above functions and are all used in the below line to gather the final information.
	for (unsigned int processrecords = 0; processrecords < size; processrecords++)
	{
		if (PayrollRecords[processrecords].salary > salary)
	// All data is then gathered and used to display onto the console accordingly.
			{
				cout << endl;
				cout << "Employee Name: " << organisationRecords[processrecords].name << endl;
				cout << "Employee's Address: " << HRRecords[processrecords].address << endl;
				cout << "Department: " << organisationRecords[processrecords].department << endl;
				cout << "Employee's Salary: " << PayrollRecords[processrecords].salary << endl;	
				cout << endl;
			}
		else
	// If one of the records within the text files has a salary of under £20000 then the data won't be displayed and will output the following message.
			{
				cout << "------------------------------------------------" << endl;
				cout << endl;
				cout << "Salary is below 20000" << endl;
				cout << endl;
				cout << "------------------------------------------------" << endl;
			}
	}
				cout << "------------------------------------------------" << endl;
}

int main()
{
	PayrollProcessing myProject;
	myProject.loadOrganisationRecords("organisation.txt"); // The function takes the Organisation.txt file into consideration when the program is excuted.
	myProject.loadHRRecords("hr.txt"); // The function takes the hr.txt file into consideration when the program is excuted.
	myProject.loadPayrollRecords("payroll.txt"); // The function takes the Payroll.txt file into consideration when the program is excuted.
	myProject.displayEmployeeOfSalaryGTE(20000); // This is how we determine if the are earning under or over £20000 as a salary.
	
	return 0;

}