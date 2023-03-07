# include "Addition of Two Polynomials.h"

using namespace std;

int main() {

	int num = 0;	// Used for the user to pick the option from the menu
	string polynomial_1;	// The first poylnomial as a string
	string polynomial_2;	// The second polynomial as a string

	Polynomial_Addition<int> poly_1;	// First polynomial as a list
	Polynomial_Addition<int> poly_2;	// Second polynomial as a list
	Polynomial_Addition<int> result;	// Result of the polynomial addition
	
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
		if (num == 1) {
			cout << "Enter first polynomial: ";
			cin >> polynomial_1;
			
		}
		// Enter second polynomial
		else if (num == 2) {
			cout << "Enter second polynomial: ";
			cin >> polynomial_2;

		}
		// Add the two polynomials
		else if (num == 3) {
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