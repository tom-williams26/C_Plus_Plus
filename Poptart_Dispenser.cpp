#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum state { Out_Of_Poptart, No_Credit, Has_Credit, Dispenses_Poptart }; // Poptart Dispenser avaliable states.
enum stateParameter { No_Of_Poptarts, Credit, Cost_Of_Poptart }; // The current number of poptarts, Credit and Cost within the Dispenser.??

enum poptartBases { Plain_Base = 1, Spicy_Base = 2, Chocolate_Base = 4, Coconut_Base = 8, Fruity_Base = 16 }; // The avaliable poptart bases and their corresponding codes.
enum fillings {
	chocolate = 32, banana = 64, strawberry = 128, raspberry = 256, apple = 512, blackberry = 1024, maple = 2048,
	marshmallow = 4096, cheese = 8192, cheeseAndHam = 16384, caramel = 32768, vanilla = 65536
}; // The avaliable poptart fillings and their corresponding codes.

class StateContext; // Holds the foundation for setting states, stateParamters and retieving them when nessecary. Forward decleration.

class State
{
protected:

	StateContext * CurrentContext; // CurrentContext points to StateContext to access its members and attributes.

public:

	State(StateContext* Context)
	{
		CurrentContext = Context; // allows for selecting a state/ state parameter.
	}
	virtual ~State(void) {} // virtual deconstructor which can be accessed from other classes to ensure they are deleted.
	virtual void transition(void) {} // virtual constructor which can be accessed by the transition class.
};

class StateContext // Holds the current values of the state parameters and can also switch between states.
{
protected:

	State * CurrentState = nullptr;
	int stateIndex = 0;
	vector<State*> availableStates;
	vector<int> stateParameters;

public:
	virtual ~StateContext(void);
	virtual void setState(state newState);
	virtual int getStateIndex(void);
	virtual void setStateParam(stateParameter SP, int value);
	virtual int getStateParam(stateParameter SP); // Refers to the apporiate state parameter and retrieves it. e.g.(Credit or Cost_Of_Poptart).
};

StateContext::~StateContext(void)
{
	for (unsigned int i = 0; i < this->availableStates.size(); i++) delete this->availableStates[i]; // takes the size of the vector and deletes the states at the end of runtime.
	this->availableStates.clear();
	this->stateParameters.clear();
}

//
void StateContext::setState(state newState)
{
	this->CurrentState = availableStates[newState]; // takes the newstate parameter and stores it in the current state..
	this->stateIndex = newState;
	this->CurrentState->transition();
}

int StateContext::getStateIndex(void)
{
	return this->stateIndex; // returns the current state. 
}

void StateContext::setStateParam(stateParameter SP, int value)
{
	this->stateParameters[SP] = value; // takes a state parameter and assigns it with a value e.g. (Credit, 0) this will initiaize credit to zero.
}

int StateContext::getStateParam(stateParameter SP)
{
	return this->stateParameters[SP]; // Returns the specified state parameter.
}

//If any of the following methods are set to true. The method is executed, otherwise if the method returns false the below messages are displayed with any custom error message in the specific method.
class Transition
{
public:
	virtual bool insertMoney(int) { cout << "Error!" << endl; return false; }
	virtual bool makeSelection(int) { cout << "Error!" << endl; return false; }
	virtual bool moneyRejected(void) { cout << "Error!" << endl; return false; }
	virtual bool addPoptart(int) { cout << "Error!" << endl; return false; }
	virtual bool dispense(void) { cout << "Error!" << endl; return false; }
};

class PoptartState : public State, public Transition
{
public:

	PoptartState(StateContext* Context) : State(Context) {}
};

/*** OUT OF POPTART CLASS/STATE	***/

class OutOfPoptart : public PoptartState
{
public:
	OutOfPoptart(StateContext* Context) : PoptartState(Context) {}
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
};

/*** NO CREDIT CLASS/STATE	***/

class NoCredit : public PoptartState
{
public:
	NoCredit(StateContext* Context) : PoptartState(Context) {}
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
};

/*** HAS CREDIT CLASS/STATE	***/

class HasCredit : public PoptartState
{
public:
	HasCredit(StateContext* Context) : PoptartState(Context) {};
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);

};

/*** DISPENSES POPTART CLASS/STATE	***/

