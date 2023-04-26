#include "Infix_solver.h"

using namespace std;

// Constructors
// Default
Infix_solver::Infix_solver() {
	token = "";
}

// Class-member functions
// Sets the string
void Infix_solver::set(string expression) {
	token = expression;
}

// Determines the precedence of the functions
int Infix_solver::precedence(const string& oper) {
	if (oper == "||") { return 7; } // Or functions determines if it is this or that
	if (oper == "&&") { return 6; } // And functions determines if it is both
	if (oper == "==" || oper == "!=") { return 5; } // == determines if it is equal, != determines if it is not equal
	if (oper == ">" || oper == ">=" || oper == "<" || oper == "<=") { return 4; } // > determines if left is greater, >= determines if left is greater than or equal to, < determines if right is greater, <= determines if right is greater than or equal to
	if (oper == "+" || oper == "-") { return 3; } // + adds both operands, - subtracts right from left
	if (oper == "*" || oper == "/" || oper == "%") { return 2; } // * multiplies both operands, / divides right from left, % operand left mod operand right
	if (oper == "^") { return 1; } // ^ is operand left power of operand right
	throw exception("Unsupported operator");
}

// Performs the calculations of the functions
int Infix_solver::perform_calc(int operandl, int operandr, string operators) {
	// Supported operators
	if (operators == "+") { return (operandl + operandr); }
	if (operators == "-") { return (operandl - operandr); }
	if (operators == "*") { return (operandl * operandr); }
	if (operators == "/") {
		if (!operandr) { throw exception("Divide by zero"); }
		return (operandl / operandr);
	}
	if (operators == "%") { return operandl % operandr; }
	if (operators == "^") { return (pow(operandl, operandr)); }
	if (operators == "==") { return operandl == operandr; }
	if (operators == "!=") { return operandl != operandr; }
	if (operators == ">") { return operandl > operandr; }
	if (operators == ">=") { return operandl >= operandr; }
	if (operators == "<") { return operandl < operandr; }
	if (operators == "<=") { return operandl <= operandr; }
	if (operators == "&&") { return operandl && operandr; }
	if (operators == "||") { return operandl || operandr; }
}

// Solves the string
int Infix_solver::solve(std::ofstream& out) {
	stack<string> stk;
	stack<int> operands;
	string temp;
	string operatortemp;
	string newtoken;
	int operandl, operandr;
	string operators;

	if (token.empty()) {
		return 0;
	}
	for (int i = 0; i < token.length(); i++) {
		if (token[i] == ' ') {
			continue;
		}
		string s(1, token[i]);
		// Tests if the character is a left parenthesis
		if (token[i] == '(') { stk.push(s); }
		else if (isdigit(token[i])) {
			temp = temp + token[i];
			newtoken = temp;
			// tests to see if the next character in the string is a digit
			if (isdigit(token[i + 1])) {
				continue;
			}
			else {
				operands.push(stoi(newtoken));
				temp = "";
			}
		}
		// Tests if the character is a right parenthesis
		else if (token[i] == ')') {
			// If not a left parenthesis
			while (stk.top() != "(") {
				// Get the right operand
				operandr = operands.top();
				operands.pop();
				// Get the left operands
				operandl = operands.top();
				operands.pop();
				// Get the operator
				operators = stk.top();
				stk.pop();
				// performs the calculations and adds to the stack
				operands.push(perform_calc(operandl, operandr, operators));
			}
			stk.pop();
		}
		else {
			string s(1, token[i]);
			while (!stk.empty() && !s.empty() && stk.top() != "(" && precedence(s) >= precedence(stk.top())) {
				// Get the right operand
				operandr = operands.top();
				operands.pop();
				// Get the left operands
				operandl = operands.top();
				operands.pop();
				// Get the operator
				operators = stk.top();
				stk.pop();
				// performs the calculations and adds to the stack
				operands.push(perform_calc(operandl, operandr, operators));
			}
			operatortemp = operatortemp + token[i];
			// tests if the next character is not a digit, not a space, not a left parenthesis, and not a right parenthesis. Only does if all requirements met.
			if (!isdigit(token[i + 1]) && token[i + 1] != ' ' && token[i + 1] != '(' && token[i + 1] != ')') {
				continue;
			}
			else {
				stk.push(operatortemp);
				// resets operatortemp to empty it
				operatortemp = "";
			}
		}
	}
	// tests if the stack is not empty
	while (!stk.empty()) {
		// Get the right operand
		operandr = operands.top();
		operands.pop();
		// Get the left operands
		operandl = operands.top();
		operands.pop();
		// Get the operator
		operators = stk.top();
		stk.pop();
		// performs the calculations and adds to the stack
		operands.push(perform_calc(operandl, operandr, operators));
	}
	// top of the stk result, returns it
	int result = operands.top();
	// Outputs to the file the equation string = the result
	out << token << " = " << result << endl;
	return result;
}