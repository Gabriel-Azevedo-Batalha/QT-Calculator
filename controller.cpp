#include "controller.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>

Controller::Controller() = default;

Controller::~Controller() = default;

float Controller::calculate(float firstValue, float secondValue, char op)
{
    float result;
    switch (op) {
    case ('/'):
        result = firstValue/ secondValue;
        break;
    case('x'):
        result = firstValue * secondValue;
        break;
    case('+'):
        result = firstValue + secondValue;
        break;
    default:
        result = firstValue - secondValue;
        break;
    }
    return result;
}

void Controller::parse(std::string ops)
{
    while (1) {
        size_t op = temporary.find_first_of(ops);
        if (op == 0 && temporary[op] == '-') {
            op = temporary.substr(1).find_first_of(ops) + 1;
        }

        if(op == std::string::npos) break;
        int size = temporary.size();
        if ((op == 0 && temporary[op] != '-') || op == size || (!isdigit(temporary[op+1]) && temporary[op+1] != '-')){
            temporary = "Error: Invalid Expression!";
            break;
        }

        // Search first operand
        int firstOp = 0;
        for (int i=op-1; i>=0; i--) {
            if (i == 0 && temporary[i] == '-') {
                firstOp = 0;
                break;
            }
            if (!isdigit(temporary[i]) && temporary[i] != ',') {
                firstOp = i+1;
                break;
            }
        }
        // Search second operand
        int secondOp = size;
        for (int i=op+1; i<=size; i++) {
            if (i == op+1 && temporary[i] == '-') continue;
            else if (!isdigit(temporary[i]) && temporary[i] != ',') {
                secondOp = i;
                break;
            }
        }
        if (op - firstOp == 0) break;
        float firstValue = std::stof(temporary.substr(firstOp, op).c_str());
        float secondValue = std::stof(temporary.substr(op+1, secondOp).c_str());
        float result = calculate(firstValue, secondValue, temporary[op]);
        std::stringstream resultStringStream;
        resultStringStream << result;
        std::string resultString = resultStringStream.str();
        std::replace(resultString.begin(), resultString.end(), '.', ',');
        temporary = temporary.substr(0, firstOp) + resultString  + temporary.substr(secondOp, size);
    }
}

std::string Controller::compute(const std::string expression){
    temporary = expression;
    parse("x/");
    parse("+-");
    return temporary;
}
