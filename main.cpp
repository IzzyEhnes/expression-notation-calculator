// Izzy Ehnes
// main.cpp
// 5 March 2019

/*
	DESCRIPTION:

	This program converts infix expressions into postfix form and can then compute
	an answer. It requires there to spaces between the operands and operators to work
	correctly to prevent any issues with multiple-digit operands.

	The main() function tests the functions by providing various infix problems,
	which are converted to postfix in the function infixToPostfix and calculated in the
	function evaluateInfix.

*/



#include <iostream>
#include <stack>
#include <cctype>
#include <string>
#include <cmath>



// Main functions
double evaluateInfix(std::string inExpression);
double evaluatePostfix(std::string inExpression);
double evaluatePrefix(std::string inExpression);

std::string infixToPostfix(std::string inExpression);
std::string infixToPrefix(std::string inExpression);

std::string postfixToInfix(std::string inExpression);
std::string prefixToInfix(std::string inExpression);

std::string prefixToPostfix(std::string inExpression);
std::string postfixToPrefix(std::string inExpression);



// Helper functions
int precedenceCheck(char inOperator);
bool isOperator(char inChar);
double calculate(double operand1, double operand2, char symbol);
std::string reverse(std::string &inExpression);






bool isOperator(char inChar)
{
	switch(inChar)
	{
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
			return true;

		default:
			return false;
	}
}






double calculate(double operand1, double operand2, char symbol)
{
	double result = 0;

	switch (symbol)
	{
		case '+':
			result = operand1 + operand2;
			break;

		case '-':
			result = operand1 - operand2;
			break;

		case '*':
			result = operand1 * operand2;
			break;

		case '/':
			// add throw div by 0 error
			result = operand1 / operand2;
			break;

		case '^':
			result = pow(operand1, operand2);
			break;

		default:
			//add throw error
			return -1;
	}

	return result;
}






std::string reverse(std::string &inExpression)
{
	int length = inExpression.length();

	// Changes open parentheses to closed parentheses and vice versa
	for (int i = 0; i < length; i++)
	{
		if (inExpression[i] == '(')
		{
			inExpression[i] = ')';
		}

		else if (inExpression[i] == ')')
		{
			inExpression[i] = '(';
		}
	}

	// Reverses the string
	for (int count = 0; count < length/2; count++)
	{
		char temp = inExpression[count];
		inExpression[count] = inExpression[length - 1 - count];
		inExpression[length - 1 - count] = temp;
	}

	return inExpression;
}






/**************************************************
* evaluateInfix evaluates the incoming infix    *
* string "inExpression" and calculates an answer, *
* which is then returned as an double value.      *
**************************************************/
double evaluateInfix(std::string infixString)
{
	double result = 0;
	std::string postfixString = "";

	postfixString = infixToPostfix(infixString);

	result = evaluatePostfix(postfixString);


	return result;
}






double evaluatePostfix(std::string postfixString)
{
	std::stack<int> stack;

	int length = postfixString.length();
	std::string tempString = "";
	double tempNum = 0;

	double result = 0;

	for (int count = 0; count < length; count++)
	{

		// if current char is an operand
		if (isdigit(postfixString[count]))
		{
			std::string tempString;

			while (count < length && isdigit(postfixString[count]))
			{
					tempString += postfixString[count];
					count++;
			}

			count--;

			tempNum = stod(tempString);
			tempString = "";
			stack.push(tempNum);

		}


		// if current char is an operator
		else if (isOperator(postfixString[count]))
		{
			char symbol = postfixString[count];
			int operand1, operand2;
			operand2 = stack.top();
			stack.pop();
			operand1 = stack.top();
			stack.pop();

			stack.push(calculate(operand1, operand2, symbol));
		}

		else
		{
			//add error if not space char
			continue;
		}

	}

	result = stack.top();;
	return result;
}






double evaluatePrefix(std::string prefixString)
{
	double result = 0;

	std::string postfixString = prefixToPostfix(prefixString);
	result = evaluatePostfix(postfixString);

	return result;
}






/******************************************************************
* precedenceCheck is a helper function for infixToPostfix.        *
* It returns '0' if inOperator is a '+' or '-' (lower precedence) *
* and '1' if inOperator is a '*', '^', or '/' (higher precedence).*
******************************************************************/
int precedenceCheck(char inOperator)
{
	if (inOperator == '^')
	{
		return 3;
	}

	else if (inOperator == '*' || inOperator == '/')
	{
		return 2;
	}

	else if (inOperator == '+' || inOperator == '-')
	{
		return 1;
	}

	else
	{
		return 0;
	}
}






