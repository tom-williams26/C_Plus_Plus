#include <iostream>

using namespace std;

/*
Function templates are used whenever we need several different functions with the same
problem-solving logic, but which differ only in the types of the parameters the work with.
Class templates can be used whenever we need several class that only differ in the types
of some of their data members, or in the tpes of the parametersof their member functions.
*/
template <typename T>

/*
A node is a part of a linked list which contains one or more members that hold data. Each node contains a seccessor pointer that points to the next node in the list.
The first node of a non-empty linked list is called the head of the list. To gain access to the nodes in a linked list, a pointer is required at the head of the list.
Starting with the head, the nodes can be accessed in the list by following the successor pointers stored in each node. The successor pointer in the last node is set to NULL pointer which brings the list to an end.
*/
class Node
{
public:
	T value;					// Stores a single data item of the data type
	Node *pNext = nullptr;		// Points to the next node.
	Node *pPrevious = nullptr;  // Points to the previous node.
								// Nullptr = Ends sequence.
};

template <typename T>
class Stack
{
public:

	~Stack(void);
	void Push(T value);
	Node<T>* NodePop(void);
	T pop(void);

protected:
	int count = 0;				// This variable is used to hold a value within the count mechanics in the main function.
	Node<T> *pTop = nullptr;	// Calls the node class and sends the next value to the top until it reaches the end of the sequence.
};

/*
The virtual characteristic is inherited  by a member function of a derived class overides
a virtual function in the base class then that member is automatically virtual itsself.
*/
template <typename T>
class Queue : protected Stack<T>
{
private:
	Node<T> *pFront = nullptr;	// Sends the next value to the front of the queue until it reaches the end of the sequence.

public:
	Queue(void);
	~Queue(void);
	virtual void enqueue(T value);
	virtual Node<T>* nodeDequeue(void);
	virtual T dequeue(void);
};

/*
Destrcutors are automatically called when an object is destroyed. Destrcutors are used to perform shutdown operations when an object ceases to exist.
This happens when a program stops excuting or when you return from a function that created an object.
*/
template <typename T>
Stack<T>::~Stack(void)

{
	while (pTop != nullptr) // As long as pTop isnt equal to NULL then an integer is declared which is used to mark the top of the stack. It specifies the position of the next item that will be added back to the stack. 
	{
		delete NodePop();
	}   // Terimnates the "NodePop" function.
}

/*
The Push function simply creates a new node whose value is the number to be pushed on to the stack
and whose successor pointer is the node that is currently at the top of the stack, making the newly
created node the new top of the stack.
*/
template <typename T>
void Stack<T>::Push(T value)
{
	Node<T>* pTmp = new Node<T>; // Creates a copy of a node and saves it as pTmp.
	pTmp->value = value;		 // pTmp is then saved as value.
	pTmp->pNext = pTop;			 // pTmp is then forwarded on as the top node of the stack.
	pTop = pTmp;				 // pTop is the new node that was copied.
}

/*
As long as the nodes keep pushing in the stack, this function will keep redirecting
the nodes to the top of the stack and continue to pop until the value reaches zero.
*/
template <typename T>
Node<T>* Stack<T>::NodePop(void)
{
	Node<T> *pTmp = pTop;						// The tempoary node is moved to the top of the stack.
	if (pTop != nullptr) pTop = pTop->pNext;	// As long as pTop doesnt equal NULL. Then pTop is the following node to be processed while "pTop->pNext will become the next node in the stack.

	return pTmp;								// This will keep creating copies of nodes and assigning them with the next value until it reaches zero.
}


/*
The pop function removes elements off the top of the stack.
Firstly, the function calls "pTmp != nullptr" to determine if there is any nodes in the stack.
If not then the function will pass to "delete pTmp".
*/
template <typename T>
T Stack<T>::pop(void)
{
	Node<T> *pTmp = NodePop();	// If pTmp still exists then the NodePop function is called.
	int ret = 0;				// Declares a variable called "ret".
	if (pTmp != nullptr)		// As long as pTmp doesnt equal NULL. The following statement is then excuted.
	{
		ret = pTmp->value;		// The variable which was declared will become the same value as pTmp. Additonally the value object is deferencing pTmp as it come to the end of the cycle.
	}
	else
	{
		throw "Stack Empty";	// Throws the excpectation of the stack being empty. This will only occur when the variable "ret" reaches zero.
	}

	delete pTmp;				// The copy of the node is deleted, this can only occur if the stack reaches NULL.

	return ret;					// This holds the next value in the sequence and stores it, until it is ready to be pushed out onto the stack.
}

