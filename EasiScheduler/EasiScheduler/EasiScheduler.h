
#ifndef __EasiScheduler__EasiScheduler__
#define __EasiScheduler__EasiScheduler__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class EasiScheduler{

private:
	//_filename stores the name of the textfile which stores the lines
    string _filename;
	//_no_of_lines keeps track of the lines in the textfile
    int _no_of_lines;
	//_lines is a vector stores the lines in the buffer for processing
    vector<string> _lines;
    
    static const string PROMPT_WELCOME;
    static const string PROMPT_EMPTY;
    static const string PROMPT_ADDED;
    static const string PROMPT_DELETED;
    static const string PROMPT_CLEARED;
    static const string PROMPT_INVALID_COMMAND;
    static const string PROMPT_PROGRAM_EXIT;
    
public:
	enum CommandType{
        ADD, DELETE_LINE, CLEAR_ALL, DISPLAY_ALL,EXIT, INVALID
    };
    
	
	//Constructor construct a EasiScheduler class object 
	//Pre-condition:
	//		User must type in text file name after program name
	//		Format: EasiScheduler.exe <textfilename>.txt
	//Post-condition:
	//		A new EasiScheduler object will be constructed
	//		readFilename(char *),		
	//		setFilename(string)			
	//		setInitialNoOfLines(),		
	//		and printWelcomeMessage()	
	//		will be called.
    EasiScheduler(char* argv[]);
	//read in filename from user input
    string readFilename(char* argv[]);
	//set filename for write-in files
    void setFilename(string Filename);
	//set initial _no_of_lines to be 0
	void setInitialNoOfLines();
	//print Welcome Message
    void printWelcomeMessage();
	
	
	//This function will read in command keyword from user input
	//Pre-condition:
	//Post-condition: 
	//		command keyword will be returned in string format
	string readCommand();
	
	
	//This function determines commandtype using enum CommandType
	//Pre-condition:
	//		string format command must be read
	//Post-condition: 
	//		command will be be returned in the type of enum CommandType
	CommandType const determineCommandType(string command);
    
	
	//This function executes command by calling corresponding operations
	//Pre-condition: 
	//		Command must be in enum CommandType format
	//Post-condition:
	//		performAddLine(),
	//		performDeleteLine(),
	//		performClearAll(),
	//		performDisplayAll(),
	//		performDisplayAll(),
	//		performProgramExit(),
	//		and printMessageifCommandInvalid() 
	//	could be called.
	void executeCommand(EasiScheduler::CommandType _commandType);
    
	//A new line will be added to the buffer vector
	void performAddLine();
	//Read in a new line from user input
	string readNewLine();
	//Store the line in vector _lines
	void pushBackLine(string line);
	//_no_of_lines in the vector will increment by one each time
    void incrementNoOfLines();
	//Message will be printed after each line addition.
	void printMessageAfterAdded(string line);
	
    //Delete certain line from buffer
	void performDeleteLine();
	//Get line index from user
	int readIndex();
	//Check if line index is valid (exists in the list)
	//Pre-condition: User input an index
	//Post-condition: If index exists in the list, perform deletion
	//				if not, exits program
	void checkValidIndex(int index);
	//Decrement _no_of_lines by one
    void decrementNoOfLines(int index);
	//Throw message after deletion of certain line
    void printMessageAfterDeleted(int lineIndex);
	//Set an iterator pointing to the line for deletion
	vector<string>::iterator getIteratorOfLineDeleted(int index);
	//Delete the line specified
	void deleteLine(vector<string>::iterator iter);
    
	
    //Perform clear operation
	void performClearAll();
	//Clear All the lines in the buffer
	void clearAllLines();
	//Pop the line at the back of the vector
    void popBackLine();
	//Print Message after all lines have been cleared
    void printMessageAfterClear();
	
	//Perform displayAll operation
	void performDisplayAll();
	//Print Message if there is no line to display
	void printMessageIfNoLine();
	//Display all the lines in the buffer
	void displayAllLines();
	//Print one line at a time
	void printOneLine(int lineIndex);
    
	//Perform Exit Program Operation
	void performProgramExit();

   
	//Print message if the command is invalid
	void printMessageifCommandInvalid();

	
	//This block of method saves changes to file after each operation
	//Pre-condition: 
	//		Operations are executed
	//Post-condition:
	///		File will be overwrited by processed information
	void saveToFile();
	//Open the textfile
    void openOutputFile(ofstream & outFile);
	//Remove the existing lines in the file
	void removeCacheInFile();
	//Write the lines in the buffer into the text file
	void writeLinesInFile(ofstream & outFile);
	//Write a specific line into the file
	void writeOneLineInFile(ofstream & outFile, int lineIndex);
	//Close output file
	void closeOutputFile(ofstream & outFile);

};	  
#endif /* defined(__EasiScheduler__EasiScheduler__) */
