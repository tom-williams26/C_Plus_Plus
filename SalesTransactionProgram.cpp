// Assignment 1.2.cpp : Stock Transaction Program.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

void retrieveBuyValues(string& stockname, double& unitstockbuyprice, double& buycommission, int& amountbought)
{
	cout << "What was the name of the shares you purchased?" << endl;
	// The program will ask the user for the name of the stock that they bought.
	cin >> stockname;
	// This will allow the user to enter the name of the stock they bought.
	
	cout << endl;
	// New line.

	cout << "Please enter the price you bought you're shares at: -" << endl;
	// The program will ask the user for the price the user bought their shares at.
	cin >> unitstockbuyprice; 
	// This will allow the user to enter the price of the stock they bought.
	cout << "Please enter the amount of shares bought: - " << endl;
	// The program will ask the user how many shares the user bought.
	cin >> amountbought;
	// This will allow the user to enter the amount of shares they bought.

	cout << "Please enter the commission (%) for purchase (stated as decimal): " << endl;
	// The program will display the question for entering the amount of commision (%) paid to the broker when buying their shares. 
	cin >> buycommission; 
	// This will allow the user to enter the commission (%) paid to the broker for buying their shares.
	
	cout << endl;
	// New line.

	cout << "---------------------------------------------------" << endl;
						
}
							// End of Section.

void retrieveSales(double& unitstocksaleprice, double& salecommission, int& amountsold)
{

	cout << endl;
	// New line.

	cout << "Please enter amount of shares sold: " << endl;
	// The program will display the question for the amount of shares sold.
	cin >> amountsold;
	// This will allow the user to enter the amount of the shares sold.
	cout << "Please enter unit stock sale price: " << endl;
	// The program will display the question for entering the unit stock sale price.
	cin >> unitstocksaleprice;
	// The program will allow the user to enter the unit stock sale price.
	cout << "Please enter the commission (%) for sale (stated as decimal): " << endl;
	// The program will display the question for entering the amount of commision (%) paid to the broker when selling their shares.
	cin >> salecommission;
	// This will allow the user to enter the commission (%) paid to the broker for selling their shares.
	
	cout << endl;
	// New line.

	cout << "---------------------------------------------------" << endl;
	
}
							// End of Section.

void displayInformation(const string stockname, const double unitstockbuyprice, const double buycommission,
	const int amountbought, const double unitstocksaleprice, const double salecommission, const int amountsold)
{

	cout << endl;
	// New line.

	cout << "---------------------------------------------------" << endl;
	
	cout << endl;
	// New line.

	cout << "Stock name = " << stockname << endl;
	// The program will display the name of the shares and retrieve the stock name entered.
	
	cout << endl;
	// New line.

	cout << "---------------------------------------------------" << endl;

	cout << endl;
	// New line.

	cout << "Unit stock buy Price = " << unitstockbuyprice << endl;
	// The program will retrieve the Unit stock buy Price for the shares.
	cout << "Buy commission (%)(Express as decimal) = " << buycommission << endl;
	// The program will retrieve the commission paid to the broker for the shares.
	cout << "Amount bought = " << amountbought << endl;
	// The program will retrieve the amount of shares bought.
	cout << "Total paid = " << amountbought * unitstockbuyprice * (1 + buycommission) << endl;
	// The program will retrieve the amount paid for the shares bought (taking commission into consideration).

	cout << endl;
	// New line.

	cout << "---------------------------------------------------" << endl;
							// Spacing
	cout << "---------------------------------------------------" << endl;

	cout << endl;
	// New line.

	cout << "Unit stock sale Price = " << unitstocksaleprice << endl;
	// The program will retrieve the Unit stock sale Price for the shares.
	cout << "Sale commission (%)(Express as decimal) = " << salecommission << endl;
	// The program will retrieve the commission paid to the broker for the shares.
	cout << "Amount sold = " << amountsold << endl;
	// The program will retrieve the amount paid for the shares sold.
	
	cout << endl;
	// New line.

	cout << "---------------------------------------------------" << endl;

	
}
							// End of Section.

void retrieveProfitLoss(const int amountsold, const double unitstocksaleprice, const double salecommission)
{
	cout << endl;
	// New line.

	cout << "Total gained = " << amountsold * unitstocksaleprice * (1 - salecommission) << endl;
	// The program retrieves the amount of shares sold and at what price they were sold for (also taking the commission into consideration).

}
							// End of Section.

void salesProgram(void)
{
	
	string stockname;
	double unitstockbuyprice, unitstocksaleprice = 0;
	double buycommission = 0, salecommission = 0;
	int amountbought = 0, amountsold = 0;
	// This allows all values (when entering the shares information) except for the "stockname" to be set to zero, until the user inputs data.

	// *Sub functions*
	retrieveBuyValues(stockname, unitstockbuyprice, buycommission, amountbought);
	retrieveSales(unitstocksaleprice, salecommission, amountsold);
	displayInformation(stockname, unitstockbuyprice, buycommission, amountbought, unitstocksaleprice, salecommission, amountsold);
	retrieveProfitLoss(amountsold, unitstocksaleprice, salecommission);
	// Calls the following functions when the program is running.
	
}

							// End of Section.

int main()
{

	salesProgram();
	// Excutes the sales program function.
    return 0;

}
						  // ** End of program **
