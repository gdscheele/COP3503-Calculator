//
//  Logarithm.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Logarithm.h"

Logarithm::Logarithm(int base, int operand){
    this->type = "logarithm";
    this->base = base;
    this->operand = operand;
}
Logarithm::~Logarithm(){
    
}
Expression Logarithm::simplify(){
    Expression* c = this;
    return *c;
}



Expression* Logarithm::add(Expression* a){
    Expression* c = this;
    return c;
}
Expression* Logarithm::subtract(Expression* a){
    Expression* c = this;
    return c;
}
Expression* Logarithm::multiply(Expression* a){
    Expression* c = this;
    return c;
}
Expression* Logarithm::divide(Expression* a){
    Expression* c = this;
    return c;
}
ostream& Logarithm::print(std::ostream& output) const{
    output << "Log" << this->base << "(" << this->operand << ")";
    return output;
}
