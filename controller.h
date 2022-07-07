#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <cstdlib>

class Controller
{
public:
    Controller();
    ~Controller();
    std::string compute(const std::string expression);
    void parse(std::string op);
    float calculate(float firstValue, float secondValue, char op);

private:
    std::string temporary;
};

#endif // CONTROLLER_H
