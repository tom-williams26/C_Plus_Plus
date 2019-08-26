// Assignment 1.1.cpp : Gemoetry Calculator.

#include <iostream>
#include <string>
#include <limits>

using namespace std;

// cout << endl = new line.
//***Area of the Circle***
void AreaofCircle(int radius = 0) // The parameter for the radius is set to 0 until the user enters a postive value.
{
	// This figure represents how much PI is and will be using it to calculate the area of the circle.
	double PI = 3.14159;

	// This will be the title for the area of the circle just to clarify its the right task they want to carry out.
	cout << "Area of the Circle" << endl;
	cout << endl;
	
	// The program will ask the user to enter a value for the radius of the circle, also allowing the user to enter a value at the same time.
	cout << "Please enter a value for the radius?    ";
	cin >> radius;
	cout << endl;
	
	// This is a validation stage during the area of the circle function. It will prevent the user from entering any negative numbers.
	// If a negative number is given, the user will get prompted to enter a number again, which has to be a postive number if they want to contiue with the program.
	while (radius < 0)
	{
		cout << "You have entered a negative number \n" << endl;
		
		cout << "Please enter a value for the radius?    ";
		cin >> radius;
	}
	
	// This will state the area of the circle and will calculate the radius by PI to get the area of the circle.
	cout << "\nArea of the Circle =   ";

	cout << PI * (radius * radius);
	
	// End of function
}
//***Area of the Rectangle***
void AreaofRectangle(int height = 0, int width = 0) // The parameter for the height and width is set to 0 until the user enters a postive value.
{
	// This will be the title for the area of the rectangle just to clarify its the right task they want to carry out.
	cout << "Area of the Rectangle" << endl;
	cout << endl;

	// The program will ask the user to enter a value for the height and width for the area of the rectangle, also allowing the user to enter a value at the same time.
	cout << "Please enter a value for the height?	";
	cin >> height;
	cout << endl;

	cout << "Please enter a value for the width?	";
	cin >> width;
	cout << endl;

	// This is a validation stage during the area of the rectangle function. It will prevent the user from entering any negative numbers.
	// If a negative number is given, the user will get prompted to enter a number again, which has to be a postive number if they want to contiue with the program.
	// This applies for both the height and width.
	while (height < 0)
	{
		cout << "You have entered a negative number \n" << endl;
		cout << "Please enter a value for the height?    ";
		cin >> height;
		cout << endl;
	}
	while (width < 0)
	{
		cout << "You have entered a negative number" << endl;
		cout << "\nPlease enter a value for the width?	";
		cin >> width;
		cout << endl;
	}
	// This is the title for stating what the area of the rectangle is once 2 postive values have been entered and accepted by the validation stage.
	cout << "\n The area of the rectangle is: 	";

	// The height and width are multiplied together to give a final value.
	cout << height << " * " << width << " = " << height * width << endl;

	// End of Section
}
//***Area of the Triangle***
void AreaofTriangle(int height = 0, int width = 0)// The parameter for the height and width is set to 0 until the user enters a postive value.
{
	// This will be the title for the area of the triangle just to clarify its the right task they want to carry out.
	cout << "Area of the Triangle  " << endl;
	cout << endl;

	// The program will ask the user to enter a value for the height and width for the area of the rectangle, also allowing the user to enter a value at the same time.
	cout << "Please enter a value for the height?  ";
	cin >> height;
	cout << endl;

	cout << "Please enter a value for the width?   ";
	cin >> width;
	cout << endl;

	// This is a validation stage during the area of the rectangle function. It will prevent the user from entering any negative numbers.
	// If a negative number is given, the user will get prompted to enter a number again, which has to be a postive number if they want to contiue with the program.
	// This applies for both the height and width.
	while (height < 0)
	{
		cout << "You have entered a negative number" << endl;
		cout << endl;
		cout << "\nPlease enter a value for the height?    ";
		cin >> height;
	}

	while (width < 0)
	{
		cout << "You have entered a negative number" << endl;
		cout << "\nPlease enter a value for the width?	";
		cin >> width;
	}

	// This is the title for stating what the area of the rectangle is once 2 postive values have been entered and accepted by the validation stage.
	cout << "\n The area of the triangle is:	";

	// The height and width are multiplied together to give a final value.
	cout << height << " * " << width << " * .5" << " = " << height * width * .5 << endl;
	
	// End of Section
}
//***Display Menu***
void displayMenu(void)
{
	// Display Menu.
	// This will state the following options the user can choose from.
	cout << endl;
	cout << "****************************************************************************" << endl;
	cout << endl;

	// This states to the user that they have multiple options to choose from.
	cout << "Please choose from one of the following options: \n" << endl;

	// If option one is selected the program will proceed to the area of the circle function.
	cout << "Calculate the Area of a Circle \n" << endl;

	// If option two is selected the program will proceed to the area of the rectangle function.
	cout << "Calculate the Area of a Rectangle \n" << endl;

	// If option three is selected the program will proceed to the area of the triangle function.
	cout << "Calculate the Area of a Triangle \n" << endl;

	//If option four is selected the program will proceed to closing down the program.
	cout << "Quit" << endl;
	cout << endl;

}
//***Maths Program***
void mathsprogram(void)
{
	// Sets the Menu option to 0, to avoid any conflicts with choosing an option from the menu.
	int option = 0;

	// This will allow the program to open the Display Menu upon starting the program and giving the user the capabilities of selecting an option.
	while (true)
	{
		displayMenu(); // Opens Menu.
		cin >> option; // Select option.
		cout << endl;

		if (option > 0 && option < 4)// If the user selects a value within these parameters a function will be called.
		{
			cout << endl;

			switch (option)
			// This allows the program to alernate between the display menu and the other three functions, once the user has been brought out of the last function they were in.
			{
			// Once the user has selected a value the program will then call one of these 3 functions.
			// Proceeding to that called function and following the instructions within that function.
			case 1: AreaofCircle(); break;
			case 2: AreaofRectangle(); break;
			case 3: AreaofTriangle(); break;
			}
		}
		else if (option == 4) // Program will close. Program returns to the display menu.
		{
			// States the program is closing.
			cout << "Quiting...." << endl;
			break;
		}
		// If the user enter a value higher or lower than values 1 through 4 the program won't accept it, prompting the user to enter a value withing the parameters.
		else cout << "Error! Please enter a value from 1-4. " << endl; // only values 1 equal to or less than 4 can be entered.
		cout << endl;
	}
}
	
//***Main Function***
int main(void) // main function
{
	mathsprogram(); // Calls and Opens Maths Program.

	return 0; // Ends program.
} // End of Program.
