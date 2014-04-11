
//
//  Rational.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Rational.h"
Rational::Rational(int numerator, int denominator){     //constructor for rational with two integers
    this->type = "rational";
    this->numerator = numerator;
    this->denominator = denominator;
    this->eNumerator = new Integer(numerator);
    this->eDenominator = new Integer(denominator);
    simplify(numerator);

}
Rational::Rational(Expression* numerator, Expression* denominator){     //constructor for rational that has more complicated numerator and/or denominator
    this->type = "rational";
    if (numerator->type == denominator->type && numerator->type != "integer") {
        this->eNumerator = new Integer(1);
        this->eDenominator = new Integer(1);
    }else{
        this->eNumerator = numerator;
        this->eDenominator = denominator;
        simplify(numerator);
    }
}

Rational::~Rational(){
    delete this->eNumerator;
    delete this->eDenominator;
    
}
Expression* Rational::geteDenominator(){
    return this->eDenominator;
}
void Rational::setDenominator(Expression* denominator){
    this->eDenominator = denominator;
}

Expression* Rational::geteNumerator(){
    return this->eNumerator;
}
void Rational::setNumerator(Expression* numerator){
    this->eNumerator = numerator;
}
int Rational::getNumerator(){
    return this->numerator;
}
int Rational::getDenominator(){
    return this->denominator;
}
bool Rational::hasIntegerOperands(){
    if(this->numerator){
        return true;
    }else return false;
}






Expression* Rational::simplify(int num){
    //if numerator and denominator are both type pi or type Euler, then simplify to one.
    
    if(this->numerator == 1 || this->numerator == -1){   //if the numerator is 1, it's already simplified
        return this;
    }
    
    else if(this->numerator % this->denominator == 0 ){   //the numerator and denominator are evenly divisible
        this->numerator = this->numerator/this->denominator;
        this->denominator = 1;
    }
    else if(this->denominator % this->numerator == 0){
        if(this->numerator < 0){
            this->denominator = this->denominator/(-this->numerator);
        }else{
            this->denominator = this->denominator/this->numerator;
        }
        if(this->numerator < 0) this->numerator = -1;
        else this->numerator = 1;

    }
    
    else{
        int commonFactor = findCommonFactor(2);
        while (commonFactor != -1) {
            this->numerator = this->numerator/commonFactor;
            this->denominator = this->denominator/commonFactor;
            syncExpToInt();
            commonFactor = findCommonFactor(2);
        }
    }
    if(denominator < 0 && numerator > 0){
        denominator *= -1;
        numerator *= -1;
        syncExpToInt();
    }
    return this;
}
Expression* Rational::simplify(Expression* eNumerator){

    return this;
}
Rational* Rational::findCommonDenominator(Rational* a){
    
    //      a = -2/1
    //      this = -7/4
    //
    if(a->hasIntegerOperands()){
        int aNum = a->getNumerator();           // aNum = -2
        int aDen = a->getDenominator();         //aDen = 1
        aNum *= this->denominator;              // aNum = -8
        this->numerator *= aDen;                // numerator = 1
        Integer *num = new Integer(this->numerator);    //num = 1
        eNumerator = num;                               //eNumerator = 1
        aDen *= this->denominator;                      // aDen = 4
        this->denominator *= a->getDenominator();       //denominator = 4
        Integer *den = new Integer(this->denominator); //den = 4
        eDenominator = den;                             //edenominator = 4
        a->setNumerator(new Integer(aNum));             //numerator = -2
        a->setDenominator(new Integer(aDen));           //denominator = 1
        
        Integer *v = (Integer *)a->geteNumerator();
        a->numerator = v->getValue();
        
        Integer *w = (Integer *)a->geteDenominator();
        a->denominator = w->getValue();
        //a->simplify(1);
    }
    return a;
}

int Rational::findCommonFactor(int n){
    if(n > 9){
        return -1;
    }
    else if(this->numerator % n == 0 && this->denominator % n == 0){
        return n;
    }else{
        return findCommonFactor(n+1);
    }
}

