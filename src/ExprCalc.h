// ExprCalc.h: Jarvis Prestidge
// Description: Header for the ExprCalc class.  

#include <string>
#include <queue>
#include <stack>

bool IsDigit(char digit);

bool IsOperator(char op);

bool Precedence(char lhs, char rhs);

std::stack<char> InfixToPostfix(std::string infix);

std::string StackToString(std::stack<char> stack);

int ApplyOperator(char operation, int operand1, int operand2);

int CalcPostfix(std::string postfix);