std::string infixToPostfix(std::string infixString)
{
	std::stack<char> operatorStack;
	std::string postfixString = "";

	int length = infixString.length();

	for (int count = 0; count < length; count++)
	{
		if (infixString[count] == '(')
		{
			operatorStack.push('(');
		}

		else if (isalnum(infixString[count]))
		{
			if (isdigit(infixString[count]))
			{
				std::string temp;

				while (count < length && isdigit(infixString[count]))
				{
					temp += infixString[count];
					count++;
				}

				count--;

				postfixString += temp;
				postfixString += ' ';

			}

			else
			{
				postfixString += infixString[count];
				postfixString += ' ';
			}
		}

		else if (infixString[count] == ')')
		{
			while (operatorStack.top() != '(' && !operatorStack.empty())
			{
				postfixString += operatorStack.top();
				postfixString += ' ';

				operatorStack.pop();
			}
				operatorStack.pop();
		}

		else if (isOperator(infixString[count]))
		{
			while (!operatorStack.empty() &&
					(precedenceCheck(operatorStack.top()) >= precedenceCheck(infixString[count]))
					&& operatorStack.top() != '(' && operatorStack.top() != ')')
			{
				postfixString += operatorStack.top();
				operatorStack.pop();
				postfixString += ' ';
			}
				operatorStack.push(infixString[count]);
		}
	}

	while (!operatorStack.empty())
	{
		postfixString += operatorStack.top();
		postfixString += ' ';
		operatorStack.pop();
	}

	return postfixString;
}






std::string infixToPrefix(std::string infixString)
{
	std::stack<char> operatorStack;
	std::stack<char> operandStack;
	std::string postfixExp = "";
	std::string prefixExp = "";
	std::string reversedExp = reverse(infixString);

	postfixExp = infixToPostfix(reversedExp);
	prefixExp = reverse(postfixExp);

	return prefixExp;
}






std::string postfixToInfix(std::string postfixString)
{
	std::stack<std::string> stack;
	int length = postfixString.size();
	std::string infixString = "";

	for (int count = 0; count < length; count++)
	{
		if (isOperator(postfixString[count]))
		{
			std::string operand1 = stack.top();
			stack.pop();

			std::string operand2 = stack.top();
			stack.pop();

			std::string temp = "(" + operand2 + ' ' + postfixString[count] + ' ' + operand1 + ")";

			stack.push(temp);
		}

	    else if (isalnum(postfixString[count]))
	    {
	    	if (isdigit(postfixString[count]))
	    	{
	    		std::string tempString;

	    		while (count < length && isdigit(postfixString[count]))
	    		{
	    			tempString += postfixString[count];
	    			count++;
	    		}

	    		count--;

	    		stack.push(tempString);
	    		tempString = "";
	    	}

	    	else
	    	{
	    		stack.push(std::string(1, postfixString[count]));
	    	}
	    }

		else
		{
			continue;
		}
	}

	infixString = stack.top();
	return infixString;
}






std::string prefixToInfix(std::string prefixString)
{
	std::stack<std::string> stack;
	std::string infixString = "";

	int length = prefixString.size();
	std::string reversedString = reverse(prefixString);


	for (int count = 0; count < length; count++)
	{
		if (isOperator(reversedString[count]))
	    {
	    	std::string operand1 = stack.top();
	    	stack.pop();

	    	std::string operand2 = stack.top();
	    	stack.pop();

	    	std::string temp = "(" + operand1 + ' ' + reversedString[count] + ' ' + operand2 + ")";

	    	stack.push(temp);
	    }

	    else if (isalnum(reversedString[count]))
	    {
	    	if (isdigit(reversedString[count]))
	    	{
	    		std::string tempString;

	    		while (count < length && isdigit(reversedString[count]))
	    		{
	    			tempString += reversedString[count];
	    			count++;
	    		}

	    		count--;

	    		stack.push(reverse(tempString));
	    		tempString = "";
	    	}

	    	else
	    	{
	    		stack.push(std::string(1, reversedString[count]));
	    	}
	    }

	    else
	    {
	    	continue;
	    }
	  }

	infixString = stack.top();
	return infixString;
}






