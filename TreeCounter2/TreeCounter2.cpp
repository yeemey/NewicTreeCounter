#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>
#include <ctype.h>

//using namespace std;

std::vector<std::string> Split(std::string Target, char delim);
std::string Strip(std::string Target, char delim);
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

	if(GetFile("Please enter in the path to the main tree file: ", rootTree)){
		if(GetFile("Please enter in the path to the bootstrap tree file: ", bootTrees)){

		}
	}
	//string testInput;
	//cout << "Please enter in a string with commas" << endl;
	//cin >> testInput;
	//getline(cin, testInput);

//	vector<string> Tokens = Split(testInput, ',');
//
//	for (int j = 0; j < Tokens.size(); j++) {
//		ostringstream convert;
//		convert << j;
//		string output = Tokens.at(j);
//		cout << "This is the output at " + convert.str() + " " << output << endl;
//	}

	return 0;
}

//Split function is a simple splitter based on the delimiter given.
std::vector<std::string> Split(std::string Target, char delim) {
//String stream will not work in this case because the stream stops at every white space before moving on to the next word.  We're looking to split on a
	//user-defined delimiter.  We do not want to restrict the format of the function.
	std::vector<std::string> Tokens;

	//Target = Strip(Target, ' ');
	Target = Strip(Target, ':');
	int position_LastDelim = -1;
	std::ostringstream convert;
	std::ostringstream inputstring;
	inputstring << Target;
	//int streamlength = inputstring.str().length();
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

