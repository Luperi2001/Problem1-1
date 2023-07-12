//
//  Problema 1
//  Ludovico Lapo Luperi
//  ludovicolapo.luperi@studenti.unimi.it
//

/* Obiettivo del codice
 Generare variabili pseudocasuali, calcolarne medie e varianze e confrontarle con i calcoli esatti
 */

/*Results and issues
 Le r_i non sono correlate, quindi media nulla per ogni caso e varianza data dalla somma delle varianze
 All'aumentare del numero di variabili non correlate aumenta la varianza della variabile x e la curva tende a una distribuzione normale standard (aka gaussiana) (teorema limite centrale verificato)
 Mancano i dati/una trattazione migliore del fit del punto c; è facoltativo, ma lo voglio fare
 Il multigraph è per evdere come la curva tenda a una gaussiana all'aumentare del numero di variabili che costituiscono la x
 */
#include <iostream>
#include <stdio.h>
#include <cassert>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <vector>
#include <cassert>
#include <algorithm>  // algoritmi STL
#include <numeric>    // inner_product

#include "random.h"

//ROOT
#include "TApplication.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TGraph.h"
#include "TNamed.h"
#include "TColor.h"
#include "TH1F.h"
#include "TStyle.h"

using namespace std;

const int Times = pow(10,4);

void RootGraphs(RandomGenerator &RandomNumber);

int main(int argc, const char * argv[]){
    
    assert(argc == 2 && "Syntax:\t <nome_eseguibilie> <seed>");
    
    RandomGenerator RandomNumber(atoi(argv[1]));
    RootGraphs(RandomNumber);
    
    cout << "\n\n\n";
    return 0;
}

