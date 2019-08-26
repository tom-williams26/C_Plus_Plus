#include <iostream>
#include <fstream>

using namespace std;

const int MAX_CHARS = 10;
const int MAX_STUDENTS = 2;

typedef struct
{
	char name[MAX_CHARS];
	int age;
	bool male;
} student_t;



void readFile(string filename)
{
	student_t studLoaded[MAX_STUDENTS];

	// Reading from the file
	ifstream input_file(filename, ios::binary);
	if (input_file.fail())
	{
		cout << "Could not open file" << endl;
	}
	else
	{
		if (!input_file.read((char*)&studLoaded, sizeof(studLoaded)))
		{
		cout << "Could not read file" << endl;
		}
		else
		{
			streamsize bytesRead = input_file.gcount();
			if (bytesRead != sizeof(studLoaded))
			{
				cout << "Could not read expected number of bytes" << endl;
			}
			else
			{
				//Displaying data
				for (size_t i = 0; i < MAX_STUDENTS; i++)
				{
					cout << "RECORD #" << i << endl;
					cout << "Name: " << studLoaded[i].name << endl;
					cout << "Age: " << studLoaded[i].age << endl;
					cout << "Gender: ";
					if (studLoaded[i].male) cout << "male";
					else cout << "female";
					cout << endl;
				}
			}
		}
	}
	input_file.close();
}

void writingToFile(string filename)
{
	student_t studToSave[MAX_STUDENTS];

	// Seeding data into struct array

	strncpy_s(studToSave[0].name, "John", MAX_CHARS);
	studToSave[0].age = 21;
	studToSave[0].male = true;

	strncpy_s(studToSave[1].name, "Mary", MAX_CHARS);
	studToSave[1].age = 22;
	studToSave[1].male = false;

	// Serialising structo to students.data

	ofstream output_file(filename, ios::binary);
	if (output_file.fail())
	{
		cout << "Could not open file for writing" << endl;
	}
	else
	{
		if (!output_file.write((char*)studToSave, sizeof(studToSave)))
		{
			cout << "Could not write to file" << endl;
		}
		else
		{
			streamsize bytesWritten = output_file.tellp();
			if (bytesWritten != sizeof(studToSave))
			{
				cout << "Could not write expected number of bytes" << endl;
			}
			else
			{
				cout << "file written OK" << endl;
			}
		}
	}
	output_file.close();
}

int main(void)
{


	return 0;
}