class DispensesPoptart : public PoptartState
{
public:
	DispensesPoptart(StateContext* Context) : PoptartState(Context) {}
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
};

/////////////////////////////////Decorator Pattern//////////////////////////////////////

/***Product class***/
class Product
{
	friend class Filling;
protected:
	string product_description;
	int itemCost = 0;
public:
	virtual void consume(void);
	virtual int cost(void);
	virtual string description(void);
};

string Product::description(void)
{
	return this->product_description; // returns the apporiate poptart
}

int Product::cost(void)
{
	return this->itemCost; // returns the apporiate cost of poptart
}

void Product::consume(void)
{
	delete this; //deletes the poptart.
}

/***Poptart class / Base constructor***/

class Poptart : public Product
{
public:
	Poptart(void)
	{
		this->product_description = "Poptart"; // description/ name of poptart.
		this->itemCost = 50; // item cost of poptart.
	}
};

/***PlainBase class / constructor***/

class PlainBase : public Poptart
{
public:
	PlainBase(void)
	{
		this->product_description = "Plain";
		this->itemCost = 100;
	}
};

/***SpicyBase class / constructor***/

class SpicyBase : public Poptart
{
public:
	SpicyBase(void)
	{
		this->product_description = "Spicy";
		this->itemCost = 150;
	}
};

/***ChocolateBase class / constructor***/

class ChocolateBase : public Poptart
{
public:
	ChocolateBase(void)
	{
		this->product_description = "Chocolate";
		this->itemCost = 200;
	}
};

/***CoconutBase class / constructor***/

class CoconutBase : public Poptart
{
public:
	CoconutBase(void)
	{
		this->product_description = "Coconut";
		this->itemCost = 200;
	}
};

/***FruityBase class / constructor***/

class FruityBase : public Poptart
{
public:
	FruityBase(void)
	{
		this->product_description = "fruity";
		this->itemCost = 200;
	}
};

/***Filling class / constructor***/

class Filling :public Product
{
public:
	Filling(void)
	{
		this->product_description = "filling";
		this->itemCost = 20;
	}
};

//Decorator class

class FillingDecorator : public Filling
{
protected:
	Product * addFilling;

public:
	virtual int cost(void);
	virtual string description(void);
	void addToPoptart(Product* newPoptartFilling);
	~FillingDecorator(void);

};

int FillingDecorator::cost(void)
{
	return this->itemCost + addFilling->cost(); // adds the cost of the poptart and adds it to the cost of the filling.
}

string FillingDecorator::description(void)
{
	return this->addFilling->description() + " + " + description; // adds the name of the filling to the descirpton of poptart.
}

void FillingDecorator::addToPoptart(Product* newPoptartFilling)
{
	addFilling = newPoptartFilling; // takes add filling and stores it in newPoptartFilling.
}

FillingDecorator::~FillingDecorator(void)
{
	delete this->addFilling; // deletes the approprate filling.
}


/***ChocolateFilling class / constructor***/

class Chocolate : public FillingDecorator
{
public:
	Chocolate(void)
	{
		this->product_description = "Chocolate"; //Description/ name of filling
		this->itemCost = 20; // price of filling.
	}
};

/***BananaFilling class / constructor***/

class Banana : public FillingDecorator
{
public:
	Banana(void)
	{
		this->product_description = "Banana";
		this->itemCost = 50;
	}
};

/***StrawberryFilling class / constructor***/

class Strawberry : public FillingDecorator
{
public:
	Strawberry(void)
	{
		this->product_description = "Strawberry";
		this->itemCost = 50;
	}
};

/***RaspberryFilling class / constructor***/

class Raspberry : public FillingDecorator
{
public:
	Raspberry(void)
	{
		this->product_description = "Raspberry";
		this->itemCost = 50;
	}
};

/***AppleFilling class / constructor***/

class Apple : public FillingDecorator
{
public:
	Apple(void)
	{
		this->product_description = "Apple";
		this->itemCost = 50;
	}
};

/***BlackberryFilling class / constructor***/

class Blackberry : public FillingDecorator
{
public:
	Blackberry(void)
	{
		this->product_description = "Blackberry";
		this->itemCost = 50;
	}
};
/***MapleFilling class / constructor***/

class Maple : public FillingDecorator
{
public:
	Maple(void)
	{
		this->product_description = "Maple";
		this->itemCost = 100;
	}
};

