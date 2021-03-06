//
//  Exponent.h
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#ifndef __Calculator__Exponential__
#define __Calculator__Exponential__

#include <iostream>
#include "Expression.h"
#include "Solver.h"

class Integer;
class Rational;
class Exponential : public Expression{
public:
    Exponential(Expression* base, Rational* exponent);
    ~Exponential();
    void exponentiate();
    Expression* exponentiate(Rational* expo); //exponentiate using parameter as exponent
    Rational* getExponent();
    Expression* getBase();
    Integer* getExnu();
    Integer* getExde();
    void setExnu(Integer* n);
    void setExde(Integer* n);
    void setExponent(Rational* e);
    void setBase(Expression* e);
    bool canExponentiate();
    string toString();

    Expression* add(Expression* a);
    Expression* subtract(Expression* a);
    Expression* multiply(Expression* a);
    Expression* divide(Expression* a);
    bool canAdd(Expression* b);
    bool canSubtract(Expression* b);
    bool canMultiply(Expression* b);
    bool canDivide(Expression* b);
    ostream& print(std::ostream& output) const;

private:
    Expression* base;
    Rational* exponent;
    Integer* exnu;
    Integer* exde;
};
#endif /* defined(__Calculator__Exponential__) */