void RootGraphs(RandomGenerator &RandomNumber){
    TApplication app ("app",0,0);
    TH1F UnifGraph2("Uniform2", "Uniform2", 100, -1.5, 1.5);
    TH1F UnifGraph4("Uniform4", "Uniform4", 100, -2.5, 2.5);
    TH1F UnifGraph12("Uniform12", "Uniform12", 100, -6.5, 6.5);
    
    double x = 0;
    for(int i = 0; i<Times;i++){
        
        //Riempiemento primo grafico
        for(int j = 0; j<2;j++) x+= RandomNumber.Unif(0,1);
        x -= 1;
        UnifGraph2.Fill(x);
        x = 0;
        //Riempiemento secondo grafico
        for(int j = 0; j<4;j++) x+= RandomNumber.Unif(0,1);
        x -= 2;
        UnifGraph4.Fill(x);
        x=0;
        //Riempiemento terzo grafico
        for(int j = 0; j<12;j++) x+= RandomNumber.Unif(0,1);
        x -= 6;
        UnifGraph12.Fill(x);
        x=0;
    }
    
    
    //Riempimento grafico per limite centrale
    TH1F UnifGraphA("MultiGraph", "MultiGraph", 100, -10, 10);
    TH1F UnifGraphB("MultiGraphB", "MultiGraphB", 100, -10, 10);
    TH1F UnifGraphC("MultiGraphC", "MultiGraphC", 100, -10, 10);
    TH1F UnifGraphD("MultiGraphD", "MultiGraphD", 100, -10, 10);
    TH1F UnifGraphE("MultiGraphE", "MultiGraphE", 100, -10, 10);
    TH1F UnifGraphF("MultiGraphF", "MultiGraphF", 100, -10, 10);
    
    int j;
    int npoints = 2;
    for(int i = 0; i<Times*10;i++){
        //A
        for(j = 1; j<=npoints;j++) x+= RandomNumber.Unif(0,1); x -= j/2;
        UnifGraphA.Fill(x);
        x = 0;
        //B
        for(j = 1; j<=npoints*2;j++) x+= RandomNumber.Unif(0,1); x -= j/2;
        UnifGraphB.Fill(x);
        x = 0;
        //C
        for(j = 1; j<=npoints*4;j++) x+= RandomNumber.Unif(0,1); x -= j/2;
        UnifGraphC.Fill(x);
        x = 0;
        //D
        for(j = 1; j<=npoints*8;j++) x+= RandomNumber.Unif(0,1); x -= j/2;
        UnifGraphD.Fill(x);
        x = 0;
        //E
        for(j = 1; j<=npoints*16;j++) x+= RandomNumber.Unif(0,1); x -= j/2;
        UnifGraphE.Fill(x);
        x = 0;
        //F
        for(j = 1; j<=npoints*32;j++) x+= RandomNumber.Unif(0,1); x -= j/2;
        UnifGraphF.Fill(x);
        x = 0;
    }
        
    //Stampa dati
    double Mean = 0;
    double Variance = 0;
    
    cout << "Punto a" << endl;
    cout << "Media di x da ROOT:\t\t\t" << UnifGraph2.GetMean() << endl;
    for(int i = 0; i<2;i++) Mean += 0.5; Mean -=1;
    cout << "Media di x da calcolo esatto:\t\t"<< Mean << endl;
    //cout << "Discrepanza ROOT-calcolo:\t\t" << UnifGraph2.GetMean()-Mean << endl;
    cout << "Varianza di x da ROOT:\t\t\t" << pow(UnifGraph2.GetStdDev(),2) << endl;
    for(int i = 0; i<2;i++) Variance += 0.0833;
    cout << "Varianza di x da calcolo esatto:\t" << Variance << endl;
    Mean = 0;
    Variance = 0;
    cout << endl;
    
    cout << "Punto b" << endl;
    cout << "Media di x da ROOT:\t\t\t" << UnifGraph4.GetMean() << endl;
    for(int i = 0; i<4;i++) Mean += 0.5; Mean -=2;
    cout << "Media di x da calcolo esatto:\t\t"<< Mean << endl;
    //cout << "Discrepanza ROOT-calcolo:\t\t" << UnifGraph4.GetMean()-Mean << endl;
    cout << "Varianza di x da ROOT:\t\t\t" << pow(UnifGraph4.GetStdDev(),2) << endl;
    for(int i = 0; i<4;i++) Variance += 0.0833;
    cout << "Varianza di x da calcolo esatto:\t" << Variance << endl;
    Mean = 0;
    Variance = 0;
    cout << endl;
    
    cout << "Punto c" << endl;
    cout << "Media di x da ROOT:\t\t\t" << UnifGraph12.GetMean() << endl;
    for(int i = 0; i<12;i++) Mean += 0.5; Mean -=6;
    cout << "Media di x da calcolo esatto:\t\t"<< Mean << endl;
    //cout << "Discrepanza ROOT-calcolo:\t\t" << UnifGraph12.GetMean()-Mean << endl;
    cout << "Varianza di x da ROOT:\t\t\t" << pow(UnifGraph12.GetStdDev(),2) << endl;
    for(int i = 0; i<12;i++) Variance += 0.0833;
    cout << "Varianza di x da calcolo esatto:\t" << Variance << endl;
    Mean = 0;
    Variance = 0;
    cout << endl;
    
    
    TCanvas alpha;
    alpha.Divide(2,2);
    alpha.cd(1);
    UnifGraph2.GetXaxis() -> SetTitle("Value [AU]");
    UnifGraph2.GetYaxis() -> SetTitle("Number of events");
    UnifGraph2.Draw();
    
    alpha.cd(2);
    UnifGraph4.GetXaxis() -> SetTitle("Value [AU]");
    UnifGraph4.GetYaxis() -> SetTitle("Number of events");
    UnifGraph4.Draw();
    
    alpha.cd(3);
    UnifGraph12.GetXaxis() -> SetTitle("Value [AU]");
    UnifGraph12.GetYaxis() -> SetTitle("Number of events");
    UnifGraph12.Draw();
    gStyle->SetOptFit(1111);
    UnifGraph12.Fit("gausn","L");
    
    alpha.cd(4);
    UnifGraphA.SetLineColor(1);
    UnifGraphB.SetLineColor(2);
    UnifGraphC.SetLineColor(3);
    UnifGraphD.SetLineColor(4);
    UnifGraphE.SetLineColor(5);
    UnifGraphF.SetLineColor(6);
    
    UnifGraphA.GetXaxis() -> SetTitle("Value [AU]");
    UnifGraphA.GetYaxis() -> SetTitle("Number of events");
    
    UnifGraphA.Draw("apl");
    UnifGraphB.Draw("apl same");
    UnifGraphC.Draw("apl same");
    UnifGraphD.Draw("apl same");
    UnifGraphE.Draw("apl same");
    UnifGraphF.Draw("apl same");
    
    app.Run();
}