/***MarshmallowFilling class / constructor***/

class Marshmallow : public FillingDecorator
{
public:
	Marshmallow(void)
	{
		this->product_description = "Marshmallow";
		this->itemCost = 20;
	}
};

/***CheeseFilling class / constructor***/

class Cheese : public FillingDecorator
{
public:
	Cheese(void)
	{
		this->product_description = "Cheese";
		this->itemCost = 70;
	}
};

/***CheeseAndHamFilling class / constructor***/

class CheeseAndHam : public FillingDecorator
{
public:
	CheeseAndHam(void)
	{
		this->product_description = "CheeseAndHam";
		this->itemCost = 100;
	}
};

/***MarshmallowFilling class / constructor***/

class Caramel : public FillingDecorator
{
public:
	Caramel(void)
	{
		this->product_description = "Caramel";
		this->itemCost = 20;
	}
};

/***VanillaFilling class / constructor***/

class Vanilla : public FillingDecorator
{
public:
	Vanilla(void)
	{
		this->product_description = "Vanilla";
		this->itemCost = 50;
	}
};

//////////////////////////////End of Decorator Pattern////////////////////////////////////////

class Poptart_Dispenser : public StateContext, public Transition
{
	friend class DispensesPoptart;
	friend class HasCredit;
private:
	PoptartState * PoptartCurrentState = nullptr;
	bool itemDispensed = false;
	//indicates whether a product is there to be retrieved
	Product* DispensedItem = nullptr;
	bool itemRetrieved = false; //indicates whether a product has been retrieved
public:
	Poptart_Dispenser(int inventory_count);
	~Poptart_Dispenser(void);
	bool insertMoney(int money);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addPoptart(int number);
	bool dispense(void);
	Product* getProduct(void);
	virtual void setStateParam(stateParameter SP, int value);
	virtual int getStateParam(stateParameter SP);
};

Poptart_Dispenser::~Poptart_Dispenser(void)
{
	//When itemRetrieved is called the dispenseditem is deleted.
	if (!this->itemRetrieved)
	{
		delete this->DispensedItem;
	}
}

bool Poptart_Dispenser::insertMoney(int money)
{
	PoptartCurrentState = (PoptartState*)this->CurrentState;
	return this->PoptartCurrentState->insertMoney(money);
}

bool Poptart_Dispenser::makeSelection(int option)
{
	PoptartCurrentState = (PoptartState*)this->CurrentState;
	return this->PoptartCurrentState->makeSelection(option);
}

bool Poptart_Dispenser::moneyRejected(void)
{
	PoptartCurrentState = (PoptartState*)this->CurrentState;
	return this->PoptartCurrentState->moneyRejected();
}

bool Poptart_Dispenser::addPoptart(int number)
{
	PoptartCurrentState = (PoptartState*)this->CurrentState;
	return this->PoptartCurrentState->addPoptart(number);
}

bool Poptart_Dispenser::dispense(void)
{
	PoptartCurrentState = (PoptartState*)this->CurrentState;
	return this->PoptartCurrentState->dispense();
}

Product* Poptart_Dispenser::getProduct(void)
{

	// itemDispensed returns the Dispensed item.
	if (this->itemDispensed)
	{
		this->itemDispensed = false; // unless itemDispensed is set to true this statement won't execute.
		this->itemRetrieved = true; // deletes the itemRetrieved.
		return this->DispensedItem; // returns the dispensed item.
	}

	return nullptr;
}
void Poptart_Dispenser::setStateParam(stateParameter SP, int value)
{
	// a new value is specified and overwrites the exist value of the cost of poptart corresponding with the selected poptart and filling if there is one.
	if (SP == Cost_Of_Poptart) return;
	this->stateParameters[SP] = value;
}

int Poptart_Dispenser::getStateParam(stateParameter SP)
{
	// takes the value of SP and stores it in Cost_Of_Poptart.
	if (SP == Cost_Of_Poptart)
	{
		if (DispensedItem == nullptr) return 0; // If DispensedItem doesn't hold a value return zero.
		return DispensedItem->cost(); // Returns the current cost of the poptart.
	}
	return this->stateParameters[SP]; // cost of poptart is returned within the parameter SP.
}

