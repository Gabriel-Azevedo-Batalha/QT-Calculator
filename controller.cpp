#include "controller.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <algorithm>

Controller::Controller()
{
}

Controller::~Controller() = default;

float Controller::calculate(float firstValue, float secondValue, char op)
{
    float result;
    if(op == '/') result = firstValue/ secondValue;
    else if(op == 'x') result = firstValue * secondValue;
    else if(op == '+') result = firstValue + secondValue;
    else result = firstValue - secondValue;
    return result;
}

void Controller::parse(std::string ops)
{
    while (1) {
        size_t op = temporary.find_first_of(ops);
        if (op == 0 && temporary[op] == '-') {
            op = temporary.substr(1).find_first_of(ops) + 1;
        //    std::cout << "Novo op " << op << std::endl;
        }

        if(op == std::string::npos) break;
        int size = temporary.size();
        //std::cout << "Op " << op << " Op+1 " << temporary[op+1]  << std::endl;
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
        //std::cout << "Strings " << temporary.substr(firstOp, op).c_str()  << " e " << temporary.substr(op+1, secondOp).c_str() << std::endl;
        if (op - firstOp == 0) break;
        float firstValue = std::stof(temporary.substr(firstOp, op).c_str());
        float secondValue = std::stof(temporary.substr(op+1, secondOp).c_str());
        //std::cout << "Posicoes " << firstOp  << " e " << secondOp << std::endl;
        //std::cout << "Valores " << firstValue  << " e " << secondValue << std::endl;
        float result = calculate(firstValue, secondValue, temporary[op]);
        //std::cout << " New String " << temporary.substr(0, firstOp).c_str()  << " + " << std::to_string(result) << " + " << temporary.substr(secondOp, size).c_str() << std::endl;
        std::stringstream resultStringStream;
        resultStringStream << result;
        std::string resultString = resultStringStream.str();
        //std::cout << "Result " << resultString << std::endl;
        std::replace(resultString.begin(), resultString.end(), '.', ',');
        temporary = temporary.substr(0, firstOp) + resultString  + temporary.substr(secondOp, size);
    }
}

std::string Controller::compute(std::string expression){
    temporary = expression;
    parse("x/");
    parse("+-");
    return temporary;
}
