#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>
#include <ctype.h>
#include "stack.h"
#include <stdlib.h>
#include <map>
#include <algorithm>
//#include <unistd.h>

//using namespace std;

std::vector<std::string> Split(std::string Target, char delim);
std::string Strip(std::string Target, char delim);
std::string Strip(std::string Target, std::vector<char> delim);
std::vector<std::string> FindPatterns(std::string Tree);
std::vector<std::vector<std::string> > BootStrapPatterns(
		std::ifstream& InputFile);
std::map<std::string, int> Count(std::vector<std::string> PrimaryTree,
		std::vector<std::vector<std::string> > BootTrees);

bool SearchPattern(std::string Pattern, std::vector<std::string> Target,
		int min, int max);
bool Contains(char Target, std::vector<char> delim);
bool GetFile(std::string Prompt, std::ifstream& InputFile);
bool FileExists(std::string Prompt, std::string& Path,
		std::ifstream& InputFile);

/*
 * Idea: There are at a hundred bootstrapped trees to count.  The basic binary relationships should be extracted first
 * before proceeding to count.  This allows the search function to compare the string of interest
 * against the arrays rather than strings, which will make counting much easier.
 */
int main() {
	using namespace std;
//	ifstream rootTree;
//	ifstream bootTrees;
//	ofstream patternCounts;
//	string testInput;
//
//	cout << "Please enter in a string with parentheses: " << endl;
//	getline(cin, testInput);

	char delimArr[] = {';','.',' ',':','0','1','2','3','4','5','6','7','8','9'};
	std::vector<char> delimiters(delimArr, delimArr + sizeof(delimArr) / sizeof(char));
//	testInput = Strip(testInput, delimiters);
//	std::cout << "This is what's in the testInput: " << testInput << std::endl;
//	std::vector<std::string> Patterns = FindPatterns(testInput);
//	std::cout << "The size of the Patterns is: " << Patterns.size() << endl;
//	std::cout << "The testInput is: " << testInput << endl;
//	for(int j = 0; j < Patterns.size(); ++j){
//		std::cout << "The pattern selected is: " << Patterns[j].c_str() << endl;
//	}

	string ExamplePrimaryPattern = "(TYLCV_GP: 0.014972, ((((TYLCV_US_Flo: 0.000004, TYLCV_PR: 0.005754): 0.005764, TYLCV_MX_Yuc: 0.002855): 0.000004, (TYLCV_CU: 0.000004, (TYLCV_Flo: 0.000004, TYLCV_US_TX: 0.000004): 0.000004): 0.000004): 0.000004, TYLCV_DO: 0.000004): 0.000004, (((((TYLCV_MX_Sin: 0.000004, TYLCV_MX_Cul: 0.002828): 0.000004, TYLCV_MX_Sin2: 0.000004): 0.000004, TYLCV_US_CA: 0.002833): 0.002985, (TYLCV_CN_SH2: 0.002861, TYLCV_JA_Tosa: 0.000004): 0.005699): 0.005774, TYLCV_IL: 0.005821): 0.002864);";
	ExamplePrimaryPattern = Strip(ExamplePrimaryPattern, delimiters);

	string ExampleBootPatternOne = "(TYLCV_GP: 0.019721, ((TYLCV_US_Flo: 0.000004, TYLCV_PR: 0.002782): 0.008365, (TYLCV_MX_Yuc: 0.002782, ((TYLCV_CU: 0.000004, TYLCV_DO: 0.000004): 0.000004, (TYLCV_Flo: 0.000004, TYLCV_US_TX: 0.000004): 0.000004): 0.000004): 0.000004): 0.000004, ((((TYLCV_MX_Sin: 0.000004, (TYLCV_MX_Cul: 0.005556, TYLCV_MX_Sin2: 0.000004): 0.000004): 0.000004, TYLCV_US_CA: 0.002776): 0.005613, (TYLCV_CN_SH2: 0.002780, TYLCV_JA_Tosa: 0.000004): 0.005544): 0.008389, TYLCV_IL: 0.002789): 0.002786);";
	ExampleBootPatternOne = Strip(ExampleBootPatternOne, delimiters);

	string ExampleBootPatternTwo = "(TYLCV_GP: 0.013980, ((((TYLCV_US_Flo: 0.000004, TYLCV_PR: 0.000004): 0.002776, ((TYLCV_MX_Yuc: 0.000004, TYLCV_Flo: 0.000004): 0.000004, TYLCV_US_TX: 0.000004): 0.000004): 0.000004, TYLCV_CU: 0.000004): 0.000004, TYLCV_DO: 0.000004): 0.000004, (((((TYLCV_MX_Sin: 0.000004, TYLCV_MX_Cul: 0.005558): 0.000004, TYLCV_MX_Sin2: 0.000004): 0.000004, TYLCV_US_CA: 0.000004): 0.005596, (TYLCV_CN_SH2: 0.002779, TYLCV_JA_Tosa: 0.000004): 0.002767): 0.005578, TYLCV_IL: 0.000004): 0.002778);";
	ExampleBootPatternTwo = Strip(ExampleBootPatternTwo, delimiters);

	string ExampleBootPatternThree = "(TYLCV_GP: 0.011255, (((((TYLCV_US_Flo: 0.000004, TYLCV_PR: 0.005599): 0.008404, TYLCV_IL: 0.008364): 0.000004, ((TYLCV_MX_Yuc: 0.000004, TYLCV_CU: 0.000004): 0.000004, TYLCV_DO: 0.000004): 0.000004): 0.000004, TYLCV_US_TX: 0.000004): 0.000004, TYLCV_Flo: 0.000004): 0.000004, ((TYLCV_MX_Sin: 0.000004, (TYLCV_MX_Cul: 0.002785, (TYLCV_MX_Sin2: 0.000004, TYLCV_US_CA: 0.000004): 0.000004): 0.000004): 0.002790, (TYLCV_CN_SH2: 0.000004, TYLCV_JA_Tosa: 0.000004): 0.000004): 0.005582);";
	ExampleBootPatternThree = Strip(ExampleBootPatternThree, delimiters);

//	vector<string> PrimaryPattern = FindPatterns("((C,D),(A,B))");
	vector<string> PrimaryPattern = FindPatterns(ExamplePrimaryPattern);

//	for (int i = 0; i < PrimaryPattern.size(); ++i) {
//		cout << "Primary pattern value: " << PrimaryPattern[i] << endl;
//	}

	vector<vector<string> > BootPattern;
	BootPattern.push_back(FindPatterns(ExampleBootPatternOne));
	BootPattern.push_back(FindPatterns(ExampleBootPatternTwo));
	BootPattern.push_back(FindPatterns(ExampleBootPatternThree));
//	BootPattern.push_back(FindPatterns("(B,(A,B))"));
//	BootPattern.push_back(FindPatterns("((B,D),(A,B))"));
//	BootPattern.push_back(FindPatterns("((C,D),(E,F))"));
//	BootPattern.push_back(FindPatterns("(C,(D,(E,(A,B))))"));
//	BootPattern.push_back(FindPatterns("((C,D),(E,(A,B)))"));
//	BootPattern.push_back(FindPatterns("((R,S),(T,((C,D),(A,B))))"));

	map<string, int> Counts = Count(PrimaryPattern, BootPattern);
	for (map<string, int>::iterator p = Counts.begin(); p != Counts.end();
			++p) {
		cout << "Key: " << p->first << endl;
		cout << "Value: " << p->second << endl;
	}

//	ifstream PrimaryTreeFile;
//	string PrimaryTreePath;
//	string PrimaryTreePrompt =
//			"Please enter in the path of the primary tree file: ";
//
//	ifstream BootTreeFile;
//	string BootTreePath;
//	string BootTreePrompt = "Please enter in the path of the boot tree file: ";
//
//	if (FileExists(PrimaryTreePrompt, PrimaryTreePath, PrimaryTreeFile)
//			&& FileExists(BootTreePrompt, BootTreePath, BootTreeFile)) {
//
//	}

	return 0;
}

