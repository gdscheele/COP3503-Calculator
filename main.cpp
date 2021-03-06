//
//  main.cpp
//  Calculator
//
//  Created by Gavin Scheele on 4/6/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Solver.h"
using namespace std;
int main(int argc, char * argv[])  {
    
    cout << "Welcome to the calculator. Please insert spaces between every operator and operand. Examples are provided in the 'help' section of the Menu.\n" << endl;
    string choice = "z";
    bool useAns = false;
    string previousExpression = "";
    string floatExpression = "";
    while (choice.compare("d") != 0 && choice.compare("D") != 0) {
        cout << "Menu" << "\n" <<
        "a. Compute a new expression" << "\n" <<
        "b. Help" << "\n" <<
        "c. Review previous expressions and answers" << "\n" <<
        "d. Quit" << "\n";

        cin >> choice;
        cout << "\n";


        if (choice.compare("a") == 0 || choice.compare("A") == 0) {
            string secondChoice = "n";
            while (secondChoice.compare("y") != 0 && secondChoice.compare("Y") != 0) {
                cout << "Enter an Expression:" << endl;
                string expression;
                cin.ignore();
                std::getline(cin, expression);
                Solver *s = new Solver();
                if (useAns) {
                    string ans = *new string("ans");
                    const string to = *new string(previousExpression);
                    s->replace(expression, ans, to);
                }
                try{
                    s = new Solver(expression);
                    floatExpression = expression;
                    previousExpression = s->solve(false);
                    cout << "Result: " << previousExpression << endl;
                }catch(runtime_error &e){
                    cerr << e.what() << endl;
                }
                // cin >> expression;
                //that's the input - I don't know how you want to handle it
                cout <<"\n" << "Would you like to go back to the main menu? (y/n)" << "\n";
                cin >> secondChoice;
                cout << "\n";
            }
        }


        else if (choice.compare("b") == 0 || choice.compare("B") == 0) {
            cout << "Directions for Use of This Program" << endl;
            cout << "----------------------------------" << endl;
            cout << "*Enter 'a' from the menu to begin a calculation" << endl;
            cout << "*Calculation operands and operations should each be seperated by a space" << endl;
            cout << "*Ex: ( 4 + 3 ) - log_3:(2) - log_pi:(pi * pi) * ( e ^ 2 ) / ( pi ^ 2 ) + 2rt:8 + 2 / 3" << endl;
            cout << "*After each calculation, enter 'y' to proceed with another calculation, or 'n' to go back to the main menu" << endl;
            cout << "*Enter 'c' from the main menu to view previous answers normally or in float form" << endl;
            cout << "*From this menu, you can also refer to the previous answer as 'ans'" << endl;
            cout << "*Enter 'd' from the main menu is you want to exit the program" << endl;
            cout << endl;
        }


        else if (choice.compare("c") == 0 || choice.compare("C") == 0) {
            //we're screwed
            string thirdChoice = "z";
            cout << "Sub-Options \n" <<
            "a. Show the float form of the last expression" << "\n" <<
            "b. Set 'ans' equal to the previous expression's answer \n";
            cin >> thirdChoice;
            if (thirdChoice.compare("a") == 0 || thirdChoice.compare("A") == 0) {
                Solver *s = new Solver(floatExpression);
                cout << s->solve(true) << endl;
            }
            else if (thirdChoice.compare("b") == 0 || thirdChoice.compare("B") == 0) {
                useAns = true;
            }
            else {
                cout << "Sorry, couldn't recognize your input \n";
            }
        }else if(choice.compare("d") != 0 && choice.compare("D") != 0){
            cout << "Sorry, couldn't recognize your input." << "\n";
        }
    }
    cout << "Thank You. Have A Nice Day." << "\n";
    return 0;

}

 //    Rational *a = new Rational(2,1);
 //    Rational *b = new Rational(1,-8);
 //    Rational *c = new Rational(2,1);
 //    Integer *d = new Integer(4);
 //    Integer *e = new Integer(-1);
 //    Integer *f = new Integer(0);
 //
 //    cout << *a->add(c) << endl;
 //    cout << *a->subtract(d) << endl;
 //    cout << *a->multiply(e) << endl;
 //    cout << *a->divide(b) << endl;


/*
Euler* em = new Euler();
Expression* el = new Integer(0);
el->exp = "e * 3";
 Logarithm* log = new Logarithm(em,em);

cout<<*log->simplify();

 //Solver *s = new Solver("");
 //cout << s->solve() << endl;;


 return 0;
 }
=======
//
//
//Euler* em = new Euler();
//Expression* el = new Integer(0);
//el->exp = "e * 3";
// Logarithm* log = new Logarithm(em,em);
//
//cout<<*log->simplify();
//
// //Solver *s = new Solver("");
// //cout << s->solve() << endl;;
//
//
// return 0;
// }

*/
