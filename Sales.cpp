#include <iostream> // Contains code that allows C++ programs to display output on the screen and read input from the keyboard.
#include <string>   // Allows for creating string type variables. As char's can only store one character.
#include <fstream>  // fstream allows the program to read from a file using ifstream and can also be displayed in the console. fstream also allows you to create and write to a file using ofstream.
#include <vector>	// The standard Template Libary. Vectors allow for storing data, additonally the STL is a collection of programmer-defined data types.

using namespace std;
// A class is describing the set of all objects that have certain characteristics. An object of a derived class inherits all the characteristics of the base class, so it can be regarded as belonging to the base class.
// Objects of the derived class are specialized objects of the base class. The derived class is often called a sub class of the base class, and the base class is called a superclass of the derived class.  
class SalesData
{
private:
	vector<int>salesrecord; // Vectors allow for storing data, but when writing out a program we refer to the name that we give which is "salesrecord". Otherwise defines a number, a vector of ints.
	// Usually a vector normally has "()" with a figure entered inside of the brackets and will take the nessacry amount of numbers into consideration when creating a program.
	// However, we are not using a figure, but we are refering to the name of the vector and taking the informstion from within the inputfile.
	ifstream inputfile;  // fstream allows the program to read from a file using ifstream and can also be displayed in the console.
	ofstream outputfile; // fstream also allows you to create and write to a file using ofstream.
public:
	void loadDataFromFile(string filename); // This function will be used for gathering the data from the manually created text file and passing it for the second function to handle.
	void saveBarChartToFile(string filename); // This function will create a text file and store the data in the form of a horizontal bar chart.
};

void SalesData::loadDataFromFile(string filename)
{
	int value = 0; // Declares this variable so we can use it as apart of loading the data further on within this function.

	inputfile.open(filename); // Opens an existing text file.

	if (inputfile.fail()) // Validation if statement which checks to see if the file exists within any of the directries.
	{
		cerr << "Error opening file" << endl; // If the file doesn't exist then this message will be output to the console.
		return; // Exits the if statement.
	}

	while (inputfile >> value) // Inputfile is passed through as value which is refered to as the contents of the text file "sales.txt".
	{
		salesrecord.push_back(value); // This is apart of the vector, it allows a new element to be created holding however many figures within the brackets. 
		// It also allows for storing data, whether its taking data from another file or if we maunally enter data in. 
		outputfile << value; // Outputs the value variable to the outputfile.
	}
	inputfile.close(); // Closes the inputfile.
}

void SalesData::saveBarChartToFile(string filename)
{
	
	if (outputfile.fail()) // Validation if statement which checks to see if the file exists within any of the directries.
	{
		cerr << "Error opening output file\n"; // If the file doesn't exist then this message will be output to the console.
		return; // Exits the if statement.
	}

	//If the file exists then the following context is outputted to the outputfile.
	outputfile << "SALES BAR CHART\n"; 
	outputfile << "Each '*' Represents $100\n";

	// Unlike arrays, vectors can report the number of elements they contain. This is done with the size member function. After the statement excutes, the "salesrecord" will contain the number of elements used.
	// Unsigned int is a variable that can only accept postive numbers.
	for (unsigned int i = 0; i < salesrecord.size(); i++) // A variable is declared and when it reaches the end of the file it then moves on to the next statement.
	{
		outputfile << endl; // Creates a new line on the outputfile.
		outputfile << "Store " << i + 1 << ": "; // will output numbers 1-5, but with the output messages "Store:" then the program knows what the numbers represent.
		
		int star = salesrecord[i] / 100; // Another variable is declared and it is equal to the values within the text file by using the salesrecord vector and dividing them numbers by 100 to give the correct amount of "*".
		for (int x = 0; x < star; x++) // The contents of the file which is being refered to as salesrecord is taking the figures within the text file, dividing them accordingly and outputing the neseccary amount of "*" needed.
			{
				outputfile << "*"; // Outputs the nessacry amount of "*" for each figure once divided by 100, as each "*" reperesents £100. 
			}
	}
	outputfile.close(); // closes the outputfile.
}

int main()
{
	SalesData MySales; // the Sales Data Class is being called and is being refered to as "MySales".
	MySales.loadDataFromFile("sales.txt"); // Calls the class, function and opens the "sales.txt" file.
	MySales.saveBarChartToFile("graph.txt"); // Calls the class, function and opens the "graph.txt" file.
	return 0; // End of Program.
} 
// End of Program.