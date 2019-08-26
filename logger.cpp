#include <iostream>
#include <string>
using namespace std;

#pragma region Logger_Class
enum LoggerType { L_TXT_FILE, L_BIN_FILE, L_CONSOLE};
enum Format {NO_FORMAT, HTML_FORMAT, ENC_FORMAT};

class Logger
{
private:
	unsigned formatType;
public:
	virtual void log(string msg) {};
};
#pragma endregion

#pragma region LoggerDecorator_Class
class LoggerDecorator : public Logger
{
private:
	Logger *contents;
public:
	void log(string msg);
	LoggerDecorator(Logger *contents);

};

LoggerDecorator::LoggerDecorator(Logger *acontents)
	: contents(acontents) {};

void LoggerDecorator::log(string msg)
{

	contents->log(msg);
}



class HTMLLogger : public LoggerDecorator
{
public:
	HTMLLogger(Logger * logger);
	void log(string msg);
	string makeHTML(string msg);
};

HTMLLogger::HTMLLogger(Logger *alogger) : LoggerDecorator(alogger) {};

void HTMLLogger::log(string msg)
{
	msg = makeHTML(msg);
	LoggerDecorator::log(msg);
}

string HTMLLogger::makeHTML(string msg)
{
	cout << " HTML" << endl;
	return "<HTML><BODY><b>" + msg + "</b></BODY></HTML>";
}

class EncyptLogger : public LoggerDecorator
{
public:
	string encryptDecrypt(string toEncrypt)
	{
		char key = 'A';
		string output = toEncrypt;
		for (int i = 0; i < toEncrypt.size(); i++)
			output[i] = toEncrypt[i] ^ key;
		return output;
	}
	EncyptLogger(Logger *aLogger) : LoggerDecorator(aLogger) {};
	void log(string msg)
	{
		msg = encryptDecrypt(msg);
		LoggerDecorator::log(msg);
	}

};
#pragma endregion

#pragma region specificLogger_Classes
class ConsoleLogger : public Logger
{
public:
	void log(string msg)
	{
		cout << "Logging: writing A message to log to console" << endl;
	}

};

class TxtFileLogger : public Logger
{
	void log(string msg)
	{
		cout << "Logging: writing a message to a text file" << endl;
	}
};

class BinFileLogger : public Logger
{
	void log(string msg)
	{
		cout << "Logging: writing A message to log to a BIN file" << endl;
	}
};
#pragma endregion

#pragma region factor
//Logger class
class LoggerFactoryM
{
public:
	Logger *getLogger();
};

Logger *LoggerFactoryM::getLogger()
{
	unsigned loggerType; // variable to store the input
	cout << "\n SELECT LOGGER [1: TXT FILE, 2: BIN FILE, 3: CONSOLE] : ";
	cin >> loggerType;

	switch (loggerType - 1)
	{
	case L_TXT_FILE:
		return new TxtFileLogger();
		break;
	case L_BIN_FILE:
		return new BinFileLogger();
		break;
	case L_CONSOLE:
		return new ConsoleLogger();
		break;
	default:
		cout << "NO LOGGER" << endl;
		return NULL;
		break;
	} // swittch
}

#pragma endregion

// Main function for the program
int main(void)
{

	int userExited = 0; // user has not chosen to exit
	unsigned formatType; // variable to store the input
	// loop while user has not chosen option to exit system
	while (!userExited)
	{
		LoggerFactoryM *factory = new LoggerFactoryM();
		Logger *logger = factory->getLogger();

		cout << "\n SELECT FORMAT [1: NO FORMAT, 2: HTML, 3: ENCRYPT] : ";
		cin >> formatType;

		cout << " Formatting: ";

		switch (formatType - 1)
		{
		case NO_FORMAT:
			logger = new LoggerDecorator(logger);
			break;
		case HTML_FORMAT:
			logger = new HTMLLogger(logger);
		break;
		case ENC_FORMAT:
			logger = new EncyptLogger(logger);
		break;
		default:
			cout << "NO LOGGER" << endl;
			break;
		}

		string msg = "A message to log";
		logger->log(msg);

		cout << "\n EXIT Yes = 1, No = 0 :";
		cin >> userExited;
	}

	return 0;
}
