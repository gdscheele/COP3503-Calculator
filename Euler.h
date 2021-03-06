//
//  Euler.h
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#ifndef __Calculator__Euler__
#define __Calculator__Euler__

#include <iostream>
#include "Expression.h"
#include "Exponential.h"
#include "Logarithm.h"
#include "Integer.h"
#include "Rational.h"
#include "Solver.h"
#include <sstream>

class Euler : public Expression{
public:
    Euler();
    ~Euler();

    Expression* add(Expression* a);
    Expression* subtract(Expression* a);
    Expression* multiply(Expression* a);
    Expression* divide(Expression* a);
    bool canAdd(Expression* b);
    bool canSubtract(Expression* b);
    bool canMultiply(Expression* b);
    bool canDivide(Expression* b);
    string toString();
	Integer* getCoefficient();
	void setCoefficient(Integer* x);
    ostream& print(std::ostream& output) const;
private:
    Integer* coefficient;
};
#endif /* defined(__Calculator__Euler__) */
