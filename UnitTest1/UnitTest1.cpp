#include "pch.h"
#include "CppUnitTest.h"
#include "../Project19/main.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(ReversePolishCalculatorTests)
    {
    public:
        TEST_METHOD(TestCalculate)
        {
            ReversePolishCalculator calculator;
            double result = calculator.calculate("100 3 5 * -");
            Assert::AreEqual(85.0, result);
        }
        TEST_METHOD(TestInvalidExpression)
        {
            ReversePolishCalculator calculator;

            Assert::ExpectException<std::invalid_argument>([&calculator] {
                calculator.calculate("100 3 * -"); 
                });

            Assert::ExpectException<std::invalid_argument>([&calculator] {
                calculator.calculate("100 3 5 * - *");
                });
        }

        TEST_METHOD(TestDivisionByZero)
        {
            ReversePolishCalculator calculator;

            Assert::ExpectException<std::runtime_error>([&calculator] {
                calculator.calculate("5 0 /");
                });
        }
    };
    TEST_CLASS(RPNConverterTests)
    {
    public:
        TEST_METHOD(TestInfixToRPN)
        {
            std::string infixExpression = "100 - 3 * 5";
            std::string expectedRPNExpression = "100 3 5 * -";
            std::string actualRPNExpression = RPNConverter::infixToRPN(infixExpression);
            Assert::AreEqual(expectedRPNExpression, actualRPNExpression);
        }
    };
}