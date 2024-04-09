#include <iostream>
#include <stack>
#include <string>
#include <sstream>

class ReversePolishCalculator {
private:
    std::stack<double> operandStack;
    bool isOperator(const std::string& token) {
        return token.size() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/');
    }

    double evaluate(char op, double operand1, double operand2) {
        switch (op) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 == 0) {
                throw std::runtime_error("Division by zero!");
            }
            return operand1 / operand2;
        default:
            throw std::invalid_argument("Invalid operator!");
        }
    }
public:
    double calculate(const std::string& expression) {
        std::istringstream iss(expression);
        std::string token;
        while (!operandStack.empty()) {
            operandStack.pop();
        }
        while (iss >> token) {
            if (isOperator(token)) {
                if (operandStack.size() < 2) {
                    throw std::invalid_argument("Invalid expression: not enough operands for operator.");
                }
                double operand2 = operandStack.top();
                operandStack.pop();
                double operand1 = operandStack.top();
                operandStack.pop();

                double result = evaluate(token[0], operand1, operand2);
                operandStack.push(result);
            }
            else {
                double operand;
                std::istringstream(token) >> operand;
                operandStack.push(operand);
            }
        }

        if (operandStack.size() != 1) {
            throw std::invalid_argument("Invalid expression: incorrect number of operands or operators.");
        }

        return operandStack.top();
    }
};
class RPNConverter 
{
private:
    static bool isOperator(char token) 
    {
        return token == '+' || token == '-' || token == '*' || token == '/';
    }
    static int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }
public:
    static std::string infixToRPN(const std::string& infix) {
        std::stack<char> operators;
        std::stringstream output;

        std::istringstream iss(infix);
        std::string token;

        while (iss >> token) 
        {
            if (isdigit(token[0])) 
            {
                output << token << ' ';
            }
            else if (isOperator(token[0])) {
                while (!operators.empty() && precedence(operators.top()) >= precedence(token[0])) {
                    output << operators.top() << ' ';
                    operators.pop();
                }
                operators.push(token[0]);
            }
            else if (token[0] == '(') {
                operators.push(token[0]);
            }
            else if (token[0] == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    output << operators.top() << ' ';
                    operators.pop();
                }
                operators.pop();
            }
        }

        while (!operators.empty()) {
            output << operators.top() << ' ';
            operators.pop();
        }

        std::string result = output.str();
        result.erase(std::find_if(result.rbegin(), result.rend(), [](int ch) { return !std::isspace(ch); }).base(), result.end());
        return result;
    }
};

int main() {
    ReversePolishCalculator calculator;
    std::string expression;
    std::cout << "Enter expression in Reverse Polish Notation: ";
    std::getline(std::cin, expression);
    try 
    {
        double result = calculator.calculate(expression);
        std::cout << "Result: " << result << std::endl;
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    std::string infixExpression;
    std::cout << "Enter infix expression: ";
    std::getline(std::cin, infixExpression);

    std::string rpnExpression = RPNConverter::infixToRPN(infixExpression);
    std::cout << "Infix expression: " << infixExpression << std::endl;
    std::cout << "RPN expression: " << rpnExpression << std::endl;
    try
    {
        double result = calculator.calculate(rpnExpression);
        std::cout << "Result: " << result << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