/*
 * The count function goes through each pattern in the list, and makes an entry for the pattern in the mapping object.  It then proceeds
 * to search for matching patterns in the multiple tree files.
 */
std::map<std::string, int> Count(std::vector<std::string> PrimaryTree,
		std::vector<std::vector<std::string> > BootTrees) {
	std::map<std::string, int> PatternCounts;
	std::cout << "We entered pattern counting." << std::endl;
	std::cout << "The number of patterns we have are: " << PrimaryTree.size() << std::endl;
	for (int i = 0; i < PrimaryTree.size(); ++i) {
		std::cout << "Primary pattern: " << PrimaryTree[i] << std::endl;
		PatternCounts[PrimaryTree[i]] = 0;
		for (int j = 0; j < BootTrees.size(); ++j) {
			if (SearchPattern(PrimaryTree[i], BootTrees[j], 0,
					BootTrees[j].size() - 1)) {
				PatternCounts[PrimaryTree[i]]++;
			}
		}
	}
	return PatternCounts;
}

/*
 * This search pattern uses a binary search algorithm to discover the location of the string.  The worst-case scenario complexity of this method is
 * O(log n).  It only works in cases where the list is already sorted.
 */
bool SearchPattern(std::string Pattern, std::vector<std::string> Target,
		int min, int max) {

	if (max < min) {
//		std::cout << "Returning false" << std::endl;
		return false;
	} else {
		int middle =  min + ((max - min) / 2);
		sort(Target.begin(), Target.end());

		if (Pattern < Target[middle]) {
//			std::cout << "Pattern was less than middle target. Pattern: " << Pattern << " Target: " << Target[middle] << " Middle: " << middle << " Max: " << max << " Min: " << min << std::endl;
			return SearchPattern(Pattern, Target, min, middle - 1);
		} else if (Pattern > Target[middle]) {
//			std::cout << "Pattern was greater than middle target. Pattern: " << Pattern << " Target: " << Target[middle] << " Middle: " << middle << " Max: " << max << " Min: " << min << std::endl;
			return SearchPattern(Pattern, Target, middle + 1, max);
		} else if (Pattern == Target[middle]) {
			return true;
		}
	}
	return false;
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
std::vector<std::string> FindPatterns(std::string Tree) {
	std::vector<std::string> Patterns;
	int TreeLength = Tree.length();
	Stack parensStack(TreeLength);

	for (int i = 0; i < TreeLength; i++) {
		if (Tree[i] == '(') {
			//std::cout << "Pushing index of ( onto stack @ " << i << std::endl;
			parensStack.push(i);
		} else if (Tree[i] == ')') {
			int StartParen = 0;
			parensStack.pop(StartParen);
//			std::cout << "Popping index of ( from stack @ " << StartParen
//					<< ". Up until: " << i << std::endl;
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
//	std::cout << "Length of string is: " + convert.str() << std::endl;
//	std::cout << "This is the string: " + inputstring.str() << std::endl;
	for (int i = 0; i < inputstring.str().length(); i++) {
		//Handle the first case.
		std::string checkstring;
		std::stringstream checkstream;
		checkstream << inputstring.str()[i];
		checkstream >> checkstring;
//		std::cout << "Checking character " + checkstring << std::endl;
		if (i == 0 && Target[i] == delim) {
			position_LastDelim = 0;
		} else if (Target[i] == delim) {
			Tokens.push_back(
					Target.substr(position_LastDelim + 1,
							i - position_LastDelim - 1));
			position_LastDelim = i;
		} else if (i == Target.length() - 1 && Target[i] != delim) {
			Tokens.push_back(
					Target.substr(position_LastDelim + 1,
							i - position_LastDelim));
		} else if (isspace(Target[i])) {
//			std::cout << "Space condition triggered..." << std::endl;
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
			std::string postdelim = Target.substr(i + 1,
					Target.length() - i - 1);
			Target = predelim + postdelim;
			return Strip(Target, delim);
		}
	}
	return Target;
}

/*
 * This stripping function will remove whatever characters are contained in the delimiters array.
 */
std::string Strip(std::string Target, std::vector<char> delim) {
	int initialPosition = 0;
	for (int i = 0; i < Target.length(); ++i) {
//		std::cout << "Makes it to the inside of strip on " << i << std::endl;
		bool contains = Contains(Target[i], delim);
//		std::cout << "Value of 'contains' on " << i << ":" << contains
//				<< std::endl;
		if (contains) {
			std::string predelim = Target.substr(initialPosition, i);
			std::string postdelim = Target.substr(i + 1,
					Target.length() - i - 1);
			Target = predelim + postdelim;
//			std::cout << "This is in the target string: " << Target
//					<< std::endl;
			return Strip(Target, delim);
		}
	}
//	std::cout
//			<< "We're about to return to the main thread.  This is what's in the target: "
//			<< Target << std::endl;
	return Target;
}

/*
 * Detects whether a vector contains a specific character.
 */
bool Contains(char Target, std::vector<char> delim) {
	for (int i = 0; i < delim.size(); ++i) {
		if (Target == delim[i]) {
			if (Target != ' ') {
//				std::cout << "This character is going to return as true: "
//						<< Target << std::endl;
			} else {
//				std::cout
//						<< "This character is space and is going to return as true."
//						<< std::endl;
			}
			return true;
		}
	}
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
		std::cout
				<< "The file path you entered does not exist.  Please try again."
				<< std::endl;
		return GetFile(prompt, InputFile);
	}
	return false;
}

std::vector<std::vector<std::string> > BootStrapPatterns(
		std::ifstream& InputFile) {
	std::vector<std::vector<std::string> > BootStrapTreePatterns;
	while (InputFile.good()) {
		std::string BootStrapTree;
		getline(InputFile, BootStrapTree);
		std::vector<std::string> BootStrapTreePattern = FindPatterns(
				BootStrapTree);
		BootStrapTreePatterns.push_back(BootStrapTreePattern);
	}
	return BootStrapTreePatterns;
}

bool FileExists(std::string Prompt, std::string& FilePath,
		std::ifstream& InputFile) {
	std::cout << Prompt << std::endl;
	std::cin >> FilePath;
	InputFile.open(FilePath.c_str());
	if (InputFile) {
		return false;
	} else {
		return true;
	}
}
