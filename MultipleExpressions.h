#ifndef MULTIPLEEXPRESSIONS_H_INCLUDED
#define MULTIPLEEXPRESSIONS_H_INCLUDED

#include <iostream>
#include "Expression.h"
#include "Exponential.h"
#include "Logarithm.h"
#include "Integer.h"
#include "Rational.h"
#include "Solver.h"
#include <sstream>
using namespace std;

class MultipleExpressions : public Expression{
public:
    MultipleExpressions(string s);
    ~MultipleExpressions();
    string toString();
	string getExpressions();
    ostream& print(std::ostream& output) const;
    Expression* add(Expression* a);
    Expression* subtract(Expression* a);
    Expression* multiply(Expression* a);
    Expression* divide(Expression* a);

private:
    string expressions;
};


#endif // MULTIPLELOGS_H_INCLUDED