Poptart_Dispenser::Poptart_Dispenser(int inventory_count)
{
	//Creates new elements/ states of the poptart dispenser as stated in the state diagram.
	this->availableStates.push_back(new OutOfPoptart(this));
	this->availableStates.push_back(new NoCredit(this));
	this->availableStates.push_back(new HasCredit(this));
	this->availableStates.push_back(new DispensesPoptart(this));

	this->stateParameters.push_back(0); // No of Poptarts
	this->stateParameters.push_back(0); // Available Credit

	this->setState(Out_Of_Poptart); // Out_Of_Poptarts is the first state that is set upon runtime.
	if (inventory_count > 0) // If the inventory_count is greater than zero execute the following.
	{
		this->addPoptart(inventory_count);// adds poptarts to the inventory count.
	}
}

/*** OUT OF POPTART CLASS/STATE	***/

bool OutOfPoptart::insertMoney(int money)
{
	cout << "Error! No poptarts left!" << endl;
	this->moneyRejected(); // Credits are returned if the dispenser is out of poptarts.
	CurrentContext->setStateParam(Credit, 0); // The Credit parameter is given a value of zero by replacing the orginal value with the new value within the parameters.
	CurrentContext->setState(Out_Of_Poptart); // Sets the current state to Out of poptarts (For clarity).
	return true;
}

bool OutOfPoptart::makeSelection(int option)
{
	cout << "Error! No Poptarts left! No selection can be made..." << endl;
	return false; // Will force the method not to execute as its not valid path between states.
}

bool OutOfPoptart::moneyRejected(void)
{
	if (CurrentContext->getStateParam(No_Of_Poptarts) == 0)  // Regardless of the dispenser containing any poptarts the current credits are rejected.
	{														 // If the poptart dispenser is out of poptarts it is possible to reject any remaining credits.
		cout << "Ejecting money! No poptarts remaining..." << endl;
	}
	else
	{
		cout << "Ejecting money!" << endl;

	}
	this->CurrentContext->setStateParam(Credit, 0); // The Credit parameter is given a value of zero by replacing the orginal value with the new value within the parameters..
	this->CurrentContext->setState(Out_Of_Poptart); // Sets the current state to Out of poptarts (For clarity).
	return true; // Allows this method to execute as there is a valid relationship between states.
}

bool OutOfPoptart::addPoptart(int number)
{
	cout << "Adding " << number << " poptarts..." << endl; // outputs the current avaliable poptarts to the console.
	number += this->CurrentContext->getStateParam(No_Of_Poptarts); // This allows to add poptarts and also add more later on it run time if needed, as long as it adheres the state Diagram.
	this->CurrentContext->setStateParam(No_Of_Poptarts, number);   // This sets the current number of poptarts to the value stored within number which will be the number of avaliable poptarts.
	if (this->CurrentContext->getStateParam(No_Of_Poptarts) > 0)   // If the number of poptarts is greater than zero set the state to no credit.
	{
		this->CurrentContext->setState(No_Credit);				   // Sets the current state to no credit.
	}

	return true; // allows this method to execute as it is a valid relationship between states.
}

bool OutOfPoptart::dispense(void)
{
	cout << "Error! No Poptarts left! Nothing to Dispense!" << endl;
	return false; // Its not possible to dispense a poptart while the dispenser is has no poptarts avaliable. this results with the method not being called.
}

/*** NO CREDIT CLASS/STATE	***/

bool NoCredit::insertMoney(int money)
{

	cout << "Inserting " << money << " Credits..." << endl; // Takes the value of the integer money and replaces it with a number outputting the number of credits to the console.
	this->CurrentContext->setStateParam(Credit, money);     // Credit takes the value of money and stores it in Credit parameter.
	if (CurrentContext->getStateParam(Credit) > 0)		    // As long as there is credits in the dispenser the following code is executed.
	{
		this->CurrentContext->setState(Has_Credit); // Switches the state from No Credit to Has Credit.
	}
	cout << "Avaliable credits: " << money << endl; // Outputs the avaliable credits to the console.
	return true; // allows this method to execute as it is a valid relationship between states.
}

bool NoCredit::makeSelection(int option)
{
	cout << "Error! Please Insert Credit before making a selection..." << endl; // A selection can't be made without any availiable credit and there is no valid method for the state no Credit to make a selection.
	return false; // allows this method to execute as it is a valid relationship between states.
}

