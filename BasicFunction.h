//
//  Problema 1
//  Ludovico Lapo Luperi
//  ludovicolapo.luperi@studenti.unimi.it
//

/* Obiettivo del codice
 Generare variabili pseudocasuali, calcolarne medie e varianze e confrontarle con i calcoli esatti
 */

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;

#pragma once
class BasicFunction{
    public:
        BasicFunction(){};
        virtual double Evaluate(double x) const = 0;
        virtual ~BasicFunction(){};
        double Sign(double value) const{if(Evaluate(value) >= 0) return 1; return -1;};
};

#pragma once
class Sin: public BasicFunction{
public:
    Sin(): BasicFunction(){};
    virtual ~Sin(){};
    Sin(double value){x = value;};
    double Evaluate(double x) const override{ return sin(x);};
    
private:
    double x;
};

#pragma once
class Gauss: public BasicFunction{
public:
    Gauss(): BasicFunction(){};
    Gauss(double m, double s){ mean = m; sigma = s;}
    virtual ~Gauss(){};
    double Evaluate(double x) const override{return sqrt(1/(2*M_PI*pow(sigma,2)))*exp(-pow(((x-mean)/sigma),2)/2);};
    double GetMax() const {return sqrt(1/(2*M_PI*pow(sigma,2)));};
    
private:
    double mean, sigma;
};

#pragma once
class Parable: public BasicFunction{
    
    public:
        //Constructors
        Parable(){};
        Parable(double ax2, double bx, double c0){c_a = ax2; c_b = bx; c_c = c0;}
        
        //Destructor
        virtual ~Parable(){};
        
        double Evaluate(double x) const override {return c_a*x*x+c_b*x+c_c;};
        
        double Get_a        () const{ return c_a;};
        double Get_b        () const{ return c_b;};
        double Get_c        () const{ return c_c;};
        double Get_xv       () const{ return c_xv;};
        double Get_yv       () const{ return c_yv;};
        
        void Set_a      (double value){c_a = value;};
        void Set_b      (double value){c_b = value;};
        void Set_c      (double value){c_c = value;};
        void Set_xv (){c_xv = -Get_b()/(2*Get_a());};
        void Set_yv (){c_yv = -(pow(Get_b(),2)-(4*Get_a()*Get_c()))/(4*Get_a());};
    
        
        void CalculateVertixAxis(double sens){Set_xv(); Set_yv();}
    
        void Print() const{
            cout << "Parable data:\t\t";
            
            //OUTPUT STYLE
            if(Get_a() == 1) cout << "ƒ(x) = x\u00b2";
            if(Get_a() == -1) cout << "ƒ(x) = -x\u00b2";
            if(Get_a() != -1 and Get_a() != 1) cout << "ƒ(x) = " << Get_a() << "x\u00b2";
            
            if(Get_b() == 1) cout << "+x";
            if(Get_b() == -1) cout << "-x";
            if(Get_b() != -1 and Get_b() != 1){
                if(Get_b() > 0) cout << "+" << Get_b() << "x";
                if(Get_b() < 0) cout << Get_b() << "x";
            }
            
            if(Get_c() == 1) cout << "+" << Get_c();
            if(Get_c() != -1 and Get_c() != 1){
                if(Get_c() > 0) cout << "+" << Get_c();
                if(Get_c() < 0) cout << Get_c();
            }
            
            cout << endl;
        }
        void PrintVertixAxis(int sens) const{
            cout << "\nApex:\t\t\t" << "x\u2090:\t";
            if(c_xv >=0) cout << fixed << setprecision(sens) << "+" << fabs(c_xv) << endl;
            else cout << fixed << setprecision(sens) << (c_xv) << endl;
            cout << "\n\t\t\ty\u2090:\t";
            if(c_yv >=0) cout << fixed << setprecision(sens) << "+" << fabs(c_yv) << endl;
            else cout << fixed << setprecision(sens) << (c_yv) << endl;
        }
        
    private:
        double c_a,c_b,c_c;
        double c_xv,c_yv;
    
};