/*
This function queues the stack in ascending order, meaning the last node
that was at the top of the stack will be brought to the front of the queue.
*/
template <typename T>
Queue<T>::Queue(void)
{
	pFront = pTop = nullptr;	// The node at the top of the stack becomes the value at the front on the queue and excutes in order, until the sequuence has ended.
}

/*
This function terminates the queue once the sequence has come to an end.
*/
template<typename T>
Queue<T>::~Queue(void)
{
	//uses stack destructor
}

/*
The Enqueue function at first starts with no elements within it.
The Enqueue function inserts an element/node to the rear of the queue.
*/
template<typename T>
void Queue<T>::enqueue(T value)
{
	this->Push(value);						// This line is accessing the push function and retrieving the current value from the function.

	if (pFront == nullptr) pFront = pTop;	// Whilst the enqueue is still outputting values to the end of the queue the sequence will not end.
	else (pTop->pNext)->pPrevious = pTop;	// This outputs the next value and queues it behind the current node.
}

/*
This function takes the node at the beginning of the queue and
processes each node until they have all been removed from the queue.
*/
template <typename T>
Node<T>* Queue<T>::nodeDequeue(void)
{
	Node<T> *pTmp = pFront;								   // Takes the temporary node which is then next to be removed from the queue.
	if (pFront != nullptr)								   // Whilst pFront isn't equal to NULL, it will excute the following conditions.
	{
		pFront = pFront->pPrevious;						   // Points to the node that was queued behind the current node.
		if (pFront != nullptr) pFront->pNext = nullptr;	   // Will move to the next node ready to be removed from the queue until the queue has nothing left to remove.
	}
	return pTmp;										   // Stores the tempoary node pTmp, until it is required again.					
}

/*
The dequeue function removes elements from the front of the queue 
and sends the data back to the main to output to the console.
*/
template<typename T>
T Queue<T>::dequeue(void)
{
	Node<T> *pTmp = nodeDequeue();
	T ret = 0;							  // Declaring a variable called T ret, this will be used to store the value.
	if (pTmp != nullptr)				  // While pTmp has not reached the end of the sequence, it will excute the following: -
	{
		ret = pTmp->value;				  // ret holds the value of pTmp and dereferences from value. 
	}
	else								  // This condition is only reached once the end of the sequence had been reached.
	{
		throw "Queue Empty";			  // This exception is called once the end of the sequence has been reached.
	}
	if (pFront == nullptr) pTop = pFront; // The last node has been deleted.

	delete pTmp;						  // The copy of the node is deleted.

	return ret;							  // This holds the next value in the sequence and stores it.
}

/*
The Main function of the program will create a temporary node and stores a value within it and will send it to the top of the stack ready to be popped off the top.
Once 10 values have been popped off the stack, the values are then sorted into a queue in ascending order and are dequeued in order. (FIFO)
*/
int main(void)
{
	Stack<int> MyStack;								// Calls the Stack class and excutes all the nessecary functions.
	Queue<int> MyQueue;								// Calls the Queue class and excutes all the nessecary functions.

	for (int count = 0; count <= 10; count++)		// Once the count of this loop reaches 10 then this loop will end and the function will proceed.
	{
		MyStack.Push(count);						// The Stack is loaded with 10 available values.
		MyQueue.enqueue(count);						// The Queue is loaded with 10 available values.
	}

	try												// As long as this function has excuted correctly so far, then this try block will excute. 
	{
		{
			cout << "Stack Output:" << endl;		// The try block begins by outputting this message to the console.
		}

		while (true)								// This while loop is then excuted. It will keep looping until there are no more values to be popped from the stack. When the Stack is empty, the loop ends.
		{
			cout << MyStack.pop() << " ";		    // Outputs the values of count in reversed order to the console, once the pop function has been excuted.
		}

	}
	catch (...)										// This catch block handles any exceptions and then seeks control over the try block.
	{
		cout << endl;								// Creates a new line ready to output the Queue to the console.
	}

	try												// As long as this function has excuted correctly so far, then another try block will excute. 
	{
		cout << "Queue output" << endl;				// The try block begins by outputting this message to the console.

		while (true)								// Another while loop is then excuted. It will keep looping until there are no more values to be removed from the queue. When the Queue is empty, the loop ends.
		{
			cout << MyQueue.dequeue() << " ";		// Outputs the values of count in correct order to the console, once the dequeue function has been removed them from the dequeue.
		}

	}
	catch (...)										// This catch block handles any exceptions and then seeks control over the try block.
	{
		cout << endl;								// Creates a new line ready to output the Queue to the console.
	}

	return 0;										// Ends program.
}