bool NoCredit::moneyRejected(void)
{
	cout << "Error! Please insert money!" << endl; // If there is no credit, no money can be rejected.
	return false; // It is not possible to eject credits if there is no credit avaliable.
}

bool NoCredit::addPoptart(int number)
{
	cout << "Error! Already got poptart!" << endl; // Dispenser already contains Poptarts from the Out of poptart state.
	return false; // Not possible to add poptarts in a No Credit state.
}

bool NoCredit::dispense(void)
{
	cout << "Error! No Money!" << endl;
	return false; // No poptarts can be dispense if there is no credit in the dipenser.
}

/*** HAS CREDIT CLASS/STATE	***/

bool HasCredit::insertMoney(int money)
{
	unsigned int currentBalance = this->CurrentContext->getStateParam(Credit); // The state parameter credit is stored within a integer called currentBalance
	currentBalance += money; // Allows for adding more credits to the existing credits. 

	cout << "Inserting " << money << " Credits..." << endl; // Outputs the credits being inserted.
	this->CurrentContext->setStateParam(Credit, currentBalance); // the new value overwrittes the existing value of Credit.

	cout << "Avaliable credits: " << currentBalance << endl; // Outputs the current balance to the console. 
	this->CurrentContext->setState(Has_Credit); // Sets the state from HasCredit to HasCredit For clarity.
	return true; // The user may want to add additonal credits to the dispenser and it adheres to the state diagram.
}

