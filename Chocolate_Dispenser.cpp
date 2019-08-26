#include <iostream>
#include <vector>

using namespace std;

enum state { Out_of_Chocolate, No_Credit, Has_Credit, Dispenses_Chocolate, Maintenance_Mode }; // the lists of states used throughout the dispenser.

class StateContext;

class State
{
protected:
	StateContext* CurrentContext;
public:
	State(StateContext* Context) { CurrentContext = Context; } // throughout the program when Current Context is shown it will have a named state along it (for example Out_Of_Chocolate).
	virtual ~State(void) {} // terminates the state.
};

class StateContext
{
protected:
	State* CurrentState = nullptr; // state points to current state and ends once it reaches nullptr.
	int stateIndex = 0;
	vector<State*> availableStates;

public:
	virtual ~StateContext(void); // terminates the state.
	virtual void setState(state newState); // when setState is called it will also require a new state to replace the current state.
	virtual int getStateIndex(void);

};

StateContext::~StateContext(void)
{
	for (int i = 0; i < this->availableStates.size(); i++) delete this->availableStates[i]; // declares a variable and includes all the availableStates and then deletes the value within the array.
	this->availableStates.clear(); // clears the avaliableStates.
}

void StateContext::setState(state newState)
{
	this->CurrentState = availableStates[newState]; // points to the current state and replaces it with a new state using one of the avaliable states created within the Chocolate_Dispenser class.
	this->stateIndex = newState;  
}

int StateContext::getStateIndex(void)
{
	return this->stateIndex; // returns the current state.
}
// If return false is used within the functions from that point on the rest of the functions will display errors (not particularly in the following order however).
class Transition
{
public:
	virtual bool insertMoney(int) { cout << "Error!" << endl; return false; }
	virtual bool makeSelection(int) { cout << "Error!" << endl; return false; }
	virtual bool moneyRejected(void) { cout << "Error!" << endl; return false; }
	virtual bool addChocolate(int) { cout << "Error!" << endl; return false; }
	virtual bool dispense(void) { cout << "Error!" << endl; return false; }
	virtual bool enterPin(int pin) { cout << "Error!" << endl; return false; }
	virtual bool exit(void) { cout << "Error!" << endl; return false; }
};

class Chocolate_Dispenser : public StateContext, public Transition
{
	friend class OutOfChocolate;
	friend class NoCredit;
	friend class HasCredit;
	friend class DispensesChocolate;
	friend class MaintenanceMode;
private:
	int inventory = 0; //number of chocolate.
	int credit = 0; //a measure of the number of bars that can be purchased and not money.
	int pin = 54321; // secret pin for maintenance mode.
public:
	// The list of functions required to make up the dispenser.
	Chocolate_Dispenser(void);
	bool insertMoney(int credit);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addChocolate(int number);
	bool dispense(void);
	bool enterPin(int pin);
	bool exit(void);
};


class ChocoState : public State, public Transition
{
public:
	ChocoState(StateContext* Context) : State(Context) {}
};

// the following list of classes show the appropriate list of functions to allow the chocolate dispenser to work just accordingly to the state diagram.
class OutOfChocolate : public ChocoState
{
public:
	OutOfChocolate(StateContext* Context) : ChocoState(Context) {} 
	bool enterPin(int pin);
};

class NoCredit : public ChocoState
{
public:
	NoCredit(StateContext* Context) : ChocoState(Context) {}
	bool enterPin(int pin);
	bool insertMoney(int credit);
};

class HasCredit : public ChocoState
{
public:
	HasCredit(StateContext* Context) : ChocoState(Context) {}
	bool insertMoney(int credit);
	bool makeSelection(int option);
	bool moneyRejected(void);
};

class DispensesChocolate : public ChocoState
{
public:
	DispensesChocolate(StateContext* Context) : ChocoState(Context) {}
	bool dispense(void);
};

class MaintenanceMode : public ChocoState
{
public:
	MaintenanceMode(StateContext* Context) : ChocoState(Context) {}
	bool addChocolate(int number);
	bool exit(void);
};

bool OutOfChocolate::enterPin(int pin) // This function will request to enter a pin which access is then decided upon what number is entered in the parameters within the "enterPin" section of the main.
 {

	cout << "Please Enter Pin: " << pin << endl;
	if (((Chocolate_Dispenser*)CurrentContext)->pin == pin)
	{
		cout << "Correct pin entered." << endl; // Entering the correct pin number will allow the user to use the Chocolate Dispenser.
		CurrentContext->setState(Maintenance_Mode); // In the result of a correct pin number, the current state which is Out_Of_Chocolate will set to Maintenance mode. 
		return true; // Return true will exit out of the function and proceed to the above state.
	}

	cout << "Incorrect pin entered." << endl;
	return false; // This will cause the errors for the following functions, upon an incorrect pin entered.
}

