#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>
#include <ctype.h>
#include "stack.h"

//using namespace std;

std::vector<std::string> Split(std::string Target, char delim);
std::string Strip(std::string Target, char delim);
std::string Strip(std::string Target, char delim[]);
std::vector<std::string> FindPatterns(std::string Tree);
bool GetFile(std::string Prompt, std::ifstream& InputFile);

/*
 * Idea: There are at a hundred bootstrapped trees to count.  The basic binary relationships should be extracted first
 * before proceeding to count.  This allows the search function to compare the string of interest
 * against the arrays rather than strings, which will make counting much easier.
 */
int main() {
	using namespace std;
	ifstream rootTree;
	ifstream bootTrees;
	ofstream patternCounts;
	string testInput;

	cout << "Please enter in a string with parentheses: " << endl;
	getline(cin, testInput);

	std::vector<std::string> Patterns = FindPatterns(testInput);
	std::cout << "The size of the Patterns is: " << Patterns.size() << endl;
	std::cout << "The testInput is: " << testInput << endl;
	for(int j = 0; j < Patterns.size(); ++j){
		std::cout << "The pattern selected is: " << Patterns[j].c_str() << endl;
	}

	return 0;
}


/*
 * This function takes the string and does the following:
 * 1. Determines the length of the string.
 * 2. Creates a stack object based on the length of the string.  The length of the string is just to determine
 * the max height the stack can reach.  The stack uses a vector and not an array so this is not an important
 * factor to consider when changes are made and can be changed in future updates.
 * 3. Using an iterator, the function goes through each character in the string looking for an opening parenthesis '(' or closing parenthesis ')'.
 * 4. If it detects an opening parenthesis, it pushes the index of the opening parenthesis on top of the Stack.  If it detects a closing parenthesis,
 * it retrieves the last index of the opening parenthesis, and then retrieves a substring based on the opening parenthesis index and the current index where the
 * closing parenthesis was found.  It will then pop the last index used.
 */
std::vector<std::string> FindPatterns(std::string Tree){
	std::vector<std::string> Patterns;
	int TreeLength = Tree.length();
	Stack parensStack(TreeLength);

	for(int i = 0; i < TreeLength; i++){
		if(Tree[i] == '('){
			parensStack.push(i);
		}else if(Tree[i] == ')'){
			int StartParen;
			parensStack.pop(StartParen);
			Patterns.push_back(Tree.substr(StartParen, i - StartParen + 1));
		}
	}
	return Patterns;
}

//Split function is a simple splitter based on the delimiter given.
std::vector<std::string> Split(std::string Target, char delim) {
//String stream will not work in this case because the stream stops at every white space before moving on to the next word.  We're looking to split on a
	//user-defined delimiter.  We do not want to restrict the format of the function.
	std::vector<std::string> Tokens;
	Target = Strip(Target, ':');
	int position_LastDelim = -1;
	std::ostringstream convert;
	std::ostringstream inputstring;
	inputstring << Target;
	convert << Target.length();
	std::cout << "Length of string is: " + convert.str() << std::endl;
	std::cout << "This is the string: " + inputstring.str() << std::endl;
	for (int i = 0; i < inputstring.str().length(); i++) {
		//Handle the first case.
		std::string checkstring;
		std::stringstream checkstream;
		checkstream << inputstring.str()[i];
		checkstream >> checkstring;
		std::cout << "Checking character " + checkstring << std::endl;
		if (i == 0 && Target[i] == delim) {
			position_LastDelim = 0;
		} else if (Target[i] == delim) {
			Tokens.push_back(Target.substr(position_LastDelim + 1, i - position_LastDelim - 1));
			position_LastDelim = i;
		} else if(i == Target.length() - 1 && Target[i] != delim){
			Tokens.push_back(Target.substr(position_LastDelim + 1, i - position_LastDelim));
		} else if(isspace(Target[i])){
			std::cout << "Space condition triggered..." << std::endl;
			continue;
		}
	}
	return Tokens;
}

//Strip will remove whatever characters are considered delimiters.
std::string Strip(std::string Target, char delim) {
	int initialPosition = 0;
	for (int i = 0; i < Target.length(); ++i) {
		if (Target[i] == delim) {
			std::string predelim = Target.substr(initialPosition, i);
			std::string postdelim = Target.substr(i + 1, Target.length() - i - 1);
			Target = predelim + postdelim;
			return Strip(Target, delim);
		}
	}
	return Target;
}

/*
 * This stripping function will remove whatever characters are contained in the delimiters array.
 */
std::string Strip(std::string Target, char delim[]){
	int initialPosition = 0;
	for(int i = 0; i < Target.length(); ++i){

	}
	return Target;
}

/*
 * Detects whether an array contains a specific character.
 */
bool Contains(char Target, char delim[]){

	return false;
}

//GetFile checks that the file exists, and opens it.  Otherwise it prompts until a file path is entered.
bool GetFile(std::string prompt, std::ifstream& InputFile) {
	std::string FilePath;
	std::cout << prompt << std::endl;
	std::cin >> FilePath;

	InputFile.open(FilePath.c_str());
	if (InputFile) {
		return true;
	} else {
		std::cout << "The file path you entered does not exist.  Please try again."
				<< std::endl;
		return GetFile(prompt, InputFile);
	}
	return false;
}

