#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "DynIntStack.h"

using namespace std;

int spaceCounter(string line) //counts the number of leading spaces
{
	unsigned int count = 0;
	bool check = true;
	while(line[count] == ' ' && check){
		count++;
		if (line[count] != ' ')
			check = false;
	}   return count;
}

void stackDeleter(DynIntStack & SITECH) { //deletes all the elements of stack
	
	int deleter;
	while (!SITECH.isEmpty()) 
		SITECH.pop(deleter);
}
int main() {

	ifstream stream;
	string fileName;

	cout << "Please enter the file name that is going to be analyzed." << endl;
	cin >> fileName;

	while(stream.fail()) { //if stream fails ask for a proper name
		
		cout << "Unable to open file please enter a different file name." << endl;
		cin >> fileName;     
	}   stream.open(fileName.c_str()); 
     
	cout << "Starting file analysis..." << endl;
	cout << "Initial indentation level is pushed to the stack as 0." << endl << endl;

	DynIntStack SITECH;
	SITECH.push(0);

	string line;
	static unsigned int lineNum = 0;
	unsigned int currentLevel = 0;

	bool check = true; //this boolean decides if former line has a keyword
	while(getline(stream,line)) {
		
		lineNum++;
		cout << "Line Number: " << lineNum << endl;
		cout << "Line: " << line << endl;

		unsigned int spaceNum = spaceCounter(line);

		cout << spaceNum << " number of spaces observed before the start of the line." << endl;
		
		if(!check)
			cout << "This line proceeds a keyword containing line." << endl;
		
		cout << "Current Level = " << currentLevel << " This Line = " << spaceNum << endl;

		if(spaceNum > currentLevel && !check) { //if there is keyword , current > indentation

			SITECH.push(spaceNum);
			cout << "Line correct. Depth " << spaceNum << " added to the stack." << endl; 
			currentLevel = spaceNum;
		}
		else if (spaceNum <= currentLevel && !check ) { //if there is keyword, current <= indentation
			
			cout << "Incorrect file structure. " << endl;
			cout << "Current line must be greater than the Current indentation level. " << endl;
			cout << "Stopping file analysis..." << endl;

			stackDeleter(SITECH);

			cout << endl << "Stack emptied and program ending." << endl; 
		    return 0;
		}
		else if(spaceNum < currentLevel && check) { //if there is no keyword, current < indentation

			cout << "Current line is smaller than Current indentation level; checking if line belongs to outer indentation." << endl;
			int dude;
			SITECH.pop(dude);
			currentLevel = dude;
			
			while (currentLevel != spaceNum && currentLevel != 0) { //it will pop until current = indentation or current = 0
				SITECH.pop(dude);
				currentLevel = dude;
				
				cout << "Current Level = " << currentLevel << " This Line = " << spaceNum << endl;
				if (dude != spaceNum)
					cout << "Current line is smaller than Current indentation level; checking if line belongs to outer indentation." << endl;		
			}
			if(currentLevel == spaceNum) {

				cout << "Line belongs to outer block. " << endl;
				SITECH.push(currentLevel);
			}
			else if(currentLevel == spaceNum || currentLevel < spaceNum) {

				cout << "Incorrect file structure." << endl;
				cout << "Current line cannot be greater than the Current indentiation level." << endl;
				cout << "Stopping file analysis..." << endl;
			
				stackDeleter(SITECH);
		   
				cout << endl << "Stack emptied and program ending." << endl; 
				return 0;
			}	
		}
		else if(spaceNum > currentLevel && check) { //there is no keyword and current > indentation

			cout << "Incorrect file structure." << endl;
			cout << "Current line cannot be greater than the Current indentiation level." << endl;
			cout << "Stopping file analysis..." << endl;
			
			stackDeleter(SITECH);
		   
		    cout << endl << "Stack emptied and program ending." << endl; 
		    return 0;
		}
		else if (spaceNum == currentLevel && check) //if there is no keyword and current = indentation
			cout << "Line belongs to current block." << endl;

		string keyWord;
		istringstream keyFinder(line);
		keyFinder >> keyWord;
		
		if(keyWord == "while" || keyWord == "if" || keyWord == "else" || keyWord == "elif" || keyWord == "for") { //keyword check
			cout << "Keyword " << keyWord << " found on this line." << endl;
			check = false;
		}
		else
			check = true;
		cout << endl << endl;
	}

	stackDeleter(SITECH); //deletes the stack and finishes program
	cout << "Finished file analysis. File structure is correct!" << endl << "Stack emptied and program ending." ;
	return 0;
}