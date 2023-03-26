#include "Addition of Two Polynomials.h"
#include <string>
#include <algorithm>

using namespace std;

int main() {

	int num = 0;	// Used for the user to pick the option from the menu
	string polynomialterm;	// The first poylnomial as a string

	Polynomial_Addition<Term*> poly_1;	// First polynomial as a list
	Polynomial_Addition<Term*> poly_2;	// Second polynomial as a list
	Polynomial_Addition<Term*> result;	// Result of the polynomial addition

	// A menu system that allows the user to select their options
	while (num != 5) {
		cout << "Addition of Two Polynomials" << endl;
		cout << "Type '1' to enter first polynomial" << endl;
		cout << "Type '2' to enter second polynomial" << endl;
		cout << "Type '3' to add polynomials" << endl;
		cout << "Type '4' to show result" << endl;
		cout << "Type '5' to exit" << endl;
		cin >> num;
		// Enter first polynomial
		if (num == 1 || num == 2) {
			if (num == 1) {
				cout << "Enter the first polynomial: ";
			}
			else {
				cout << "Enter the second polynomial: ";
			}
			cin >> polynomialterm;

			int poly_coefficient = 1;
			int poly_exponent = 1;
			int constant = 0;
			string polynomialterm_parse;
			bool coeffienent = false;
			bool exponent = false;
			bool variable = false;

			for (int i = 0; i < polynomialterm.size(); i++) {

				if (polynomialterm[i] == '+' || polynomialterm[i] == '-' && i != 0)
				{
					if (variable == false && polynomialterm_parse.size() > 0) {
						// stoi is a string to integer converstion function
						constant = stoi(polynomialterm_parse);
						Term* term = new Term(constant, 0);
						if (num == 1) {
							poly_1.push_back(term);
						}
						else {
							poly_2.push_back(term);
						}
						polynomialterm_parse = "";
					}
				}
				
				if (exponent == true) {
					// read to the next + or - sign
					while (polynomialterm[i] != '+' && polynomialterm[i] != '-' && i < polynomialterm.size()) {
						polynomialterm_parse.append(1, polynomialterm[i]);
						i++;
					}
					// move back to the + or - sign for processing
					poly_exponent = stoi(polynomialterm_parse);
					exponent = false;
					polynomialterm_parse = "";
					// monomial is complete
					variable = false;
					coeffienent = false;
					exponent = false;
					Term* term = new Term(poly_coefficient, poly_exponent);
					if (num == 1) {
						poly_1.push_back(term);
					}
					else {
						poly_2.push_back(term);
					}
				}
			
				if (polynomialterm[i] != 'x' && polynomialterm[i] != '^'){
					polynomialterm_parse.append(1, polynomialterm[i]);
                }

				if (polynomialterm[i] == 'x') {
					// found an x so set its coefficient.  Convert string to int using stoi 
					// Check if there is only a + or - wich means there was no coefficient so it shold be 1.
					if (polynomialterm_parse.size() == 1) {
						if (polynomialterm_parse[0] == '+' || polynomialterm_parse[0] == '-') {
							polynomialterm_parse.append(1, '1');
						}
					}
					poly_coefficient = stoi(polynomialterm_parse);
					coeffienent = true;
					variable = true;
					polynomialterm_parse = "";
					
					// check if there is an exponent
					if (polynomialterm[i + 1] == '^') {
						exponent = true;
						i++; // Move to the ^ character
						// check if the next character is a -
						if (polynomialterm[i + 1] == '-') {
							i++;// Move past the ^
							polynomialterm_parse.append(1, polynomialterm[i]);
						}
					}
					else {
						// no exponent
						variable = false;
						coeffienent = false;
						Term* term = new Term(poly_coefficient, 1);
						if (num == 1) {
							poly_1.push_back(term);
						}
						else {
							poly_2.push_back(term);
						}
					}
				}
				else if (i == polynomialterm.size()-1)
				{
					// check if the last part of the polynomial is a constant
					if (variable == false && coeffienent == false) {
						constant = stoi(polynomialterm_parse);
						Term* term = new Term(constant, 0);
						if (num == 1) {
							poly_1.push_back(term);
						}
						else {
							poly_2.push_back(term);
						}
						polynomialterm_parse = "";
					}
				}
			}
		}
		
		// Add the two polynomials
		else if (num == 3) {
		    // need to add a sort
			result = poly_1 + poly_2;
		}
		// Shows the result
		else if (num == 4) {
			cout << result << endl;
		}
		// Allows the user to exit the loop
		else if (num == 5) {
			break;
		}
		// Any other number asks the user to enter a different number
		else {
			cout << "Invalid number, try agian." << endl;
		}
	}

	system("pause");
	return 0;
}