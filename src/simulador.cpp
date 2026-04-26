#include "simulador.h"

// necesito pow() para el calculo de lambda
#include <cmath>
#include <iostream>

using namespace std;

// el simulador solo existe para la prueba base al arrancar el programa
Simulador::Simulador() {
}

// formula del enunciado: lambda = mu * (GF_a / mu)^alpha * (GC_b / mu)^beta
// basicamente: cuanto mas goles hace A y mas goles recibe B, mas alto el lambda
double Simulador::calcularlambda(double golesfavora, double golescontrab) const {
    double alpha = 0.6;  // el ataque propio pesa mas que la defensa rival
    double beta = 0.4;
    double mu = 1.35;    // promedio historico de goles por partido en mundiales

    double gfa = golesfavora;
    double gcb = golescontrab;

    // si no tiene datos en el csv uso el promedio mundial como punto de partida
    if (gfa <= 0.0) {
        gfa = mu;
    }

    if (gcb <= 0.0) {
        gcb = mu;
    }

    double factorataque = pow(gfa / mu, alpha);
    double factordefensa = pow(gcb / mu, beta);
    double lambda = mu * factorataque * factordefensa;

    if (lambda < 0.2) {
        lambda = 0.2;  // minimo pa que siempre haya chance de marcar
    }

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
