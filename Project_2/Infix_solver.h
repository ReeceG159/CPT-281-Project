#ifndef INFIX_SOVER_H
#define INFIX_SOLVER_H

#include <iostream>
#include <fstream>
#include <string>
#include<stack>

using namespace std;

class Infix_solver {
public:
	// Constructor
	Infix_solver(); // Default

	// Class-member functions
	void set(string); // Sets the string
	int solve(std::ofstream& out); // Solves the string

private:
	// Data fields
	string token;

	// Class-member functions
	int precedence(const string& oper); // Determines the precedence of the functions
	int perform_calc(int operandl, int operandr, string operators); // Performs the calculations of the functions
};
#endif;