//
//  nthRoot.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "nthRoot.h"
#include "Integer.h"
#include <array>
using namespace std;
nthRoot::nthRoot(int root, int operand, int coefficient) {
    this->type = "nthRoot";
    this->operand = operand;
    this->root = root;
    this->coefficient = coefficient;
    this->simplify();

    if ((root % 2) == 0 && operand < 0) {
        throw runtime_error("unreal answer");
    }
}

nthRoot::nthRoot(int root, Expression* eoperand, int coefficient) {
    this->type = "nthRoot";
    this->eoperand = eoperand;
    this->root = root;
    this->coefficient = coefficient;

    if ((root % 2) == 0 && eoperand->type == "integer") {
        Integer *a = (Integer *)eoperand;
        if (a->getValue() < 0) {
            throw runtime_error("unreal answer");
        }
    }

    if ((root % 2) == 0 && eoperand->type == "Rational"){
        Rational *b = (Rational*)eoperand;
        if ((b->getNumerator() < 0 || b->getDenominator() < 0)
             && !(b->getNumerator() < 0 && b->getDenominator() < 0)) {
             throw runtime_error("unreal answer");
        }
    }
}

nthRoot::~nthRoot() {

}

 int* nthRoot::primeFactorization(int n, int div, int k) {
    if (n % div == 0) {
        factors[k] = div;
        if (div == n) {
            factors[k+1] = 0; //the zero works as a stopping point later on
            return factors;
        }
        else {
            primeFactorization((n / div), div, (k + 1));
        }
    }
    else if (div <= n) {
        primeFactorization(n, (div + 1), k);
    }
    return factors;
}

int nthRoot::localExponentiate(int base, int locExponent) {
    if (locExponent >= 1)
        return base * (localExponentiate(base, locExponent - 1));
    else return 1;
}

/*
int nthRoot::localExponentiate(int under, int locExponent) {
    for (int i = 1; i < locExponent; i++) {
        under *= under;
    }
//    cout << under << "\n";
    return under;
}
*/
/*int* nthRoot::primeFactorization(int n, int num, int number) {    //non-recursive version
    int k = 0;
    int* factors;
    while (n%2 == 0) {
        factors[k] = 2;
        k++;
        n = n/2;
    }
    for (int i = 3; i <= sqrt(n); i = i + 2) {
//        if (n%i == 0) {
            while (n%i == 0) {
                factors[k] = i;
                k++;
                n = n/i;
            }
//        }
    }
    if (n > 2) {
        factors[k] = n;
    }
    n = 3;
    return factors;
    // added bonus: factors should be sorted already
} */

Expression* nthRoot::simplify(){
    //if coefficient == 0 then return 0?
    //if operand < 0 throw an error
    if ((root % 2) == 0 && operand < 0) {
        throw runtime_error("unreal answer");
    }
//    int *factorsCopy = this->primeFactorization(operand, 2, 0);
      this->primeFactorization(operand, 2, 0);
//    copy(this->primeFactorization(operand, 2, 0)+50, factors);
    int i = 0;
    int factorsSize = sizeof(factors)/sizeof(factors[0]);

    while (i <= factorsSize && factors[i] != 0) {   //all this takes unnecessary factors out of the operand
        int j = i;               //and puts them into the coefficient
        int count = 1;
        while (j <= factorsSize && factors[j + 1] == factors[j] && factors[j] != 0) {
            count++;
            j++;
        }
        if (count >= root) {

            coefficient = coefficient * localExponentiate(factors[i], (count/root));
            operand = (operand / localExponentiate(factors[i], (count - (count % root))));
        }
        i = j + 1;
    }
    if (operand == 1) {
        Integer* newInt = new Integer(coefficient);
        return newInt;
    }
    else {
        /*Expression* newRoot = new nthRoot(root, operand, coefficient);
        return newRoot; */
        return this;
    }

}


Expression* nthRoot::add(Expression* a) {
    nthRoot *b = (nthRoot *)a;
    int asCoefficient = b->getCoefficient();
    int asOperand = b->getOperand();
    int asRoot = b->getRoot();
    if (root == asRoot && operand == asOperand) {
        int newCoefficient = asCoefficient + coefficient;
        nthRoot* newNthRoot = new nthRoot(root, operand, newCoefficient);
        nthRoot* simplifiedVersion = (nthRoot *)newNthRoot->simplify();
        return simplifiedVersion;
    }
    else {
        return this;
    }
}

Expression* nthRoot::subtract(Expression* a) {
    nthRoot *b = (nthRoot *)a;
    int asCoefficient = b->getCoefficient();
    int asOperand = b->getOperand();
    int asRoot = b->getRoot();
    if (root == asRoot && operand == asOperand) {
        int newCoefficient = coefficient - asCoefficient;
        nthRoot* newNthRoot = new nthRoot(root, operand, newCoefficient);
        nthRoot* simplifiedVersion = (nthRoot *)newNthRoot->simplify();
        return simplifiedVersion;
    }
    else {
        return this;
    }
}