std::string prefixToPostfix(std::string prefixString)
{
	std::string infixString = prefixToInfix(prefixString);
	std::string postfixString = infixToPostfix(infixString);

	return postfixString;
}






std::string postfixToPrefix(std::string postfixString)
{
	std::string infixString = postfixToInfix(postfixString);
	std::string prefixString = infixToPrefix(infixString);

	return prefixString;
}






int main()
{
	std::string string1;
	std::string string2;
	std::string string3;
	std::string string4;
	std::string string5;



	std::cout << std::endl;
	std::cout << "****************************************\n";
	std::cout << "* Testing of function \"infixToPostfix\" *\n";
	std::cout << "****************************************\n";

	std::cout << std::endl;
	string1 = "A + B";
	std::cout << "Infix expression: ";
	std::cout << string1 << std::endl;
	std::cout << "After conversion to postfix, the expression is now: ";
	std::cout << infixToPostfix(string1) << std::endl;

	std::cout << std::endl;
	string2 = "(A + B) * (C - D)";
	std::cout << "Infix expression: ";
	std::cout << string2 << std::endl;
	std::cout << "After conversion to postfix, the expression is now: ";
	std::cout << infixToPostfix(string2) << std::endl;

	std::cout << std::endl;
	string3 = "A - (B + C * D) / E";
	std::cout << "Infix expression: ";
	std::cout << string3 << std::endl;
	std::cout << "After conversion to postfix, the expression is now: ";
	std::cout << infixToPostfix(string3) << std::endl;

	std::cout << std::endl;
	string4 = "A ^ B / C * D + E";
	std::cout << "Infix expression: ";
	std::cout << string4 << std::endl;
	std::cout << "After conversion to postfix, the expression is now: ";
	std::cout << infixToPostfix(string4) << std::endl;

	std::cout << std::endl;
	string5 = "A + B * (C - D) / E + (F ^ G - H)";
	std::cout << "Infix expression: ";
	std::cout << string5 << std::endl;
	std::cout << "After conversion to postfix, the expression is now: ";
	std::cout << infixToPostfix(string5) << std::endl;






	std::cout << "\n\n\n***************************************\n";
	std::cout << "* Testing of function \"infixToPrefix\" *\n";
	std::cout << "***************************************\n";

	std::cout << std::endl;
	string1 = "A + B";
	std::cout << "Infix expression: ";
	std::cout << string1 << std::endl;
	std::cout << "After conversion to prefix, the expression is now: ";
	std::cout << infixToPrefix(string1) << std::endl;

	std::cout << std::endl;
	string2 = "(A + B) * (C - D)";
	std::cout << "Infix expression: ";
	std::cout << string2 << std::endl;
	std::cout << "After conversion to prefix, the expression is now: ";
	std::cout << infixToPrefix(string2) << std::endl;

	std::cout << std::endl;
	string3 = "A - (B + C * D) / E";
	std::cout << "Infix expression: ";
	std::cout << string3 << std::endl;
	std::cout << "After conversion to prefix, the expression is now: ";
	std::cout << infixToPrefix(string3) << std::endl;

	std::cout << std::endl;
	string4 = "A ^ B / C * (D + E)";
	std::cout << "Infix expression: ";
	std::cout << string4 << std::endl;
	std::cout << "After conversion to prefix, the expression is now: ";
	std::cout << infixToPrefix(string4) << std::endl;

	std::cout << std::endl;
	string5 = "A + B * (C - D ^ E) / F ^ G";
	std::cout << "Infix expression: ";
	std::cout << string5 << std::endl;
	std::cout << "After conversion to prefix, the expression is now: ";
	std::cout << infixToPrefix(string5) << std::endl;






	std::cout << "\n\n\n****************************************\n";
	std::cout << "* Testing of function \"postfixToInfix\" *\n";
	std::cout << "****************************************\n";

	std::cout << std::endl;
	string1 = "A + B";
	std::cout << "Infix expression: ";
	std::cout << string1 << std::endl;
	std::cout << "After conversion to postfix, the expression is now: ";
	string1 = infixToPostfix(string1);
	std::cout << string1 << std::endl;
	std::cout << "After conversion back to infix, the expression is now: ";
	string1 = postfixToInfix(string1);
	std::cout << string1 << std::endl;

	std::cout << std::endl;
	string2 = "(A + B) * (C - D)";
	std::cout << "Infix expression: ";
	std::cout << string2 << std::endl;
	std::cout << "After conversion to postfix, the expression is now: ";
	string2 = infixToPostfix(string2);
	std::cout << string2 << std::endl;
	std::cout << "After conversion back to infix, the expression is now: ";
	string2 = postfixToInfix(string2);
	std::cout << string2 << std::endl;

	std::cout << std::endl;
	string3 = "A - (B + C * D) / E";
	std::cout << "Infix expression: ";
	std::cout << string3 << std::endl;
	std::cout << "After conversion to postfix, the expression is now: ";
	string3 = infixToPostfix(string3);
	std::cout << string3 << std::endl;
	std::cout << "After conversion back to infix, the expression is now: ";
	string3 = postfixToInfix(string3);
	std::cout << string3 << std::endl;

	std::cout << std::endl;
	string4 = "A ^ B / C * (D + E)";
	std::cout << "Infix expression: ";
	std::cout << string4 << std::endl;
	std::cout << "After conversion to postfix, the expression is now: ";
	string4 = infixToPostfix(string4);
	std::cout << string4 << std::endl;
	std::cout << "After conversion back to infix, the expression is now: ";
	string4 = postfixToInfix(string4);
	std::cout << string4 << std::endl;

	std::cout << std::endl;
	string5 = "A + B * (C - D ^ E) / F ^ G";
	std::cout << "Infix expression: ";
	std::cout << string5 << std::endl;
	std::cout << "After conversion to postfix, the expression is now: ";
	string5 = infixToPostfix(string5);
	std::cout << string5 << std::endl;
	std::cout << "After conversion back to infix, the expression is now: ";
	string5 = postfixToInfix(string5);
	std::cout << string5 << std::endl;






	std::cout << "\n\n\n***************************************\n";
	std::cout << "* Testing of function \"prefixToInfix\" *\n";
	std::cout << "***************************************\n";

	std::cout << std::endl;
	string1 = "A + B";
	std::cout << "Infix expression: ";
	std::cout << string1 << std::endl;
	std::cout << "After conversion to prefix, the expression is now: ";
	string1 = infixToPrefix(string1);
	std::cout << string1 << std::endl;
	std::cout << "After conversion back to infix, the expression is now: ";
	string1 = prefixToInfix(string1);
	std::cout << string1 << std::endl;

	std::cout << std::endl;
	string2 = "(A + B) * (C - D)";
	std::cout << "Infix expression: ";
	std::cout << string2 << std::endl;
	std::cout << "After conversion to prefix, the expression is now: ";
	string2 = infixToPrefix(string2);
	std::cout << string2 << std::endl;
	std::cout << "After conversion back to infix, the expression is now: ";
	string2 = prefixToInfix(string2);
	std::cout << string2 << std::endl;

	std::cout << std::endl;
	string3 = "A - (B + C * D) / E";
	std::cout << "Infix expression: ";
	std::cout << string3 << std::endl;
	std::cout << "After conversion to prefix, the expression is now: ";
	string3 = infixToPrefix(string3);
	std::cout << string3 << std::endl;
	std::cout << "After conversion back to infix, the expression is now: ";
	string3 = prefixToInfix(string3);
	std::cout << string3 << std::endl;

	std::cout << std::endl;
	string4 = "A ^ B / C * (D + E)";
	std::cout << "Infix expression: ";
	std::cout << string4 << std::endl;
	std::cout << "After conversion to prefix, the expression is now: ";
	string4 = infixToPrefix(string4);
	std::cout << string4 << std::endl;
	std::cout << "After conversion back to infix, the expression is now: ";
	string4 = prefixToInfix(string4);
	std::cout << string4 << std::endl;

	std::cout << std::endl;
	string5 = "A + B * (C - D ^ E) / F ^ G";
	std::cout << "Infix expression: ";
	std::cout << string5 << std::endl;
	std::cout << "After conversion to prefix, the expression is now: ";
	string5 = infixToPrefix(string5);
	std::cout << string5 << std::endl;
	std::cout << "After conversion back to infix, the expression is now: ";
	string5 = prefixToInfix(string5);
	std::cout << string5 << std::endl;






	std::cout << "\n\n\n*****************************************\n";
	std::cout << "* Testing of function \"prefixToPostfix\" *\n";
	std::cout << "*****************************************\n";

	std::cout << std::endl;
	string1 = "+ A B";
	std::cout << "Prefix expression: ";
	std::cout << string1 << std::endl;
	std::cout << "After conversion to postfix, the expression is now: ";
	string1 = prefixToPostfix(string1);
	std::cout << string1 << std::endl;

	std::cout << std::endl;
	string2 = "* + A B - C D";
	std::cout << "Prefix expression: ";
	std::cout << string2 << std::endl;
	std::cout << "After conversion to postfix, the expression is now: ";
	string2 = prefixToPostfix(string2);
	std::cout << string2 << std::endl;

	std::cout << std::endl;
	string3 = "- A / + B * C D E";
	std::cout << "Prefix expression: ";
	std::cout << string3 << std::endl;
	std::cout << "After conversion to postfix, the expression is now: ";
	string3 = prefixToPostfix(string3);
	std::cout << string3 << std::endl;

	std::cout << std::endl;
	string4 = "/ ^ A B * C + D E";
	std::cout << "Prefix expression: ";
	std::cout << string4 << std::endl;
	std::cout << "After conversion to postfix, the expression is now: ";
	string4 = prefixToPostfix(string4);
	std::cout << string4 << std::endl;

	std::cout << std::endl;
	string5 = "+ A * B / - C ^ D E ^ F G";
	std::cout << "Prefix expression: ";
	std::cout << string5 << std::endl;
	std::cout << "After conversion to postfix, the expression is now: ";
	string5 = prefixToPostfix(string5);
	std::cout << string5 << std::endl;






	std::cout << "\n\n\n*****************************************\n";
	std::cout << "* Testing of function \"postfixToPrefix\" *\n";
	std::cout << "*****************************************\n";

	std::cout << std::endl;
	string1 = "A B +";
	std::cout << "Postfix expression: ";
	std::cout << string1 << std::endl;
	std::cout << "After conversion to prefix, the expression is now: ";
	string1 = postfixToPrefix(string1);
	std::cout << string1 << std::endl;

	std::cout << std::endl;
	string2 = "A B + C D - *";
	std::cout << "Postfix expression: ";
	std::cout << string2 << std::endl;
	std::cout << "After conversion to prefix, the expression is now: ";
	string2 = postfixToPrefix(string2);
	std::cout << string2 << std::endl;

	std::cout << std::endl;
	string3 = "A B C D * + E / -";
	std::cout << "Postfix expression: ";
	std::cout << string3 << std::endl;
	std::cout << "After conversion to prefix, the expression is now: ";
	string3 = postfixToPrefix(string3);
	std::cout << string3 << std::endl;

	std::cout << std::endl;
	string4 = "A B ^ C D E + * /";
	std::cout << "Postfix expression: ";
	std::cout << string4 << std::endl;
	std::cout << "After conversion to prefix, the expression is now: ";
	string4 = postfixToPrefix(string4);
	std::cout << string4 << std::endl;

	std::cout << std::endl;
	string5 = "A B C D E ^ - F G ^ / * +";
	std::cout << "Postfix expression: ";
	std::cout << string5 << std::endl;
	std::cout << "After conversion to prefix, the expression is now: ";
	string5 = postfixToPrefix(string5);
	std::cout << string5 << std::endl;






	std::cout << "\n\n\n*****************************************\n";
	std::cout << "* Testing of function \"evaluateInfix\" *\n";
	std::cout << "*****************************************\n";

	std::cout << std::endl;
	string1 = "10 + 243";
	std::cout << "Infix expression: ";
	std::cout << string1 << std::endl;
	std::cout << "Calculated value: ";
	std::cout << evaluateInfix(string1) << std::endl;

	std::cout << std::endl;
	string2 = "(7 + 3) - 12 + 3";
	std::cout << "Infix expression: ";
	std::cout << string2 << std::endl;
	std::cout << "Calculated value: ";
	std::cout << evaluateInfix(string2) << std::endl;

	std::cout << std::endl;
	string3 = "3 * 20 + (7 - 2)";
	std::cout << "Infix expression: ";
	std::cout << string3 << std::endl;
	std::cout << "Calculated value: ";
	std::cout << evaluateInfix(string3) << std::endl;

	std::cout << std::endl;
	string4 = "((9 + 11) / (5 - 3)) * 3 + 7";
	std::cout << "Infix expression: ";
	std::cout << string4 << std::endl;
	std::cout << "Calculated value: ";
	std::cout << evaluateInfix(string4) << std::endl;

	std::cout << std::endl;
	string5 = "(2 ^ 3 + (50 * 4)) / 4 ^ 2 - 20";
	std::cout << "Infix expression: ";
	std::cout << string5 << std::endl;
	std::cout << "Calculated value: ";
	std::cout << evaluateInfix(string5) << std::endl;






	std::cout << "\n\n\n*****************************************\n";
	std::cout << "* Testing of function \"evaluatePostfix\" *\n";
	std::cout << "*****************************************\n";

	std::cout << std::endl;
	string1 = "10 + 243";
	string1 = infixToPostfix(string1);
	std::cout << "Postfix expression: ";
	std::cout << string1 << std::endl;
	std::cout << "Calculated value: ";
	std::cout << evaluatePostfix(string1) << std::endl;

	std::cout << std::endl;
	string2 = "(7 + 3) - 12 + 3";
	string2 = infixToPostfix(string2);
	std::cout << "Postfix expression: ";
	std::cout << string2 << std::endl;
	std::cout << "Calculated value: ";
	std::cout << evaluatePostfix(string2) << std::endl;

	std::cout << std::endl;
	string3 = "3 * 20 + (7 - 2)";
	string3 = infixToPostfix(string3);
	std::cout << "Postfix expression: ";
	std::cout << string3 << std::endl;
	std::cout << "Calculated value: ";
	std::cout << evaluatePostfix(string3) << std::endl;

	std::cout << std::endl;
	string4 = "((9 + 11) / (5 - 3)) * 3 + 7";
	string4 = infixToPostfix(string4);
	std::cout << "Postfix expression: ";
	std::cout << string4 << std::endl;
	std::cout << "Calculated value: ";
	std::cout << evaluatePostfix(string4) << std::endl;

	std::cout << std::endl;
	string5 = "(2 ^ 3 + (50 * 4)) / 4 ^ 2 - 20";
	string5 = infixToPostfix(string5);
	std::cout << "Postfix expression: ";
	std::cout << string5 << std::endl;
	std::cout << "Calculated value: ";
	std::cout << evaluatePostfix(string5) << std::endl;






	std::cout << "\n\n\n*****************************************\n";
	std::cout << "* Testing of function \"evaluatePrefix\" *\n";
	std::cout << "*****************************************\n";

	std::cout << std::endl;
	string1 = "10 + 243";
	string1 = infixToPrefix(string1);
	std::cout << "Prefix expression: ";
	std::cout << string1 << std::endl;
	std::cout << "Calculated value: ";
	std::cout << evaluatePrefix(string1) << std::endl;

	std::cout << std::endl;
	string2 = "(7 + 3) - 12 + 3";
	string2 = infixToPrefix(string2);
	std::cout << "Prefix expression: ";
	std::cout << string2 << std::endl;
	std::cout << "\nPrefix to infix: " << prefixToInfix(string2) << std::endl;
	std::cout << "Calculated value: ";
	std::cout << evaluatePrefix(string2) << std::endl;

	std::cout << std::endl;
	string3 = "3 * 20 + (7 - 2)";
	string3 = infixToPrefix(string3);
	std::cout << "Prefix expression: ";
	std::cout << string3 << std::endl;
	std::cout << "Calculated value: ";
	std::cout << evaluatePrefix(string3) << std::endl;

	std::cout << std::endl;
	string4 = "((9 + 11) / (5 - 3)) * 3 + 7";
	string4 = infixToPrefix(string4);
	std::cout << "Prefix expression: ";
	std::cout << string4 << std::endl;
	std::cout << "Calculated value: ";
	std::cout << evaluatePrefix(string4) << std::endl;

	std::cout << std::endl;
	string5 = "(2 ^ 3 + (50 * 4)) / 4 ^ 2 - 20";
	string5 = infixToPrefix(string5);
	std::cout << "Prefix expression: ";
	std::cout << string5 << std::endl;
	std::cout << "Calculated value: ";
	std::cout << evaluatePrefix(string5) << std::endl;
}
