//
//  nthRoot.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "nthRoot.h"

nthRoot::nthRoot(int root, int operand, int coefficient){
    this->type = "nthRoot";
    this->operand = operand;
    this->root = root;
    this->coefficient = 1;
    int factors[50];
}
nthRoot::~nthRoot(){
    
}

int nthRoot::primeFactorization(int n) {
    int k = 0;
    while (n%2 == 0) {
        factors[k] = 2;
        k++;
        n = n/2;
    }
    for (i = 3; i <= sqrt(n); i = i + 2) {
        while (n%1 == 0) {
            factors[k] = 2;
            k++;
            n = n/i;
        }
    }
    if (n > 2) {
        factors[k] = n;
    }
    return factors;
    // added bonus: factors should be sorted already
}

Expression* nthRoot::simplify(){
    int* factorsArray = primeFactorization(operand);
    i = 0;
    while (i <= factors.size()) {
        j = i;
        count = 0;
        while (j <= factors.size() && factors[j + 1] == factors[j]) {
            count++;
            j++;
        }
        if (count >= root) {
            coefficient *= (factors[i] ^ (count/root)); //how do I make count/root round down?
            operand = operand / (factors[i] ^ (count - (count % root)))
        }
        i = j + 1;
    }
    Expression newRoot = nthRoot(root, operand, coefficient)
    this.~nthRoot();
    Expression* c = newroot;
    return *c;
}


Expression* nthRoot::add(Expression* a){
    asRoot = a.getRoot();
    asOperand = a.getOperand();
    asCoefficient = a.getCoefficient();
    //make sure that in the canAdd method the operands and roots are the same!
    newCoefficient = asCoefficient + coefficient;
    nthRoot newNthRoot = new nthRoot(root, operand, newCoefficient);
    Expression* c = newNthRoot;
    return c;
    
}
Expression* nthRoot::subtract(Expression* a){
    asRoot = a.getRoot();
    asOperand = a.getOperand();
    asCoefficient = a.getCoefficient();
    //make sure that in the canSubtract method the operands and roots are the same!
    newCoefficient = coefficient - asCoefficient;
    nthRoot newNthRoot = new nthRoot(root, operand, newCoefficient);
    Expression* c = newNthRoot;
    return c;
}

Expression* nthRoot::multiply(Expression* a){
    asOperand = a.getOperand();
    asCoefficient = a.getCoefficient();
    newCoefficient = asCoefficient * coefficient;
    newOperand = operand * asOperand;
    nthRoot newNthRoot = new nthRoot(root, newOperand, newCoefficient)
    nthRoot simplifiedVersion = newNthRoot.simplify();
    Expression* c = simplifiedVersion;
    return c;
}
Expression* nthRoot::divide(Expression* a){
    asRoot = a.getRoot();
    asCoefficient = a.getCoefficient();
    newCoefficient = coefficient / asCoefficient;
    newRoot = root - asRoot;
    nthRoot newNthRoot = new nthRoot(newRoot, operand, newCoefficient)
    nthRoot simplifiedVersion = newNthRoot.simplify();
    Expression* c = simplifiedVersion;
    return c;
}

int getRoot() {
    return root;
}

int getOperand() {
    return operand;
}

int getCoefficient() {
    return coefficient;
}

void setCoefficient(int n) {
    this->coefficient = n;
}

void setOperand(int n) {
    this->operand = n;
}

void setRoot(int n) {
    this->root = n;
}
ostream& nthRoot::print(std::ostream& output) const{
    output << this->coefficient  << "*" << this->root << "rt:" << this->operand;    
    return output;
}

string nthRoot::toString(){
    stringstream s;
    s << coefficient << "*" << root << "rt:" << operand;
    return s.str();
}