bool MaintenanceMode::exit(void) // This function is used to exit out of the maintenance mode section which is decided upon the inventory levels within the main. 
{
	cout << "Leaving Maintenance Mode..." << endl;

	if (((Chocolate_Dispenser*)CurrentContext)->inventory == 0) CurrentContext->setState(Out_of_Chocolate); // The current state is set from maintenance mode to Out_of_Chocolate this is because, no chocolate is added to the dispenser. 

	else if (((Chocolate_Dispenser*)CurrentContext)->inventory > 0) CurrentContext->setState(No_Credit); // the current state is set from maintenance mode to No_Credit, this will only occur if the inventory is greater than 0.

	return true; // Exits out of the exit function and refers to one of two of the following function which is decided upon the value within the parameters within the main.
}

bool MaintenanceMode::addChocolate(int number) // This function adds Chocolate to the inventory. Which is entered in the relevant parameters in the main.
{
	((Chocolate_Dispenser*)CurrentContext)->inventory += number;
	cout << "Adding Chocolate... Inventory = " << ((Chocolate_Dispenser*)CurrentContext)->inventory << endl; // adds chocolate.
	return true; // Exits out of the function, although the chocolate is added during the maintenance mode. which is stated above. 
}

bool NoCredit::insertMoney(int credit) // This functions prompts the user for credit.
{
	cout << "Insert credit." << endl;
	((Chocolate_Dispenser*)CurrentContext)->credit += credit; // Points to the credit that has been inserted.
	cout << "Adding Credit... Credit = " << ((Chocolate_Dispenser*)CurrentContext)->credit << endl;
	CurrentContext->setState(Has_Credit); // the current state is set from No_Credit to Has_Credit.
	return true;
}

bool NoCredit::enterPin(int pin) // Another pin is then required to re-enter the maintenance mode.
{
	cout << "Please Enter Pin: " << pin << endl;
	if (((Chocolate_Dispenser*)CurrentContext)->pin == pin)
	{
		cout << "Correct pin entered." << endl;
		CurrentContext->setState(Maintenance_Mode);
		return true;
	}
	cout << "Incorrect pin entered." << endl;
	return false;
}

bool HasCredit::insertMoney(int credit) // this function takes the credit that has been inserted and then the dispenser decides whether the money shoudl be accepted or rejected.
{
	((Chocolate_Dispenser*)CurrentContext)->credit += credit;
	cout << "Adding credit... Credit = " << ((Chocolate_Dispenser*)CurrentContext)->credit << endl;
	return true;
}

bool HasCredit::makeSelection(int option) // This function requires to the user to select the amount of chocolate they require.
{
	//Option = number of bars, but could be used to represent a menu choice
	cout << "You have selected " << option << " bar(s) of chocolate" << endl;

	if (((Chocolate_Dispenser*)CurrentContext)->inventory < option)// if the user's selection is more than the inventory levels then the following cout message will display.
	{
		cout << "Error: you have selected more chocolate than the machine contains." << endl;
		return true;
	}

	if (((Chocolate_Dispenser*)CurrentContext)->credit < option) // if the user selects more chocolate than the credit available the following cout message will display to the console.
	{
		cout << "Error: you dont have enough money for that selection" << endl;
		return true;
	}

	cout << "Credit and inventory is sufficient for you selection. " << endl;

	((Chocolate_Dispenser*)CurrentContext)->inventory -= option; // Deduct Inventory
	((Chocolate_Dispenser*)CurrentContext)->credit -= option; // Deduct credit

	CurrentContext->setState(Dispenses_Chocolate); // sets the current state from has credit to Dispenses_Chocolate.

	return true;
}

bool HasCredit::moneyRejected(void) // this function is used to reject any insufficent funds added to the dispenser.
{
	cout << "Rejecting money....." << endl;
	((Chocolate_Dispenser*)CurrentContext)->credit = 0; // if no credit is inserted the dispenser will not proceed and it will return to the No_Credit state.
	CurrentContext->setState(No_Credit); // sets the current state from Has_Credit to No_Credit.
	return true;

}