bool HasCredit::makeSelection(int option)
{
	Product* newProduct = nullptr; // newProduct points to the Class Product and is set to nullptr.
	FillingDecorator* newFilling = nullptr; // newFilling points to the class filling decorator and points to nullptr.

	switch (option & 31) // The switch allows the user to select a poptarts from multiple options.
	{
	case 1: // If this option is selected a new object of the base is created.
		newProduct = new PlainBase; // A new object of plain base is created and stored in newProduct.
		cout << newProduct->description() << " poptart selected!" << endl; // outputs the description/ name of the poptart.
		break; // exits the switch statement.

	case 2: // If this option is selected a new object of the base is created.
		newProduct = new SpicyBase; // A new object of spicy base is created and stored in newProduct.
		cout << newProduct->description() << " poptart selected!" << endl; // outputs the description/ name of the poptart.
		break; // exits the switch statement.

	case 4: // If this option is selected a new object of the base is created.
		newProduct = new ChocolateBase; // A new object of chocolate base is created and stored in newProduct.
		cout << newProduct->description() << " poptart selected!" << endl; // outputs the description/ name of the poptart.
		break; // exits the switch statement.

	case 8: // If this option is selected a new object of the base is created.
		newProduct = new CoconutBase; // A new object of Coconut base is created and stored in newProduct.
		cout << newProduct->description() << " poptart selected!" << endl; // outputs the description/ name of the poptart.
		break; // exits the switch statement.

	case 16: // If this option is selected a new object of the base is created.
		newProduct = new FruityBase; // A new object of Fruity base is created and stored in newProduct.
		cout << newProduct->description() << " poptart selected!" << endl; // outputs the description/ name of the poptart.
		break; // exits the switch statement.

	default: // if a option other that the ones above is selected. 
		cout << "Invalid option!" << endl; // if the user enters a invalid option.
		return false; // If a one of the above poptart bases isn't selected, a selection isn't made.
		break;
	}

	if (option & 32) // Chocolate option / filling
	{
		newFilling = new Chocolate; // A new object of the chocolate filling is created.
		newFilling->addToPoptart(newProduct); // the new filling is then added to the newProduct.
		newProduct = newFilling; // The new product becomes the new filling.

		cout << "Chocolate filling selected!" << endl;
	}

	if (option & 64) // Banana option / filling
	{
		newFilling = new Banana;  // A new object of the banana filling is created.
		newFilling->addToPoptart(newProduct); // the new filling is then added to the newProduct.
		newProduct = newFilling; // The new product becomes the new filling.

		cout << "Banana filling selected!" << endl;
	}

	if (option & 128) // Strawberry option / filling
	{
		newFilling = new Strawberry;  // A new object of the strawberry filling is created.
		newFilling->addToPoptart(newProduct); // the new filling is then added to the newProduct.
		newProduct = newFilling; // The new product becomes the new filling.

		cout << "Strawberry filling selected!" << endl;
	}

	if (option & 256) // Raspberry option / filling
	{
		newFilling = new Raspberry;  // A new object of the raspberry filling is created.
		newFilling->addToPoptart(newProduct); // the new filling is then added to the newProduct.
		newProduct = newFilling; // The new product becomes the new filling.

		cout << "Raspberry filling selected!" << endl;
	}

	if (option & 512) // Apple option / filling
	{
		newFilling = new Apple;  // A new object of the apple filling is created.
		newFilling->addToPoptart(newProduct); // the new filling is then added to the newProduct.
		newProduct = newFilling; // The new product becomes the new filling.

		cout << "Apple filling selected!" << endl;
	}

	if (option & 1024) // Blackberry option / filling
	{

		newFilling = new Blackberry;  // A new object of the blackberry filling is created.
		newFilling->addToPoptart(newProduct); // the new filling is then added to the newProduct.
		newProduct = newFilling; // The new product becomes the new filling.

		cout << "Blackberry filling selected!" << endl;
	}

	if (option & 2048) // Maple option / filling
	{
		newFilling = new Maple;  // A new object of the maple filling is created.
		newFilling->addToPoptart(newProduct); // the new filling is then added to the newProduct.
		newProduct = newFilling; // The new product becomes the new filling.

		cout << "Maple filling selected!" << endl;
	}

	if (option & 4096) // Marshmallow option / filling
	{
		newFilling = new Marshmallow;  // A new object of the marshmallow filling is created.
		newFilling->addToPoptart(newProduct); // the new filling is then added to the newProduct.
		newProduct = newFilling; // The new product becomes the new filling.

		cout << "Marshmallow filling selected!" << endl;
	}

	if (option & 8192) // Cheese option / filling
	{
		newFilling = new Cheese;  // A new object of the cheese filling is created.
		newFilling->addToPoptart(newProduct); // the new filling is then added to the newProduct.
		newProduct = newFilling; // The new product becomes the new filling.

		cout << " Cheese filling selected!" << endl;
	}

	if (option & 16384) // Cheese and ham option / filling
	{
		newFilling = new CheeseAndHam;  // A new object of the cheese and ham filling is created.
		newFilling->addToPoptart(newProduct); // the new filling is then added to the newProduct.
		newProduct = newFilling; // The new product becomes the new filling.

		cout << "Cheese and ham filling selected!" << endl;
	}

	if (option & 32768) // Caramel option / filling
	{
		newFilling = new Caramel;  // A new object of the caramel filling is created.
		newFilling->addToPoptart(newProduct); // the new filling is then added to the newProduct.
		newProduct = newFilling; // The new product becomes the new filling.

		cout << "Caramel filling selected!" << endl;
	}

	if (option & 65536) // Vanilla option / filling
	{
		newFilling = new Vanilla;  // A new object of the vanilla filling is created.
		newFilling->addToPoptart(newProduct); // the new filling is then added to the newProduct.
		newProduct = newFilling; // The new product becomes the new filling.

		cout << "Vanilla filling selected!" << endl;
	}
	if (option && !32 || !64 || !128 || !256 || !512 || !1024 || // If invalid option codes are entered e.g.(1 or 9999) then a selection won't be made.
		!2048 || !4096 || !8192 || !16384 || !32768 || !65536)
	{
		cout << "invalid filling" << endl;
		return false; // returns false  when the incorrect selection of filling has been made.
	}


	((Poptart_Dispenser*)this->CurrentContext)->DispensedItem = newProduct; // newProduct is stored in DispensedItem.
	((Poptart_Dispenser*)this->CurrentContext)->itemRetrieved = false; // ItemRetrieved is set to false, because this will otherwise delete the DispensedItem.

	this->CurrentContext->setState(Dispenses_Poptart); // Sets state to Dispenses Poptart.
	return true; // making a selection within the HasCredit is adhering to the state diagram and is a valid path between HasCredit and DispensesPoptart states.
}

bool HasCredit::moneyRejected(void)
{
	cout << "Returning remaining balance..." << endl;

	CurrentContext->setStateParam(Credit, 0); // Sets the Credit to zero.
	this->CurrentContext->setState(No_Credit); // Sets the state to NoCredit.
	return true; // this method is accepted in case the user wants to eject their credits.
}

bool HasCredit::addPoptart(int number)
{
	cout << "Error! Poptarts already added... " << endl;
	return false; // Cannot add poptarts in the has credit state.
}

