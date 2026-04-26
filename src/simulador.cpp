#include "simulador.h"

// necesito pow() para el calculo de lambda
#include <cmath>
#include <iostream>

using namespace std;

// el simulador solo existe para la prueba base al arrancar el programa
Simulador::Simulador() {
}

// mismo calculo de gol esperado que usa el torneo
// mas ataque propio y mas fragilidad del rival dan un lambda mas alto
double Simulador::calcularlambda(double golesfavora, double golescontrab) const {
    double alpha = 0.6;  // el ataque propio pesa mas que la defensa rival
    double beta = 0.4;
    double mu = 1.35;    // promedio historico de goles por partido en mundiales

    double factorataque = pow(golesfavora / mu, alpha);
    double factordefensa = pow(golescontrab / mu, beta);
    double lambda = mu * factorataque * factordefensa;

    return lambda;
}

// el torneo usa Poisson para los goles, pero aqui solo redondeo simple para la prueba
int Simulador::redondeargoles(double lambda) const {
    int goles = int(lambda + 0.5);

    if (goles < 0) {
        goles = 0;
    }

    return goles;
}

// calcula lambda y marcador estimado entre los dos primeros equipos del csv
// sirve para confirmar que el modulo de simulacion esta funcionando
void Simulador::probar(const Repositorio& repo) {
    cout << "Modulo sim listo" << endl;

    if (repo.getcantidadequipos() < 2) {
        return;
    }

    string equipoa = repo.getequipo(0);
    string equipob = repo.getequipo(1);

    // sus promedios historicos vienen del csv
    double gfahistorico = repo.getgolesfavorhistorico(0);
    double gcbhistorico = repo.getgolescontrahistorico(1);
    double gfbhistorico = repo.getgolesfavorhistorico(1);
    double gcahistorico = repo.getgolescontrahistorico(0);

    // calculo lambda para cada equipo: cada uno ataca contra la defensa del otro
    double lambdaa = calcularlambda(gfahistorico, gcbhistorico);
    double lambdab = calcularlambda(gfbhistorico, gcahistorico);

    // redondeo a goles enteros para mostrar un marcador estimado
    int golesa = redondeargoles(lambdaa);
    int golesb = redondeargoles(lambdab);

    cout << "lambda base prueba" << endl;
    cout << "  " << equipoa << " vs " << equipob << endl;
    cout << "  promedio de gol (\u03BB) " << equipoa << ": " << lambdaa << endl;
    cout << "  promedio de gol (\u03BB) " << equipob << ": " << lambdab << endl;
    cout << "  marcador estimado: " << golesa << " - " << golesb << endl;
}