bool DispensesChocolate::dispense(void) // this function dispenses the chocolate by displaying to the console, how much chocolate has been purchased.
{
	cout << "Dispensing..." << endl;
	cout << "Inventory = " << ((Chocolate_Dispenser*)CurrentContext)->inventory << endl; // Checks the remaining inventory levels and displays to the console.
	cout << "Credit = " << ((Chocolate_Dispenser*)CurrentContext)->credit << endl; // Checks the remaining avaliable credit and displays to the console.

	if (((Chocolate_Dispenser*)CurrentContext)->inventory == 0) CurrentContext->setState(Out_of_Chocolate); // sets the state from Dispenses_Chocolate to Out_Of_Chocolate upon an empty inventory.
	else if (((Chocolate_Dispenser*)CurrentContext)->credit == 0) CurrentContext->setState(No_Credit); // if there is 0 credit but chocolate is still avaliable in the dispenser then it will return to the No_Credit state.
	else CurrentContext->setState(Has_Credit); // sets the current state from Dispenses_Chocolate to Has_Credit.
	return true;
}
// creates an instance of the all avaliable states.
Chocolate_Dispenser::Chocolate_Dispenser(void)
{
	this->availableStates.push_back(new OutOfChocolate(this)); 
	this->availableStates.push_back(new NoCredit(this));
	this->availableStates.push_back(new HasCredit(this));
	this->availableStates.push_back(new DispensesChocolate(this));
	this->availableStates.push_back(new MaintenanceMode(this));

	this->setState(Out_of_Chocolate); // this is the state the dispenser begins at upon operation.
}
// these bool function are otherwise known as a value-returning function. its not the same as void functions as these dont return a value, although bool does.
bool Chocolate_Dispenser::enterPin(int pin)
{
	return ((ChocoState*)CurrentState)->enterPin(pin);
}

bool Chocolate_Dispenser::exit(void)
{
	return ((ChocoState*)CurrentState)->exit();
}

bool Chocolate_Dispenser::insertMoney(int credit)
{
	return ((ChocoState*)CurrentState)->insertMoney(credit);
}

bool Chocolate_Dispenser::makeSelection(int option)
{
	return ((ChocoState*)CurrentState)->makeSelection(option);
}

bool Chocolate_Dispenser::moneyRejected(void)
{
	return ((ChocoState*)CurrentState)->moneyRejected();
}

bool Chocolate_Dispenser::addChocolate(int number)
{
	return ((ChocoState*)CurrentState)->addChocolate(number);
}

bool Chocolate_Dispenser::dispense(void)
{
	return((ChocoState*)CurrentState)->dispense();
}


int main(void)
{
	Chocolate_Dispenser MyDispenser; // calls the Chocolate Dispenser class and the dispenser begins.

	//Working correctly.
	//These calls show that the Chocolate Dispenser works correctly.

	cout << "The Working Dispenser" << endl;
	cout << endl;

	MyDispenser.enterPin(54321);
	MyDispenser.addChocolate(10);
	MyDispenser.exit();
	MyDispenser.enterPin(54321);
	MyDispenser.exit();
	MyDispenser.insertMoney(10);
	MyDispenser.makeSelection(10);
	MyDispenser.dispense();

	cout << endl;
	cout << "**********************************************************" << endl;
	cout << endl;
	// Incorrect pin.
	// The following set of calls show that by entering an incorrect pin the Dispenser will display a set of errors.

	cout << "Incorrect pin" << endl;
	cout << endl;

	MyDispenser.enterPin(12345);
	MyDispenser.addChocolate(10);
	MyDispenser.exit();
	MyDispenser.enterPin(12345);
	MyDispenser.exit();
	MyDispenser.insertMoney(10);
	MyDispenser.makeSelection(10);
	MyDispenser.dispense();

	cout << endl;
	cout << "**********************************************************" << endl;
	cout << endl;

	//No chocolate avaliable.
	// The following set of calls show that if there is no chocolate available the dispenser will not allow to insert money or dispense any chocolate.
	
	cout << "No Chocolate avaliable" << endl;
	cout << endl;

	MyDispenser.enterPin(54321);
	MyDispenser.addChocolate(0);
	MyDispenser.exit();
	MyDispenser.enterPin(54321);
	MyDispenser.exit();
	MyDispenser.insertMoney(10);
	MyDispenser.makeSelection(10);
	MyDispenser.dispense();

	cout << endl;
	cout << "**********************************************************" << endl;
	cout << endl;
	
	//No Working order.
	// The following set of calls show that by not correctly ordering the function calls. It can result in a list of errors.

	cout << "Not working correctly" << endl;
	cout << endl;

	MyDispenser.enterPin(54321);
	MyDispenser.exit();
	MyDispenser.addChocolate(10);
	MyDispenser.enterPin(54321);
	MyDispenser.exit();
	MyDispenser.insertMoney(10);
	MyDispenser.makeSelection(10);
	MyDispenser.dispense();
	
	cout << endl;
	cout << "**********************************************************" << endl;
	cout << endl;
	//Not enough chocolate.
	//The following set of calls show that if the user selects more chocolate than what the dispenser holds then, the dispenser will read to the user that you have selected more chocolate than the dispenser holds.

	cout << "Not Enough Chocolate" << endl;
	cout << endl;

	MyDispenser.enterPin(54321);
	MyDispenser.addChocolate(10);
	MyDispenser.exit();
	MyDispenser.enterPin(54321);
	MyDispenser.exit();
	MyDispenser.insertMoney(15);
	MyDispenser.makeSelection(15);
	MyDispenser.dispense();
	
	

	return 0;
}