bool HasCredit::dispense(void)
{
	cout << "Unable to dispense poptart! Please make a selection.." << endl;
	cout << endl;
	return false; // Dispensing an item before a selection is made is not possible.
}

/*** DISPENSES POPTART CLASS/STATE	***/

bool DispensesPoptart::insertMoney(int money)
{
	cout << "Error! Not able to add credit when dispensing. " << endl;
	return false; // Credits can't be inserted during the dispensesPoptart state.
}

bool DispensesPoptart::makeSelection(int option)
{
	cout << "You have already made a selection. Please wait.." << endl;
	return false; // this returns false as a selection isn't made in dispensesPoptart.
}

bool DispensesPoptart::moneyRejected(void)
{
	cout << "Dispensing poptart! Please wait.." << endl;
	return false; // Not able to reject money while dispensing a poptart.
}

bool DispensesPoptart::addPoptart(int number)
{
	cout << "Poptarts already added... " << endl;
	return false; // Unable to add poptarts while dispensing them.
}

bool DispensesPoptart::dispense(void) // Dispenses poptarts	
{

	if (CurrentContext->getStateParam(No_Of_Poptarts) == 0) // If the poptart dispenser doesn't contain any more poptarts, then step within this condition.
	{
		cout << "Dispenser empty!" << endl;
		this->CurrentContext->setState(Out_Of_Poptart); // Sets the state to "Out of poptarts", only when the dispenser meets the above condition.

	}
	else if (CurrentContext->getStateParam(Credit) == 0
		&& CurrentContext->getStateParam(No_Of_Poptarts) > 0) // If there is insufficient credits but there are poptarts still avaliable, then step within this condition
	{
		cout << "Out of Credit... Please insert credit.." << endl;
		this->CurrentContext->setState(No_Credit); // Sets the state to "No Credit", only when the dispenser meets the above condition.

	}
	else if (CurrentContext->getStateParam(No_Of_Poptarts) > 0
		&& CurrentContext->getStateParam(Credit) > 0) // If there is sufficient credits and poptarts are still avaliable, then step within this condition.
	{
		if (CurrentContext->getStateParam(Credit) > CurrentContext->getStateParam(Cost_Of_Poptart)) // This condition is met as long as there is sufficient credits and poptarts still avaliable.
		{
			cout << endl << "Cost of poptart: " << CurrentContext->getStateParam(Cost_Of_Poptart) << endl; // Outputs the total cost of the poptart to the console whether any fillings were added or not.
			cout << "Selection in progress...  Poptart dispensing!" << endl;

			CurrentContext->setStateParam(Credit, CurrentContext->getStateParam(Credit) - CurrentContext->getStateParam(Cost_Of_Poptart)); // The state parameter "Credit" is given a new value as a new parameter is set for the new value to be replace the current value.
																																		   // The current "Credit" is subtracted from the "Cost of poptart" originally added. leaving the new value which is stored in setStateParam.
			cout << "Credit remaining: " << CurrentContext->getStateParam(Credit) << endl; // The new value is outputs to the console.

			((Poptart_Dispenser*)CurrentContext)->itemDispensed = true; // Once itemDispensed is set to true the poptart including any fillings which is stored in DispensedItem will be returned and deleted as itemRetrieved deletes the dispensedItem.
			((Poptart_Dispenser*)CurrentContext)->itemRetrieved = true; // This allows the newProduct which is stored in dispensedItem to be deleted.
			CurrentContext->setStateParam(No_Of_Poptarts, CurrentContext->getStateParam(No_Of_Poptarts) - 1); // The state parameter "No of poptart" is given a new value as a new parameter is set for the new value to be replace the current value.
																											  // Once an item is dispensed, the number of poptarts subtract one from the total amount of poptarts originally added. leaving the new value which is stored in setStateParam.
			cout << endl << "Poptarts remaining: " << CurrentContext->getStateParam(No_Of_Poptarts) << endl;  // The new value is outputs to the console.

			cout << endl << "Make another selection..." << endl;
			this->CurrentContext->setState(Has_Credit); // The Current state switches from DispensesPoptart to Has Credit, ready for another selection to made.
		}
		else
		{
			cout << "Insufficent credits! Please insert Credits.." << endl;
			return false;
		}
	}

	return true;
}