Expression* nthRoot::multiply(Expression* a) {
    if (a->type == "integer") {
        Integer *b = (Integer*)a;
        int asValue = b->getValue();
        int newCoefficient = asValue * coefficient;
        nthRoot* newNthRoot = new nthRoot(root, operand, newCoefficient);
        nthRoot* simplifiedVersion = (nthRoot *)newNthRoot->simplify();
        return simplifiedVersion;
    }
    if (a->type == "nthRoot") {
        nthRoot *b = (nthRoot *)a;
        int asCoefficient = b->getCoefficient();
        int asOperand = b->getOperand();
        int asRoot = b->getRoot();
        if (root == asRoot) {
            int newCoefficient = asCoefficient * coefficient;
            int newOperand = operand * asOperand;       //asOperand doesnt exist?
            nthRoot* newNthRoot = new nthRoot(root, newOperand, newCoefficient);
            nthRoot* simplifiedVersion = (nthRoot *)newNthRoot->simplify();
            return simplifiedVersion;
        }
    }
    else {
        return this;
    }
    return this;
}

Expression* nthRoot::divide(Expression* a) {
    nthRoot *b = (nthRoot *)a;
    int asRoot = b->getRoot();
    int asOperand = b->getOperand();
    int asCoefficient = b->getCoefficient();
    if (root == asRoot && fmod( ((double)coefficient / (double)asCoefficient), 1) == 0 && fmod(((double)operand / (double)asOperand), 1) == 0) {
        int newCoefficient = coefficient / asCoefficient;
        int newOperand = operand / asOperand;
        nthRoot* newNthRoot = new nthRoot(root, newOperand, newCoefficient);
        nthRoot* simplifiedVersion = (nthRoot *)newNthRoot->simplify();
        return simplifiedVersion;
    }
   else if (fmod( ((double)coefficient / (double)asCoefficient),1) == 0) {
        int newCoefficient = coefficient / asCoefficient;
        nthRoot* newNthRoot = new nthRoot(root, operand, newCoefficient);
        nthRoot* simplifiedVersion = (nthRoot *)newNthRoot->simplify();
        return simplifiedVersion;
    }
    else {
        return this;
    }
}

int nthRoot::getRoot() {
    return root;
}

int nthRoot::getOperand() {
    return operand;
}

int nthRoot::getCoefficient() {
    return coefficient;
}

void nthRoot::setCoefficient(int n) {
    this->coefficient = n;
}

void nthRoot::setOperand(int n) {
    this->operand = n;
}

void nthRoot::setRoot(int n) {
    this->root = n;
}
ostream& nthRoot::print(std::ostream& output) const {
    if (this->operand == 1) {
        output << this->coefficient;
    }else if(this->coefficient == 1){
        output << this->root << "rt:" << this->operand;
    }else{
        output << this->coefficient  << "*" << this->root << "rt:" << this->operand;
    }
    return output;
}

string nthRoot::toString() {
    stringstream s;
    if (this->operand == 1) {
        s << this->coefficient;
    }else if(this->coefficient == 1){
        s << this->root << "rt:" << this->operand;
    }else{
        s << this->coefficient  << "*" << this->root << "rt:" << this->operand;
    }
    return s.str();
}




bool nthRoot::canAdd(Expression* b){     //use "this" as comparison. Solver will call someExpression.canAdd(&someOtherExpression)

    if (this->type == b->type && this->type != "logarithm") {
        if (this->type == "nthRoot") {
        }
        return true;
    }else if((this->type == "integer" && b->type == "rational") || (this->type == "rational" && b->type == "integer")){
        return true;
    }else if(this->type == "multiple" && b->type == "multiple"){
        MultipleExpressions *t = (MultipleExpressions *)this;
        MultipleExpressions *m = (MultipleExpressions *)b;
        if ((t->meType == "as" && m->meType == "as") || (t->meType == "md" && m->meType == "md")) {
            return true;
        }
    }else if(this->type == "multiple" || b->type == "multiple") return true;
    return false;
}
bool nthRoot::canSubtract(Expression* b){
    if (this->type == b->type) {
        return true;
    }else if((this->type == "integer" && b->type == "rational") || (this->type == "rational" && b->type == "integer")){
        return true;
    }else if(this->type == "multiple" && b->type == "multiple"){
        MultipleExpressions *t = (MultipleExpressions *)this;
        MultipleExpressions *m = (MultipleExpressions *)b;
        if ((t->meType == "as" && m->meType == "as") || (t->meType == "md" && m->meType == "md")) {
            return true;
        }
    }else if(this->type == "multiple" || b->type == "multiple") return true;
    return false;
}
bool nthRoot::canMultiply(Expression* b){
    if (this->type == b->type) {
        return true;
    }
    else if(this->type == "integer" && b->type == "rational") return true;
    else if(this->type == "rational" && b->type == "integer") return true;
    else if(this->type == "multiple" && b->type == "multiple"){
        MultipleExpressions *t = (MultipleExpressions *)this;
        MultipleExpressions *m = (MultipleExpressions *)b;
        if ((t->meType == "as" && m->meType == "as") || (t->meType == "md" && m->meType == "md")) {
            return true;
        }
    }else if(this->type == "multiple" || b->type == "multiple") return true;
    return false;

}
bool nthRoot::canDivide(Expression* b){
    if (this->type == b->type) {
        return true;
    }
    else if(this->type == "integer"){
        if( b->type == "rational") return true;
    }
    else if(this->type == "rational" && b->type == "integer") return true;
    else if(this->type == "multiple" && b->type == "multiple"){
        MultipleExpressions *t = (MultipleExpressions *)this;
        MultipleExpressions *m = (MultipleExpressions *)b;
        if ((t->meType == "as" && m->meType == "as") || (t->meType == "md" && m->meType == "md")) {
            return true;
        }
    }else if(this->type == "multiple" || b->type == "multiple") return true;
    return false;
}
