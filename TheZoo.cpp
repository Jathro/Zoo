#include <iostream>
#include <jni.h>
#include <vector>
#include <iomanip>
#include <string>
#include "Animal.h"
#include <fstream>
using namespace std;

// Pad spaces to the end of a string
void PadSpaces(string& toPad, int length) {
	length = length - toPad.size() + 1;
	for (int i = 0;i < length; i++) {
		toPad.push_back(' ');
	}
}

// Remove extra spaces from end of string
void rtrim(string& input) {
	for (unsigned int i = input.size() - 1; i > 0; i--) {
		if (input.at(i) == ' ') {
			input.erase (i);
		}
	}
}

// Check input matching for Track# or Name
// IF the userInput is a number, the pad with '0' and compare to storedValue
// else remove spaces from storedValue and compare to userInput
bool CheckInputMatch(string storedValue, string userInput) {
	if (isdigit(userInput[0]) > 0) {
		userInput = string(6 - userInput.size(), '0').append(userInput);
	}
	else {
		rtrim(storedValue);
	}

	if (storedValue == userInput) {return true;} else {return false;}
}

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     //cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            //cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }

     jvm->DestroyJavaVM();
     cin.get();
}

// Adds an animal to the animal list vector from user input
void AddAnimal(vector<string>& addAnimal)
{
	int newTrackNum, numEggs;
	string trackInput, newName, newType, newSubType, animalToAdd;
	bool isNursing;
	char toSave;

	cout << "Track#:" << endl;
	cin >> trackInput;
	while (isdigit(trackInput[0]) == 0) {  //Validate a number is entered
		cout << "Please enter a number." << endl;
		cin >> trackInput;
	}
	newTrackNum = stoi (trackInput);

	cout << "Name:" << endl;
	cin.ignore();
	getline(cin, newName); // Get next line for name
	Animal newAnimal(newTrackNum, newName);
	PadSpaces(newName, 15);

	cout << "Type:" << endl;
	cin >> newType;
	while (!newAnimal.CheckClass(newType)) {  // Validate correct type is selected
		cout << "Please select Mammal or Oviparous" << endl;
		cin >> newType;
	}
	PadSpaces(newType,15);
	cout << "Sub-Type:" << endl;
	cin >> newSubType;
	PadSpaces(newSubType,15);

	cout << "Eggs:" << endl;
	cin >> numEggs;
	cout << "Nurse:" << endl;
	cin >> isNursing;

	animalToAdd = string(6 - to_string(newTrackNum).length(), '0').append(to_string(newTrackNum))
		+ " " + newName
		+ " " + newType
		+ " " + newSubType
		+ " " + to_string(numEggs)
		+ " " + to_string(isNursing);

	cout << "Do you want to save? \"y\" " << endl;
	cin >> toSave;

	if (toSave == 'y' || toSave == 'Y') {
		addAnimal.push_back(animalToAdd);
	}
}

// Removes an animal based on track# or name
void RemoveAnimal(vector<string>& removeAnimal)
{
	string input, track, name;
	cout << "Track# or Name of animal to delete" << endl;
	cin >> input;

	for (unsigned int i = 0; i < removeAnimal.size(); i++) {
		track = removeAnimal.at(i).substr(0, 6);
		name = removeAnimal.at(i).substr(7, 16);
		if (CheckInputMatch(name, input) || CheckInputMatch(track, input)) {
			removeAnimal.erase(removeAnimal.begin() + i);
			cout << "Animal Removed: " << input << endl << endl;
			return;
		}
	}
	cout << "No matching animals: " << input << endl << endl;
}

// Loads data from file
void LoadDataFromFile(vector<string>& addAnimal)
{
	ifstream animalFile;
	string fileString;
	animalFile.open("zoodata.txt");

	if (!animalFile.is_open()) {
		cout << "Could not open file zoodata.txt." << endl;
	}

	cout << "Loading Data" << endl << endl;

	while (!animalFile.eof()) {
		getline(animalFile, fileString);

		if (!animalFile.fail()) {
			addAnimal.push_back(fileString);
		}
	}
	animalFile.close();
}

// Saves data to file
void SaveDataToFile(vector<string>& saveAnimal)
{
	ofstream animalFile;

	animalFile.open("zoodata.txt");

	if (!animalFile.is_open()) {
		cout << "Could not open file zoodata.txt." << endl;
	}
	cout << "Saving Data" << endl << endl;

	for (unsigned int i = 0; i < saveAnimal.size(); i++) {
		animalFile << saveAnimal.at(i) << endl;
	}

	animalFile.close();
}

// Displays menu for user to select from
void DisplayMenu()
{
     cout << "******Menu ('0' to exit)******" << endl
    	  << "1) Load Animal Data" << endl
		  << "2) Generate Data" << endl
		  << "3) Display Animal Data" << endl
		  << "4) Add Record" << endl
		  << "5) Delete Record" << endl
		  << "6) Save Animal Data" << endl
		  << "Make selection:" << endl;
}

// prints out a list of animals
void DisplayAnimals(vector<string>& animals) {
	for (unsigned int i = 0; i < animals.size(); i++) {
		cout << animals.at(i) << endl;
	}
}

int main()
{
	vector<string> Animals;
	char userInput;

	DisplayMenu();
	cin >> userInput;

	while (userInput != '0') {
		switch(userInput) {
		case '1':
			LoadDataFromFile(Animals);
			break;
		case '2':
			GenerateData();
			break;
		case '3':
			DisplayAnimals(Animals);
			break;
		case '4':
			AddAnimal(Animals);
			break;
		case '5':
			RemoveAnimal(Animals);
			break;
		case '6':
			SaveDataToFile(Animals);
			break;
		default:
			cout << "Not a valid selection, please try again." << endl;
			break;
		}
		DisplayMenu();
		cin >> userInput;
	}

	return 1;
}
