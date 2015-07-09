// ExprCalc_unittest.cpp  : Jarvis Prestidge
// Description  : Testing class to test ExprCalc using the gtest framework.

#include "ExprCalc.h"
#include "gtest/gtest.h"

#include <string>
#include <stack>

TEST(ExprCalcTest, IsDigit) {
  // Checks helper function to parse digits and return bool.
  EXPECT_TRUE(IsDigit('1'));
  EXPECT_TRUE(IsDigit('9'));
  EXPECT_FALSE(IsDigit('*')); 
  EXPECT_FALSE(IsDigit('c'));
}

TEST(ExprCalcTest, IsOperator) {
  // Checks if char is an operator and returns bool.
  EXPECT_TRUE(IsOperator('*'));
  EXPECT_TRUE(IsOperator('/'));
  EXPECT_TRUE(IsOperator('-'));
  EXPECT_TRUE(IsOperator('+'));
  EXPECT_FALSE(IsOperator('1')); 
  EXPECT_FALSE(IsOperator('c')); 
}

TEST(ExprCalcTest, PrecedenceOrder) {
  // Checks that the left hand side precedence to higher than rhs.
  // Returns true if the case.
  EXPECT_FALSE(Precedence('+', '+'));
  EXPECT_FALSE(Precedence('+', '-'));
  EXPECT_FALSE(Precedence('-', '-'));
  EXPECT_FALSE(Precedence('-', '+'));
  EXPECT_FALSE(Precedence('*', '*'));
  EXPECT_FALSE(Precedence('*', '/'));
  EXPECT_FALSE(Precedence('/', '/'));
  EXPECT_FALSE(Precedence('/', '*'));
  EXPECT_TRUE(Precedence('*', '+'));
  EXPECT_TRUE(Precedence('/', '-'));
  EXPECT_TRUE(Precedence('*', '-'));
  EXPECT_TRUE(Precedence('/', '+'));
  EXPECT_FALSE(Precedence('+', '*')); 
  EXPECT_FALSE(Precedence('+', '/'));
  EXPECT_FALSE(Precedence('-', '/')); 
  EXPECT_FALSE(Precedence('-', '*'));
}

// TEST(ExprCalcTest, InfixToPostfixConversion) {
//   // Checks that the InfixToPostfix function correctly converts.
//   EXPECT_EQ("132*+", InfixToPostfix("1 + 3 * 2"));
//   EXPECT_EQ("42/1-6+", InfixToPostfix("4 / 2 - 1 + 6"));
// }

// TEST(ExprCalcTest, ParenthesisExtension1) {
//   // Checking if adding parenthesis now works.
//   EXPECT_EQ("132*+", InfixToPostfix("1 + (3 * 2)")); 
// }

// TEST(ExprCalcTest, ParenthesisExtension2) {
//   // Checking if adding parenthesis now works.
//   EXPECT_EQ("13+2*", InfixToPostfix("(1 + 3) * 2"));
// }

TEST(ExprCalcTest, CalulatingResultFromPostfix1) {
  // Testing the calcuation of the stack passed to CalcPostfix().
  // std::string str = "13+2*";
  std::stack<char> stack;
  stack.push('1');
  stack.push('3');
  stack.push('+');
  stack.push('2');
  stack.push('*');
  EXPECT_EQ(8, CalcPostfix(stack));
}

TEST(ExprCalcTest, CalulatingResultFromPostfix2) {
  // Testing the calcuation of the stack passed to CalcPostfix().
  // std::string str = "132*+";
  std::stack<char> stack;
  stack.push('1');
  stack.push('3');
  stack.push('2');
  stack.push('*');
  stack.push('+');
  EXPECT_EQ(7, CalcPostfix(stack));
}