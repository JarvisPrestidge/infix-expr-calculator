// ExprCalc.cpp : Jarvis Prestidge
// Description  : Class used to convert an infix expression to
// postfix notation. Built using TDD.

#include "ExprCalc.h"

#include <stdexcept>
#include <algorithm>
#include <iostream>

bool IsDigit(char digit) {
  if (digit >= '1' && digit <= '9')
    return true;
  return false;
}

bool IsOperator(char op) {
  switch (op) {
    case '+':
    case '-':
    case '*':
    case '/':
      return true;
    default:
      return false;
  }
  return true;
}

bool Precedence(char lhs, char rhs) {
  if (((lhs == '*' || lhs == '/') && (rhs == '+' || rhs == '-')) || rhs == '(')
    return true;
  return false;
}

std::stack<char> InfixToPostfix(std::string infix) {
  std::stack<char> postfix;
  std::stack<char> stack;
  for (int i = 0; (unsigned)i < infix.size(); ++i) {
    char current = infix[i];
    if (current == ' ') {
    } else if (current == '(') {
      stack.push(current);
    } else if (current == ')') {
      while (!stack.empty() && (stack.top() != '(')) {
        postfix.push(stack.top());
        stack.pop();
      }
      if (!stack.empty()) {
        stack.pop();
      } else {
        throw std::runtime_error("Runtime error!");
      }
    } else if (IsDigit(current)) {
      postfix.push(current);
    } else if (IsOperator(current)) {
      if (stack.empty()) {
        stack.push(current);
      } else {
        while (!stack.empty()) {
          if (Precedence(current, stack.top())) {
            stack.push(current);
            break;
          } else {
            postfix.push(stack.top());
            stack.pop();
            if (stack.empty()) {
              stack.push(current);
              break;
            }
          } 
        } 
      } 
    } 
  } 
  for (int i = 0; (unsigned)i <= stack.size(); ++i) {
    if (stack.top() == '(') {
      stack.pop();
      if (stack.empty()) {
        break;
      }
    }
    postfix.push(stack.top());
    stack.pop();
  }
  return postfix;
}

std::string StackToString(std::stack<char> stack) {
  std::string str;
  for (int i = 0, j = stack.size(); i < j; ++i) {
    str += ' ';
    str += stack.top();
    stack.pop();
  }
  std::reverse(str.rbegin(), str.rend());
  return str;
}

int ApplyOperator(char op, int operand1, int operand2) {
  switch (op) {
    case '+':
      return operand1 + operand2;
    case '-':
      return operand1 - operand2;
    case '*':
      return operand1 * operand2;
    case '/':
      return operand1 / operand2;
    default: 
      return -1;
  }
}

int CalcPostfix(std::string postfix) {
  std::stack<int> stack;
  for (int i = 0; (unsigned)i < postfix.size(); ++i) {
    if (postfix[i] == ' ') {
      continue;
    } else if (IsDigit(postfix[i])) {
      int num = postfix[i] - '0';
      stack.push(num);
    } else if (IsOperator(postfix[i])) {
      int operand2 = stack.top();
      stack.pop();
      int operand1 = stack.top();
      stack.pop();
      int result = ApplyOperator(postfix[i], operand1, operand2);
      stack.push(result);
    }
  }
  return stack.top();
}

int main() {
  std::string infix;
  std::cout << "Infix expression: \t";
  std::getline (std::cin, infix);
  std::stack<char> stack;
  try {
    stack = InfixToPostfix(infix);
  } catch (const std::runtime_error&  e) {
    std::cout << "Incorrect expression syntax... Exiting" << std::endl;
    return 0;
  }
  std::string postfix = StackToString(stack);
  std::cout << "Postfix expression: \t" << postfix << std::endl;
  int result = CalcPostfix(postfix);
  std::cout << "Expression result: \t" << result << std::endl;
  return 0;
}