Expression* Rational::add(Expression* a){
    if(a->type == "integer"){
        
        Integer *b = (Integer *)a;
        if(this->numerator){
            Rational *c = new Rational(b->getValue() * denominator, denominator);
            this->add(c);
        }
        
    }else if(a->type == "rational"){

        Rational *b =  (Rational *)a;                                    //cast expression as Rational type
        Rational *commonD = this->findCommonDenominator(b);             //Find a common denominator between "this" and the passed expression. Save that to commonD
        
        if(commonD->hasIntegerOperands()){                              //If it has integer operands
            Integer *in = (Integer *)commonD->eNumerator;               //Make an Integer type for the numerator of the first rational
            Integer *in2 = (Integer *)eNumerator;                       //Make an Integer type for this numerator
            
            this->eNumerator = new Integer(in->getValue() + in2->getValue());     //Set the value of the numerator to the addition of the two numerators. We can do this because
                                                                        //They already share a common denominator
            Integer *num1 = (Integer *)eNumerator;                      //update the value of numerator to match eNumerator
            this->numerator = num1->getValue();
            
            Integer *den1 = (Integer *)eDenominator;                    //update the value of denominator to match eDenominator
            this->denominator = den1->getValue();
            
            this->simplify(1);                                          //call the simplify method for integer only rationals
            
            Integer *num = new Integer(this->numerator);                //update the value of eNumerator to match numerator
            Integer *den = new Integer(this->denominator);              //update the value of eDenominator to match denominator
            if((num->getValue() < 0) && (den->getValue() < 0)){
                Integer *g = new Integer(-1);
                eNumerator->multiply(g);
                
                eDenominator->multiply(g);

            }else{
                eNumerator = num;
                eDenominator = den;
            }
        }else{
            cout << "non integer rational operands not yet implemented. Returning first argument" << endl;
        }
        
        
    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}
Expression* Rational::subtract(Expression* a){
    if(a->type == "integer"){
        Integer *b = (Integer *)a;
        if(this->numerator){
            Rational *c = new Rational(b->getValue() * denominator, denominator);
            this->subtract(c);
        }
    }else if(a->type == "rational"){
        Rational *b = (Rational *)a;                                    //cast expression as Rational type
        Rational *commonD = (Rational *)this->findCommonDenominator(b); //Find a common denominator between "this" and the passed expression. Save that to commonD
        
        if(commonD->hasIntegerOperands()){                              //If it has integer operands
            Integer *in2 = (Integer *)commonD->eNumerator;               //Make an Integer type for the numerator of the first rational
            Integer *in = (Integer *)eNumerator;                       //Make an Integer type for this numerator
            
           this->eNumerator = new Integer(in->getValue() - in2->getValue());     //Set the value of the numerator to the addition of the two numerators. We can do this because

            //They already share a common denominator
            Integer *num1 = (Integer *)eNumerator;                      //update the value of numerator to match eNumerator
            this->numerator = num1->getValue();
            
            Integer *den1 = (Integer *)eDenominator;                    //update the value of denominator to match eDenominator
            this->denominator = den1->getValue();
            
            this->simplify(1);                                          //call the simplify method for integer only rationals
            
            Integer *num = new Integer(this->numerator);                //update the value of eNumerator to match numerator
            Integer *den = new Integer(this->denominator);              //update the value of eDenominator to match denominator
            if((num->getValue() < 0) && (den->getValue() < 0)){
                Integer *g = new Integer(-1);
                eNumerator->multiply(g);
                
                eDenominator->multiply(g);

            }else{
                eNumerator = num;
                eDenominator = den;
            }
        }else{
            cout << "non integer rational operands not yet implemented. Returning first argument" << endl;
        }
    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}
Expression* Rational::multiply(Expression* a){
    if(a->type == "integer"){
        Integer *b = (Integer *)a;
        if(this->numerator){
            Rational *c = new Rational(b->getValue() * denominator, denominator);
            c->syncIntToExp();
            Rational *z = (Rational *)this->multiply(c);
            this->numerator = z->getNumerator();
            this->denominator = z->getDenominator();
            this->eDenominator = z->geteDenominator();
            this->eNumerator = z->geteNumerator();
        }
    }else if(a->type == "rational"){
        Rational *b = (Rational *)a;                                    //cast expression as Rational type
        b->eNumerator->multiply(this->eNumerator);
        b->eDenominator->multiply(this->eDenominator);
        Integer *num = (Integer *)b->eNumerator;
        b->numerator = num->getValue();
        Integer *den = (Integer *)b->eDenominator;
        b->denominator = den->getValue();
        b->simplify(1);
        return b;
    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}
Expression* Rational::divide(Expression* a){
    if(a->type == "integer"){
        Integer *b = (Integer *)a;
        if(this->numerator){
            Rational *c = new Rational(b->getValue() * denominator, denominator);
            this->divide(c);
        }
    }else if(a->type == "rational"){
        Rational *b = (Rational *)a;                                    //cast expression as Rational type
        Expression *den1 = b->eNumerator;
        b->eNumerator = b->eDenominator;
        b->eDenominator = den1;
        b->syncIntToExp();
        
        b->eNumerator->multiply(this->eNumerator);
        b->eDenominator->multiply(this->eDenominator);
        Integer *num = (Integer *)b->eNumerator;
        b->numerator = num->getValue();
        Integer *den = (Integer *)b->eDenominator;
        b->denominator = den->getValue();
        b->simplify(1);
        return b;
    }
    else{
        cout << "type not recognized" << endl;
    }
    return this;
}
void Rational::syncExpToInt(){
    Expression *a = new Integer(this->numerator);
    Expression *b = new Integer(this->denominator);
    this->eNumerator = a;
    this->eDenominator = b;
}
void Rational::syncIntToExp(){
    Integer *a = (Integer *)eNumerator;
    this->numerator = a->getValue();
    
    Integer *b = (Integer *)eDenominator;
    this->denominator = b->getValue();
}
ostream& Rational::print(std::ostream& output) const{
    cout << *eNumerator << "/" << *eDenominator;
    return output;
}
string Rational::toString(){
    stringstream s;
    s << *eNumerator << "/" << *eDenominator;
    return s.str();
}

