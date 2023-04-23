#include "Infix_solver.h"

using namespace std;

int main() {
	// Variables
	string token;

	// Input file
	ifstream fin("inputfile.txt");
	// Tests to find and open the input file
	if (!fin) {
		cout << "[Error} Nonexistent input file" << endl;
		return -1;
	}

	// Creates the output file
	ofstream fout("outputfile.txt");

	// Creates the infixparser object
	Infix_solver infixparser;

	// reads the input file into token
	while (getline(fin, token)) {
		// sets token
		infixparser.set(token);
		// solves the function
		infixparser.solve(fout);
	}

	fin.close();
	fout.close();
	return 0;
}